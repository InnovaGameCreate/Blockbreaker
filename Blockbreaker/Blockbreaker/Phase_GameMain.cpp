#include "Phase_GameMain.h"
#include "MainFunc.h"

Phase_GameMain::Phase_GameMain() {
}


Phase_GameMain::~Phase_GameMain() {
}

//初期化(描画処理)
void Phase_GameMain::Init_Draw() {
	//ゲーム画面の生成(後でシェーダを使いたいので2のn乗のサイズで作成します)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("ウィンドウ作成に失敗しました"));

	if ((Tex_BlockRED = LoadGraph(_T("Data/Blocks/Block_RED.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED.png)"));
	if ((Tex_BlockBLUE = LoadGraph(_T("Data/Blocks/Block_BLUE.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE.png)"));
	if ((Tex_BlockYELLOW = LoadGraph(_T("Data/Blocks/Block_YELLOW.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW.png)"));
	if ((Tex_BlockGREEN = LoadGraph(_T("Data/Blocks/Block_GREEN.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN.png)"));
	if ((Tex_BlockPURPLE = LoadGraph(_T("Data/Blocks/Block_PURPLE.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE.png)"));
	if ((Tex_BlockTREE = LoadGraph(_T("Data/Blocks/Block_TREE.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_TREE.png)"));
	if ((Tex_BlockBLACK = LoadGraph(_T("Data/Blocks/Block_BLACK.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLACK.png)"));
	if ((Tex_BlockRAINBOW = LoadGraph(_T("Data/Blocks/Block_RAINBOW.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RAINBOW.png)"));
	if ((Tex_BlockBOMB = LoadGraph(_T("Data/Blocks/Block_BOMB.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BOMB.png)"));
	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)					printLog_E(_T("ファイルの読み込み失敗(Data/image/colorbom.png)"));

	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

}

//初期化(計算処理)
void Phase_GameMain::Init_Update() {
	Flag_Pause = FALSE;
	Flag_pauseRequest = FALSE;
	Create_Wait_Block();
	Create_Wait_Block();
}

//描画処理
void Phase_GameMain::Draw() {

	//描画先をゲーム画面にする
	SetDrawScreen(gameWindow);

	ClearDrawScreen();

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawBox(BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE,
		GAMEWINDOW_WIDTH + BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_HEIGHT + BLOCK_PADDINGUP*BLOCK_SIZE,
		GetColor(0xb3, 0x65, 0xe5), TRUE);

	//フィールドブロックの描画
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//描画先の座標を計算する
			double X, Y;
			if (field[x][y].blockMoveMotion.Enable) {
				//移動モーション有り
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, &X, &Y);	//移動元座標の計算
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//現在の移動距離の計算
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//上の計算結果より、描画座標の計算
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//移動モーション無し
				Convert_Ingame_FromBlock(x, y, &X, &Y);
			}

			//中心座標に変換
			X += BLOCK_SIZE / 2.;
			Y += BLOCK_SIZE / 2.;
			if (field[x][y].blockChangeMotion.Enable) {
				//変化モーション有り
				int Alpha = (int)((field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length) * 255);

				if (field[x][y].blockChangeMotion.To == BLOCK_TYPE_NO) {
					//変化先のブロックが無効ブロックの場合は変化元を薄くする

					Alpha = 255 - Alpha;	//アルファ値反転

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
					DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else {
					//普通に描画
					DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
					//変化量に応じて半透明で描画する
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
					DrawBlock(X, Y, field[x][y].blockChangeMotion.To);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				}
			}
			else {
				DrawBlock(X, Y, field[x][y].color);
			}

		}
	}

	//落下中ブロックの描画
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
				X += BLOCK_SIZE / 2.;
				Y += BLOCK_SIZE / 2.;
				DrawBlock(X, Y, fallBlockInfo.fallblock.BlockID[x][y]);
			}
		}
	}

	//デバッグ
#ifdef _DEBUG_GAMEMAIN_
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

	//落下ブロックの範囲を描画する
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
				DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), FALSE);
			}
		}
	}
#endif // _DEBUG_GAMEMAIN_



	//描画先をバックスクリーンにする
	SetDrawScreen(DX_SCREEN_BACK);

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawGraph(0, 0, haikei, FALSE);


	//ゲーム画面を描画する(デバッグモードの場合は、全ブロック領域を描画する)
	if (DEBUG_GAMEMAIN) {
		DrawRectGraph(GAMEWINDOW_PADDINGX - BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_PADDINGY - BLOCK_PADDINGUP*BLOCK_SIZE, 0, 0, BLOCK_WIDTHNUM*BLOCK_SIZE, BLOCK_HEIGHTNUM*BLOCK_SIZE, gameWindow, FALSE, FALSE);
	}
	else {
		DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);
	}


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

	if (isPaused()) {//ポーズ状態の時
							  //ポーズ状態と分かるように描画する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (getFrameCount(THREAD_Update) % 120 > 40)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("PAUSE"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
	}
}

//ブロックを描画する(インゲーム座標)
void Phase_GameMain::DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type) {
	switch (type) {
	case BLOCK_TYPE_RED:	//赤ブロック描画
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockRED, TRUE);
		break;
	case BLOCK_TYPE_BLUE:	//青ブロック描画
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockBLUE, TRUE);
		break;
	case BLOCK_TYPE_GREEN:	//緑ブロック描画
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockGREEN, TRUE);
		break;
	case BLOCK_TYPE_PURPLE:	//紫ブロック描画
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockPURPLE, TRUE);
		break;
	case BLOCK_TYPE_YELLOW:	//黄色ブロック描画
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockYELLOW, TRUE);
		break;
	case BLOCK_TYPE_TREE:	//樹木ブロック
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockTREE, TRUE);
		break;
	case BLOCK_TYPE_BLACK:	//黒ブロック
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockBLACK, TRUE);
		break;
	case BLOCK_TYPE_RAINBOW://虹色ブロック
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockRAINBOW, TRUE);
		break;
	case BLOCK_TYPE_BOM://爆弾ブロック
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockBOMB, TRUE);
		break;
	}
}

//計算処理
void Phase_GameMain::Update() {
	//計算処理の最初に行いたい処理(多くなったら関数化？)

	//リクエストの反映

	Flag_Pause = Flag_pauseRequest;//リクエストの反映
	//ここまで

	GameMain_Key();	//キー処理

	if (isPaused())	return;//ポーズ処理が入った場合は先に進まない




	switch (gameCycle) {
	case GameCycle_FALL:
		if (getFallBlock_Interval() > 30)	Create_FallBlock(NULL);//前回の落下ブロック終了から一定時間後に落下ブロックの再出現
		//落下ブロックの落下処理
		if (Update_FallBlock()) {
			//落下完了後は計算を行う
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
		//ランダムで一番上の段に木ブロックを設置する
		for (int i = 0; add_FraldBlock((int)randomTable.getRand(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT), 1, BLOCK_TYPE_TREE) == FALSE && i < 10; i++);
		UpdateBlockRequest(GameCycle_FALL);
		break;
	case GameCycle_Update://ブロックの計算
		Update_FieldBlock();
		break;
	}
}

//落下ブロックの落下処理(TRUEで落下ブロックの落下終了)
int Phase_GameMain::Update_FallBlock() {
	if (!isFallBlock_Enable()) {
		//無効の時はインターバルカウントを加算し終了
		fallBlockInfo.Counter--;
		return FALSE;
	}

	//以下有効なとき
	fallBlockInfo.Counter++;	//カウンタを加算

	if (isFallBlock_Falling()) {//落下中の場合
		fallBlockInfo.FallCount--;
		if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 5;	//高速落下モードの場合カウントをさらに入れる
		if (fallBlockInfo.FallCount < 0)		fallBlockInfo.FallCount = 0;	//落下カウントが0以下だと都合が悪いので
		if (fallBlockInfo.Key_LRMove > 0) {
			//右移動
			if (FallBlock_MoveX(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);

		}
		if (fallBlockInfo.Key_LRMove < 0) {
			//左移動
			if (FallBlock_MoveX(-1))	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else						SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota > 0) {
			//時計回りに回転
			if (FallBlock_Rotate(1))	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else						SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota < 0) {
			//反時計回りに回転
			if (FallBlock_Rotate(-1))	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else						SoundEffect_Play(SE_TYPE_Graze);
		}

		if (fallBlockInfo.FallCount <= 0) {//カウント0以下で落下
			fallBlockInfo.FallCount = 60;	//カウントを戻す(ここで戻さないとFallBlock_MoveY関数で移動無効と判定され、うまく動かない)
											/*落下しようとして無理だったらカウントを0にし無効化する方針*/
			if (FallBlock_MoveY(1) == 0) {	//落下出来なかった
				fallBlockInfo.FallCount = -1;	//落下カウントの無効化
				printLog_I(_T("ブロックの落下終了"));
				FallBlock_addField();	//フィールドに落下ブロックを設置
				SoundEffect_Play(SE_TYPE_DecisionSelect);
				return TRUE;
			}
		}
	}

	//キー入力による状態のリセット
	fallBlockInfo.Key_FlagFirstFall = FALSE;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	return FALSE;
}

//フィールドブロックの細々とした計算ループ
int Phase_GameMain::Update_FieldBlock() {
	/*
	ゲーム更新ループ
	0.初期化処理(最初の1度のみ実行)
	1.重力計算
	2.移動モーション
	3.ブロックの特殊効果
	4.変化モーション
	5.重力計算
	6.移動モーション
	7.ブロックの消去判定→消去ブロック無しの場合は11へ
	8.変化モーション
	9.重力計算
	10.移動モーションから7へ
	11.更新ループ終了
	*/

	switch (Loop_No) {
	case 0://初期化
		Loop_No = 1;
		printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
		break;
	case 1://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 2;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 2://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			Loop_No = 3;
			printLog_I(_T("ブロックの特殊効果へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 3://ブロックの特殊効果
		Block_Black_Func();		//黒ブロックの色変更
		Block_Rainbow_Func();	//虹色ブロックの色を変更
		Block_BOMB_Func();		//爆弾ブロックの処理
		Loop_No = 4;
		printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 4://変化モーション
		if (Update_ChangeMotion() == FALSE) {
			//変化がなかった場合
			Loop_No = 5;
			printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 5://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 6;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 6://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			Loop_No = 7;
			printLog_I(_T("ブロックの消去判定へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 7://ブロックの消去判定
		if (Block_Delete() > 0) {
			//ブロックの消去判定が入れば
			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Loop_No = 8;
			printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		}
		else {
			Loop_No = 11;
			printLog_I(_T("終了処理へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 8://変化モーション
		if (Update_ChangeMotion() == FALSE) {
			//変化がなかった場合
			Loop_No = 9;
			printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 9://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 10;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 10://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			Loop_No = 7;
			printLog_I(_T("ブロックの消去判定へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 11://終了
		Loop_No = -1;
		printLog_I(_T("ブロック計算ループの終了"));
		setGameCycle(Loop_Next);
		break;
	default:
		printLog_E(_T("不明なLoop_Noが指定されました(無限ループ)(Loop_No=%d)"), Loop_No);
		break;
	}
	return 0;
}

//移動モーションの更新(移動モーションが行われたときはTRUE)
int Phase_GameMain::Update_MoveMotion() {
	int count = 0;//変化処理を行ったブロックの数

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//移動モーション
			if (field[x][y].blockMoveMotion.Enable) {
				field[x][y].blockMoveMotion.Count++;//カウントアップ
													//移動する距離の計算
				double fX, fY, tX, tY;
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, &fX, &fY);
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY, &tX, &tY);
				double FMD = getDistance(fX, fY, tX, tY);	//最終的な移動距離
				double MD = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//現在の移動距離
				if (FMD <= MD) {//移動完了
					field[x][y].blockMoveMotion.Enable = FALSE;//移動を無効化
				}
				count++;	//移動した
			}
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
			//変化モーション
			if (field[x][y].blockChangeMotion.Enable) {
				field[x][y].blockChangeMotion.Count++;//カウントアップ
				if (field[x][y].blockChangeMotion.Count > field[x][y].blockChangeMotion.Length) {//移動完了
					field[x][y].blockChangeMotion.Enable = FALSE;//移動を無効化
				}
				count++;
			}
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//終了処理(描画処理)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);

	DeleteGraph(Tex_BlockRED);
	DeleteGraph(Tex_BlockBLUE);
	DeleteGraph(Tex_BlockYELLOW);
	DeleteGraph(Tex_BlockGREEN);
	DeleteGraph(Tex_BlockPURPLE);
	DeleteGraph(Tex_BlockTREE);
	DeleteGraph(Tex_BlockBLACK);
	DeleteGraph(Tex_BlockRAINBOW);
	DeleteGraph(haikei);

	DeleteSoundMem(BGM);
}

//終了処理(計算処理)
void Phase_GameMain::Finalize_Update() {

}

//キー処理
void Phase_GameMain::GameMain_Key() {

	//ポーズ処理
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		PauseRequest(!isPaused());	//ポーズ状態の反転
	}

	if (isPaused())	return;//ポーズ処理が入った場合は先に進まない

	if (getKeyBind(KEYBIND_UP) == 1) {
		add_FraldBlock(0, 18, BLOCK_TYPE_BLUE, TRUE);
		printLog_D(_T("押した"));

	}

	if (isFallBlock_Falling()) {
		if (getKeyBind(KEYBIND_DOWN) > 0) {//高速落下モード
			fallBlockInfo.Key_FlagFirstFall = TRUE;
		}
		if (getKeyBind(KEYBIND_RIGHT) == 1) {//右移動
			fallBlockInfo.Key_LRMove++;
		}
		if (getKeyBind(KEYBIND_LEFT) == 1) {//左移動
			fallBlockInfo.Key_LRMove--;
		}
		if (getKeyBind(KEYBIND_ROTAL) == 1) {//反時計回り
			fallBlockInfo.Key_LRRota--;
		}
		if (getKeyBind(KEYBIND_ROTAR) == 1) {//時計回り
			fallBlockInfo.Key_LRRota++;
		}
	}
}

//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
void Phase_GameMain::Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE;
	}
}

//ポーズ状態かどうかの取得(TRUEでポーズ)
int Phase_GameMain::isPaused() {
	return Flag_Pause;
}

//ポーズ状態のリクエスト
void Phase_GameMain::PauseRequest(int b_Flag) {
	b_Flag = (b_Flag) ? TRUE : FALSE;//不正な引数の対策

	Flag_pauseRequest = b_Flag;
	if (Flag_pauseRequest)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ポーズリクエスト【有効】"));
	else					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ポーズリクエスト【無効】"));
}

//落下ブロックが落下中かどうかの取得(TRUEで落下中)
int Phase_GameMain::isFallBlock_Falling() {
	if (!isFallBlock_Enable())	return FALSE;
	return (fallBlockInfo.FallCount >= 0) ? TRUE : FALSE;
}

//落下ブロックが有効かどうかの取得(TRUEで有効)
int Phase_GameMain::isFallBlock_Enable() {
	return (fallBlockInfo.Enable) ? TRUE : FALSE;
}

//落下ブロックを生成する(戻り値:成功でTRUE)
int Phase_GameMain::Create_FallBlock(struct Fallblock_Pack *fallblock_Pack) {
	//if (fallblock_Pack == NULL)	return FALSE;

	if (isFallBlock_Enable()) {
		printLog_C(_T("落下中のブロックがすでに存在するため、落下ブロックを新たに追加出来ませんでした"));
		return FALSE;
	}

	//落下ブロックの形状を設定する(暫定)
	/*十時マークそして0は無効、1は有効(赤ブロックになるように設定)*/
	fallBlockInfo.fallblock.BlockID[0][0] = BLOCK_TYPE_YELLOW;
	fallBlockInfo.fallblock.BlockID[1][0] = BLOCK_TYPE_BLACK;
	fallBlockInfo.fallblock.BlockID[2][0] = BLOCK_TYPE_RED;

	fallBlockInfo.fallblock.BlockID[0][1] = BLOCK_TYPE_PURPLE;
	fallBlockInfo.fallblock.BlockID[1][1] = BLOCK_TYPE_BLUE;
	fallBlockInfo.fallblock.BlockID[2][1] = BLOCK_TYPE_GREEN;

	fallBlockInfo.fallblock.BlockID[0][2] = BLOCK_TYPE_BOM;
	fallBlockInfo.fallblock.BlockID[1][2] = BLOCK_TYPE_RAINBOW;
	fallBlockInfo.fallblock.BlockID[2][2] = BLOCK_TYPE_NO;

	//fallBlockInfo.fallblock = waitBlockinfo[1].fallblock;
	//Create_Wait_Block();

	//落下カウントを60に設定
	fallBlockInfo.FallCount = 60;

	//落下ブロックのその他の情報の初期化
	fallBlockInfo.PlaceX = BLOCK_WIDTHNUM / 2;
	fallBlockInfo.PlaceY = 2;
	fallBlockInfo.Counter = 0;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	fallBlockInfo.Key_FlagFirstFall = FALSE;

	//有効
	fallBlockInfo.Enable = TRUE;

	printLog_I(_T("落下ブロックの【新規生成】"));
	return TRUE;
}

//落下ブロックの前回の落下からのインターバルの取得(落下ブロックが存在するときは0が返ります)
int Phase_GameMain::getFallBlock_Interval() {
	if (isFallBlock_Enable())	return 0;
	return (-fallBlockInfo.Counter);
}

//落下ブロックの無効化
void Phase_GameMain::Delete_FallBlock() {
	if (!isFallBlock_Enable())	return;	//そもそも有効で無い時は無視

	fallBlockInfo.Counter = 0;		//カウンタを0にもどす
	fallBlockInfo.Enable = FALSE;	//落下ブロックの無効化

	printLog_I(_T("落下ブロックの【消去】"));
}

//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
int Phase_GameMain::FallBlock_MoveX(int MoveVal) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

	//方針:だんだんMoveValを大きくしていく
	int Minus = FALSE;//マイナスフラグ
	if (MoveVal < 0) {
		//符号反転
		MoveVal = -MoveVal;
		Minus = TRUE;
	}

	for (int i = 0; i < MoveVal; i++) {
		//擬似的に移動したことにする
		int pX = 0;
		if (Minus)	pX = fallBlockInfo.PlaceX - (i + 1);	//負の方向
		else		pX = fallBlockInfo.PlaceX + (i + 1);	//正の方向

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {
					//ブロック有りの場合、フィールドブロックとの重なりを確認する
					if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
						//他のブロックと重なっていた場合はループを抜ける
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						MoveVal = i;//最外のループも抜ける
					}
				}
			}
		}
	}

	//符号を元に戻す
	if (Minus) {
		MoveVal = -MoveVal;
	}

	//ずらしの反映
	fallBlockInfo.PlaceX += MoveVal;

	return MoveVal;
}

//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
int Phase_GameMain::FallBlock_MoveY(int MoveVal) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

												//方針:だんだんMoveValを大きくしていく
	int Minus = FALSE;//マイナスフラグ
	if (MoveVal < 0) {
		//符号反転
		MoveVal = -MoveVal;
		Minus = TRUE;
	}

	for (int i = 0; i < MoveVal; i++) {
		//擬似的に移動したことにする
		int pY = 0;
		if (Minus)	pY = fallBlockInfo.PlaceY - (i + 1);	//負の方向
		else		pY = fallBlockInfo.PlaceY + (i + 1);	//正の方向

															//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
						//他のブロックと重なっていた場合はループを抜ける
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						MoveVal = i;//最外のループも抜ける
					}
				}
			}
		}
	}

	//符号を元に戻す
	if (Minus) {
		MoveVal = -MoveVal;
	}

	//ずらしの反映
	fallBlockInfo.PlaceY += MoveVal;

	return MoveVal;
}

//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)
int Phase_GameMain::FallBlock_Rotate(int RotaVal) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

												//方針:だんだんMoveValを大きくしていく
	int Minus = FALSE;//マイナスフラグ
	if (RotaVal < 0) {
		//符号反転
		RotaVal = -RotaVal;
		Minus = TRUE;
	}


	int FLAG = FALSE;
	for (int i = 0; i < RotaVal; i++) {
		//擬似的に回転したことにする
		BLOCK_TYPE RotaBlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];
		if (Minus) {//反時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = fallBlockInfo.fallblock.BlockID[x][y];
				}
			}
		}
		else {//時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = fallBlockInfo.fallblock.BlockID[x][y];
				}
			}
		}

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (RotaBlockID[x][y] != BLOCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
						//他のブロックと重なっていた場合はループを抜ける
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						RotaVal = i;
						FLAG = TRUE;//最外のループも抜ける
					}
				}
			}
		}

		if (FLAG) {
			break;
		}
		else {
			//回転を確定する
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					fallBlockInfo.fallblock.BlockID[x][y] = RotaBlockID[x][y];
				}
			}
		}

	}

	//符号を元に戻す
	if (Minus) {
		RotaVal = -RotaVal;
	}

	return RotaVal;
}

//落下ブロックをフィールドブロックに変換する(つまり設置)
void Phase_GameMain::FallBlock_addField() {
	if (!isFallBlock_Enable())	return;	//そもそも有効で無い時は無視

	//何も無しブロック以外はフィールドブロックに順次変換を行う
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
			if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {
				int fX, fY;		//ブロックのフィールド上の位置
				BLOCK_TYPE fB;	//設置するブロックの種類
				fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
				fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
				fB = fallBlockInfo.fallblock.BlockID[x][y];

				add_FraldBlock(fX, fY, fB);

			}
		}
	}
	printLog_I(_T("落下ブロックの【設置】"));

	//落下ブロックの無効化処理
	Delete_FallBlock();

}

//フィールドにブロックを追加する(成功でTRUE,失敗でFALSE)(上書き禁止)
int Phase_GameMain::add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int OutScreen) {
	//ブロック無しブロックは設置不可
	if (brock_type == BLOCK_TYPE_NO)					return FALSE;
	//画面外ブロックも設置不可
	if (brock_type == BLOCK_TYPE_NUM)					return FALSE;

	//ブロックの上書きは失敗にする(画面外もブロック有りと判定が出る設定にする)
	if (getBlockColor(X, Y, TRUE, !OutScreen) != BLOCK_TYPE_NO)		return FALSE;

	//ブロックの設置
	field[X][Y].fall_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
	field[X][Y].move_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
	field[X][Y].color = brock_type;	//ブロックの置き換え


	printLog_I(_T("フィールドブロックの新規生成[%d][%d](type=%d)"), X, Y, brock_type);

	return TRUE;
}

//フィールドに存在する黒色ブロックの色を決定する
void Phase_GameMain::Block_Black_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_BLACK) {//黒ブロックの時
				//確率でブロックのIDを書き換える
				int Val = (int)randomTable.getRand(0, 100);
				if (Val < 20)		field[x][y].color = BLOCK_TYPE_RED;		//赤色ブロック
				else if (Val < 40)	field[x][y].color = BLOCK_TYPE_BLUE;	//青色ブロック
				else if (Val < 60)	field[x][y].color = BLOCK_TYPE_YELLOW;	//黄色ブロック
				else if (Val < 80)	field[x][y].color = BLOCK_TYPE_GREEN;	//緑色ブロック
				else 				field[x][y].color = BLOCK_TYPE_PURPLE;	//紫色ブロック

				//変化モーションの設定
				Block_SetChangeMotion(x, y, BLOCK_TYPE_BLACK, field[x][y].color, 60);
			}
		}
	}
}

//フィールドに存在する虹色ブロックの色を決定する
void Phase_GameMain::Block_Rainbow_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_RAINBOW) {//虹色ブロックの時
				if (getBlockColor(x, y + 1) == BLOCK_TYPE_NO) {
					//下にブロックが無い
					//確率でブロックのIDを書き換える
					int Val = (int)randomTable.getRand(0, 100);
					if (Val < 20)		field[x][y].color = BLOCK_TYPE_RED;		//赤色ブロック
					else if (Val < 40)	field[x][y].color = BLOCK_TYPE_BLUE;	//青色ブロック
					else if (Val < 60)	field[x][y].color = BLOCK_TYPE_YELLOW;	//黄色ブロック
					else if (Val < 80)	field[x][y].color = BLOCK_TYPE_GREEN;	//緑色ブロック
					else 				field[x][y].color = BLOCK_TYPE_PURPLE;	//紫色ブロック

				}
				else {
					//下にブロックがある場合
					field[x][y].color = getBlockColor(x, y + 1);
				}

				//変化モーションの設定
				Block_SetChangeMotion(x, y, BLOCK_TYPE_RAINBOW, field[x][y].color, 60);


			}
		}
	}
}

//フィールドに存在する爆弾ブロックを爆破する
void Phase_GameMain::Block_BOMB_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_BOM) {//爆弾ブロックの時
				//自身の削除
				if (Block_Delete_Direct(x, y, TRUE))	DeleteNum++;

				//周囲のブロックを削除する(爆弾ブロックは削除しない)
				if (getBlockColor(x + 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 2, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 2, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 2, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 2, TRUE))	DeleteNum++;
				}


				if (getBlockColor(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y - 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y - 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y + 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y + 1, TRUE))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Bulletfire5);

}

//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock, int InGame) {

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

	return field[X][Y].color;

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
		field_info t[BLOCK_HEIGHTNUM];
		for (int y = sY; y < eY; y++) {
			t[y] = field[x][y];
			field[x][y].color = BLOCK_TYPE_NO;
		}
		int Count = eY - 1;
		//下の段から存在するブロックを並べ直す(逆順回し)
		for (int y = eY - 1; y >= sY; y--) {
			if (t[y].color != BLOCK_TYPE_NO) {
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
int Phase_GameMain::Block_Delete_Direct(int X, int Y, int PlayMotion) {
	//画面外処理
	BLOCK_TYPE t = getBlockColor(X, Y);
	if (t == BLOCK_TYPE_NO)	return FALSE;//ないので削除しない

	field[X][Y].color = BLOCK_TYPE_NO;
	printLog_I(_T("ブロックの【削除】[%d][%d]"), X, Y);

	if (PlayMotion)			Block_SetChangeMotion(X, Y, t, BLOCK_TYPE_NO, 40);	//モーションの生成
	else					field[X][Y].blockChangeMotion.Enable = FALSE;		//モーションの削除

	return TRUE;
}

//指定した座標が指定したブロックだった場合に削除(削除されたらTRUE)
int Phase_GameMain::Block_Delete_Type(int X, int Y, BLOCK_TYPE type, int PlayMotion) {
	if (getBlockColor(X, Y) != type)	return FALSE;//違うブロックの場合は削除しない

	return Block_Delete_Direct(X, Y, PlayMotion);
}

//連続するフィールドブロックを削除する(ついでにお邪魔ブロックの処理も行う)(消去したブロックの数)
int Phase_GameMain::Block_Delete() {
	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_NO ||
				field[x][y].color == BLOCK_TYPE_NUM ||
				field[x][y].color == BLOCK_TYPE_TREE ||
				field[x][y].color == BLOCK_TYPE_BLACK ||
				field[x][y].color == BLOCK_TYPE_RAINBOW ||
				field[x][y].color == BLOCK_TYPE_BOM) {//除外ブロック
				DeleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				DeleteFlag[x][y] = -1;
			}
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

	//4以上隣接しているブロックは削除する
	int DelCount = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
				if (Counter[DeleteFlag[x][y]] >= 3) {
					//削除
					Block_Delete_Direct(x, y, TRUE);
					DelCount++;
					//ついでに隣接する樹木ブロックも削除
					if (Block_Delete_Type(x, y - 1, BLOCK_TYPE_TREE, TRUE))	DelCount++;//上
					if (Block_Delete_Type(x, y + 1, BLOCK_TYPE_TREE, TRUE))	DelCount++;//下
					if (Block_Delete_Type(x - 1, y, BLOCK_TYPE_TREE, TRUE))	DelCount++;//左
					if (Block_Delete_Type(x + 1, y, BLOCK_TYPE_TREE, TRUE))	DelCount++;//右

				}
			}
		}
	}

	printLog_I(_T("隣接ブロックの削除計算を行いました(%dブロック)"), DelCount);


	return DelCount;
}

//隣接する同色ブロックにマーカーを付ける
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter) {
	if (deleteFlag[x][y] != -1)	return;		//未探索ブロックじゃない場合
	BLOCK_TYPE bt = field[x][y].color;      //ブロックの種類を記録する
	deleteFlag[x][y] = ID;					//探索済み(探索IDを設定する)
	(*Counter)++;

	if (x + 1 < BLOCK_WIDTHNUM	&& field[x + 1][y].color == bt) SequenceCount(x + 1, y, ID, deleteFlag, Counter);
	if (y + 1 < BLOCK_HEIGHTNUM	&& field[x][y + 1].color == bt) SequenceCount(x, y + 1, ID, deleteFlag, Counter);
	if (x - 1 >= 0 && field[x - 1][y].color == bt) SequenceCount(x - 1, y, ID, deleteFlag, Counter);
	if (y - 1 >= 0 && field[x][y - 1].color == bt) SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//フィールドのブロック移動にモーションを設定する
void Phase_GameMain::Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockColor(x, y, FALSE, FALSE) == BLOCK_TYPE_NO)	return;	//ブロックが無効の場合は処理をしない
	if (FromX == ToX && FromY == ToY)			return;	//移動無しの場合も処理をしない
	if (a <= 0)									return;	//加速度が負の数の場合も処理をしない
	if (MaxSpeed <= 0)							return;	//最大速度が負の数の場合も処理をしない

	if (field[x][y].blockMoveMotion.Enable) {
		printLog_C(_T("ブロックの移動モーションを上書きします"));
		field[x][y].blockMoveMotion.Enable = FALSE;
	}

	field[x][y].blockMoveMotion.ToX = ToX;
	field[x][y].blockMoveMotion.ToY = ToY;
	field[x][y].blockMoveMotion.FromX = FromX;
	field[x][y].blockMoveMotion.FromY = FromY;
	field[x][y].blockMoveMotion.a = a;
	field[x][y].blockMoveMotion.MaxSpeed = MaxSpeed;
	field[x][y].blockMoveMotion.Count = 0;

	field[x][y].blockMoveMotion.Enable = TRUE;

	printLog_I(_T("ブロックに【移動モーション】を設定"));
}

//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Phase_GameMain::isBlock_PlayMoveMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].blockMoveMotion.Enable) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//フィールドのブロックに変化モーションを設定する
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//ブロックが画面外の場合は処理をしない
	if (From == To)											return;	//変化無しの場合も処理をしない
	if (MotionLength <= 0)									return;	//長さが負の数の場合も処理をしない

	if (field[x][y].blockChangeMotion.Enable) {
		printLog_C(_T("ブロック変化モーションを上書きします"));
		field[x][y].blockChangeMotion.Enable = FALSE;
	}

	field[x][y].blockChangeMotion.To = To;
	field[x][y].blockChangeMotion.From = From;
	field[x][y].blockChangeMotion.Length = MotionLength;
	field[x][y].blockChangeMotion.Count = 0;

	field[x][y].blockChangeMotion.Enable = TRUE;

	printLog_I(_T("ブロックに【変化モーション】を設定[%d][%d]"), x, y);
}

//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Phase_GameMain::isBlock_PlayChangeMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].blockChangeMotion.Enable) {
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
	if (Next == GameCycle_NUM || Next == GameCycle_Update) {
		printLog_E(_T("引数が不正です"));
		return;
	}

	if (gameCycle == GameCycle_Update) {
		//すでに実行されている
		printLog_E(_T("現在ブロック情報の更新を行ってるためリクエストは無視されます"));
	}

	//ブロック計算サイクルへ移行
	setGameCycle(GameCycle_Update);

	//移行先のゲームサイクルを記録する
	Loop_Next = Next;

	//計算ループの処理位置を設定
	Loop_No = 0;

	printLog_I(_T("ブロック計算ループに入ります(終了後=%d)"), Loop_Next);

}

void Phase_GameMain::Create_Wait_Block() {
	waitBlockinfo[1].fallblock = waitBlockinfo[0].fallblock;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			waitBlockinfo[0].fallblock.BlockID[i][j] = BLOCK_TYPE_NO;
		}
	}
	int wait_block_patern = rand() % 2;
	if (wait_block_patern == 0) {//縦
		for (i = 0; i < 2; i++) {
			int wait_block_type = (rand() % BLOCK_TYPE_PURPLE) + 1;
			switch (wait_block_type) {

			case 1:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_RED;//赤
				break;
			case 2:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_BLUE;//青
				break;
			case 3:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_YELLOW;//黄
				break;
			case 4:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_GREEN;//緑
				break;
			case 5:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_PURPLE;//紫
			}
		}
	}
	else {//if (wait_block_patern == 1) {//横
		for (i = 0; i < 2; i++) {
			int wait_block_type = (rand() % BLOCK_TYPE_PURPLE) + 1;
			switch (wait_block_type) {
			case 0:

				break;
			case 1:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_RED;//赤
				break;
			case 2:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_BLUE;//青
				break;
			case 3:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_YELLOW;//黄
				break;
			case 4:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_GREEN;//緑
				break;
			case 5:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_PURPLE;//紫
			}
		}
	}
}

/*
BLOCK_TYPE Phase_GameMain::Get_Block_Type(int h) {
	switch (h)
	{
	case 0:

		break;
	case 1:
		return BLOCK_TYPE_RED;//赤
	case 2:
		return BLOCK_TYPE_BLUE;//青
	case 3:
		return BLOCK_TYPE_YELLOW;//黄
	case 4:
		return BLOCK_TYPE_GREEN;//緑

	case 5:
		return BLOCK_TYPE_PURPLE;//紫


	}
	return BLOCK_TYPE_NO;
}
*/