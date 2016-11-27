//ログ出力モジュール(printf拡張)

//ライブラリの読み込み
#ifdef _DEBUG
	#ifdef WIN64
		#ifdef _UNICODE
			#pragma comment(lib, "PrintLogWx64_d.lib")
		#else
			#pragma comment(lib, "PrintLogMx64_d.lib")
		#endif // _UNICODE
	#else
		#ifdef _UNICODE
			#pragma comment(lib, "PrintLogW_d.lib")
		#else
			#pragma comment(lib, "PrintLogM_d.lib")
		#endif // _UNICODE
#endif // WIN64
#else
	#ifdef WIN64
		#ifdef _UNICODE
			#pragma comment(lib, "PrintLogWx64.lib")
		#else
			#pragma comment(lib, "PrintLogMx64.lib")	//Multibyte,32Bit,Release
		#endif // _UNICODE
	#else
		#ifdef _UNICODE
			#pragma comment(lib, "PrintLogW.lib")
		#else
			#pragma comment(lib, "PrintLogM.lib")
		#endif // _UNICODE
	#endif // WIN64
#endif // _DEBUG

//Log_printの引数を最小限に抑えたマクロ
#define printLog_I( fmt, ... )	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_C( fmt, ... )	Log_print(Log_Type_CAUTION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_E( fmt, ... )	Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#ifdef _DEBUG
#define printLog_D( fmt, ... )	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#endif // _DEBUG

enum Log_Type {
	Log_Type_INFORMATION,	//情報
	Log_Type_CAUTION,		//警告
	Log_Type_ERROR,			//エラー
#ifdef _DEBUG
	Log_Type_DEBUG,			//デバッグ(デバッグビルド時のみ有効)
#endif // _DEBUG
};

extern void Log_Initialize();								//ログ関連の初期化
extern void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...);
extern void Log_setEnable(int b_flag);						//ログの出力を有効・無効にする
extern void Log_SetThreadID(int threadNo, TCHAR threadID);	//現在のスレッドの識別文字列を設定する
extern void Log_SetFrame(int threadNo, int *f);				//ログに表示するフレーム数を管理する変数へのポインタを設定する
extern const TCHAR *getVersionName();						//バージョン名の取得
extern TCHAR *getCompileDate();								//最終コンパイル日時の取得
extern int isMultibyte();									//文字コードがマルチバイトかどうかの取得(TRUE=マルチバイト、FALSE=UNICODE)
extern int isDebug();										//デバッグが有効かどうかの取得(TRUEデバッグ有効)
extern int isx86();											//32BitならTRUE

//デバッグモードの時しか使用できません
#ifdef _DEBUG
//お手軽版(int型)
void Log_p(int value);
//お手軽版(double型)
void Log_p(double value);
//お手軽版(float型)
void Log_p(float value);
//お手軽版(TCHAR型)
void Log_p(TCHAR value);
//お手軽版(PTCHAR型)(文字列)
void Log_p(TCHAR *value);
//お手軽版(float型)(ベクトルとか表示用)
void Log_p(float X, float Y, float Z);
#endif // _DEBUG