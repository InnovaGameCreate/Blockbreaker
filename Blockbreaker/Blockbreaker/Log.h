#pragma once
//ログ関連

//#include "MainFunc.h"


//ログの種類
enum Log_Type {
	Log_Type_INFORMATION,	//情報
	Log_Type_CAUTION,		//警告(プログラム自体は動くがあまりよろしくない状態)
	Log_Type_ERROR,			//エラー(プログラムの実行に影響が出るもの)
#ifdef _DEBUG
	Log_Type_DEBUG			//デバッグ用に仮に出力するもの
#endif // _DEBUG
};

//スレッド関係
enum THREAD {
	THREAD_Draw,			//描画スレッド
	THREAD_Update			//処理スレッド
};


//ログの種類(Noに入れる引数)エラー番号的な
#define LOG_NULL			0x00000000U	//分別無し

//Log_printの引数を最小限に抑えたマクロ
#define printLog_I( fmt, ... )	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_C( fmt, ... )	Log_print(Log_Type_CAUTION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_E( fmt, ... )	Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#ifdef _DEBUG
#define printLog_D( fmt, ... )	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#endif // _DEBUG




static const int LOG_INTERVAL = 1000;	//ログを見やすくするために空行を入れるまでの時間(ミリ秒)




/*Log.cpp*/
extern void Log_Initialize();															//ログ関連の初期化
extern void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...);	//ログを出力(const TCHAR* messageからはprintfと同じように使用できます)
extern void Log_setEnable(int b_flag);													//ログの出力を有効・無効にする
extern void Log_SetThreadID(THREAD thread, DWORD threadID);								//スレッドIDの設定

#ifdef _DEBUG
																						//お手軽Log出力関数
extern void Log_p(int value);
extern void Log_p(double value);
extern void Log_p(float value);
extern void Log_p(TCHAR value);
extern void Log_p(TCHAR *value);
extern void Log_p(float X, float Y, float Z);
#endif // _DEBUG