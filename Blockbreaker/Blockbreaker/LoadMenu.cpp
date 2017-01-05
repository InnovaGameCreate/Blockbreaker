//ロード画面関係
#include "MainFunc.h"

static int LoadScreen;//ロード画面
static int LoadScreen2;//ロード画面


//初期化
void LoadMenu_Initialize() {
	//ロード画面のロード
	LoadScreen = LoadGraph(_T("Data/LoadMenu/LoadBack.png"));
	if (LoadScreen == -1) {
		printLog_E(_T("画像ロード失敗(Data/LoadMenu/LoadBack.png)"));
	}
	//ロード画面のロード2
	LoadScreen2 = LoadGraph(_T("Data/LoadMenu/LoadBack2.png"));
	if (LoadScreen2 == -1) {
		printLog_E(_T("画像ロード失敗(Data/LoadMenu/LoadBack2.png)"));
	}
	printLog_I(_T("ロード画面の初期化に成功"));
}

//ロード画面の表示
void LoadMenu_Draw(int count) {
	//ロード画面の描画
	DrawGraph(0, 0, LoadScreen, 0);
	TCHAR str[100];
	switch ((count % 180)/60) {
	case 0:
		_stprintf_s(str, _T("Now Loading."));
		break;
	case 1:
		_stprintf_s(str, _T("Now Loading.."));
		break;
	default:
		_stprintf_s(str, _T("Now Loading..."));
		break;
	}

	DrawStringToHandle(750 + 4, 870 + 4, str, GetColor(30, 30, 30), Font_getHandle(FONTTYPE_GenJyuuGothicLHeavy_Edge70));
	DrawStringToHandle(750, 870, str, GetColor(0xcb, 0xff, 0x8e), Font_getHandle(FONTTYPE_GenJyuuGothicLHeavy_Edge70));
}

//ロード画面の表示(最初の起動時用)
void LoadMenu_Draw2() {
	//ロード画面の描画
	DrawGraph(0, 0, LoadScreen2, 0);
	ScreenFlip();		//裏画面を表画面に反映
}