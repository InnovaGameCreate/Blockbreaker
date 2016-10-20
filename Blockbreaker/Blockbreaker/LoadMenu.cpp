//ロード画面関係

static int LoadScreen;//ロード画面
static int LoadScreen2;//ロード画面

//初期化
void LoadMenu_Initialize() {
	//ロード画面のロード
	LoadScreen = LoadGraph(_T("Data/LoadMenu/LoadBack.png"));
	if (LoadScreen == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("画像ロード失敗(Data/LoadMenu/LoadBack.png)"));
	}
	//ロード画面のロード2
	LoadScreen2 = LoadGraph(_T("Data/LoadMenu/LoadBack2.png"));
	if (LoadScreen2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("画像ロード失敗(Data/LoadMenu/LoadBack2.png)"));
	}
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ロード画面の初期化に成功"));
}

//ロード画面の表示
void LoadMenu_Draw() {
	//ロード画面の描画
	DrawGraph(0, 0, LoadScreen, 0);

	DrawStringToHandle(760 + 4, 870 + 4, _T("Now Loading…"), GetColor(30, 30, 30), Font_getHandle(FONTTYPE_GenJyuuGothicLHeavy_Edge70));
	DrawStringToHandle(760, 870, _T("Now Loading…"), GetColor(0xcb, 0xff, 0x8e), Font_getHandle(FONTTYPE_GenJyuuGothicLHeavy_Edge70));
	ScreenFlip();		//裏画面を表画面に反映
}

//ロード画面の表示(最初の起動時用)
void LoadMenu_Draw2() {
	//ロード画面の描画
	DrawGraph(0, 0, LoadScreen2, 0);
	ScreenFlip();		//裏画面を表画面に反映
}