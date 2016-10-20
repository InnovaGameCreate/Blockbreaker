//メイン関数

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
static int gpUpdateKey();
static void gpUpdateKeyBind();
static void setWindowModeVirtualFullScreen();


//メイン関数(ここから始まります)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	_tsetlocale(LC_ALL, _T(""));//ロケールの設定

#ifdef _DEBUG
	::AllocConsole();               // コマンドプロンプトが表示される
	FILE *fp;
	_tfreopen_s(&fp, _T("CON"), _T("r"), stdin);     // 標準入力の割り当て
	_tfreopen_s(&fp, _T("CON"), _T("w"), stdout);    // 標準出力の割り当て
#endif // _DEBUG

	SetOutApplicationLogValidFlag(FALSE);				//DXライブラリのログ出力を行わない
	Log_Initialize();									//ログ関連の初期化(一番最初に実行してください)
	Log_SetThreadID(THREAD_Draw, GetCurrentThreadId());	//描画スレッドのIDを通知
	setKeybind();										//キーバインド設定を初期値にする
	setUSEGAMEPAD();									//使用するゲームパッドの設定を初期値にする
	SetAnalogueStickMode();								//アナログスティックの操作モードを初期値にする


	//コンパイル時刻などを出力
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("最終コンパイル時刻は%s %sです"), _T(__DATE__), _T(__TIME__));
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("コンパイルに使用したDXライブラリのバージョンは%sです"), DXLIB_VERSION_STR_T);
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("開発に使用しているDXライブラリのバージョンは%sです"), _T("3.16f"));


	Flag_NonActivePauseRequest = FALSE;

	setClearScreen(0);

	StartDialog_Initialize(hInstance);	//起動設定画面の初期化
	StartDialog_Show();					//起動設定画面の表示


	//キー入力情報の初期化
	for (int i = 0; i < ARRAY_LENGTH(stateKey); i++) {
		stateKey[i] = 0;
	}
	for (int i = 0; i < ARRAY_LENGTH(stateKeyBind); i++) {
		stateKeyBind[i] = 0;
	}
	for (int i = 0; i < ARRAY_LENGTH(stateKeyJoy); i++) {
		stateKeyJoy[i] = 0;
	}

	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);//フルスクリーン時の拡大モードの設定
	SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);		//画面拡大時のピクセル保管方法の設定
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);			//ウィンドウサイズの変更

	TCHAR title[50];
	_stprintf_s(title, _T("%s [Ver.%s]"), TITLE, GAMEVERSION);
	SetMainWindowText(title);								//ウィンドウのタイトル設定

#ifdef _DEBUG
	SetUseDXArchiveFlag(0);									//DXライブラリアーカイブを使用しない
#else
	SetUseDXArchiveFlag(1);									//DXライブラリアーカイブを使用する
#endif // _DEBUG

	SetUseDirect3DVersion(DX_DIRECT3D_9EX);					//シェーダモデル3を使用するためDirectX9を使用するように指定する

	if (DxLib_Init() == -1)	return -1;						//DXライブラリの初期化(ウィンドウ表示)

	fpsController_Draw.SetVSyncMode(GetWaitVSyncFlag());	//垂直同期を使用してゲームを停止するかどうかの設定
															
	SetActiveStateChangeCallBackFunction(ActiveStateChange, NULL);	// ウインドウのアクティブ状態に変化があったときに呼ばれるコールバック関数を登録
	


																	
	SetMouseDispFlag(Flag_MouseCursor);		//マウスカーソル設定(ウィンドウの生成後に行わないと無理っぽい)

	SetDrawScreen(DX_SCREEN_BACK);							//裏画面に描画を行うように設定する

	LoadMenu_Initialize();				//ロード画面の初期化

	LoadMenu_Draw2();					//ロード画面の描画


	srand((unsigned)time(NULL));							//乱数のシード値を変更


	//ここで各モジュールの初期化処理を行う
	SoundEffect_init();	//効果音関係の初期化
	Font_init();		//フォント関係の初期化


															
	if (isMultiThread())	_beginthreadex(NULL, 0, Thread_Update, "計算スレッド", 0, NULL);//マルチスレッドならば新規スレッド作成


	Thread_Draw(NULL);

	return 0;
}

//描画のメインループ
static void Draw() {
	//描画停止リクエストの反映
	FLAG_PauseDraw = FLAG_PauseDrawrequest;
	if (FLAG_PauseDraw == 1) { //描画停止フラグ
		if (faze_Wait_Loading == TRUE)	LoadMenu_Draw();
		return;
	}

	//描画のフェーズ移行
	Changefaze_Draw(); //フェーズ変更の際にテクスチャなどの読み直し

	switch (faze) {
	case FAZE_TopMenu:
		//TopMenu_Draw();
		break;
	case FAZE_GameMain:
		GameMain_Draw();
		break;
	case FAZE_Manual:
		//Manual_Draw();
		break;
	}


#ifdef _DEBUG
	//FPS描画
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("FPS(D):%.2f %.2fms(%.2f%%)"), fpsController_Draw.GetFPS_Average(), fpsController_Draw.GetWaitTime_Average(), fpsController_Draw.GetWaitTime_Average_Par());
	DrawFormatStringToHandle(0, 0 + 20, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("FPS(U):%.2f %.2fms(%.2f%%)"), fpsController_Update.GetFPS_Average(), fpsController_Update.GetWaitTime_Average(), fpsController_Update.GetWaitTime_Average_Par());
	int DrawStrW = GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("FPS(U):%.2f %.2fms(%.2f%%)"), fpsController_Update.GetFPS_Average(), fpsController_Update.GetWaitTime_Average(), fpsController_Update.GetWaitTime_Average_Par());
	if (!isMultiThread())	DrawLine(0, 31, DrawStrW, 31, GetColor(255, 255, 255), 4);
#endif // _DEBUG
}

//計算処理のループ
static void Update() {
	//フェーズ変更リクエストがあるばあい
	if (ChangefazeRequest != faze)
		Changefaze(ChangefazeRequest, THREAD_Update, faze_arg, faze_Wait_Loading);
	if (faze_Wait_Loading == TRUE)	return;

	SoundEffect_update();//フェーズ関係なく動作

	switch (faze) {
	case FAZE_Nothing: //トップメニューに移行
		Changefaze(FAZE_GameMain, THREAD_Update);
		break;
	case FAZE_TopMenu:
		//TopMenu_Update();
		break;
	case FAZE_GameMain:
		GameMain_Update();
		break;
	case FAZE_Manual:
		//Manual_Update();
		break;
	}
	Flag_NonActivePauseRequest = FALSE;


	///*キー入力情報を取得するサンプルコード(リリースでコンパイルするとエラーが出ます)*/
	//if (getKeyBind(KEYBIND_SELECT) == 1) {
	//	Log_p(_T("項目の決定"));
	//}
	//if (getKeyBind(KEYBIND_PAUSE) == 1) {
	//	Log_p(_T("キャンセル/ポーズ"));
	//}
	//if (getKeyBind(KEYBIND_ROTAL) == 1) {
	//	Log_p(_T("落下するブロックを反時計回りに回転させる"));
	//}
	//if (getKeyBind(KEYBIND_ROTAR) == 1) {
	//	Log_p(_T("落下するブロックを時計回りに回転させる"));
	//}
	//if (getKeyBind(KEYBIND_UP) == 1) {
	//	Log_p(_T("項目選択:上"));
	//}
	//if (getKeyBind(KEYBIND_DOWN) == 1) {
	//	Log_p(_T("項目選択:下/落下するブロックの加速"));
	//}
	//if (getKeyBind(KEYBIND_LEFT) == 1) {
	//	Log_p(_T("目選択:左/落下するブロックの左移動"));
	//}
	//if (getKeyBind(KEYBIND_RIGHT) == 1) {
	//	Log_p(_T("項目選択:右/落下するブロックの右移動"));
	//}

}

//フェーズを変更する
void Changefaze(FAZE NO, THREAD FLAG, int arg, int b_Wait_Loading) {
	if (FLAG == THREAD_Draw) {
		//Drawスレッドからのリクエストの場合
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("フェーズ変更リクエスト(%dから%d)"), faze, NO);
		ChangefazeRequest = NO;
		faze_arg = arg;
		faze_Wait_Loading = b_Wait_Loading;
		return;
	}

	FLAG_PauseDrawrequest = 1; //描画の停止をリクエストする
	while (1) { //無限ループ描画の一時停止を待機
		Sleep(10); /* ミリ秒単位。0.01秒待つ */ //超速無限ループ回避のため
		if (!isMultiThread()) {//マルチスレッドで動作していない場合
			FLAG_PauseDraw = FLAG_PauseDrawrequest;
		}
		if (FLAG_PauseDraw == 1) {
			break; //描画の一時停止を確認
		}
	}
	faze_Wait_Loading = b_Wait_Loading;
	faze_arg = arg;
	/* フェーズ終了の際に呼び出す関数を記述(メモリの開放など) */
	switch (faze) {
	case FAZE_TopMenu:
		//TopMenu_UpdateEnd();
		break;
	case FAZE_GameMain:
		GameMain_Finalize_Update();
		break;
	case FAZE_Manual:
		//Manual_UpdateEnd();
		break;
	}

	/* フェーズ開始の際に呼び出す関数を記述(テクスチャの読み込みなど) */
	switch (NO) {
	case FAZE_TopMenu:
		//TopMenu_UpdateSetup();
		break;
	case FAZE_GameMain:
		GameMain_Init_Update();
		break;
	case FAZE_Manual:
		//Manual_UpdateSetup();
		break;
	}

	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("フェーズ変更(%dから%d)"), faze, NO);
	faze = NO;
	ChangefazeRequest = faze;
	ChangefazeRequest_Draw = faze;
	FLAG_PauseDrawrequest = 0; //描画の一時停止解除
}

//フェーズを変更する(描画スレッド)
static void Changefaze_Draw() {

	if (faze_draw == faze && ChangefazeRequest_Draw == -1)
		return;

	//フェーズ変更があった場合↓↓↓

	if (faze_Wait_Loading == TRUE) {
		LoadMenu_Draw();
	}
	/* フェーズ終了の際に呼び出す関数を記述(メモリの開放など) */
	switch (faze_draw) {
	case FAZE_TopMenu: //メニュー
		//TopMenu_DrawEnd();
		break;
	case FAZE_GameMain:
		GameMain_Finalize_Draw();
		break;
	case FAZE_Manual:
		//Manual_DrawEnd();
		break;
	}

	/* フェーズ開始の際に呼び出す関数を記述(テクスチャの読み込みなど) */
	switch (faze) {
	case FAZE_TopMenu: //メニュー
		//TopMenu_DrawSetup();
		break;
	case FAZE_GameMain:
		GameMain_Init_Draw();
		break;
	case FAZE_Manual:
		//Manual_DrawSetup();
		break;

	}
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("フェーズ変更(%dから%d)(描画)"), faze_draw, faze);
	faze_draw = faze;
	ChangefazeRequest_Draw = -1;
	faze_Wait_Loading = FALSE;
}

#pragma region いじらなくて良い関数群
// スレッド実行する関数(ゲーム処理)
static unsigned __stdcall Thread_Update(void* args) {
	Log_SetThreadID(THREAD_Update, GetCurrentThreadId());	//計算スレッドのIDを通知
	while (TRUE) {//キーイベント処理(0でループを抜ける)
		UpdateLoop();//処理ループ
	}

	return 0;
}

//処理ループ
static void UpdateLoop() {
	fpsController_Update.Update_First();
	gpUpdateKey();		//キー取得
	Update();			//描画処理
	fpsController_Update.Update_Last();
	if (isMultiThread())	fpsController_Update.Wait();	//待機
}

// スレッド実行する関数(ゲーム描画)
static int Thread_Draw(void* args) {
	while (ProcessMessage() == 0) {//キーイベント処理(0でループを抜ける)
		fpsController_Draw.Update_First();
		if (FLAG_ClearScreen) ClearDrawScreen();	//画面を消す
		if (EndFlag)		//終了フラグ確認
			return 0;		//終了
		if (!isMultiThread()) {
			UpdateLoop();
		}
		if (fpsController_Draw.GetFrameCount() % Drawing_interval == 0) {
			Draw();				//描画処理
		}
		fpsController_Draw.Update_Last();
		if (fpsController_Draw.GetFrameCount() % Drawing_interval == 0) {
			ScreenFlip();		//裏画面を表画面に反映
		}
		else if (fpsController_Draw.GetVSyncMode()) {//垂直同期の待機を行う(垂直同期が有効な場合)
			WaitTimer(1);		//1ミリ秒待機1ループが早すぎると正しく動かない？ようなので1ミリ秒待機する
			WaitVSync(1);		//裏画面を表画面に反映
		}
		fpsController_Draw.Wait();	//待機
	}

	return 0;
}

// キーの入力状態を更新する
static int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			stateKey[i]++;     // 加算
		}
		else {              // 押されていなければ
			stateKey[i] = 0;   // 0にする
		}
	}
	//ゲームパッドのキー入力状態の更新
	unsigned int tmpJoyKey = GetJoypadInputState(gettUSEGAMEPAD());//入力状態の取得;
	for (int i = 0; i < ARRAY_LENGTH(stateKeyJoy); i++) {
		unsigned int Value = 1 << i;
		if (tmpJoyKey & Value)	stateKeyJoy[i]++;
		else					stateKeyJoy[i] = 0;
	}
	//上の結果に基づきキーバインドによる入力状態を更新する
	gpUpdateKeyBind();
	return 0;
}

//キーバインドによるキー入力状態の更新
static void gpUpdateKeyBind() {
	//項目の決定
	if (getKey(KeyBindSetting.Key_ENTER) || getKey(KeyBindSetting.Key_ENTER2)
		|| getJoyKey(JoyKeyBindSetting.Joy_ENTER[0]) || getJoyKey(JoyKeyBindSetting.Joy_ENTER[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_ENTER[2]) || getJoyKey(JoyKeyBindSetting.Joy_ENTER[3])) {
		stateKeyBind[KEYBIND_SELECT]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_SELECT] = 0;	//押されていなければ0にする

	//キャンセル/ポーズ
	if (getKey(KeyBindSetting.Key_PAUSE) || getKey(KeyBindSetting.Key_PAUSE2)
		|| getJoyKey(JoyKeyBindSetting.Joy_PAUSE[0]) || getJoyKey(JoyKeyBindSetting.Joy_PAUSE[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_PAUSE[2]) || getJoyKey(JoyKeyBindSetting.Joy_PAUSE[3])) {
		stateKeyBind[KEYBIND_PAUSE]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_PAUSE] = 0;	//押されていなければ0にする

	//落下するブロックを反時計回りに回転させる
	if (getKey(KeyBindSetting.Key_RotateL) || getKey(KeyBindSetting.Key_RotateL2)
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateL[0]) || getJoyKey(JoyKeyBindSetting.Joy_RotateL[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateL[2]) || getJoyKey(JoyKeyBindSetting.Joy_RotateL[3])) {
		stateKeyBind[KEYBIND_ROTAL]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_ROTAL] = 0;		//押されていなければ0にする

	//落下するブロックを時計回りに回転させる
	if (getKey(KeyBindSetting.Key_RotateR) || getKey(KeyBindSetting.Key_RotateR2)
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateR[0]) || getJoyKey(JoyKeyBindSetting.Joy_RotateR[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateR[2]) || getJoyKey(JoyKeyBindSetting.Joy_RotateR[3])) {
		stateKeyBind[KEYBIND_ROTAR]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_ROTAR] = 0;		//押されていなければ0にする

	//項目選択:上
	if (getKey(KeyBindSetting.Key_UP) || getKey(KeyBindSetting.Key_UP2)
		|| getJoyKey(JoyKeyBindSetting.Joy_UP[0]) || getJoyKey(JoyKeyBindSetting.Joy_UP[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_UP[2]) || getJoyKey(JoyKeyBindSetting.Joy_UP[3])) {
		stateKeyBind[KEYBIND_UP]++;			//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_UP] = 0;		//押されていなければ0にする

	//項目選択:下/落下するブロックの加速
	if (getKey(KeyBindSetting.Key_DOWN) || getKey(KeyBindSetting.Key_DOWN2)
		|| getJoyKey(JoyKeyBindSetting.Joy_DOWN[0]) || getJoyKey(JoyKeyBindSetting.Joy_DOWN[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_DOWN[2]) || getJoyKey(JoyKeyBindSetting.Joy_DOWN[3])) {
		stateKeyBind[KEYBIND_DOWN]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_DOWN] = 0;		//押されていなければ0にする

	//項目選択:左/落下するブロックの左移動
	if (getKey(KeyBindSetting.Key_LEFT) || getKey(KeyBindSetting.Key_LEFT2)
		|| getJoyKey(JoyKeyBindSetting.Joy_LEFT[0]) || getJoyKey(JoyKeyBindSetting.Joy_LEFT[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_LEFT[2]) || getJoyKey(JoyKeyBindSetting.Joy_LEFT[3])) {
		stateKeyBind[KEYBIND_LEFT]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_LEFT] = 0;		//押されていなければ0にする

	//項目選択:右/落下するブロックの右移動
	if (getKey(KeyBindSetting.Key_RIGHT) || getKey(KeyBindSetting.Key_RIGHT2)
		|| getJoyKey(JoyKeyBindSetting.Joy_RIGHT[0]) || getJoyKey(JoyKeyBindSetting.Joy_RIGHT[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_RIGHT[2]) || getJoyKey(JoyKeyBindSetting.Joy_RIGHT[3])) {
		stateKeyBind[KEYBIND_RIGHT]++;		//対応するキーが押されていたら加算
	}
	else	stateKeyBind[KEYBIND_RIGHT] = 0;	//押されていなければ0にする
}

// ウインドウのアクティブ状態に変化があったときに呼ばれるコールバック関数
static int ActiveStateChange(int ActiveState, void *UserData) {
	// アクティブに変化した場合にカウントする
	if (ActiveState == FALSE)//ウィンドウが非アクティブになったとき
	{
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ウィンドウが【非アクティブ】になりました"));
		Flag_NonActivePauseRequest = TRUE;
	}
	else {
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ウィンドウが【アクティブ】になりました"));
	}

	// 終了
	return 0;
}

#pragma endregion


/*値の取得系*/
//非アクティブになった際にポーズを要求するフラグが立っているかの取得
int isFlag_NonActivePauseRequest() {
#ifndef DEBUG
	return Flag_NonActivePauseRequest;
#else
	return FALSE;//Debugモードでコンパイルしたときはポーズにならない
#endif // DEBUG
}

//マルチスレッドで動作するかどうかの取得(FALSEシングル)
int isMultiThread() {
	return Flag_MultiThread;
}

//使用するゲームパッドの取得
int gettUSEGAMEPAD() {
	return USEGamePad;
}

//キーの入力状態を取得する(DXライブラリで定義されているキーの番号)(戻り値：キーが押されている時間、押されていないときは0)
unsigned int getKey(int KEYNO) {
	if (KEYNO < 0 || 256 <= KEYNO)	return 0;
	return stateKey[KEYNO];
}

//ゲームパッド入力状態の取得(DXライブラリで定義されているキーの番号)(戻り値：キーが押されている時間、押されていないときは0)(ゲームパッド用)
unsigned int getJoyKey(int JoyKeyNO) {
	//何ビット目かの確認
	int bit = 0;
	for (int i = 0; i < ARRAY_LENGTH(stateKeyJoy); i++) {
		unsigned int Value = 1 << i;
		if (JoyKeyNO == Value) {
			bit = i + 1;	//キーコンビネーションが入った場合は反応無し
			break;
		}
	}
	if (bit <= 0)	return 0;
	bit--;//配列は0起算なのでデクリメント
	if (bit < 0 || ARRAY_LENGTH(stateKeyJoy) <= bit)	return 0;
	return stateKeyJoy[bit];
}

//キーバインドでのキー入力情報の取得(0押してない、1押した直後)
unsigned int getKeyBind(KEYBIND kEYBIND) {
	if (kEYBIND < 0 || KEYBIND_NUM <= kEYBIND)	return 0;
	return stateKeyBind[kEYBIND];
}

//ゲームが起動してからの経過フレーム数を取得する
unsigned int getFrameCount(THREAD thread) {
	switch (thread) {
	case THREAD_Draw:
		return fpsController_Draw.GetFrameCount();
	case THREAD_Update:
		return fpsController_Update.GetFrameCount();
	}
	return 0;
}

//プログラムを終了する

#pragma region いじらなくて良い関数群
/*値の設定系(ここも通常いじらない)*/
//キーバインドの設定(NULLで規定値)
void setKeybind(KeyBind *keyBind) {

	//とりあえず規定値を設定
	KeyBindSetting.Key_ENTER = KEY_INPUT_RETURN;
	KeyBindSetting.Key_ENTER2 = KEY_INPUT_RETURN;
	KeyBindSetting.Key_PAUSE = KEY_INPUT_ESCAPE;
	KeyBindSetting.Key_PAUSE2 = KEY_INPUT_BACK;
	KeyBindSetting.Key_RotateL = KEY_INPUT_Z;
	KeyBindSetting.Key_RotateL2 = KEY_INPUT_K;
	KeyBindSetting.Key_RotateR = KEY_INPUT_X;
	KeyBindSetting.Key_RotateR2 = KEY_INPUT_L;
	KeyBindSetting.Key_UP = KEY_INPUT_UP;
	KeyBindSetting.Key_UP2 = KEY_INPUT_W;
	KeyBindSetting.Key_DOWN = KEY_INPUT_DOWN;
	KeyBindSetting.Key_DOWN2 = KEY_INPUT_S;
	KeyBindSetting.Key_LEFT = KEY_INPUT_LEFT;
	KeyBindSetting.Key_LEFT2 = KEY_INPUT_D;
	KeyBindSetting.Key_RIGHT = KEY_INPUT_RIGHT;
	KeyBindSetting.Key_RIGHT2 = KEY_INPUT_A;
	if (keyBind == NULL) return;
	//変換失敗を表す65535が無いかの確認後設定する
	//if (keyBind->Key_ENTER != 65535)	KeyBindSetting.Key_ENTER = keyBind->Key_ENTER;
	//if (keyBind->Key_ENTER2 != 65535)	KeyBindSetting.Key_ENTER2 = keyBind->Key_ENTER2;
	//if (keyBind->Key_PAUSE != 65535)	KeyBindSetting.Key_PAUSE = keyBind->Key_PAUSE;
	if (keyBind->Key_PAUSE2 != 65535)	KeyBindSetting.Key_PAUSE2 = keyBind->Key_PAUSE2;
	if (keyBind->Key_RotateL != 65535)		KeyBindSetting.Key_RotateL = keyBind->Key_RotateL;
	if (keyBind->Key_RotateL2 != 65535)	KeyBindSetting.Key_RotateL2 = keyBind->Key_RotateL2;
	if (keyBind->Key_RotateR != 65535)		KeyBindSetting.Key_RotateR = keyBind->Key_RotateR;
	if (keyBind->Key_RotateR2 != 65535)	KeyBindSetting.Key_RotateR2 = keyBind->Key_RotateR2;
	if (keyBind->Key_UP != 65535)		KeyBindSetting.Key_UP = keyBind->Key_UP;
	if (keyBind->Key_UP2 != 65535)		KeyBindSetting.Key_UP2 = keyBind->Key_UP2;
	if (keyBind->Key_DOWN != 65535)		KeyBindSetting.Key_DOWN = keyBind->Key_DOWN;
	if (keyBind->Key_DOWN2 != 65535)	KeyBindSetting.Key_DOWN2 = keyBind->Key_DOWN2;
	if (keyBind->Key_LEFT != 65535)		KeyBindSetting.Key_LEFT = keyBind->Key_LEFT;
	if (keyBind->Key_LEFT2 != 65535)	KeyBindSetting.Key_LEFT2 = keyBind->Key_LEFT2;
	if (keyBind->Key_RIGHT != 65535)	KeyBindSetting.Key_RIGHT = keyBind->Key_RIGHT;
	if (keyBind->Key_RIGHT2 != 65535)	KeyBindSetting.Key_RIGHT2 = keyBind->Key_RIGHT2;
}

//使用するゲームパッドの設定(引数省略で設定無し)
void setUSEGAMEPAD(int type) {
	if (type < 0 || DX_INPUT_PAD16 < type)	type = 0;
	USEGamePad = type;
}

//ゲームパッドのアナログスティックの動作方法の設定
void SetAnalogueStickMode(ANALOGSTICKMODE type) {
	if (type < 0 || ANALOGSTICKMODE_NUM <= type)	type = ANALOGSTICKMODE_NOUSE;
	Analogstickmode = type;
}

//画面のクリアを行うかどうか(FALSE行わない)(するとこはします)
void setClearScreen(int Flag) {
	FLAG_ClearScreen = (Flag) ? TRUE : FALSE;
	if (FLAG_ClearScreen)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("画面消去を【すべて有効】に設定"));
	else 					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("画面消去を【適宜有効】に設定"));
}

//描画間隔の設定(0から項目順)
void SetDrawing_interval(int Mode) {
	switch (Mode) {
	case 0://全フレーム
		Drawing_interval = 1;
		break;
	case 1://1/2フレーム
		Drawing_interval = 2;
		break;
	case 2://1/3フレーム
		Drawing_interval = 3;
		break;
	case 3://1/4フレーム
		Drawing_interval = 4;
		break;
	default:
		Drawing_interval = 1;
		break;
	}
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("描画間隔を1/%dに設定しました"), Drawing_interval);
}

//ウィンドウモードの設定(0から項目順)
void SetWindowMode(int Mode) {
	switch (Mode) {
	case 0://1280x960
		SetWindowSizeExtendRate(1);	//ウィンドウサイズの倍率を変更する
		ChangeWindowMode(TRUE);		//ウィンドウモードに変更
		SetAlwaysRunFlag(TRUE);		//バックグラウンドで停止しないようにする
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ウィンドウの大きさを%dx%dに設定しました"), WINDOW_WIDTH * 1, WINDOW_HEIGHT * 1);
		break;
	case 1://960x720
		SetWindowSizeExtendRate(0.75);	//ウィンドウサイズの倍率を変更する
		ChangeWindowMode(TRUE);	//ウィンドウモードに変更
		SetAlwaysRunFlag(TRUE);	//バックグラウンドで停止しないようにする
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ウィンドウの大きさを%dx%dに設定しました"), (int)(WINDOW_WIDTH * 0.75), (int)(WINDOW_HEIGHT * 0.75));
		break;
	case 2://640x480
		SetWindowSizeExtendRate(0.5);	//ウィンドウサイズの倍率を変更する
		ChangeWindowMode(TRUE);	//ウィンドウモードに変更
		SetAlwaysRunFlag(TRUE);	//バックグラウンドで停止しないようにする
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ウィンドウの大きさを%dx%dに設定しました"), (int)(WINDOW_WIDTH * 0.5), (int)(WINDOW_HEIGHT * 0.5));
		break;
	case 3://仮想フルスクリーン
		setWindowModeVirtualFullScreen();
		ChangeWindowMode(TRUE);	//ウィンドウモードに変更
		SetAlwaysRunFlag(TRUE);	//バックグラウンドで停止しないようにする
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("仮想フルスクリーンに設定"));
		break;
	case 4://フルスクリーン
		SetWindowSizeExtendRate(1);	//ウィンドウサイズの倍率を変更する
		SetAlwaysRunFlag(FALSE);	//バックグラウンドで停止するようにする
		ChangeWindowMode(FALSE);	//フルスクリーンに変更
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("フルスクリーンに設定"));
		break;
	default:
		SetWindowSizeExtendRate(1);	//ウィンドウサイズの倍率を変更する
		ChangeWindowMode(TRUE);	//ウィンドウモードに変更
		SetAlwaysRunFlag(TRUE);	//バックグラウンドで停止しないようにする
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ウィンドウの大きさを%dx%dに設定しました"), WINDOW_WIDTH * 1, WINDOW_HEIGHT * 1);
		break;
	}
}

//仮想フルスクリーン化
static void setWindowModeVirtualFullScreen() {
	int X = 0, Y = 0, Clolr = 0;
	GetDefaultState(&X, &Y, &Clolr);//ウィンドウの大きさ取得
	SetWindowStyleMode(2);															//ウィンドウの縁を消す
	SetWindowPosition(0, 0);														//ウィンドウの位置を左上に合わせる
	SetWindowSizeExtendRate(X / (double)WINDOW_WIDTH, Y / (double)WINDOW_HEIGHT);	//ウィンドウサイズの倍率を変更する
}

//垂直同期の設定(0から項目順)
void SetModeVSync(int Mode) {
	switch (Mode) {
	case 0://垂直同期有り
		fpsController_Draw.SetVSyncMode(TRUE);
		SetWaitVSyncFlag(TRUE);
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("垂直同期を【有効】に設定"), Drawing_interval);
		break;
	case 1://垂直同期無し
		fpsController_Draw.SetVSyncMode(FALSE);
		SetWaitVSyncFlag(FALSE);
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("垂直同期を【無効】に設定"), Drawing_interval);
		break;
	default:
		fpsController_Draw.SetVSyncMode(TRUE);
		SetWaitVSyncFlag(TRUE);
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("垂直同期を【有効】に設定"), Drawing_interval);
		break;
	}
}

//画面消去の設定(0から項目順)
void SetModeClear(int Mode) {
	switch (Mode) {
	case 0://適宜画面消去
		setClearScreen(FALSE);
		break;
	case 1://すべて画面消去
		setClearScreen(TRUE);
		break;
	default:
		setClearScreen(FALSE);
		break;
	}
}

//マウスカーソルの設定(0から項目順)(ウィンドウモードの設定と同じ引数)
void SetModeCursor(int Mode, int WinMode) {
	switch (Mode) {
	case 0://適宜表示
		if (WinMode == 3 || WinMode == 4) {//仮想フルスクリーンの時、フルスクリーンの時に非表示
			Flag_MouseCursor = FALSE;
		}
		else {
			Flag_MouseCursor = TRUE;
		}
		break;
	case 1://常に表示
		Flag_MouseCursor = TRUE;
		break;
	default://適宜表示
		if (WinMode == 3 || WinMode == 4) {//仮想フルスクリーンの時、フルスクリーンの時に非表示
			Flag_MouseCursor = FALSE;
		}
		else {
			Flag_MouseCursor = TRUE;
		}
		break;
	}
}

//マルチスレッドの設定(0から項目順)
void SetModeMultiThread(int Mode) {
	switch (Mode) {
	case 0://マルチスレッド
		Flag_MultiThread = TRUE;
		break;
	case 1://シングルスレッド
		Flag_MultiThread = FALSE;
		break;
	default://マルチスレッド
		Flag_MultiThread = TRUE;
		break;
	}
}

//テクスチャの分割の設定(0から項目順)
void SetTextureCut(int Mode) {
	switch (Mode) {
	case 0://分割
		SetUseDivGraphFlag(TRUE);
		break;
	case 1://そのまま
		SetUseDivGraphFlag(FALSE);
		break;
	default://分割
		SetUseDivGraphFlag(TRUE);
		break;
	}
}

//キーバインド設定(ゲームパッド)(NULLで規定値を設定)
void setKeybindjoy(KeyBindjoy *keyBindjoy) {

	//とりあえず規定値を設定
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_ENTER); i++)		JoyKeyBindSetting.Joy_ENTER[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_PAUSE); i++)		JoyKeyBindSetting.Joy_PAUSE[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateL); i++)	JoyKeyBindSetting.Joy_RotateL[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateR); i++)	JoyKeyBindSetting.Joy_RotateR[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_UP); i++)		JoyKeyBindSetting.Joy_UP[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_DOWN); i++)		JoyKeyBindSetting.Joy_DOWN[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_LEFT); i++)		JoyKeyBindSetting.Joy_LEFT[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RIGHT); i++)		JoyKeyBindSetting.Joy_RIGHT[i] = 0;

	if (keyBindjoy == NULL) return;
	//キー設定
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_ENTER); i++)		JoyKeyBindSetting.Joy_ENTER[i] = keyBindjoy->Joy_ENTER[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_PAUSE); i++)		JoyKeyBindSetting.Joy_PAUSE[i] = keyBindjoy->Joy_PAUSE[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateL); i++)	JoyKeyBindSetting.Joy_RotateL[i] = keyBindjoy->Joy_RotateL[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateR); i++)	JoyKeyBindSetting.Joy_RotateR[i] = keyBindjoy->Joy_RotateR[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_UP); i++)		JoyKeyBindSetting.Joy_UP[i] = keyBindjoy->Joy_UP[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_DOWN); i++)		JoyKeyBindSetting.Joy_DOWN[i] = keyBindjoy->Joy_DOWN[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_LEFT); i++)		JoyKeyBindSetting.Joy_LEFT[i] = keyBindjoy->Joy_LEFT[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RIGHT); i++)		JoyKeyBindSetting.Joy_RIGHT[i] = keyBindjoy->Joy_RIGHT[i];

}
#pragma endregion