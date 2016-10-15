#pragma once
//���O�֘A

#include "MainFunc.h"

//���O�̎��(No�ɓ�������)�G���[�ԍ��I��
#define LOG_NULL			0x00000000	//���ʖ���

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