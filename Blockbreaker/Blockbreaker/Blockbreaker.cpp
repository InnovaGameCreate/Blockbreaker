//メイン関数
#include "MainFunc.h"

//グローバル変数の定義
Phase_Default phase_Default;
Phase_GameMain phase_GameMain;
Phase_TopMenu phase_TopMenu;

//変数
static unsigned int stateKey[256];				//キーボードのキー
static unsigned int stateKeyJoy[32];			//ゲームパッド(int型より32びっと)
static unsigned int stateKeyBind[KEYBIND_NUM];	//キーバインドによるキー入力情報
static FpsController fpsController_Update(UPDATEFPS);	//FPSコントローラー(計算スレッド)
static FpsController fpsController_Draw(DRAWFPS);		//FPSコントローラー(描画スレッド)

static int Flag_NonActivePauseRequest;			//非アクティブになった際にポーズを要求するフラグ

//操作関連
static KeyBind KeyBindSetting;			//キーバインド設定
static KeyBindjoy JoyKeyBindSetting;	//キーバインド設定(アナログパッド)
static int USEGamePad;					//使用するゲームパッドの種類(0使用しない)
static ANALOGSTICKMODE Analogstickmode;	//アナログスティックの操作モード

//フェーズ関連
static FAZE faze = FAZE_Nothing;				//現在のフェーズ(Update)
static FAZE ChangefazeRequest = FAZE_Nothing;	//フェーズ変更リクエスト(DrawからUpdate)
static int ChangefazeRequest_Draw = -1;			//フェーズ変更リクエスト(UpdateからDraw)
static FAZE faze_draw = FAZE_Nothing;			//現在のフェーズ(Draw)
static int faze_Wait_Loading = FALSE;			//描画スレットのロード待ちを行うかどうか
static int faze_arg = 0;						//引数

//描画関連
static int FLAG_PauseDraw = 0;			//描画のスキップ
static int FLAG_PauseDrawrequest = 0;	//描画のスキップのリクエスト
static int FLAG_ClearScreen = 1;		//毎フレーム背景を消去する(ゲーム画面はここの設定にかかわらず常時消去されます)
static int Drawing_interval = 1;		//描画間隔

static int EndFlag = 0;				//プログラム終了フラグ

static int Flag_MultiThread = TRUE;	//マルチスレッドで動作するかどうか(FALSEシングル)

static int Flag_MouseCursor = TRUE;	//マウスカーソルを表示するかどうか(FALSEで表示しない)


//プロトタイプ宣言(ファイル内のみ有効な関数)
static void Draw();
static void Update();
static void Changefaze_Draw();
static unsigned __stdcall Thread_Update(void* args);
static void UpdateLoop();
static int Thread_Draw(void* args);
static int ActiveStateChange(int ActiveState, void *UserData);
static void RestoreGraphCallback();
static int gpUpdateKey();
static void gpUpdateKeyBind();
static void setWindowModeVirtualFullScreen();

static void Init_AfterDXlibInit();

//フェーズごとのクラスのインスタンスへのポインタ
static PhaseController *phaseController[FAZE_NUM];

//メイン関数(ここから始まります)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Base_BB_Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);


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
