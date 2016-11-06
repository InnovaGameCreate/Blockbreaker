#include "MainFunc.h"



Phase_GameMain::Phase_GameMain() {
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
	if ((Tex_BlockFireEffect = LoadGraph(_T("Data/Blocks/Block_FireEffect.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_FireEffect.png)"));
	if ((Tex_BlockFireEffect2 = LoadGraph(_T("Data/Blocks/Block_FireEffect2.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_FireEffect2.png)"));

	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/image/colorbom.png)"));


	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

	//�|�[�Y���j���[�̍��ڂ��쐬
	pauseMenu.addItem(_T("�ĊJ"), 3, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("��蒼��"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.addItem(_T("�Q�[���I��"), 5, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	pauseMenu.setScrolltype(1);
	pauseMenu.sethaba(50);
	pauseMenu.setCenteringMode(0);
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
	Count_Pause = 0;
	Count_Turn = 0;
	//�������u���b�N�̍폜
	Delete_FallBlock();
	score.init();//�X�R�A�̏�����

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
	DrawBox(BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE,
		GAMEWINDOW_WIDTH + BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_HEIGHT + BLOCK_PADDINGUP*BLOCK_SIZE,
		GetColor(0xb3, 0x65, 0xe5), TRUE);

	//�t�B�[���h�u���b�N�̕`��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//�`���̍��W���擾
			double X, Y;
			X = field[x][y].DrawPlaceX;
			Y = field[x][y].DrawPlaceY;
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
				ShaderBackGround_DeleteBlock(X, Y, field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length
					, getBlockTexture(field[x][y].blockChangeMotion.From), Tex_BlockFireEffect, Tex_BlockFireEffect2);
				break;
			case BlockChangeMotionType_SMALL:
				//�������Ȃ�
				DrawBlock(X, Y, field[x][y].blockChangeMotion.From, 1 - (field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length));
				break;
			}
		}
	}

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
	//�������u���b�N�̕`��
	if (isFallBlock_Enable()) {//�����u���b�N���L���Ȏ�
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), 0, 0, &X, &Y);

				//�S�̂��炵�̕��`����W�����炷
				if (Block_AllMovedata.Enable) {//�S�̂��炷���L���ȏꍇ
					X += Field_PaddingX;
					Y += Field_PaddingY;
				}

				if (Y < (y + BLOCK_PADDINGUP)*BLOCK_SIZE) {
					Y = (y + BLOCK_PADDINGUP)*BLOCK_SIZE;
				}

				DrawBlock(X, Y, fallBlockInfo.fallblock.BlockID[x][y]);
			}
		}
	}

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

	//��ʈ�t�Ɏl�p�`��`�悷��(��X�e�N�X�`���ɒu�������)
	DrawGraph(0, 0, haikei, FALSE);


	//�Q�[����ʂ�`�悷��(�f�o�b�O���[�h�̏ꍇ�́A�S�u���b�N�̈��`�悷��)
	if (DEBUG_GAMEMAIN) {
		DrawRectGraph(GAMEWINDOW_PADDINGX - BLOCK_PADDINGLEFT*BLOCK_SIZE, GAMEWINDOW_PADDINGY - BLOCK_PADDINGUP*BLOCK_SIZE, 0, 0, BLOCK_WIDTHNUM*BLOCK_SIZE, BLOCK_HEIGHTNUM*BLOCK_SIZE, gameWindow, FALSE, FALSE);
	}
	else {
		DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, BLOCK_PADDINGLEFT*BLOCK_SIZE, BLOCK_PADDINGUP*BLOCK_SIZE, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);
	}


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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(150, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (Count_Pause % 120 <= 80)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("GAME OVER"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);

		//�I�����̍��ڂ̕`��
		pauseMenu.Draw();
		break;
	}
}

//�u���b�N��`�悷��(�C���Q�[�����W)
void Phase_GameMain::DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type, double Scale) {

	if (type == BLOCK_TYPE_NO)	return;

	//���S���W�ɕϊ�
	int X = (int)(CenterX + BLOCK_SIZE / 2.);
	int Y = (int)(CenterY + BLOCK_SIZE / 2.);

	DrawRectRotaGraphFast2(X, Y, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2, (float)Scale, 0, getBlockTexture(type), TRUE, FALSE);

	//DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, getBlockTexture(type), TRUE);
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
			Create_FallBlock(NULL);//�O��̗����u���b�N�I�������莞�Ԍ�ɗ����u���b�N�̍ďo��
		}
		//�����u���b�N�̗�������
		if (Update_FallBlock()) {
			//����������͌v�Z���s��
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
	{

		if (Count_Turn % 3 == 0) {
			under_Block();
		}
		else {
			BLOCK_TYPE bt = BLOCK_TYPE_RAINBOW;
			int swi = (int)(randomTable.getRand(0, 219) / 10.);
			switch (swi) {
			case 0:		bt = BLOCK_TYPE_RED_ARROW_X;		break;
			case 1:		bt = BLOCK_TYPE_RED_ARROW_Y;		break;
			case 2:		bt = BLOCK_TYPE_RED_ARROW_XY;		break;
			case 3:		bt = BLOCK_TYPE_RED_ARROW_XY2;		break;
			case 4:		bt = BLOCK_TYPE_BLUE_ARROW_X;		break;
			case 5:		bt = BLOCK_TYPE_BLUE_ARROW_Y;		break;
			case 6:		bt = BLOCK_TYPE_BLUE_ARROW_XY;		break;
			case 7:		bt = BLOCK_TYPE_BLUE_ARROW_XY2;		break;
			case 8:		bt = BLOCK_TYPE_YELLOW_ARROW_X;		break;
			case 9:		bt = BLOCK_TYPE_YELLOW_ARROW_Y;		break;
			case 10:	bt = BLOCK_TYPE_YELLOW_ARROW_XY;	break;
			case 11:	bt = BLOCK_TYPE_YELLOW_ARROW_XY2;	break;
			case 12:	bt = BLOCK_TYPE_GREEN_ARROW_X;		break;
			case 13:	bt = BLOCK_TYPE_GREEN_ARROW_Y;		break;
			case 14:	bt = BLOCK_TYPE_GREEN_ARROW_XY;		break;
			case 15:	bt = BLOCK_TYPE_GREEN_ARROW_XY2;	break;
			case 16:	bt = BLOCK_TYPE_PURPLE_ARROW_X;		break;
			case 17:	bt = BLOCK_TYPE_PURPLE_ARROW_Y;		break;
			case 18:	bt = BLOCK_TYPE_PURPLE_ARROW_XY;	break;
			case 19:	bt = BLOCK_TYPE_PURPLE_ARROW_XY2;	break;
			case 20:	bt = BLOCK_TYPE_TREE;				break;
			case 21:	bt = BLOCK_TYPE_BOM;				break;
			}

			//�����_���ň�ԏ�̒i�ɖ؃u���b�N��ݒu����
			for (int i = 0; add_FraldBlock((int)randomTable.getRand(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT), 1, bt) == FALSE && i < 10; i++);
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
		if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 5;	//�����������[�h�̏ꍇ�J�E���g������ɓ����
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
	1.�d�͌v�Z
	2.�ړ����[�V����
	3.�u���b�N�̓������
	4.�ω����[�V����
	5.�d�͌v�Z
	6.�ړ����[�V����
	7.�u���b�N�̏������聨�����u���b�N�����̏ꍇ��11��
	8.�ω����[�V����
	9.�d�͌v�Z
	10.�ړ����[�V��������7��
	11.�X�V���[�v�I��
	*/


	switch (Loop_No) {
	case 0://������

		ChainCount = 0;	//�A���J�E���g�����Z�b�g����
		gameCycleFirstCallFlag = FALSE;	//�Q�[���T�C�N�����ύX���ꂽ���̃t���O��FALSE�ɐݒ肷��

		////�Q�[���I�[�o�[�̔�����s��
		//if (JudgeGameOver() != 0) {
		//	PauseRequest(PauseMode_GameOver);	//�|�[�Y���N�G�X�g
		//}
		//��ʊO�u���b�N���폜����
		Block_Delete_OutScreen();

		if (!gameCycleFirstCallFlag) {
			Loop_No = 1;
			printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		break;
	case 1://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 2;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 2://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 3;
				printLog_I(_T("�u���b�N�̓�����ʂֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 3://�u���b�N�̓������
		Block_Black_Func();		//���u���b�N�̐F�ύX
		Block_Rainbow_Func();	//���F�u���b�N�̐F��ύX
		Block_BOMB_Func();		//���e�u���b�N�̏���
		Loop_No = 4;
		printLog_I(_T("�ω����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 4://�ω����[�V����
		if (Update_ChangeMotion() == FALSE) {
			//�ω����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 5;
				printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 5://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 6;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 6://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 7;
				printLog_I(_T("�u���b�N�̏�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 7://�u���b�N�̏�������
		if (Block_Delete() > 0) {
			//�u���b�N�̏������肪�����
			ChainCount++;	//�A���J�E���g�����Z����
			//�A���J�E���g��`�悷��(�t���C�e�L�X�g)
			if (ChainCount >= 2) flyText.addFlyText(GAMEWINDOW_WIDTH / 2., GAMEWINDOW_HEIGHT / 2., 60, FONTTYPE_GenJyuuGothicLHeavy_Edge60, GetColor(200, 200, 0), _T("%d�A���I�I"), ChainCount);


			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Loop_No = 8;
			printLog_I(_T("�ω����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		else {
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 11;
				printLog_I(_T("�I�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 8://�ω����[�V����
		if (Update_ChangeMotion() == FALSE) {
			//�ω����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 9;
				printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 9://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 10;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 10://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			if (gameCycleFirstCallFlag) {
				Loop_No = 0;
				printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
			else {
				Loop_No = 7;
				printLog_I(_T("�u���b�N�̏�������ֈڍs�yLoop_No=%d�z"), Loop_No);
			}
		}
		break;
	case 11://�I��
		if (gameCycleFirstCallFlag) {
			Loop_No = 0;
			printLog_I(_T("�������ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		else {
			//���S������s��
			if (JudgeGameOver() != 0) {
				PauseRequest(PauseMode_GameOver);
			}
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

	//�X�e�[�W�o�ߎ��Ԃ̃J�E���g�A�b�v(�ʏ�v���C���ɉ��Z����)
	if (getPauseMode() == PauseMode_NO && Block_AllMovedata.Enable == FALSE)	Count_PlayTime++;

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
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, 0, 0, &X, &Y);	//�ړ������W�̌v�Z
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//���݂̈ړ������̌v�Z
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//��̌v�Z���ʂ��A�`����W�̌v�Z
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//�ړ����[�V��������
				Convert_Ingame_FromBlock(x, y, 0, 0, &X, &Y);
			}

			//�S�̂��炵�̕��`����W�����炷
			X += Field_PaddingX;
			Y += Field_PaddingY;

			//�Q�[���I�[�o�[���߂��ꍇ�͍��E�ɗh�炷
			if (getBlockColor(x, GAMEOVER_BORDER + 2) != BLOCK_TYPE_NO) {
				X += getGraph_Sin(Count_PlayTime * 30, 3, 0);
				X += randomTable.getRand(-2, 2);
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
	DeleteGraph(haikei);

	DeleteMask(Tex_BlockFireEffect2);

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
int Phase_GameMain::Create_FallBlock(struct Fallblock_Pack *fallblock_Pack) {
	//if (fallblock_Pack == NULL)	return FALSE;

	if (isFallBlock_Enable()) {
		printLog_C(_T("�������̃u���b�N�����łɑ��݂��邽�߁A�����u���b�N��V���ɒǉ��o���܂���ł���"));
		return FALSE;
	}

	//�����u���b�N�̌`���ݒ肷��(�b��)
	/*�\���}�[�N������0�͖����A1�͗L��(�ԃu���b�N�ɂȂ�悤�ɐݒ�)*/
	fallBlockInfo.fallblock.BlockID[0][0] = BLOCK_TYPE_YELLOW;
	fallBlockInfo.fallblock.BlockID[1][0] = BLOCK_TYPE_BLACK;
	fallBlockInfo.fallblock.BlockID[2][0] = BLOCK_TYPE_RED;

	fallBlockInfo.fallblock.BlockID[0][1] = BLOCK_TYPE_PURPLE;
	fallBlockInfo.fallblock.BlockID[1][1] = BLOCK_TYPE_BLUE;
	fallBlockInfo.fallblock.BlockID[2][1] = BLOCK_TYPE_GREEN;

	fallBlockInfo.fallblock.BlockID[0][2] = BLOCK_TYPE_NO;
	fallBlockInfo.fallblock.BlockID[1][2] = BLOCK_TYPE_RAINBOW;
	fallBlockInfo.fallblock.BlockID[2][2] = BLOCK_TYPE_NO;

	//fallBlockInfo.fallblock = waitBlockinfo[1].fallblock;
	//Create_Wait_Block();

	//�����J�E���g��60�ɐݒ�
	fallBlockInfo.FallCount = 60;

	//�����u���b�N�̂��̑��̏��̏�����
	fallBlockInfo.PlaceX = BLOCK_WIDTHNUM / 2;
	fallBlockInfo.PlaceY = 2;
	fallBlockInfo.Counter = 0;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	fallBlockInfo.Key_FlagFirstFall = FALSE;
	fallBlockInfo.Flag_Rotate = TRUE;

	//�L��
	fallBlockInfo.Enable = TRUE;

	//if (JudgeGameOver() != 0) {
	//	PauseRequest(PauseMode_GameOver);
	//}

	printLog_I(_T("�����u���b�N�́y�V�K�����z"));
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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {
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

	//���炵�̔��f
	fallBlockInfo.PlaceX += MoveVal;


	////��]���������ꍇ�͎��S���������
	//if (MoveVal != 0) {
	//	if (JudgeGameOver() != 0) {
	//		PauseRequest(PauseMode_GameOver);//�Q�[���I�[�o�[�ɂ���
	//	}
	//}

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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
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

	////�ړ����������ꍇ�͎��S���������
	//if (MoveVal != 0) {
	//	if (JudgeGameOver() != 0) {
	//		PauseRequest(PauseMode_GameOver);//�Q�[���I�[�o�[�ɂ���
	//	}
	//}


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
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = fallBlockInfo.fallblock.BlockID[x][y];
				}
			}
		}
		else {//���v����90�x
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = fallBlockInfo.fallblock.BlockID[x][y];
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
					fallBlockInfo.fallblock.BlockID[x][y] = RotaBlockID[x][y];
				}
			}
		}

	}

	//���������ɖ߂�
	if (Minus) {
		RotaVal = -RotaVal;
	}

	////��]���������ꍇ�͎��S���������
	//if (RotaVal != 0) {
	//	if (JudgeGameOver() != 0) {
	//		PauseRequest(PauseMode_GameOver);//�Q�[���I�[�o�[�ɂ���
	//	}
	//}

	return RotaVal;
}

//�����u���b�N���t�B�[���h�u���b�N�ɕϊ�����(�܂�ݒu)
void Phase_GameMain::FallBlock_addField() {
	if (!isFallBlock_Enable())	return;	//���������L���Ŗ������͖���

	//���������u���b�N�ȊO�̓t�B�[���h�u���b�N�ɏ����ϊ����s��
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
			if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {
				int fX, fY;		//�u���b�N�̃t�B�[���h��̈ʒu
				BLOCK_TYPE fB;	//�ݒu����u���b�N�̎��
				fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
				fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
				fB = fallBlockInfo.fallblock.BlockID[x][y];

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
int Phase_GameMain::add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int Override, int OutScreen, BlockChangeMotionType MotionType, int MotionLengh, BLOCK_TYPE *Before) {
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;	//�O�̃u���b�N���w�肷��
	BLOCK_TYPE before = BLOCK_TYPE_NO;	//�����O�̃u���b�N
	//��ʊO�u���b�N�͐ݒu�s��
	if (brock_type == BLOCK_TYPE_NUM)	return FALSE;
	//�u���b�N�����u���b�N���w�肳�ꂽ�ꍇ�͍폜�������s��


	//�u���b�N��ݒu���悤�Ƃ��Ă���ʒu�̌��݂̃u���b�N���擾����(�{���ΏۊO�͉�ʊO�u���b�N�ɂȂ�܂�)
	BLOCK_TYPE bt = getBlockColor(X, Y, TRUE, !OutScreen);
	if (Override) {
		//�㏑�����L���ȏꍇ
		if (bt == BLOCK_TYPE_NUM)	return FALSE;//��ʊO�u���b�N�̎��̂ݎ��s
	}
	else {
		//�㏑�������̏ꍇ
		if (bt != BLOCK_TYPE_NO)	return FALSE;//�u���b�N�����Əo�Ȃ��ꍇ�͎��s
	}

	//���݂̃u���b�N���L�^����
	before = field[X][Y].color;

	//���[�V�����̐ݒ�
	switch (MotionType) {
	case Phase_GameMain::BlockChangeMotionType_NO:
		//���[�V�����̏�����
		field[X][Y].blockChangeMotion.Type = BlockChangeMotionType_NO;
		break;
	case Phase_GameMain::BlockChangeMotionType_NOMAL:
		Block_SetChangeMotion_NOMAL(X, Y, brock_type, MotionLengh);	//�폜���݂̂͐ݒ�s��(��������)
		break;
	case Phase_GameMain::BlockChangeMotionType_EXPLOSION:
		if (brock_type == BLOCK_TYPE_NO) Block_SetChangeMotion_EXPLOSION(X, Y, MotionLengh);	//�폜���̂ݐݒ�\
		break;
	case Phase_GameMain::BlockChangeMotionType_SMALL:
		if (brock_type == BLOCK_TYPE_NO) Block_SetChangeMotion_SMALL(X, Y, MotionLengh);	//�폜���̂ݐݒ�\
		break;
	}
	field[X][Y].blockMoveMotion.Enable = FALSE;

	//�u���b�N�̐ݒu(�폜)
	field[X][Y].fall_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
	field[X][Y].move_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
	field[X][Y].color = brock_type;	//�u���b�N�̒u������


	if (brock_type == BLOCK_TYPE_NO) {
		//���̏ꍇ�̓u���b�N�폜�Ȃ̂�
		printLog_I(_T("�t�B�[���h�u���b�N�́y�폜�z[%d][%d]"), X, Y);
	}
	else {
		printLog_I(_T("�t�B�[���h�u���b�N�́y�V�K�����z[%d][%d](type=%d)"), X, Y, brock_type);
	}


	if (Before != NULL)	*Before = before;	//�O�̃u���b�N���w�肷��
	return TRUE;
}


//������u���b�N���킢�Ă���
void Phase_GameMain::under_Block() {
	const int BLOCKSPOWN_Y = BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;//�u���b�N�̏o������ʒu


	for (int i = BLOCK_PADDINGLEFT; BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT > i; i++) {
		BLOCK_TYPE bt = BLOCK_TYPE_RAINBOW;


		BLOCK_TYPE bl = getBlockColor(i - 1, BLOCKSPOWN_Y, FALSE, FALSE);//�����̃u���b�N
		BLOCK_TYPE bu = getBlockColor(i, BLOCKSPOWN_Y - 1, FALSE, FALSE);//�㑤�̃u���b�N

		do {
			int swi = (int)(randomTable.getRand(0, 259) / 10.);
			switch (swi) {
			case 0:		bt = BLOCK_TYPE_RED_ARROW_X;		break;
			case 1:		bt = BLOCK_TYPE_RED_ARROW_Y;		break;
			case 2:		bt = BLOCK_TYPE_RED_ARROW_XY;		break;
			case 3:		bt = BLOCK_TYPE_RED_ARROW_XY2;		break;
			case 4:		bt = BLOCK_TYPE_BLUE_ARROW_X;		break;
			case 5:		bt = BLOCK_TYPE_BLUE_ARROW_Y;		break;
			case 6:		bt = BLOCK_TYPE_BLUE_ARROW_XY;		break;
			case 7:		bt = BLOCK_TYPE_BLUE_ARROW_XY2;		break;
			case 8:		bt = BLOCK_TYPE_YELLOW_ARROW_X;		break;
			case 9:		bt = BLOCK_TYPE_YELLOW_ARROW_Y;		break;
			case 10:	bt = BLOCK_TYPE_YELLOW_ARROW_XY;	break;
			case 11:	bt = BLOCK_TYPE_YELLOW_ARROW_XY2;	break;
			case 12:	bt = BLOCK_TYPE_GREEN_ARROW_X;		break;
			case 13:	bt = BLOCK_TYPE_GREEN_ARROW_Y;		break;
			case 14:	bt = BLOCK_TYPE_GREEN_ARROW_XY;		break;
			case 15:	bt = BLOCK_TYPE_GREEN_ARROW_XY2;	break;
			case 16:	bt = BLOCK_TYPE_PURPLE_ARROW_X;		break;
			case 17:	bt = BLOCK_TYPE_PURPLE_ARROW_Y;		break;
			case 18:	bt = BLOCK_TYPE_PURPLE_ARROW_XY;	break;
			case 19:	bt = BLOCK_TYPE_PURPLE_ARROW_XY2;	break;
			case 20:	bt = BLOCK_TYPE_TREE;				break;
			case 21:	bt = BLOCK_TYPE_RED;				break;
			case 22:	bt = BLOCK_TYPE_BLUE;				break;
			case 23:	bt = BLOCK_TYPE_YELLOW;				break;
			case 24:	bt = BLOCK_TYPE_GREEN;				break;
			case 25:	bt = BLOCK_TYPE_PURPLE;				break;
			}
		} while (isSameColorBlock(bt, bl) || isSameColorBlock(bt, bu));



		add_FraldBlock(i, BLOCKSPOWN_Y, bt, FALSE, TRUE);
	}

	Block_AllMoveRequest(0, -1);	//�u���b�N�S�̂��ړ�
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
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_BLACK, 20);
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
				Block_SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_RAINBOW, 20);


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
					if (Block_Delete_Direct(x + 1, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 2, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 2, y, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 2, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 2, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}


				if (getBlockColor(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y - 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y - 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y + 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y + 1, BlockChangeMotionType_EXPLOSION, 40))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);

}

//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���TRUE����)(��4�����͎��ۂɕ`�悳���G���A�ȊO����ʊO�ɂ���ꍇTRUE,�u���b�N��񂪖����ʒu����ʊO�ɂ���ꍇ��FALSE��ݒ肷��)
Phase_GameMain::BLOCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock, int InGame) {

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

	return field[X][Y].color;

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
int Phase_GameMain::Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int MotionLengh) {

	if (getBlockColor(X, Y, FALSE, FALSE) == BLOCK_TYPE_NO)	return FALSE;//�u���b�N�������������݂��Ȃ��ꍇ�͉������Ȃ�

	//�u���b�N�̍폜���s��
	int flag = add_FraldBlock(X, Y, BLOCK_TYPE_NO, TRUE, TRUE, PlayMotion, MotionLengh);

	if (flag) {
		//�u���b�N���폜���ꂽ
		if (PlayMotion == BlockChangeMotionType_EXPLOSION) {
			Block_SetChangeMotion_EXPLOSION(X, Y, MotionLengh);	//���[�V�����̐���
		}
		else if (PlayMotion == BlockChangeMotionType_SMALL) {
			Block_SetChangeMotion_SMALL(X, Y, MotionLengh);	//���[�V�����̐���
		}
	}

	return ((flag) ? TRUE : FALSE);
}

//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜(�폜���ꂽ��TRUE)
int Phase_GameMain::Block_Delete_Type(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion, int MotionLengh) {
	if (getBlockColor(X, Y) != type)	return FALSE;//�Ⴄ�u���b�N�̏ꍇ�͍폜���Ȃ�

	return Block_Delete_Direct(X, Y, PlayMotion, MotionLengh);
}

//�A������t�B�[���h�u���b�N���폜����(���łɏ����ɂ���Ĕ���������ʂ���������)(���������u���b�N�̐�)
int Phase_GameMain::Block_Delete() {
	//��ʓ��̑��݂���u���b�N�݂̂Ōv�Z����

	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (x < BLOCK_PADDINGLEFT || BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT - 1 < x ||	//��ʊO
				y < BLOCK_PADDINGUP || BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - 1 < y ||	//��ʊO
				field[x][y].color == BLOCK_TYPE_NO ||
				field[x][y].color == BLOCK_TYPE_NUM ||
				field[x][y].color == BLOCK_TYPE_TREE ||
				field[x][y].color == BLOCK_TYPE_BLACK ||
				field[x][y].color == BLOCK_TYPE_RAINBOW ||
				field[x][y].color == BLOCK_TYPE_BOM) {//���O�u���b�N
				DeleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				DeleteFlag[x][y] = -1;
			}
		}
	}

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
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//�z��͈͓̔�
				if (Counter[DeleteFlag[x][y]] >= BLOCK_DELETE_LEN) {
					//�����̖��̏ꍇ
					if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_X ||
						old[x][y] == BLOCK_TYPE_GREEN_ARROW_X ||
						old[x][y] == BLOCK_TYPE_PURPLE_ARROW_X ||
						old[x][y] == BLOCK_TYPE_RED_ARROW_X ||
						old[x][y] == BLOCK_TYPE_YELLOW_ARROW_X) {
						//���[����E�[�܂ł̈����ꊇ����
						for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
							if (Block_Delete_Direct(i, y, BlockChangeMotionType_EXPLOSION, 40)) {
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
							if (Block_Delete_Direct(x, i, BlockChangeMotionType_EXPLOSION, 40)) {
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
							if (Block_Delete_Direct(x + i, y - i, BlockChangeMotionType_EXPLOSION, 40)) {
								//�t���C�e�L�X�g�̐���
								double X, Y;
								Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
								flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
								score.addScore(0, 50);
								DelCount++;
							}
							if (Block_Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, 40)) {
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
							if (Block_Delete_Direct(x + i, y + i, BlockChangeMotionType_EXPLOSION, 40)) {
								//�t���C�e�L�X�g�̐���
								double X, Y;
								Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
								flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+50"));
								score.addScore(0, 50);
								DelCount++;
							}
							if (Block_Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, 40)) {
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

	//�אڂ��Ă���u���b�N���폜����
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//�z��͈͓̔�
				if (Counter[DeleteFlag[x][y]] >= BLOCK_DELETE_LEN) {
					//�폜
					if (Block_Delete_Direct(x, y, BlockChangeMotionType_SMALL, 15)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+100"));
						score.addScore(0, 100);
						DelCount++;
					}

					//���łɗאڂ�����؃u���b�N���폜
					if (Block_Delete_Type(x, y - 1, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//��
					}
					if (Block_Delete_Type(x, y + 1, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//��
					}
					if (Block_Delete_Type(x - 1, y, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
						//�t���C�e�L�X�g�̐���
						double X, Y;
						Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						flyText.addFlyText(X, Y, 30, FONTTYPE_GenJyuuGothicLHeavy_Edge25, GetColor(150, 150, 150), _T("+80"));
						score.addScore(0, 80);
						DelCount++;//��
					}
					if (Block_Delete_Type(x + 1, y, BLOCK_TYPE_TREE, BlockChangeMotionType_SMALL, 15)) {
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
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter) {
	if (deleteFlag[x][y] != -1)	return;		//���T���u���b�N����Ȃ��ꍇ
	BLOCK_TYPE bt = field[x][y].color;      //�u���b�N�̎�ނ��L�^����
	deleteFlag[x][y] = ID;					//�T���ς�(�T��ID��ݒ肷��)
	(*Counter)++;

	if (x + 1 < BLOCK_WIDTHNUM	&& isSameColorBlock(field[x + 1][y].color, bt, TRUE))	SequenceCount(x + 1, y, ID, deleteFlag, Counter);
	if (y + 1 < BLOCK_HEIGHTNUM	&& isSameColorBlock(field[x][y + 1].color, bt, TRUE))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);
	if (x - 1 >= 0 && isSameColorBlock(field[x - 1][y].color, bt, TRUE))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);
	if (y - 1 >= 0 && isSameColorBlock(field[x][y - 1].color, bt, TRUE))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//�w�肵��2�̃u���b�N�����F�u���b�N���ǂ����̎擾(TRUE�œ��F)
int Phase_GameMain::isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int FirstFlag) {
	if (!FirstFlag) {//�ȗ��v�Z�łȂ��Ƃ�
		//�F�̊T�O�̖����u���b�N�̏ꍇ
		if (type1 == BLOCK_TYPE_NO)			return FALSE;
		if (type1 == BLOCK_TYPE_TREE)		return FALSE;
		if (type1 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type1 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type1 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type1 == BLOCK_TYPE_BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_NUM)		return FALSE;
		if (type2 == BLOCK_TYPE_NO)			return FALSE;
		if (type2 == BLOCK_TYPE_TREE)		return FALSE;
		if (type2 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type2 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type2 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type2 == BLOCK_TYPE_BOM)		return FALSE;
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
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//�u���b�N����ʊO�̏ꍇ�͏��������Ȃ�
	if (MotionLength <= 0)									return;	//���������̐��̏ꍇ�����������Ȃ�

	if (field[x][y].blockChangeMotion.Type != BlockChangeMotionType_NO) {
		printLog_C(_T("�u���b�N�ω����[�V�������㏑�����܂�"));
		field[x][y].blockChangeMotion.Type = BlockChangeMotionType_NO;
	}

	field[x][y].blockChangeMotion.To = To;
	field[x][y].blockChangeMotion.From = From;
	field[x][y].blockChangeMotion.Length = MotionLength;
	field[x][y].blockChangeMotion.Count = 0;

	field[x][y].blockChangeMotion.Type = mtype;

	printLog_I(_T("�u���b�N�Ɂy�ω����[�V�����z��ݒ�[%d][%d]"), x, y);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��
void Phase_GameMain::Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == To)				return;		//�ω��悪�����ꍇ�͏��������Ȃ�
	if (To == BLOCK_TYPE_NO)	return;		//�ω��悪�u���b�N�����̏ꍇ�͏��������Ȃ�(�������`��o���Ȃ�����)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, From, To, MotionLength);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��(�ω����w��)
void Phase_GameMain::Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength) {

	BLOCK_TYPE To = getBlockColor(x, y, FALSE, FALSE);
	if (from == To)				return;		//�ω��悪�����ꍇ�͏��������Ȃ�
	if (To == BLOCK_TYPE_NO)	return;		//�ω��悪�u���b�N�����̏ꍇ�͏��������Ȃ�(�������`��o���Ȃ�����)
	Block_SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, from, To, MotionLength);
}


//�t�B�[���h�̃u���b�N�ɕω����[�V����(����)��ݒ肷��
void Phase_GameMain::Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == BLOCK_TYPE_NO)	return;//�u���b�N�����݂��Ȃ��ꍇ�͖���

	Block_SetChangeMotion(x, y, BlockChangeMotionType_EXPLOSION, From, From, MotionLength);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�������Ȃ��ď�����)��ݒ肷��
void Phase_GameMain::Block_SetChangeMotion_SMALL(int x, int y, int MotionLength) {

	BLOCK_TYPE From = getBlockColor(x, y, FALSE, FALSE);

	if (From == BLOCK_TYPE_NO)	return;//�u���b�N�����݂��Ȃ��ꍇ�͖���

	Block_SetChangeMotion(x, y, BlockChangeMotionType_SMALL, From, From, MotionLength);
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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BLOCK_TYPE_NO) {
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

void Phase_GameMain::Create_Wait_Block() {
	waitBlockinfo[1].fallblock = waitBlockinfo[0].fallblock;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			waitBlockinfo[0].fallblock.BlockID[i][j] = BLOCK_TYPE_NO;
		}
	}
	int wait_block_patern = rand() % 2;
	if (wait_block_patern == 0) {//�c
		for (i = 0; i < 2; i++) {
			int wait_block_type = (rand() % BLOCK_TYPE_PURPLE) + 1;
			switch (wait_block_type) {

			case 1:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_RED;//��
				break;
			case 2:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_BLUE;//��
				break;
			case 3:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_YELLOW;//��
				break;
			case 4:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_GREEN;//��
				break;
			case 5:
				waitBlockinfo[0].fallblock.BlockID[1][i] = BLOCK_TYPE_PURPLE;//��
			}
		}
	}
	else {//if (wait_block_patern == 1) {//��
		for (i = 0; i < 2; i++) {
			int wait_block_type = (rand() % BLOCK_TYPE_PURPLE) + 1;
			switch (wait_block_type) {
			case 0:

				break;
			case 1:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_RED;//��
				break;
			case 2:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_BLUE;//��
				break;
			case 3:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_YELLOW;//��
				break;
			case 4:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_GREEN;//��
				break;
			case 5:
				waitBlockinfo[0].fallblock.BlockID[i][1] = BLOCK_TYPE_PURPLE;//��
			}
		}
	}
}

/*
BLOCK_TYPE Phase_GameMain::Get_Block_Type(int h) {
	switch (h)
	{
	case 0:

		break;
	case 1:
		return BLOCK_TYPE_RED;//��
	case 2:
		return BLOCK_TYPE_BLUE;//��
	case 3:
		return BLOCK_TYPE_YELLOW;//��
	case 4:
		return BLOCK_TYPE_GREEN;//��

	case 5:
		return BLOCK_TYPE_PURPLE;//��


	}
	return BLOCK_TYPE_NO;
}
*/

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
		ExitGameRequest();
		break;
	default:
		printLog_C(_T("��`����Ă��Ȃ��I�����ڂ��I�����ꂽ�悤�ł�(%d)"), No);
		break;
	}
}