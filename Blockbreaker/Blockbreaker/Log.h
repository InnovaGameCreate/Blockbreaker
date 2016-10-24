#pragma once
//���O�֘A

//#include "MainFunc.h"


//���O�̎��
enum Log_Type {
	Log_Type_INFORMATION,	//���
	Log_Type_CAUTION,		//�x��(�v���O�������͓̂��������܂��낵���Ȃ����)
	Log_Type_ERROR,			//�G���[(�v���O�����̎��s�ɉe�����o�����)
#ifdef _DEBUG
	Log_Type_DEBUG			//�f�o�b�O�p�ɉ��ɏo�͂������
#endif // _DEBUG
};

//�X���b�h�֌W
enum THREAD {
	THREAD_Draw,			//�`��X���b�h
	THREAD_Update			//�����X���b�h
};


//���O�̎��(No�ɓ�������)�G���[�ԍ��I��
#define LOG_NULL			0x00000000U	//���ʖ���

//Log_print�̈������ŏ����ɗ}�����}�N��
#define printLog_I( fmt, ... )	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_C( fmt, ... )	Log_print(Log_Type_CAUTION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_E( fmt, ... )	Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#ifdef _DEBUG
#define printLog_D( fmt, ... )	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#endif // _DEBUG




static const int LOG_INTERVAL = 1000;	//���O�����₷�����邽�߂ɋ�s������܂ł̎���(�~���b)




/*Log.cpp*/
extern void Log_Initialize();															//���O�֘A�̏�����
extern void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...);	//���O���o��(const TCHAR* message�����printf�Ɠ����悤�Ɏg�p�ł��܂�)
extern void Log_setEnable(int b_flag);													//���O�̏o�͂�L���E�����ɂ���
extern void Log_SetThreadID(THREAD thread, DWORD threadID);								//�X���b�hID�̐ݒ�

#ifdef _DEBUG
																						//����yLog�o�͊֐�
extern void Log_p(int value);
extern void Log_p(double value);
extern void Log_p(float value);
extern void Log_p(TCHAR value);
extern void Log_p(TCHAR *value);
extern void Log_p(float X, float Y, float Z);
#endif // _DEBUG