//ゲーム関係のメイン

static int gameWindow;	//ゲーム画面を描画するハンドル

static void GameMain_Key();

//初期化(描画処理)
void GameMain_Init_Draw() {
	//ゲーム画面の生成(後でシェーダを使いたいので2のn乗のサイズで作成します)
	if((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("ウィンドウ作成に失敗しました"));
}

//初期化(計算処理)
void GameMain_Init_Update() {

}

//描画
void GameMain_Draw() {

	//描画先をゲーム画面にする
	SetDrawScreen(gameWindow);

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawBox(0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, GetColor(0xb3, 0x65, 0xe5), TRUE);

	//デバッグ
#ifdef DEBUG_GAMEMAIN
	//縦横70間隔で線を描画する
	for (int i = 1; i < GAMEWINDOW_WIDTH / 50; i++) {
		DrawLine(i * 50, 0, i * 50, GAMEWINDOW_HEIGHT, GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = 1; i < GAMEWINDOW_HEIGHT / 50; i++) {
		DrawLine(0, i * 50, GAMEWINDOW_WIDTH, i * 50, GetColor(0xff, 0xbf, 0x74));
	}
#endif // DEBUG_GAMEMAIN



	//描画先をバックスクリーンにする
	SetDrawScreen(DX_SCREEN_BACK);

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0x5b, 0x8e, 0xda), TRUE);


	//ゲーム画面を描画する
	DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, 0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);

	//デバッグ
#ifdef DEBUG_GAMEMAIN
	//マス目の番号を描画
	for (int i = 0; i < GAMEWINDOW_WIDTH / 50; i++) {
		int Width = -GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
		Width += 50;
		Width /= 2;
		DrawFormatStringToHandle(GAMEWINDOW_PADDINGX + i*50 + Width, 30, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
	}
	for (int i = 0; i < GAMEWINDOW_HEIGHT / 50; i++) {
		DrawFormatStringToHandle(20, GAMEWINDOW_PADDINGY + i * 50 + 15, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%2d"), i);
	}
#endif // DEBUG_GAMEMAIN

}

//計算処理
void GameMain_Update() {

	GameMain_Key();	//キー処理

}

//キー処理
static void GameMain_Key() {

}

//終了処理(描画処理)
void GameMain_Finalize_Draw() {

}

//終了処理(計算処理)
void GameMain_Finalize_Update() {

}