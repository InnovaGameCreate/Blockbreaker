#include "MainFunc.h"


Phase_GameMain::Phase_GameMain() {
	//ポーズメニューの項目を作成
	pauseMenu.addItem(_T("再開"), 3, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("やり直す"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("トップメニューへ"), 8, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.setScrolltype(1);
	pauseMenu.sethaba(50);
	pauseMenu.setCenteringMode(0);

	//ゲームオーバーの項目を作成
	gameOverMenu.addItem(_T("やり直す"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	gameOverMenu.addItem(_T("トップメニューへ"), 8, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	gameOverMenu.setScrolltype(1);
	gameOverMenu.sethaba(50);
	gameOverMenu.setCenteringMode(0);

	//ゲームクリアの項目を作成
	gameClearMenu.addItem(_T("ランキングへ"), 6, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	gameClearMenu.addItem(_T("もう一度"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	gameClearMenu.addItem(_T("トップメニューへ"), 8, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	gameClearMenu.setScrolltype(1);
	gameClearMenu.sethaba(50);
	gameClearMenu.setCenteringMode(0);
}


Phase_GameMain::~Phase_GameMain() {
}

//初期化(描画処理)
void Phase_GameMain::Init_Draw() {
	using SK::Math::Pot;

	//ゲーム画面の生成(後でシェーダを使いたいので2のn乗のサイズで作成します)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("ウィンドウ作成に失敗しました"));

	tex_Block.Init_Draw();	//ブロック画像のロード

	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/colorbom.png)"));
	if ((Tex_FieldBack = LoadGraph(_T("Data/image/BlockField_Back.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/BlockField_Back.png)"));


	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);

	Field.Init_Draw();	//フィールド情報の初期化

	//BGM再生
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

	//各メニューの選択を有効にする
	pauseMenu.setControlEnable(TRUE);
	gameOverMenu.setControlEnable(TRUE);
	gameClearMenu.setControlEnable(TRUE);
}

//フルスクリーンに復帰時に呼ばれる
void Phase_GameMain::RestoreGraphCallback() {

}

//初期化(計算処理)
void Phase_GameMain::Init_Update() {
	Field.Init_Update();	//フィールド情報の初期化

	ranking.File();

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
	//落下中ブロックの初期化
	fallBlockInfo.Restart();
	score.init();//スコアの初期化
	flyText.AllDelete();	//フライテキストの全消去
	Field.Restart();	//フィールドのリスタート

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

	Field.Draw_Block();	//フィールドブロックの描画



	//フライテキストを描画する
	flyText.Draw();


	//デバッグ
	if (isDebugMode()) {
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
	}

	//クリア状態の時にゲーム画面を加工する
	if (getPauseMode() == PauseMode_GameClear) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 80);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(100, 100, 100), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		GraphFilter(gameWindow, DX_GRAPH_FILTER_GAUSS, 32, 500);
	}


	//描画先をバックスクリーンにする
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲーム画面の背景画像を描画
	DrawGraph(0, 0, haikei, FALSE);

	fallBlockInfo.Draw_WaitLine();	//次の落下ブロックの描画

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
	}
	break;
	case PauseMode_GameClear://ゲームクリア時
		Draw_ClearScreen();

		break;
	}

	//メニューの選択肢を描画する
	pauseMenu.Draw();
	gameOverMenu.Draw();
	gameClearMenu.Draw();
}

//クリア画面の追加描画
void Phase_GameMain::Draw_ClearScreen() {
	TCHAR tmp[100];
	Font_DrawStringCenterWithShadow(GAMEWINDOW_PADDINGX + GAMEWINDOW_WIDTH / 2, 300, _T("そこまで！"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);

	Font_DrawStringCenterWithShadow(GAMEWINDOW_PADDINGX + GAMEWINDOW_WIDTH / 2, 380, _T("あなたの順位は"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge30);

	int Rank = 1;

	_stprintf_s(tmp, _T("%d位"), Rank);
	Font_DrawStringCenterWithShadow(GAMEWINDOW_PADDINGX + GAMEWINDOW_WIDTH / 2, 410, tmp, GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge40);


	if (isKeyImputEnable()) {
		//キー入力が有効な場合はキー入力の途中経過を描画する
		Font_DrawStringCenterWithShadow(GAMEWINDOW_PADDINGX + GAMEWINDOW_WIDTH / 2, 450, getKeyImputStr(), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge40);
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
	//キーボードが有効な場合はここから先には進めない

	if (isKeyImputEnable())	return;

	//各メニュー項目の処理
	pauseMenu.Update();
	gameOverMenu.Update();
	gameClearMenu.Update();

	//フライテキストの更新(通常ゲームプレイ時とゲームクリア時)
	if(getPauseMode() == PauseMode_NO || getPauseMode() == PauseMode_GameClear) flyText.Update();

	//ポーズ時の処理をしてこの先には進まない
	if (getPauseMode() != PauseMode_NO) return;
	



	//全体移動の更新を行い、終わった瞬間なら現在のゲームサイクルに割り込む形でゲームサイクルの更新を行う
	if (Field.Update_AllMove())		UpdateBlockRequest(gameCycle);

	if (Field.getBlockMoveMotion()->isEnable())	return;//全体移動が有効な場合はここから先は処理をしない


	switch (gameCycle) {
	case GameCycle_FALL:
		if (fallBlockInfo.getInterval() > 0) {
			//前回の落下ブロック終了から一定時間後
			Count_Turn++;	//経過ターンを加算する
			fallBlockInfo.Create();	//落下ブロックの再出現
		}
		//落下ブロックの落下処理
		if (fallBlockInfo.Update()) {
			//落下完了後は計算を行う
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
	{
		if (Count_Turn % 4 == 0 || Field.getmaxUpperX() > BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL) {
			//下からブロックを沸かす
			Field.add_Under();
		}
		else if (Count_Turn % 7 == 0) {
			//お邪魔ブロック設置
			int ran[5];
			randomTable.getRand_num(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT, ran, ARRAY_LENGTH(ran));
			for (int i = 0; i < ARRAY_LENGTH(ran); i++) {
				Field.add_FieldBlock(ran[i], BLOCK_PADDINGUP, BLOCK_TYPE_TREE);
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
		Field.ChainCount_Reset();//連鎖カウントをリセットする
		gameCycleFirstCallFlag = FALSE;	//ゲームサイクルが変更された時のフラグをFALSEに設定する

		//画面外ブロックを削除する
		Field.Delete_OutScreen();

		if (!gameCycleFirstCallFlag) {
			Loop_No = 1;
			printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 1://変化モーション
		if (Field.Update_ChangeMotion() == FALSE) {
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
		Field.Gravity();//重力計算を行う
		Loop_No = 3;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 3://移動モーション
		if (Field.Update_MoveMotion() == FALSE) {
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
		Field.Func_Black();		//黒ブロックの色変更
		Field.Func_Rainbow();	//虹色ブロックの色を変更
		Field.Func_BOMB();		//爆弾ブロックの処理
		Field.Func_2BOMB();		//2爆弾ブロックの処理
		Field.Func_BOMBColor();	//同色爆弾ブロックの処理
		Loop_No = 5;
		printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 5://変化モーション
		if (Field.Update_ChangeMotion() == FALSE) {
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
		Field.Gravity();//重力計算を行う
		Loop_No = 7;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 7://移動モーション
		if (Field.Update_MoveMotion() == FALSE) {
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

		if (Field.Delete_Join() > 0) {
			//連鎖カウントを描画する(フライテキスト)
			if (Field.getChain() >= 2) flyText.addFlyText(GAMEWINDOW_WIDTH / 2., GAMEWINDOW_HEIGHT / 2., 60, FONTTYPE_GenJyuuGothicLHeavy_Edge60, GetColor(200, 200, 0), _T("%d連鎖！！"), Field.getChain());


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
		if (Field.Update_ChangeMotion() == FALSE) {
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
		Field.Gravity();//重力計算を行う
		Loop_No = 11;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 11://移動モーション
		if (Field.Update_MoveMotion() == FALSE) {
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
			Clear();
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



//カウンタのカウントアップ
void Phase_GameMain::Update_Counter() {

	//実際に操作をしている経過フレーム数の加算
	if (getPauseMode() == PauseMode_NO
		&& Field.getBlockMoveMotion()->isEnable() == FALSE
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

	Field.Update_DrawData();

	//フィールド全体のズレを計算
	double Field_PaddingX, Field_PaddingY;
	Field.getField_Padding(&Field_PaddingX, &Field_PaddingY);

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
			pauseMenu.setEnable(FALSE);		//ポーズ状態メニューの無効化
		}
		else if (getPauseMode() == PauseMode_NO) {
			//ポーズに
			pauseMenu.setSelecedtItem(0);
			SoundEffect_Play(SE_TYPE_Pause);
			Request_Pause(PauseMode_NOMAL);	//ポーズ状態
			pauseMenu.setEnable(TRUE);		//ポーズ状態メニューの有効化
		}
	}

	if (getPauseMode() != PauseMode_NO)	return;//ポーズ処理が入った場合はこの先は処理をしない

	if (Field.getBlockMoveMotion()->isEnable())	return;//全体移動が入っている場合はこの先の処理をしない

	Field.key();			//フィールドのキー処理

	fallBlockInfo.Key();	//落下ブロックのキー処理
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
		break;
	case PauseMode_GameOver:
		printLog_I(_T("【ゲームオーバーポーズ】リクエスト"));
		gameOverMenu.setEnable(TRUE);
		break;
	case PauseMode_GameClear:
		printLog_I(_T("【ゲームクリアポーズ】リクエスト"));
		break;
	}
	Flag_pauseRequest = pauseMode;
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
			if (Field.getBlockType(x, y, FALSE, FALSE) != BLOCK_TYPE_NO) {
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
	if (score.getScore() > 10'00) {
		//スコアが一定以上でクリア判定を入れる
		return TRUE;
	}
	return FALSE;
}


//ランダムでブロックの種類を返す(落下ブロック用)
BLOCK_TYPE Phase_GameMain::GetRandomBlockType_FALL() {
	int Rand = (int)randomTable.getRand(0, 100);

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

//ポーズメニューのボタンが押されたとき
void Phase_GameMain::SelectItem_Pause::Event_Select(int No) {
	switch (No) {
	case 0://再開ボタン
		phase_GameMain.Request_Pause(PauseMode_NO);
		setEnable(FALSE);		//ポーズ状態メニューの無効化
		break;
	case 1://やり直すボタン
		phase_GameMain.Restart();
		setEnable(FALSE);		//ポーズ状態メニューの無効化
		break;
	case 2://終了ボタン
		phaseController.ChangefazeRequest(FAZE_TopMenu, 0);
		setEnable(FALSE);		//ポーズ状態メニューの無効化
		break;
	default:
		printLog_C(_T("定義されていない選択項目が選択されたようです(%d)"), No);
		break;
	}
}

//ゲームオーバーのボタンが押されたとき
void Phase_GameMain::SelectItem_GameOver::Event_Select(int No) {
	switch (No) {
	case 0://やり直すボタン
		phase_GameMain.Restart();
		setEnable(FALSE);		//メニューの無効化
		break;
	case 1://終了ボタン
		phaseController.ChangefazeRequest(FAZE_TopMenu, 0);
		setEnable(FALSE);		//メニューの無効化
		break;
	default:
		printLog_C(_T("定義されていない選択項目が選択されたようです(%d)"), No);
		break;
	}
}

//ゲームクリアのボタンが押されたとき
void Phase_GameMain::SelectItem_GameClear::Event_Select(int No) {
	switch (No) {
	case 0:
		//ここにランキング画面への処理記述
		break;
	case 1://やり直すボタン
		phase_GameMain.Restart();
		setEnable(FALSE);		//メニューの無効化
		break;
	case 2://終了ボタン
		phaseController.ChangefazeRequest(FAZE_TopMenu, 0);
		setEnable(FALSE);		//メニューの無効化
		break;
	default:
		printLog_C(_T("定義されていない選択項目が選択されたようです(%d)"), No);
		break;
	}
}

//テクスチャの情報の取得
Tex_Block *Phase_GameMain::getTex_Block() {
	return &tex_Block;
}

//乱数表の取得
SK::RandomTable *Phase_GameMain::getRandomTable() {
	return &randomTable;
}

//落下ブロッククラスのポインタ取得
Block_Fall *Phase_GameMain::getfallBlockInfo() {
	return &fallBlockInfo;
}

//デバッグが有効かどうかの取得
int Phase_GameMain::isDebugMode() {
#ifdef _DEBUG_GAMEMAIN_
	return TRUE;
#endif
	return FALSE;
}

//スコアクラスのインスタンスの取得
Phase_GameMain::Score *Phase_GameMain::getScore() {
	return &score;
}

//フライテキストのインスタンスの取得
FlyText *Phase_GameMain::getFlyText() {
	return &flyText;
}

//フィールドブロックのインスタンスの取得
Field_Admin *Phase_GameMain::getField() {
	return &Field;
}

//クリアしたときに一度だけ実行される
void Phase_GameMain::Clear() {
	//順位を確認する
	int No = 1;	//仮に一位だとする

	//ランクインしている場合はキーボードを表示する
	if (No < 40) {
		setKeyImputStart(GAMEWINDOW_PADDINGX + GAMEWINDOW_WIDTH / 2, 540, &keyImputEnd);
	}
	else {
		//ランク外の時は選択メニューの表示を行う
		gameClearMenu.setEnable(TRUE);	//クリアメニューを有効にする
	}
}

//キー入力が終了した時に呼ばれる
void Phase_GameMain::KeyImputEnd::operator()(TCHAR *str) {
	P->setEnable(TRUE);
}