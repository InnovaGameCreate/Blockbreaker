#pragma once
//公開用のヘッダ
//ライブラリの読み込み
#ifdef DEBUG
#ifdef WIN64
#pragma comment(lib, "Base_BlockBreakerx64_d.lib")
#else
#pragma comment(lib, "Base_BlockBreaker_d.lib")
#endif // WIN64
#else
#ifdef WIN64
#pragma comment(lib, "Base_BlockBreakerx64.lib")
#else
#pragma comment(lib, "Base_BlockBreaker.lib")
#endif // WIN64

#endif // DEBUG

#include "Base_BB_Func.h"