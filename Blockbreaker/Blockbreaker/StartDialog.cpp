//ゲーム起動時の設定画面ダイアログ関係
#include "MainFunc.h"

#define WM_USER_JOYDOWN (WM_USER+1)	//ジョイスティックのキーが押されたとき

//起動時のダイアログの項目
struct DialogSetting {
	int resolution;			//ゲームの解像度
	int VSync;				//垂直同期
	int Clear;				//画面の消去モード
	int Cursor;				//マウスカーソル
	int Thread;				//マルチスレッド
	int Texture;			//テクスチャの分割
	int Drawing_interval;	//描画間隔
	int analogstick;		//アナログスティックの操作モード
	bool Key_Enable;		//キーバインドが有効かどうか
	WPARAM Key_PAUSE;			//キャンセル/ポーズ
	WPARAM Key_PAUSE2;			//キャンセル/ポーズ2
	WPARAM Key_RotateL;		//落下するブロックを反時計回りに回転させる
	WPARAM Key_RotateL2;		//落下するブロックを反時計回りに回転させる2
	WPARAM Key_RotateR;		//落下するブロックを時計回りに回転させる
	WPARAM Key_RotateR2;		//落下するブロックを時計回りに回転させる2
	WPARAM Key_UP;				//項目選択:上
	WPARAM Key_UP2;			//項目選択:上2
	WPARAM Key_DOWN;			//項目選択:下/落下するブロックの加速
	WPARAM Key_DOWN2;			//項目選択:下/落下するブロックの加速2
	WPARAM Key_LEFT;			//項目選択:左/落下するブロックの左移動
	WPARAM Key_LEFT2;			//項目選択:左/落下するブロックの左移動2
	WPARAM Key_ROGHT;			//項目選択:右/落下するブロックの右移動
	WPARAM Key_ROGHT2;			//項目選択:右/落下するブロックの右移動2
	unsigned int Joy_Type;	//ジョイパッド入力の種類
	int Joy_ENTER[4];		//入力ジョイパッドの項目の決定
	int Joy_PAUSE[4];		//入力ジョイパッドのキャンセル/ポーズ
	int Joy_RotateL[4];		//入力ジョイパッドの落下するブロックを反時計回りに回転させる
	int Joy_RotateR[4];		//入力ジョイパッドの落下するブロックを時計回りに回転させる
	int Joy_UP[4];			//入力ジョイパッドの項目選択:上
	int Joy_DOWN[4];		//入力ジョイパッドの項目選択:下/落下するブロックの加速
	int Joy_LEFT[4];		//入力ジョイパッドの項目選択:左/落下するブロックの左移動
	int Joy_ROGHT[4];		//入力ジョイパッドの項目選択:右/落下するブロックの右移動
};


const HBRUSH bkColorBrush = CreateSolidBrush(RGB(255, 255, 255));//背景色のブラシを用意する

static HINSTANCE HInstance;

static HWND Tab1;
static HWND Tab2;
static HWND Tab3;
static HWND Tab4;
static HWND Tab5;
static HWND Tab6;
static HWND Tab7;
static HWND Tab8;		//アナログスティック設定
static HWND Tab9;		//キーボードのキー設定
static HWND Tab10;		//ジョイパッドのキー設定

static struct DialogSetting dialogSetting;	//ダイアログの設定
static HWND Dialoghandle;	//ダイアログウィンドウのハンドル
static int keyConfigType = 0;	//キーコンフィグの設定状態(0で設定無し)
static bool keyConfigmode = false;	//キーコンフィグの設定状態(faseで設定中出ない)
static int joyConfigType = 0;	//キーコンフィグの設定(ジョイパッド)状態(0で設定無し)
static bool joyConfigmode = false;	//キーコンフィグの設定(ジョイパッド)状態(faseで設定中出ない)
static int joyBeforeState = 0;		//ジョイパッドの前の状態


static HFONT SetMyFont(LPCTSTR face, int h);
static LRESULT CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab4(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab5(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab6(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab7(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab8(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab9(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK DlgProcTab10(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
static void StartDialog_Save();
static void VerifySaveData();
static TCHAR *ConvertVerKey(WPARAM VkeyCode);
static void CreateKeyConfig(KeyBind *kb);
static void CreateKeyConfigjoy(KeyBindjoy *kb);
static bool CheckDouble(int defplm, WPARAM wParam);
static void joypatEvent();
static int *getJoySettings(int ItemID);
static void SetJoyNomalText(HWND hDlg, LPARAM lParam, int ItemID);
static int EnentJoySetButtonChange(HWND hDlg, WPARAM wParam, LPARAM lParam, int ItemID);
static TCHAR *ConvertVerJoyKey(int JoyCode);
static int GetBit(LPARAM Val);
static int SetBitRight(LPARAM Val);
static bool CheckDoubleJoy(int defplm, int wParam);

//初期化
void StartDialog_Initialize(HINSTANCE hInstance) {
	HInstance = hInstance;
	printLog_I(_T("起動設定画面の初期化を行います"));
	//初期値を設定する
	dialogSetting.resolution = IDC_DSIZE_RADIO1;
	dialogSetting.VSync = IDC_VSYNC_RADIO1;
	dialogSetting.Clear = IDC_CLEAR_RADIO1;
	dialogSetting.Cursor = IDC_CURSOR_RADIO1;
	dialogSetting.Thread = IDC_THREAD_RADIO1;
	dialogSetting.Texture = IDC_TEXTURE_RADIO1;
	dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL1;
	dialogSetting.analogstick = IDC_RADIO1;
	dialogSetting.Key_Enable = true;
	dialogSetting.Key_RotateL = 'Z';
	dialogSetting.Key_RotateL2 = 'K';
	dialogSetting.Key_RotateR = 'X';
	dialogSetting.Key_RotateR2 = 'L';
	dialogSetting.Key_UP = VK_UP;
	dialogSetting.Key_UP2 = 'W';
	dialogSetting.Key_DOWN = VK_DOWN;
	dialogSetting.Key_DOWN2 = 'S';
	dialogSetting.Key_ROGHT = VK_RIGHT;
	dialogSetting.Key_ROGHT2 = 'D';
	dialogSetting.Key_LEFT = VK_LEFT;
	dialogSetting.Key_LEFT2 = 'A';
	dialogSetting.Key_PAUSE = VK_ESCAPE;
	dialogSetting.Key_PAUSE2 = VK_BACK;
	dialogSetting.Joy_Type = 0;
	dialogSetting.Joy_RotateL[4] = {};		//入力ジョイパッドの低ショット発射
	dialogSetting.Joy_RotateR[4] = {};		//入力ジョイパッドの低速移動
	dialogSetting.Joy_UP[4] = {};		//入力ジョイパッドの上移動
	dialogSetting.Joy_DOWN[4] = {};		//入力ジョイパッドの下移動
	dialogSetting.Joy_ROGHT[4] = {};	//入力ジョイパッドの右移動
	dialogSetting.Joy_LEFT[4] = {};		//入力ジョイパッドの左移動
	dialogSetting.Joy_PAUSE[4] = {};	//入力ジョイパッドのポーズ
	dialogSetting.Joy_ENTER[4] = {};	//入力ジョイパッドの決定
	keyConfigType = 0;
	keyConfigmode = false;
	joyConfigType = 0;
	joyConfigmode = false;
	joyBeforeState = 0;
	FILE* fp;
	_tfopen_s(&fp, _T("Setting.bin"), _T("rb"));
	if (fp == NULL) {
		return;
	}
	CHAR ver[15];
	size_t len = _tcslen(GAMEVERSION) + 1;
	fread(&len, sizeof(len), 1, fp);//バージョンの文字数
	if (len > 15) {
		if (fclose(fp) == EOF) {
			return;
		}
		len = 15;
	}
	fread(ver, sizeof(CHAR), len, fp);//バージョンの明記
	fread(&dialogSetting, sizeof(dialogSetting), 1, fp);//セーブデータ読み出し

	if (fclose(fp) == EOF) {
		printLog_E(_T("ファイルクローズに失敗しました。(Setting.bin)"));
		return;
	}
	VerifySaveData();
	printLog_I(_T("ゲームの起動設定を復元しました"));
}

//保存処理
static void StartDialog_Save() {
	FILE* fp;
	_tfopen_s(&fp, _T("Setting.bin"), _T("wb"));
	if (fp == NULL) {
		return;
	}
	size_t len = _tcslen(GAMEVERSION) + 1;
	fwrite(&len, sizeof(len), 1, fp);//バージョンの文字数
	fwrite(GAMEVERSION, sizeof(CHAR), len, fp);//バージョンの明記
	fwrite(&dialogSetting, sizeof(dialogSetting), 1, fp);//セーブデータ読み出し

	if (fclose(fp) == EOF) {
		printLog_E(_T("ファイルクローズに失敗しました。(Setting.bin)"));
		return;
	}
	printLog_I(_T("ゲームの起動設定を保存しました"));
}

//起動設定画面の表示
void StartDialog_Show() {
	printLog_I(_T("起動設定画面を開きます"));
	Dialoghandle = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgProc);	//ダイアログの生成+表示

	ShowWindow(Dialoghandle, SW_SHOW);

	MSG msg;
	while (TRUE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			if (keyConfigmode == false) {
				if (Dialoghandle == 0 || !IsDialogMessage(Dialoghandle, &msg)) {//通常のダイアログの挙動を行う
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				}
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//もはやゴリ押し･･･
				if (msg.message == WM_KEYDOWN) {
					SendMessage(Tab9, WM_KEYDOWN, msg.wParam, msg.lParam);//タブ8に強制的にキーを押したイベントを起こさせる
				}
				else if (msg.message == WM_KEYUP) {
					SendMessage(Tab9, WM_KEYUP, msg.wParam, msg.lParam);//タブ8に強制的にキーを押したイベントを起こさせる
				}
			}
		}
		else {
			joypatEvent();
		}
	}
}

//メインのダイアログのコールバック関数
static LRESULT CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
	{
		//バージョン情報
		TCHAR txt[30] = _T("");
		_stprintf_s(txt, _T("Ver.%s"), GAMEVERSION);//ダイアログに書く文字列(バージョン)の生成
		SetDlgItemText(hDlg, IDC_VERSION_STATIC, txt);


		//タブの追加
		HWND hStatic = GetDlgItem(hDlg, IDC_TAB1);//なんかインスタンス的なものを取得
		NMHDR nmhdr;
		nmhdr.hwndFrom = hDlg;
		nmhdr.idFrom = IDC_TAB1;
		nmhdr.code = TCN_SELCHANGE;
		TCITEM tcitem;
		tcitem.mask = TCIF_TEXT;//pszText
		tcitem.dwState = TCIS_BUTTONPRESSED;//タブコントロールアイテムは選択されています。(TCM_INSERTITEMでは無視？)
		tcitem.dwStateMask = 0;//dwState メンバのどのビットが有効な情報を含んでいるのかを指定します。 TCM_INSERTITEM メッセージではこのメンバは無視されます。
		tcitem.pszText = _T("基本1");//タブに表示する文字
		tcitem.cchTextMax = 3;//pszTextの文字数
		tcitem.iImage = -1;//タブコントロールに関連付けられたイメージリストのインデックスが格納されます(イメージを表示しない場合は -1)
		tcitem.lParam = (LPARAM)&nmhdr;//タブアイテムに関連付けられたアプリケーション定義の32ビット値
		SendMessage(hStatic, TCM_INSERTITEM, (WPARAM)(int)0, (LPARAM)&tcitem);
		tcitem.pszText = _T("基本2");//タブに表示する文字
		SendMessage(hStatic, TCM_INSERTITEM, (WPARAM)(int)1, (LPARAM)&tcitem);
		tcitem.pszText = _T("その他1");//タブに表示する文字
		SendMessage(hStatic, TCM_INSERTITEM, (WPARAM)(int)2, (LPARAM)&tcitem);
		tcitem.pszText = _T("その他2");//タブに表示する文字
		SendMessage(hStatic, TCM_INSERTITEM, (WPARAM)(int)3, (LPARAM)&tcitem);
		tcitem.pszText = _T("キー");//タブに表示する文字
		SendMessage(hStatic, TCM_INSERTITEM, (WPARAM)(int)4, (LPARAM)&tcitem);
		tcitem.pszText = _T("キー2");//タブに表示する文字
		SendMessage(hStatic, TCM_INSERTITEM, (WPARAM)(int)5, (LPARAM)&tcitem);

		//子ダイアログの生成
		//選択されている内容に応じて表示内容を変更する
		Tab1 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_SCREENSIZE), hDlg, (DLGPROC)DlgProcTab1);
		ShowWindow(Tab1, SW_SHOW);
		Tab2 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_DRAWING_INTERVAL), hDlg, (DLGPROC)DlgProcTab2);
		Tab3 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_VSYNC), hDlg, (DLGPROC)DlgProcTab3);
		Tab4 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_SCREENCLEAR), hDlg, (DLGPROC)DlgProcTab4);
		Tab5 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_CURSOR), hDlg, (DLGPROC)DlgProcTab5);
		Tab6 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_THREAD), hDlg, (DLGPROC)DlgProcTab6);
		Tab7 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_TEXTURE), hDlg, (DLGPROC)DlgProcTab7);
		Tab8 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_ANALOGSTICK), hDlg, (DLGPROC)DlgProcTab8);
		Tab9 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_KEY1), hDlg, (DLGPROC)DlgProcTab9);
		Tab10 = CreateDialog(HInstance, MAKEINTRESOURCE(IDD_KEY2), hDlg, (DLGPROC)DlgProcTab10);


		//書体の変更
		HFONT hFont = SetMyFont(_T("HG正楷書体-PRO"), 20);//HG正楷書体-PRO
		hStatic = GetDlgItem(hDlg, IDC_VERSION_STATIC);
		SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);
		hStatic = GetDlgItem(hDlg, IDOK);
		SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);



		break;

	}
	case WM_CREATE:
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {//OKボタンが押されたとき
			DestroyWindow(Dialoghandle);
			//データの整合性の確認
			VerifySaveData();
			//設定の保存をここで行う
			StartDialog_Save();
			//各種設定項目の反映
			SetWindowMode(dialogSetting.resolution - IDC_DSIZE_RADIO1);
			SetDrawing_interval(dialogSetting.Drawing_interval - IDC_DRAWING_INTERVAL1);
			SetModeVSync(dialogSetting.VSync - IDC_VSYNC_RADIO1);
			SetModeClear(dialogSetting.Clear - IDC_CLEAR_RADIO1);
			SetModeCursor(dialogSetting.Cursor - IDC_CURSOR_RADIO1, dialogSetting.resolution - IDC_DSIZE_RADIO1);
			SetModeMultiThread(dialogSetting.Thread - IDC_THREAD_RADIO1);
			SetTextureCut(dialogSetting.Texture - IDC_TEXTURE_RADIO1);
			SetAnalogueStickMode((ANALOGSTICKMODE)(dialogSetting.analogstick - IDC_RADIO1));
			if (dialogSetting.Key_Enable) {
				KeyBind kb;
				CreateKeyConfig(&kb);//キーバインド生成
				setKeybind(&kb);	//キーコンフィグの設定
			}
			else {
				setKeybind(NULL);	//キーコンフィグの設定(規定値)
			}
			setUSEGAMEPAD(dialogSetting.Joy_Type);
			{
				KeyBindjoy kbj;
				CreateKeyConfigjoy(&kbj);//キーバインド生成
				setKeybindjoy(&kbj);//キーコンフィグの設定
			}
			return 0;
		}
		break;
	case WM_CLOSE://×ボタンが押されたとき
		exit(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_NOTIFY://コモンコントロールからの通知(タブが変更された時？)
	{
		switch (((NMHDR *)lParam)->code) {
		case TCN_SELCHANGE:
			HWND hStatic = GetDlgItem(hDlg, IDC_TAB1);//なんかインスタンス的なものを取得
			int a = TabCtrl_GetCurSel(hStatic);//現在選択されているタブの取得
											   //選択されている内容に応じて表示内容を変更する
											   //いったん全部隠す
			ShowWindow(Tab1, SW_HIDE);
			ShowWindow(Tab2, SW_HIDE);
			ShowWindow(Tab3, SW_HIDE);
			ShowWindow(Tab4, SW_HIDE);
			ShowWindow(Tab5, SW_HIDE);
			ShowWindow(Tab6, SW_HIDE);
			ShowWindow(Tab7, SW_HIDE);
			ShowWindow(Tab8, SW_HIDE);
			ShowWindow(Tab9, SW_HIDE);
			ShowWindow(Tab10, SW_HIDE);
			switch (a) {
			case 0://画面サイズ
				ShowWindow(Tab1, SW_SHOW);
				break;
			case 1:
				ShowWindow(Tab2, SW_SHOW);
				break;
			case 2:
				ShowWindow(Tab3, SW_SHOW);
				ShowWindow(Tab4, SW_SHOW);
				ShowWindow(Tab5, SW_SHOW);
				break;
			case 3:
				ShowWindow(Tab6, SW_SHOW);
				ShowWindow(Tab7, SW_SHOW);
				ShowWindow(Tab8, SW_SHOW);
				break;
			case 4:
				ShowWindow(Tab9, SW_SHOW);
				break;
			case 5:
				ShowWindow(Tab10, SW_SHOW);
				break;
			}
			break;
		}
		break;
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);
}

//フォントデータの作成
static HFONT SetMyFont(LPCTSTR face, int h) {
	HFONT hFont;
	hFont = CreateFont(h,    //フォント高さ
		0,                    //文字幅
		0,                    //テキストの角度
		0,                    //ベースラインとｘ軸との角度
		FW_REGULAR,            //フォントの重さ（太さ）
		FALSE,                //イタリック体
		FALSE,                //アンダーライン
		FALSE,                //打ち消し線
		SHIFTJIS_CHARSET,    //文字セット
		OUT_DEFAULT_PRECIS,    //出力精度
		CLIP_DEFAULT_PRECIS,//クリッピング精度
		PROOF_QUALITY,        //出力品質
		FIXED_PITCH | FF_MODERN,//ピッチとファミリー
		face);    //書体名
	return hFont;
}

//画面サイズのやつのやつ
static LRESULT CALLBACK DlgProcTab1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	HBRUSH bkColorBrush = CreateSolidBrush(RGB(255, 255, 255));//背景色のブラシを用意する
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_DSIZE_RADIO1, IDC_DSIZE_RADIO5, dialogSetting.resolution);
		{//スコープが面倒なのでブロック化
		 //コンボボックスの選択している値より画面サイズの表示
			TCHAR txt[30] = _T("");
			int X = 0, Y = 0, Clolr = 0;
			GetDefaultState(&X, &Y, &Clolr);//ウィンドウの大きさ取得
			_stprintf_s(txt, _T("疑似フルスクリーン[%dx%d]"), X, Y);//ダイアログに書く文字列(ウィンドウサイズ)の生成
			SetDlgItemText(hDlg, IDC_DSIZE_RADIO4, txt);
		}
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_DSIZE_RADIO1)) {
			dialogSetting.resolution = IDC_DSIZE_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DSIZE_RADIO2)) {
			dialogSetting.resolution = IDC_DSIZE_RADIO2;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DSIZE_RADIO3)) {
			dialogSetting.resolution = IDC_DSIZE_RADIO3;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DSIZE_RADIO4)) {//疑似フルスクリーン
			dialogSetting.resolution = IDC_DSIZE_RADIO4;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DSIZE_RADIO5)) {//フルスクリーン
			dialogSetting.resolution = IDC_DSIZE_RADIO5;
		}
		else {//どれでもないとき
			dialogSetting.resolution = IDC_DSIZE_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_DSIZE_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DSIZE_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DSIZE_RADIO3)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DSIZE_RADIO4)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DSIZE_RADIO5)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//描画間隔のやつのやつ
static LRESULT CALLBACK DlgProcTab2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_DRAWING_INTERVAL1, IDC_DRAWING_INTERVAL4, dialogSetting.Drawing_interval);
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_DRAWING_INTERVAL1)) {
			dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DRAWING_INTERVAL2)) {
			dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL2;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DRAWING_INTERVAL3)) {
			dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL3;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_DRAWING_INTERVAL4)) {
			dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL4;
		}
		else {//どれでもないとき
			dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_DRAWING_INTERVAL1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DRAWING_INTERVAL2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DRAWING_INTERVAL3)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_DRAWING_INTERVAL4)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//垂直同期のやつのやつ
static LRESULT CALLBACK DlgProcTab3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_VSYNC_RADIO1, IDC_VSYNC_RADIO2, dialogSetting.VSync);
		if (GetRefreshRate() != 60 && dialogSetting.Thread == IDC_THREAD_RADIO2) {//ディスプレイのリフレッシュレートが60以外でかつシングルスレッド動作の時
			EnableWindow(GetDlgItem(hDlg, IDC_VSYNC_RADIO1), FALSE);//垂直同期を選択不可にする
			CheckRadioButton(hDlg, IDC_VSYNC_RADIO1, IDC_VSYNC_RADIO2, IDC_VSYNC_RADIO2);
			dialogSetting.VSync = IDC_VSYNC_RADIO2;
		}
		break;
	case WM_SHOWWINDOW://ウィンドウの可視状態が変更された時(多分)
		if (GetRefreshRate() != 60 && dialogSetting.Thread == IDC_THREAD_RADIO2) {//ディスプレイのリフレッシュレートが60以外でかつシングルスレッド動作の時
			EnableWindow(GetDlgItem(hDlg, IDC_VSYNC_RADIO1), FALSE);//垂直同期を選択不可にする
			CheckRadioButton(hDlg, IDC_VSYNC_RADIO1, IDC_VSYNC_RADIO2, IDC_VSYNC_RADIO2);
			dialogSetting.VSync = IDC_VSYNC_RADIO2;
		}
		else {
			EnableWindow(GetDlgItem(hDlg, IDC_VSYNC_RADIO1), TRUE);//垂直同期を選択可にする
		}
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_VSYNC_RADIO1)) {
			dialogSetting.VSync = IDC_VSYNC_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_VSYNC_RADIO2)) {
			dialogSetting.VSync = IDC_VSYNC_RADIO2;
		}
		else {//どれでもないとき
			dialogSetting.VSync = IDC_VSYNC_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_VSYNC_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_VSYNC_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//画面消去のやつのやつ
static LRESULT CALLBACK DlgProcTab4(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_CLEAR_RADIO1, IDC_CLEAR_RADIO2, dialogSetting.Clear);
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_CLEAR_RADIO1)) {
			dialogSetting.Clear = IDC_CLEAR_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_CLEAR_RADIO2)) {
			dialogSetting.Clear = IDC_CLEAR_RADIO2;
		}
		else {//どれでもないとき
			dialogSetting.Clear = IDC_CLEAR_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_CLEAR_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_CLEAR_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//マウスカーソルのやつのやつ
static LRESULT CALLBACK DlgProcTab5(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_CURSOR_RADIO1, IDC_CURSOR_RADIO2, dialogSetting.Cursor);
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_CURSOR_RADIO1)) {
			dialogSetting.Cursor = IDC_CURSOR_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_CURSOR_RADIO2)) {
			dialogSetting.Cursor = IDC_CURSOR_RADIO2;
		}
		else {//どれでもないとき
			dialogSetting.Cursor = IDC_CURSOR_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_CURSOR_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_CURSOR_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//マルチスレッドのやつのやつ
static LRESULT CALLBACK DlgProcTab6(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_THREAD_RADIO1, IDC_THREAD_RADIO2, dialogSetting.Thread);
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_THREAD_RADIO1)) {
			dialogSetting.Thread = IDC_THREAD_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_THREAD_RADIO2)) {
			dialogSetting.Thread = IDC_THREAD_RADIO2;
		}
		else {//どれでもないとき
			dialogSetting.Thread = IDC_THREAD_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_THREAD_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_THREAD_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//テクスチャ分割のやつのやつ
static LRESULT CALLBACK DlgProcTab7(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_TEXTURE_RADIO1, IDC_TEXTURE_RADIO2, dialogSetting.Texture);
		break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_TEXTURE_RADIO1)) {
			dialogSetting.Texture = IDC_TEXTURE_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_TEXTURE_RADIO2)) {
			dialogSetting.Texture = IDC_TEXTURE_RADIO2;
		}
		else {//どれでもないとき
			dialogSetting.Texture = IDC_TEXTURE_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_TEXTURE_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_TEXTURE_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//アナログスティックのやつのやつ
static LRESULT CALLBACK DlgProcTab8(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		//項目の選択肢の選択
		//初期値の設定
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO3, dialogSetting.analogstick);
		if (dialogSetting.Joy_Type == 0) {//ジョイパッド無効の時
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO1), false);
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO2), false);
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO3), false);
		}
		break;
	case WM_SHOWWINDOW:
	{
		if (dialogSetting.Joy_Type == 0) {//ジョイパッド無効の時
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO1), false);
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO2), false);
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO3), false);
		}
		else {
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO1), true);
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO2), true);
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO3), true);
		}
	}
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (IsDlgButtonChecked(hDlg, IDC_RADIO1)) {
			dialogSetting.analogstick = IDC_RADIO1;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_RADIO2)) {
			dialogSetting.analogstick = IDC_RADIO2;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_RADIO3)) {
			dialogSetting.analogstick = IDC_RADIO3;
		}
		else {//どれでもないとき
			dialogSetting.analogstick = IDC_RADIO1;
		}
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_RADIO1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_RADIO2)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_RADIO3)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) {
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//キーバインド設定のやつのやつ
static LRESULT CALLBACK DlgProcTab9(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	//Log_print(LOG_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_INFORMAL, _T("%x(16進数)"), msg);

	switch (msg) {
	case WM_INITDIALOG:
	{
		int state = (dialogSetting.Key_Enable) ? BST_UNCHECKED : BST_CHECKED;
		SendMessage(GetDlgItem(hDlg, IDC_CHECK20), BM_SETCHECK, state, 0);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK2), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK3), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK4), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK5), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK6), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK7), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK8), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK9), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK10), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK11), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK12), dialogSetting.Key_Enable);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK13), false);
		EnableWindow(GetDlgItem(hDlg, IDC_CHECK14), dialogSetting.Key_Enable);
		SetDlgItemText(hDlg, IDC_CHECK1, ConvertVerKey(dialogSetting.Key_RotateL));
		SetDlgItemText(hDlg, IDC_CHECK2, ConvertVerKey(dialogSetting.Key_RotateL2));
		SetDlgItemText(hDlg, IDC_CHECK3, ConvertVerKey(dialogSetting.Key_RotateR));
		SetDlgItemText(hDlg, IDC_CHECK4, ConvertVerKey(dialogSetting.Key_RotateR2));
		SetDlgItemText(hDlg, IDC_CHECK5, ConvertVerKey(dialogSetting.Key_UP));
		SetDlgItemText(hDlg, IDC_CHECK6, ConvertVerKey(dialogSetting.Key_UP2));
		SetDlgItemText(hDlg, IDC_CHECK7, ConvertVerKey(dialogSetting.Key_DOWN));
		SetDlgItemText(hDlg, IDC_CHECK8, ConvertVerKey(dialogSetting.Key_DOWN2));
		SetDlgItemText(hDlg, IDC_CHECK9, ConvertVerKey(dialogSetting.Key_ROGHT));
		SetDlgItemText(hDlg, IDC_CHECK10, ConvertVerKey(dialogSetting.Key_ROGHT2));
		SetDlgItemText(hDlg, IDC_CHECK11, ConvertVerKey(dialogSetting.Key_LEFT));
		SetDlgItemText(hDlg, IDC_CHECK12, ConvertVerKey(dialogSetting.Key_LEFT2));
		SetDlgItemText(hDlg, IDC_CHECK13, ConvertVerKey(dialogSetting.Key_PAUSE));
		SetDlgItemText(hDlg, IDC_CHECK14, ConvertVerKey(dialogSetting.Key_PAUSE2));

	}
	break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたときでとりあえずイベント
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK1, ConvertVerKey(dialogSetting.Key_RotateL));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK2, ConvertVerKey(dialogSetting.Key_RotateL2));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK3), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK3, ConvertVerKey(dialogSetting.Key_RotateR));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK4), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK4, ConvertVerKey(dialogSetting.Key_RotateR2));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK5), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK5, ConvertVerKey(dialogSetting.Key_UP));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK6), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK6, ConvertVerKey(dialogSetting.Key_UP2));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK7), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK7, ConvertVerKey(dialogSetting.Key_DOWN));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK8), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK8, ConvertVerKey(dialogSetting.Key_DOWN2));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK9), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK9, ConvertVerKey(dialogSetting.Key_ROGHT));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK10), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK10, ConvertVerKey(dialogSetting.Key_ROGHT2));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK11), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK11, ConvertVerKey(dialogSetting.Key_LEFT));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK12), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK12, ConvertVerKey(dialogSetting.Key_LEFT2));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK13), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK13, ConvertVerKey(dialogSetting.Key_PAUSE));
			}
			if ((HWND)lParam != GetDlgItem(hDlg, keyConfigType)) {//自身の場合は無視する
				SendMessage(GetDlgItem(hDlg, IDC_CHECK14), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK14, ConvertVerKey(dialogSetting.Key_PAUSE2));
			}
		}
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK1)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK1;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK1, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK2)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK2;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK2, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK3)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK3;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK3, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK4)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK4;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK4, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK5)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK5;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK5, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK6)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK6;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK6, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK7)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK7;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK7, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK8)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK8;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK8, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK9)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK9;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK9, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK10)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK10;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK10, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK11)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK11;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK11, _T("入力中･･･"));
				return 0;
			}
		}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK12)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK12;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK12, _T("入力中･･･"));
				return 0;
			}
		}
		//else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK13)) {//ボタンのイベント
		//	if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
		//		keyConfigType = IDC_CHECK13;
		//		keyConfigmode = true;
		//		SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
		//		SetDlgItemText(hDlg, IDC_CHECK13, _T("入力中･･･"));
		//		return 0;
		//	}
		//}
		else if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK14)) {//ボタンのイベント
			if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
				keyConfigType = IDC_CHECK14;
				keyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, IDC_CHECK14, _T("入力中･･･"));
				return 0;
			}
		}

		if ((HWND)lParam == GetDlgItem(hDlg, IDC_CHECK20)) {
			dialogSetting.Key_Enable = (SendMessage(GetDlgItem(hDlg, IDC_CHECK20), BM_GETCHECK, 0, 0) == BST_UNCHECKED) ? true : false;//チェック項目の状態の保存
																																	   //ボタンの有効状態の設定
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK2), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK3), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK4), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK5), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK6), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK7), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK8), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK9), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK10), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK11), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK12), dialogSetting.Key_Enable);
			//EnableWindow(GetDlgItem(hDlg, IDC_CHECK13), dialogSetting.Key_Enable);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK14), dialogSetting.Key_Enable);

		}
		break;
	case WM_SHOWWINDOW:
	{
		SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK1, ConvertVerKey(dialogSetting.Key_RotateL));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK2, ConvertVerKey(dialogSetting.Key_RotateL2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK3), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK3, ConvertVerKey(dialogSetting.Key_RotateR));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK4), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK4, ConvertVerKey(dialogSetting.Key_RotateR2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK5), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK5, ConvertVerKey(dialogSetting.Key_UP));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK6), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK6, ConvertVerKey(dialogSetting.Key_UP2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK7), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK7, ConvertVerKey(dialogSetting.Key_DOWN));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK8), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK8, ConvertVerKey(dialogSetting.Key_DOWN2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK9), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK9, ConvertVerKey(dialogSetting.Key_ROGHT));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK10), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK10, ConvertVerKey(dialogSetting.Key_ROGHT2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK11), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK11, ConvertVerKey(dialogSetting.Key_LEFT));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK12), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK12, ConvertVerKey(dialogSetting.Key_LEFT2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK13), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK13, ConvertVerKey(dialogSetting.Key_PAUSE));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK14), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK14, ConvertVerKey(dialogSetting.Key_PAUSE2));
		keyConfigType = 0;
		keyConfigmode = false;
	}
	break;
	case WM_TIMER:
		break;
	case WM_SETFOCUS:
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT2)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT3)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT4)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT5)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT6)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT7)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT8)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_CHECK20)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_KEYDOWN:
	{
		int state = lParam & 0x40000000;//31ビット目を抜き出し
		if (keyConfigmode == false)	break;//キー入力モードで無い時は何もしない
		if (state)	break;//直前もキーが押された状態なら無視
		if (keyConfigType == 0)	break;//キー入力が終わっている
		if (wParam == VK_RETURN) break;//エンターキーもだめ
		if (wParam == VK_SPACE) break;//スペースキーもだめ
		if (wParam == VK_ADD) break;//+キーもだめ
		if (wParam == VK_SHIFT) {//シフトキーが押されたとき
								 //左右どちらのキーか判別する
			if (GetKeyState(VK_LSHIFT) & 0x8000) {//左シフトキーが押されている
				wParam = VK_LSHIFT;//左シフトキーが押されていたことにする
			}
			else {
				wParam = VK_RSHIFT;//右シフトキーが押されていたことにする
			}
		}
		else if (wParam == VK_CONTROL) {
			//左右どちらのキーか判別する
			if (GetKeyState(VK_LCONTROL) & 0x8000) {//左シフトキーが押されている
				wParam = VK_LCONTROL;//左Ctrlが押されていたことにする
			}
			else {
				wParam = VK_RCONTROL;//右Ctrが押されていたことにする
			}
		}
		if (CheckDouble(keyConfigType, wParam)) break;//キー重複もダメ
		if (ConvertVirtualKeyToKeyCode((int)wParam) == 65535)	break;//DXライブラリのキーに変換できないときは無視
		SetDlgItemText(hDlg, keyConfigType, ConvertVerKey(wParam));
		SendMessage(GetDlgItem(hDlg, keyConfigType), BM_SETCHECK, BST_UNCHECKED, 0);
		switch (keyConfigType) {
		case IDC_CHECK1://落下するブロックを反時計回りに回転させる
			dialogSetting.Key_RotateL = wParam;
			break;
		case IDC_CHECK2://落下するブロックを反時計回りに回転させる2
			dialogSetting.Key_RotateL2 = wParam;
			break;
		case IDC_CHECK3://落下するブロックを時計回りに回転させる
			dialogSetting.Key_RotateR = wParam;
			break;
		case IDC_CHECK4://落下するブロックを時計回りに回転させる2
			dialogSetting.Key_RotateR2 = wParam;
			break;
		case IDC_CHECK5://項目選択:上
			dialogSetting.Key_UP = wParam;
			break;
		case IDC_CHECK6://項目選択:上2
			dialogSetting.Key_UP2 = wParam;
			break;
		case IDC_CHECK7://項目選択:下/落下するブロックの加速
			dialogSetting.Key_DOWN = wParam;
			break;
		case IDC_CHECK8://項目選択:下/落下するブロックの加速2
			dialogSetting.Key_DOWN2 = wParam;
			break;
		case IDC_CHECK9://項目選択:右/落下するブロックの右移動
			dialogSetting.Key_ROGHT = wParam;
			break;
		case IDC_CHECK10://項目選択:右/落下するブロックの右移動2
			dialogSetting.Key_ROGHT2 = wParam;
			break;
		case IDC_CHECK11://項目選択:左/落下するブロックの左移動
			dialogSetting.Key_LEFT = wParam;
			break;
		case IDC_CHECK12://項目選択:左/落下するブロックの左移動2
			dialogSetting.Key_LEFT2 = wParam;
			break;
		case IDC_CHECK13://キャンセル/ポーズ
			dialogSetting.Key_PAUSE = wParam;
			break;
		case IDC_CHECK14://キャンセル/ポーズ2
			dialogSetting.Key_PAUSE2 = wParam;
			break;
		}
		keyConfigType = 0;
	}
	break;
	case WM_KEYUP:
		if (wParam == VK_RETURN) break;//エンターキーもだめ
		if (wParam == VK_SPACE) break;//スペースキーもだめ
		if (wParam == VK_ADD) break;//+キーもだめ
		if (CheckDouble(keyConfigType, wParam)) break;//キー重複もダメ
		if (ConvertVirtualKeyToKeyCode((int)wParam) == 65535)	break;//DXライブラリのキーに変換できないときは無視
		SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK1, ConvertVerKey(dialogSetting.Key_RotateL));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK2, ConvertVerKey(dialogSetting.Key_RotateL2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK3), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK3, ConvertVerKey(dialogSetting.Key_RotateR));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK4), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK4, ConvertVerKey(dialogSetting.Key_RotateR2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK5), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK5, ConvertVerKey(dialogSetting.Key_UP));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK6), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK6, ConvertVerKey(dialogSetting.Key_UP2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK7), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK7, ConvertVerKey(dialogSetting.Key_DOWN));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK8), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK8, ConvertVerKey(dialogSetting.Key_DOWN2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK9), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK9, ConvertVerKey(dialogSetting.Key_ROGHT));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK10), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK10, ConvertVerKey(dialogSetting.Key_ROGHT2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK11), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK11, ConvertVerKey(dialogSetting.Key_LEFT));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK12), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK12, ConvertVerKey(dialogSetting.Key_LEFT2));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK13), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK13, ConvertVerKey(dialogSetting.Key_PAUSE));
		SendMessage(GetDlgItem(hDlg, IDC_CHECK14), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, IDC_CHECK14, ConvertVerKey(dialogSetting.Key_PAUSE2));
		keyConfigmode = false;
		break;
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//キーバインド設定のやつのやつ2
static LRESULT CALLBACK DlgProcTab10(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	//Log_print(LOG_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_INFORMAL, _T("%x(16進数)"), msg);

	switch (msg) {
	case WM_INITDIALOG:
	{
		TCHAR cmbstr[][30] = { _T("パッド無効"), _T("PAD1使用"), _T("PAD2使用"), _T("PAD3使用"), _T("PAD4使用"), _T("PAD5使用"), _T("PAD6使用"), _T("PAD7使用"), _T("PAD8使用"), _T("PAD9使用"), _T("PAD10使用"), _T("PAD11使用"), _T("PAD12使用"), _T("PAD13使用"), _T("PAD14使用"), _T("PAD15使用"), _T("PAD16使用") };
		for (int i = 0; i < ARRAY_LENGTH(cmbstr); i++) {
			SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)cmbstr[i]);//コンボボックスにデータの追加をする
		}
		SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, dialogSetting.Joy_Type, 0);//コンボボックスにデータの追加をする

																						   //パッド無効の場合は選択肢を選べないようにする
		{
			bool en = (dialogSetting.Joy_Type == 0) ? false : true;
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK2), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK3), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK4), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK5), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK6), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK7), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK8), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK9), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK10), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK11), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK12), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK13), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK14), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK15), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK16), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK17), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK18), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK19), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK20), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK21), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK22), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK23), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK24), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK25), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK26), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK27), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK28), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK29), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK30), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK31), en);
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK32), en);
		}

		//現在の設定を反映させる
		{
			SetDlgItemText(hDlg, IDC_CHECK1, ConvertVerJoyKey(dialogSetting.Joy_RotateL[0]));
			SetDlgItemText(hDlg, IDC_CHECK2, ConvertVerJoyKey(dialogSetting.Joy_RotateL[1]));
			SetDlgItemText(hDlg, IDC_CHECK3, ConvertVerJoyKey(dialogSetting.Joy_RotateL[2]));
			SetDlgItemText(hDlg, IDC_CHECK4, ConvertVerJoyKey(dialogSetting.Joy_RotateL[3]));

			SetDlgItemText(hDlg, IDC_CHECK5, ConvertVerJoyKey(dialogSetting.Joy_RotateR[0]));
			SetDlgItemText(hDlg, IDC_CHECK6, ConvertVerJoyKey(dialogSetting.Joy_RotateR[1]));
			SetDlgItemText(hDlg, IDC_CHECK7, ConvertVerJoyKey(dialogSetting.Joy_RotateR[2]));
			SetDlgItemText(hDlg, IDC_CHECK8, ConvertVerJoyKey(dialogSetting.Joy_RotateR[3]));

			SetDlgItemText(hDlg, IDC_CHECK9, ConvertVerJoyKey(dialogSetting.Joy_UP[0]));
			SetDlgItemText(hDlg, IDC_CHECK10, ConvertVerJoyKey(dialogSetting.Joy_UP[1]));
			SetDlgItemText(hDlg, IDC_CHECK11, ConvertVerJoyKey(dialogSetting.Joy_UP[2]));
			SetDlgItemText(hDlg, IDC_CHECK12, ConvertVerJoyKey(dialogSetting.Joy_UP[3]));

			SetDlgItemText(hDlg, IDC_CHECK13, ConvertVerJoyKey(dialogSetting.Joy_DOWN[0]));
			SetDlgItemText(hDlg, IDC_CHECK14, ConvertVerJoyKey(dialogSetting.Joy_DOWN[1]));
			SetDlgItemText(hDlg, IDC_CHECK15, ConvertVerJoyKey(dialogSetting.Joy_DOWN[2]));
			SetDlgItemText(hDlg, IDC_CHECK16, ConvertVerJoyKey(dialogSetting.Joy_DOWN[3]));

			SetDlgItemText(hDlg, IDC_CHECK17, ConvertVerJoyKey(dialogSetting.Joy_ROGHT[0]));
			SetDlgItemText(hDlg, IDC_CHECK18, ConvertVerJoyKey(dialogSetting.Joy_ROGHT[1]));
			SetDlgItemText(hDlg, IDC_CHECK19, ConvertVerJoyKey(dialogSetting.Joy_ROGHT[2]));
			SetDlgItemText(hDlg, IDC_CHECK20, ConvertVerJoyKey(dialogSetting.Joy_ROGHT[3]));

			SetDlgItemText(hDlg, IDC_CHECK21, ConvertVerJoyKey(dialogSetting.Joy_LEFT[0]));
			SetDlgItemText(hDlg, IDC_CHECK22, ConvertVerJoyKey(dialogSetting.Joy_LEFT[1]));
			SetDlgItemText(hDlg, IDC_CHECK23, ConvertVerJoyKey(dialogSetting.Joy_LEFT[2]));
			SetDlgItemText(hDlg, IDC_CHECK24, ConvertVerJoyKey(dialogSetting.Joy_LEFT[3]));

			SetDlgItemText(hDlg, IDC_CHECK25, ConvertVerJoyKey(dialogSetting.Joy_PAUSE[0]));
			SetDlgItemText(hDlg, IDC_CHECK26, ConvertVerJoyKey(dialogSetting.Joy_PAUSE[1]));
			SetDlgItemText(hDlg, IDC_CHECK27, ConvertVerJoyKey(dialogSetting.Joy_PAUSE[2]));
			SetDlgItemText(hDlg, IDC_CHECK28, ConvertVerJoyKey(dialogSetting.Joy_PAUSE[3]));

			SetDlgItemText(hDlg, IDC_CHECK29, ConvertVerJoyKey(dialogSetting.Joy_ENTER[0]));
			SetDlgItemText(hDlg, IDC_CHECK30, ConvertVerJoyKey(dialogSetting.Joy_ENTER[1]));
			SetDlgItemText(hDlg, IDC_CHECK31, ConvertVerJoyKey(dialogSetting.Joy_ENTER[2]));
			SetDlgItemText(hDlg, IDC_CHECK32, ConvertVerJoyKey(dialogSetting.Joy_ENTER[3]));
		}
	}
	break;
	case WM_COMMAND:
		//ウィンドウ関連のチェック項目取得
		//ボタンをクリックしたときでとりあえずイベント
		if (HIWORD(wParam) == BN_CLICKED || HIWORD(wParam) == CBN_SELCHANGE) {
			//現在選択しているもの以外のボタンを初期状態に戻す
			SetJoyNomalText(hDlg, lParam, IDC_CHECK1);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK2);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK3);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK4);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK5);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK6);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK7);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK8);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK9);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK10);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK11);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK12);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK13);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK14);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK15);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK16);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK17);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK18);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK19);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK20);

			SetJoyNomalText(hDlg, lParam, IDC_CHECK21);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK22);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK23);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK24);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK25);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK26);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK27);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK28);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK29);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK30);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK31);
			SetJoyNomalText(hDlg, lParam, IDC_CHECK32);
		}

		//各ボタンのイベント処理
		{
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK1);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK2);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK3);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK4);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK5);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK6);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK7);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK8);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK9);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK10);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK11);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK12);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK13);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK14);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK15);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK16);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK17);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK18);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK19);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK20);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK21);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK22);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK23);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK24);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK25);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK26);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK27);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK28);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK29);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK30);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK31);
			EnentJoySetButtonChange(hDlg, wParam, lParam, IDC_CHECK32);
		}

		if ((HWND)lParam == GetDlgItem(hDlg, IDC_COMBO1)) {
			if (HIWORD(wParam) == CBN_SELCHANGE) {//コンボボックスの選択が変更されたとき
				dialogSetting.Joy_Type = (unsigned int)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);//コンボボックスの選択項目の取得

																													 //パッド無効の場合は選択肢を選べないようにする
				{
					bool en = (dialogSetting.Joy_Type == 0) ? false : true;
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK2), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK3), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK4), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK5), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK6), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK7), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK8), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK9), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK10), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK11), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK12), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK13), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK14), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK15), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK16), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK17), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK18), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK19), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK20), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK21), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK22), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK23), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK24), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK25), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK26), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK27), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK28), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK29), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK30), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK31), en);
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK32), en);
				}
			}
		}
		break;
	case WM_SHOWWINDOW:
	{
		//現在選択しているものも含めてボタンを初期状態に戻す(無理矢理関数内のIF分を通過させます)
		joyConfigType = 0;
		SetJoyNomalText(hDlg, -1, IDC_CHECK1);
		SetJoyNomalText(hDlg, -1, IDC_CHECK2);
		SetJoyNomalText(hDlg, -1, IDC_CHECK3);
		SetJoyNomalText(hDlg, -1, IDC_CHECK4);
		SetJoyNomalText(hDlg, -1, IDC_CHECK5);
		SetJoyNomalText(hDlg, -1, IDC_CHECK6);
		SetJoyNomalText(hDlg, -1, IDC_CHECK7);
		SetJoyNomalText(hDlg, -1, IDC_CHECK8);
		SetJoyNomalText(hDlg, -1, IDC_CHECK9);
		SetJoyNomalText(hDlg, -1, IDC_CHECK10);
		SetJoyNomalText(hDlg, -1, IDC_CHECK11);
		SetJoyNomalText(hDlg, -1, IDC_CHECK12);
		SetJoyNomalText(hDlg, -1, IDC_CHECK13);
		SetJoyNomalText(hDlg, -1, IDC_CHECK14);
		SetJoyNomalText(hDlg, -1, IDC_CHECK15);
		SetJoyNomalText(hDlg, -1, IDC_CHECK16);
		SetJoyNomalText(hDlg, -1, IDC_CHECK17);
		SetJoyNomalText(hDlg, -1, IDC_CHECK18);
		SetJoyNomalText(hDlg, -1, IDC_CHECK19);
		SetJoyNomalText(hDlg, -1, IDC_CHECK20);

		SetJoyNomalText(hDlg, -1, IDC_CHECK21);
		SetJoyNomalText(hDlg, -1, IDC_CHECK22);
		SetJoyNomalText(hDlg, -1, IDC_CHECK23);
		SetJoyNomalText(hDlg, -1, IDC_CHECK24);
		SetJoyNomalText(hDlg, -1, IDC_CHECK25);
		SetJoyNomalText(hDlg, -1, IDC_CHECK26);
		SetJoyNomalText(hDlg, -1, IDC_CHECK27);
		SetJoyNomalText(hDlg, -1, IDC_CHECK28);
		SetJoyNomalText(hDlg, -1, IDC_CHECK29);
		SetJoyNomalText(hDlg, -1, IDC_CHECK30);
		SetJoyNomalText(hDlg, -1, IDC_CHECK31);
		SetJoyNomalText(hDlg, -1, IDC_CHECK32);
		joyConfigmode = false;
	}
	break;
	case WM_TIMER:
		break;
	case WM_SETFOCUS:
		break;
	case WM_CTLCOLORSTATIC:
	{
		HDC hDC = (HDC)wParam;
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == GetDlgItem(hDlg, IDC_STATIC)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT1)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT2)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT3)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT4)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT5)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT6)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT7)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT8)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT9)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT10)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_CHECK20)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		else if (hCtrl == GetDlgItem(hDlg, IDC_STATICTEXT11)) //ラジオボタンのID
		{
			SetBkMode(hDC, TRANSPARENT);	// 背景を透過
			return (LRESULT)bkColorBrush;	// 背景色の色
		}
		break;

	}
	case WM_USER_JOYDOWN:
	{
		if (joyConfigmode == false)	break;//キー入力モードで無い時は何もしない
		if (joyConfigType == 0)	break;//キー入力が終わっている
		CheckDoubleJoy(joyConfigType, SetBitRight(lParam));//キー重複は上書きする
														   //設定の記録
		int *p = getJoySettings(joyConfigType);
		*p = SetBitRight(lParam);
		joyConfigType = 0;
		joyConfigmode = false;
		SetJoyNomalText(hDlg, -1, IDC_CHECK1);
		SetJoyNomalText(hDlg, -1, IDC_CHECK2);
		SetJoyNomalText(hDlg, -1, IDC_CHECK3);
		SetJoyNomalText(hDlg, -1, IDC_CHECK4);

		SetJoyNomalText(hDlg, -1, IDC_CHECK5);
		SetJoyNomalText(hDlg, -1, IDC_CHECK6);
		SetJoyNomalText(hDlg, -1, IDC_CHECK7);
		SetJoyNomalText(hDlg, -1, IDC_CHECK8);

		SetJoyNomalText(hDlg, -1, IDC_CHECK9);
		SetJoyNomalText(hDlg, -1, IDC_CHECK10);
		SetJoyNomalText(hDlg, -1, IDC_CHECK11);
		SetJoyNomalText(hDlg, -1, IDC_CHECK12);

		SetJoyNomalText(hDlg, -1, IDC_CHECK13);
		SetJoyNomalText(hDlg, -1, IDC_CHECK14);
		SetJoyNomalText(hDlg, -1, IDC_CHECK15);
		SetJoyNomalText(hDlg, -1, IDC_CHECK16);

		SetJoyNomalText(hDlg, -1, IDC_CHECK17);
		SetJoyNomalText(hDlg, -1, IDC_CHECK18);
		SetJoyNomalText(hDlg, -1, IDC_CHECK19);
		SetJoyNomalText(hDlg, -1, IDC_CHECK20);

		SetJoyNomalText(hDlg, -1, IDC_CHECK21);
		SetJoyNomalText(hDlg, -1, IDC_CHECK22);
		SetJoyNomalText(hDlg, -1, IDC_CHECK23);
		SetJoyNomalText(hDlg, -1, IDC_CHECK24);

		SetJoyNomalText(hDlg, -1, IDC_CHECK25);
		SetJoyNomalText(hDlg, -1, IDC_CHECK26);
		SetJoyNomalText(hDlg, -1, IDC_CHECK27);
		SetJoyNomalText(hDlg, -1, IDC_CHECK28);

		SetJoyNomalText(hDlg, -1, IDC_CHECK29);
		SetJoyNomalText(hDlg, -1, IDC_CHECK30);
		SetJoyNomalText(hDlg, -1, IDC_CHECK31);
		SetJoyNomalText(hDlg, -1, IDC_CHECK32);
	}
	break;
	case WM_CTLCOLORDLG:
		return (LRESULT)bkColorBrush;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);

}

//ダイアログ選択項目のセーブデータの整合性の確認(前提として選択項目のIDが連続している)
static void VerifySaveData() {
	//画面サイズ
	int No = dialogSetting.resolution - IDC_DSIZE_RADIO1;
	if (No < 0 || (IDC_DSIZE_RADIO5 - IDC_DSIZE_RADIO1) < No)	dialogSetting.resolution = IDC_DSIZE_RADIO1;//整合性が合っていない場合は規定値で書き換え
																											//描画間隔
	No = dialogSetting.Drawing_interval - IDC_DRAWING_INTERVAL1;
	if (No < 0 || (IDC_DRAWING_INTERVAL4 - IDC_DRAWING_INTERVAL1) < No)	dialogSetting.Drawing_interval = IDC_DRAWING_INTERVAL1;//整合性が合っていない場合は規定値で書き換え
																															   //垂直同期
	No = dialogSetting.VSync - IDC_VSYNC_RADIO1;
	if (No < 0 || (IDC_VSYNC_RADIO2 - IDC_VSYNC_RADIO1) < No)	dialogSetting.VSync = IDC_VSYNC_RADIO1;//整合性が合っていない場合は規定値で書き換え
																									   //画面消去
	No = dialogSetting.Clear - IDC_CLEAR_RADIO1;
	if (No < 0 || (IDC_CLEAR_RADIO2 - IDC_CLEAR_RADIO1) < No)	dialogSetting.Clear = IDC_CLEAR_RADIO1;//整合性が合っていない場合は規定値で書き換え
																									   //マウスカーソル
	No = dialogSetting.Cursor - IDC_CURSOR_RADIO1;
	if (No < 0 || (IDC_CURSOR_RADIO2 - IDC_CURSOR_RADIO1) < No)	dialogSetting.Cursor = IDC_CURSOR_RADIO1;//整合性が合っていない場合は規定値で書き換え
																										 //マルチスレッド
	No = dialogSetting.Thread - IDC_THREAD_RADIO1;
	if (No < 0 || (IDC_THREAD_RADIO2 - IDC_THREAD_RADIO1) < No)	dialogSetting.Thread = IDC_THREAD_RADIO1;//整合性が合っていない場合は規定値で書き換え
																										 //テクスチャ分割
	No = dialogSetting.Texture - IDC_TEXTURE_RADIO1;
	if (No < 0 || (IDC_TEXTURE_RADIO2 - IDC_TEXTURE_RADIO1) < No)	dialogSetting.Texture = IDC_TEXTURE_RADIO1;//整合性が合っていない場合は規定値で書き換え
	No = dialogSetting.analogstick - IDC_RADIO1;
	if (No < 0 || (IDC_RADIO3 - IDC_RADIO1) < No)	dialogSetting.analogstick = IDC_RADIO1;//整合性が合っていない場合は規定値で書き換え
																						   //キーコンフィグ
	dialogSetting.Key_Enable = (dialogSetting.Key_Enable) ? true : false;
	//DXライブラリのキーに変換できるかの確認(一応重複してても動くので確認しない)
	{
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateL) == 65535) {
			dialogSetting.Key_RotateL = 'Z';
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateL2) == 65535) {
			dialogSetting.Key_RotateL2 = 'Z';
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateR) == 65535) {
			dialogSetting.Key_RotateR = VK_SHIFT;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateR2) == 65535) {
			dialogSetting.Key_RotateR2 = VK_SHIFT;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_UP) == 65535) {
			dialogSetting.Key_UP = VK_UP;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_UP2) == 65535) {
			dialogSetting.Key_UP2 = VK_UP;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_DOWN) == 65535) {
			dialogSetting.Key_DOWN = VK_DOWN;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_DOWN2) == 65535) {
			dialogSetting.Key_DOWN2 = VK_DOWN;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_ROGHT) == 65535) {
			dialogSetting.Key_ROGHT = VK_RIGHT;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_ROGHT2) == 65535) {
			dialogSetting.Key_ROGHT2 = VK_RIGHT;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_LEFT) == 65535) {
			dialogSetting.Key_LEFT = VK_LEFT;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_LEFT2) == 65535) {
			dialogSetting.Key_LEFT2 = VK_LEFT;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_LEFT2) == 65535) {
			dialogSetting.Key_LEFT2 = VK_LEFT;
		}
		if (dialogSetting.Key_PAUSE != VK_ESCAPE) {//ここは絶対ESCキー
			dialogSetting.Key_PAUSE = VK_ESCAPE;
		}
		if (ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_PAUSE2) == 65535) {
			dialogSetting.Key_PAUSE2 = VK_ESCAPE;
		}
	}
	//ジョイパッド
	if (dialogSetting.Joy_Type < 0 || DX_INPUT_PAD16 < dialogSetting.Joy_Type)	dialogSetting.Joy_Type = 0;
	//ジョイパッドのキーが妥当かどうかの確認(32ビット目まで使ってるので右詰のみ行う)
	{
		for (int i = 0; i < 4; i++) dialogSetting.Joy_RotateL[i] = SetBitRight(dialogSetting.Joy_RotateL[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_RotateR[i] = SetBitRight(dialogSetting.Joy_RotateR[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_UP[i] = SetBitRight(dialogSetting.Joy_UP[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_DOWN[i] = SetBitRight(dialogSetting.Joy_DOWN[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_ROGHT[i] = SetBitRight(dialogSetting.Joy_ROGHT[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_LEFT[i] = SetBitRight(dialogSetting.Joy_LEFT[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_PAUSE[i] = SetBitRight(dialogSetting.Joy_PAUSE[i]);
		for (int i = 0; i < 4; i++) dialogSetting.Joy_ENTER[i] = SetBitRight(dialogSetting.Joy_ENTER[i]);
	}
}

//ボタンIDからジョイパッド設定項目のポインタを取得する
static int *getJoySettings(int ItemID) {
	switch (ItemID) {
	case IDC_CHECK1:	return &dialogSetting.Joy_RotateL[0];
	case IDC_CHECK2:	return &dialogSetting.Joy_RotateL[1];
	case IDC_CHECK3:	return &dialogSetting.Joy_RotateL[2];
	case IDC_CHECK4:	return &dialogSetting.Joy_RotateL[3];

	case IDC_CHECK5:	return &dialogSetting.Joy_RotateR[0];
	case IDC_CHECK6:	return &dialogSetting.Joy_RotateR[1];
	case IDC_CHECK7:	return &dialogSetting.Joy_RotateR[2];
	case IDC_CHECK8:	return &dialogSetting.Joy_RotateR[3];

	case IDC_CHECK9:	return &dialogSetting.Joy_UP[0];
	case IDC_CHECK10:	return &dialogSetting.Joy_UP[1];
	case IDC_CHECK11:	return &dialogSetting.Joy_UP[2];
	case IDC_CHECK12:	return &dialogSetting.Joy_UP[3];

	case IDC_CHECK13:	return &dialogSetting.Joy_DOWN[0];
	case IDC_CHECK14:	return &dialogSetting.Joy_DOWN[1];
	case IDC_CHECK15:	return &dialogSetting.Joy_DOWN[2];
	case IDC_CHECK16:	return &dialogSetting.Joy_DOWN[3];

	case IDC_CHECK17:	return &dialogSetting.Joy_ROGHT[0];
	case IDC_CHECK18:	return &dialogSetting.Joy_ROGHT[1];
	case IDC_CHECK19:	return &dialogSetting.Joy_ROGHT[2];
	case IDC_CHECK20:	return &dialogSetting.Joy_ROGHT[3];

	case IDC_CHECK21:	return &dialogSetting.Joy_LEFT[0];
	case IDC_CHECK22:	return &dialogSetting.Joy_LEFT[1];
	case IDC_CHECK23:	return &dialogSetting.Joy_LEFT[2];
	case IDC_CHECK24:	return &dialogSetting.Joy_LEFT[3];

	case IDC_CHECK25:	return &dialogSetting.Joy_PAUSE[0];
	case IDC_CHECK26:	return &dialogSetting.Joy_PAUSE[1];
	case IDC_CHECK27:	return &dialogSetting.Joy_PAUSE[2];
	case IDC_CHECK28:	return &dialogSetting.Joy_PAUSE[3];

	case IDC_CHECK29:	return &dialogSetting.Joy_ENTER[0];
	case IDC_CHECK30:	return &dialogSetting.Joy_ENTER[1];
	case IDC_CHECK31:	return &dialogSetting.Joy_ENTER[2];
	case IDC_CHECK32:	return &dialogSetting.Joy_ENTER[3];
	default:
		printLog_E(_T("ジョイパッドの設定項目が特定できませんでした(ID=%d)"), ItemID);
		return NULL;
	}
}

//現在のジョイパッド設定でボタンを更新する
static void SetJoyNomalText(HWND hDlg, LPARAM lParam, int ItemID) {
	if ((HWND)lParam != GetDlgItem(hDlg, joyConfigType)) {//自身の場合は無視する
		SendMessage(GetDlgItem(hDlg, ItemID), BM_SETCHECK, BST_UNCHECKED, 0);
		SetDlgItemText(hDlg, ItemID, ConvertVerJoyKey(*getJoySettings(ItemID)));
	}
}

//ジョイパッド設定のボタンが押されたときのイベント
static int EnentJoySetButtonChange(HWND hDlg, WPARAM wParam, LPARAM lParam, int ItemID) {
	if ((HWND)lParam == GetDlgItem(hDlg, ItemID)) {//ボタンのイベント
		if (HIWORD(wParam) == BN_CLICKED) {//ボタンをクリックしたとき
			switch (SendMessage(GetDlgItem(hDlg, ItemID), BM_GETCHECK, 0, 0)) {
			case BST_CHECKED:
			{
				//入力状態を終了し、項目の設定を削除する
				joyConfigType = 0;
				joyConfigmode = false;
				int *p = getJoySettings(ItemID);
				*p = 0;
				SendMessage(GetDlgItem(hDlg, ItemID), BM_SETCHECK, BST_UNCHECKED, 0);
				SetDlgItemText(hDlg, ItemID, ConvertVerJoyKey(*p));
			}
			break;
			case BST_UNCHECKED:
				joyConfigType = ItemID;
				joyConfigmode = true;
				SendMessage(GetDlgItem(hDlg, joyConfigType), BM_SETCHECK, BST_CHECKED, 0);
				SetDlgItemText(hDlg, ItemID, _T("入力中"));
				break;
			}
			return 1;
		}
	}
	return 0;
}

//仮想キーコードを文字列に変換する
static TCHAR *ConvertVerKey(WPARAM VkeyCode) {
	//vkey[仮想キーコード]="その内容を表す文字列");
	WPARAM VK = VkeyCode;
	TCHAR *vkey[500];

	vkey[0] = _T("NULL");
	vkey[1] = _T("[LBUTTON]");
	vkey[2] = _T("[RBUTTON]");
	vkey[3] = _T("[ScrollLock]");
	vkey[4] = _T("[MBUTTON]");
	vkey[5] = _T("[5]");
	vkey[6] = _T("[6]");
	vkey[7] = _T("[7]");
	vkey[8] = _T("[BS]");
	vkey[9] = _T("[TAB]");
	vkey[10] = _T("[10]");
	vkey[11] = _T("[11]");
	vkey[12] = _T("[CLEAR]");
	vkey[13] = _T("[Enter]");
	vkey[14] = _T("[14]");
	vkey[15] = _T("[15]");
	vkey[16] = _T("[Shift]");
	vkey[17] = _T("[Ctrl]");
	vkey[18] = _T("[Alt]");
	vkey[19] = _T("[Pause]");
	vkey[20] = _T("[CAPS]");
	vkey[21] = _T("[KANA]");
	vkey[22] = _T("[22]");
	vkey[23] = _T("[JUNJA]");
	vkey[24] = _T("[FINAL]");
	vkey[25] = _T("[ALT+半角/全角]");
	vkey[26] = _T("[26]");
	vkey[27] = _T("[Esc]");
	vkey[28] = _T("[前候補]");
	vkey[29] = _T("[無変換]");
	vkey[30] = _T("[ACCEPT]");
	vkey[31] = _T("[MODECHANGE]");
	vkey[32] = _T("[SPACE]");
	vkey[33] = _T("[PageUp]");
	vkey[34] = _T("[PageDown]");
	vkey[35] = _T("[END]");
	vkey[36] = _T("[HOME]");
	vkey[37] = _T("[LEFT]");
	vkey[38] = _T("[UP]");
	vkey[39] = _T("[RIGHT]");
	vkey[40] = _T("[DOWN]");
	vkey[41] = _T("[SELECT]");
	vkey[42] = _T("[PRINT]");
	vkey[43] = _T("[EXECUTE]");
	vkey[44] = _T("[PSc/SRq]");
	vkey[45] = _T("[INS]");
	vkey[46] = _T("[Del]");
	vkey[47] = _T("[HELP]");
	vkey[48] = _T("[KEY 0]");
	vkey[49] = _T("[KEY 1]");
	vkey[50] = _T("[KEY 2]");
	vkey[51] = _T("[KEY 3]");
	vkey[52] = _T("[KEY 4]");
	vkey[53] = _T("[KEY 5]");
	vkey[54] = _T("[KEY 6]");
	vkey[55] = _T("[KEY 7]");
	vkey[56] = _T("[KEY 8]");
	vkey[57] = _T("[KEY 9]");
	vkey[58] = _T("[58]");
	vkey[59] = _T("[59]");
	vkey[60] = _T("[60]");
	vkey[61] = _T("[61]");
	vkey[62] = _T("[62]");
	vkey[63] = _T("[63]");
	vkey[64] = _T("[64]");
	vkey[65] = _T("[A]");
	vkey[66] = _T("[B]");
	vkey[67] = _T("[C]");
	vkey[68] = _T("[D]");
	vkey[69] = _T("[E]");
	vkey[70] = _T("[F]");
	vkey[71] = _T("[G]");
	vkey[72] = _T("[H]");
	vkey[73] = _T("[I]");
	vkey[74] = _T("[J]");
	vkey[75] = _T("[K]");
	vkey[76] = _T("[L]");
	vkey[77] = _T("[M]");
	vkey[78] = _T("[N]");
	vkey[79] = _T("[O]");
	vkey[80] = _T("[P]");
	vkey[81] = _T("[Q]");
	vkey[82] = _T("[R]");
	vkey[83] = _T("[S]");
	vkey[84] = _T("[T]");
	vkey[85] = _T("[U]");
	vkey[86] = _T("[V]");
	vkey[87] = _T("[W]");
	vkey[88] = _T("[X]");
	vkey[89] = _T("[Y]");
	vkey[90] = _T("[Z]");
	vkey[91] = _T("[L Windowsキー]");
	vkey[92] = _T("[R Windowsキー]");
	vkey[93] = _T("[アプリケーション]");
	vkey[94] = _T("[94]");
	vkey[95] = _T("[95]");
	vkey[96] = _T("[NUM 0]");
	vkey[97] = _T("[NUM 1]");
	vkey[98] = _T("[NUM 2]");
	vkey[99] = _T("[NUM 3]");
	vkey[100] = _T("[NUM 4]");
	vkey[101] = _T("[NUM 5]");
	vkey[102] = _T("[NUM 6]");
	vkey[103] = _T("[NUM 7]");
	vkey[104] = _T("[NUM 8]");
	vkey[105] = _T("[NUM 9]");
	vkey[106] = _T("[*]");
	vkey[107] = _T("[+]");
	vkey[108] = _T("[SEP]");
	vkey[109] = _T("[-]");
	vkey[110] = _T("[.]");
	vkey[111] = _T("[/]");
	vkey[112] = _T("[F1]");
	vkey[113] = _T("[F2]");
	vkey[114] = _T("[F3]");
	vkey[115] = _T("[F4]");
	vkey[116] = _T("[F5]");
	vkey[117] = _T("[F6]");
	vkey[118] = _T("[F7]");
	vkey[119] = _T("[F8]");
	vkey[120] = _T("[F9]");
	vkey[121] = _T("[F10]");
	vkey[122] = _T("[F11]");
	vkey[123] = _T("[F12]");
	vkey[124] = _T("[F13]");
	vkey[125] = _T("[F14]");
	vkey[126] = _T("[F15]");
	vkey[127] = _T("[F16]");
	vkey[128] = _T("[F17]");
	vkey[129] = _T("[F18]");
	vkey[130] = _T("[F19]");
	vkey[131] = _T("[F20]");
	vkey[132] = _T("[F21]");
	vkey[133] = _T("[F22]");
	vkey[134] = _T("[F23]");
	vkey[135] = _T("[F24]");
	vkey[136] = _T("[136]");
	vkey[137] = _T("[137]");
	vkey[138] = _T("[138]");
	vkey[139] = _T("[139]");
	vkey[140] = _T("[140]");
	vkey[141] = _T("[141]");
	vkey[142] = _T("[142]");
	vkey[143] = _T("[143]");
	vkey[144] = _T("[NumLock]");
	vkey[145] = _T("[Scr Lk]");
	vkey[146] = _T("[146]");
	vkey[147] = _T("[147]");
	vkey[148] = _T("[148]");
	vkey[149] = _T("[149]");
	vkey[150] = _T("[150]");
	vkey[151] = _T("[151]");
	vkey[152] = _T("[152]");
	vkey[153] = _T("[153]");
	vkey[154] = _T("[154]");
	vkey[155] = _T("[155]");
	vkey[156] = _T("[156]");
	vkey[157] = _T("[157]");
	vkey[158] = _T("[158]");
	vkey[159] = _T("[159]");
	vkey[160] = _T("[LSHIFT]");
	vkey[161] = _T("[RSHIFT]");
	vkey[162] = _T("[LCONTROL]");
	vkey[163] = _T("[RCONTROL]");
	vkey[164] = _T("[LMENU]");
	vkey[165] = _T("[RMENU]");
	vkey[166] = _T("[166]");
	vkey[167] = _T("[167]");
	vkey[168] = _T("[168]");
	vkey[169] = _T("[169]");
	vkey[170] = _T("[170]");
	vkey[171] = _T("[171]");
	vkey[172] = _T("[172]");
	vkey[173] = _T("[173]");
	vkey[174] = _T("[174]");
	vkey[175] = _T("[175]");
	vkey[176] = _T("[176]");
	vkey[177] = _T("[177]");
	vkey[178] = _T("[178]");
	vkey[179] = _T("[179]");
	vkey[180] = _T("[180]");
	vkey[181] = _T("[181]");
	vkey[182] = _T("[182]");
	vkey[183] = _T("[183]");
	vkey[184] = _T("[184]");
	vkey[185] = _T("[185]");
	vkey[186] = _T("[:]");
	vkey[187] = _T("[;]");
	vkey[188] = _T("[,]");
	vkey[189] = _T("[-]");
	vkey[190] = _T("[.]");
	vkey[191] = _T("[/]");
	vkey[192] = _T("[@]");
	vkey[193] = _T("[193]");
	vkey[194] = _T("[194]");
	vkey[195] = _T("[195]");
	vkey[196] = _T("[196]");
	vkey[197] = _T("[197]");
	vkey[198] = _T("[198]");
	vkey[199] = _T("[199]");
	vkey[200] = _T("[200]");
	vkey[201] = _T("[201]");
	vkey[202] = _T("[202]");
	vkey[203] = _T("[203]");
	vkey[204] = _T("[204]");
	vkey[205] = _T("[205]");
	vkey[206] = _T("[206]");
	vkey[207] = _T("[207]");
	vkey[208] = _T("[208]");
	vkey[209] = _T("[209]");
	vkey[210] = _T("[210]");
	vkey[211] = _T("[211]");
	vkey[212] = _T("[212]");
	vkey[213] = _T("[213]");
	vkey[214] = _T("[214]");
	vkey[215] = _T("[215]");
	vkey[216] = _T("[216]");
	vkey[217] = _T("[217]");
	vkey[218] = _T("[218]");
	vkey[219] = _T("[ [ ]");
	vkey[220] = _T("[\\]");
	vkey[221] = _T("[ ] ]");
	vkey[222] = _T("[^]");
	vkey[223] = _T("[223]");
	vkey[224] = _T("[224]");
	vkey[225] = _T("[225]");
	vkey[226] = _T("[ _ ]");
	vkey[227] = _T("[227]");
	vkey[228] = _T("[228]");
	vkey[229] = _T("[ひらがな]");
	vkey[230] = _T("[230]");
	vkey[231] = _T("[231]");
	vkey[232] = _T("[232]");
	vkey[233] = _T("[233]");
	vkey[234] = _T("[234]");
	vkey[235] = _T("[235]");
	vkey[236] = _T("[236]");
	vkey[237] = _T("[237]");
	vkey[238] = _T("[238]");
	vkey[239] = _T("[239]");
	vkey[240] = _T("[CAPS]");
	vkey[241] = _T("[241]");
	vkey[242] = _T("[カタカナひらがな]");
	vkey[243] = _T("[243]");
	vkey[244] = _T("[半角/全角]");
	vkey[245] = _T("[245]");
	vkey[246] = _T("[ATTN]");
	vkey[247] = _T("[CRSEL]");
	vkey[248] = _T("[EXSEL]");
	vkey[249] = _T("[EREOF]");
	vkey[250] = _T("[PLAY]");
	vkey[251] = _T("[ZOOM]");
	vkey[252] = _T("[NONAME]");
	vkey[253] = _T("[PA1]");
	vkey[254] = _T("[OEM_CLEAR]");
	vkey[255] = _T("[255]");
	vkey[256] = _T("[256]");
	vkey[257] = _T("[257]");
	vkey[258] = _T("[258]");
	vkey[259] = _T("[259]");
	vkey[260] = _T("[260]");
	vkey[261] = _T("[261]");
	vkey[262] = _T("[262]");
	vkey[263] = _T("[263]");
	vkey[264] = _T("[264]");
	vkey[265] = _T("[265]");
	vkey[266] = _T("[266]");
	vkey[267] = _T("[267]");
	vkey[268] = _T("[268]");
	vkey[269] = _T("[269]");
	vkey[270] = _T("[270]");
	vkey[271] = _T("[271]");
	vkey[272] = _T("[272]");
	vkey[273] = _T("[273]");
	vkey[274] = _T("[274]");
	vkey[275] = _T("[275]");
	vkey[276] = _T("[276]");
	vkey[277] = _T("[277]");
	vkey[278] = _T("[278]");
	vkey[279] = _T("[279]");
	vkey[280] = _T("[280]");
	vkey[281] = _T("[281]");
	vkey[282] = _T("[カタカナ]");
	vkey[283] = _T("[283]");
	vkey[284] = _T("[284]");
	vkey[285] = _T("[285]");
	vkey[286] = _T("[286]");
	vkey[287] = _T("[287]");
	vkey[288] = _T("[288]");
	vkey[289] = _T("[289]");
	vkey[290] = _T("[290]");
	vkey[291] = _T("[291]");
	vkey[292] = _T("[292]");
	vkey[293] = _T("[293]");
	vkey[294] = _T("[294]");
	vkey[295] = _T("[295]");
	vkey[296] = _T("[296]");
	vkey[297] = _T("[297]");
	vkey[298] = _T("[298]");
	vkey[299] = _T("[299]");
	vkey[300] = _T("[300]");
	vkey[301] = _T("[301]");
	vkey[302] = _T("[302]");
	vkey[303] = _T("[303]");
	vkey[304] = _T("[304]");
	vkey[305] = _T("[305]");
	vkey[306] = _T("[306]");
	vkey[307] = _T("[307]");
	vkey[308] = _T("[308]");
	vkey[309] = _T("[309]");
	vkey[310] = _T("[310]");
	vkey[311] = _T("[311]");
	vkey[312] = _T("[312]");
	vkey[313] = _T("[313]");
	vkey[314] = _T("[314]");
	vkey[315] = _T("[315]");
	vkey[316] = _T("[316]");
	vkey[317] = _T("[317]");
	vkey[318] = _T("[318]");
	vkey[319] = _T("[319]");
	vkey[320] = _T("[320]");
	vkey[321] = _T("[321]");
	vkey[322] = _T("[322]");
	vkey[323] = _T("[323]");
	vkey[324] = _T("[324]");
	vkey[325] = _T("[325]");
	vkey[326] = _T("[326]");
	vkey[327] = _T("[327]");
	vkey[328] = _T("[328]");
	vkey[329] = _T("[329]");
	vkey[330] = _T("[330]");
	vkey[331] = _T("[331]");
	vkey[332] = _T("[332]");
	vkey[333] = _T("[333]");
	vkey[334] = _T("[334]");
	vkey[335] = _T("[335]");
	vkey[336] = _T("[336]");
	vkey[337] = _T("[337]");
	vkey[338] = _T("[338]");
	vkey[339] = _T("[339]");
	vkey[340] = _T("[340]");
	vkey[341] = _T("[341]");
	vkey[342] = _T("[342]");
	vkey[343] = _T("[343]");
	vkey[344] = _T("[344]");
	vkey[345] = _T("[345]");
	vkey[346] = _T("[346]");
	vkey[347] = _T("[347]");
	vkey[348] = _T("[348]");
	vkey[349] = _T("[349]");
	vkey[350] = _T("[350]");
	vkey[351] = _T("[351]");
	vkey[352] = _T("[352]");
	vkey[353] = _T("[353]");
	vkey[354] = _T("[354]");
	vkey[355] = _T("[355]");
	vkey[356] = _T("[356]");
	vkey[357] = _T("[357]");
	vkey[358] = _T("[358]");
	vkey[359] = _T("[359]");
	vkey[360] = _T("[360]");
	vkey[361] = _T("[361]");
	vkey[362] = _T("[362]");
	vkey[363] = _T("[363]");
	vkey[364] = _T("[364]");
	vkey[365] = _T("[365]");
	vkey[366] = _T("[366]");
	vkey[367] = _T("[367]");
	vkey[368] = _T("[368]");
	vkey[369] = _T("[369]");
	vkey[370] = _T("[370]");
	vkey[371] = _T("[371]");
	vkey[372] = _T("[372]");
	vkey[373] = _T("[373]");
	vkey[374] = _T("[374]");
	vkey[375] = _T("[375]");
	vkey[376] = _T("[376]");
	vkey[377] = _T("[377]");
	vkey[378] = _T("[378]");
	vkey[379] = _T("[379]");
	vkey[380] = _T("[380]");
	vkey[381] = _T("[381]");
	vkey[382] = _T("[382]");
	vkey[383] = _T("[383]");
	vkey[384] = _T("[384]");
	vkey[385] = _T("[385]");
	vkey[386] = _T("[386]");
	vkey[387] = _T("[387]");
	vkey[388] = _T("[388]");
	vkey[389] = _T("[389]");
	vkey[390] = _T("[390]");
	vkey[391] = _T("[391]");
	vkey[392] = _T("[392]");
	vkey[393] = _T("[393]");
	vkey[394] = _T("[394]");
	vkey[395] = _T("[395]");
	vkey[396] = _T("[396]");
	vkey[397] = _T("[397]");
	vkey[398] = _T("[398]");
	vkey[399] = _T("[399]");
	vkey[400] = _T("[400]");
	vkey[401] = _T("[401]");
	vkey[402] = _T("[402]");
	vkey[403] = _T("[403]");
	vkey[404] = _T("[404]");
	vkey[405] = _T("[405]");
	vkey[406] = _T("[406]");
	vkey[407] = _T("[407]");
	vkey[408] = _T("[408]");
	vkey[409] = _T("[409]");
	vkey[410] = _T("[410]");
	vkey[411] = _T("[411]");
	vkey[412] = _T("[412]");
	vkey[413] = _T("[413]");
	vkey[414] = _T("[414]");
	vkey[415] = _T("[415]");
	vkey[416] = _T("[416]");
	vkey[417] = _T("[417]");
	vkey[418] = _T("[418]");
	vkey[419] = _T("[419]");
	vkey[420] = _T("[420]");
	vkey[421] = _T("[421]");
	vkey[422] = _T("[422]");
	vkey[423] = _T("[423]");
	vkey[424] = _T("[424]");
	vkey[425] = _T("[425]");
	vkey[426] = _T("[426]");
	vkey[427] = _T("[427]");
	vkey[428] = _T("[428]");
	vkey[429] = _T("[429]");
	vkey[430] = _T("[430]");
	vkey[431] = _T("[431]");
	vkey[432] = _T("[432]");
	vkey[433] = _T("[433]");
	vkey[434] = _T("[434]");
	vkey[435] = _T("[435]");
	vkey[436] = _T("[436]");
	vkey[437] = _T("[437]");
	vkey[438] = _T("[438]");
	vkey[439] = _T("[439]");
	vkey[440] = _T("[440]");
	vkey[441] = _T("[441]");
	vkey[442] = _T("[442]");
	vkey[443] = _T("[443]");
	vkey[444] = _T("[444]");
	vkey[445] = _T("[445]");
	vkey[446] = _T("[446]");
	vkey[447] = _T("[447]");
	vkey[448] = _T("[448]");
	vkey[449] = _T("[449]");
	vkey[450] = _T("[450]");
	vkey[451] = _T("[451]");
	vkey[452] = _T("[452]");
	vkey[453] = _T("[453]");
	vkey[454] = _T("[454]");
	vkey[455] = _T("[455]");
	vkey[456] = _T("[456]");
	vkey[457] = _T("[457]");
	vkey[458] = _T("[458]");
	vkey[459] = _T("[459]");
	vkey[460] = _T("[460]");
	vkey[461] = _T("[461]");
	vkey[462] = _T("[462]");
	vkey[463] = _T("[463]");
	vkey[464] = _T("[464]");
	vkey[465] = _T("[465]");
	vkey[466] = _T("[466]");
	vkey[467] = _T("[467]");
	vkey[468] = _T("[468]");
	vkey[469] = _T("[469]");
	vkey[470] = _T("[470]");
	vkey[471] = _T("[471]");
	vkey[472] = _T("[472]");
	vkey[473] = _T("[473]");
	vkey[474] = _T("[474]");
	vkey[475] = _T("[475]");
	vkey[476] = _T("[476]");
	vkey[477] = _T("[477]");
	vkey[478] = _T("[478]");
	vkey[479] = _T("[479]");
	vkey[480] = _T("[480]");
	vkey[481] = _T("[481]");
	vkey[482] = _T("[482]");
	vkey[483] = _T("[483]");
	vkey[484] = _T("[484]");
	vkey[485] = _T("[485]");
	vkey[486] = _T("[486]");
	vkey[487] = _T("[487]");
	vkey[488] = _T("[488]");
	vkey[489] = _T("[489]");
	vkey[490] = _T("[490]");
	vkey[491] = _T("[491]");
	vkey[492] = _T("[492]");
	vkey[493] = _T("[493]");
	vkey[494] = _T("[494]");
	vkey[495] = _T("[495]");
	vkey[496] = _T("[496]");
	vkey[497] = _T("[497]");
	vkey[498] = _T("[498]");
	vkey[499] = _T("[499]");

	if (VK >= 500)	return _T("NotFound");

	return vkey[VK];
}

//キーコンフィグに変換
static void CreateKeyConfig(KeyBind *kb) {
	//DXライブラリのキーに変換
	kb->Key_ENTER = KEY_INPUT_RETURN;
	kb->Key_ENTER2 = KEY_INPUT_RETURN;
	kb->Key_PAUSE = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_PAUSE);
	kb->Key_PAUSE2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_PAUSE2);
	kb->Key_RotateL = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateL);
	kb->Key_RotateL2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateL2);
	kb->Key_RotateR = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateR);
	kb->Key_RotateR2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_RotateR2);
	kb->Key_UP = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_UP);
	kb->Key_UP2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_UP2);
	kb->Key_DOWN = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_DOWN);
	kb->Key_DOWN2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_DOWN2);
	kb->Key_LEFT = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_LEFT);
	kb->Key_LEFT2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_LEFT2);
	kb->Key_RIGHT = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_ROGHT);
	kb->Key_RIGHT2 = ConvertVirtualKeyToKeyCode((int)dialogSetting.Key_ROGHT2);
}

//キーコンフィグに変換(ジョイパッド)
static void CreateKeyConfigjoy(KeyBindjoy *kb) {
	//配列をコピーする
	for (int i = 0; i < 4; i++) kb->Joy_ENTER[i] = dialogSetting.Joy_ENTER[i];
	for (int i = 0; i < 4; i++) kb->Joy_PAUSE[i] = dialogSetting.Joy_PAUSE[i];
	for (int i = 0; i < 4; i++) kb->Joy_RotateL[i] = dialogSetting.Joy_RotateL[i];
	for (int i = 0; i < 4; i++) kb->Joy_RotateR[i] = dialogSetting.Joy_RotateR[i];
	for (int i = 0; i < 4; i++) kb->Joy_UP[i] = dialogSetting.Joy_UP[i];
	for (int i = 0; i < 4; i++) kb->Joy_DOWN[i] = dialogSetting.Joy_DOWN[i];
	for (int i = 0; i < 4; i++) kb->Joy_LEFT[i] = dialogSetting.Joy_LEFT[i];
	for (int i = 0; i < 4; i++) kb->Joy_RIGHT[i] = dialogSetting.Joy_ROGHT[i];
}

//パッドのキー番号を文字列に変換する
static TCHAR *ConvertVerJoyKey(int JoyCode) {
	JoyCode = SetBitRight(JoyCode);
	switch (JoyCode) {
	case 0:					return _T("なし");
	case PAD_INPUT_DOWN:	return _T("↓");
	case PAD_INPUT_LEFT:	return _T("←");
	case PAD_INPUT_RIGHT:	return _T("→");
	case PAD_INPUT_UP:		return _T("↑");
	case PAD_INPUT_1:		return _T("1");
	case PAD_INPUT_2:		return _T("2");
	case PAD_INPUT_3:		return _T("3");
	case PAD_INPUT_4:		return _T("4");
	case PAD_INPUT_5:		return _T("5");
	case PAD_INPUT_6:		return _T("6");
	case PAD_INPUT_7:		return _T("7");
	case PAD_INPUT_8:		return _T("8");
	case PAD_INPUT_9:		return _T("9");
	case PAD_INPUT_10:		return _T("10");
	case PAD_INPUT_11:		return _T("11");
	case PAD_INPUT_12:		return _T("12");
	case PAD_INPUT_13:		return _T("13");
	case PAD_INPUT_14:		return _T("14");
	case PAD_INPUT_15:		return _T("15");
	case PAD_INPUT_16:		return _T("16");
	case PAD_INPUT_17:		return _T("17");
	case PAD_INPUT_18:		return _T("18");
	case PAD_INPUT_19:		return _T("19");
	case PAD_INPUT_20:		return _T("20");
	case PAD_INPUT_21:		return _T("21");
	case PAD_INPUT_22:		return _T("22");
	case PAD_INPUT_23:		return _T("23");
	case PAD_INPUT_24:		return _T("24");
	case PAD_INPUT_25:		return _T("25");
	case PAD_INPUT_26:		return _T("26");
	case PAD_INPUT_27:		return _T("27");
	case PAD_INPUT_28:		return _T("28");
	}
	return _T("不明");
}

//キーの重複確認(元々書いてあったキー)(falseで重複無し)
static bool CheckDouble(int defplm, WPARAM wParam) {
	//if (keyConfigmode == false)	defplm = 0;//キー入力状態出ないとき

	if (defplm != IDC_CHECK1 && dialogSetting.Key_RotateL == wParam)	return true;
	if (defplm != IDC_CHECK2 && dialogSetting.Key_RotateL2 == wParam)	return true;
	if (defplm != IDC_CHECK3 && dialogSetting.Key_RotateR == wParam)	return true;
	if (defplm != IDC_CHECK4 && dialogSetting.Key_RotateR2 == wParam)	return true;
	if (defplm != IDC_CHECK9 && dialogSetting.Key_UP == wParam)			return true;
	if (defplm != IDC_CHECK10 && dialogSetting.Key_UP2 == wParam)		return true;
	if (defplm != IDC_CHECK11 && dialogSetting.Key_DOWN == wParam)		return true;
	if (defplm != IDC_CHECK12 && dialogSetting.Key_DOWN2 == wParam)		return true;
	if (defplm != IDC_CHECK13 && dialogSetting.Key_ROGHT == wParam)		return true;
	if (defplm != IDC_CHECK14 && dialogSetting.Key_ROGHT2 == wParam)	return true;
	if (defplm != IDC_CHECK15 && dialogSetting.Key_LEFT == wParam)		return true;
	if (defplm != IDC_CHECK16 && dialogSetting.Key_LEFT2 == wParam)		return true;
	if (defplm != IDC_CHECK17 && dialogSetting.Key_PAUSE == wParam)		return true;
	if (defplm != IDC_CHECK18 && dialogSetting.Key_PAUSE2 == wParam)	return true;

	return false;
}

//ジョイパッドのキー重複確認(重複していた場合は重複している設定を削除します)(変更した場合true)
static bool CheckDoubleJoy(int defplm, int wParam) {
	bool Changed = false;
	//自身のと重複する場合も面倒なので設定消去ww
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_RotateL); i++) {
		if (dialogSetting.Joy_RotateL[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_RotateL[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_RotateR); i++) {
		if (dialogSetting.Joy_RotateR[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_RotateR[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_UP); i++) {
		if (dialogSetting.Joy_UP[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_UP[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_DOWN); i++) {
		if (dialogSetting.Joy_DOWN[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_DOWN[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_ROGHT); i++) {
		if (dialogSetting.Joy_ROGHT[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_ROGHT[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_LEFT); i++) {
		if (dialogSetting.Joy_LEFT[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_LEFT[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_PAUSE); i++) {
		if (dialogSetting.Joy_PAUSE[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_PAUSE[i] = 0;
		}
	}
	for (int i = 0; i < ARRAY_LENGTH(dialogSetting.Joy_ENTER); i++) {
		if (dialogSetting.Joy_ENTER[i] == wParam) {
			Changed = true;
			dialogSetting.Joy_ENTER[i] = 0;
		}
	}

	return Changed;
}

//ジョイパットのキー入力状態を取得し、押された瞬間にウィンドウメッセージを送信する
static void joypatEvent() {
	int state = GetJoypadInputState(dialogSetting.Joy_Type);//入力状態の取得
	int ChangeVal = joyBeforeState ^ state;//排他的論理和より変化部分のビットを取得
										   //押されたキーを判定する
	int Push = (ChangeVal & state);//変化があってかつ今回取得したときに押されているキーの取得
	if (Push) {//該当キーが存在する
		SendMessage(Tab10, WM_USER_JOYDOWN, NULL, Push);//ジョイパッドが押されたイベント(カスタム)をTab10ウィンドウに送信
	}
	//直前の状態の記録
	joyBeforeState = state;
}

//キー入力ビット列から一番右を取得(無しは0で1加算)←注意！！！
static int GetBit(LPARAM Val) {
	for (int i = 0; i < sizeof(Val) * 8; i++) {
		if (Val & 1) {
			return i + 1;
		}
		else {
			Val >>= 1;
		}
	}
	return 0;
}

//一番右のビットのみ残し他を0で埋める
static int SetBitRight(LPARAM Val) {
	int base = 1;
	LPARAM V = GetBit(Val);
	for (int i = 1; i < V; i++) {
		base *= 2;
	}
	return (Val & base);
}