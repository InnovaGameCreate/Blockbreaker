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

	//ブロック画像
	if ((Tex_BlockRED = LoadGraph(_T("Data/Blocks/Block_RED.png"))) == -1)								printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED.png)"));
	if ((Tex_BlockRED_ARROW_X = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_X.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_X.png)"));
	if ((Tex_BlockRED_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_Y.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_Y.png)"));
	if ((Tex_BlockRED_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_XY.png)"));
	if ((Tex_BlockRED_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY2.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_XY2.png)"));

	if ((Tex_BlockBLUE = LoadGraph(_T("Data/Blocks/Block_BLUE.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE.png)"));
	if ((Tex_BlockBLUE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_X.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_X.png)"));
	if ((Tex_BlockBLUE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_Y.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_Y.png)"));
	if ((Tex_BlockBLUE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_XY.png)"));
	if ((Tex_BlockBLUE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY2.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_XY2.png)"));

	if ((Tex_BlockYELLOW = LoadGraph(_T("Data/Blocks/Block_YELLOW.png"))) == -1)						printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW.png)"));
	if ((Tex_BlockYELLOW_ARROW_X = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_X.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_X.png)"));
	if ((Tex_BlockYELLOW_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_Y.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_Y.png)"));
	if ((Tex_BlockYELLOW_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_XY.png)"));
	if ((Tex_BlockYELLOW_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY2.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_XY2.png)"));

	if ((Tex_BlockGREEN = LoadGraph(_T("Data/Blocks/Block_GREEN.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN.png)"));
	if ((Tex_BlockGREEN_ARROW_X = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_X.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_X.png)"));
	if ((Tex_BlockGREEN_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_Y.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_Y.png)"));
	if ((Tex_BlockGREEN_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_XY.png)"));
	if ((Tex_BlockGREEN_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY2.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_XY2.png)"));

	if ((Tex_BlockPURPLE = LoadGraph(_T("Data/Blocks/Block_PURPLE.png"))) == -1)						printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE.png)"));
	if ((Tex_BlockPURPLE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_X.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_X.png)"));
	if ((Tex_BlockPURPLE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_Y.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_Y.png)"));
	if ((Tex_BlockPURPLE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_XY.png)"));
	if ((Tex_BlockPURPLE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY2.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_XY2.png)"));

	if ((Tex_BlockTREE = LoadGraph(_T("Data/Blocks/Block_TREE.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_TREE.png)"));
	if ((Tex_BlockBLACK = LoadGraph(_T("Data/Blocks/Block_BLACK.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLACK.png)"));
	if ((Tex_BlockRAINBOW = LoadGraph(_T("Data/Blocks/Block_RAINBOW.png"))) == -1)						printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RAINBOW.png)"));
	if ((Tex_BlockBOMB = LoadGraph(_T("Data/Blocks/Block_BOMB.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BOMB.png)"));
	if ((Tex_Block2BOMB = LoadGraph(_T("Data/Blocks/Block_2BOMB.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_2BOMB.png)"));
	if ((Tex_BlockBOMB_Color = LoadGraph(_T("Data/Blocks/Block_BOMB_Color.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BOMB_Color.png)"));
	if ((Tex_BlockFireEffect = LoadGraph(_T("Data/Blocks/Block_FireEffect.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_FireEffect.png)"));
	if ((Tex_BlockFireEffect2 = LoadGraph(_T("Data/Blocks/Block_FireEffect2.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_FireEffect2.png)"));
	if ((Tex_BlockCenterEffect = LoadGraph(_T("Data/Blocks/Block_CENTER.png"))) == -1)					printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_CENTER.png)"));
	if ((Tex_BlockBack = LoadGraph(_T("Data/Blocks/Block_Back.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_Back.png)"));

	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/colorbom.png)"));
	if ((Tex_FieldBack = LoadGraph(_T("Data/image/BlockField_Back.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/BlockField_Back.png)"));


	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

	pauseMenu.setEnable(TRUE);
}

//フルスクリーンに復帰時に呼ばれる
void Phase_GameMain::RestoreGraphCallback() {
	//テクスチャの読み直し
}

//初期化(計算処理)
void Phase_GameMain::Init_Update() {
	Create_Wait_Block();
	Create_Wait_Block();
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
	//落下中ブロックの削除
	Delete_FallBlock();
	score.init();//スコアの初期化
	//ブロック待機列の初期化
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo); i++) Create_Wait_Block();

	//ブロックの削除を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].color = BLOCK_TYPE_NO;
			field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;
			field[x][y].blockMoveMotion.Enable = FALSE;
			field[x][y].fall_flag = 0;
			field[x][y].move_flag = 0;
		}
	}

	//適当にブロックを設置する(下から3段)
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

	Draw_FallBlock();	//落下ブロックの描画

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
	Convert_Ingame_FromBlock(0, GAMEOVER_BORDER, 0, 0, NULL, &tY);
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

	//落下ブロックの範囲を描画する
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0, 0, &X, &Y);
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
	}
}

//落下ブロックの描画
void Phase_GameMain::Draw_FallBlock() {
	//フィールド全体のズレを計算する
	double Field_PaddingX = 0;
	double Field_PaddingY = 0;
	if (Block_AllMovedata.Enable) {//全体ずらすが有効な場合
		double D = getMoveDistance(Block_AllMovedata.a, Block_AllMovedata.MaxSpeed, Block_AllMovedata.Count);	//現在の移動距離の計算
		double Rota = getRotation(Block_AllMovedata.FromX, Block_AllMovedata.FromY, Block_AllMovedata.ToX, Block_AllMovedata.ToY);
		//上の計算結果より、描画座標の計算
		Field_PaddingX += D * cos(deg_to_rad(Rota));
		Field_PaddingY += D * sin(deg_to_rad(Rota));
	}


	if (isFallBlock_Enable()) {//落下ブロックが有効な時

		//ブロックの落下予想地点にブロックを描画する
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			int ShadowDrawDFlag = FALSE;
			int yCount = 0;	//y方向に存在するブロックの数
			for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
				//ブロックの落下予想地点の描画
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {

					int ansY = getBlock_Upper(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER)) - 1 - yCount;
					double X, Y;
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), ansY, 0.5, 0.5, &X, &Y);

					//フィールドのズレの部分を反映する
					X += Field_PaddingX;
					Y += Field_PaddingY;

					DrawBlock_Tex(X, Y, Tex_BlockBack);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
					DrawBlock(X, Y, fallBlockInfo.BlockID[x][y]);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					yCount++;
				}
			}
		}

		//落下中ブロックの描画
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			int ShadowDrawDFlag = FALSE;
			int yCount = 0;	//y方向に存在するブロックの数
			for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
				double X, Y;
				double Per = -(fallBlockInfo.FallCount / 60.);
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0.5, Per + 0.5, &X, &Y);

				//フィールドのズレの部分を反映する
				X += Field_PaddingX;
				Y += Field_PaddingY;
				//画面外に出てしまう場合はでないように調整する
				int Dan = 0;//ブロックが存在する段数
				for (int y2 = 0; y2 < FALLBLOCK_SIZE; y2++) {
					for (int x2 = 0; x2 < FALLBLOCK_SIZE; x2++) {
						if (fallBlockInfo.BlockID[x2][y2] != BLOCK_TYPE_NO) {
							Dan = y2;
							//ループを抜ける
							x2 = FALLBLOCK_SIZE;
							y2 = FALLBLOCK_SIZE;
						}
					}
				}
				if (Y < (y - Dan + BLOCK_PADDINGUP)*BLOCK_SIZE + BLOCK_SIZE / 2) {
					Y = (y - Dan + BLOCK_PADDINGUP)*BLOCK_SIZE + BLOCK_SIZE / 2;
				}

				DrawBlock(X, Y, fallBlockInfo.BlockID[x][y]);
				if (x == 1 && y == 1 && fallBlockInfo.Flag_Rotate) {
					//中心の場合かつ回転可能ブロックの場合
					//float Scale = 0.9 + getGraph_Sin(fallBlockInfo.Counter*5, 0.05, 0);
					float Scale = 1;

					DrawRectRotaGraphFast2((int)X, (int)Y, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, Scale, 0, Tex_BlockCenterEffect, TRUE, FALSE);
				}
			}
		}
	}
}

//フィールドブロックの描画
void Phase_GameMain::Draw_FieldBlock() {

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//描画先の座標を取得
			double X, Y;
			X = field[x][y].DrawPlaceX;
			Y = field[x][y].DrawPlaceY;

			//ゲームオーバー時に下に落下させる
			if (getPauseMode() == PauseMode_GameOver) {
				if (Count_Pause < 300)	Y += 1 / 2.*0.2*Count_Pause*Count_Pause;
				else					Y += 1 / 2.*0.2 * 300 * 300;
			}

			switch (field[x][y].blockChangeMotion.Type) {
			case BlockChangeMotionType_NO:
				//変化モーション無しの場合は無難に描画する
				DrawBlock(X, Y, field[x][y].color);
				break;
			case BlockChangeMotionType_NOMAL:
				//普通の変化モーション
				DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
				//変化量に応じて半透明で描画する
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)((field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length) * 255));
				DrawBlock(X, Y, field[x][y].blockChangeMotion.To);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case BlockChangeMotionType_EXPLOSION:
				//爆発(シェーダに頑張ってもらう)
				if (field[x][y].blockChangeMotion.Count < 0) {//モーション前は普通に描画
					DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
				}
				else {
					ShaderBackGround_DeleteBlock(X, Y, field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length
						, getBlockTexture(field[x][y].blockChangeMotion.From), Tex_BlockFireEffect, Tex_BlockFireEffect2);
				}
				break;
			case BlockChangeMotionType_SMALL:
				//小さくなる
				DrawBlock(X, Y, field[x][y].blockChangeMotion.From, 1 - (field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length));
				break;
			}
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
	int placeX = 550;
	int placeY = 60;
	double Before_X = 0;	//直前の描画エリアの高さ
	double Scale = 1;

	for (int i = 0; i < min(ARRAY_LENGTH(waitBlockinfo), 5); i++) {
		placeY += (int)Before_X;
		if (i != 0)	Scale = 0.7;
		Before_X = BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale + 20;
		DrawBox(placeX, placeY, (int)(placeX + BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale), (int)(placeY + BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale), GetColor(10, 10, 10), TRUE);
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);

				//縦にずらす
				X *= Scale;
				Y *= Scale;

				X += placeX + BLOCK_SIZE * Scale;
				Y += placeY + BLOCK_SIZE * Scale;

				DrawBlock(X, Y, waitBlockinfo[i].BlockID[x][y], Scale);
			}
		}
	}
}

//ブロックを描画する(インゲーム座標)
void Phase_GameMain::DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type, double Scale) {

	if (type == BLOCK_TYPE_NO)	return;

	DrawBlock_Tex(CenterX, CenterY, getBlockTexture(type), Scale);
}

//テクスチャを直接指定してブロックを描画する(インゲーム座標)
void Phase_GameMain::DrawBlock_Tex(double CenterX, double CenterY, int tex, double Scale) {

	if (tex <= 0)	return;

	DrawRectRotaGraphFast2((int)CenterX, (int)CenterY, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, (float)Scale, 0, tex, TRUE, FALSE);
}

//ブロックタイプよりテクスチャハンドルの取得
int Phase_GameMain::getBlockTexture(BLOCK_TYPE type) {
	switch (type) {
	case BLOCK_TYPE_RED:	//赤ブロック
		return Tex_BlockRED;
	case BLOCK_TYPE_BLUE:	//青ブロック
		return Tex_BlockBLUE;
	case BLOCK_TYPE_GREEN:	//緑ブロック
		return Tex_BlockGREEN;
	case BLOCK_TYPE_PURPLE:	//紫ブロック
		return Tex_BlockPURPLE;
	case BLOCK_TYPE_RED_ARROW_X://赤(平行矢印)
		return Tex_BlockRED_ARROW_X;
	case BLOCK_TYPE_RED_ARROW_Y://赤(垂直矢印)
		return Tex_BlockRED_ARROW_Y;
	case BLOCK_TYPE_RED_ARROW_XY://赤(斜め右上)
		return Tex_BlockRED_ARROW_XY;
	case BLOCK_TYPE_RED_ARROW_XY2://赤(斜め右下)
		return Tex_BlockRED_ARROW_XY2;
	case BLOCK_TYPE_BLUE_ARROW_X://青(平行矢印)
		return Tex_BlockBLUE_ARROW_X;
	case BLOCK_TYPE_BLUE_ARROW_Y://青(垂直矢印)
		return Tex_BlockBLUE_ARROW_Y;
	case BLOCK_TYPE_BLUE_ARROW_XY://青(斜め右上)
		return Tex_BlockBLUE_ARROW_XY;
	case BLOCK_TYPE_BLUE_ARROW_XY2://青(斜め右下)
		return Tex_BlockBLUE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW_ARROW_X://黄(平行矢印)
		return Tex_BlockYELLOW_ARROW_X;
	case BLOCK_TYPE_YELLOW_ARROW_Y://黄(垂直矢印)
		return Tex_BlockYELLOW_ARROW_Y;
	case BLOCK_TYPE_YELLOW_ARROW_XY://黄(斜め右上)
		return Tex_BlockYELLOW_ARROW_XY;
	case BLOCK_TYPE_YELLOW_ARROW_XY2://黄(斜め右下)
		return Tex_BlockYELLOW_ARROW_XY2;
	case BLOCK_TYPE_GREEN_ARROW_X://緑(平行矢印)
		return Tex_BlockGREEN_ARROW_X;
	case BLOCK_TYPE_GREEN_ARROW_Y://緑(垂直矢印)
		return Tex_BlockGREEN_ARROW_Y;
	case BLOCK_TYPE_GREEN_ARROW_XY://緑(斜め右上)
		return Tex_BlockGREEN_ARROW_XY;
	case BLOCK_TYPE_GREEN_ARROW_XY2://緑(斜め右下)
		return Tex_BlockGREEN_ARROW_XY2;
	case BLOCK_TYPE_PURPLE_ARROW_X://紫(平行矢印)
		return Tex_BlockPURPLE_ARROW_X;
	case BLOCK_TYPE_PURPLE_ARROW_Y://紫(垂直矢印)
		return Tex_BlockPURPLE_ARROW_Y;
	case BLOCK_TYPE_PURPLE_ARROW_XY://紫(斜め右上)
		return Tex_BlockPURPLE_ARROW_XY;
	case BLOCK_TYPE_PURPLE_ARROW_XY2://紫(斜め右下)
		return Tex_BlockPURPLE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW:	//黄色ブロック描画
		return Tex_BlockYELLOW;
	case BLOCK_TYPE_TREE:	//樹木ブロック
		return Tex_BlockTREE;
	case BLOCK_TYPE_BLACK:	//黒ブロック
		return Tex_BlockBLACK;
	case BLOCK_TYPE_RAINBOW://虹色ブロック
		return Tex_BlockRAINBOW;
	case BLOCK_TYPE_BOM://爆弾ブロック
		return Tex_BlockBOMB;
	case BLOCK_TYPE_2BOM://2爆弾ブロック
		return Tex_Block2BOMB;
	case BLOCK_TYPE_BOM_Color://同色爆弾ブロック
		return Tex_BlockBOMB_Color;
	}
	printLog_E(_T("テクスチャ番号を取得できませんでした(BLOCK_TYPE=%d)"), type);
	return -1;	//エラー
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
	}

	//破壊光線エフェクトの更新
	Update_Lay_BlockDel();
	//フライテキストの更新
	flyText.Update();

	//ブロック全体移動が有効な場合は、通常の処理を実行せず、全体移動のカウントアップのみ行うようにする
	if (Block_AllMovedata.Enable == TRUE) {
		Block_AllMovedata.Count++;//カウントアップ
		//移動する距離の計算
		double fX, fY, tX, tY;
		Convert_Ingame_FromBlock(Block_AllMovedata.FromX, Block_AllMovedata.FromY, 0, 0, &fX, &fY);
		Convert_Ingame_FromBlock(Block_AllMovedata.ToX, Block_AllMovedata.ToY, 0, 0, &tX, &tY);
		double FMD = getDistance(fX, fY, tX, tY);	//最終的な移動距離
		double MD = getMoveDistance(Block_AllMovedata.a, Block_AllMovedata.MaxSpeed, Block_AllMovedata.Count);	//現在の移動距離
		if (FMD <= MD) {//移動完了

			Block_AllMove(Block_AllMovedata.ToX, Block_AllMovedata.ToY);
			Block_AllMovedata.Enable = FALSE;//移動を無効化(Block_AllMoveしてからすること！)

			////ゲームオーバーの判定を行う
			//if (JudgeGameOver() != 0) {
			//	PauseRequest(PauseMode_GameOver);	//ポーズリクエスト
			//}

			UpdateBlockRequest(gameCycle);	//現在のゲームサイクルに割り込む形でブロックのアップデートを入れる
		}
		return;
	}

	switch (gameCycle) {
	case GameCycle_FALL:
		if (getFallBlock_Interval() > 30) {
			Count_Turn++;
			Create_FallBlock();//前回の落下ブロック終了から一定時間後に落下ブロックの再出現
		}
		//落下ブロックの落下処理
		if (Update_FallBlock()) {
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
				add_FraldBlock(ran[i], BLOCK_PADDINGUP, BLOCK_TYPE_TREE);
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
		if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 20;	//高速落下モードの場合カウントをさらに入れる

		if (fallBlockInfo.FallCount < 0)		fallBlockInfo.FallCount = 0;	//落下カウントが0以下だと都合が悪いので
		if (fallBlockInfo.Key_LRMove > 0) {
			//右移動
			if (FallBlock_MoveX(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);

		}
		if (fallBlockInfo.Key_LRMove < 0) {
			//左移動
			if (FallBlock_MoveX(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota > 0) {
			//時計回りに回転
			if (FallBlock_Rotate(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota < 0) {
			//反時計回りに回転
			if (FallBlock_Rotate(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);
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
			PauseRequest(PauseMode_GameOver);
			//UpdateBlockRequest(GameCycle_Update);
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
	int count = 0;//変化処理を行ったブロックの数

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//移動モーション
			if (field[x][y].blockMoveMotion.Enable) {
				field[x][y].blockMoveMotion.Count++;//カウントアップ
													//移動する距離の計算
				double fX, fY, tX, tY;
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, 0, 0, &fX, &fY);
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY, 0, 0, &tX, &tY);
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
			if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
				field[x][y].blockChangeMotion.Count++;//カウントアップ
				if (field[x][y].blockChangeMotion.Count > field[x][y].blockChangeMotion.Length) {//モーション完了
					field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;//変化モーションを無効化
				}
				count++;
			}
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//カウンタのカウントアップ
void Phase_GameMain::Update_Counter() {

	//実際に操作をしている経過フレーム数の加算
	if (getPauseMode() == PauseMode_NO
		&& Block_AllMovedata.Enable == FALSE
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
	if (Block_AllMovedata.Enable) {//全体ずらすが有効な場合
		double D = getMoveDistance(Block_AllMovedata.a, Block_AllMovedata.MaxSpeed, Block_AllMovedata.Count);	//現在の移動距離の計算
		double Rota = getRotation(Block_AllMovedata.FromX, Block_AllMovedata.FromY, Block_AllMovedata.ToX, Block_AllMovedata.ToY);
		//上の計算結果より、描画座標の計算
		Field_PaddingX += D * cos(deg_to_rad(Rota));
		Field_PaddingY += D * sin(deg_to_rad(Rota));
	}
	//フィールドブロックの座標計算
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//描画先の座標を計算する
			double X, Y;
			if (field[x][y].blockMoveMotion.Enable) {
				//移動モーション有り
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, 0.5, 0.5, &X, &Y);	//移動元座標の計算
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//現在の移動距離の計算
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//上の計算結果より、描画座標の計算
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//移動モーション無し
				Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
			}

			//全体ずらしの分描画座標をずらす
			X += Field_PaddingX;
			Y += Field_PaddingY;

			//ゲームオーバーが近い場合は左右に揺らす
			if (getBlockColor(x, GAMEOVER_BORDER + 2) != BLOCK_TYPE_NO) {
				if (getBlockColor(x, GAMEOVER_BORDER) != BLOCK_TYPE_NO)	X += getGraph_Sin(getCountTime() * 30, 3, 0);
				X += randomTable.getRand(-2, 2, getCountTime() + x*y + y);
			}

			//座標の記録
			field[x][y].DrawPlaceX = X;
			field[x][y].DrawPlaceY = Y;
		}
	}

}

//終了処理(描画処理)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);

	DeleteGraph(Tex_BlockRED);
	DeleteGraph(Tex_BlockRED_ARROW_X);
	DeleteGraph(Tex_BlockRED_ARROW_Y);
	DeleteGraph(Tex_BlockRED_ARROW_XY);
	DeleteGraph(Tex_BlockRED_ARROW_XY2);
	DeleteGraph(Tex_BlockBLUE);
	DeleteGraph(Tex_BlockBLUE_ARROW_X);
	DeleteGraph(Tex_BlockBLUE_ARROW_Y);
	DeleteGraph(Tex_BlockBLUE_ARROW_XY);
	DeleteGraph(Tex_BlockBLUE_ARROW_XY2);
	DeleteGraph(Tex_BlockYELLOW);
	DeleteGraph(Tex_BlockYELLOW_ARROW_X);
	DeleteGraph(Tex_BlockYELLOW_ARROW_Y);
	DeleteGraph(Tex_BlockYELLOW_ARROW_XY);
	DeleteGraph(Tex_BlockYELLOW_ARROW_XY2);
	DeleteGraph(Tex_BlockGREEN);
	DeleteGraph(Tex_BlockGREEN_ARROW_X);
	DeleteGraph(Tex_BlockGREEN_ARROW_Y);
	DeleteGraph(Tex_BlockGREEN_ARROW_XY);
	DeleteGraph(Tex_BlockGREEN_ARROW_XY2);
	DeleteGraph(Tex_BlockPURPLE);
	DeleteGraph(Tex_BlockPURPLE_ARROW_X);
	DeleteGraph(Tex_BlockPURPLE_ARROW_Y);
	DeleteGraph(Tex_BlockPURPLE_ARROW_XY);
	DeleteGraph(Tex_BlockPURPLE_ARROW_XY2);
	DeleteGraph(Tex_BlockTREE);
	DeleteGraph(Tex_BlockBLACK);
	DeleteGraph(Tex_BlockRAINBOW);
	DeleteGraph(Tex_BlockFireEffect);
	DeleteGraph(Tex_BlockFireEffect2);
	DeleteGraph(Tex_BlockCenterEffect);
	DeleteGraph(Tex_BlockBOMB);
	DeleteGraph(Tex_Block2BOMB);
	DeleteGraph(Tex_BlockBOMB_Color);
	DeleteGraph(Tex_BlockBack);

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
			PauseRequest(PauseMode_NO);	//ポーズ状態
		}
		else if (getPauseMode() == PauseMode_NO) {
			//ポーズに
			pauseMenu.setSelecedtItem(0);
			SoundEffect_Play(SE_TYPE_Pause);
			PauseRequest(PauseMode_NOMAL);	//ポーズ状態
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

	if (isFallBlock_Falling() && !Block_AllMovedata.Enable) {
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

//ブロックの座標？からインゲームの座標を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
void Phase_GameMain::Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE + XVal*BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE + YVal*BLOCK_SIZE;
	}
}

//ポーズ状態の取得
Phase_GameMain::PauseMode Phase_GameMain::getPauseMode() {
	return Flag_Pause;
}

//ポーズ状態のリクエスト
void Phase_GameMain::PauseRequest(PauseMode pauseMode) {

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
	}
	Flag_pauseRequest = pauseMode;
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
int Phase_GameMain::Create_FallBlock() {
	//if (fallblock_Pack == NULL)	return FALSE;

	if (isFallBlock_Enable()) {
		printLog_C(_T("落下中のブロックがすでに存在するため、落下ブロックを新たに追加出来ませんでした"));
		return FALSE;
	}

	//ブロック待機列の先頭の要素から生成する

	//ブロック情報のコピー
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			fallBlockInfo.BlockID[i][j] = waitBlockinfo[0].BlockID[i][j];
		}
	}

	//拡張設定のコピー
	fallBlockInfo.PlaceX = waitBlockinfo[0].PlaceX;
	fallBlockInfo.PlaceY = waitBlockinfo[0].PlaceY;
	fallBlockInfo.Flag_Rotate = waitBlockinfo[0].Flag_Rotate;


	//落下カウントを60に設定
	fallBlockInfo.FallCount = 60;

	//落下ブロックのその他の情報の初期化
	fallBlockInfo.Counter = 0;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	fallBlockInfo.Key_FlagFirstFall = FALSE;

	//有効
	fallBlockInfo.Enable = TRUE;

	printLog_I(_T("落下ブロックの【新規生成】"));

	//ブロック待機列を進める
	Create_Wait_Block();

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
int Phase_GameMain::FallBlock_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

	MoveVal = getFallBlockVal_MoveX(MoveVal, CollisionFieldBlock);

	//ずらしの反映
	fallBlockInfo.PlaceX += MoveVal;




	return MoveVal;
}

//落下ブロックがX軸方向に移動可能かどうかの取得(|移動出来る量|<=MoveVal)(つまり0で移動不可)
int Phase_GameMain::getFallBlockVal_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isFallBlock_Falling())		return FALSE;	//そもそも落下中で無い時は移動不可


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
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {
					//ブロック有りの場合、フィールドブロックとの重なりを確認する
					if (CollisionFieldBlock) {//フィールドブロックとのあたり判定を有効にする場合
						if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//他のブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
					}
					else {
						if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
							//画面外ブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
					}
				}
			}
		}
	}
	//符号を元に戻す
	if (Minus) {
		MoveVal = -MoveVal;
	}

	return MoveVal;
}

//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
int Phase_GameMain::FallBlock_MoveY(int MoveVal, int CollisionFieldBlock) {
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
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (CollisionFieldBlock) {//フィールドブロックとのあたり判定を有効にする場合
						if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//他のブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
					}
					else {
						if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
							//画面外ブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
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

	if (fallBlockInfo.Flag_Rotate == FALSE)	return 0;//回転が無効の場合は回転しない

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
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = fallBlockInfo.BlockID[x][y];
				}
			}
		}
		else {//時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = fallBlockInfo.BlockID[x][y];
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
					fallBlockInfo.BlockID[x][y] = RotaBlockID[x][y];
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
			if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {
				int fX, fY;		//ブロックのフィールド上の位置
				BLOCK_TYPE fB;	//設置するブロックの種類
				fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
				fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
				fB = fallBlockInfo.BlockID[x][y];

				add_FraldBlock(fX, fY, fB);

			}
		}
	}
	printLog_I(_T("落下ブロックの【設置】"));

	//落下ブロックの無効化処理
	Delete_FallBlock();

}

//フィールドにブロックを追加(削除)する(移動モーションは削除されます)
/*
引数
	Override:TRUEでブロック上書きを許可する(消すときはTRUEにしないとブロックは消えないよ)
	MotionInit:TRUEでモーションデータも初期化する
	OutScreen:TRUEで画面外にブロックを設置することを許可
	MotionType:変化モーション設定(BlockChangeMotionType_NOで変化モーション削除)
	MotionLengh:モーションの長さ
	Before:前に設置されていたブロック
戻り値
	TRUEで設置(削除)成功
*/
int Phase_GameMain::add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int Override, int OutScreen, BLOCK_TYPE *Before, int UseVirtualField) {
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;	//前のブロックを指定する
	BLOCK_TYPE before = BLOCK_TYPE_NO;	//消去前のブロック
	//画面外ブロックは設置不可
	if (brock_type == BLOCK_TYPE_NUM)	return FALSE;
	//ブロック無しブロックが指定された場合は削除処理を行う


	//ブロックを設置しようとしている位置の現在のブロックを取得する(捜査対象外は画面外ブロックになります)
	BLOCK_TYPE bt = getBlockColor(X, Y, TRUE, !OutScreen, UseVirtualField);
	if (Override) {
		//上書きが有効な場合
		if (bt == BLOCK_TYPE_NUM)	return FALSE;//画面外ブロックの時のみ失敗
	}
	else {
		//上書き無効の場合
		if (bt != BLOCK_TYPE_NO)	return FALSE;//ブロック無しと出ない場合は失敗
	}

	//現在のブロックを記録する
	before = getBlockColor(X, Y, TRUE, FALSE, UseVirtualField);

	if (UseVirtualField) {
		//設定されているモーションを削除する
		Virtualfield[X][Y].blockChangeMotion.Type = BlockChangeMotionType_NO;
		Virtualfield[X][Y].blockMoveMotion.Enable = FALSE;

		//ブロックの設置(削除)
		Virtualfield[X][Y].fall_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
		Virtualfield[X][Y].move_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
		Virtualfield[X][Y].color = brock_type;	//ブロックの置き換え
	}
	else {
		//設定されているモーションを削除する
		field[X][Y].blockChangeMotion.Type = BlockChangeMotionType_NO;
		field[X][Y].blockMoveMotion.Enable = FALSE;

		//ブロックの設置(削除)
		field[X][Y].fall_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
		field[X][Y].move_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
		field[X][Y].color = brock_type;	//ブロックの置き換え
	}


	if (brock_type == BLOCK_TYPE_NO) {
		//この場合はブロック削除なので
		if (UseVirtualField)	printLog_I(_T("仮想フィールドブロックの【削除】[%d][%d]"), X, Y);
		else					printLog_I(_T("フィールドブロックの【削除】[%d][%d]"), X, Y);
	}
	else {
		if (UseVirtualField)	printLog_I(_T("仮想フィールドブロックの【新規生成】[%d][%d](type=%d)"), X, Y, brock_type);
		else					printLog_I(_T("フィールドブロックの【新規生成】[%d][%d](type=%d)"), X, Y, brock_type);
	}


	if (Before != NULL)	*Before = before;	//前のブロックを指定する
	return TRUE;
}


//下からブロックがわいてくる
void Phase_GameMain::under_Block() {
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
			if (field[x][y].color == BLOCK_TYPE_BLACK) {//黒ブロックの時
				//確率でブロックのIDを書き換える
				int Val = (int)randomTable.getRand(0, 100);
				if (Val < 20)		field[x][y].color = BLOCK_TYPE_RED;		//赤色ブロック
				else if (Val < 40)	field[x][y].color = BLOCK_TYPE_BLUE;	//青色ブロック
				else if (Val < 60)	field[x][y].color = BLOCK_TYPE_YELLOW;	//黄色ブロック
				else if (Val < 80)	field[x][y].color = BLOCK_TYPE_GREEN;	//緑色ブロック
				else 				field[x][y].color = BLOCK_TYPE_PURPLE;	//紫色ブロック

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
			if (field[x][y].color == BLOCK_TYPE_BOM) {//爆弾ブロックの時
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
			if (field[x][y].color == BLOCK_TYPE_2BOM) {//爆弾ブロックの時
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
			if (field[x][y].color == BLOCK_TYPE_BOM_Color) {//爆弾ブロックの時
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
Phase_GameMain::BLOCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock, int InGame, int UseVirtualField) {

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

	return ((UseVirtualField) ? Virtualfield[X][Y].color : field[X][Y].color);

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
int Phase_GameMain::Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int MotionLengh, int Delay) {
	if (getBlockColor(X, Y, FALSE, FALSE) == BLOCK_TYPE_NO)	return FALSE;//ブロックがそもそも存在しない場合は何もしない
	BLOCK_TYPE bt = BLOCK_TYPE_NO;	//削除されたブロックの種類
	//ブロックの削除を行う
	int flag = add_FraldBlock(X, Y, BLOCK_TYPE_NO, TRUE, TRUE, &bt);

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
	if (!isSameColorBlock(type, getBlockColor(X, Y)))	return FALSE;//違う色のブロックの場合は削除しない

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
									Convert_Ingame_FromBlock(i, y, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
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
									Convert_Ingame_FromBlock(x, i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
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
									Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
								if (Block_Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Convert_Ingame_FromBlock(x - i, y + i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
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
									Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
								if (Block_Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//フライテキストの生成
									double X, Y;
									Convert_Ingame_FromBlock(x - i, y - i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
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
						Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+100"));
						score.addScore(0, 100);
						DelCount++;
					}

					//ついでに隣接する樹木ブロックも削除
					if (Block_Delete_Color(x, y - 1, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//上
					}
					if (Block_Delete_Color(x, y + 1, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//下
					}
					if (Block_Delete_Color(x - 1, y, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//左
					}
					if (Block_Delete_Color(x + 1, y, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x + 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
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

//SequenceCountで使用するマーカーテーブルを作成する(有効なエリア)(TRUEで仮想の面を使用する)
void Phase_GameMain::CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField) {
	if (deleteFlag == NULL)	return;



	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field_info *f = &(field[x][y]);
			if (UseVirtualField)	f = &(Virtualfield[x][y]);
			if (!(X <= x && x < X + W && Y <= y && y < Y + H) ||	//範囲外
				f->color == BLOCK_TYPE_NO ||
				f->color == BLOCK_TYPE_NUM ||
				f->color == BLOCK_TYPE_TREE ||
				f->color == BLOCK_TYPE_BLACK ||
				f->color == BLOCK_TYPE_RAINBOW ||
				f->color == BLOCK_TYPE_BOM ||
				f->color == BLOCK_TYPE_2BOM ||
				f->color == BLOCK_TYPE_BOM_Color) {		//除外ブロック
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
	BLOCK_TYPE bt = ((UseVirtualField) ? Virtualfield[x][y].color : field[x][y].color);	//ブロックの種類を記録する
	deleteFlag[x][y] = ID;	//探索済み(探索IDを設定する)
	(*Counter)++;

	int OnlyColor = TRUE;

	BLOCK_TYPE NextBlock = ((UseVirtualField) ? Virtualfield[x + 1][y].color : field[x + 1][y].color);
	if (x + 1 < BLOCK_WIDTHNUM	&& isSameColorBlock(NextBlock, bt, OnlyColor))		SequenceCount(x + 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y + 1].color : field[x][y + 1].color);
	if (y + 1 < BLOCK_HEIGHTNUM	&& isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x - 1][y].color : field[x - 1][y].color);
	if (x - 1 >= 0 && isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y - 1].color : field[x][y - 1].color);
	if (y - 1 >= 0 && isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//指定した2個のブロックが同色ブロックかどうかの取得(TRUEで同色)
int Phase_GameMain::isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int OnlyColorBlock) {
	if (OnlyColorBlock) {//簡略計算でないとき
		//色の概念の無いブロックの場合
		if (type1 == BLOCK_TYPE_NO)			return FALSE;
		if (type1 == BLOCK_TYPE_TREE)		return FALSE;
		if (type1 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type1 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type1 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type1 == BLOCK_TYPE_BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_2BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_BOM_Color)	return FALSE;
		if (type1 == BLOCK_TYPE_NUM)		return FALSE;

		if (type2 == BLOCK_TYPE_NO)			return FALSE;
		if (type2 == BLOCK_TYPE_TREE)		return FALSE;
		if (type2 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type2 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type2 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type2 == BLOCK_TYPE_BOM)		return FALSE;
		if (type2 == BLOCK_TYPE_2BOM)		return FALSE;
		if (type2 == BLOCK_TYPE_BOM_Color)	return FALSE;
		if (type2 == BLOCK_TYPE_NUM)		return FALSE;
	}

	//同色判定(同一ブロックの場合)
	if (type1 == type2)	return TRUE;

	//同色判定(基本ブロックに直して考えます)
	switch (type1) {
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY2:
		type1 = BLOCK_TYPE_RED;
		break;
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY2:
		type1 = BLOCK_TYPE_BLUE;
		break;
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY2:
		type1 = BLOCK_TYPE_YELLOW;
		break;
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY2:
		type1 = BLOCK_TYPE_GREEN;
		break;
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY2:
		type1 = BLOCK_TYPE_PURPLE;
		break;
	}
	switch (type2) {
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY2:
		type2 = BLOCK_TYPE_RED;
		break;
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY2:
		type2 = BLOCK_TYPE_BLUE;
		break;
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY2:
		type2 = BLOCK_TYPE_YELLOW;
		break;
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY2:
		type2 = BLOCK_TYPE_GREEN;
		break;
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY2:
		type2 = BLOCK_TYPE_PURPLE;
		break;
	}
	//同色判定
	if (type1 == type2)	return TRUE;

	return FALSE;
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

//フィールドのブロックに変化モーションを設定する(これ単体で使用して事故っても知りません)
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//ブロックが画面外の場合は処理をしない
	if (MotionLength <= 0)									return;	//長さが負の数の場合も処理をしない

	if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
		printLog_C(_T("ブロック変化モーションを上書きします"));
		field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;
	}

	field[x][y].blockChangeMotion.To = To;
	field[x][y].blockChangeMotion.From = From;
	field[x][y].blockChangeMotion.Length = MotionLength;
	field[x][y].blockChangeMotion.Count = -Delay;

	field[x][y].blockChangeMotion.Type = mtype;

	printLog_I(_T("ブロックに【変化モーション】を設定[%d][%d]"), x, y);
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
			if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
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

	if (Block_AllMovedata.Enable)	return;//すでにブロックが移動中の場合、無視する


	Block_AllMovedata.ToX = X;
	Block_AllMovedata.ToY = Y;
	Block_AllMovedata.FromX = 0;
	Block_AllMovedata.FromY = 0;
	Block_AllMovedata.a = 0.1;
	Block_AllMovedata.MaxSpeed = 2;
	Block_AllMovedata.Count = 0;

	Block_AllMovedata.Enable = TRUE;

	printLog_I(_T("ブロック全体移動が設定されました(%d,%d)"), X, Y);
}

//フィールド全体のブロックを指定した分だけ移動する(画面外に出てしまうブロックは消滅します)
void Phase_GameMain::Block_AllMove(int X, int Y) {
	//処理に無駄が多い…

	//一時変数
	field_info t[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//実際にブロックをすべて移動させる

	//左上移動
	if (X <= 0 && Y <= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					if (field[x][y].blockMoveMotion.Enable) {//移動モーションが有効な場合は移動モーションに補正をかける
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
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
					if (field[x][y].blockMoveMotion.Enable) {//移動モーションが有効な場合は移動モーションに補正をかける
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
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
					if (field[x][y].blockMoveMotion.Enable) {//移動モーションが有効な場合は移動モーションに補正をかける
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
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
					if (field[x][y].blockMoveMotion.Enable) {//移動モーションが有効な場合は移動モーションに補正をかける
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
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
	FallBlock_MoveX(X, FALSE);
	FallBlock_MoveY(Y, FALSE);

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
				add_FraldBlock(bl_X, bl_Y, bt, TRUE, TRUE, NULL, TRUE);
				int BlockFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
				//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
				CreateSequenceCountTable(BlockFlag, 0, 0, BLOCK_WIDTHNUM, BLOCK_HEIGHTNUM, TRUE);
				SequenceCount(bl_X, bl_Y, 0, BlockFlag, &Count, TRUE);
			} while (Count >= BLOCK_DELETE_LEN);

			add_FraldBlock(bl_X, bl_Y, bt, FALSE, TRUE);//本番の設置

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

	//普通は起きない
	if (isFallBlock_Enable()) {
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {
					int fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
					int fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
					BLOCK_TYPE fB = getBlockColor(fX, fY, TRUE);	//ブロックの種類取得
					if (fB != BLOCK_TYPE_NO) {
						printLog_I(_T("落下ブロックが既存ブロックと重なってしまってゲームオーバー"));
						return 2;	//落下ブロックの下の位置に通常ブロックがある
					}
				}
			}
		}
	}

	return 0;
}

//落下ブロックの待機列の作成
void Phase_GameMain::Create_Wait_Block() {

	//列を詰める(先頭は0)
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo) - 1; i++) {
		waitBlockinfo[i] = waitBlockinfo[i + 1];
	}



	//新規に作成する落下ブロックの配置パターンを決定する(0～3)
	const int Percent = (int)(randomTable.getRand(0, 100));
	int Pattern = 0;	//ブロックのパターン
	if (Percent < 24) {
		Pattern = 0;
	}
	else if (Percent < 48) {
		Pattern = 1;
	}
	else if (Percent < 72) {
		Pattern = 2;
	}
	else if (Percent < 96) {
		Pattern = 3;
	}
	else {
		Pattern = 4;
	}


	//5％の確率で爆弾を単体で落下させる
	if (randomTable.getRand(0, 1000) < 50) {
		Pattern = 4;
	}

	//ランダムに設置するブロックを2個決定する
	BLOCK_TYPE type1 = GetRandomBlockType_FALL();
	BLOCK_TYPE type2 = GetRandomBlockType_FALL();

	//最後尾待機ブロックの配置を初期化する
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[i][j] = BLOCK_TYPE_NO;
		}
	}


	//ブロックの特殊効果を設定する
	waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = TRUE;


	//先に決めたパターンよりブロックの配置を決定する(ついでにスポーン位置も)
	switch (Pattern) {
	case 0://縦で下側中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][0] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP + 1;
		//printLog_D(_T("縦で下側中心パターン"));
		break;
	case 1://縦で上側中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][2] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("縦で上側中心パターン"));
		break;
	case 2://横で左中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[2][1] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("横で左中心パターン"));
		break;
	case 3://横で右中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[0][1] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("横で右中心パターン"));
		break;
	case 4://同色爆弾の単体落下
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = BLOCK_TYPE_BOM_Color;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//無条件で回転不可
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = FALSE;
		break;
	default:
		printLog_E(_T("落下ブロック配置パターンが不明です"));
		break;
	}


	printLog_I(_T("ブロックの待機列を進めました"));
}

//ランダムでブロックの種類を返す(落下ブロック用)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::GetRandomBlockType_FALL() {
	int Rand = (int)randomTable.getRand(0, 100);

	//確率で戻り値を変えるようにする
	if (Rand < 17)	return BLOCK_TYPE_RED;		//赤
	if (Rand < 35)	return BLOCK_TYPE_BLUE;		//青
	if (Rand < 52)	return BLOCK_TYPE_YELLOW;	//黄
	if (Rand < 70)	return BLOCK_TYPE_GREEN;	//緑
	if (Rand < 88)	return BLOCK_TYPE_PURPLE;	//紫

	//ここから特殊ブロック↓
	if (Rand < 89)	return BLOCK_TYPE_RED_ARROW_X;		//赤(平行矢印)
	if (Rand < 91)	return BLOCK_TYPE_BLUE_ARROW_X;		//青(平行矢印)
	if (Rand < 93)	return BLOCK_TYPE_YELLOW_ARROW_X;	//黄(平行矢印)
	if (Rand < 95)	return BLOCK_TYPE_GREEN_ARROW_X;	//緑(平行矢印)
	if (Rand < 97)	return BLOCK_TYPE_PURPLE_ARROW_X;	//紫(平行矢印)
	return BLOCK_TYPE_RAINBOW;							//虹色のブロック(下のブロックと同じ色になる)
}

//ランダムでブロックの種類を返す(下から沸いてくるブロック用)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::GetRandomBlockType_UNDER() {
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
		phase_GameMain.PauseRequest(PauseMode_NO);
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