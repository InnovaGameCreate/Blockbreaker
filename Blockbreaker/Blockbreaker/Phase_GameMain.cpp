#include "MainFunc.h"


Phase_GameMain::Phase_GameMain() {
	//ポーズメニューの項目を作成
	pauseMenu.addItem(_T("再開"), 3, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("やり直す"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("トップメニューへ"), 8, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.setScrolltype(1);
	pauseMenu.sethaba(50);
	pauseMenu.setCenteringMode(0);
}


Phase_GameMain::~Phase_GameMain() {
}

//初期化(描画処理)
void Phase_GameMain::Init_Draw() {
	//ゲーム画面の生成(後でシェーダを使いたいので2のn乗のサイズで作成します)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("ウィンドウ作成に失敗しました"));

	tex_Block.Init_Draw();	//ブロック画像のロード
	
	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/colorbom.png)"));
	if ((Tex_FieldBack = LoadGraph(_T("Data/image/BlockField_Back.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/BlockField_Back.png)"));


	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);

	//全フィールドブロックの初期化を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Init_Draw();
		}
	}

	//BGM再生
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

	pauseMenu.setEnable(TRUE);
}

//フルスクリーンに復帰時に呼ばれる
void Phase_GameMain::RestoreGraphCallback() {

}

//初期化(計算処理)
void Phase_GameMain::Init_Update() {
	//全フィールドブロックの初期化を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Init_Update();
		}
	}

	Restart();	//リスタート


}

//リスタート
void Phase_GameMain::Restart() {
	Flag_Pause = PauseMode_NO;
	Flag_pauseRequest = PauseMode_NO;
	Count_PlayTime = 0;
	Count_GameTime = 0;
	Count_Time = 0;
	Count_Pause = 0;
	Count_Turn = 0;
	Count_lay = 0;
	lay.SetpointNum(0);
	//落下中ブロックの初期化
	fallBlockInfo.Restart();
	score.init();//スコアの初期化

	//全フィールドブロックのリスタート処理を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Restart();
		}
	}

	//適当にブロックを設置する(下から複数段)
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL, BLOCK_WIDTHNUM_INGAME, BLOCK_DEFAULT_VAL);

	//仮想ブロックの更新を行う
	Virtualfield_Update();

	//ゲームサイクルをブロック落下に設定
	setGameCycle(GameCycle_FALL);

	//BGMを最初から再生し直す
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);


	printLog_I(_T("ステージを最初からやり直しました(Restart)"));
}

//描画処理
void Phase_GameMain::Draw() {


	//描画先をゲーム画面にする
	SetDrawScreen(gameWindow);
	ClearDrawScreen();

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawGraph(BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE, Tex_FieldBack, FALSE);

	fallBlockInfo.Draw();	//落下ブロックの描画

	Draw_FieldBlock();	//フィールドブロックの描画

	//破壊光線の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawPolygon2D_Notexture2(&lay, GetColor(200, 200, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フライテキストを描画する
	flyText.Draw();


	//デバッグ
#ifdef _DEBUG_GAMEMAIN_
	//ゲームオーバー領域を描画する
	double tY;
	Block_Field::Convert_Ingame_FromBlock(0, GAMEOVER_BORDER, 0, 0, NULL, &tY);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, WINDOW_WIDTH, (int)tY, GetColor(0, 255, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//縦横BLOCK_SIZE間隔で線を描画する
	for (int i = BLOCK_PADDINGLEFT + 1; i < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; i++) {
		DrawLine(i * BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE,
			i * BLOCK_SIZE, GAMEWINDOW_HEIGHT + BLOCK_PADDINGUP*BLOCK_SIZE,
			GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = BLOCK_PADDINGUP + 1; i < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; i++) {
		DrawLine(BLOCK_PADDINGLEFT*BLOCK_SIZE, i * BLOCK_SIZE,
			GAMEWINDOW_WIDTH + BLOCK_PADDINGLEFT*BLOCK_SIZE,
			i * BLOCK_SIZE, GetColor(0xff, 0xbf, 0x74));
	}

	////落下ブロックの範囲を描画する
	//if (fallBlockInfo.isEnable()) {//落下ブロックが有効な時
	//	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
	//		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
	//			double X, Y;
	//			Block_Field::Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0, 0, &X, &Y);
	//			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//			DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), TRUE);
	//			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//			DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), FALSE);
	//		}
	//	}
	//}
#endif // _DEBUG_GAMEMAIN_



	//描画先をバックスクリーンにする
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲーム画面の背景画像を描画
	DrawGraph(0, 0, haikei, FALSE);

	Draw_NextFallBlock();	//次の落下ブロックの描画

	Draw_Status();	//ステータス描画

	//ゲーム画面を描画する
	//デバッグ
#ifdef _DEBUG_GAMEMAIN_
	//デバッグモードの場合、全ブロック領域を描画する
	DrawRectGraph(GAMEWINDOW_PADDINGX - BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_PADDINGY - BLOCK_PADDINGUP*BLOCK_SIZE, 0, 0, BLOCK_WIDTHNUM*BLOCK_SIZE, BLOCK_HEIGHTNUM*BLOCK_SIZE, gameWindow, FALSE, FALSE);
#else
	DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);
#endif


	//デバッグ
#ifdef _DEBUG_GAMEMAIN_
	//マス目の番号を描画
	for (int i = BLOCK_PADDINGLEFT; i < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; i++) {
		int Width = -GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
		Width += BLOCK_SIZE;
		Width /= 2;
		DrawFormatStringToHandle(GAMEWINDOW_PADDINGX + (i - BLOCK_PADDINGLEFT)*BLOCK_SIZE + Width, 30
			, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
	}
	for (int i = BLOCK_PADDINGUP; i < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; i++) {
		DrawFormatStringToHandle(20, GAMEWINDOW_PADDINGY + (i - BLOCK_PADDINGUP) * BLOCK_SIZE + 15,
			GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%2d"), i);
	}
#endif // _DEBUG_GAMEMAIN_


	switch (getPauseMode()) {
	case PauseMode_NOMAL:
		//ポーズ状態と分かるように描画する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (Count_Pause % 120 <= 80)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("PAUSE"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);

		//選択肢の項目の描画
		pauseMenu.Draw();
		break;
	case PauseMode_GameOver:
	{
		//だんだん濃くする
		int Alpha = 200;
		Alpha = (int)(Alpha * Count_Pause / 300.);
		if (Alpha > 200)	Alpha = 200;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//上から文字が落ちてくる
		const int strW = 60;
		int strX = (int)(WINDOW_WIDTH / 2. - strW * (9 / 2.));
		double strY = 460;

		strY = 460 * Count_Pause / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("G"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 30) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("A"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 60) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("M"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 90) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("E"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strX += strW;

		strY = 460 * (Count_Pause - 120) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("O"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 150) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("V"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 180) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("E"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 210) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("R"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);


		//選択肢の項目の描画
		pauseMenu.Draw();
	}
	break;
	case PauseMode_GameClear://ゲームクリア時
		Font_DrawStringCenterWithShadow(GAMEWINDOW_PADDINGX + GAMEWINDOW_WIDTH / 2, 300, _T("そこまで！"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
		
		//選択肢の項目の描画
		pauseMenu.Draw();
		break;
	}
}

//フィールドブロックの描画
void Phase_GameMain::Draw_FieldBlock() {

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {

			////ゲームオーバー時に下に落下させる
			//if (getPauseMode() == PauseMode_GameOver) {
			//	if (Count_Pause < 300)	Y += 1 / 2.*0.2*Count_Pause*Count_Pause;
			//	else					Y += 1 / 2.*0.2 * 300 * 300;
			//}

			field[x][y].Draw();


		}
	}
}

//ステータスの描画
void Phase_GameMain::Draw_Status() {
	//現在の経過ターン数の描画
	int placeX = 880;	//項目の基準位置
	int placeY = 60;	//項目の基準位置

	TCHAR str[100];
	Font_DrawStringWithShadow(placeX, placeY, _T("経過ターン数"), GetColor(0x00, 0xac, 0xd7), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%dターン"), Count_Turn);
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0x70, 0xe2, 0xff), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);

	placeY += 110;
	Font_DrawStringWithShadow(placeX, placeY, _T("ゲーム経過時間"), GetColor(0x13, 0xc6, 0x00), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%.2fs"), getCountGameTime() / 60.);
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0x90, 0xff, 0x85), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);

	placeY += 110;
	Font_DrawStringWithShadow(placeX, placeY, _T("操作経過時間"), GetColor(0xff, 0xa4, 0x38), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%.2fs"), getCountPlayTime() / 60.);
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0xd9, 0x8b, 0x30), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);

	placeY += 110;
	Font_DrawStringWithShadow(placeX, placeY, _T("獲得スコア"), GetColor(0xff, 0xa4, 0x38), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%d"), score.getScore());
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0xd9, 0x8b, 0x30), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);
}

//次の落下ブロックの描画
void Phase_GameMain::Draw_NextFallBlock() {
	fallBlockInfo.Draw_WaitLine();
}

//計算処理
void Phase_GameMain::Update() {
	//計算処理の最初に行いたい処理(多くなったら関数化？)

	//リクエストの反映
	if (Flag_pauseRequest != PauseMode_NUM) {
		Flag_Pause = Flag_pauseRequest;//リクエストの反映
		Flag_pauseRequest = PauseMode_NUM;
		Count_Pause = 0;
	}

	//カウンタの加算
	Update_Counter();

	GameMain_Key();	//キー処理

	//ポーズ時の処理をしてこの先には進まない
	switch (getPauseMode()) {
	case PauseMode_NOMAL:
		//選択肢の項目の更新
		pauseMenu.Update();
		return;
	case PauseMode_GameOver:
		pauseMenu.Update();
		return;
	case PauseMode_GameClear:
		pauseMenu.Update();
		return;
	}

	//破壊光線エフェクトの更新
	Update_Lay_BlockDel();
	//フライテキストの更新
	flyText.Update();

	//ブロック全体移動が有効な場合は、通常の処理を実行せず、全体移動のカウントアップのみ行うようにする
	if (Block_AllMovedata.isEnable() == TRUE) {
		Block_AllMovedata.Update();
		if (Block_AllMovedata.isEnable() == FALSE) {
			//移動完了の時
			int ToX, ToY;
			Block_AllMovedata.getToPoint(&ToX, &ToY);	//移動先に設定した座標を取得する
			Block_AllMove(ToX, ToY);					//ブロック全体を移動する
			UpdateBlockRequest(gameCycle);				//現在のゲームサイクルに割り込む形でブロックのアップデートを入れる
		}
		return;
	}

	switch (gameCycle) {
	case GameCycle_FALL:
		if (fallBlockInfo.getInterval() > 0) {
			//前回の落下ブロック終了から一定時間後
			Count_Turn++;	//経過ターンを加算する
			fallBlockInfo.Create_FallBlock();	//落下ブロックの再出現
		}
		//落下ブロックの落下処理
		if (fallBlockInfo.Update()) {
			//落下完了後は計算を行う
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
	{
		if (Count_Turn % 4 == 0 || getBlock_maxUpper() > BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL) {
			//下からブロックを沸かす
			under_Block();
		}
		else if (Count_Turn % 7 == 0) {
			int ran[5];
			randomTable.getRand_num(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT, ran, ARRAY_LENGTH(ran));
			for (int i = 0; i < ARRAY_LENGTH(ran); i++) {
				add_FraldBlock2(ran[i], BLOCK_PADDINGUP, BLOCK_TYPE_TREE);
			}
		}
		UpdateBlockRequest(GameCycle_FALL);
	}
	break;
	case GameCycle_Update://ブロックの計算
		Update_FieldBlock();
		break;
	}
}

//フィールドブロックの細々とした計算ループ
int Phase_GameMain::Update_FieldBlock() {
	/*
	ゲーム更新ループ
	0.初期化処理(最初の1度のみ実行)
	1.変化モーション
	2.重力計算
	3.移動モーション
	4.ブロックの特殊効果
	5.変化モーション
	6.重力計算
	7.移動モーション
	8.ブロックの消去判定→消去ブロック無しの場合は11へ
	9.変化モーション
	10.重力計算
	11.移動モーションから7へ
	12.更新ループ終了
	*/


	switch (Loop_No) {
	case 0://初期化

		ChainCount = 0;	//連鎖カウントをリセットする
		gameCycleFirstCallFlag = FALSE;	//ゲームサイクルが変更された時のフラグをFALSEに設定する

		//画面外ブロックを削除する
		Block_Delete_OutScreen();

		if (!gameCycleFirstCallFlag) {
			Loop_No = 1;
			printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 1://変化モーション
		if (Update_ChangeMotion() == FALSE) {
			//変化がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 2;
				printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 2://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 3;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 3://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 4;
				printLog_I(_T("ブロックの特殊効果へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 4://ブロックの特殊効果
		Block_Black_Func();		//黒ブロックの色変更
		Block_Rainbow_Func();	//虹色ブロックの色を変更
		Block_BOMB_Func();		//爆弾ブロックの処理
		Block_2BOMB_Func();		//2爆弾ブロックの処理
		Block_BOMBColor_Func();	//同色爆弾ブロックの処理
		Loop_No = 5;
		printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 5://変化モーション
		if (Update_ChangeMotion() == FALSE) {
			//変化がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 6;
				printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 6://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 7;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 7://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 8;
				printLog_I(_T("ブロックの消去判定へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 8://ブロックの消去判定
		if (Block_Delete() > 0) {
			//ブロックの消去判定が入れば
			ChainCount++;	//連鎖カウントを加算する
			//連鎖カウントを描画する(フライテキスト)
			if (ChainCount >= 2) flyText.addFlyText(GAMEWINDOW_WIDTH / 2., GAMEWINDOW_HEIGHT / 2., 60, FONTTYPE_GenJyuuGothicLHeavy_Edge60, GetColor(200, 200, 0), _T("%d連鎖！！"), ChainCount);


			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Loop_No = 9;
			printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		}
		else {
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 12;
				printLog_I(_T("終了処理へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 9://変化モーション
		if (Update_ChangeMotion() == FALSE) {
			//変化がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 10;
				printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 10://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 11;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 11://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 8;
				printLog_I(_T("ブロックの消去判定へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 12://終了
			//死亡判定を行う
		if (JudgeGameOver() != 0) {
			//ゲームオーバーラインを超えたら破壊光線でブロックを破壊する
			//Lay_BlockDel();
			Request_Pause(PauseMode_GameOver);
			//UpdateBlockRequest(GameCycle_Update);
		}
		else if (JudgeGameClear() == TRUE) {
			//クリア判定を行う
			Request_Pause(PauseMode_GameClear);

		}

		if (gameCycleFirstCallFlag) {
			Loop_No = 0;
			printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
		}
		else {

			Loop_No = -1;
			printLog_I(_T("ブロック計算ループの終了"));
			setGameCycle(Loop_Next);
		}
		break;
	default:
		printLog_E(_T("不明なLoop_Noが指定されました(無限ループ)(Loop_No=%d)"), Loop_No);
		break;
	}
	return 0;
}

//移動モーションの更新(移動モーションが行われたときはTRUE)
int Phase_GameMain::Update_MoveMotion() {
	int count = 0;//移動モーションが有効な数

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].getMoveMotion()->Update();
			if (field[x][y].getMoveMotion()->isEnable())	count++;//有効な場合は加算
		}
	}

	return ((count > 0) ? TRUE : FALSE);
}

//変化モーションの更新(変化モーションが行われたときはTRUE)
int Phase_GameMain::Update_ChangeMotion() {
	int count = 0;//移動処理を行ったブロックの数

	//変化モーションのカウントアップ
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].getChangeMotion()->Update();
			if(field[x][y].getChangeMotion()->isEnable())	count++;
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//カウンタのカウントアップ
void Phase_GameMain::Update_Counter() {

	//実際に操作をしている経過フレーム数の加算
	if (getPauseMode() == PauseMode_NO
		&& Block_AllMovedata.isEnable() == FALSE
		&& gameCycle == GameCycle_FALL) {
		Count_PlayTime++;
	}

	//ステージ経過時間のカウントアップ(通常プレイ時に加算する)
	if (getPauseMode() == PauseMode_NO) {
		Count_GameTime++;
	}

	//ゲーム経過フレーム数のカウントアップ
	if (getPauseMode() != PauseMode_NOMAL) {
		Count_Time++;
	}

	//ポーズ時のカウンタ
	if (getPauseMode() != PauseMode_NO)	Count_Pause++;
}

//Update後に呼ばれる
void Phase_GameMain::Update_Final() {
	/*描画スレッド用の座標を計算する*/

	//フィールド全体のズレを計算
	double Field_PaddingX = 0;
	double Field_PaddingY = 0;
	if (Block_AllMovedata.isEnable()) {//全体ずらすが有効な場合
		Field_PaddingX = Block_AllMovedata.getPointX() - BLOCK_SIZE/2.;
		Field_PaddingY = Block_AllMovedata.getPointY() - BLOCK_SIZE / 2.;
	}

	//フィールドブロックの座標計算
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//描画先の座標を計算する
			field[x][y].Update_DrawData(Field_PaddingX, Field_PaddingY, x, y);
		}
	}

	//落下ブロックの座標更新
	fallBlockInfo.Update_DrawData(Field_PaddingX, Field_PaddingY);

}

//終了処理(描画処理)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);

	tex_Block.Finalize_Draw();

	DeleteGraph(haikei);
	DeleteGraph(Tex_FieldBack);


	DeleteSoundMem(BGM);

}

//終了処理(計算処理)
void Phase_GameMain::Finalize_Update() {

}

//キー処理
void Phase_GameMain::GameMain_Key() {

	//ポーズ処理
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		if (getPauseMode() == PauseMode_NOMAL) {
			//ポーズ状態解除
			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Request_Pause(PauseMode_NO);	//ポーズ状態
		}
		else if (getPauseMode() == PauseMode_NO) {
			//ポーズに
			pauseMenu.setSelecedtItem(0);
			SoundEffect_Play(SE_TYPE_Pause);
			Request_Pause(PauseMode_NOMAL);	//ポーズ状態
		}
	}

	if (getPauseMode() != PauseMode_NO)	return;//ポーズ処理が入った場合はこの先は処理をしない

	if (getKeyBind(KEYBIND_UP) == 1) {
		//ブロックの設置
		//自殺防止
		int Flag = TRUE;//死亡領域にブロックがあったらFALSEになる
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < GAMEOVER_BORDER + 1; y++) {
				if (getBlockColor(x, y) != BLOCK_TYPE_NO) {
					//なんかブロックがある場合
					Flag = FALSE;
					break;
				}
			}
		}
		if (Flag)	under_Block();//上にブロックがない場合に実行される
	}

	if (!Block_AllMovedata.isEnable()) {
		//ブロックの全体移動を行っていないとき
		fallBlockInfo.Key();	//落下ブロックのキー処理
	}

	
}



//ポーズ状態の取得
Phase_GameMain::PauseMode Phase_GameMain::getPauseMode() {
	return Flag_Pause;
}

//ポーズ状態のリクエスト
void Phase_GameMain::Request_Pause(PauseMode pauseMode) {

	switch (pauseMode) {
	case PauseMode_NO:
		printLog_I(_T("【ポーズ解除】リクエスト"));
		break;
	case PauseMode_NOMAL:
		//ゲームオーバーのリクエストがある場合は上書きしない
		if (Flag_pauseRequest == PauseMode_GameOver)	return;
		printLog_I(_T("【通常ポーズ】リクエスト"));
		pauseMenu.setItemEnable(TRUE, 0);	//項目0を有効
		break;
	case PauseMode_GameOver:
		printLog_I(_T("【ゲームオーバーポーズ】リクエスト"));
		pauseMenu.setItemEnable(FALSE, 0);	//項目0を無効化
		break;
	case PauseMode_GameClear:
		printLog_I(_T("【ゲームクリアポーズ】リクエスト"));
		pauseMenu.setItemEnable(FALSE, 0);	//項目0を無効化
		break;
	}
	Flag_pauseRequest = pauseMode;
}

//フィールドにブロックを設置する
int Phase_GameMain::add_FraldBlock2(int X, int Y, BLOCK_TYPE type, int Override, int OutScreen, BLOCK_TYPE *Before, int UseVirtualField) {
	//前に設置されていたブロックの情報を初期化する
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;

	//現在設置されているブロックの取得
	const BLOCK_TYPE NowBlockType = getBlockColor(X, Y, TRUE, !OutScreen, UseVirtualField);

	//現在設置されているブロックが画面外ブロック(つまり範囲外の座標が渡された)場合は何もしない
	if (NowBlockType == BLOCK_TYPE_NUM) {
		return FALSE;
	}

	//変更を加えるブロックのクラスのポインタを設定する
	Block_Field *pblock = NULL;
	if (UseVirtualField) {//仮想フィールド使用の場合
		pblock = &Virtualfield[X][Y];
	}
	else {	//通常フィールド使用の場合
		pblock = &field[X][Y];
	}

	//ブロックの設置を行う
	const int ans = pblock->addBlcok(type, Override, Before);
	if (ans) {//ブロックの設置に成功した場合
		if(UseVirtualField)	printLog_I(_T("[仮想]フィールドブロック【新規生成】[%d][%d](type=%d)"), X, Y, type);
		else				printLog_I(_T("フィールドブロック【新規生成】[%d][%d](type=%d)"), X, Y, type);
	}

	return ans;
}

//下からブロックがわいてくる
void Phase_GameMain::under_Block() {
	if (Block_AllMovedata.isEnable())	return;//すでに実行中の場合は処理をしない
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN, BLOCK_WIDTHNUM_INGAME, 1);
	Block_AllMoveRequest(0, -1);	//ブロック全体を移動
}

//破壊光線でブロックを破壊する
void Phase_GameMain::Lay_BlockDel() {
	//レーザーのエフェクト
	lay.SetpointNum(3);	//三角形を設定
	lay.X[0] = GAMEWINDOW_WIDTH / 2.;
	lay.Y[0] = 0 + BLOCK_SIZE * BLOCK_PADDINGUP;
	lay.X[1] = 0;
	lay.Y[1] = BLOCK_SIZE * 3 + BLOCK_SIZE * BLOCK_PADDINGUP;
	lay.X[2] = 0;
	lay.Y[2] = BLOCK_SIZE * 12 + BLOCK_SIZE * BLOCK_PADDINGUP;
	Count_lay = 0;

	//エフェクト範囲のブロックを抹消する
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		for (int y = BLOCK_PADDINGUP + 3; y < BLOCK_PADDINGUP + 12; y++) {
			Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40, x*2 + 15);
		}
	}

	//スコアを減らす
	score.addScore(1, -1'0000);
}

//破壊光線エフェクトの更新
void Phase_GameMain::Update_Lay_BlockDel() {
	if (lay.getpointNum() == 3) {
		Count_lay++;
		if (Count_lay < 15) {
			//何もしない
		}
		else if(Count_lay < 45){
			//フレーム数の割合から位置を計算する
			lay.X[1] = GAMEWINDOW_WIDTH * ((Count_lay - 15) / 30.);
			lay.X[2] = GAMEWINDOW_WIDTH * ((Count_lay - 15) / 30.);
		}
		else if (Count_lay < 55) {
			lay.X[1] = GAMEWINDOW_WIDTH;
			lay.X[2] = GAMEWINDOW_WIDTH;
		}
		else {
			lay.SetpointNum(0);
		}
	}
}

//フィールドに存在する黒色ブロックの色を決定する
void Phase_GameMain::Block_Black_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BLACK) {//黒ブロックの時
				//確率でブロックのIDを書き換える
				int Val = (int)randomTable.getRand(0, 100);
				if (Val < 20)		field[x][y].addBlcok(BLOCK_TYPE_RED, TRUE);		//赤色ブロック
				else if (Val < 40)	field[x][y].addBlcok(BLOCK_TYPE_BLUE, TRUE);	//青色ブロック
				else if (Val < 60)	field[x][y].addBlcok(BLOCK_TYPE_YELLOW, TRUE);	//黄色ブロック
				else if (Val < 80)	field[x][y].addBlcok(BLOCK_TYPE_GREEN, TRUE);	//緑色ブロック
				else 				field[x][y].addBlcok(BLOCK_TYPE_PURPLE, TRUE);	//紫色ブロック

				//変化モーションの設定
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_BLACK, 20, 0);
			}
		}
	}
}

//フィールドに存在する虹色ブロックの色を決定する(下から順に)
void Phase_GameMain::Block_Rainbow_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_RAINBOW) {//虹色ブロックの時
				if (getBlockColor(x, y + 1) == BLOCK_TYPE_NO) {
					//下にブロックが無い
					//確率でブロックのIDを書き換える
					int Val = (int)randomTable.getRand(0, 100);
					if (Val < 20)		field[x][y].addBlcok(BLOCK_TYPE_RED, TRUE);		//赤色ブロック
					else if (Val < 40)	field[x][y].addBlcok(BLOCK_TYPE_BLUE, TRUE);	//青色ブロック
					else if (Val < 60)	field[x][y].addBlcok(BLOCK_TYPE_YELLOW, TRUE);	//黄色ブロック
					else if (Val < 80)	field[x][y].addBlcok(BLOCK_TYPE_GREEN, TRUE);	//緑色ブロック
					else 				field[x][y].addBlcok(BLOCK_TYPE_PURPLE, TRUE);	//紫色ブロック
				}
				else {
					//下にブロックがある場合
					field[x][y].addBlcok(getBlockColor(x, y + 1), TRUE);
				}

				//変化モーションの設定
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_RAINBOW, 20, 0);
			}
		}
	}
}

//フィールドに存在する爆弾ブロックを爆破する
void Phase_GameMain::Block_BOMB_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BOM) {//爆弾ブロックの時
				//自身の削除
				if (Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;

				//周囲のブロックを削除する(爆弾ブロックは削除しない)
				if (getBlockColor(x + 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 2, y, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 2, y, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}
				if (getBlockColor(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 1, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 2, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}
				if (getBlockColor(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 1, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 2, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}


				if (getBlockColor(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y - 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y - 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y + 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y + 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//フィールドに存在する2爆弾ブロックを爆破する
void Phase_GameMain::Block_2BOMB_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_2BOM) {//爆弾ブロックの時
				//自身の削除
				if (Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;

				//2個隣接しているブロックを破壊する
				DeleteNum += Block_Delete(2, FALSE);
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//フィールドに存在する同色爆弾ブロックを爆破する
void Phase_GameMain::Block_BOMBColor_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BOM_Color) {//爆弾ブロックの時
				//自身の削除
				if (Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				//真下のブロックの色を取得する
				BLOCK_TYPE under = getBlockColor(x, y + 1);

				//同色ブロックを削除する
				for (int x2 = BLOCK_PADDINGLEFT; x2 < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x2++) {
					for (int y2 = BLOCK_PADDINGUP; y2 < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y2++) {
						Block_Delete_Color(x2, y2, under, BlockChangeMotionType_EXPLOSION, 40);
					}
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}


//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
BLOCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock, int InGame, int UseVirtualField) {

	//画面外処理
	if (InGame) {
		//実際の描画エリアで判定
		if (X < BLOCK_PADDINGLEFT || (BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT) <= X)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
		if (Y < BLOCK_PADDINGUP || (BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN) <= Y)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
	}
	else {
		//フィールド情報から判定する
		if (X < 0 || BLOCK_WIDTHNUM <= X)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
		if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
	}

	return ((UseVirtualField) ? Virtualfield[X][Y].getBlockType() : field[X][Y].getBlockType());
}

//フィールドブロックを重力で落下させる
void Phase_GameMain::Block_Gravity(int InGameOnly) {
	int sX = 0, sY = 0;
	int eX = BLOCK_WIDTHNUM, eY = BLOCK_HEIGHTNUM;

	if (InGameOnly) {
		sX = BLOCK_PADDINGLEFT;
		sY = BLOCK_PADDINGUP;

		eX = BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT;
		eY = BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;
	}

	for (int x = sX; x < eX; x++) {
		//列ごとにブロック情報をコピーする
		Block_Field t[BLOCK_HEIGHTNUM];
		for (int y = sY; y < eY; y++) {
			t[y] = field[x][y];
			field[x][y].Delete_Block();
		}
		int Count = eY - 1;
		//下の段から存在するブロックを並べ直す(逆順回し)
		for (int y = eY - 1; y >= sY; y--) {
			if (t[y].getBlockType() != BLOCK_TYPE_NO) {
				field[x][Count] = t[y];
				//落下モーション(カウントが移動先、yが移動元になる)
				Block_SetMoveMotion(x, Count, x, y, x, Count, 0.3, 15);
				Count--;
			}
		}
	}

	printLog_I(_T("ブロックに重力計算を行いました"));
}

//フィールドブロックを直接削除する(削除されたらTRUE)
int Phase_GameMain::Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int MotionLengh, int Delay) {
	//現在のブロックの種類の取得(削除前)
	BLOCK_TYPE bt = getBlockColor(X, Y, FALSE, FALSE);	//削除されるブロックの種類
	if (bt == BLOCK_TYPE_NO)	return FALSE;//ブロックがそもそも存在しない場合は何もしない
	//ブロックの削除を行う
	

	int flag = field[X][Y].Delete_Block();

	if (flag) {
		//ブロックが削除された
		if (PlayMotion == BlockChangeMotionType_EXPLOSION) {
			Block_SetChangeMotion_EXPLOSION(X, Y, MotionLengh, bt, Delay);	//モーションの生成
		}
		else if (PlayMotion == BlockChangeMotionType_SMALL) {
			Block_SetChangeMotion_SMALL(X, Y, MotionLengh, bt, Delay);	//モーションの生成
		}
	}

	return ((flag) ? TRUE : FALSE);
}

//指定した座標が指定したブロックだった場合に削除(削除されたらTRUE)
int Phase_GameMain::Block_Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion, int MotionLengh) {
	if (!Block::isSameColorBlock(type, getBlockColor(X, Y), FALSE))	return FALSE;//違う色のブロックの場合は削除しない

	return Block_Delete_Direct(X, Y, PlayMotion, MotionLengh);
}

//連続するフィールドブロックを削除する(ついでに消去によって発動する効果も発動する)(消去したブロックの数)
int Phase_GameMain::Block_Delete(const int Len, int Flag_Event) {
	//画面内の存在するブロックのみで計算する


	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	CreateSequenceCountTable(DeleteFlag, BLOCK_PADDINGLEFT, BLOCK_PADDINGUP, BLOCK_WIDTHNUM_INGAME, BLOCK_HEIGHTNUM_INGAME);

	//削除前のブロックの一覧を作成する
	BLOCK_TYPE old[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			old[x][y] = getBlockColor(x, y);
		}
	}

	//隣接ブロックの計算を行う
	int Counter[BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM];	//IDごとの隣接カウント数
	int ID = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (DeleteFlag[x][y] == -1) {//未探索ブロック
				Counter[ID] = 0;
				SequenceCount(x, y, ID, DeleteFlag, &(Counter[ID]));
				ID++;
			}
		}
	}

	//矢印ブロックの効果を先に発動する
	int DelCount = 0;
	if (Flag_Event) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
					if (Counter[DeleteFlag[x][y]] >= Len) {
						//水平の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_X ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_X ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_X ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_X ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_X) {
							//左端から右端までの一列を一括消去
							for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
								if (Block_Delete_Direct(i, y, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Block_Field::Convert_Ingame_FromBlock(i, y, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
						//垂直の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_Y) {
							//左端から右端までの一列を一括消去
							for (int i = 0; i < BLOCK_HEIGHTNUM; i++) {
								if (Block_Delete_Direct(x, i, BlockChangeMotionType_EXPLOSION, 40, abs(y - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Block_Field::Convert_Ingame_FromBlock(x, i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
						//右上の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_XY) {
							//斜めに一括消去
							for (int i = 0; i < max(BLOCK_HEIGHTNUM, BLOCK_WIDTHNUM); i++) {
								if (Block_Delete_Direct(x + i, y - i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Block_Field::Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("50"));
									score.addScore(0, 50);
									DelCount++;
								}
								if (Block_Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Block_Field::Convert_Ingame_FromBlock(x - i, y + i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
						//右下の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_XY2) {
							//斜めに一括消去
							for (int i = 0; i < max(BLOCK_HEIGHTNUM, BLOCK_WIDTHNUM); i++) {
								if (Block_Delete_Direct(x + i, y + i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Block_Field::Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("50"));
									score.addScore(0, 50);
									DelCount++;
								}
								if (Block_Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Block_Field::Convert_Ingame_FromBlock(x - i, y - i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
					}
				}
			}
		}
		//この時点で削除があった(つまり矢印ブロックで消された)
		if (DelCount > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
	}


	BlockChangeMotionType DelMotion = BlockChangeMotionType_SMALL;
	int DelLen = 15;
	if (!Flag_Event) {
		DelMotion = BlockChangeMotionType_EXPLOSION;
		DelLen = 40;
	}
	//隣接しているブロックを削除する
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
				if (Counter[DeleteFlag[x][y]] >= Len) {
					//削除
					if (Block_Delete_Direct(x, y, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Block_Field::Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("100"));
						score.addScore(0, 100);
						DelCount++;
					}

					//ついでに隣接する樹木ブロックも削除
					if (Block_Delete_Color(x, y - 1, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Block_Field::Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("80"));
						score.addScore(0, 80);
						DelCount++;//上
					}
					if (Block_Delete_Color(x, y + 1, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Block_Field::Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("80"));
						score.addScore(0, 80);
						DelCount++;//下
					}
					if (Block_Delete_Color(x - 1, y, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Block_Field::Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("80"));
						score.addScore(0, 80);
						DelCount++;//左
					}
					if (Block_Delete_Color(x + 1, y, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Block_Field::Convert_Ingame_FromBlock(x + 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), _T("80"));
						score.addScore(0, 80);
						DelCount++;//右
					}



				}
			}
		}
	}

	printLog_I(_T("隣接ブロックの削除計算を行いました(%dブロック)"), DelCount);


	return DelCount;
}

//SequenceCountで使用するマーカーテーブルを作成する(有効なエリア)(UseVirtualField=TRUEで仮想の面を使用する)
void Phase_GameMain::CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField) {
	if (deleteFlag == NULL)	return;

	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			const BLOCK_TYPE type = getBlockColor(x, y, FALSE, FALSE, UseVirtualField);	//ブロックの種類を取得する
			if (!(X <= x && x < X + W && Y <= y && y < Y + H) ||	//範囲外
				type == BLOCK_TYPE_NO ||
				type == BLOCK_TYPE_NUM ||
				type == BLOCK_TYPE_TREE ||
				type == BLOCK_TYPE_BLACK ||
				type == BLOCK_TYPE_RAINBOW ||
				type == BLOCK_TYPE_BOM ||
				type == BLOCK_TYPE_2BOM ||
				type == BLOCK_TYPE_BOM_Color) {		//除外ブロック
				deleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				deleteFlag[x][y] = -1;
			}
		}
	}
}

//画面外のブロックをすべて削除する(消去したブロックの数)
int Phase_GameMain::Block_Delete_OutScreen() {
	int count = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (getBlockColor(x, y, TRUE, TRUE) == BLOCK_TYPE_NUM) {
				//画面外ブロックの場合は削除
				if (Block_Delete_Direct(x, y)) {
					count++;
				}
			}
		}
	}

	printLog_I(_T("画面外のブロックをすべて削除(%d個)"), count);


	return count;
}

//隣接する同色ブロックにマーカーを付ける
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter, int UseVirtualField) {
	if (deleteFlag == NULL)		return;		//マーカーを付けるテーブルがない場合
	if (deleteFlag[x][y] != -1)	return;		//未探索ブロックじゃない場合
	BLOCK_TYPE bt = ((UseVirtualField) ? Virtualfield[x][y].getBlockType() : field[x][y].getBlockType());	//ブロックの種類を記録する
	deleteFlag[x][y] = ID;	//探索済み(探索IDを設定する)
	(*Counter)++;

	int OnlyColor = TRUE;

	BLOCK_TYPE NextBlock = ((UseVirtualField) ? Virtualfield[x + 1][y].getBlockType() : field[x + 1][y].getBlockType());
	if (x + 1 < BLOCK_WIDTHNUM	&& Block::isSameColorBlock(NextBlock, bt, OnlyColor))		SequenceCount(x + 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y + 1].getBlockType() : field[x][y + 1].getBlockType());
	if (y + 1 < BLOCK_HEIGHTNUM	&& Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x - 1][y].getBlockType() : field[x - 1][y].getBlockType());
	if (x - 1 >= 0 && Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y - 1].getBlockType() : field[x][y - 1].getBlockType());
	if (y - 1 >= 0 && Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//フィールドのブロック移動にモーションを設定する
void Phase_GameMain::Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockColor(x, y, FALSE, FALSE) == BLOCK_TYPE_NO)	return;	//ブロックが無効の場合は処理をしない
	
	int ans = field[x][y].getMoveMotion()->Create(FromX, FromY, ToX, ToY, a, MaxSpeed);

	if(ans)	printLog_I(_T("ブロックに【移動モーション】を設定(%d,%d)"), x, y);
}

//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Phase_GameMain::isBlock_PlayMoveMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getMoveMotion()->isEnable()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//フィールドのブロックに変化モーションを設定する(これ単体で使用して事故っても知りません)
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//ブロックが画面外の場合は処理をしない

	int ans = field[x][y].getChangeMotion()->Create(mtype, From, To, MotionLength, Delay);

	if(ans)	printLog_I(_T("ブロックに【変化モーション】を設定[%d][%d]"), x, y);
}

//フィールドのブロックに変化モーション(通常)を設定する
void Phase_GameMain::Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength, int Delay) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == To)				return;		//変化先が同じ場合は処理をしない
	if (To == BLOCK_TYPE_NO)	return;		//変化先がブロック無しの場合は処理をしない(正しく描画出来ないため)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, From, To, MotionLength, Delay);
}

//フィールドのブロックに変化モーション(通常)を設定する(変化元指定)
void Phase_GameMain::Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength, int Delay) {

	BLOCK_TYPE To = getBlockColor(x, y, FALSE, FALSE);
	if (from == To)				return;		//変化先が同じ場合は処理をしない
	if (To == BLOCK_TYPE_NO)	return;		//変化先がブロック無しの場合は処理をしない(正しく描画出来ないため)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, from, To, MotionLength, Delay);
}


//フィールドのブロックに変化モーション(爆発)を設定する
void Phase_GameMain::Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//ブロックが存在しない場合は無視

	Block_SetChangeMotion(x, y, BlockChangeMotionType_EXPLOSION, From, From, MotionLength, Delay);
}

//フィールドのブロックに変化モーション(小さくなって消える)を設定する
void Phase_GameMain::Block_SetChangeMotion_SMALL(int x, int y, int MotionLength, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//ブロックが存在しない場合は無視

	Block_SetChangeMotion(x, y, BlockChangeMotionType_SMALL, From, From, MotionLength, Delay);
}

//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Phase_GameMain::isBlock_PlayChangeMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getChangeMotion()->isEnable()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//ゲームサイクルを設定する
void Phase_GameMain::setGameCycle(GameCycle gamecycle) {
	if (gamecycle == GameCycle_NUM) {
		printLog_E(_T("無効なゲームサイクルが指定されました"));
		return;
	}

	GameCycle old = gameCycle;
	gameCycle = gamecycle;

	printLog_I(_T("ゲームサイクルの変更(%d→%d)"), old, gameCycle);
	gameCycleFirstCallFlag = TRUE;
}

//ブロック情報を更新するようにリクエスト
void Phase_GameMain::UpdateBlockRequest(GameCycle Next) {
	if (Next == GameCycle_NUM) {
		printLog_E(_T("引数が不正です"));
		return;
	}


	if (gameCycle != GameCycle_Update) {	//ブロック更新サイクルを実行中でない場合は、
		//計算ループの処理位置を設定
		Loop_No = 0;
	}

	//ブロック計算サイクルへ移行(ループの再設定)
	setGameCycle(GameCycle_Update);

	//移行先のゲームサイクルを記録する(ブロック更新が指定された場合は移行先を設定しない)
	if (Next != GameCycle_Update) {
		Loop_Next = Next;
	}



	printLog_I(_T("ブロック計算ループに入ります(終了後=%d)"), Loop_Next);

}

//フィールド全体のブロックを指定した分だけ移動するリクエストをする(ゲームを一時停止して動かします)
void Phase_GameMain::Block_AllMoveRequest(int X, int Y) {

	Block_AllMovedata.Create(0, 0, X, Y, 0.1, 2);

	if (Block_AllMovedata.isEnable())	return;//すでにブロックが移動中の場合、無視する

	printLog_I(_T("ブロック全体移動が設定されました(%d,%d)"), X, Y);
}

//フィールド全体のブロックを指定した分だけ移動する(画面外に出てしまうブロックは消滅します)
void Phase_GameMain::Block_AllMove(int X, int Y) {
	//処理に無駄が多い…

	//一時変数
	//Block_Field t[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//実際にブロックをすべて移動させる

	//左上移動
	if (X <= 0 && Y <= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を左上にずらしました(%d,%d)"), X, Y);
	}
	//左下移動
	else if (X <= 0 && Y >= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を左下にずらしました(%d,%d)"), X, Y);
	}
	//右上移動
	else if (X >= 0 && Y <= 0) {
		for (int x = BLOCK_WIDTHNUM - 1; x >= 0; x--) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を右上にずらしました(%d,%d)"), X, Y);
	}
	//右下移動
	else if (X >= 0 && Y >= 0) {
		for (int x = BLOCK_WIDTHNUM - 1; x >= 0; x--) {
			for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を右下にずらしました(%d,%d)"), X, Y);
	}

	//落下中ブロックも移動する(画面外には行きません)
	fallBlockInfo.FallBlock_MoveX(X, FALSE);
	fallBlockInfo.FallBlock_MoveY(Y, FALSE);

}

//実際に操作をしている経過フレーム数を取得する
int Phase_GameMain::getCountPlayTime() {
	return Count_PlayTime;
}

//ゲームの経過フレーム数を取得(クリアで停止します)
int Phase_GameMain::getCountGameTime() {
	return Count_GameTime;
}

//ゲームの経過フレーム数を取得(ポーズでのみ停止する)
int Phase_GameMain::getCountTime() {
	return Count_Time;
}

//指定したエリアにブロックを設置する(消去判定が入らないように設置します)
void Phase_GameMain::setBlock_Rect(int x, int y, int w, int h) {
	//仮想フィールド情報を更新する
	Virtualfield_Update();

	for (int bl_X = x; bl_X < x + w; bl_X++) {
		for (int bl_Y = y; bl_Y < y + h; bl_Y++) {
			BLOCK_TYPE bt;
			int Count = 0;

			do {
				Count = 0;
				bt = GetRandomBlockType_UNDER();//ランダムでブロックを決定し仮想設置する
				add_FraldBlock2(bl_X, bl_Y, bt, TRUE, TRUE, NULL, TRUE);
				int BlockFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
				//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
				CreateSequenceCountTable(BlockFlag, 0, 0, BLOCK_WIDTHNUM, BLOCK_HEIGHTNUM, TRUE);
				SequenceCount(bl_X, bl_Y, 0, BlockFlag, &Count, TRUE);
			} while (Count >= BLOCK_DELETE_LEN);

			add_FraldBlock2(bl_X, bl_Y, bt, FALSE, TRUE);//本番の設置
		}
	}
}

//ゲームオーバーになっているかどうかの確認
/*
戻り値
0:ゲームオーバーでは無い
1:ブロックが上まで積み上がっていまってゲームオーバー
2:落下ブロックが既存ブロックと重なってしまってゲームオーバー
*/
int Phase_GameMain::JudgeGameOver() {
	printLog_I(_T("ゲームオーバーかどうかの判定を行います"));
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < GAMEOVER_BORDER; y++) {
			if (getBlockColor(x, y, FALSE, FALSE) != BLOCK_TYPE_NO) {
				//0列目(画面上の見えない部分)にブロックが侵入した
				printLog_I(_T("ブロックが上まで積み上がっていまってゲームオーバー"));
				return 1;
			}
		}
	}

	return 0;
}

//ゲームクリアかどうかの確認(TRUEゲームクリア)
int Phase_GameMain::JudgeGameClear() {
	if (score.getScore() > 10'0000) {
		//スコアが一定以上でクリア判定を入れる
		return TRUE;
	}
	return FALSE;
}


//ランダムでブロックの種類を返す(落下ブロック用)
BLOCK_TYPE Phase_GameMain::GetRandomBlockType_FALL() {
	int Rand = (int)phase_GameMain.getRandomTable()->getRand(0, 100);

	//確率で戻り値を変えるようにする
	if (Rand < 17)	return BLOCK_TYPE_RED;		//赤
	if (Rand < 35)	return BLOCK_TYPE_BLUE;		//青
	if (Rand < 52)	return BLOCK_TYPE_YELLOW;	//黄
	if (Rand < 70)	return BLOCK_TYPE_GREEN;	//緑
	if (Rand < 88)	return BLOCK_TYPE_PURPLE;	//紫

												/*ここから特殊ブロック↓*/
	if (Rand < 89)	return BLOCK_TYPE_RED_ARROW_X;		//赤(平行矢印)
	if (Rand < 91)	return BLOCK_TYPE_BLUE_ARROW_X;		//青(平行矢印)
	if (Rand < 93)	return BLOCK_TYPE_YELLOW_ARROW_X;	//黄(平行矢印)
	if (Rand < 95)	return BLOCK_TYPE_GREEN_ARROW_X;	//緑(平行矢印)
	if (Rand < 97)	return BLOCK_TYPE_PURPLE_ARROW_X;	//紫(平行矢印)
	return BLOCK_TYPE_RAINBOW;							//虹色のブロック(下のブロックと同じ色になる)
}

//ランダムでブロックの種類を返す(下から沸いてくるブロック用)
BLOCK_TYPE Phase_GameMain::GetRandomBlockType_UNDER() {
	int Rand = (int)randomTable.getRand(0, 200);

	//確率で戻り値を変えるようにする
	if (Rand < 37)	return BLOCK_TYPE_RED;		//赤
	if (Rand < 75)	return BLOCK_TYPE_BLUE;		//青
	if (Rand < 112)	return BLOCK_TYPE_YELLOW;	//黄
	if (Rand < 150)	return BLOCK_TYPE_GREEN;	//緑
	if (Rand < 188)	return BLOCK_TYPE_PURPLE;	//紫

	//ここから特殊ブロック↓
	if (Rand < 189)	return BLOCK_TYPE_RED_ARROW_X;		//赤(平行矢印)
	if (Rand < 191)	return BLOCK_TYPE_BLUE_ARROW_X;		//青(平行矢印)
	if (Rand < 193)	return BLOCK_TYPE_YELLOW_ARROW_X;	//黄(平行矢印)
	if (Rand < 195)	return BLOCK_TYPE_GREEN_ARROW_X;	//緑(平行矢印)
	if (Rand < 197)	return BLOCK_TYPE_PURPLE_ARROW_X;	//紫(平行矢印)
	return BLOCK_TYPE_TREE;								//樹木の形のブロック（隣接する４方向のどこかが消えたときに一緒に消える）
}

//仮想フィールドを現在のフィールドと一致させる
void Phase_GameMain::Virtualfield_Update() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			Virtualfield[x][y] = field[x][y];
		}
	}
	printLog_I(_T("仮想フィールドを更新しました"));


}

//ポーズメニューのボタンが押されたとき
void Phase_GameMain::SelectItem_pause::Event_Select(int No) {
	switch (No) {
	case 0://再開ボタン
		phase_GameMain.Request_Pause(PauseMode_NO);
		break;
	case 1://やり直すボタン
		phase_GameMain.Restart();
		break;
	case 2://終了ボタン
		Changefaze(FAZE_TopMenu, THREAD_Update);
		break;
	default:
		printLog_C(_T("定義されていない選択項目が選択されたようです(%d)"), No);
		break;
	}
}

//指定したX座標の一番上のブロックのY座標を取得する(見えている座標のみで判断)
int Phase_GameMain::getBlock_Upper(int x) {
	for (int y = BLOCK_PADDINGUP; y < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y++) {
		if (getBlockColor(x, y) != BLOCK_TYPE_NO)	return y;
	}
	return BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;//最下段の一段下の座標を返す
}

//最大の高さのブロックのY座標を取得する
int Phase_GameMain::getBlock_maxUpper() {
	int Max_Y = BLOCK_HEIGHTNUM;
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		Max_Y = min(Max_Y, getBlock_Upper(x));
	}
	return Max_Y;
}

//テクスチャの情報の取得
Tex_Block *Phase_GameMain::getTex_Block() {
	return &tex_Block;
}

//乱数表の取得
RandomTable *Phase_GameMain::getRandomTable() {
	return &randomTable;
}

//全体移動によるXY方向のズレを取得する
void Phase_GameMain::getAllPadding(double *paddingX, double *paddingY) {
	if (Block_AllMovedata.isEnable()) {
		if (paddingX != NULL)	*paddingX = Block_AllMovedata.getPointX();
		if (paddingY != NULL)	*paddingY = Block_AllMovedata.getPointY();
	}
	else {
		if (paddingX != NULL)	*paddingX = 0;
		if (paddingY != NULL)	*paddingY = 0;
	}
}