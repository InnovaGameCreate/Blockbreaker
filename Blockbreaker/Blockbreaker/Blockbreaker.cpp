//���C���֐�
#include "MainFunc.h"

//�O���[�o���ϐ��̒�`
Phase_Default phase_Default;
Phase_GameMain phase_GameMain;
Phase_TopMenu phase_TopMenu;

//�ϐ�
static unsigned int stateKey[256];				//�L�[�{�[�h�̃L�[
static unsigned int stateKeyJoy[32];			//�Q�[���p�b�h(int�^���32�т���)
static unsigned int stateKeyBind[KEYBIND_NUM];	//�L�[�o�C���h�ɂ��L�[���͏��
static FpsController fpsController_Update(UPDATEFPS);	//FPS�R���g���[���[(�v�Z�X���b�h)
static FpsController fpsController_Draw(DRAWFPS);		//FPS�R���g���[���[(�`��X���b�h)

static int Flag_NonActivePauseRequest;			//��A�N�e�B�u�ɂȂ����ۂɃ|�[�Y��v������t���O

//����֘A
static KeyBind KeyBindSetting;			//�L�[�o�C���h�ݒ�
static KeyBindjoy JoyKeyBindSetting;	//�L�[�o�C���h�ݒ�(�A�i���O�p�b�h)
static int USEGamePad;					//�g�p����Q�[���p�b�h�̎��(0�g�p���Ȃ�)
static ANALOGSTICKMODE Analogstickmode;	//�A�i���O�X�e�B�b�N�̑��샂�[�h

//�t�F�[�Y�֘A
static FAZE faze = FAZE_Nothing;				//���݂̃t�F�[�Y(Update)
static FAZE ChangefazeRequest = FAZE_Nothing;	//�t�F�[�Y�ύX���N�G�X�g(Draw����Update)
static int ChangefazeRequest_Draw = -1;			//�t�F�[�Y�ύX���N�G�X�g(Update����Draw)
static FAZE faze_draw = FAZE_Nothing;			//���݂̃t�F�[�Y(Draw)
static int faze_Wait_Loading = FALSE;			//�`��X���b�g�̃��[�h�҂����s�����ǂ���
static int faze_arg = 0;						//����

//�`��֘A
static int FLAG_PauseDraw = 0;			//�`��̃X�L�b�v
static int FLAG_PauseDrawrequest = 0;	//�`��̃X�L�b�v�̃��N�G�X�g
static int FLAG_ClearScreen = 1;		//���t���[���w�i����������(�Q�[����ʂ͂����̐ݒ�ɂ�����炸�펞��������܂�)
static int Drawing_interval = 1;		//�`��Ԋu

static int EndFlag = 0;				//�v���O�����I���t���O

static int Flag_MultiThread = TRUE;	//�}���`�X���b�h�œ��삷�邩�ǂ���(FALSE�V���O��)

static int Flag_MouseCursor = TRUE;	//�}�E�X�J�[�\����\�����邩�ǂ���(FALSE�ŕ\�����Ȃ�)


//�v���g�^�C�v�錾(�t�@�C�����̂ݗL���Ȋ֐�)
static void Draw();
static void Update();
static void Changefaze_Draw();
static unsigned __stdcall Thread_Update(void* args);
static void UpdateLoop();
static int Thread_Draw(void* args);
static int ActiveStateChange(int ActiveState, void *UserData);
static void RestoreGraphCallback();
static int gpUpdateKey();
static void gpUpdateKeyBind();
static void setWindowModeVirtualFullScreen();

static void Init_AfterDXlibInit();

//�t�F�[�Y���Ƃ̃N���X�̃C���X�^���X�ւ̃|�C���^
static PhaseController *phaseController[FAZE_NUM];

//���C���֐�(��������n�܂�܂�)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Base_BB_Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);


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
