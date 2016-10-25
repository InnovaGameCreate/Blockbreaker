//���O�֘A
#include "MainFunc.h"
#include "Log.h"

static inline TCHAR *gettypestr(int Type);
static inline TCHAR *getNostr(unsigned int Type);
static THREAD getThreadEnum(DWORD threadID);
static TCHAR *getThreadName(DWORD threadID);
static DWORD LastLogTime = 0;

static int Enable = TRUE;//���O�̏o�͂�L���ɂ��邩�ǂ���
static DWORD UpdateThreadID;//�����X���b�h��ID
static DWORD DrawThreadID;//�`��X���b�h��ID


//���O�֘A�̏�����
void Log_Initialize() {
#ifdef _DEBUG
	LastLogTime = GetTickCount();//�V�X�e���N��������̌o�ߎ��Ԃ̎擾
	DrawThreadID = 0;
	UpdateThreadID = 0;
#endif // _DEBUG
}

//���O���o��(printf�Ɠ����悤�Ɏg�p�ł��܂�)
void Log_print(Log_Type Type, TCHAR *fileName, TCHAR *func, int Line, unsigned int No, const TCHAR* message, ...) {
#ifdef _DEBUG

	if (!Enable)	return;
	TCHAR str[500];//�����i�[�p

	va_list arg;//�������i�[����ꏊ
	va_start(arg, message);

	_vstprintf_s(str, message, arg);  //Printf�ɊY�����镔��
	fileName = PathFindFileName(fileName);
	va_end(arg);

	//���ݓ������擾
	SYSTEMTIME t;
	GetLocalTime(&t);
	DWORD time = GetTickCount();
	if (time - LastLogTime > LOG_INTERVAL) {//�O�񃍃O���o�͂��Ă��玞�Ԃ��o���Ă���ꍇ
		_tprintf(_T("\n"));
	}
	//�t������t���ďo��
	//_tprintf(_T("%02d:%02d:%02d.%03d[%d] %s(%s:%d(%s�֐���)):%s\n"), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, getFrameCount(s_thread) , gettypestr(TypeID), fileName, Line, func, str);
	_tprintf(_T("%02d:%02d:%02d.%03d[%s:%d] %s(%s:%d):%s\n"), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, getThreadName(GetCurrentThreadId()), getFrameCount(getThreadEnum(GetCurrentThreadId())), gettypestr(Type), fileName, Line, str);
	LastLogTime = time;

	if (Type == Log_Type_ERROR) {
		throw std::exception();	//�����I�ɃG���[���o�͂��A�v���O�����̓�����~����
	}


#endif // _DEBUG
}


//�f�o�b�O���[�h�̎������g�p�ł��܂���
#ifdef _DEBUG
//����y��(int�^)
void Log_p(int value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%d(int�^)"), value);
}

//����y��(double�^)
void Log_p(double value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%f(double�^)"), value);
}

//����y��(float�^)
void Log_p(float value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%f(float�^)"), value);
}

//����y��(TCHAR�^)
void Log_p(TCHAR value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%c(TCHAR�^)"), value);
}

//����y��(PTCHAR�^)(������)
void Log_p(TCHAR *value) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("%s(PTCHAR�^)"), value);
}

//����y��(float�^)(�x�N�g���Ƃ��\���p)
void Log_p(float X, float Y, float Z) {
	Log_print(Log_Type_DEBUG, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("(%f,%f,%f)(float3�^)"), X, Y, Z);
}
#endif // _DEBUG

//�G���[�̃^�C�v�擾
static inline TCHAR *gettypestr(int Type) {
	switch (Type) {
	case Log_Type_INFORMATION:
		return _T("���");
	case Log_Type_CAUTION:
		return _T("�x��");
	case Log_Type_ERROR:
		return _T("�G���[");
#ifdef _DEBUG
	case Log_Type_DEBUG:
		return _T("�f�o�b�O");
#endif // _DEBUG
	default:
		return _T("");
	}
}

//��ނ̎擾
static inline TCHAR *getNostr(unsigned int Type) {
	switch (Type) {
	case LOG_NULL:
		return _T("NULL");
	default:
		return _T("���w��");
	}
}

//���O�̏o�͂�L���E�����ɂ���
void Log_setEnable(int b_flag) {
	b_flag = (b_flag) ? TRUE : FALSE;
	if (b_flag == FALSE) {
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("���O�o�͂��y�����z�ɐݒ肵�܂���"));
	}
	Enable = b_flag;
	if (b_flag) {
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("���O�o�͂��y�L���z�ɐݒ肵�܂���"));
	}
}

//�X���b�hID�̐ݒ�
void Log_SetThreadID(THREAD thread, DWORD threadID) {
	switch (thread) {
	case THREAD_Draw:
		DrawThreadID = threadID;
	case THREAD_Update:
		UpdateThreadID = threadID;
		break;
	}
}

//�X���b�hID����X���b�h�����擾(�I���W�i���d�l)
static TCHAR *getThreadName(DWORD threadID) {
	if (DrawThreadID == threadID)	return _T("D");
	if (UpdateThreadID == threadID)	return _T("U");
	return _T("N");
}

//�X���b�hID����X���b�hENUM���擾(�擾���s��THREAD_Draw)
static THREAD getThreadEnum(DWORD threadID) {
	if (DrawThreadID == threadID)	return THREAD_Draw;
	if (UpdateThreadID == threadID)	return THREAD_Update;
	return THREAD_Draw;
}