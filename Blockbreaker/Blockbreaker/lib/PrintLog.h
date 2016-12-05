#pragma once

#include <tchar.h>


#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
namespace SK {
	//ライブラリの読み込み
#ifdef _DEBUG
#ifdef _WIN64
#ifdef _UNICODE
#pragma comment(lib, "PrintLogWx64_d.lib")
#else
#pragma comment(lib, "PrintLogAx64_d.lib")
#endif // _UNICODE
#else
#ifdef _UNICODE
#pragma comment(lib, "PrintLogWx86_d.lib")
#else
#pragma comment(lib, "PrintLogAx86_d.lib")
#endif // _UNICODE
#endif // WIN64
#else
#ifdef _WIN64
#ifdef _UNICODE
#pragma comment(lib, "PrintLogWx64.lib")
#else
#pragma comment(lib, "PrintLogAx64.lib")	//Multibyte,32Bit,Release
#endif // _UNICODE
#else
#ifdef _UNICODE
#pragma comment(lib, "PrintLogWx86.lib")
#else
#pragma comment(lib, "PrintLogAx86.lib")
#endif // _UNICODE
#endif // WIN64
#endif // _DEBUG

	enum Log_Type {
		Log_Type_INFORMATION,	//情報
		Log_Type_CAUTION,		//警告
		Log_Type_ERROR,			//エラー
#ifdef _DEBUG
		Log_Type_DEBUG,			//デバッグ(デバッグビルド時のみ有効)
#endif // _DEBUG
	};

	//Log_printの引数を最小限に抑えたマクロ
#define printLog_I( fmt, ... )	SK::Log_print(SK::Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_C( fmt, ... )	SK::Log_print(SK::Log_Type_CAUTION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_E( fmt, ... )	SK::Log_print(SK::Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#ifdef _DEBUG
#define printLog_D( fmt, ... )	SK::Log_print(SK::Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#endif // _DEBUG



	extern void Log_Initialize();								//ログ関連の初期化
	extern void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...);
	extern void Log_setEnable(int b_flag);						//ログの出力を有効・無効にする
	extern void Log_SetThreadID(int threadNo, TCHAR threadID);	//現在のスレッドの識別文字列を設定する
	extern void Log_SetFrame(int threadNo, int *f);				//ログに表示するフレーム数を管理する変数へのポインタを設定する
	extern void Log_setignore(unsigned int ignoreNo);			//無視するログの種類を設定する
	extern const TCHAR *Log_getVersionName();					//バージョン名の取得
	extern TCHAR *Log_getCompileDate();							//最終コンパイル日時の取得
	extern int Log_isMultibyte();								//文字コードがマルチバイトかどうかの取得(TRUE=マルチバイト、FALSE=UNICODE)
	extern int Log_isDebug();									//デバッグが有効かどうかの取得(TRUEデバッグ有効)
	extern int Log_isx86();										//32BitならTRUE

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
}