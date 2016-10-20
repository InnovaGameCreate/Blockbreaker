//���C���֐�

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
static int gpUpdateKey();
static void gpUpdateKeyBind();
static void setWindowModeVirtualFullScreen();


//���C���֐�(��������n�܂�܂�)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	_tsetlocale(LC_ALL, _T(""));//���P�[���̐ݒ�

#ifdef _DEBUG
	::AllocConsole();               // �R�}���h�v�����v�g���\�������
	FILE *fp;
	_tfreopen_s(&fp, _T("CON"), _T("r"), stdin);     // �W�����͂̊��蓖��
	_tfreopen_s(&fp, _T("CON"), _T("w"), stdout);    // �W���o�͂̊��蓖��
#endif // _DEBUG

	SetOutApplicationLogValidFlag(FALSE);				//DX���C�u�����̃��O�o�͂��s��Ȃ�
	Log_Initialize();									//���O�֘A�̏�����(��ԍŏ��Ɏ��s���Ă�������)
	Log_SetThreadID(THREAD_Draw, GetCurrentThreadId());	//�`��X���b�h��ID��ʒm
	setKeybind();										//�L�[�o�C���h�ݒ�������l�ɂ���
	setUSEGAMEPAD();									//�g�p����Q�[���p�b�h�̐ݒ�������l�ɂ���
	SetAnalogueStickMode();								//�A�i���O�X�e�B�b�N�̑��샂�[�h�������l�ɂ���


	//�R���p�C�������Ȃǂ��o��
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�ŏI�R���p�C��������%s %s�ł�"), _T(__DATE__), _T(__TIME__));
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�R���p�C���Ɏg�p����DX���C�u�����̃o�[�W������%s�ł�"), DXLIB_VERSION_STR_T);
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�J���Ɏg�p���Ă���DX���C�u�����̃o�[�W������%s�ł�"), _T("3.16f"));


	Flag_NonActivePauseRequest = FALSE;

	setClearScreen(0);

	StartDialog_Initialize(hInstance);	//�N���ݒ��ʂ̏�����
	StartDialog_Show();					//�N���ݒ��ʂ̕\��


	//�L�[���͏��̏�����
	for (int i = 0; i < ARRAY_LENGTH(stateKey); i++) {
		stateKey[i] = 0;
	}
	for (int i = 0; i < ARRAY_LENGTH(stateKeyBind); i++) {
		stateKeyBind[i] = 0;
	}
	for (int i = 0; i < ARRAY_LENGTH(stateKeyJoy); i++) {
		stateKeyJoy[i] = 0;
	}

	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);//�t���X�N���[�����̊g�僂�[�h�̐ݒ�
	SetFullScreenScalingMode(DX_FSSCALINGMODE_NEAREST);		//��ʊg�厞�̃s�N�Z���ۊǕ��@�̐ݒ�
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);			//�E�B���h�E�T�C�Y�̕ύX

	TCHAR title[50];
	_stprintf_s(title, _T("%s [Ver.%s]"), TITLE, GAMEVERSION);
	SetMainWindowText(title);								//�E�B���h�E�̃^�C�g���ݒ�

#ifdef _DEBUG
	SetUseDXArchiveFlag(0);									//DX���C�u�����A�[�J�C�u���g�p���Ȃ�
#else
	SetUseDXArchiveFlag(1);									//DX���C�u�����A�[�J�C�u���g�p����
#endif // _DEBUG

	SetUseDirect3DVersion(DX_DIRECT3D_9EX);					//�V�F�[�_���f��3���g�p���邽��DirectX9���g�p����悤�Ɏw�肷��

	if (DxLib_Init() == -1)	return -1;						//DX���C�u�����̏�����(�E�B���h�E�\��)

	fpsController_Draw.SetVSyncMode(GetWaitVSyncFlag());	//�����������g�p���ăQ�[�����~���邩�ǂ����̐ݒ�
															
	SetActiveStateChangeCallBackFunction(ActiveStateChange, NULL);	// �E�C���h�E�̃A�N�e�B�u��Ԃɕω����������Ƃ��ɌĂ΂��R�[���o�b�N�֐���o�^
	


																	
	SetMouseDispFlag(Flag_MouseCursor);		//�}�E�X�J�[�\���ݒ�(�E�B���h�E�̐�����ɍs��Ȃ��Ɩ������ۂ�)

	SetDrawScreen(DX_SCREEN_BACK);							//����ʂɕ`����s���悤�ɐݒ肷��

	LoadMenu_Initialize();				//���[�h��ʂ̏�����

	LoadMenu_Draw2();					//���[�h��ʂ̕`��


	srand((unsigned)time(NULL));							//�����̃V�[�h�l��ύX


	//�����Ŋe���W���[���̏������������s��
	SoundEffect_init();	//���ʉ��֌W�̏�����
	Font_init();		//�t�H���g�֌W�̏�����


															
	if (isMultiThread())	_beginthreadex(NULL, 0, Thread_Update, "�v�Z�X���b�h", 0, NULL);//�}���`�X���b�h�Ȃ�ΐV�K�X���b�h�쐬


	Thread_Draw(NULL);

	return 0;
}

//�`��̃��C�����[�v
static void Draw() {
	//�`���~���N�G�X�g�̔��f
	FLAG_PauseDraw = FLAG_PauseDrawrequest;
	if (FLAG_PauseDraw == 1) { //�`���~�t���O
		if (faze_Wait_Loading == TRUE)	LoadMenu_Draw();
		return;
	}

	//�`��̃t�F�[�Y�ڍs
	Changefaze_Draw(); //�t�F�[�Y�ύX�̍ۂɃe�N�X�`���Ȃǂ̓ǂݒ���

	switch (faze) {
	case FAZE_TopMenu:
		//TopMenu_Draw();
		break;
	case FAZE_GameMain:
		GameMain_Draw();
		break;
	case FAZE_Manual:
		//Manual_Draw();
		break;
	}


#ifdef _DEBUG
	//FPS�`��
	DrawFormatStringToHandle(0, 0, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("FPS(D):%.2f %.2fms(%.2f%%)"), fpsController_Draw.GetFPS_Average(), fpsController_Draw.GetWaitTime_Average(), fpsController_Draw.GetWaitTime_Average_Par());
	DrawFormatStringToHandle(0, 0 + 20, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("FPS(U):%.2f %.2fms(%.2f%%)"), fpsController_Update.GetFPS_Average(), fpsController_Update.GetWaitTime_Average(), fpsController_Update.GetWaitTime_Average_Par());
	int DrawStrW = GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("FPS(U):%.2f %.2fms(%.2f%%)"), fpsController_Update.GetFPS_Average(), fpsController_Update.GetWaitTime_Average(), fpsController_Update.GetWaitTime_Average_Par());
	if (!isMultiThread())	DrawLine(0, 31, DrawStrW, 31, GetColor(255, 255, 255), 4);
#endif // _DEBUG
}

//�v�Z�����̃��[�v
static void Update() {
	//�t�F�[�Y�ύX���N�G�X�g������΂���
	if (ChangefazeRequest != faze)
		Changefaze(ChangefazeRequest, THREAD_Update, faze_arg, faze_Wait_Loading);
	if (faze_Wait_Loading == TRUE)	return;

	SoundEffect_update();//�t�F�[�Y�֌W�Ȃ�����

	switch (faze) {
	case FAZE_Nothing: //�g�b�v���j���[�Ɉڍs
		Changefaze(FAZE_GameMain, THREAD_Update);
		break;
	case FAZE_TopMenu:
		//TopMenu_Update();
		break;
	case FAZE_GameMain:
		GameMain_Update();
		break;
	case FAZE_Manual:
		//Manual_Update();
		break;
	}
	Flag_NonActivePauseRequest = FALSE;


	///*�L�[���͏����擾����T���v���R�[�h(�����[�X�ŃR���p�C������ƃG���[���o�܂�)*/
	//if (getKeyBind(KEYBIND_SELECT) == 1) {
	//	Log_p(_T("���ڂ̌���"));
	//}
	//if (getKeyBind(KEYBIND_PAUSE) == 1) {
	//	Log_p(_T("�L�����Z��/�|�[�Y"));
	//}
	//if (getKeyBind(KEYBIND_ROTAL) == 1) {
	//	Log_p(_T("��������u���b�N�𔽎��v���ɉ�]������"));
	//}
	//if (getKeyBind(KEYBIND_ROTAR) == 1) {
	//	Log_p(_T("��������u���b�N�����v���ɉ�]������"));
	//}
	//if (getKeyBind(KEYBIND_UP) == 1) {
	//	Log_p(_T("���ڑI��:��"));
	//}
	//if (getKeyBind(KEYBIND_DOWN) == 1) {
	//	Log_p(_T("���ڑI��:��/��������u���b�N�̉���"));
	//}
	//if (getKeyBind(KEYBIND_LEFT) == 1) {
	//	Log_p(_T("�ڑI��:��/��������u���b�N�̍��ړ�"));
	//}
	//if (getKeyBind(KEYBIND_RIGHT) == 1) {
	//	Log_p(_T("���ڑI��:�E/��������u���b�N�̉E�ړ�"));
	//}

}

//�t�F�[�Y��ύX����
void Changefaze(FAZE NO, THREAD FLAG, int arg, int b_Wait_Loading) {
	if (FLAG == THREAD_Draw) {
		//Draw�X���b�h����̃��N�G�X�g�̏ꍇ
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�t�F�[�Y�ύX���N�G�X�g(%d����%d)"), faze, NO);
		ChangefazeRequest = NO;
		faze_arg = arg;
		faze_Wait_Loading = b_Wait_Loading;
		return;
	}

	FLAG_PauseDrawrequest = 1; //�`��̒�~�����N�G�X�g����
	while (1) { //�������[�v�`��̈ꎞ��~��ҋ@
		Sleep(10); /* �~���b�P�ʁB0.01�b�҂� */ //�����������[�v����̂���
		if (!isMultiThread()) {//�}���`�X���b�h�œ��삵�Ă��Ȃ��ꍇ
			FLAG_PauseDraw = FLAG_PauseDrawrequest;
		}
		if (FLAG_PauseDraw == 1) {
			break; //�`��̈ꎞ��~���m�F
		}
	}
	faze_Wait_Loading = b_Wait_Loading;
	faze_arg = arg;
	/* �t�F�[�Y�I���̍ۂɌĂяo���֐����L�q(�������̊J���Ȃ�) */
	switch (faze) {
	case FAZE_TopMenu:
		//TopMenu_UpdateEnd();
		break;
	case FAZE_GameMain:
		GameMain_Finalize_Update();
		break;
	case FAZE_Manual:
		//Manual_UpdateEnd();
		break;
	}

	/* �t�F�[�Y�J�n�̍ۂɌĂяo���֐����L�q(�e�N�X�`���̓ǂݍ��݂Ȃ�) */
	switch (NO) {
	case FAZE_TopMenu:
		//TopMenu_UpdateSetup();
		break;
	case FAZE_GameMain:
		GameMain_Init_Update();
		break;
	case FAZE_Manual:
		//Manual_UpdateSetup();
		break;
	}

	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�t�F�[�Y�ύX(%d����%d)"), faze, NO);
	faze = NO;
	ChangefazeRequest = faze;
	ChangefazeRequest_Draw = faze;
	FLAG_PauseDrawrequest = 0; //�`��̈ꎞ��~����
}

//�t�F�[�Y��ύX����(�`��X���b�h)
static void Changefaze_Draw() {

	if (faze_draw == faze && ChangefazeRequest_Draw == -1)
		return;

	//�t�F�[�Y�ύX���������ꍇ������

	if (faze_Wait_Loading == TRUE) {
		LoadMenu_Draw();
	}
	/* �t�F�[�Y�I���̍ۂɌĂяo���֐����L�q(�������̊J���Ȃ�) */
	switch (faze_draw) {
	case FAZE_TopMenu: //���j���[
		//TopMenu_DrawEnd();
		break;
	case FAZE_GameMain:
		GameMain_Finalize_Draw();
		break;
	case FAZE_Manual:
		//Manual_DrawEnd();
		break;
	}

	/* �t�F�[�Y�J�n�̍ۂɌĂяo���֐����L�q(�e�N�X�`���̓ǂݍ��݂Ȃ�) */
	switch (faze) {
	case FAZE_TopMenu: //���j���[
		//TopMenu_DrawSetup();
		break;
	case FAZE_GameMain:
		GameMain_Init_Draw();
		break;
	case FAZE_Manual:
		//Manual_DrawSetup();
		break;

	}
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�t�F�[�Y�ύX(%d����%d)(�`��)"), faze_draw, faze);
	faze_draw = faze;
	ChangefazeRequest_Draw = -1;
	faze_Wait_Loading = FALSE;
}

#pragma region ������Ȃ��ėǂ��֐��Q
// �X���b�h���s����֐�(�Q�[������)
static unsigned __stdcall Thread_Update(void* args) {
	Log_SetThreadID(THREAD_Update, GetCurrentThreadId());	//�v�Z�X���b�h��ID��ʒm
	while (TRUE) {//�L�[�C�x���g����(0�Ń��[�v�𔲂���)
		UpdateLoop();//�������[�v
	}

	return 0;
}

//�������[�v
static void UpdateLoop() {
	fpsController_Update.Update_First();
	gpUpdateKey();		//�L�[�擾
	Update();			//�`�揈��
	fpsController_Update.Update_Last();
	if (isMultiThread())	fpsController_Update.Wait();	//�ҋ@
}

// �X���b�h���s����֐�(�Q�[���`��)
static int Thread_Draw(void* args) {
	while (ProcessMessage() == 0) {//�L�[�C�x���g����(0�Ń��[�v�𔲂���)
		fpsController_Draw.Update_First();
		if (FLAG_ClearScreen) ClearDrawScreen();	//��ʂ�����
		if (EndFlag)		//�I���t���O�m�F
			return 0;		//�I��
		if (!isMultiThread()) {
			UpdateLoop();
		}
		if (fpsController_Draw.GetFrameCount() % Drawing_interval == 0) {
			Draw();				//�`�揈��
		}
		fpsController_Draw.Update_Last();
		if (fpsController_Draw.GetFrameCount() % Drawing_interval == 0) {
			ScreenFlip();		//����ʂ�\��ʂɔ��f
		}
		else if (fpsController_Draw.GetVSyncMode()) {//���������̑ҋ@���s��(�����������L���ȏꍇ)
			WaitTimer(1);		//1�~���b�ҋ@1���[�v����������Ɛ����������Ȃ��H�悤�Ȃ̂�1�~���b�ҋ@����
			WaitVSync(1);		//����ʂ�\��ʂɔ��f
		}
		fpsController_Draw.Wait();	//�ҋ@
	}

	return 0;
}

// �L�[�̓��͏�Ԃ��X�V����
static int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			stateKey[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			stateKey[i] = 0;   // 0�ɂ���
		}
	}
	//�Q�[���p�b�h�̃L�[���͏�Ԃ̍X�V
	unsigned int tmpJoyKey = GetJoypadInputState(gettUSEGAMEPAD());//���͏�Ԃ̎擾;
	for (int i = 0; i < ARRAY_LENGTH(stateKeyJoy); i++) {
		unsigned int Value = 1 << i;
		if (tmpJoyKey & Value)	stateKeyJoy[i]++;
		else					stateKeyJoy[i] = 0;
	}
	//��̌��ʂɊ�Â��L�[�o�C���h�ɂ����͏�Ԃ��X�V����
	gpUpdateKeyBind();
	return 0;
}

//�L�[�o�C���h�ɂ��L�[���͏�Ԃ̍X�V
static void gpUpdateKeyBind() {
	//���ڂ̌���
	if (getKey(KeyBindSetting.Key_ENTER) || getKey(KeyBindSetting.Key_ENTER2)
		|| getJoyKey(JoyKeyBindSetting.Joy_ENTER[0]) || getJoyKey(JoyKeyBindSetting.Joy_ENTER[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_ENTER[2]) || getJoyKey(JoyKeyBindSetting.Joy_ENTER[3])) {
		stateKeyBind[KEYBIND_SELECT]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_SELECT] = 0;	//������Ă��Ȃ����0�ɂ���

	//�L�����Z��/�|�[�Y
	if (getKey(KeyBindSetting.Key_PAUSE) || getKey(KeyBindSetting.Key_PAUSE2)
		|| getJoyKey(JoyKeyBindSetting.Joy_PAUSE[0]) || getJoyKey(JoyKeyBindSetting.Joy_PAUSE[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_PAUSE[2]) || getJoyKey(JoyKeyBindSetting.Joy_PAUSE[3])) {
		stateKeyBind[KEYBIND_PAUSE]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_PAUSE] = 0;	//������Ă��Ȃ����0�ɂ���

	//��������u���b�N�𔽎��v���ɉ�]������
	if (getKey(KeyBindSetting.Key_RotateL) || getKey(KeyBindSetting.Key_RotateL2)
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateL[0]) || getJoyKey(JoyKeyBindSetting.Joy_RotateL[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateL[2]) || getJoyKey(JoyKeyBindSetting.Joy_RotateL[3])) {
		stateKeyBind[KEYBIND_ROTAL]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_ROTAL] = 0;		//������Ă��Ȃ����0�ɂ���

	//��������u���b�N�����v���ɉ�]������
	if (getKey(KeyBindSetting.Key_RotateR) || getKey(KeyBindSetting.Key_RotateR2)
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateR[0]) || getJoyKey(JoyKeyBindSetting.Joy_RotateR[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_RotateR[2]) || getJoyKey(JoyKeyBindSetting.Joy_RotateR[3])) {
		stateKeyBind[KEYBIND_ROTAR]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_ROTAR] = 0;		//������Ă��Ȃ����0�ɂ���

	//���ڑI��:��
	if (getKey(KeyBindSetting.Key_UP) || getKey(KeyBindSetting.Key_UP2)
		|| getJoyKey(JoyKeyBindSetting.Joy_UP[0]) || getJoyKey(JoyKeyBindSetting.Joy_UP[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_UP[2]) || getJoyKey(JoyKeyBindSetting.Joy_UP[3])) {
		stateKeyBind[KEYBIND_UP]++;			//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_UP] = 0;		//������Ă��Ȃ����0�ɂ���

	//���ڑI��:��/��������u���b�N�̉���
	if (getKey(KeyBindSetting.Key_DOWN) || getKey(KeyBindSetting.Key_DOWN2)
		|| getJoyKey(JoyKeyBindSetting.Joy_DOWN[0]) || getJoyKey(JoyKeyBindSetting.Joy_DOWN[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_DOWN[2]) || getJoyKey(JoyKeyBindSetting.Joy_DOWN[3])) {
		stateKeyBind[KEYBIND_DOWN]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_DOWN] = 0;		//������Ă��Ȃ����0�ɂ���

	//���ڑI��:��/��������u���b�N�̍��ړ�
	if (getKey(KeyBindSetting.Key_LEFT) || getKey(KeyBindSetting.Key_LEFT2)
		|| getJoyKey(JoyKeyBindSetting.Joy_LEFT[0]) || getJoyKey(JoyKeyBindSetting.Joy_LEFT[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_LEFT[2]) || getJoyKey(JoyKeyBindSetting.Joy_LEFT[3])) {
		stateKeyBind[KEYBIND_LEFT]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_LEFT] = 0;		//������Ă��Ȃ����0�ɂ���

	//���ڑI��:�E/��������u���b�N�̉E�ړ�
	if (getKey(KeyBindSetting.Key_RIGHT) || getKey(KeyBindSetting.Key_RIGHT2)
		|| getJoyKey(JoyKeyBindSetting.Joy_RIGHT[0]) || getJoyKey(JoyKeyBindSetting.Joy_RIGHT[1])
		|| getJoyKey(JoyKeyBindSetting.Joy_RIGHT[2]) || getJoyKey(JoyKeyBindSetting.Joy_RIGHT[3])) {
		stateKeyBind[KEYBIND_RIGHT]++;		//�Ή�����L�[��������Ă�������Z
	}
	else	stateKeyBind[KEYBIND_RIGHT] = 0;	//������Ă��Ȃ����0�ɂ���
}

// �E�C���h�E�̃A�N�e�B�u��Ԃɕω����������Ƃ��ɌĂ΂��R�[���o�b�N�֐�
static int ActiveStateChange(int ActiveState, void *UserData) {
	// �A�N�e�B�u�ɕω������ꍇ�ɃJ�E���g����
	if (ActiveState == FALSE)//�E�B���h�E����A�N�e�B�u�ɂȂ����Ƃ�
	{
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�E�B���h�E���y��A�N�e�B�u�z�ɂȂ�܂���"));
		Flag_NonActivePauseRequest = TRUE;
	}
	else {
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�E�B���h�E���y�A�N�e�B�u�z�ɂȂ�܂���"));
	}

	// �I��
	return 0;
}

#pragma endregion


/*�l�̎擾�n*/
//��A�N�e�B�u�ɂȂ����ۂɃ|�[�Y��v������t���O�������Ă��邩�̎擾
int isFlag_NonActivePauseRequest() {
#ifndef DEBUG
	return Flag_NonActivePauseRequest;
#else
	return FALSE;//Debug���[�h�ŃR���p�C�������Ƃ��̓|�[�Y�ɂȂ�Ȃ�
#endif // DEBUG
}

//�}���`�X���b�h�œ��삷�邩�ǂ����̎擾(FALSE�V���O��)
int isMultiThread() {
	return Flag_MultiThread;
}

//�g�p����Q�[���p�b�h�̎擾
int gettUSEGAMEPAD() {
	return USEGamePad;
}

//�L�[�̓��͏�Ԃ��擾����(DX���C�u�����Œ�`����Ă���L�[�̔ԍ�)(�߂�l�F�L�[��������Ă��鎞�ԁA������Ă��Ȃ��Ƃ���0)
unsigned int getKey(int KEYNO) {
	if (KEYNO < 0 || 256 <= KEYNO)	return 0;
	return stateKey[KEYNO];
}

//�Q�[���p�b�h���͏�Ԃ̎擾(DX���C�u�����Œ�`����Ă���L�[�̔ԍ�)(�߂�l�F�L�[��������Ă��鎞�ԁA������Ă��Ȃ��Ƃ���0)(�Q�[���p�b�h�p)
unsigned int getJoyKey(int JoyKeyNO) {
	//���r�b�g�ڂ��̊m�F
	int bit = 0;
	for (int i = 0; i < ARRAY_LENGTH(stateKeyJoy); i++) {
		unsigned int Value = 1 << i;
		if (JoyKeyNO == Value) {
			bit = i + 1;	//�L�[�R���r�l�[�V�������������ꍇ�͔�������
			break;
		}
	}
	if (bit <= 0)	return 0;
	bit--;//�z���0�N�Z�Ȃ̂Ńf�N�������g
	if (bit < 0 || ARRAY_LENGTH(stateKeyJoy) <= bit)	return 0;
	return stateKeyJoy[bit];
}

//�L�[�o�C���h�ł̃L�[���͏��̎擾(0�����ĂȂ��A1����������)
unsigned int getKeyBind(KEYBIND kEYBIND) {
	if (kEYBIND < 0 || KEYBIND_NUM <= kEYBIND)	return 0;
	return stateKeyBind[kEYBIND];
}

//�Q�[�����N�����Ă���̌o�߃t���[�������擾����
unsigned int getFrameCount(THREAD thread) {
	switch (thread) {
	case THREAD_Draw:
		return fpsController_Draw.GetFrameCount();
	case THREAD_Update:
		return fpsController_Update.GetFrameCount();
	}
	return 0;
}

//�v���O�������I������

#pragma region ������Ȃ��ėǂ��֐��Q
/*�l�̐ݒ�n(�������ʏ킢����Ȃ�)*/
//�L�[�o�C���h�̐ݒ�(NULL�ŋK��l)
void setKeybind(KeyBind *keyBind) {

	//�Ƃ肠�����K��l��ݒ�
	KeyBindSetting.Key_ENTER = KEY_INPUT_RETURN;
	KeyBindSetting.Key_ENTER2 = KEY_INPUT_RETURN;
	KeyBindSetting.Key_PAUSE = KEY_INPUT_ESCAPE;
	KeyBindSetting.Key_PAUSE2 = KEY_INPUT_BACK;
	KeyBindSetting.Key_RotateL = KEY_INPUT_Z;
	KeyBindSetting.Key_RotateL2 = KEY_INPUT_K;
	KeyBindSetting.Key_RotateR = KEY_INPUT_X;
	KeyBindSetting.Key_RotateR2 = KEY_INPUT_L;
	KeyBindSetting.Key_UP = KEY_INPUT_UP;
	KeyBindSetting.Key_UP2 = KEY_INPUT_W;
	KeyBindSetting.Key_DOWN = KEY_INPUT_DOWN;
	KeyBindSetting.Key_DOWN2 = KEY_INPUT_S;
	KeyBindSetting.Key_LEFT = KEY_INPUT_LEFT;
	KeyBindSetting.Key_LEFT2 = KEY_INPUT_D;
	KeyBindSetting.Key_RIGHT = KEY_INPUT_RIGHT;
	KeyBindSetting.Key_RIGHT2 = KEY_INPUT_A;
	if (keyBind == NULL) return;
	//�ϊ����s��\��65535���������̊m�F��ݒ肷��
	//if (keyBind->Key_ENTER != 65535)	KeyBindSetting.Key_ENTER = keyBind->Key_ENTER;
	//if (keyBind->Key_ENTER2 != 65535)	KeyBindSetting.Key_ENTER2 = keyBind->Key_ENTER2;
	//if (keyBind->Key_PAUSE != 65535)	KeyBindSetting.Key_PAUSE = keyBind->Key_PAUSE;
	if (keyBind->Key_PAUSE2 != 65535)	KeyBindSetting.Key_PAUSE2 = keyBind->Key_PAUSE2;
	if (keyBind->Key_RotateL != 65535)		KeyBindSetting.Key_RotateL = keyBind->Key_RotateL;
	if (keyBind->Key_RotateL2 != 65535)	KeyBindSetting.Key_RotateL2 = keyBind->Key_RotateL2;
	if (keyBind->Key_RotateR != 65535)		KeyBindSetting.Key_RotateR = keyBind->Key_RotateR;
	if (keyBind->Key_RotateR2 != 65535)	KeyBindSetting.Key_RotateR2 = keyBind->Key_RotateR2;
	if (keyBind->Key_UP != 65535)		KeyBindSetting.Key_UP = keyBind->Key_UP;
	if (keyBind->Key_UP2 != 65535)		KeyBindSetting.Key_UP2 = keyBind->Key_UP2;
	if (keyBind->Key_DOWN != 65535)		KeyBindSetting.Key_DOWN = keyBind->Key_DOWN;
	if (keyBind->Key_DOWN2 != 65535)	KeyBindSetting.Key_DOWN2 = keyBind->Key_DOWN2;
	if (keyBind->Key_LEFT != 65535)		KeyBindSetting.Key_LEFT = keyBind->Key_LEFT;
	if (keyBind->Key_LEFT2 != 65535)	KeyBindSetting.Key_LEFT2 = keyBind->Key_LEFT2;
	if (keyBind->Key_RIGHT != 65535)	KeyBindSetting.Key_RIGHT = keyBind->Key_RIGHT;
	if (keyBind->Key_RIGHT2 != 65535)	KeyBindSetting.Key_RIGHT2 = keyBind->Key_RIGHT2;
}

//�g�p����Q�[���p�b�h�̐ݒ�(�����ȗ��Őݒ薳��)
void setUSEGAMEPAD(int type) {
	if (type < 0 || DX_INPUT_PAD16 < type)	type = 0;
	USEGamePad = type;
}

//�Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓�����@�̐ݒ�
void SetAnalogueStickMode(ANALOGSTICKMODE type) {
	if (type < 0 || ANALOGSTICKMODE_NUM <= type)	type = ANALOGSTICKMODE_NOUSE;
	Analogstickmode = type;
}

//��ʂ̃N���A���s�����ǂ���(FALSE�s��Ȃ�)(����Ƃ��͂��܂�)
void setClearScreen(int Flag) {
	FLAG_ClearScreen = (Flag) ? TRUE : FALSE;
	if (FLAG_ClearScreen)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("��ʏ������y���ׂėL���z�ɐݒ�"));
	else 					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("��ʏ������y�K�X�L���z�ɐݒ�"));
}

//�`��Ԋu�̐ݒ�(0���獀�ڏ�)
void SetDrawing_interval(int Mode) {
	switch (Mode) {
	case 0://�S�t���[��
		Drawing_interval = 1;
		break;
	case 1://1/2�t���[��
		Drawing_interval = 2;
		break;
	case 2://1/3�t���[��
		Drawing_interval = 3;
		break;
	case 3://1/4�t���[��
		Drawing_interval = 4;
		break;
	default:
		Drawing_interval = 1;
		break;
	}
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�`��Ԋu��1/%d�ɐݒ肵�܂���"), Drawing_interval);
}

//�E�B���h�E���[�h�̐ݒ�(0���獀�ڏ�)
void SetWindowMode(int Mode) {
	switch (Mode) {
	case 0://1280x960
		SetWindowSizeExtendRate(1);	//�E�B���h�E�T�C�Y�̔{����ύX����
		ChangeWindowMode(TRUE);		//�E�B���h�E���[�h�ɕύX
		SetAlwaysRunFlag(TRUE);		//�o�b�N�O���E���h�Œ�~���Ȃ��悤�ɂ���
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�E�B���h�E�̑傫����%dx%d�ɐݒ肵�܂���"), WINDOW_WIDTH * 1, WINDOW_HEIGHT * 1);
		break;
	case 1://960x720
		SetWindowSizeExtendRate(0.75);	//�E�B���h�E�T�C�Y�̔{����ύX����
		ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ɕύX
		SetAlwaysRunFlag(TRUE);	//�o�b�N�O���E���h�Œ�~���Ȃ��悤�ɂ���
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�E�B���h�E�̑傫����%dx%d�ɐݒ肵�܂���"), (int)(WINDOW_WIDTH * 0.75), (int)(WINDOW_HEIGHT * 0.75));
		break;
	case 2://640x480
		SetWindowSizeExtendRate(0.5);	//�E�B���h�E�T�C�Y�̔{����ύX����
		ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ɕύX
		SetAlwaysRunFlag(TRUE);	//�o�b�N�O���E���h�Œ�~���Ȃ��悤�ɂ���
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�E�B���h�E�̑傫����%dx%d�ɐݒ肵�܂���"), (int)(WINDOW_WIDTH * 0.5), (int)(WINDOW_HEIGHT * 0.5));
		break;
	case 3://���z�t���X�N���[��
		setWindowModeVirtualFullScreen();
		ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ɕύX
		SetAlwaysRunFlag(TRUE);	//�o�b�N�O���E���h�Œ�~���Ȃ��悤�ɂ���
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("���z�t���X�N���[���ɐݒ�"));
		break;
	case 4://�t���X�N���[��
		SetWindowSizeExtendRate(1);	//�E�B���h�E�T�C�Y�̔{����ύX����
		SetAlwaysRunFlag(FALSE);	//�o�b�N�O���E���h�Œ�~����悤�ɂ���
		ChangeWindowMode(FALSE);	//�t���X�N���[���ɕύX
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�t���X�N���[���ɐݒ�"));
		break;
	default:
		SetWindowSizeExtendRate(1);	//�E�B���h�E�T�C�Y�̔{����ύX����
		ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ɕύX
		SetAlwaysRunFlag(TRUE);	//�o�b�N�O���E���h�Œ�~���Ȃ��悤�ɂ���
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�E�B���h�E�̑傫����%dx%d�ɐݒ肵�܂���"), WINDOW_WIDTH * 1, WINDOW_HEIGHT * 1);
		break;
	}
}

//���z�t���X�N���[����
static void setWindowModeVirtualFullScreen() {
	int X = 0, Y = 0, Clolr = 0;
	GetDefaultState(&X, &Y, &Clolr);//�E�B���h�E�̑傫���擾
	SetWindowStyleMode(2);															//�E�B���h�E�̉�������
	SetWindowPosition(0, 0);														//�E�B���h�E�̈ʒu������ɍ��킹��
	SetWindowSizeExtendRate(X / (double)WINDOW_WIDTH, Y / (double)WINDOW_HEIGHT);	//�E�B���h�E�T�C�Y�̔{����ύX����
}

//���������̐ݒ�(0���獀�ڏ�)
void SetModeVSync(int Mode) {
	switch (Mode) {
	case 0://���������L��
		fpsController_Draw.SetVSyncMode(TRUE);
		SetWaitVSyncFlag(TRUE);
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�����������y�L���z�ɐݒ�"), Drawing_interval);
		break;
	case 1://������������
		fpsController_Draw.SetVSyncMode(FALSE);
		SetWaitVSyncFlag(FALSE);
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�����������y�����z�ɐݒ�"), Drawing_interval);
		break;
	default:
		fpsController_Draw.SetVSyncMode(TRUE);
		SetWaitVSyncFlag(TRUE);
		Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�����������y�L���z�ɐݒ�"), Drawing_interval);
		break;
	}
}

//��ʏ����̐ݒ�(0���獀�ڏ�)
void SetModeClear(int Mode) {
	switch (Mode) {
	case 0://�K�X��ʏ���
		setClearScreen(FALSE);
		break;
	case 1://���ׂĉ�ʏ���
		setClearScreen(TRUE);
		break;
	default:
		setClearScreen(FALSE);
		break;
	}
}

//�}�E�X�J�[�\���̐ݒ�(0���獀�ڏ�)(�E�B���h�E���[�h�̐ݒ�Ɠ�������)
void SetModeCursor(int Mode, int WinMode) {
	switch (Mode) {
	case 0://�K�X�\��
		if (WinMode == 3 || WinMode == 4) {//���z�t���X�N���[���̎��A�t���X�N���[���̎��ɔ�\��
			Flag_MouseCursor = FALSE;
		}
		else {
			Flag_MouseCursor = TRUE;
		}
		break;
	case 1://��ɕ\��
		Flag_MouseCursor = TRUE;
		break;
	default://�K�X�\��
		if (WinMode == 3 || WinMode == 4) {//���z�t���X�N���[���̎��A�t���X�N���[���̎��ɔ�\��
			Flag_MouseCursor = FALSE;
		}
		else {
			Flag_MouseCursor = TRUE;
		}
		break;
	}
}

//�}���`�X���b�h�̐ݒ�(0���獀�ڏ�)
void SetModeMultiThread(int Mode) {
	switch (Mode) {
	case 0://�}���`�X���b�h
		Flag_MultiThread = TRUE;
		break;
	case 1://�V���O���X���b�h
		Flag_MultiThread = FALSE;
		break;
	default://�}���`�X���b�h
		Flag_MultiThread = TRUE;
		break;
	}
}

//�e�N�X�`���̕����̐ݒ�(0���獀�ڏ�)
void SetTextureCut(int Mode) {
	switch (Mode) {
	case 0://����
		SetUseDivGraphFlag(TRUE);
		break;
	case 1://���̂܂�
		SetUseDivGraphFlag(FALSE);
		break;
	default://����
		SetUseDivGraphFlag(TRUE);
		break;
	}
}

//�L�[�o�C���h�ݒ�(�Q�[���p�b�h)(NULL�ŋK��l��ݒ�)
void setKeybindjoy(KeyBindjoy *keyBindjoy) {

	//�Ƃ肠�����K��l��ݒ�
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_ENTER); i++)		JoyKeyBindSetting.Joy_ENTER[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_PAUSE); i++)		JoyKeyBindSetting.Joy_PAUSE[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateL); i++)	JoyKeyBindSetting.Joy_RotateL[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateR); i++)	JoyKeyBindSetting.Joy_RotateR[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_UP); i++)		JoyKeyBindSetting.Joy_UP[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_DOWN); i++)		JoyKeyBindSetting.Joy_DOWN[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_LEFT); i++)		JoyKeyBindSetting.Joy_LEFT[i] = 0;
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RIGHT); i++)		JoyKeyBindSetting.Joy_RIGHT[i] = 0;

	if (keyBindjoy == NULL) return;
	//�L�[�ݒ�
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_ENTER); i++)		JoyKeyBindSetting.Joy_ENTER[i] = keyBindjoy->Joy_ENTER[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_PAUSE); i++)		JoyKeyBindSetting.Joy_PAUSE[i] = keyBindjoy->Joy_PAUSE[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateL); i++)	JoyKeyBindSetting.Joy_RotateL[i] = keyBindjoy->Joy_RotateL[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RotateR); i++)	JoyKeyBindSetting.Joy_RotateR[i] = keyBindjoy->Joy_RotateR[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_UP); i++)		JoyKeyBindSetting.Joy_UP[i] = keyBindjoy->Joy_UP[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_DOWN); i++)		JoyKeyBindSetting.Joy_DOWN[i] = keyBindjoy->Joy_DOWN[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_LEFT); i++)		JoyKeyBindSetting.Joy_LEFT[i] = keyBindjoy->Joy_LEFT[i];
	for (int i = 0; i < ARRAY_LENGTH(JoyKeyBindSetting.Joy_RIGHT); i++)		JoyKeyBindSetting.Joy_RIGHT[i] = keyBindjoy->Joy_RIGHT[i];

}
#pragma endregion