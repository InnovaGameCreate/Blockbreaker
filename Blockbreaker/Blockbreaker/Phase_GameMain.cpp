#include "stdafx.h"
#include "Phase_GameMain.h"

//�F
enum COLOR{RED, BLUE, YELLOW, GREEN, PURPLE};

struct field_info {
	int color;//�u���b�N�̐F
	int fall_flag;//���������ǂ����̃t���O
	int move_flag;//�ړ������ǂ����̃t���O
};

struct field_info field[10][16];

Phase_GameMain::Phase_GameMain() {
}


Phase_GameMain::~Phase_GameMain() {
}

//������(�`�揈��)
void Phase_GameMain::Init_Draw() {
	//�Q�[����ʂ̐���(��ŃV�F�[�_���g�������̂�2��n��̃T�C�Y�ō쐬���܂�)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("�E�B���h�E�쐬�Ɏ��s���܂���"));
}

//������(�v�Z����)
void Phase_GameMain::Init_Update() {
	CursorX = 0;
	CursorY = 0;
	Flag_Pause = FALSE;
	Flag_pauseRequest = FALSE;
}

//�`�揈��
void Phase_GameMain::Draw() {

	//�`�����Q�[����ʂɂ���
	SetDrawScreen(gameWindow);

	//��ʈ�t�Ɏl�p�`��`�悷��(��X�e�N�X�`���ɒu�������)
	DrawBox(0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, GetColor(0xb3, 0x65, 0xe5), TRUE);

	//�J�[�\���ʒu�Ɏl�p�`�̘g��`��
	{//�X�R�[�v�ʓ|���̂�
		double X, Y;
		GameMain_Convert_Block_FromIngame(GameMain_getCursorX(), GameMain_getCursorY(), &X, &Y);
		DrawBox((int)X + 2, (int)Y + 2, (int)(X + BLOCK_SIZE - 2), (int)(Y + BLOCK_SIZE - 2), GetColor(0x07, 0xdb, 0x9d), FALSE);
		DrawLine((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 2), (int)(Y + BLOCK_SIZE - 2), GetColor(0x07, 0xdb, 0x9d));
		DrawLine((int)(X + 2), (int)(Y + BLOCK_SIZE - 2), (int)(X + BLOCK_SIZE - 2), (int)(Y + 2), GetColor(0x07, 0xdb, 0x9d));
	}

	//�f�o�b�O
#ifdef DEBUG_GAMEMAIN
	//�c��70�Ԋu�Ő���`�悷��
	for (int i = 1; i < BLOCK_WIDTHNUM; i++) {
		DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, GAMEWINDOW_HEIGHT, GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = 1; i < BLOCK_HEIGHTNUM; i++) {
		DrawLine(0, i * BLOCK_SIZE, GAMEWINDOW_WIDTH, i * BLOCK_SIZE, GetColor(0xff, 0xbf, 0x74));
	}
#endif // DEBUG_GAMEMAIN



	//�`�����o�b�N�X�N���[���ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//��ʈ�t�Ɏl�p�`��`�悷��(��X�e�N�X�`���ɒu�������)
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0x5b, 0x8e, 0xda), TRUE);


	//�Q�[����ʂ�`�悷��
	DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, 0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);

	//�f�o�b�O
#ifdef DEBUG_GAMEMAIN
	//�}�X�ڂ̔ԍ���`��
	for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
		int Width = -GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
		Width += BLOCK_SIZE;
		Width /= 2;
		DrawFormatStringToHandle(GAMEWINDOW_PADDINGX + i*BLOCK_SIZE + Width, 30, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
	}
	for (int i = 0; i < BLOCK_HEIGHTNUM; i++) {
		DrawFormatStringToHandle(20, GAMEWINDOW_PADDINGY + i * BLOCK_SIZE + 15, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%2d"), i);
	}
#endif // DEBUG_GAMEMAIN

	if (GameMain_isPaused()) {//�|�[�Y��Ԃ̎�
							  //�|�[�Y��Ԃƕ�����悤�ɕ`�悷��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (getFrameCount(THREAD_Update) % 120 > 40)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("PAUSE"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
	}
}

//�v�Z����
void Phase_GameMain::Update() {
	//�v�Z�����̍ŏ��ɍs����������(�����Ȃ�����֐����H)
	//���N�G�X�g�̔��f

	Flag_Pause = Flag_pauseRequest;//���N�G�X�g�̔��f
	//�����܂�


	GameMain_Key();	//�L�[����

	if (GameMain_isPaused())	return;//�|�[�Y�������������ꍇ�͐�ɐi�܂Ȃ�
}

//�I������(�`�揈��)
void Phase_GameMain::Finalize_Draw() {

}

//�I������(�v�Z����)
void Phase_GameMain::Finalize_Update() {

}

//�L�[����
void Phase_GameMain::GameMain_Key() {

	//�|�[�Y����
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		GameMain_PauseRequest(!GameMain_isPaused());	//�|�[�Y��Ԃ̔��]
	}

	if (GameMain_isPaused())	return;//�|�[�Y�������������ꍇ�͐�ɐi�܂Ȃ�


	static int Flag_DOWN = TRUE;	//���ړ���SE�֘A�̃t���O
	static int Flag_UP = TRUE;		//���ړ���SE�֘A�̃t���O
	static int Flag_RIGHT = TRUE;	//���ړ���SE�֘A�̃t���O
	static int Flag_LEFT = TRUE;		//���ړ���SE�֘A�̃t���O

										//�L�[���͂Ȃ��̏ꍇ
	if (getKeyBind(KEYBIND_DOWN) == 0)	Flag_DOWN = TRUE;
	if (getKeyBind(KEYBIND_UP) == 0)	Flag_UP = TRUE;
	if (getKeyBind(KEYBIND_RIGHT) == 0)	Flag_RIGHT = TRUE;
	if (getKeyBind(KEYBIND_LEFT) == 0)	Flag_LEFT = TRUE;

	if (getKeyBind(KEYBIND_DOWN) == 1 || (getKeyBind(KEYBIND_DOWN) > 20 && getKeyBind(KEYBIND_DOWN) % 3 == 1)) {//���ړ�
		if (GameMain_CursorY_add(1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//�ړ������ꍇ
		}
		else {
			if (Flag_DOWN) {
				SoundEffect_Play(SE_TYPE_Graze);	//�ړ��o���Ȃ������Ƃ����t���O�������Ă���Ƃ�
				Flag_DOWN = FALSE;					//�t���O��FALSE��
			}
		}
	}

	if (getKeyBind(KEYBIND_UP) == 1 || (getKeyBind(KEYBIND_UP) > 20 && getKeyBind(KEYBIND_UP) % 3 == 1)) {//��ړ�
		if (GameMain_CursorY_add(-1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//�ړ������ꍇ
		}
		else {
			if (Flag_UP) {
				SoundEffect_Play(SE_TYPE_Graze);	//�ړ��o���Ȃ������Ƃ����t���O�������Ă���Ƃ�
				Flag_UP = FALSE;					//�t���O��FALSE��
			}
		}
	}

	if (getKeyBind(KEYBIND_RIGHT) == 1 || (getKeyBind(KEYBIND_RIGHT) > 20 && getKeyBind(KEYBIND_RIGHT) % 3 == 1)) {//�E�ړ�
		if (GameMain_CursorX_add(1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//�ړ������ꍇ
		}
		else {
			if (Flag_RIGHT) {
				SoundEffect_Play(SE_TYPE_Graze);	//�ړ��o���Ȃ������Ƃ����t���O�������Ă���Ƃ�
				Flag_RIGHT = FALSE;					//�t���O��FALSE��
			}
		}
	}

	if (getKeyBind(KEYBIND_LEFT) == 1 || (getKeyBind(KEYBIND_LEFT) > 20 && getKeyBind(KEYBIND_LEFT) % 3 == 1)) {//���ړ�
		if (GameMain_CursorX_add(-1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//�ړ������ꍇ
		}
		else {
			if (Flag_LEFT) {
				SoundEffect_Play(SE_TYPE_Graze);	//�ړ��o���Ȃ������Ƃ����t���O�������Ă���Ƃ�
				Flag_LEFT = FALSE;					//�t���O��FALSE��
			}
		}
	}
}

//�J�[�\���ʒu�𑊑ΓI�Ɉړ�����
int Phase_GameMain::GameMain_CursorX_add(int Val) {
	//���Ɉړ��������Ƃɂ���
	int t = CursorX + Val;
	//��ʊO�ɏo��ꍇ�͒[�Ŏ~�܂�悤��Val�̒l�𒲐�����
	if (t < 0)	Val = 0 - CursorX;	//��ʍ���
	else if (t >= BLOCK_WIDTHNUM)	Val = (BLOCK_WIDTHNUM - 1) - CursorX;	//��ʉE��

																			//�{�����K�p
	CursorX += Val;
	return Val;
}

//�J�[�\���ʒu�𑊑ΓI�Ɉړ�����
int Phase_GameMain::GameMain_CursorY_add(int Val) {
	//���Ɉړ��������Ƃɂ���
	int t = CursorY + Val;
	//��ʊO�ɏo��ꍇ�͒[�Ŏ~�܂�悤��Val�̒l�𒲐�����
	if (t < 0)	Val = 0 - CursorY;	//��ʏ㑤
	else if (t >= BLOCK_HEIGHTNUM)	Val = (BLOCK_HEIGHTNUM - 1) - CursorY;	//��ʉ���

																			//�{�����K�p
	CursorY += Val;
	return Val;
}

//�J�[�\���ʒu���擾����
int Phase_GameMain::GameMain_getCursorX() {
	return CursorX;
}

//�J�[�\���ʒu���擾����
int Phase_GameMain::GameMain_getCursorY() {
	return CursorY;
}

//�u���b�N�̍��W�H����C���Q�[���̍��W�̍��[���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
void Phase_GameMain::GameMain_Convert_Block_FromIngame(int blockX, int blockY, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE;
	}
}

//�|�[�Y��Ԃ��ǂ����̎擾(TRUE�Ń|�[�Y)
int Phase_GameMain::GameMain_isPaused() {
	return Flag_Pause;
}

//�|�[�Y��Ԃ̃��N�G�X�g
void Phase_GameMain::GameMain_PauseRequest(int b_Flag) {
	b_Flag = (b_Flag) ? TRUE : FALSE;//�s���Ȉ����̑΍�

	Flag_pauseRequest = b_Flag;
	if (Flag_pauseRequest)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�|�[�Y���N�G�X�g�y�L���z"));
	else					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�|�[�Y���N�G�X�g�y�����z"));
}