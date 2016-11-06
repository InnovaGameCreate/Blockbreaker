#include "MainFunc.h"



Phase_GameMain::Phase_GameMain() {
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
	if ((Tex_BlockFireEffect = LoadGraph(_T("Data/Blocks/Block_FireEffect.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_FireEffect.png)"));
	if ((Tex_BlockFireEffect2 = LoadGraph(_T("Data/Blocks/Block_FireEffect2.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_FireEffect2.png)"));

	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/colorbom.png)"));


	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

	//ポーズメニューの項目を作成
	pauseMenu.addItem(_T("再開"), 3, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("やり直す"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("ゲーム終了"), 5, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.setScrolltype(1);
	pauseMenu.sethaba(50);
	pauseMenu.setCenteringMode(0);
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
	Count_Pause = 0;
	Count_Turn = 0;
	//落下中ブロックの削除
	Delete_FallBlock();
	score.init();//スコアの初期化

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
	DrawBox(BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE,
		GAMEWINDOW_WIDTH + BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_HEIGHT + BLOCK_PADDINGUP*BLOCK_SIZE,
		GetColor(0xb3, 0x65, 0xe5), TRUE);

	//フィールドブロックの描画
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//描画先の座標を取得
			double X, Y;
			X = field[x][y].DrawPlaceX;
			Y = field[x][y].DrawPlaceY;
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
				ShaderBackGround_DeleteBlock(X, Y, field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length
					, getBlockTexture(field[x][y].blockChangeMotion.From), Tex_BlockFireEffect, Tex_BlockFireEffect2);
				break;
			case BlockChangeMotionType_SMALL:
				//小さくなる
				DrawBlock(X, Y, field[x][y].blockChangeMotion.From, 1 - (field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length));
				break;
			}
		}
	}

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
	//落下中ブロックの描画
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0, 0, &X, &Y);

				//全体ずらしの分描画座標をずらす
				if (Block_AllMovedata.Enable) {//全体ずらすが有効な場合
					X += Field_PaddingX;
					Y += Field_PaddingY;
				}

				if (Y < (y + BLOCK_PADDINGUP)*BLOCK_SIZE) {
					Y = (y + BLOCK_PADDINGUP)*BLOCK_SIZE;
				}

				DrawBlock(X, Y, fallBlockInfo.fallblock.BlockID[x][y]);
			}
		}
	}

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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(150, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (Count_Pause % 120 <= 80)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("GAME OVER"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);

		//選択肢の項目の描画
		pauseMenu.Draw();
		break;
	}
}

//ブロックを描画する(インゲーム座標)
void Phase_GameMain::DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type, double Scale) {

	if (type == BLOCK_TYPE_NO)	return;

	//中心座標に変換
	int X = (int)(CenterX + BLOCK_SIZE / 2.);
	int Y = (int)(CenterY + BLOCK_SIZE / 2.);

	DrawRectRotaGraphFast2(X, Y, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, (float)Scale, 0, getBlockTexture(type), TRUE, FALSE);

	//DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, getBlockTexture(type), TRUE);
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
			Create_FallBlock(NULL);//前回の落下ブロック終了から一定時間後に落下ブロックの再出現
		}
		//落下ブロックの落下処理
		if (Update_FallBlock()) {
			//落下完了後は計算を行う
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
	{

		if (Count_Turn % 3 == 0) {
			under_Block();
		}
		else {
			BLOCK_TYPE bt = BLOCK_TYPE_RAINBOW;
			int swi = (int)(randomTable.getRand(0, 219) / 10.);
			switch (swi) {
			case 0:		bt = BLOCK_TYPE_RED_ARROW_X;		break;
			case 1:		bt = BLOCK_TYPE_RED_ARROW_Y;		break;
			case 2:		bt = BLOCK_TYPE_RED_ARROW_XY;		break;
			case 3:		bt = BLOCK_TYPE_RED_ARROW_XY2;		break;
			case 4:		bt = BLOCK_TYPE_BLUE_ARROW_X;		break;
			case 5:		bt = BLOCK_TYPE_BLUE_ARROW_Y;		break;
			case 6:		bt = BLOCK_TYPE_BLUE_ARROW_XY;		break;
			case 7:		bt = BLOCK_TYPE_BLUE_ARROW_XY2;		break;
			case 8:		bt = BLOCK_TYPE_YELLOW_ARROW_X;		break;
			case 9:		bt = BLOCK_TYPE_YELLOW_ARROW_Y;		break;
			case 10:	bt = BLOCK_TYPE_YELLOW_ARROW_XY;	break;
			case 11:	bt = BLOCK_TYPE_YELLOW_ARROW_XY2;	break;
			case 12:	bt = BLOCK_TYPE_GREEN_ARROW_X;		break;
			case 13:	bt = BLOCK_TYPE_GREEN_ARROW_Y;		break;
			case 14:	bt = BLOCK_TYPE_GREEN_ARROW_XY;		break;
			case 15:	bt = BLOCK_TYPE_GREEN_ARROW_XY2;	break;
			case 16:	bt = BLOCK_TYPE_PURPLE_ARROW_X;		break;
			case 17:	bt = BLOCK_TYPE_PURPLE_ARROW_Y;		break;
			case 18:	bt = BLOCK_TYPE_PURPLE_ARROW_XY;	break;
			case 19:	bt = BLOCK_TYPE_PURPLE_ARROW_XY2;	break;
			case 20:	bt = BLOCK_TYPE_TREE;				break;
			case 21:	bt = BLOCK_TYPE_BOM;				break;
			}

			//ランダムで一番上の段に木ブロックを設置する
			for (int i = 0; add_FraldBlock((int)randomTable.getRand(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT), 1, bt) == FALSE && i < 10; i++);
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
		if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 5;	//高速落下モードの場合カウントをさらに入れる
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

		ChainCount = 0;	//連鎖カウントをリセットする
		gameCycleFirstCallFlag = FALSE;	//ゲームサイクルが変更された時のフラグをFALSEに設定する

		////ゲームオーバーの判定を行う
		//if (JudgeGameOver() != 0) {
		//	PauseRequest(PauseMode_GameOver);	//ポーズリクエスト
		//}
		//画面外ブロックを削除する
		Block_Delete_OutScreen();

		if (!gameCycleFirstCallFlag) {
			Loop_No = 1;
			printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
		}
		break;
	case 1://重力計算
		Block_Gravity();//重力計算を行う
		Loop_No = 2;
		printLog_I(_T("移動モーションへ移行【Loop_No=%d】"), Loop_No);
		break;
	case 2://移動モーション
		if (Update_MoveMotion() == FALSE) {
			//移動がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 3;
				printLog_I(_T("ブロックの特殊効果へ移行【Loop_No=%d】"), Loop_No);
			}
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
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 5;
				printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
			}
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
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 7;
				printLog_I(_T("ブロックの消去判定へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 7://ブロックの消去判定
		if (Block_Delete() > 0) {
			//ブロックの消去判定が入れば
			ChainCount++;	//連鎖カウントを加算する
			//連鎖カウントを描画する(フライテキスト)
			if (ChainCount >= 2) flyText.addFlyText(GAMEWINDOW_WIDTH / 2., GAMEWINDOW_HEIGHT / 2., 60, FONTTYPE_GenJyuuGothicLHeavy_Edge60, GetColor(200, 200, 0), _T("%d連鎖！！"), ChainCount);


			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Loop_No = 8;
			printLog_I(_T("変化モーションへ移行【Loop_No=%d】"), Loop_No);
		}
		else {
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 11;
				printLog_I(_T("終了処理へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 8://変化モーション
		if (Update_ChangeMotion() == FALSE) {
			//変化がなかった場合
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 9;
				printLog_I(_T("重力計算へ移行【Loop_No=%d】"), Loop_No);
			}
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
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
			}
			else {
				Loop_No = 7;
				printLog_I(_T("ブロックの消去判定へ移行【Loop_No=%d】"), Loop_No);
			}
		}
		break;
	case 11://終了
		if (gameCycleFirstCallFlag) {
			Loop_No = 0;
			printLog_I(_T("初期化へ移行【Loop_No=%d】"), Loop_No);
		}
		else {
			//死亡判定を行う
			if (JudgeGameOver() != 0) {
				PauseRequest(PauseMode_GameOver);
			}
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

	//ステージ経過時間のカウントアップ(通常プレイ時に加算する)
	if (getPauseMode() == PauseMode_NO && Block_AllMovedata.Enable == FALSE)	Count_PlayTime++;

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
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, 0, 0, &X, &Y);	//移動元座標の計算
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//現在の移動距離の計算
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//上の計算結果より、描画座標の計算
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//移動モーション無し
				Convert_Ingame_FromBlock(x, y, 0, 0, &X, &Y);
			}

			//全体ずらしの分描画座標をずらす
			X += Field_PaddingX;
			Y += Field_PaddingY;

			//ゲームオーバーが近い場合は左右に揺らす
			if (getBlockColor(x, GAMEOVER_BORDER + 2) != BLOCK_TYPE_NO) {
				X += getGraph_Sin(Count_PlayTime * 30, 3, 0);
				X += randomTable.getRand(-2, 2);
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
	DeleteGraph(haikei);

	DeleteMask(Tex_BlockFireEffect2);

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

	fallBlockInfo.fallblock.BlockID[0][2] = BLOCK_TYPE_NO;
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
	fallBlockInfo.Flag_Rotate = TRUE;

	//有効
	fallBlockInfo.Enable = TRUE;

	//if (JudgeGameOver() != 0) {
	//	PauseRequest(PauseMode_GameOver);
	//}

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
int Phase_GameMain::FallBlock_MoveX(int MoveVal, int CollisionFieldBlock) {
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

	//ずらしの反映
	fallBlockInfo.PlaceX += MoveVal;


	////回転が入った場合は死亡判定をする
	//if (MoveVal != 0) {
	//	if (JudgeGameOver() != 0) {
	//		PauseRequest(PauseMode_GameOver);//ゲームオーバーにする
	//	}
	//}

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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
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

	////移動が入った場合は死亡判定をする
	//if (MoveVal != 0) {
	//	if (JudgeGameOver() != 0) {
	//		PauseRequest(PauseMode_GameOver);//ゲームオーバーにする
	//	}
	//}


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

	////回転が入った場合は死亡判定をする
	//if (RotaVal != 0) {
	//	if (JudgeGameOver() != 0) {
	//		PauseRequest(PauseMode_GameOver);//ゲームオーバーにする
	//	}
	//}

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
int Phase_GameMain::add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int Override, int OutScreen, BlockChangeMotionType MotionType, int MotionLengh, BLOCK_TYPE *Before) {
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;	//前のブロックを指定する
	BLOCK_TYPE before = BLOCK_TYPE_NO;	//消去前のブロック
	//画面外ブロックは設置不可
	if (brock_type == BLOCK_TYPE_NUM)	return FALSE;
	//ブロック無しブロックが指定された場合は削除処理を行う


	//ブロックを設置しようとしている位置の現在のブロックを取得する(捜査対象外は画面外ブロックになります)
	BLOCK_TYPE bt = getBlockColor(X, Y, TRUE, !OutScreen);
	if (Override) {
		//上書きが有効な場合
		if (bt == BLOCK_TYPE_NUM)	return FALSE;//画面外ブロックの時のみ失敗
	}
	else {
		//上書き無効の場合
		if (bt != BLOCK_TYPE_NO)	return FALSE;//ブロック無しと出ない場合は失敗
	}

	//現在のブロックを記録する
	before = field[X][Y].color;

	//モーションの設定
	switch (MotionType) {
	case Phase_GameMain::BlockChangeMotionType_NO:
		//モーションの初期化
		field[X][Y].blockChangeMotion.Type = BlockChangeMotionType_NO;
		break;
	case Phase_GameMain::BlockChangeMotionType_NOMAL:
		Block_SetChangeMotion_NOMAL(X, Y, brock_type, MotionLengh);	//削除時のみは設定不可(内部処理)
		break;
	case Phase_GameMain::BlockChangeMotionType_EXPLOSION:
		if (brock_type == BLOCK_TYPE_NO) Block_SetChangeMotion_EXPLOSION(X, Y, MotionLengh);	//削除時のみ設定可能
		break;
	case Phase_GameMain::BlockChangeMotionType_SMALL:
		if (brock_type == BLOCK_TYPE_NO) Block_SetChangeMotion_SMALL(X, Y, MotionLengh);	//削除時のみ設定可能
		break;
	}
	field[X][Y].blockMoveMotion.Enable = FALSE;

	//ブロックの設置(削除)
	field[X][Y].fall_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
	field[X][Y].move_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
	field[X][Y].color = brock_type;	//ブロックの置き換え


	if (brock_type == BLOCK_TYPE_NO) {
		//この場合はブロック削除なので
		printLog_I(_T("フィールドブロックの【削除】[%d][%d]"), X, Y);
	}
	else {
		printLog_I(_T("フィールドブロックの【新規生成】[%d][%d](type=%d)"), X, Y, brock_type);
	}


	if (Before != NULL)	*Before = before;	//前のブロックを指定する
	return TRUE;
}


//下からブロックがわいてくる
void Phase_GameMain::under_Block() {
	const int BLOCKSPOWN_Y = BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;//ブロックの出現する位置


	for (int i = BLOCK_PADDINGLEFT; BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT > i; i++) {
		BLOCK_TYPE bt = BLOCK_TYPE_RAINBOW;


		BLOCK_TYPE bl = getBlockColor(i - 1, BLOCKSPOWN_Y, FALSE, FALSE);//左側のブロック
		BLOCK_TYPE bu = getBlockColor(i, BLOCKSPOWN_Y - 1, FALSE, FALSE);//上側のブロック

		do {
			int swi = (int)(randomTable.getRand(0, 259) / 10.);
			switch (swi) {
			case 0:		bt = BLOCK_TYPE_RED_ARROW_X;		break;
			case 1:		bt = BLOCK_TYPE_RED_ARROW_Y;		break;
			case 2:		bt = BLOCK_TYPE_RED_ARROW_XY;		break;
			case 3:		bt = BLOCK_TYPE_RED_ARROW_XY2;		break;
			case 4:		bt = BLOCK_TYPE_BLUE_ARROW_X;		break;
			case 5:		bt = BLOCK_TYPE_BLUE_ARROW_Y;		break;
			case 6:		bt = BLOCK_TYPE_BLUE_ARROW_XY;		break;
			case 7:		bt = BLOCK_TYPE_BLUE_ARROW_XY2;		break;
			case 8:		bt = BLOCK_TYPE_YELLOW_ARROW_X;		break;
			case 9:		bt = BLOCK_TYPE_YELLOW_ARROW_Y;		break;
			case 10:	bt = BLOCK_TYPE_YELLOW_ARROW_XY;	break;
			case 11:	bt = BLOCK_TYPE_YELLOW_ARROW_XY2;	break;
			case 12:	bt = BLOCK_TYPE_GREEN_ARROW_X;		break;
			case 13:	bt = BLOCK_TYPE_GREEN_ARROW_Y;		break;
			case 14:	bt = BLOCK_TYPE_GREEN_ARROW_XY;		break;
			case 15:	bt = BLOCK_TYPE_GREEN_ARROW_XY2;	break;
			case 16:	bt = BLOCK_TYPE_PURPLE_ARROW_X;		break;
			case 17:	bt = BLOCK_TYPE_PURPLE_ARROW_Y;		break;
			case 18:	bt = BLOCK_TYPE_PURPLE_ARROW_XY;	break;
			case 19:	bt = BLOCK_TYPE_PURPLE_ARROW_XY2;	break;
			case 20:	bt = BLOCK_TYPE_TREE;				break;
			case 21:	bt = BLOCK_TYPE_RED;				break;
			case 22:	bt = BLOCK_TYPE_BLUE;				break;
			case 23:	bt = BLOCK_TYPE_YELLOW;				break;
			case 24:	bt = BLOCK_TYPE_GREEN;				break;
			case 25:	bt = BLOCK_TYPE_PURPLE;				break;
			}
		} while (isSameColorBlock(bt, bl) || isSameColorBlock(bt, bu));



		add_FraldBlock(i, BLOCKSPOWN_Y, bt, FALSE, TRUE);
	}

	Block_AllMoveRequest(0, -1);	//ブロック全体を移動
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
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_BLACK, 20);
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
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_RAINBOW, 20);


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
					if (Block_Delete_Direct(x + 1, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 2, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 2, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 2, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 2, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}


				if (getBlockColor(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y - 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y - 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y + 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y + 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);

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
int Phase_GameMain::Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int MotionLengh) {

	if (getBlockColor(X, Y, FALSE, FALSE) == BLOCK_TYPE_NO)	return FALSE;//ブロックがそもそも存在しない場合は何もしない

	//ブロックの削除を行う
	int flag = add_FraldBlock(X, Y, BLOCK_TYPE_NO, TRUE, TRUE, PlayMotion, MotionLengh);

	if (flag) {
		//ブロックが削除された
		if (PlayMotion == BlockChangeMotionType_EXPLOSION) {
			Block_SetChangeMotion_EXPLOSION(X, Y, MotionLengh);	//モーションの生成
		}
		else if (PlayMotion == BlockChangeMotionType_SMALL) {
			Block_SetChangeMotion_SMALL(X, Y, MotionLengh);	//モーションの生成
		}
	}

	return ((flag) ? TRUE : FALSE);
}

//指定した座標が指定したブロックだった場合に削除(削除されたらTRUE)
int Phase_GameMain::Block_Delete_Type(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion, int MotionLengh) {
	if (getBlockColor(X, Y) != type)	return FALSE;//違うブロックの場合は削除しない

	return Block_Delete_Direct(X, Y, PlayMotion, MotionLengh);
}

//連続するフィールドブロックを削除する(ついでに消去によって発動する効果も発動する)(消去したブロックの数)
int Phase_GameMain::Block_Delete() {
	//画面内の存在するブロックのみで計算する

	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (x < BLOCK_PADDINGLEFT || BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT - 1 < x ||	//画面外
				y < BLOCK_PADDINGUP || BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - 1 < y ||	//画面外
				field[x][y].color == BLOCK_TYPE_NO ||
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
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
				if (Counter[DeleteFlag[x][y]] >= BLOCK_DELETE_LEN) {
					//水平の矢印の場合
					if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_X ||
						old[x][y] == BLOCK_TYPE_GREEN_ARROW_X ||
						old[x][y] == BLOCK_TYPE_PURPLE_ARROW_X ||
						old[x][y] == BLOCK_TYPE_RED_ARROW_X ||
						old[x][y] == BLOCK_TYPE_YELLOW_ARROW_X) {
						//左端から右端までの一列を一括消去
						for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
							if (Block_Delete_Direct(i, y, BlockChangeMotionType_EXPLOSION, 40)) {
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
							if (Block_Delete_Direct(x, i, BlockChangeMotionType_EXPLOSION, 40)) {
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
							if (Block_Delete_Direct(x + i, y - i, BlockChangeMotionType_EXPLOSION, 40)) {
								//フライテキストの生成
								double X, Y;
								Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
								flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
								score.addScore(0, 50);
								DelCount++;
							}
							if (Block_Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, 40)) {
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
							if (Block_Delete_Direct(x + i, y + i, BlockChangeMotionType_EXPLOSION, 40)) {
								//フライテキストの生成
								double X, Y;
								Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
								flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
								score.addScore(0, 50);
								DelCount++;
							}
							if (Block_Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, 40)) {
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

	//隣接しているブロックを削除する
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
				if (Counter[DeleteFlag[x][y]] >= BLOCK_DELETE_LEN) {
					//削除
					if (Block_Delete_Direct(x, y, BlockChangeMotionType_SMALL, 15)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+100"));
						score.addScore(0, 100);
						DelCount++;
					}

					//ついでに隣接する樹木ブロックも削除
					if (Block_Delete_Type(x, y - 1, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//上
					}
					if (Block_Delete_Type(x, y + 1, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//下
					}
					if (Block_Delete_Type(x - 1, y, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
						//フライテキストの生成
						double X, Y;
						Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//左
					}
					if (Block_Delete_Type(x + 1, y, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
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
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter) {
	if (deleteFlag[x][y] != -1)	return;		//未探索ブロックじゃない場合
	BLOCK_TYPE bt = field[x][y].color;      //ブロックの種類を記録する
	deleteFlag[x][y] = ID;					//探索済み(探索IDを設定する)
	(*Counter)++;

	if (x + 1 < BLOCK_WIDTHNUM	&& isSameColorBlock(field[x + 1][y].color, bt, TRUE))	SequenceCount(x + 1, y, ID, deleteFlag, Counter);
	if (y + 1 < BLOCK_HEIGHTNUM	&& isSameColorBlock(field[x][y + 1].color, bt, TRUE))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);
	if (x - 1 >= 0 && isSameColorBlock(field[x - 1][y].color, bt, TRUE))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);
	if (y - 1 >= 0 && isSameColorBlock(field[x][y - 1].color, bt, TRUE))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//指定した2個のブロックが同色ブロックかどうかの取得(TRUEで同色)
int Phase_GameMain::isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int FirstFlag) {
	if (!FirstFlag) {//簡略計算でないとき
		//色の概念の無いブロックの場合
		if (type1 == BLOCK_TYPE_NO)			return FALSE;
		if (type1 == BLOCK_TYPE_TREE)		return FALSE;
		if (type1 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type1 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type1 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type1 == BLOCK_TYPE_BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_NUM)		return FALSE;
		if (type2 == BLOCK_TYPE_NO)			return FALSE;
		if (type2 == BLOCK_TYPE_TREE)		return FALSE;
		if (type2 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type2 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type2 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type2 == BLOCK_TYPE_BOM)		return FALSE;
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
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//ブロックが画面外の場合は処理をしない
	if (MotionLength <= 0)									return;	//長さが負の数の場合も処理をしない

	if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
		printLog_C(_T("ブロック変化モーションを上書きします"));
		field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;
	}

	field[x][y].blockChangeMotion.To = To;
	field[x][y].blockChangeMotion.From = From;
	field[x][y].blockChangeMotion.Length = MotionLength;
	field[x][y].blockChangeMotion.Count = 0;

	field[x][y].blockChangeMotion.Type = mtype;

	printLog_I(_T("ブロックに【変化モーション】を設定[%d][%d]"), x, y);
}

//フィールドのブロックに変化モーション(通常)を設定する
void Phase_GameMain::Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == To)				return;		//変化先が同じ場合は処理をしない
	if (To == BLOCK_TYPE_NO)	return;		//変化先がブロック無しの場合は処理をしない(正しく描画出来ないため)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, From, To, MotionLength);
}

//フィールドのブロックに変化モーション(通常)を設定する(変化元指定)
void Phase_GameMain::Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength) {

	BLOCK_TYPE To = getBlockColor(x, y, FALSE, FALSE);
	if (from == To)				return;		//変化先が同じ場合は処理をしない
	if (To == BLOCK_TYPE_NO)	return;		//変化先がブロック無しの場合は処理をしない(正しく描画出来ないため)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, from, To, MotionLength);
}


//フィールドのブロックに変化モーション(爆発)を設定する
void Phase_GameMain::Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == BLOCK_TYPE_NO)	return;//ブロックが存在しない場合は無視

	Block_SetChangeMotion(x, y, BlockChangeMotionType_EXPLOSION, From, From, MotionLength);
}

//フィールドのブロックに変化モーション(小さくなって消える)を設定する
void Phase_GameMain::Block_SetChangeMotion_SMALL(int x, int y, int MotionLength) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == BLOCK_TYPE_NO)	return;//ブロックが存在しない場合は無視

	Block_SetChangeMotion(x, y, BlockChangeMotionType_SMALL, From, From, MotionLength);
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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {
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
		ExitGameRequest();
		break;
	default:
		printLog_C(_T("定義されていない選択項目が選択されたようです(%d)"), No);
		break;
	}
}