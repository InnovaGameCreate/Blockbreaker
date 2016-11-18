//���C���֐�
#include "MainFunc.h"

//�O���[�o���ϐ��̒�`
Phase_Default phase_Default;
Phase_GameMain phase_GameMain;
Phase_TopMenu phase_TopMenu;

static void Init_AfterDXlibInit();

//���C���֐�(��������n�܂�܂�)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Base_BB_Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, GAMEVERSION);

	//�R���p�C�������Ȃǂ��o��
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�ŏI�R���p�C��������%s %s�ł�"), _T(__DATE__), _T(__TIME__));
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�R���p�C���Ɏg�p����DX���C�u�����̃o�[�W������%s�ł�"), DXLIB_VERSION_STR_T);
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�J���Ɏg�p���Ă���DX���C�u�����̃o�[�W������%s�ł�"), _T("3.16f"));

	Base_BB_setFunc_InitAfterDXlibInit(Init_AfterDXlibInit);	//DX���C�u������������̏����������֐��̓o�^
	//�t�F�[�Y�̒�`
	Base_BB_setFaze(FAZE_TopMenu, &phase_TopMenu);
	Base_BB_setFaze(FAZE_GameMain, &phase_GameMain);

	Base_BB_MainLoop();	//���C�����[�v(����)

	return 0;
}

#pragma region ������Ȃ��ėǂ��֐��Q

//DX���C�u������������ɍs������������
static void Init_AfterDXlibInit() {
	//�����Ŋe���W���[���̏������������s��
	SoundEffect_init();				//���ʉ��֌W�̏�����
	Font_init();					//�t�H���g�֌W�̏�����
	ShaderBackGround_Initialize();	//�V�F�[�_�֘A������
}

#pragma endregion
