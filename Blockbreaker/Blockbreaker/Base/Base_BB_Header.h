#pragma once
//公開用のヘッダ
//ライブラリの読み込み
#ifdef DEBUG
#ifdef WIN32
#pragma comment(lib, "Base_BlockBreaker_d.lib")
#else
#pragma comment(lib, "Base_BlockBreakerx64_d.lib")
#endif // WIN32
#else
#ifdef WIN32
#pragma comment(lib, "Base_BlockBreaker.lib")
#else
#pragma comment(lib, "Base_BlockBreakerx64.lib")
#endif // WIN32

#endif // DEBUG

#include "Base_BB_Func.h"