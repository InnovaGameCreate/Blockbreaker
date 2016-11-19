//メイン関数
#include "MainFunc.h"

//グローバル変数の定義
Phase_Default phase_Default;
Phase_GameMain phase_GameMain;
Phase_TopMenu phase_TopMenu;

static void Init_AfterDXlibInit();

//メイン関数(ここから始まります)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Base_BB_Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, GAMEVERSION);

	//コンパイル時刻などを出力
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("最終コンパイル時刻は%s %sです"), _T(__DATE__), _T(__TIME__));
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("コンパイルに使用したDXライブラリのバージョンは%sです"), DXLIB_VERSION_STR_T);
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("開発に使用しているDXライブラリのバージョンは%sです"), _T("3.16f"));

	Base_BB_setFunc_InitAfterDXlibInit(Init_AfterDXlibInit);	//DXライブラリ初期化後の初期化処理関数の登録
	//フェーズの定義
	Base_BB_setFaze(FAZE_TopMenu, &phase_TopMenu);
	Base_BB_setFaze(FAZE_GameMain, &phase_GameMain);

	Base_BB_MainLoop();	//メインループ(無限)

	return 0;
}

#pragma region いじらなくて良い関数群

//DXライブラリ初期化後に行う初期化処理
static void Init_AfterDXlibInit() {
	//ここで各モジュールの初期化処理を行う
	SoundEffect_init();				//効果音関係の初期化
	Font_init();					//フォント関係の初期化
	ShaderBackGround_Initialize();	//シェーダ関連初期化
}

#pragma endregion
