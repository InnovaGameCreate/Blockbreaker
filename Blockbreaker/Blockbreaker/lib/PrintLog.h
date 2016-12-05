#pragma once

#include <tchar.h>


#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
namespace SK {
	//���C�u�����̓ǂݍ���
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
		Log_Type_INFORMATION,	//���
		Log_Type_CAUTION,		//�x��
		Log_Type_ERROR,			//�G���[
#ifdef _DEBUG
		Log_Type_DEBUG,			//�f�o�b�O(�f�o�b�O�r���h���̂ݗL��)
#endif // _DEBUG
	};

	//Log_print�̈������ŏ����ɗ}�����}�N��
#define printLog_I( fmt, ... )	SK::Log_print(SK::Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_C( fmt, ... )	SK::Log_print(SK::Log_Type_CAUTION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_E( fmt, ... )	SK::Log_print(SK::Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#ifdef _DEBUG
#define printLog_D( fmt, ... )	SK::Log_print(SK::Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#endif // _DEBUG



	extern void Log_Initialize();								//���O�֘A�̏�����
	extern void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...);
	extern void Log_setEnable(int b_flag);						//���O�̏o�͂�L���E�����ɂ���
	extern void Log_SetThreadID(int threadNo, TCHAR threadID);	//���݂̃X���b�h�̎��ʕ������ݒ肷��
	extern void Log_SetFrame(int threadNo, int *f);				//���O�ɕ\������t���[�������Ǘ�����ϐ��ւ̃|�C���^��ݒ肷��
	extern void Log_setignore(unsigned int ignoreNo);			//�������郍�O�̎�ނ�ݒ肷��
	extern const TCHAR *Log_getVersionName();					//�o�[�W�������̎擾
	extern TCHAR *Log_getCompileDate();							//�ŏI�R���p�C�������̎擾
	extern int Log_isMultibyte();								//�����R�[�h���}���`�o�C�g���ǂ����̎擾(TRUE=�}���`�o�C�g�AFALSE=UNICODE)
	extern int Log_isDebug();									//�f�o�b�O���L�����ǂ����̎擾(TRUE�f�o�b�O�L��)
	extern int Log_isx86();										//32Bit�Ȃ�TRUE

																//�f�o�b�O���[�h�̎������g�p�ł��܂���
#ifdef _DEBUG
																//����y��(int�^)
	void Log_p(int value);
	//����y��(double�^)
	void Log_p(double value);
	//����y��(float�^)
	void Log_p(float value);
	//����y��(TCHAR�^)
	void Log_p(TCHAR value);
	//����y��(PTCHAR�^)(������)
	void Log_p(TCHAR *value);
	//����y��(float�^)(�x�N�g���Ƃ��\���p)
	void Log_p(float X, float Y, float Z);
#endif // _DEBUG
}