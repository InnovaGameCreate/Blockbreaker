#pragma once

// SDKDDKVer.h ���C���N���[�h����ƁA���p�ł���ł���ʂ� Windows �v���b�g�t�H�[������`����܂��B

// �ȑO�� Windows �v���b�g�t�H�[���p�ɃA�v���P�[�V�������r���h����ꍇ�́AWinSDKVer.h ���C���N���[�h���A
// SDKDDKVer.h ���C���N���[�h����O�ɁA�T�|�[�g�ΏۂƂ���v���b�g�t�H�[���������悤�� _WIN32_WINNT �}�N����ݒ肵�܂��B

#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#endif // _WIN32_WINNT


#include <SDKDDKVer.h>


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif