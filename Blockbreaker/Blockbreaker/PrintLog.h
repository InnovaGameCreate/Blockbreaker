//���O�o�̓��W���[��(printf�g��)

//���C�u�����̓ǂݍ���
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

//Log_print�̈������ŏ����ɗ}�����}�N��
#define printLog_I( fmt, ... )	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_C( fmt, ... )	Log_print(Log_Type_CAUTION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#define printLog_E( fmt, ... )	Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#ifdef _DEBUG
#define printLog_D( fmt, ... )	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, fmt, __VA_ARGS__)
#endif // _DEBUG

enum Log_Type {
	Log_Type_INFORMATION,	//���
	Log_Type_CAUTION,		//�x��
	Log_Type_ERROR,			//�G���[
#ifdef _DEBUG
	Log_Type_DEBUG,			//�f�o�b�O(�f�o�b�O�r���h���̂ݗL��)
#endif // _DEBUG
};

extern void Log_Initialize();								//���O�֘A�̏�����
extern void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...);
extern void Log_setEnable(int b_flag);						//���O�̏o�͂�L���E�����ɂ���
extern void Log_SetThreadID(int threadNo, TCHAR threadID);	//���݂̃X���b�h�̎��ʕ������ݒ肷��
extern void Log_SetFrame(int threadNo, int *f);				//���O�ɕ\������t���[�������Ǘ�����ϐ��ւ̃|�C���^��ݒ肷��
extern const TCHAR *getVersionName();						//�o�[�W�������̎擾
extern TCHAR *getCompileDate();								//�ŏI�R���p�C�������̎擾
extern int isMultibyte();									//�����R�[�h���}���`�o�C�g���ǂ����̎擾(TRUE=�}���`�o�C�g�AFALSE=UNICODE)
extern int isDebug();										//�f�o�b�O���L�����ǂ����̎擾(TRUE�f�o�b�O�L��)
extern int isx86();											//32Bit�Ȃ�TRUE

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