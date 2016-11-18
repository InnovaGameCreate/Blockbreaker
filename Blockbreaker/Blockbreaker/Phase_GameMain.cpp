#include "MainFunc.h"


Phase_GameMain::Phase_GameMain() {
	//�|�[�Y���j���[�̍��ڂ��쐬
	pauseMenu.addItem(_T("�ĊJ"), 3, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("��蒼��"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("�g�b�v���j���[��"), 8, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.setScrolltype(1);
	pauseMenu.sethaba(50);
	pauseMenu.setCenteringMode(0);
}


Phase_GameMain::~Phase_GameMain() {
}

//������(�`�揈��)
void Phase_GameMain::Init_Draw() {
	//�Q�[����ʂ̐���(��ŃV�F�[�_���g�������̂�2��n��̃T�C�Y�ō쐬���܂�)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("�E�B���h�E�쐬�Ɏ��s���܂���"));

	//�u���b�N�摜
	if ((Tex_BlockRED = LoadGraph(_T("Data/Blocks/Block_RED.png"))) == -1)								printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED.png)"));
	if ((Tex_BlockRED_ARROW_X = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_X.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_X.png)"));
	if ((Tex_BlockRED_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_Y.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_Y.png)"));
	if ((Tex_BlockRED_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_XY.png)"));
	if ((Tex_BlockRED_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY2.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_XY2.png)"));

	if ((Tex_BlockBLUE = LoadGraph(_T("Data/Blocks/Block_BLUE.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE.png)"));
	if ((Tex_BlockBLUE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_X.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_X.png)"));
	if ((Tex_BlockBLUE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_Y.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_Y.png)"));
	if ((Tex_BlockBLUE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_XY.png)"));
	if ((Tex_BlockBLUE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY2.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_XY2.png)"));

	if ((Tex_BlockYELLOW = LoadGraph(_T("Data/Blocks/Block_YELLOW.png"))) == -1)						printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW.png)"));
	if ((Tex_BlockYELLOW_ARROW_X = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_X.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_X.png)"));
	if ((Tex_BlockYELLOW_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_Y.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_Y.png)"));
	if ((Tex_BlockYELLOW_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_XY.png)"));
	if ((Tex_BlockYELLOW_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY2.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_XY2.png)"));

	if ((Tex_BlockGREEN = LoadGraph(_T("Data/Blocks/Block_GREEN.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN.png)"));
	if ((Tex_BlockGREEN_ARROW_X = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_X.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_X.png)"));
	if ((Tex_BlockGREEN_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_Y.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_Y.png)"));
	if ((Tex_BlockGREEN_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_XY.png)"));
	if ((Tex_BlockGREEN_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY2.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_XY2.png)"));

	if ((Tex_BlockPURPLE = LoadGraph(_T("Data/Blocks/Block_PURPLE.png"))) == -1)						printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE.png)"));
	if ((Tex_BlockPURPLE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_X.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_X.png)"));
	if ((Tex_BlockPURPLE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_Y.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_Y.png)"));
	if ((Tex_BlockPURPLE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_XY.png)"));
	if ((Tex_BlockPURPLE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY2.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_XY2.png)"));

	if ((Tex_BlockTREE = LoadGraph(_T("Data/Blocks/Block_TREE.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_TREE.png)"));
	if ((Tex_BlockBLACK = LoadGraph(_T("Data/Blocks/Block_BLACK.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLACK.png)"));
	if ((Tex_BlockRAINBOW = LoadGraph(_T("Data/Blocks/Block_RAINBOW.png"))) == -1)						printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RAINBOW.png)"));
	if ((Tex_BlockBOMB = LoadGraph(_T("Data/Blocks/Block_BOMB.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BOMB.png)"));
	if ((Tex_Block2BOMB = LoadGraph(_T("Data/Blocks/Block_2BOMB.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_2BOMB.png)"));
	if ((Tex_BlockBOMB_Color = LoadGraph(_T("Data/Blocks/Block_BOMB_Color.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BOMB_Color.png)"));
	if ((Tex_BlockFireEffect = LoadGraph(_T("Data/Blocks/Block_FireEffect.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_FireEffect.png)"));
	if ((Tex_BlockFireEffect2 = LoadGraph(_T("Data/Blocks/Block_FireEffect2.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_FireEffect2.png)"));
	if ((Tex_BlockCenterEffect = LoadGraph(_T("Data/Blocks/Block_CENTER.png"))) == -1)					printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_CENTER.png)"));
	if ((Tex_BlockBack = LoadGraph(_T("Data/Blocks/Block_Back.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_Back.png)"));

	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/image/colorbom.png)"));
	if ((Tex_FieldBack = LoadGraph(_T("Data/image/BlockField_Back.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/image/BlockField_Back.png)"));


	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

	pauseMenu.setEnable(TRUE);
}

//�t���X�N���[���ɕ��A���ɌĂ΂��
void Phase_GameMain::RestoreGraphCallback() {
	//�e�N�X�`���̓ǂݒ���
}

//������(�v�Z����)
void Phase_GameMain::Init_Update() {
	Create_Wait_Block();
	Create_Wait_Block();
	Restart();	//���X�^�[�g


}

//���X�^�[�g
void Phase_GameMain::Restart() {
	Flag_Pause = PauseMode_NO;
	Flag_pauseRequest = PauseMode_NO;
	Count_PlayTime = 0;
	Count_GameTime = 0;
	Count_Time = 0;
	Count_Pause = 0;
	Count_Turn = 0;
	Count_lay = 0;
	lay.SetpointNum(0);
	//�������u���b�N�̍폜
	Delete_FallBlock();
	score.init();//�X�R�A�̏�����
	//�u���b�N�ҋ@��̏�����
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo); i++) Create_Wait_Block();

	//�u���b�N�̍폜���s��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].color = BLOCK_TYPE_NO;
			field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;
			field[x][y].blockMoveMotion.Enable = FALSE;
			field[x][y].fall_flag = 0;
			field[x][y].move_flag = 0;
		}
	}

	//�K���Ƀu���b�N��ݒu����(������3�i)
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL, BLOCK_WIDTHNUM_INGAME, BLOCK_DEFAULT_VAL);

	//���z�u���b�N�̍X�V���s��
	Virtualfield_Update();

	//�Q�[���T�C�N�����u���b�N�����ɐݒ�
	setGameCycle(GameCycle_FALL);

	//BGM���ŏ�����Đ�������
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);


	printLog_I(_T("�X�e�[�W���ŏ������蒼���܂���(Restart)"));
}

//�`�揈��
void Phase_GameMain::Draw() {


	//�`�����Q�[����ʂɂ���
	SetDrawScreen(gameWindow);
	ClearDrawScreen();

	//��ʈ�t�Ɏl�p�`��`�悷��(��X�e�N�X�`���ɒu�������)
	DrawGraph(BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE, Tex_FieldBack, FALSE);

	Draw_FallBlock();	//�����u���b�N�̕`��

	Draw_FieldBlock();	//�t�B�[���h�u���b�N�̕`��

	//�j������̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawPolygon2D_Notexture2(&lay, GetColor(200, 200, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�t���C�e�L�X�g��`�悷��
	flyText.Draw();


	//�f�o�b�O
#ifdef _DEBUG_GAMEMAIN_
	//�Q�[���I�[�o�[�̈��`�悷��
	double tY;
	Convert_Ingame_FromBlock(0, GAMEOVER_BORDER, 0, 0, NULL, &tY);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, WINDOW_WIDTH, (int)tY, GetColor(0, 255, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�c��BLOCK_SIZE�Ԋu�Ő���`�悷��
	for (int i = BLOCK_PADDINGLEFT + 1; i < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; i++) {
		DrawLine(i * BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE,
			i * BLOCK_SIZE, GAMEWINDOW_HEIGHT + BLOCK_PADDINGUP*BLOCK_SIZE,
			GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = BLOCK_PADDINGUP + 1; i < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; i++) {
		DrawLine(BLOCK_PADDINGLEFT*BLOCK_SIZE, i * BLOCK_SIZE,
			GAMEWINDOW_WIDTH + BLOCK_PADDINGLEFT*BLOCK_SIZE,
			i * BLOCK_SIZE, GetColor(0xff, 0xbf, 0x74));
	}

	//�����u���b�N�͈̔͂�`�悷��
	if (isFallBlock_Enable()) {//�����u���b�N���L���Ȏ�
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0, 0, &X, &Y);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
				DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), FALSE);
			}
		}
	}
#endif // _DEBUG_GAMEMAIN_



	//�`�����o�b�N�X�N���[���ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[����ʂ̔w�i�摜��`��
	DrawGraph(0, 0, haikei, FALSE);

	Draw_NextFallBlock();	//���̗����u���b�N�̕`��

	Draw_Status();	//�X�e�[�^�X�`��

	//�Q�[����ʂ�`�悷��
	//�f�o�b�O
#ifdef _DEBUG_GAMEMAIN_
	//�f�o�b�O���[�h�̏ꍇ�A�S�u���b�N�̈��`�悷��
	DrawRectGraph(GAMEWINDOW_PADDINGX - BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_PADDINGY - BLOCK_PADDINGUP*BLOCK_SIZE, 0, 0, BLOCK_WIDTHNUM*BLOCK_SIZE, BLOCK_HEIGHTNUM*BLOCK_SIZE, gameWindow, FALSE, FALSE);
#else
	DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);
#endif


	//�f�o�b�O
#ifdef _DEBUG_GAMEMAIN_
	//�}�X�ڂ̔ԍ���`��
	for (int i = BLOCK_PADDINGLEFT; i < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; i++) {
		int Width = -GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
		Width += BLOCK_SIZE;
		Width /= 2;
		DrawFormatStringToHandle(GAMEWINDOW_PADDINGX + (i - BLOCK_PADDINGLEFT)*BLOCK_SIZE + Width, 30
			, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
	}
	for (int i = BLOCK_PADDINGUP; i < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; i++) {
		DrawFormatStringToHandle(20, GAMEWINDOW_PADDINGY + (i - BLOCK_PADDINGUP) * BLOCK_SIZE + 15,
			GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%2d"), i);
	}
#endif // _DEBUG_GAMEMAIN_


	switch (getPauseMode()) {
	case PauseMode_NOMAL:
		//�|�[�Y��Ԃƕ�����悤�ɕ`�悷��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (Count_Pause % 120 <= 80)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("PAUSE"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);

		//�I�����̍��ڂ̕`��
		pauseMenu.Draw();
		break;
	case PauseMode_GameOver:
	{
		//���񂾂�Z������
		int Alpha = 200;
		Alpha = (int)(Alpha * Count_Pause / 300.);
		if (Alpha > 200)	Alpha = 200;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//�ォ�當���������Ă���
		const int strW = 60;
		int strX = (int)(WINDOW_WIDTH / 2. - strW * (9 / 2.));
		double strY = 460;

		strY = 460 * Count_Pause / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("G"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 30) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("A"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 60) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("M"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 90) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("E"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strX += strW;

		strY = 460 * (Count_Pause - 120) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("O"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 150) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("V"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 180) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("E"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);
		strX += strW;

		strY = 460 * (Count_Pause - 210) / 40.;
		if (strY > 460)	strY = 460;
		Font_DrawStringWithShadow(strX, (int)strY, _T("R"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge70);


		//�I�����̍��ڂ̕`��
		pauseMenu.Draw();
	}
	break;
	}
}

//�����u���b�N�̕`��
void Phase_GameMain::Draw_FallBlock() {
	//�t�B�[���h�S�̂̃Y�����v�Z����
	double Field_PaddingX = 0;
	double Field_PaddingY = 0;
	if (Block_AllMovedata.Enable) {//�S�̂��炷���L���ȏꍇ
		double D = getMoveDistance(Block_AllMovedata.a, Block_AllMovedata.MaxSpeed, Block_AllMovedata.Count);	//���݂̈ړ������̌v�Z
		double Rota = getRotation(Block_AllMovedata.FromX, Block_AllMovedata.FromY, Block_AllMovedata.ToX, Block_AllMovedata.ToY);
		//��̌v�Z���ʂ��A�`����W�̌v�Z
		Field_PaddingX += D * cos(deg_to_rad(Rota));
		Field_PaddingY += D * sin(deg_to_rad(Rota));
	}


	if (isFallBlock_Enable()) {//�����u���b�N���L���Ȏ�

		//�u���b�N�̗����\�z�n�_�Ƀu���b�N��`�悷��
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			int ShadowDrawDFlag = FALSE;
			int yCount = 0;	//y�����ɑ��݂���u���b�N�̐�
			for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
				//�u���b�N�̗����\�z�n�_�̕`��
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {

					int ansY = getBlock_Upper(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER)) - 1 - yCount;
					double X, Y;
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), ansY, 0.5, 0.5, &X, &Y);

					//�t�B�[���h�̃Y���̕����𔽉f����
					X += Field_PaddingX;
					Y += Field_PaddingY;

					DrawBlock_Tex(X, Y, Tex_BlockBack);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
					DrawBlock(X, Y, fallBlockInfo.BlockID[x][y]);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					yCount++;
				}
			}
		}

		//�������u���b�N�̕`��
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			int ShadowDrawDFlag = FALSE;
			int yCount = 0;	//y�����ɑ��݂���u���b�N�̐�
			for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
				double X, Y;
				double Per = -(fallBlockInfo.FallCount / 60.);
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0.5, Per + 0.5, &X, &Y);

				//�t�B�[���h�̃Y���̕����𔽉f����
				X += Field_PaddingX;
				Y += Field_PaddingY;
				//��ʊO�ɏo�Ă��܂��ꍇ�͂łȂ��悤�ɒ�������
				int Dan = 0;//�u���b�N�����݂���i��
				for (int y2 = 0; y2 < FALLBLOCK_SIZE; y2++) {
					for (int x2 = 0; x2 < FALLBLOCK_SIZE; x2++) {
						if (fallBlockInfo.BlockID[x2][y2] != BLOCK_TYPE_NO) {
							Dan = y2;
							//���[�v�𔲂���
							x2 = FALLBLOCK_SIZE;
							y2 = FALLBLOCK_SIZE;
						}
					}
				}
				if (Y < (y - Dan + BLOCK_PADDINGUP)*BLOCK_SIZE + BLOCK_SIZE / 2) {
					Y = (y - Dan + BLOCK_PADDINGUP)*BLOCK_SIZE + BLOCK_SIZE / 2;
				}

				DrawBlock(X, Y, fallBlockInfo.BlockID[x][y]);
				if (x == 1 && y == 1 && fallBlockInfo.Flag_Rotate) {
					//���S�̏ꍇ����]�\�u���b�N�̏ꍇ
					//float Scale = 0.9 + getGraph_Sin(fallBlockInfo.Counter*5, 0.05, 0);
					float Scale = 1;

					DrawRectRotaGraphFast2((int)X, (int)Y, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, Scale, 0, Tex_BlockCenterEffect, TRUE, FALSE);
				}
			}
		}
	}
}

//�t�B�[���h�u���b�N�̕`��
void Phase_GameMain::Draw_FieldBlock() {

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//�`���̍��W���擾
			double X, Y;
			X = field[x][y].DrawPlaceX;
			Y = field[x][y].DrawPlaceY;

			//�Q�[���I�[�o�[���ɉ��ɗ���������
			if (getPauseMode() == PauseMode_GameOver) {
				if (Count_Pause < 300)	Y += 1 / 2.*0.2*Count_Pause*Count_Pause;
				else					Y += 1 / 2.*0.2 * 300 * 300;
			}

			switch (field[x][y].blockChangeMotion.Type) {
			case BlockChangeMotionType_NO:
				//�ω����[�V���������̏ꍇ�͖���ɕ`�悷��
				DrawBlock(X, Y, field[x][y].color);
				break;
			case BlockChangeMotionType_NOMAL:
				//���ʂ̕ω����[�V����
				DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
				//�ω��ʂɉ����Ĕ������ŕ`�悷��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)((field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length) * 255));
				DrawBlock(X, Y, field[x][y].blockChangeMotion.To);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case BlockChangeMotionType_EXPLOSION:
				//����(�V�F�[�_�Ɋ撣���Ă��炤)
				if (field[x][y].blockChangeMotion.Count < 0) {//���[�V�����O�͕��ʂɕ`��
					DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
				}
				else {
					ShaderBackGround_DeleteBlock(X, Y, field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length
						, getBlockTexture(field[x][y].blockChangeMotion.From), Tex_BlockFireEffect, Tex_BlockFireEffect2);
				}
				break;
			case BlockChangeMotionType_SMALL:
				//�������Ȃ�
				DrawBlock(X, Y, field[x][y].blockChangeMotion.From, 1 - (field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length));
				break;
			}
		}
	}
}

//�X�e�[�^�X�̕`��
void Phase_GameMain::Draw_Status() {
	//���݂̌o�߃^�[�����̕`��
	int placeX = 880;	//���ڂ̊�ʒu
	int placeY = 60;	//���ڂ̊�ʒu

	TCHAR str[100];
	Font_DrawStringWithShadow(placeX, placeY, _T("�o�߃^�[����"), GetColor(0x00, 0xac, 0xd7), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%d�^�[��"), Count_Turn);
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0x70, 0xe2, 0xff), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);

	placeY += 110;
	Font_DrawStringWithShadow(placeX, placeY, _T("�Q�[���o�ߎ���"), GetColor(0x13, 0xc6, 0x00), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%.2fs"), getCountGameTime() / 60.);
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0x90, 0xff, 0x85), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);

	placeY += 110;
	Font_DrawStringWithShadow(placeX, placeY, _T("����o�ߎ���"), GetColor(0xff, 0xa4, 0x38), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%.2fs"), getCountPlayTime() / 60.);
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0xd9, 0x8b, 0x30), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);

	placeY += 110;
	Font_DrawStringWithShadow(placeX, placeY, _T("�l���X�R�A"), GetColor(0xff, 0xa4, 0x38), GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	_stprintf_s(str, _T("%d"), score.getScore());
	Font_DrawStringWithShadow(placeX + 20, placeY + 60, str, GetColor(0xd9, 0x8b, 0x30), GetColor(10, 10, 10), FONTTYPE_SFSquareHeadCondensed_Edge45);
}

//���̗����u���b�N�̕`��
void Phase_GameMain::Draw_NextFallBlock() {
	int placeX = 550;
	int placeY = 60;
	double Before_X = 0;	//���O�̕`��G���A�̍���
	double Scale = 1;

	for (int i = 0; i < min(ARRAY_LENGTH(waitBlockinfo), 5); i++) {
		placeY += (int)Before_X;
		if (i != 0)	Scale = 0.7;
		Before_X = BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale + 20;
		DrawBox(placeX, placeY, (int)(placeX + BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale), (int)(placeY + BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale), GetColor(10, 10, 10), TRUE);
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);

				//�c�ɂ��炷
				X *= Scale;
				Y *= Scale;

				X += placeX + BLOCK_SIZE * Scale;
				Y += placeY + BLOCK_SIZE * Scale;

				DrawBlock(X, Y, waitBlockinfo[i].BlockID[x][y], Scale);
			}
		}
	}
}

//�u���b�N��`�悷��(�C���Q�[�����W)
void Phase_GameMain::DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type, double Scale) {

	if (type == BLOCK_TYPE_NO)	return;

	DrawBlock_Tex(CenterX, CenterY, getBlockTexture(type), Scale);
}

//�e�N�X�`���𒼐ڎw�肵�ău���b�N��`�悷��(�C���Q�[�����W)
void Phase_GameMain::DrawBlock_Tex(double CenterX, double CenterY, int tex, double Scale) {

	if (tex <= 0)	return;

	DrawRectRotaGraphFast2((int)CenterX, (int)CenterY, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, (float)Scale, 0, tex, TRUE, FALSE);
}

//�u���b�N�^�C�v���e�N�X�`���n���h���̎擾
int Phase_GameMain::getBlockTexture(BLOCK_TYPE type) {
	switch (type) {
	case BLOCK_TYPE_RED:	//�ԃu���b�N
		return Tex_BlockRED;
	case BLOCK_TYPE_BLUE:	//�u���b�N
		return Tex_BlockBLUE;
	case BLOCK_TYPE_GREEN:	//�΃u���b�N
		return Tex_BlockGREEN;
	case BLOCK_TYPE_PURPLE:	//���u���b�N
		return Tex_BlockPURPLE;
	case BLOCK_TYPE_RED_ARROW_X://��(���s���)
		return Tex_BlockRED_ARROW_X;
	case BLOCK_TYPE_RED_ARROW_Y://��(�������)
		return Tex_BlockRED_ARROW_Y;
	case BLOCK_TYPE_RED_ARROW_XY://��(�΂߉E��)
		return Tex_BlockRED_ARROW_XY;
	case BLOCK_TYPE_RED_ARROW_XY2://��(�΂߉E��)
		return Tex_BlockRED_ARROW_XY2;
	case BLOCK_TYPE_BLUE_ARROW_X://��(���s���)
		return Tex_BlockBLUE_ARROW_X;
	case BLOCK_TYPE_BLUE_ARROW_Y://��(�������)
		return Tex_BlockBLUE_ARROW_Y;
	case BLOCK_TYPE_BLUE_ARROW_XY://��(�΂߉E��)
		return Tex_BlockBLUE_ARROW_XY;
	case BLOCK_TYPE_BLUE_ARROW_XY2://��(�΂߉E��)
		return Tex_BlockBLUE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW_ARROW_X://��(���s���)
		return Tex_BlockYELLOW_ARROW_X;
	case BLOCK_TYPE_YELLOW_ARROW_Y://��(�������)
		return Tex_BlockYELLOW_ARROW_Y;
	case BLOCK_TYPE_YELLOW_ARROW_XY://��(�΂߉E��)
		return Tex_BlockYELLOW_ARROW_XY;
	case BLOCK_TYPE_YELLOW_ARROW_XY2://��(�΂߉E��)
		return Tex_BlockYELLOW_ARROW_XY2;
	case BLOCK_TYPE_GREEN_ARROW_X://��(���s���)
		return Tex_BlockGREEN_ARROW_X;
	case BLOCK_TYPE_GREEN_ARROW_Y://��(�������)
		return Tex_BlockGREEN_ARROW_Y;
	case BLOCK_TYPE_GREEN_ARROW_XY://��(�΂߉E��)
		return Tex_BlockGREEN_ARROW_XY;
	case BLOCK_TYPE_GREEN_ARROW_XY2://��(�΂߉E��)
		return Tex_BlockGREEN_ARROW_XY2;
	case BLOCK_TYPE_PURPLE_ARROW_X://��(���s���)
		return Tex_BlockPURPLE_ARROW_X;
	case BLOCK_TYPE_PURPLE_ARROW_Y://��(�������)
		return Tex_BlockPURPLE_ARROW_Y;
	case BLOCK_TYPE_PURPLE_ARROW_XY://��(�΂߉E��)
		return Tex_BlockPURPLE_ARROW_XY;
	case BLOCK_TYPE_PURPLE_ARROW_XY2://��(�΂߉E��)
		return Tex_BlockPURPLE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW:	//���F�u���b�N�`��
		return Tex_BlockYELLOW;
	case BLOCK_TYPE_TREE:	//���؃u���b�N
		return Tex_BlockTREE;
	case BLOCK_TYPE_BLACK:	//���u���b�N
		return Tex_BlockBLACK;
	case BLOCK_TYPE_RAINBOW://���F�u���b�N
		return Tex_BlockRAINBOW;
	case BLOCK_TYPE_BOM://���e�u���b�N
		return Tex_BlockBOMB;
	case BLOCK_TYPE_2BOM://2���e�u���b�N
		return Tex_Block2BOMB;
	case BLOCK_TYPE_BOM_Color://���F���e�u���b�N
		return Tex_BlockBOMB_Color;
	}
	printLog_E(_T("�e�N�X�`���ԍ����擾�ł��܂���ł���(BLOCK_TYPE=%d)"), type);
	return -1;	//�G���[
}

//�v�Z����
void Phase_GameMain::Update() {
	//�v�Z�����̍ŏ��ɍs����������(�����Ȃ�����֐����H)

	//���N�G�X�g�̔��f
	if (Flag_pauseRequest != PauseMode_NUM) {
		Flag_Pause = Flag_pauseRequest;//���N�G�X�g�̔��f
		Flag_pauseRequest = PauseMode_NUM;
		Count_Pause = 0;
	}

	//�J�E���^�̉��Z
	Update_Counter();

	GameMain_Key();	//�L�[����

	//�|�[�Y���̏��������Ă��̐�ɂ͐i�܂Ȃ�
	switch (getPauseMode()) {
	case PauseMode_NOMAL:
		//�I�����̍��ڂ̍X�V
		pauseMenu.Update();
		return;
	case PauseMode_GameOver:
		pauseMenu.Update();
		return;
	}

	//�j������G�t�F�N�g�̍X�V
	Update_Lay_BlockDel();
	//�t���C�e�L�X�g�̍X�V
	flyText.Update();

	//�u���b�N�S�̈ړ����L���ȏꍇ�́A�ʏ�̏��������s�����A�S�̈ړ��̃J�E���g�A�b�v�̂ݍs���悤�ɂ���
	if (Block_AllMovedata.Enable == TRUE) {
		Block_AllMovedata.Count++;//�J�E���g�A�b�v
		//�ړ����鋗���̌v�Z
		double fX, fY, tX, tY;
		Convert_Ingame_FromBlock(Block_AllMovedata.FromX, Block_AllMovedata.FromY, 0, 0, &fX, &fY);
		Convert_Ingame_FromBlock(Block_AllMovedata.ToX, Block_AllMovedata.ToY, 0, 0, &tX, &tY);
		double FMD = getDistance(fX, fY, tX, tY);	//�ŏI�I�Ȉړ�����
		double MD = getMoveDistance(Block_AllMovedata.a, Block_AllMovedata.MaxSpeed, Block_AllMovedata.Count);	//���݂̈ړ�����
		if (FMD <= MD) {//�ړ�����

			Block_AllMove(Block_AllMovedata.ToX, Block_AllMovedata.ToY);
			Block_AllMovedata.Enable = FALSE;//�ړ��𖳌���(Block_AllMove���Ă��炷�邱�ƁI)

			////�Q�[���I�[�o�[�̔�����s��
			//if (JudgeGameOver() != 0) {
			//	PauseRequest(PauseMode_GameOver);	//�|�[�Y���N�G�X�g
			//}

			UpdateBlockRequest(gameCycle);	//���݂̃Q�[���T�C�N���Ɋ��荞�ތ`�Ńu���b�N�̃A�b�v�f�[�g������
		}
		return;
	}

	switch (gameCycle) {
	case GameCycle_FALL:
		if (getFallBlock_Interval() > 30) {
			Count_Turn++;
			Create_FallBlock();//�O��̗����u���b�N�I�������莞�Ԍ�ɗ����u���b�N�̍ďo��
		}
		//�����u���b�N�̗�������
		if (Update_FallBlock()) {
			//����������͌v�Z���s��
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
	{
		if (Count_Turn % 4 == 0 || getBlock_maxUpper() > BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL) {
			//������u���b�N�𕦂���
			under_Block();
		}
		else if (Count_Turn % 7 == 0) {
			int ran[5];
			randomTable.getRand_num(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT, ran, ARRAY_LENGTH(ran));
			for (int i = 0; i < ARRAY_LENGTH(ran); i++) {
				add_FraldBlock(ran[i], BLOCK_PADDINGUP, BLOCK_TYPE_TREE);
			}
		}
		UpdateBlockRequest(GameCycle_FALL);
	}
	break;
	case GameCycle_Update://�u���b�N�̌v�Z
		Update_FieldBlock();
		break;
	}
}

//�����u���b�N�̗�������(TRUE�ŗ����u���b�N�̗����I��)
int Phase_GameMain::Update_FallBlock() {
	if (!isFallBlock_Enable()) {
		//�����̎��̓C���^�[�o���J�E���g�����Z���I��
		fallBlockInfo.Counter--;
		return FALSE;
	}

	//�ȉ��L���ȂƂ�
	fallBlockInfo.Counter++;	//�J�E���^�����Z

	if (isFallBlock_Falling()) {//�������̏ꍇ
		fallBlockInfo.FallCount--;
		if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 20;	//�����������[�h�̏ꍇ�J�E���g������ɓ����

		if (fallBlockInfo.FallCount < 0)		fallBlockInfo.FallCount = 0;	//�����J�E���g��0�ȉ����Ɠs���������̂�
		if (fallBlockInfo.Key_LRMove > 0) {
			//�E�ړ�
			if (FallBlock_MoveX(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);

		}
		if (fallBlockInfo.Key_LRMove < 0) {
			//���ړ�
			if (FallBlock_MoveX(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota > 0) {
			//���v���ɉ�]
			if (FallBlock_Rotate(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota < 0) {
			//�����v���ɉ�]
			if (FallBlock_Rotate(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else							SoundEffect_Play(SE_TYPE_Graze);
		}

		if (fallBlockInfo.FallCount <= 0) {//�J�E���g0�ȉ��ŗ���
			fallBlockInfo.FallCount = 60;	//�J�E���g��߂�(�����Ŗ߂��Ȃ���FallBlock_MoveY�֐��ňړ������Ɣ��肳��A���܂������Ȃ�)
											/*�������悤�Ƃ��Ė�����������J�E���g��0�ɂ�������������j*/
			if (FallBlock_MoveY(1) == 0) {	//�����o���Ȃ�����
				fallBlockInfo.FallCount = -1;	//�����J�E���g�̖�����
				printLog_I(_T("�u���b�N�̗����I��"));
				FallBlock_addField();	//�t�B�[���h�ɗ����u���b�N��ݒu
				SoundEffect_Play(SE_TYPE_DecisionSelect);
				return TRUE;
			}
		}
	}

	//�L�[���͂ɂ���Ԃ̃��Z�b�g
	fallBlockInfo.Key_FlagFirstFall = FALSE;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	return FALSE;
}

//�t�B�[���h�u���b�N�ׁ̍X�Ƃ����v�Z���[�v
int Phase_GameMain::Update_FieldBlock() {
	/*
	�Q�[���X�V���[�v
	0.����������(�ŏ���1�x�̂ݎ��s)
	1.�ω����[�V����
	2.�d�͌v�Z
	3.�ړ����[�V����
	4.�u���b�N�̓������
	5.�ω����[�V����
	6.�d�͌v�Z
	7.�ړ����[�V����
	8.�u���b�N�̏������聨�����u���b�N�����̏ꍇ��11��
	9.�ω����[�V����
	10.�d�͌v�Z
	11.�ړ����[�V��������7��
	12.�X�V���[�v�I��
	*/


	switch (Loop_No) {
	case 0://������

		ChainCount = 0;	//�A���J�E���g�����Z�b�g����
		gameCycleFirstCallFlag = FALSE;	//�Q�[���T�C�N�����ύX���ꂽ���̃t���O��FALSE�ɐݒ肷��

		//��ʊO�u���b�N���폜����
		Block_Delete_OutScreen();

		if (!gameCycleFirstCallFlag) {
			Loop_No = 1;
			printLog_I(_T("�ω����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		break;
	case 1://�ω����[�V����
		if (Update_ChangeMotion() == FALSE) {
			//�ω����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 2;
				printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 2://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 3;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 3://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 4;
				printLog_I(_T("�u���b�N�̓�����ʂֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 4://�u���b�N�̓������
		Block_Black_Func();		//���u���b�N�̐F�ύX
		Block_Rainbow_Func();	//���F�u���b�N�̐F��ύX
		Block_BOMB_Func();		//���e�u���b�N�̏���
		Block_2BOMB_Func();		//2���e�u���b�N�̏���
		Block_BOMBColor_Func();	//���F���e�u���b�N�̏���
		Loop_No = 5;
		printLog_I(_T("�ω����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 5://�ω����[�V����
		if (Update_ChangeMotion() == FALSE) {
			//�ω����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 6;
				printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 6://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 7;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 7://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 8;
				printLog_I(_T("�u���b�N�̏�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 8://�u���b�N�̏�������
		if (Block_Delete() > 0) {
			//�u���b�N�̏������肪�����
			ChainCount++;	//�A���J�E���g�����Z����
			//�A���J�E���g��`�悷��(�t���C�e�L�X�g)
			if (ChainCount >= 2) flyText.addFlyText(GAMEWINDOW_WIDTH / 2., GAMEWINDOW_HEIGHT / 2., 60, FONTTYPE_GenJyuuGothicLHeavy_Edge60, GetColor(200, 200, 0), _T("%d�A���I�I"), ChainCount);


			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Loop_No = 9;
			printLog_I(_T("�ω����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		else {
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 12;
				printLog_I(_T("�I�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 9://�ω����[�V����
		if (Update_ChangeMotion() == FALSE) {
			//�ω����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 10;
				printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 10://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 11;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 11://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 8;
				printLog_I(_T("�u���b�N�̏�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 12://�I��
			//���S������s��
		if (JudgeGameOver() != 0) {
			//�Q�[���I�[�o�[���C���𒴂�����j������Ńu���b�N��j�󂷂�
			//Lay_BlockDel();
			PauseRequest(PauseMode_GameOver);
			//UpdateBlockRequest(GameCycle_Update);
		}

		if (gameCycleFirstCallFlag) {
			Loop_No = 0;
			printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		else {

			Loop_No = -1;
			printLog_I(_T("�u���b�N�v�Z���[�v�̏I��"));
			setGameCycle(Loop_Next);
		}
		break;
	default:
		printLog_E(_T("�s����Loop_No���w�肳��܂���(�������[�v)(Loop_No=%d)"), Loop_No);
		break;
	}
	return 0;
}

//�ړ����[�V�����̍X�V(�ړ����[�V�������s��ꂽ�Ƃ���TRUE)
int Phase_GameMain::Update_MoveMotion() {
	int count = 0;//�ω��������s�����u���b�N�̐�

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//�ړ����[�V����
			if (field[x][y].blockMoveMotion.Enable) {
				field[x][y].blockMoveMotion.Count++;//�J�E���g�A�b�v
													//�ړ����鋗���̌v�Z
				double fX, fY, tX, tY;
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, 0, 0, &fX, &fY);
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY, 0, 0, &tX, &tY);
				double FMD = getDistance(fX, fY, tX, tY);	//�ŏI�I�Ȉړ�����
				double MD = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//���݂̈ړ�����
				if (FMD <= MD) {//�ړ�����
					field[x][y].blockMoveMotion.Enable = FALSE;//�ړ��𖳌���
				}
				count++;	//�ړ�����
			}
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//�ω����[�V�����̍X�V(�ω����[�V�������s��ꂽ�Ƃ���TRUE)
int Phase_GameMain::Update_ChangeMotion() {
	int count = 0;//�ړ��������s�����u���b�N�̐�

	//�ω����[�V�����̃J�E���g�A�b�v
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//�ω����[�V����
			if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
				field[x][y].blockChangeMotion.Count++;//�J�E���g�A�b�v
				if (field[x][y].blockChangeMotion.Count > field[x][y].blockChangeMotion.Length) {//���[�V��������
					field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;//�ω����[�V�����𖳌���
				}
				count++;
			}
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//�J�E���^�̃J�E���g�A�b�v
void Phase_GameMain::Update_Counter() {

	//���ۂɑ�������Ă���o�߃t���[�����̉��Z
	if (getPauseMode() == PauseMode_NO
		&& Block_AllMovedata.Enable == FALSE
		&& gameCycle == GameCycle_FALL) {
		Count_PlayTime++;
	}

	//�X�e�[�W�o�ߎ��Ԃ̃J�E���g�A�b�v(�ʏ�v���C���ɉ��Z����)
	if (getPauseMode() == PauseMode_NO) {
		Count_GameTime++;
	}

	//�Q�[���o�߃t���[�����̃J�E���g�A�b�v
	if (getPauseMode() != PauseMode_NOMAL) {
		Count_Time++;
	}

	//�|�[�Y���̃J�E���^
	if (getPauseMode() != PauseMode_NO)	Count_Pause++;
}

//Update��ɌĂ΂��
void Phase_GameMain::Update_Final() {
	/*�`��X���b�h�p�̍��W���v�Z����*/

	//�t�B�[���h�S�̂̃Y�����v�Z
	double Field_PaddingX = 0;
	double Field_PaddingY = 0;
	if (Block_AllMovedata.Enable) {//�S�̂��炷���L���ȏꍇ
		double D = getMoveDistance(Block_AllMovedata.a, Block_AllMovedata.MaxSpeed, Block_AllMovedata.Count);	//���݂̈ړ������̌v�Z
		double Rota = getRotation(Block_AllMovedata.FromX, Block_AllMovedata.FromY, Block_AllMovedata.ToX, Block_AllMovedata.ToY);
		//��̌v�Z���ʂ��A�`����W�̌v�Z
		Field_PaddingX += D * cos(deg_to_rad(Rota));
		Field_PaddingY += D * sin(deg_to_rad(Rota));
	}
	//�t�B�[���h�u���b�N�̍��W�v�Z
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//�`���̍��W���v�Z����
			double X, Y;
			if (field[x][y].blockMoveMotion.Enable) {
				//�ړ����[�V�����L��
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, 0.5, 0.5, &X, &Y);	//�ړ������W�̌v�Z
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//���݂̈ړ������̌v�Z
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//��̌v�Z���ʂ��A�`����W�̌v�Z
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//�ړ����[�V��������
				Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
			}

			//�S�̂��炵�̕��`����W�����炷
			X += Field_PaddingX;
			Y += Field_PaddingY;

			//�Q�[���I�[�o�[���߂��ꍇ�͍��E�ɗh�炷
			if (getBlockColor(x, GAMEOVER_BORDER + 2) != BLOCK_TYPE_NO) {
				if (getBlockColor(x, GAMEOVER_BORDER) != BLOCK_TYPE_NO)	X += getGraph_Sin(getCountTime() * 30, 3, 0);
				X += randomTable.getRand(-2, 2, getCountTime() + x*y + y);
			}

			//���W�̋L�^
			field[x][y].DrawPlaceX = X;
			field[x][y].DrawPlaceY = Y;
		}
	}

}

//�I������(�`�揈��)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);

	DeleteGraph(Tex_BlockRED);
	DeleteGraph(Tex_BlockRED_ARROW_X);
	DeleteGraph(Tex_BlockRED_ARROW_Y);
	DeleteGraph(Tex_BlockRED_ARROW_XY);
	DeleteGraph(Tex_BlockRED_ARROW_XY2);
	DeleteGraph(Tex_BlockBLUE);
	DeleteGraph(Tex_BlockBLUE_ARROW_X);
	DeleteGraph(Tex_BlockBLUE_ARROW_Y);
	DeleteGraph(Tex_BlockBLUE_ARROW_XY);
	DeleteGraph(Tex_BlockBLUE_ARROW_XY2);
	DeleteGraph(Tex_BlockYELLOW);
	DeleteGraph(Tex_BlockYELLOW_ARROW_X);
	DeleteGraph(Tex_BlockYELLOW_ARROW_Y);
	DeleteGraph(Tex_BlockYELLOW_ARROW_XY);
	DeleteGraph(Tex_BlockYELLOW_ARROW_XY2);
	DeleteGraph(Tex_BlockGREEN);
	DeleteGraph(Tex_BlockGREEN_ARROW_X);
	DeleteGraph(Tex_BlockGREEN_ARROW_Y);
	DeleteGraph(Tex_BlockGREEN_ARROW_XY);
	DeleteGraph(Tex_BlockGREEN_ARROW_XY2);
	DeleteGraph(Tex_BlockPURPLE);
	DeleteGraph(Tex_BlockPURPLE_ARROW_X);
	DeleteGraph(Tex_BlockPURPLE_ARROW_Y);
	DeleteGraph(Tex_BlockPURPLE_ARROW_XY);
	DeleteGraph(Tex_BlockPURPLE_ARROW_XY2);
	DeleteGraph(Tex_BlockTREE);
	DeleteGraph(Tex_BlockBLACK);
	DeleteGraph(Tex_BlockRAINBOW);
	DeleteGraph(Tex_BlockFireEffect);
	DeleteGraph(Tex_BlockFireEffect2);
	DeleteGraph(Tex_BlockCenterEffect);
	DeleteGraph(Tex_BlockBOMB);
	DeleteGraph(Tex_Block2BOMB);
	DeleteGraph(Tex_BlockBOMB_Color);
	DeleteGraph(Tex_BlockBack);

	DeleteGraph(haikei);
	DeleteGraph(Tex_FieldBack);


	DeleteSoundMem(BGM);

}

//�I������(�v�Z����)
void Phase_GameMain::Finalize_Update() {

}

//�L�[����
void Phase_GameMain::GameMain_Key() {

	//�|�[�Y����
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		if (getPauseMode() == PauseMode_NOMAL) {
			//�|�[�Y��ԉ���
			SoundEffect_Play(SE_TYPE_ButtonCancel);
			PauseRequest(PauseMode_NO);	//�|�[�Y���
		}
		else if (getPauseMode() == PauseMode_NO) {
			//�|�[�Y��
			pauseMenu.setSelecedtItem(0);
			SoundEffect_Play(SE_TYPE_Pause);
			PauseRequest(PauseMode_NOMAL);	//�|�[�Y���
		}
	}

	if (getPauseMode() != PauseMode_NO)	return;//�|�[�Y�������������ꍇ�͂��̐�͏��������Ȃ�

	if (getKeyBind(KEYBIND_UP) == 1) {
		//�u���b�N�̐ݒu
		//���E�h�~
		int Flag = TRUE;//���S�̈�Ƀu���b�N����������FALSE�ɂȂ�
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < GAMEOVER_BORDER + 1; y++) {
				if (getBlockColor(x, y) != BLOCK_TYPE_NO) {
					//�Ȃ񂩃u���b�N������ꍇ
					Flag = FALSE;
					break;
				}
			}
		}
		if (Flag)	under_Block();//��Ƀu���b�N���Ȃ��ꍇ�Ɏ��s�����


	}

	if (isFallBlock_Falling() && !Block_AllMovedata.Enable) {
		if (getKeyBind(KEYBIND_DOWN) > 0) {//�����������[�h
			fallBlockInfo.Key_FlagFirstFall = TRUE;
		}
		if (getKeyBind(KEYBIND_RIGHT) == 1) {//�E�ړ�
			fallBlockInfo.Key_LRMove++;
		}
		if (getKeyBind(KEYBIND_LEFT) == 1) {//���ړ�
			fallBlockInfo.Key_LRMove--;
		}
		if (getKeyBind(KEYBIND_ROTAL) == 1) {//�����v���
			fallBlockInfo.Key_LRRota--;
		}
		if (getKeyBind(KEYBIND_ROTAR) == 1) {//���v���
			fallBlockInfo.Key_LRRota++;
		}
	}
}

//�u���b�N�̍��W�H����C���Q�[���̍��W���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
void Phase_GameMain::Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE + XVal*BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE + YVal*BLOCK_SIZE;
	}
}

//�|�[�Y��Ԃ̎擾
Phase_GameMain::PauseMode Phase_GameMain::getPauseMode() {
	return Flag_Pause;
}

//�|�[�Y��Ԃ̃��N�G�X�g
void Phase_GameMain::PauseRequest(PauseMode pauseMode) {

	switch (pauseMode) {
	case PauseMode_NO:
		printLog_I(_T("�y�|�[�Y�����z���N�G�X�g"));
		break;
	case PauseMode_NOMAL:
		//�Q�[���I�[�o�[�̃��N�G�X�g������ꍇ�͏㏑�����Ȃ�
		if (Flag_pauseRequest == PauseMode_GameOver)	return;
		printLog_I(_T("�y�ʏ�|�[�Y�z���N�G�X�g"));
		pauseMenu.setItemEnable(TRUE, 0);	//����0��L��
		break;
	case PauseMode_GameOver:
		printLog_I(_T("�y�Q�[���I�[�o�[�|�[�Y�z���N�G�X�g"));
		pauseMenu.setItemEnable(FALSE, 0);	//����0�𖳌���
		break;
	}
	Flag_pauseRequest = pauseMode;
}


//�����u���b�N�����������ǂ����̎擾(TRUE�ŗ�����)
int Phase_GameMain::isFallBlock_Falling() {
	if (!isFallBlock_Enable())	return FALSE;
	return (fallBlockInfo.FallCount >= 0) ? TRUE : FALSE;
}

//�����u���b�N���L�����ǂ����̎擾(TRUE�ŗL��)
int Phase_GameMain::isFallBlock_Enable() {
	return (fallBlockInfo.Enable) ? TRUE : FALSE;
}

//�����u���b�N�𐶐�����(�߂�l:������TRUE)
int Phase_GameMain::Create_FallBlock() {
	//if (fallblock_Pack == NULL)	return FALSE;

	if (isFallBlock_Enable()) {
		printLog_C(_T("�������̃u���b�N�����łɑ��݂��邽�߁A�����u���b�N��V���ɒǉ��o���܂���ł���"));
		return FALSE;
	}

	//�u���b�N�ҋ@��̐擪�̗v�f���琶������

	//�u���b�N���̃R�s�[
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			fallBlockInfo.BlockID[i][j] = waitBlockinfo[0].BlockID[i][j];
		}
	}

	//�g���ݒ�̃R�s�[
	fallBlockInfo.PlaceX = waitBlockinfo[0].PlaceX;
	fallBlockInfo.PlaceY = waitBlockinfo[0].PlaceY;
	fallBlockInfo.Flag_Rotate = waitBlockinfo[0].Flag_Rotate;


	//�����J�E���g��60�ɐݒ�
	fallBlockInfo.FallCount = 60;

	//�����u���b�N�̂��̑��̏��̏�����
	fallBlockInfo.Counter = 0;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	fallBlockInfo.Key_FlagFirstFall = FALSE;

	//�L��
	fallBlockInfo.Enable = TRUE;

	printLog_I(_T("�����u���b�N�́y�V�K�����z"));

	//�u���b�N�ҋ@���i�߂�
	Create_Wait_Block();

	return TRUE;
}

//�����u���b�N�̑O��̗�������̃C���^�[�o���̎擾(�����u���b�N�����݂���Ƃ���0���Ԃ�܂�)
int Phase_GameMain::getFallBlock_Interval() {
	if (isFallBlock_Enable())	return 0;
	return (-fallBlockInfo.Counter);
}

//�����u���b�N�̖�����
void Phase_GameMain::Delete_FallBlock() {
	if (!isFallBlock_Enable())	return;	//���������L���Ŗ������͖���

	fallBlockInfo.Counter = 0;		//�J�E���^��0�ɂ��ǂ�
	fallBlockInfo.Enable = FALSE;	//�����u���b�N�̖�����

	printLog_I(_T("�����u���b�N�́y�����z"));
}

//�����u���b�N��X�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
int Phase_GameMain::FallBlock_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isFallBlock_Falling())		return 0;	//���������������Ŗ������͖���

	MoveVal = getFallBlockVal_MoveX(MoveVal, CollisionFieldBlock);

	//���炵�̔��f
	fallBlockInfo.PlaceX += MoveVal;




	return MoveVal;
}

//�����u���b�N��X�������Ɉړ��\���ǂ����̎擾(|�ړ��o�����|<=MoveVal)(�܂�0�ňړ��s��)
int Phase_GameMain::getFallBlockVal_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isFallBlock_Falling())		return FALSE;	//���������������Ŗ������͈ړ��s��


	//���j:���񂾂�MoveVal��傫�����Ă���
	int Minus = FALSE;//�}�C�i�X�t���O
	if (MoveVal < 0) {
		//�������]
		MoveVal = -MoveVal;
		Minus = TRUE;
	}

	for (int i = 0; i < MoveVal; i++) {
		//�[���I�Ɉړ��������Ƃɂ���
		int pX = 0;
		if (Minus)	pX = fallBlockInfo.PlaceX - (i + 1);	//���̕���
		else		pX = fallBlockInfo.PlaceX + (i + 1);	//���̕���

															//���̃u���b�N�Ƃ̏d�Ȃ���v�Z����(�g�O���u���b�N������ƍl����)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {
					//�u���b�N�L��̏ꍇ�A�t�B�[���h�u���b�N�Ƃ̏d�Ȃ���m�F����
					if (CollisionFieldBlock) {//�t�B�[���h�u���b�N�Ƃ̂����蔻���L���ɂ���ꍇ
						if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//�ŊO�̃��[�v��������
						}
					}
					else {
						if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
							//��ʊO�u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//�ŊO�̃��[�v��������
						}
					}
				}
			}
		}
	}
	//���������ɖ߂�
	if (Minus) {
		MoveVal = -MoveVal;
	}

	return MoveVal;
}

//�����u���b�N��Y�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
int Phase_GameMain::FallBlock_MoveY(int MoveVal, int CollisionFieldBlock) {
	if (!isFallBlock_Falling())		return 0;	//���������������Ŗ������͖���

												//���j:���񂾂�MoveVal��傫�����Ă���
	int Minus = FALSE;//�}�C�i�X�t���O
	if (MoveVal < 0) {
		//�������]
		MoveVal = -MoveVal;
		Minus = TRUE;
	}

	for (int i = 0; i < MoveVal; i++) {
		//�[���I�Ɉړ��������Ƃɂ���
		int pY = 0;
		if (Minus)	pY = fallBlockInfo.PlaceY - (i + 1);	//���̕���
		else		pY = fallBlockInfo.PlaceY + (i + 1);	//���̕���

															//���̃u���b�N�Ƃ̏d�Ȃ���v�Z����(�g�O���u���b�N������ƍl����)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (CollisionFieldBlock) {//�t�B�[���h�u���b�N�Ƃ̂����蔻���L���ɂ���ꍇ
						if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//�ŊO�̃��[�v��������
						}
					}
					else {
						if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
							//��ʊO�u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//�ŊO�̃��[�v��������
						}
					}
				}
			}
		}
	}

	//���������ɖ߂�
	if (Minus) {
		MoveVal = -MoveVal;
	}

	//���炵�̔��f
	fallBlockInfo.PlaceY += MoveVal;



	return MoveVal;
}

//�����u���b�N����]������(��]��1�Ŏ��v����90�x)(�߂�l�͎��ۂ̉�]��)
int Phase_GameMain::FallBlock_Rotate(int RotaVal) {
	if (!isFallBlock_Falling())		return 0;	//���������������Ŗ������͖���

	if (fallBlockInfo.Flag_Rotate == FALSE)	return 0;//��]�������̏ꍇ�͉�]���Ȃ�

												//���j:���񂾂�MoveVal��傫�����Ă���
	int Minus = FALSE;//�}�C�i�X�t���O
	if (RotaVal < 0) {
		//�������]
		RotaVal = -RotaVal;
		Minus = TRUE;
	}


	int FLAG = FALSE;
	for (int i = 0; i < RotaVal; i++) {
		//�[���I�ɉ�]�������Ƃɂ���
		BLOCK_TYPE RotaBlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];
		if (Minus) {//�����v����90�x
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = fallBlockInfo.BlockID[x][y];
				}
			}
		}
		else {//���v����90�x
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = fallBlockInfo.BlockID[x][y];
				}
			}
		}

		//���̃u���b�N�Ƃ̏d�Ȃ���v�Z����(�g�O���u���b�N������ƍl����)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (RotaBlockID[x][y] != BLOCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
						//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						RotaVal = i;
						FLAG = TRUE;//�ŊO�̃��[�v��������
					}
				}
			}
		}

		if (FLAG) {
			break;
		}
		else {
			//��]���m�肷��
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					fallBlockInfo.BlockID[x][y] = RotaBlockID[x][y];
				}
			}
		}

	}

	//���������ɖ߂�
	if (Minus) {
		RotaVal = -RotaVal;
	}

	return RotaVal;
}

//�����u���b�N���t�B�[���h�u���b�N�ɕϊ�����(�܂�ݒu)
void Phase_GameMain::FallBlock_addField() {
	if (!isFallBlock_Enable())	return;	//���������L���Ŗ������͖���

	//���������u���b�N�ȊO�̓t�B�[���h�u���b�N�ɏ����ϊ����s��
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
			if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {
				int fX, fY;		//�u���b�N�̃t�B�[���h��̈ʒu
				BLOCK_TYPE fB;	//�ݒu����u���b�N�̎��
				fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
				fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
				fB = fallBlockInfo.BlockID[x][y];

				add_FraldBlock(fX, fY, fB);

			}
		}
	}
	printLog_I(_T("�����u���b�N�́y�ݒu�z"));

	//�����u���b�N�̖���������
	Delete_FallBlock();

}

//�t�B�[���h�Ƀu���b�N��ǉ�(�폜)����(�ړ����[�V�����͍폜����܂�)
/*
����
	Override:TRUE�Ńu���b�N�㏑����������(�����Ƃ���TRUE�ɂ��Ȃ��ƃu���b�N�͏����Ȃ���)
	MotionInit:TRUE�Ń��[�V�����f�[�^������������
	OutScreen:TRUE�ŉ�ʊO�Ƀu���b�N��ݒu���邱�Ƃ�����
	MotionType:�ω����[�V�����ݒ�(BlockChangeMotionType_NO�ŕω����[�V�����폜)
	MotionLengh:���[�V�����̒���
	Before:�O�ɐݒu����Ă����u���b�N
�߂�l
	TRUE�Őݒu(�폜)����
*/
int Phase_GameMain::add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int Override, int OutScreen, BLOCK_TYPE *Before, int UseVirtualField) {
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;	//�O�̃u���b�N���w�肷��
	BLOCK_TYPE before = BLOCK_TYPE_NO;	//�����O�̃u���b�N
	//��ʊO�u���b�N�͐ݒu�s��
	if (brock_type == BLOCK_TYPE_NUM)	return FALSE;
	//�u���b�N�����u���b�N���w�肳�ꂽ�ꍇ�͍폜�������s��


	//�u���b�N��ݒu���悤�Ƃ��Ă���ʒu�̌��݂̃u���b�N���擾����(�{���ΏۊO�͉�ʊO�u���b�N�ɂȂ�܂�)
	BLOCK_TYPE bt = getBlockColor(X, Y, TRUE, !OutScreen, UseVirtualField);
	if (Override) {
		//�㏑�����L���ȏꍇ
		if (bt == BLOCK_TYPE_NUM)	return FALSE;//��ʊO�u���b�N�̎��̂ݎ��s
	}
	else {
		//�㏑�������̏ꍇ
		if (bt != BLOCK_TYPE_NO)	return FALSE;//�u���b�N�����Əo�Ȃ��ꍇ�͎��s
	}

	//���݂̃u���b�N���L�^����
	before = getBlockColor(X, Y, TRUE, FALSE, UseVirtualField);

	if (UseVirtualField) {
		//�ݒ肳��Ă��郂�[�V�������폜����
		Virtualfield[X][Y].blockChangeMotion.Type = BlockChangeMotionType_NO;
		Virtualfield[X][Y].blockMoveMotion.Enable = FALSE;

		//�u���b�N�̐ݒu(�폜)
		Virtualfield[X][Y].fall_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
		Virtualfield[X][Y].move_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
		Virtualfield[X][Y].color = brock_type;	//�u���b�N�̒u������
	}
	else {
		//�ݒ肳��Ă��郂�[�V�������폜����
		field[X][Y].blockChangeMotion.Type = BlockChangeMotionType_NO;
		field[X][Y].blockMoveMotion.Enable = FALSE;

		//�u���b�N�̐ݒu(�폜)
		field[X][Y].fall_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
		field[X][Y].move_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
		field[X][Y].color = brock_type;	//�u���b�N�̒u������
	}


	if (brock_type == BLOCK_TYPE_NO) {
		//���̏ꍇ�̓u���b�N�폜�Ȃ̂�
		if (UseVirtualField)	printLog_I(_T("���z�t�B�[���h�u���b�N�́y�폜�z[%d][%d]"), X, Y);
		else					printLog_I(_T("�t�B�[���h�u���b�N�́y�폜�z[%d][%d]"), X, Y);
	}
	else {
		if (UseVirtualField)	printLog_I(_T("���z�t�B�[���h�u���b�N�́y�V�K�����z[%d][%d](type=%d)"), X, Y, brock_type);
		else					printLog_I(_T("�t�B�[���h�u���b�N�́y�V�K�����z[%d][%d](type=%d)"), X, Y, brock_type);
	}


	if (Before != NULL)	*Before = before;	//�O�̃u���b�N���w�肷��
	return TRUE;
}


//������u���b�N���킢�Ă���
void Phase_GameMain::under_Block() {
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN, BLOCK_WIDTHNUM_INGAME, 1);
	Block_AllMoveRequest(0, -1);	//�u���b�N�S�̂��ړ�
}

//�j������Ńu���b�N��j�󂷂�
void Phase_GameMain::Lay_BlockDel() {
	//���[�U�[�̃G�t�F�N�g
	lay.SetpointNum(3);	//�O�p�`��ݒ�
	lay.X[0] = GAMEWINDOW_WIDTH / 2.;
	lay.Y[0] = 0 + BLOCK_SIZE * BLOCK_PADDINGUP;
	lay.X[1] = 0;
	lay.Y[1] = BLOCK_SIZE * 3 + BLOCK_SIZE * BLOCK_PADDINGUP;
	lay.X[2] = 0;
	lay.Y[2] = BLOCK_SIZE * 12 + BLOCK_SIZE * BLOCK_PADDINGUP;
	Count_lay = 0;

	//�G�t�F�N�g�͈͂̃u���b�N�𖕏�����
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		for (int y = BLOCK_PADDINGUP + 3; y < BLOCK_PADDINGUP + 12; y++) {
			Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40, x*2 + 15);
		}
	}

	//�X�R�A�����炷
	score.addScore(1, -1'0000);
}

//�j������G�t�F�N�g�̍X�V
void Phase_GameMain::Update_Lay_BlockDel() {
	if (lay.getpointNum() == 3) {
		Count_lay++;
		if (Count_lay < 15) {
			//�������Ȃ�
		}
		else if(Count_lay < 45){
			//�t���[�����̊�������ʒu���v�Z����
			lay.X[1] = GAMEWINDOW_WIDTH * ((Count_lay - 15) / 30.);
			lay.X[2] = GAMEWINDOW_WIDTH * ((Count_lay - 15) / 30.);
		}
		else if (Count_lay < 55) {
			lay.X[1] = GAMEWINDOW_WIDTH;
			lay.X[2] = GAMEWINDOW_WIDTH;
		}
		else {
			lay.SetpointNum(0);
		}
	}
}

//�t�B�[���h�ɑ��݂��鍕�F�u���b�N�̐F�����肷��
void Phase_GameMain::Block_Black_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_BLACK) {//���u���b�N�̎�
				//�m���Ńu���b�N��ID������������
				int Val = (int)randomTable.getRand(0, 100);
				if (Val < 20)		field[x][y].color = BLOCK_TYPE_RED;		//�ԐF�u���b�N
				else if (Val < 40)	field[x][y].color = BLOCK_TYPE_BLUE;	//�F�u���b�N
				else if (Val < 60)	field[x][y].color = BLOCK_TYPE_YELLOW;	//���F�u���b�N
				else if (Val < 80)	field[x][y].color = BLOCK_TYPE_GREEN;	//�ΐF�u���b�N
				else 				field[x][y].color = BLOCK_TYPE_PURPLE;	//���F�u���b�N

				//�ω����[�V�����̐ݒ�
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_BLACK, 20, 0);
			}
		}
	}
}

//�t�B�[���h�ɑ��݂�����F�u���b�N�̐F�����肷��(�����珇��)
void Phase_GameMain::Block_Rainbow_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
			if (field[x][y].color == BLOCK_TYPE_RAINBOW) {//���F�u���b�N�̎�
				if (getBlockColor(x, y + 1) == BLOCK_TYPE_NO) {
					//���Ƀu���b�N������
					//�m���Ńu���b�N��ID������������
					int Val = (int)randomTable.getRand(0, 100);
					if (Val < 20)		field[x][y].color = BLOCK_TYPE_RED;		//�ԐF�u���b�N
					else if (Val < 40)	field[x][y].color = BLOCK_TYPE_BLUE;	//�F�u���b�N
					else if (Val < 60)	field[x][y].color = BLOCK_TYPE_YELLOW;	//���F�u���b�N
					else if (Val < 80)	field[x][y].color = BLOCK_TYPE_GREEN;	//�ΐF�u���b�N
					else 				field[x][y].color = BLOCK_TYPE_PURPLE;	//���F�u���b�N

				}
				else {
					//���Ƀu���b�N������ꍇ
					field[x][y].color = getBlockColor(x, y + 1);
				}

				//�ω����[�V�����̐ݒ�
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_RAINBOW, 20, 0);


			}
		}
	}
}

//�t�B�[���h�ɑ��݂��锚�e�u���b�N�𔚔j����
void Phase_GameMain::Block_BOMB_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_BOM) {//���e�u���b�N�̎�
				//���g�̍폜
				if (Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;

				//���͂̃u���b�N���폜����(���e�u���b�N�͍폜���Ȃ�)
				if (getBlockColor(x + 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 2, y, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 2, y, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}
				if (getBlockColor(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 1, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 2, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}
				if (getBlockColor(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 1, BlockChangeMotionType_EXPLOSION, 40, 5))	DeleteNum++;
				}
				if (getBlockColor(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 2, BlockChangeMotionType_EXPLOSION, 40, 15))	DeleteNum++;
				}


				if (getBlockColor(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y - 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y - 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y + 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y + 1, BlockChangeMotionType_EXPLOSION, 40, 10))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//�t�B�[���h�ɑ��݂���2���e�u���b�N�𔚔j����
void Phase_GameMain::Block_2BOMB_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_2BOM) {//���e�u���b�N�̎�
				//���g�̍폜
				if (Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;

				//2�אڂ��Ă���u���b�N��j�󂷂�
				DeleteNum += Block_Delete(2, FALSE);
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//�t�B�[���h�ɑ��݂��铯�F���e�u���b�N�𔚔j����
void Phase_GameMain::Block_BOMBColor_Func() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_BOM_Color) {//���e�u���b�N�̎�
				//���g�̍폜
				if (Block_Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				//�^���̃u���b�N�̐F���擾����
				BLOCK_TYPE under = getBlockColor(x, y + 1);

				//���F�u���b�N���폜����
				for (int x2 = BLOCK_PADDINGLEFT; x2 < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x2++) {
					for (int y2 = BLOCK_PADDINGUP; y2 < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y2++) {
						Block_Delete_Color(x2, y2, under, BlockChangeMotionType_EXPLOSION, 40);
					}
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}


//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���TRUE����)(��4�����͎��ۂɕ`�悳���G���A�ȊO����ʊO�ɂ���ꍇTRUE,�u���b�N��񂪖����ʒu����ʊO�ɂ���ꍇ��FALSE��ݒ肷��)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock, int InGame, int UseVirtualField) {

	//��ʊO����
	if (InGame) {
		//���ۂ̕`��G���A�Ŕ���
		if (X < BLOCK_PADDINGLEFT || (BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT) <= X)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
		if (Y < BLOCK_PADDINGUP || (BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN) <= Y)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
	}
	else {
		//�t�B�[���h��񂩂画�肷��
		if (X < 0 || BLOCK_WIDTHNUM <= X)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
		if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
	}

	return ((UseVirtualField) ? Virtualfield[X][Y].color : field[X][Y].color);

}

//�t�B�[���h�u���b�N���d�͂ŗ���������
void Phase_GameMain::Block_Gravity(int InGameOnly) {
	int sX = 0, sY = 0;
	int eX = BLOCK_WIDTHNUM, eY = BLOCK_HEIGHTNUM;

	if (InGameOnly) {
		sX = BLOCK_PADDINGLEFT;
		sY = BLOCK_PADDINGUP;

		eX = BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT;
		eY = BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;
	}

	for (int x = sX; x < eX; x++) {
		//�񂲂ƂɃu���b�N�����R�s�[����
		field_info t[BLOCK_HEIGHTNUM];
		for (int y = sY; y < eY; y++) {
			t[y] = field[x][y];
			field[x][y].color = BLOCK_TYPE_NO;
		}
		int Count = eY - 1;
		//���̒i���瑶�݂���u���b�N����ג���(�t����)
		for (int y = eY - 1; y >= sY; y--) {
			if (t[y].color != BLOCK_TYPE_NO) {
				field[x][Count] = t[y];
				//�������[�V����(�J�E���g���ړ���Ay���ړ����ɂȂ�)
				Block_SetMoveMotion(x, Count, x, y, x, Count, 0.3, 15);
				Count--;
			}
		}
	}

	printLog_I(_T("�u���b�N�ɏd�͌v�Z���s���܂���"));
}

//�t�B�[���h�u���b�N�𒼐ڍ폜����(�폜���ꂽ��TRUE)
int Phase_GameMain::Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int MotionLengh, int Delay) {
	if (getBlockColor(X, Y, FALSE, FALSE) == BLOCK_TYPE_NO)	return FALSE;//�u���b�N�������������݂��Ȃ��ꍇ�͉������Ȃ�
	BLOCK_TYPE bt = BLOCK_TYPE_NO;	//�폜���ꂽ�u���b�N�̎��
	//�u���b�N�̍폜���s��
	int flag = add_FraldBlock(X, Y, BLOCK_TYPE_NO, TRUE, TRUE, &bt);

	if (flag) {
		//�u���b�N���폜���ꂽ
		if (PlayMotion == BlockChangeMotionType_EXPLOSION) {
			Block_SetChangeMotion_EXPLOSION(X, Y, MotionLengh, bt, Delay);	//���[�V�����̐���
		}
		else if (PlayMotion == BlockChangeMotionType_SMALL) {
			Block_SetChangeMotion_SMALL(X, Y, MotionLengh, bt, Delay);	//���[�V�����̐���
		}
	}

	return ((flag) ? TRUE : FALSE);
}

//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜(�폜���ꂽ��TRUE)
int Phase_GameMain::Block_Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion, int MotionLengh) {
	if (!isSameColorBlock(type, getBlockColor(X, Y)))	return FALSE;//�Ⴄ�F�̃u���b�N�̏ꍇ�͍폜���Ȃ�

	return Block_Delete_Direct(X, Y, PlayMotion, MotionLengh);
}

//�A������t�B�[���h�u���b�N���폜����(���łɏ����ɂ���Ĕ���������ʂ���������)(���������u���b�N�̐�)
int Phase_GameMain::Block_Delete(const int Len, int Flag_Event) {
	//��ʓ��̑��݂���u���b�N�݂̂Ōv�Z����


	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	CreateSequenceCountTable(DeleteFlag, BLOCK_PADDINGLEFT, BLOCK_PADDINGUP, BLOCK_WIDTHNUM_INGAME, BLOCK_HEIGHTNUM_INGAME);

	//�폜�O�̃u���b�N�̈ꗗ���쐬����
	BLOCK_TYPE old[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			old[x][y] = getBlockColor(x, y);
		}
	}

	//�אڃu���b�N�̌v�Z���s��
	int Counter[BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM];	//ID���Ƃ̗אڃJ�E���g��
	int ID = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (DeleteFlag[x][y] == -1) {//���T���u���b�N
				Counter[ID] = 0;
				SequenceCount(x, y, ID, DeleteFlag, &(Counter[ID]));
				ID++;
			}
		}
	}

	//���u���b�N�̌��ʂ��ɔ�������
	int DelCount = 0;
	if (Flag_Event) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//�z��͈͓̔�
					if (Counter[DeleteFlag[x][y]] >= Len) {
						//�����̖��̏ꍇ
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_X ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_X ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_X ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_X ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_X) {
							//���[����E�[�܂ł̈����ꊇ����
							for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
								if (Block_Delete_Direct(i, y, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//�t���C�e�L�X�g�̐���
									double X, Y;
									Convert_Ingame_FromBlock(i, y, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
						//�����̖��̏ꍇ
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_Y) {
							//���[����E�[�܂ł̈����ꊇ����
							for (int i = 0; i < BLOCK_HEIGHTNUM; i++) {
								if (Block_Delete_Direct(x, i, BlockChangeMotionType_EXPLOSION, 40, abs(y - i) * 2)) {
									//�t���C�e�L�X�g�̐���
									double X, Y;
									Convert_Ingame_FromBlock(x, i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
						//�E��̖��̏ꍇ
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_XY) {
							//�΂߂Ɉꊇ����
							for (int i = 0; i < max(BLOCK_HEIGHTNUM, BLOCK_WIDTHNUM); i++) {
								if (Block_Delete_Direct(x + i, y - i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//�t���C�e�L�X�g�̐���
									double X, Y;
									Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
								if (Block_Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//�t���C�e�L�X�g�̐���
									double X, Y;
									Convert_Ingame_FromBlock(x - i, y + i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
						//�E���̖��̏ꍇ
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_XY2) {
							//�΂߂Ɉꊇ����
							for (int i = 0; i < max(BLOCK_HEIGHTNUM, BLOCK_WIDTHNUM); i++) {
								if (Block_Delete_Direct(x + i, y + i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//�t���C�e�L�X�g�̐���
									double X, Y;
									Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
								if (Block_Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, 40, abs(x - i) * 2)) {
									//�t���C�e�L�X�g�̐���
									double X, Y;
									Convert_Ingame_FromBlock(x - i, y - i, 0.5, 0.5, &X, &Y);
									flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
									score.addScore(0, 50);
									DelCount++;
								}
							}
						}
					}
				}
			}
		}
		//���̎��_�ō폜��������(�܂���u���b�N�ŏ����ꂽ)
		if (DelCount > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
	}


	BlockChangeMotionType DelMotion = BlockChangeMotionType_SMALL;
	int DelLen = 15;
	if (!Flag_Event) {
		DelMotion = BlockChangeMotionType_EXPLOSION;
		DelLen = 40;
	}
	//�אڂ��Ă���u���b�N���폜����
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//�z��͈͓̔�
				if (Counter[DeleteFlag[x][y]] >= Len) {
					//�폜
					if (Block_Delete_Direct(x, y, DelMotion, DelLen)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+100"));
						score.addScore(0, 100);
						DelCount++;
					}

					//���łɗאڂ�����؃u���b�N���폜
					if (Block_Delete_Color(x, y - 1, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//��
					}
					if (Block_Delete_Color(x, y + 1, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//��
					}
					if (Block_Delete_Color(x - 1, y, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//��
					}
					if (Block_Delete_Color(x + 1, y, BLOCK_TYPE_TREE, DelMotion, DelLen)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x + 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//�E
					}



				}
			}
		}
	}

	printLog_I(_T("�אڃu���b�N�̍폜�v�Z���s���܂���(%d�u���b�N)"), DelCount);


	return DelCount;
}

//SequenceCount�Ŏg�p����}�[�J�[�e�[�u�����쐬����(�L���ȃG���A)(TRUE�ŉ��z�̖ʂ��g�p����)
void Phase_GameMain::CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField) {
	if (deleteFlag == NULL)	return;



	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field_info *f = &(field[x][y]);
			if (UseVirtualField)	f = &(Virtualfield[x][y]);
			if (!(X <= x && x < X + W && Y <= y && y < Y + H) ||	//�͈͊O
				f->color == BLOCK_TYPE_NO ||
				f->color == BLOCK_TYPE_NUM ||
				f->color == BLOCK_TYPE_TREE ||
				f->color == BLOCK_TYPE_BLACK ||
				f->color == BLOCK_TYPE_RAINBOW ||
				f->color == BLOCK_TYPE_BOM ||
				f->color == BLOCK_TYPE_2BOM ||
				f->color == BLOCK_TYPE_BOM_Color) {		//���O�u���b�N
				deleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				deleteFlag[x][y] = -1;
			}
		}
	}
}

//��ʊO�̃u���b�N�����ׂč폜����(���������u���b�N�̐�)
int Phase_GameMain::Block_Delete_OutScreen() {
	int count = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (getBlockColor(x, y, TRUE, TRUE) == BLOCK_TYPE_NUM) {
				//��ʊO�u���b�N�̏ꍇ�͍폜
				if (Block_Delete_Direct(x, y)) {
					count++;
				}
			}
		}
	}

	printLog_I(_T("��ʊO�̃u���b�N�����ׂč폜(%d��)"), count);


	return count;
}

//�אڂ��铯�F�u���b�N�Ƀ}�[�J�[��t����
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter, int UseVirtualField) {
	if (deleteFlag == NULL)		return;		//�}�[�J�[��t����e�[�u�����Ȃ��ꍇ
	if (deleteFlag[x][y] != -1)	return;		//���T���u���b�N����Ȃ��ꍇ
	BLOCK_TYPE bt = ((UseVirtualField) ? Virtualfield[x][y].color : field[x][y].color);	//�u���b�N�̎�ނ��L�^����
	deleteFlag[x][y] = ID;	//�T���ς�(�T��ID��ݒ肷��)
	(*Counter)++;

	int OnlyColor = TRUE;

	BLOCK_TYPE NextBlock = ((UseVirtualField) ? Virtualfield[x + 1][y].color : field[x + 1][y].color);
	if (x + 1 < BLOCK_WIDTHNUM	&& isSameColorBlock(NextBlock, bt, OnlyColor))		SequenceCount(x + 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y + 1].color : field[x][y + 1].color);
	if (y + 1 < BLOCK_HEIGHTNUM	&& isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x - 1][y].color : field[x - 1][y].color);
	if (x - 1 >= 0 && isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y - 1].color : field[x][y - 1].color);
	if (y - 1 >= 0 && isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//�w�肵��2�̃u���b�N�����F�u���b�N���ǂ����̎擾(TRUE�œ��F)
int Phase_GameMain::isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int OnlyColorBlock) {
	if (OnlyColorBlock) {//�ȗ��v�Z�łȂ��Ƃ�
		//�F�̊T�O�̖����u���b�N�̏ꍇ
		if (type1 == BLOCK_TYPE_NO)			return FALSE;
		if (type1 == BLOCK_TYPE_TREE)		return FALSE;
		if (type1 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type1 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type1 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type1 == BLOCK_TYPE_BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_2BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_BOM_Color)	return FALSE;
		if (type1 == BLOCK_TYPE_NUM)		return FALSE;

		if (type2 == BLOCK_TYPE_NO)			return FALSE;
		if (type2 == BLOCK_TYPE_TREE)		return FALSE;
		if (type2 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type2 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type2 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type2 == BLOCK_TYPE_BOM)		return FALSE;
		if (type2 == BLOCK_TYPE_2BOM)		return FALSE;
		if (type2 == BLOCK_TYPE_BOM_Color)	return FALSE;
		if (type2 == BLOCK_TYPE_NUM)		return FALSE;
	}

	//���F����(����u���b�N�̏ꍇ)
	if (type1 == type2)	return TRUE;

	//���F����(��{�u���b�N�ɒ����čl���܂�)
	switch (type1) {
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY2:
		type1 = BLOCK_TYPE_RED;
		break;
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY2:
		type1 = BLOCK_TYPE_BLUE;
		break;
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY2:
		type1 = BLOCK_TYPE_YELLOW;
		break;
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY2:
		type1 = BLOCK_TYPE_GREEN;
		break;
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY2:
		type1 = BLOCK_TYPE_PURPLE;
		break;
	}
	switch (type2) {
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_RED_ARROW_XY2:
		type2 = BLOCK_TYPE_RED;
		break;
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_BLUE_ARROW_XY2:
		type2 = BLOCK_TYPE_BLUE;
		break;
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_YELLOW_ARROW_XY2:
		type2 = BLOCK_TYPE_YELLOW;
		break;
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_GREEN_ARROW_XY2:
		type2 = BLOCK_TYPE_GREEN;
		break;
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_X:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_Y:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY:
	case Phase_GameMain::BLOCK_TYPE_PURPLE_ARROW_XY2:
		type2 = BLOCK_TYPE_PURPLE;
		break;
	}
	//���F����
	if (type1 == type2)	return TRUE;

	return FALSE;
}

//�t�B�[���h�̃u���b�N�ړ��Ƀ��[�V������ݒ肷��
void Phase_GameMain::Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockColor(x, y, FALSE, FALSE) == BLOCK_TYPE_NO)	return;	//�u���b�N�������̏ꍇ�͏��������Ȃ�
	if (FromX == ToX && FromY == ToY)			return;	//�ړ������̏ꍇ�����������Ȃ�
	if (a <= 0)									return;	//�����x�����̐��̏ꍇ�����������Ȃ�
	if (MaxSpeed <= 0)							return;	//�ő呬�x�����̐��̏ꍇ�����������Ȃ�

	if (field[x][y].blockMoveMotion.Enable) {
		printLog_C(_T("�u���b�N�̈ړ����[�V�������㏑�����܂�"));
		field[x][y].blockMoveMotion.Enable = FALSE;
	}

	field[x][y].blockMoveMotion.ToX = ToX;
	field[x][y].blockMoveMotion.ToY = ToY;
	field[x][y].blockMoveMotion.FromX = FromX;
	field[x][y].blockMoveMotion.FromY = FromY;
	field[x][y].blockMoveMotion.a = a;
	field[x][y].blockMoveMotion.MaxSpeed = MaxSpeed;
	field[x][y].blockMoveMotion.Count = 0;

	field[x][y].blockMoveMotion.Enable = TRUE;

	printLog_I(_T("�u���b�N�Ɂy�ړ����[�V�����z��ݒ�"));
}

//�ړ����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
int Phase_GameMain::isBlock_PlayMoveMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].blockMoveMotion.Enable) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�t�B�[���h�̃u���b�N�ɕω����[�V������ݒ肷��(����P�̂Ŏg�p���Ď��̂��Ă��m��܂���)
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//�u���b�N����ʊO�̏ꍇ�͏��������Ȃ�
	if (MotionLength <= 0)									return;	//���������̐��̏ꍇ�����������Ȃ�

	if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
		printLog_C(_T("�u���b�N�ω����[�V�������㏑�����܂�"));
		field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;
	}

	field[x][y].blockChangeMotion.To = To;
	field[x][y].blockChangeMotion.From = From;
	field[x][y].blockChangeMotion.Length = MotionLength;
	field[x][y].blockChangeMotion.Count = -Delay;

	field[x][y].blockChangeMotion.Type = mtype;

	printLog_I(_T("�u���b�N�Ɂy�ω����[�V�����z��ݒ�[%d][%d]"), x, y);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��
void Phase_GameMain::Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength, int Delay) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == To)				return;		//�ω��悪�����ꍇ�͏��������Ȃ�
	if (To == BLOCK_TYPE_NO)	return;		//�ω��悪�u���b�N�����̏ꍇ�͏��������Ȃ�(�������`��o���Ȃ�����)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, From, To, MotionLength, Delay);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��(�ω����w��)
void Phase_GameMain::Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength, int Delay) {

	BLOCK_TYPE To = getBlockColor(x, y, FALSE, FALSE);
	if (from == To)				return;		//�ω��悪�����ꍇ�͏��������Ȃ�
	if (To == BLOCK_TYPE_NO)	return;		//�ω��悪�u���b�N�����̏ꍇ�͏��������Ȃ�(�������`��o���Ȃ�����)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, from, To, MotionLength, Delay);
}


//�t�B�[���h�̃u���b�N�ɕω����[�V����(����)��ݒ肷��
void Phase_GameMain::Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//�u���b�N�����݂��Ȃ��ꍇ�͖���

	Block_SetChangeMotion(x, y, BlockChangeMotionType_EXPLOSION, From, From, MotionLength, Delay);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�������Ȃ��ď�����)��ݒ肷��
void Phase_GameMain::Block_SetChangeMotion_SMALL(int x, int y, int MotionLength, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//�u���b�N�����݂��Ȃ��ꍇ�͖���

	Block_SetChangeMotion(x, y, BlockChangeMotionType_SMALL, From, From, MotionLength, Delay);
}

//�ω����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
int Phase_GameMain::isBlock_PlayChangeMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�Q�[���T�C�N����ݒ肷��
void Phase_GameMain::setGameCycle(GameCycle gamecycle) {
	if (gamecycle == GameCycle_NUM) {
		printLog_E(_T("�����ȃQ�[���T�C�N�����w�肳��܂���"));
		return;
	}

	GameCycle old = gameCycle;
	gameCycle = gamecycle;

	printLog_I(_T("�Q�[���T�C�N���̕ύX(%d��%d)"), old, gameCycle);
	gameCycleFirstCallFlag = TRUE;
}

//�u���b�N�����X�V����悤�Ƀ��N�G�X�g
void Phase_GameMain::UpdateBlockRequest(GameCycle Next) {
	if (Next == GameCycle_NUM) {
		printLog_E(_T("�������s���ł�"));
		return;
	}


	if (gameCycle != GameCycle_Update) {	//�u���b�N�X�V�T�C�N�������s���łȂ��ꍇ�́A
		//�v�Z���[�v�̏����ʒu��ݒ�
		Loop_No = 0;
	}

	//�u���b�N�v�Z�T�C�N���ֈڍs(���[�v�̍Đݒ�)
	setGameCycle(GameCycle_Update);

	//�ڍs��̃Q�[���T�C�N�����L�^����(�u���b�N�X�V���w�肳�ꂽ�ꍇ�͈ڍs���ݒ肵�Ȃ�)
	if (Next != GameCycle_Update) {
		Loop_Next = Next;
	}



	printLog_I(_T("�u���b�N�v�Z���[�v�ɓ���܂�(�I����=%d)"), Loop_Next);

}

//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ����郊�N�G�X�g������(�Q�[�����ꎞ��~���ē������܂�)
void Phase_GameMain::Block_AllMoveRequest(int X, int Y) {

	if (Block_AllMovedata.Enable)	return;//���łɃu���b�N���ړ����̏ꍇ�A��������


	Block_AllMovedata.ToX = X;
	Block_AllMovedata.ToY = Y;
	Block_AllMovedata.FromX = 0;
	Block_AllMovedata.FromY = 0;
	Block_AllMovedata.a = 0.1;
	Block_AllMovedata.MaxSpeed = 2;
	Block_AllMovedata.Count = 0;

	Block_AllMovedata.Enable = TRUE;

	printLog_I(_T("�u���b�N�S�̈ړ����ݒ肳��܂���(%d,%d)"), X, Y);
}

//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ�����(��ʊO�ɏo�Ă��܂��u���b�N�͏��ł��܂�)
void Phase_GameMain::Block_AllMove(int X, int Y) {
	//�����ɖ��ʂ������c

	//�ꎞ�ϐ�
	field_info t[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//���ۂɃu���b�N�����ׂĈړ�������

	//����ړ�
	if (X <= 0 && Y <= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//�͈͓��Ȃ畁�ʂɃR�s�[����
					field[x][y] = field[x - X][y - Y];
					if (field[x][y].blockMoveMotion.Enable) {//�ړ����[�V�������L���ȏꍇ�͈ړ����[�V�����ɕ␳��������
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("�u���b�N�S�̂�����ɂ��炵�܂���(%d,%d)"), X, Y);
	}
	//�����ړ�
	else if (X <= 0 && Y >= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//�͈͓��Ȃ畁�ʂɃR�s�[����
					field[x][y] = field[x - X][y - Y];
					if (field[x][y].blockMoveMotion.Enable) {//�ړ����[�V�������L���ȏꍇ�͈ړ����[�V�����ɕ␳��������
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("�u���b�N�S�̂������ɂ��炵�܂���(%d,%d)"), X, Y);
	}
	//�E��ړ�
	else if (X >= 0 && Y <= 0) {
		for (int x = BLOCK_WIDTHNUM - 1; x >= 0; x--) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//�͈͓��Ȃ畁�ʂɃR�s�[����
					field[x][y] = field[x - X][y - Y];
					if (field[x][y].blockMoveMotion.Enable) {//�ړ����[�V�������L���ȏꍇ�͈ړ����[�V�����ɕ␳��������
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("�u���b�N�S�̂��E��ɂ��炵�܂���(%d,%d)"), X, Y);
	}
	//�E���ړ�
	else if (X >= 0 && Y >= 0) {
		for (int x = BLOCK_WIDTHNUM - 1; x >= 0; x--) {
			for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//�͈͓��Ȃ畁�ʂɃR�s�[����
					field[x][y] = field[x - X][y - Y];
					if (field[x][y].blockMoveMotion.Enable) {//�ړ����[�V�������L���ȏꍇ�͈ړ����[�V�����ɕ␳��������
						field[x][y].blockMoveMotion.FromX += X;
						field[x][y].blockMoveMotion.FromY += Y;
						field[x][y].blockMoveMotion.ToX += X;
						field[x][y].blockMoveMotion.ToY += Y;
					}
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Block_Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("�u���b�N�S�̂��E���ɂ��炵�܂���(%d,%d)"), X, Y);
	}

	//�������u���b�N���ړ�����(��ʊO�ɂ͍s���܂���)
	FallBlock_MoveX(X, FALSE);
	FallBlock_MoveY(Y, FALSE);

}

//���ۂɑ�������Ă���o�߃t���[�������擾����
int Phase_GameMain::getCountPlayTime() {
	return Count_PlayTime;
}

//�Q�[���̌o�߃t���[�������擾(�N���A�Œ�~���܂�)
int Phase_GameMain::getCountGameTime() {
	return Count_GameTime;
}

//�Q�[���̌o�߃t���[�������擾(�|�[�Y�ł̂ݒ�~����)
int Phase_GameMain::getCountTime() {
	return Count_Time;
}

//�w�肵���G���A�Ƀu���b�N��ݒu����(�������肪����Ȃ��悤�ɐݒu���܂�)
void Phase_GameMain::setBlock_Rect(int x, int y, int w, int h) {
	//���z�t�B�[���h�����X�V����
	Virtualfield_Update();

	for (int bl_X = x; bl_X < x + w; bl_X++) {
		for (int bl_Y = y; bl_Y < y + h; bl_Y++) {
			BLOCK_TYPE bt;
			int Count = 0;

			do {
				Count = 0;
				bt = GetRandomBlockType_UNDER();//�����_���Ńu���b�N�����肵���z�ݒu����
				add_FraldBlock(bl_X, bl_Y, bt, TRUE, TRUE, NULL, TRUE);
				int BlockFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
				//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
				CreateSequenceCountTable(BlockFlag, 0, 0, BLOCK_WIDTHNUM, BLOCK_HEIGHTNUM, TRUE);
				SequenceCount(bl_X, bl_Y, 0, BlockFlag, &Count, TRUE);
			} while (Count >= BLOCK_DELETE_LEN);

			add_FraldBlock(bl_X, bl_Y, bt, FALSE, TRUE);//�{�Ԃ̐ݒu

		}
	}
}

//�Q�[���I�[�o�[�ɂȂ��Ă��邩�ǂ����̊m�F
/*
�߂�l
0:�Q�[���I�[�o�[�ł͖���
1:�u���b�N����܂Őςݏオ���Ă��܂��ăQ�[���I�[�o�[
2:�����u���b�N�������u���b�N�Əd�Ȃ��Ă��܂��ăQ�[���I�[�o�[
*/
int Phase_GameMain::JudgeGameOver() {
	printLog_I(_T("�Q�[���I�[�o�[���ǂ����̔�����s���܂�"));
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < GAMEOVER_BORDER; y++) {
			if (getBlockColor(x, y, FALSE, FALSE) != BLOCK_TYPE_NO) {
				//0���(��ʏ�̌����Ȃ�����)�Ƀu���b�N���N������
				printLog_I(_T("�u���b�N����܂Őςݏオ���Ă��܂��ăQ�[���I�[�o�["));
				return 1;
			}
		}
	}

	//���ʂ͋N���Ȃ�
	if (isFallBlock_Enable()) {
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.BlockID[x][y] != BLOCK_TYPE_NO) {
					int fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
					int fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
					BLOCK_TYPE fB = getBlockColor(fX, fY, TRUE);	//�u���b�N�̎�ގ擾
					if (fB != BLOCK_TYPE_NO) {
						printLog_I(_T("�����u���b�N�������u���b�N�Əd�Ȃ��Ă��܂��ăQ�[���I�[�o�["));
						return 2;	//�����u���b�N�̉��̈ʒu�ɒʏ�u���b�N������
					}
				}
			}
		}
	}

	return 0;
}

//�����u���b�N�̑ҋ@��̍쐬
void Phase_GameMain::Create_Wait_Block() {

	//����l�߂�(�擪��0)
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo) - 1; i++) {
		waitBlockinfo[i] = waitBlockinfo[i + 1];
	}



	//�V�K�ɍ쐬���闎���u���b�N�̔z�u�p�^�[�������肷��(0�`3)
	const int Percent = (int)(randomTable.getRand(0, 100));
	int Pattern = 0;	//�u���b�N�̃p�^�[��
	if (Percent < 24) {
		Pattern = 0;
	}
	else if (Percent < 48) {
		Pattern = 1;
	}
	else if (Percent < 72) {
		Pattern = 2;
	}
	else if (Percent < 96) {
		Pattern = 3;
	}
	else {
		Pattern = 4;
	}


	//5���̊m���Ŕ��e��P�̂ŗ���������
	if (randomTable.getRand(0, 1000) < 50) {
		Pattern = 4;
	}

	//�����_���ɐݒu����u���b�N��2���肷��
	BLOCK_TYPE type1 = GetRandomBlockType_FALL();
	BLOCK_TYPE type2 = GetRandomBlockType_FALL();

	//�Ō���ҋ@�u���b�N�̔z�u������������
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[i][j] = BLOCK_TYPE_NO;
		}
	}


	//�u���b�N�̓�����ʂ�ݒ肷��
	waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = TRUE;


	//��Ɍ��߂��p�^�[�����u���b�N�̔z�u�����肷��(���łɃX�|�[���ʒu��)
	switch (Pattern) {
	case 0://�c�ŉ������S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][0] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP + 1;
		//printLog_D(_T("�c�ŉ������S�p�^�[��"));
		break;
	case 1://�c�ŏ㑤���S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][2] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("�c�ŏ㑤���S�p�^�[��"));
		break;
	case 2://���ō����S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[2][1] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("���ō����S�p�^�[��"));
		break;
	case 3://���ŉE���S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[0][1] = type1;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = type2;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("���ŉE���S�p�^�[��"));
		break;
	case 4://���F���e�̒P�̗���
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1] = BLOCK_TYPE_BOM_Color;

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//�������ŉ�]�s��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = FALSE;
		break;
	default:
		printLog_E(_T("�����u���b�N�z�u�p�^�[�����s���ł�"));
		break;
	}


	printLog_I(_T("�u���b�N�̑ҋ@���i�߂܂���"));
}

//�����_���Ńu���b�N�̎�ނ�Ԃ�(�����u���b�N�p)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::GetRandomBlockType_FALL() {
	int Rand = (int)randomTable.getRand(0, 100);

	//�m���Ŗ߂�l��ς���悤�ɂ���
	if (Rand < 17)	return BLOCK_TYPE_RED;		//��
	if (Rand < 35)	return BLOCK_TYPE_BLUE;		//��
	if (Rand < 52)	return BLOCK_TYPE_YELLOW;	//��
	if (Rand < 70)	return BLOCK_TYPE_GREEN;	//��
	if (Rand < 88)	return BLOCK_TYPE_PURPLE;	//��

	//�����������u���b�N��
	if (Rand < 89)	return BLOCK_TYPE_RED_ARROW_X;		//��(���s���)
	if (Rand < 91)	return BLOCK_TYPE_BLUE_ARROW_X;		//��(���s���)
	if (Rand < 93)	return BLOCK_TYPE_YELLOW_ARROW_X;	//��(���s���)
	if (Rand < 95)	return BLOCK_TYPE_GREEN_ARROW_X;	//��(���s���)
	if (Rand < 97)	return BLOCK_TYPE_PURPLE_ARROW_X;	//��(���s���)
	return BLOCK_TYPE_RAINBOW;							//���F�̃u���b�N(���̃u���b�N�Ɠ����F�ɂȂ�)
}

//�����_���Ńu���b�N�̎�ނ�Ԃ�(�����畦���Ă���u���b�N�p)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::GetRandomBlockType_UNDER() {
	int Rand = (int)randomTable.getRand(0, 200);

	//�m���Ŗ߂�l��ς���悤�ɂ���
	if (Rand < 37)	return BLOCK_TYPE_RED;		//��
	if (Rand < 75)	return BLOCK_TYPE_BLUE;		//��
	if (Rand < 112)	return BLOCK_TYPE_YELLOW;	//��
	if (Rand < 150)	return BLOCK_TYPE_GREEN;	//��
	if (Rand < 188)	return BLOCK_TYPE_PURPLE;	//��

	//�����������u���b�N��
	if (Rand < 189)	return BLOCK_TYPE_RED_ARROW_X;		//��(���s���)
	if (Rand < 191)	return BLOCK_TYPE_BLUE_ARROW_X;		//��(���s���)
	if (Rand < 193)	return BLOCK_TYPE_YELLOW_ARROW_X;	//��(���s���)
	if (Rand < 195)	return BLOCK_TYPE_GREEN_ARROW_X;	//��(���s���)
	if (Rand < 197)	return BLOCK_TYPE_PURPLE_ARROW_X;	//��(���s���)
	return BLOCK_TYPE_TREE;								//���؂̌`�̃u���b�N�i�אڂ���S�����̂ǂ������������Ƃ��Ɉꏏ�ɏ�����j
}

//���z�t�B�[���h�����݂̃t�B�[���h�ƈ�v������
void Phase_GameMain::Virtualfield_Update() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			Virtualfield[x][y] = field[x][y];
		}
	}
	printLog_I(_T("���z�t�B�[���h���X�V���܂���"));


}

//�|�[�Y���j���[�̃{�^���������ꂽ�Ƃ�
void Phase_GameMain::SelectItem_pause::Event_Select(int No) {
	switch (No) {
	case 0://�ĊJ�{�^��
		phase_GameMain.PauseRequest(PauseMode_NO);
		break;
	case 1://��蒼���{�^��
		phase_GameMain.Restart();
		break;
	case 2://�I���{�^��
		Changefaze(FAZE_TopMenu, THREAD_Update);
		break;
	default:
		printLog_C(_T("��`����Ă��Ȃ��I�����ڂ��I�����ꂽ�悤�ł�(%d)"), No);
		break;
	}
}

//�w�肵��X���W�̈�ԏ�̃u���b�N��Y���W���擾����(�����Ă�����W�݂̂Ŕ��f)
int Phase_GameMain::getBlock_Upper(int x) {
	for (int y = BLOCK_PADDINGUP; y < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y++) {
		if (getBlockColor(x, y) != BLOCK_TYPE_NO)	return y;
	}
	return BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;//�ŉ��i�̈�i���̍��W��Ԃ�
}

//�ő�̍����̃u���b�N��Y���W���擾����
int Phase_GameMain::getBlock_maxUpper() {
	int Max_Y = BLOCK_HEIGHTNUM;
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		Max_Y = min(Max_Y, getBlock_Upper(x));
	}
	return Max_Y;
}