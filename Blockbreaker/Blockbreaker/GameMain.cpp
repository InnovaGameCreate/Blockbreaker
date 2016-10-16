//�Q�[���֌W�̃��C��

static int gameWindow;	//�Q�[����ʂ�`�悷��n���h��

static void GameMain_Key();

//������(�`�揈��)
void GameMain_Init_Draw() {
	//�Q�[����ʂ̐���(��ŃV�F�[�_���g�������̂�2��n��̃T�C�Y�ō쐬���܂�)
	if((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("�E�B���h�E�쐬�Ɏ��s���܂���"));
}

//������(�v�Z����)
void GameMain_Init_Update() {

}

//�`��
void GameMain_Draw() {

	//�`�����Q�[����ʂɂ���
	SetDrawScreen(gameWindow);

	//��ʈ�t�Ɏl�p�`��`�悷��(��X�e�N�X�`���ɒu�������)
	DrawBox(0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, GetColor(0xb3, 0x65, 0xe5), TRUE);

	//�f�o�b�O
#ifdef DEBUG_GAMEMAIN
	//�c��70�Ԋu�Ő���`�悷��
	for (int i = 1; i < GAMEWINDOW_WIDTH / 50; i++) {
		DrawLine(i * 50, 0, i * 50, GAMEWINDOW_HEIGHT, GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = 1; i < GAMEWINDOW_HEIGHT / 50; i++) {
		DrawLine(0, i * 50, GAMEWINDOW_WIDTH, i * 50, GetColor(0xff, 0xbf, 0x74));
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
	for (int i = 0; i < GAMEWINDOW_WIDTH / 50; i++) {
		int Width = -GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
		Width += 50;
		Width /= 2;
		DrawFormatStringToHandle(GAMEWINDOW_PADDINGX + i*50 + Width, 30, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
	}
	for (int i = 0; i < GAMEWINDOW_HEIGHT / 50; i++) {
		DrawFormatStringToHandle(20, GAMEWINDOW_PADDINGY + i * 50 + 15, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%2d"), i);
	}
#endif // DEBUG_GAMEMAIN

}

//�v�Z����
void GameMain_Update() {

	GameMain_Key();	//�L�[����

}

//�L�[����
static void GameMain_Key() {

}

//�I������(�`�揈��)
void GameMain_Finalize_Draw() {

}

//�I������(�v�Z����)
void GameMain_Finalize_Update() {

}