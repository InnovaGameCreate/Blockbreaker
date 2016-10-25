//ログ関連
#include "MainFunc.h"
#include "Log.h"

static inline TCHAR *gettypestr(int Type);
static inline TCHAR *getNostr(unsigned int Type);
static THREAD getThreadEnum(DWORD threadID);
static TCHAR *getThreadName(DWORD threadID);
static DWORD LastLogTime = 0;

static int Enable = TRUE;//ログの出力を有効にするかどうか
static DWORD UpdateThreadID;//処理スレッドのID
static DWORD DrawThreadID;//描画スレッドのID


//ログ関連の初期化
void Log_Initialize() {
#ifdef _DEBUG
	LastLogTime = GetTickCount();//システム起動時からの経過時間の取得
	DrawThreadID = 0;
	UpdateThreadID = 0;
#endif // _DEBUG
}

//ログを出力(printfと同じように使用できます)
void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...) {
#ifdef _DEBUG

	if (!Enable)	return;
	TCHAR str[500];//文字格納用

	va_list arg;//引数を格納する場所
	va_start(arg, message);

	_vstprintf_s(str, message, arg);  //Printfに該当する部分
	fileName = PathFindFileName(fileName);
	va_end(arg);

	//現在日時を取得
	SYSTEMTIME t;
	GetLocalTime(&t);
	DWORD time = GetTickCount();
	if (time - LastLogTime > LOG_INTERVAL) {//前回ログを出力してから時間が経っている場合
		_tprintf(_T("\n"));
	}
	//付加情報を付けて出力
	//_tprintf(_T("%02d:%02d:%02d.%03d[%d] %s(%s:%d(%s関数内)):%s\n"), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, getFrameCount(s_thread) , gettypestr(TypeID), fileName, Line, func, str);
	_tprintf(_T("%02d:%02d:%02d.%03d[%s:%d] %s(%s:%d):%s\n"), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, getThreadName(GetCurrentThreadId()), getFrameCount(getThreadEnum(GetCurrentThreadId())), gettypestr(Type), fileName, Line, str);
	LastLogTime = time;

	if (Type == Log_Type_ERROR) {
		throw std::exception();	//強制的にエラーを出力し、プログラムの動作を停止する
	}


#endif // _DEBUG
}


//デバッグモードの時しか使用できません
#ifdef _DEBUG
//お手軽版(int型)
void Log_p(int value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%d(int型)"), value);
}

//お手軽版(double型)
void Log_p(double value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%f(double型)"), value);
}

//お手軽版(float型)
void Log_p(float value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%f(float型)"), value);
}

//お手軽版(TCHAR型)
void Log_p(TCHAR value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%c(TCHAR型)"), value);
}

//お手軽版(PTCHAR型)(文字列)
void Log_p(TCHAR *value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%s(PTCHAR型)"), value);
}

//お手軽版(float型)(ベクトルとか表示用)
void Log_p(float X, float Y, float Z) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("(%f,%f,%f)(float3型)"), X, Y, Z);
}
#endif // _DEBUG

//エラーのタイプ取得
static inline TCHAR *gettypestr(int Type) {
	switch (Type) {
	case Log_Type_INFORMATION:
		return _T("情報");
	case Log_Type_CAUTION:
		return _T("警告");
	case Log_Type_ERROR:
		return _T("エラー");
#ifdef _DEBUG
	case Log_Type_DEBUG:
		return _T("デバッグ");
#endif // _DEBUG
	default:
		return _T("");
	}
}

//種類の取得
static inline TCHAR *getNostr(unsigned int Type) {
	switch (Type) {
	case LOG_NULL:
		return _T("NULL");
	default:
		return _T("未指定");
	}
}

//ログの出力を有効・無効にする
void Log_setEnable(int b_flag) {
	b_flag = (b_flag) ? TRUE : FALSE;
	if (b_flag == FALSE) {
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ログ出力を【無効】に設定しました"));
	}
	Enable = b_flag;
	if (b_flag) {
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ログ出力を【有効】に設定しました"));
	}
}

//スレッドIDの設定
void Log_SetThreadID(THREAD thread, DWORD threadID) {
	switch (thread) {
	case THREAD_Draw:
		DrawThreadID = threadID;
	case THREAD_Update:
		UpdateThreadID = threadID;
		break;
	}
}

//スレッドIDからスレッド名を取得(オリジナル仕様)
static TCHAR *getThreadName(DWORD threadID) {
	if (DrawThreadID == threadID)	return _T("D");
	if (UpdateThreadID == threadID)	return _T("U");
	return _T("N");
}

//スレッドIDからスレッドENUMを取得(取得失敗はTHREAD_Draw)
static THREAD getThreadEnum(DWORD threadID) {
	if (DrawThreadID == threadID)	return THREAD_Draw;
	if (UpdateThreadID == threadID)	return THREAD_Update;
	return THREAD_Draw;
}