#include "Phase_GameMain.h"
#include "MainFunc.h"

Phase_GameMain::Phase_GameMain() {
}


Phase_GameMain::~Phase_GameMain() {
}

//������(�`�揈��)
void Phase_GameMain::Init_Draw() {
	//�Q�[����ʂ̐���(��ŃV�F�[�_���g�������̂�2��n��̃T�C�Y�ō쐬���܂�)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("�E�B���h�E�쐬�Ɏ��s���܂���"));

	if ((Tex_BlockRED = LoadGraph(_T("Data/Blocks/Block_RED.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED.png)"));
	if ((Tex_BlockBLUE = LoadGraph(_T("Data/Blocks/Block_BLUE.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE.png)"));
	if ((Tex_BlockYELLOW = LoadGraph(_T("Data/Blocks/Block_YELLOW.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW.png)"));
	if ((Tex_BlockGREEN = LoadGraph(_T("Data/Blocks/Block_GREEN.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN.png)"));
	if ((Tex_BlockPURPLE = LoadGraph(_T("Data/Blocks/Block_PURPLE.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE.png)"));
	if ((Tex_BlockTREE = LoadGraph(_T("Data/Blocks/Block_TREE.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_TREE.png)"));
	if ((Tex_BlockBLACK = LoadGraph(_T("Data/Blocks/Block_BLACK.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLACK.png)"));
	if ((Tex_BlockRAINBOW = LoadGraph(_T("Data/Blocks/Block_RAINBOW.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RAINBOW.png)"));
	if ((Tex_BlockBOMB = LoadGraph(_T("Data/Blocks/Block_BOMB.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BOMB.png)"));
	if ((haikei = LoadGraph(_T("Data/image/colorbom.png"))) == -1)					printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/image/colorbom.png)"));

	if ((BGM = LoadBGM(_T("Data/BGM/Happy_Halloween.wav"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/BGM/Happy_Halloween.wav)"));
	SetLoopTimePosSoundMem(9768, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);

}

//������(�v�Z����)
void Phase_GameMain::Init_Update() {
	Flag_Pause = FALSE;
	Flag_pauseRequest = FALSE;
	Create_Wait_Block();
	Create_Wait_Block();
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
			//�`���̍��W���v�Z����
			double X, Y;
			if (field[x][y].blockMoveMotion.Enable) {
				//�ړ����[�V�����L��
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, &X, &Y);	//�ړ������W�̌v�Z
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//���݂̈ړ������̌v�Z
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//��̌v�Z���ʂ��A�`����W�̌v�Z
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//�ړ����[�V��������
				Convert_Ingame_FromBlock(x, y, &X, &Y);
			}

			//���S���W�ɕϊ�
			X += BLOCK_SIZE / 2.;
			Y += BLOCK_SIZE / 2.;
			if (field[x][y].blockChangeMotion.Enable) {
				//�ω����[�V�����L��
				int Alpha = (int)((field[x][y].blockChangeMotion.Count / (double)field[x][y].blockChangeMotion.Length) * 255);

				if (field[x][y].blockChangeMotion.To == BLOCK_TYPE_NO) {
					//�ω���̃u���b�N�������u���b�N�̏ꍇ�͕ω����𔖂�����

					Alpha = 255 - Alpha;	//�A���t�@�l���]

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
					DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else {
					//���ʂɕ`��
					DrawBlock(X, Y, field[x][y].blockChangeMotion.From);
					//�ω��ʂɉ����Ĕ������ŕ`�悷��
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
					DrawBlock(X, Y, field[x][y].blockChangeMotion.To);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				}
			}
			else {
				DrawBlock(X, Y, field[x][y].color);
			}

		}
	}

	//�������u���b�N�̕`��
	if (isFallBlock_Enable()) {//�����u���b�N���L���Ȏ�
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
				X += BLOCK_SIZE / 2.;
				Y += BLOCK_SIZE / 2.;
				DrawBlock(X, Y, fallBlockInfo.fallblock.BlockID[x][y]);
			}
		}
	}

	//�f�o�b�O
#ifdef _DEBUG_GAMEMAIN_
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
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
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

	if (isPaused()) {//�|�[�Y��Ԃ̎�
							  //�|�[�Y��Ԃƕ�����悤�ɕ`�悷��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (getFrameCount(THREAD_Update) % 120 > 40)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("PAUSE"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
	}
}

//�u���b�N��`�悷��(�C���Q�[�����W)
void Phase_GameMain::DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type) {
	switch (type) {
	case BLOCK_TYPE_RED:	//�ԃu���b�N�`��
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockRED, TRUE);
		break;
	case BLOCK_TYPE_BLUE:	//�u���b�N�`��
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockBLUE, TRUE);
		break;
	case BLOCK_TYPE_GREEN:	//�΃u���b�N�`��
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockGREEN, TRUE);
		break;
	case BLOCK_TYPE_PURPLE:	//���u���b�N�`��
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockPURPLE, TRUE);
		break;
	case BLOCK_TYPE_YELLOW:	//���F�u���b�N�`��
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockYELLOW, TRUE);
		break;
	case BLOCK_TYPE_TREE:	//���؃u���b�N
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockTREE, TRUE);
		break;
	case BLOCK_TYPE_BLACK:	//���u���b�N
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockBLACK, TRUE);
		break;
	case BLOCK_TYPE_RAINBOW://���F�u���b�N
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockRAINBOW, TRUE);
		break;
	case BLOCK_TYPE_BOM://���e�u���b�N
		DrawRotaGraph((int)CenterX, (int)CenterY, 1, 0, Tex_BlockBOMB, TRUE);
		break;
	}
}

//�v�Z����
void Phase_GameMain::Update() {
	//�v�Z�����̍ŏ��ɍs����������(�����Ȃ�����֐����H)

	//���N�G�X�g�̔��f

	Flag_Pause = Flag_pauseRequest;//���N�G�X�g�̔��f
	//�����܂�

	GameMain_Key();	//�L�[����

	if (isPaused())	return;//�|�[�Y�������������ꍇ�͐�ɐi�܂Ȃ�




	switch (gameCycle) {
	case GameCycle_FALL:
		if (getFallBlock_Interval() > 30)	Create_FallBlock(NULL);//�O��̗����u���b�N�I�������莞�Ԍ�ɗ����u���b�N�̍ďo��
		//�����u���b�N�̗�������
		if (Update_FallBlock()) {
			//����������͌v�Z���s��
			UpdateBlockRequest(GameCycle_BeforeFALL);
		}
		break;
	case GameCycle_BeforeFALL:
		//�����_���ň�ԏ�̒i�ɖ؃u���b�N��ݒu����
		for (int i = 0; add_FraldBlock((int)randomTable.getRand(BLOCK_PADDINGLEFT, BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT), 1, BLOCK_TYPE_TREE) == FALSE && i < 10; i++);
		UpdateBlockRequest(GameCycle_FALL);
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
			if (FallBlock_MoveX(-1))	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else						SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota > 0) {
			//���v���ɉ�]
			if (FallBlock_Rotate(1))	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else						SoundEffect_Play(SE_TYPE_Graze);
		}
		if (fallBlockInfo.Key_LRRota < 0) {
			//�����v���ɉ�]
			if (FallBlock_Rotate(-1))	SoundEffect_Play(SE_TYPE_Bulletfire2);
			else						SoundEffect_Play(SE_TYPE_Graze);
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
		Loop_No = 1;
		printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 1://�d�͌v�Z
		Block_Gravity();//�d�͌v�Z���s��
		Loop_No = 2;
		printLog_I(_T("�ړ����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		break;
	case 2://�ړ����[�V����
		if (Update_MoveMotion() == FALSE) {
			//�ړ����Ȃ������ꍇ
			Loop_No = 3;
			printLog_I(_T("�u���b�N�̓�����ʂֈڍs�yLoop_No=%d�z"), Loop_No);
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
			Loop_No = 5;
			printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
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
			Loop_No = 7;
			printLog_I(_T("�u���b�N�̏�������ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		break;
	case 7://�u���b�N�̏�������
		if (Block_Delete() > 0) {
			//�u���b�N�̏������肪�����
			SoundEffect_Play(SE_TYPE_ButtonCancel);
			Loop_No = 8;
			printLog_I(_T("�ω����[�V�����ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		else {
			Loop_No = 11;
			printLog_I(_T("�I�������ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		break;
	case 8://�ω����[�V����
		if (Update_ChangeMotion() == FALSE) {
			//�ω����Ȃ������ꍇ
			Loop_No = 9;
			printLog_I(_T("�d�͌v�Z�ֈڍs�yLoop_No=%d�z"), Loop_No);
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
			Loop_No = 7;
			printLog_I(_T("�u���b�N�̏�������ֈڍs�yLoop_No=%d�z"), Loop_No);
		}
		break;
	case 11://�I��
		Loop_No = -1;
		printLog_I(_T("�u���b�N�v�Z���[�v�̏I��"));
		setGameCycle(Loop_Next);
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
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, &fX, &fY);
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY, &tX, &tY);
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
			if (field[x][y].blockChangeMotion.Enable) {
				field[x][y].blockChangeMotion.Count++;//�J�E���g�A�b�v
				if (field[x][y].blockChangeMotion.Count > field[x][y].blockChangeMotion.Length) {//�ړ�����
					field[x][y].blockChangeMotion.Enable = FALSE;//�ړ��𖳌���
				}
				count++;
			}
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//�I������(�`�揈��)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);

	DeleteGraph(Tex_BlockRED);
	DeleteGraph(Tex_BlockBLUE);
	DeleteGraph(Tex_BlockYELLOW);
	DeleteGraph(Tex_BlockGREEN);
	DeleteGraph(Tex_BlockPURPLE);
	DeleteGraph(Tex_BlockTREE);
	DeleteGraph(Tex_BlockBLACK);
	DeleteGraph(Tex_BlockRAINBOW);
	DeleteGraph(haikei);

	DeleteSoundMem(BGM);
}

//�I������(�v�Z����)
void Phase_GameMain::Finalize_Update() {

}

//�L�[����
void Phase_GameMain::GameMain_Key() {

	//�|�[�Y����
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		PauseRequest(!isPaused());	//�|�[�Y��Ԃ̔��]
	}

	if (isPaused())	return;//�|�[�Y�������������ꍇ�͐�ɐi�܂Ȃ�

	if (getKeyBind(KEYBIND_UP) == 1) {
		add_FraldBlock(0, 18, BLOCK_TYPE_BLUE, TRUE);
		printLog_D(_T("������"));

	}

	if (isFallBlock_Falling()) {
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

//�u���b�N�̍��W�H����C���Q�[���̍��W�̍��[���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
void Phase_GameMain::Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE;
	}
}

//�|�[�Y��Ԃ��ǂ����̎擾(TRUE�Ń|�[�Y)
int Phase_GameMain::isPaused() {
	return Flag_Pause;
}

//�|�[�Y��Ԃ̃��N�G�X�g
void Phase_GameMain::PauseRequest(int b_Flag) {
	b_Flag = (b_Flag) ? TRUE : FALSE;//�s���Ȉ����̑΍�

	Flag_pauseRequest = b_Flag;
	if (Flag_pauseRequest)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�|�[�Y���N�G�X�g�y�L���z"));
	else					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�|�[�Y���N�G�X�g�y�����z"));
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

	fallBlockInfo.fallblock.BlockID[0][2] = BLOCK_TYPE_BOM;
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

	//�L��
	fallBlockInfo.Enable = TRUE;

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
int Phase_GameMain::FallBlock_MoveX(int MoveVal) {
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
					if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
						//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						MoveVal = i;//�ŊO�̃��[�v��������
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

	return MoveVal;
}

//�����u���b�N��Y�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
int Phase_GameMain::FallBlock_MoveY(int MoveVal) {
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
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
						//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						MoveVal = i;//�ŊO�̃��[�v��������
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

//�t�B�[���h�Ƀu���b�N��ǉ�����(������TRUE,���s��FALSE)(�㏑���֎~)
int Phase_GameMain::add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int OutScreen) {
	//�u���b�N�����u���b�N�͐ݒu�s��
	if (brock_type == BLOCK_TYPE_NO)					return FALSE;
	//��ʊO�u���b�N���ݒu�s��
	if (brock_type == BLOCK_TYPE_NUM)					return FALSE;

	//�u���b�N�̏㏑���͎��s�ɂ���(��ʊO���u���b�N�L��Ɣ��肪�o��ݒ�ɂ���)
	if (getBlockColor(X, Y, TRUE, !OutScreen) != BLOCK_TYPE_NO)		return FALSE;

	//�u���b�N�̐ݒu
	field[X][Y].fall_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
	field[X][Y].move_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
	field[X][Y].color = brock_type;	//�u���b�N�̒u������


	printLog_I(_T("�t�B�[���h�u���b�N�̐V�K����[%d][%d](type=%d)"), X, Y, brock_type);

	return TRUE;
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
				Block_SetChangeMotion(x, y, BLOCK_TYPE_BLACK, field[x][y].color, 60);
			}
		}
	}
}

//�t�B�[���h�ɑ��݂�����F�u���b�N�̐F�����肷��
void Phase_GameMain::Block_Rainbow_Func() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
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
				Block_SetChangeMotion(x, y, BLOCK_TYPE_RAINBOW, field[x][y].color, 60);


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
				if (Block_Delete_Direct(x, y, TRUE))	DeleteNum++;

				//���͂̃u���b�N���폜����(���e�u���b�N�͍폜���Ȃ�)
				if (getBlockColor(x + 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 2, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 2, y, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y + 2, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x, y - 2, TRUE))	DeleteNum++;
				}


				if (getBlockColor(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y - 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y - 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x + 1, y + 1, TRUE))	DeleteNum++;
				}
				if (getBlockColor(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Block_Delete_Direct(x - 1, y + 1, TRUE))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Bulletfire5);

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
int Phase_GameMain::Block_Delete_Direct(int X, int Y, int PlayMotion) {
	//��ʊO����
	BLOCK_TYPE t = getBlockColor(X, Y);
	if (t == BLOCK_TYPE_NO)	return FALSE;//�Ȃ��̂ō폜���Ȃ�

	field[X][Y].color = BLOCK_TYPE_NO;
	printLog_I(_T("�u���b�N�́y�폜�z[%d][%d]"), X, Y);

	if (PlayMotion)			Block_SetChangeMotion(X, Y, t, BLOCK_TYPE_NO, 40);	//���[�V�����̐���
	else					field[X][Y].blockChangeMotion.Enable = FALSE;		//���[�V�����̍폜

	return TRUE;
}

//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜(�폜���ꂽ��TRUE)
int Phase_GameMain::Block_Delete_Type(int X, int Y, BLOCK_TYPE type, int PlayMotion) {
	if (getBlockColor(X, Y) != type)	return FALSE;//�Ⴄ�u���b�N�̏ꍇ�͍폜���Ȃ�

	return Block_Delete_Direct(X, Y, PlayMotion);
}

//�A������t�B�[���h�u���b�N���폜����(���łɂ��ז��u���b�N�̏������s��)(���������u���b�N�̐�)
int Phase_GameMain::Block_Delete() {
	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BLOCK_TYPE_NO ||
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

	//4�ȏ�אڂ��Ă���u���b�N�͍폜����
	int DelCount = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//�z��͈͓̔�
				if (Counter[DeleteFlag[x][y]] >= 3) {
					//�폜
					Block_Delete_Direct(x, y, TRUE);
					DelCount++;
					//���łɗאڂ�����؃u���b�N���폜
					if (Block_Delete_Type(x, y - 1, BLOCK_TYPE_TREE, TRUE))	DelCount++;//��
					if (Block_Delete_Type(x, y + 1, BLOCK_TYPE_TREE, TRUE))	DelCount++;//��
					if (Block_Delete_Type(x - 1, y, BLOCK_TYPE_TREE, TRUE))	DelCount++;//��
					if (Block_Delete_Type(x + 1, y, BLOCK_TYPE_TREE, TRUE))	DelCount++;//�E

				}
			}
		}
	}

	printLog_I(_T("�אڃu���b�N�̍폜�v�Z���s���܂���(%d�u���b�N)"), DelCount);


	return DelCount;
}

//�אڂ��铯�F�u���b�N�Ƀ}�[�J�[��t����
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter) {
	if (deleteFlag[x][y] != -1)	return;		//���T���u���b�N����Ȃ��ꍇ
	BLOCK_TYPE bt = field[x][y].color;      //�u���b�N�̎�ނ��L�^����
	deleteFlag[x][y] = ID;					//�T���ς�(�T��ID��ݒ肷��)
	(*Counter)++;

	if (x + 1 < BLOCK_WIDTHNUM	&& field[x + 1][y].color == bt) SequenceCount(x + 1, y, ID, deleteFlag, Counter);
	if (y + 1 < BLOCK_HEIGHTNUM	&& field[x][y + 1].color == bt) SequenceCount(x, y + 1, ID, deleteFlag, Counter);
	if (x - 1 >= 0 && field[x - 1][y].color == bt) SequenceCount(x - 1, y, ID, deleteFlag, Counter);
	if (y - 1 >= 0 && field[x][y - 1].color == bt) SequenceCount(x, y - 1, ID, deleteFlag, Counter);
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

//�t�B�[���h�̃u���b�N�ɕω����[�V������ݒ肷��
void Phase_GameMain::Block_SetChangeMotion(int x, int y, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength) {
	if (getBlockColor(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//�u���b�N����ʊO�̏ꍇ�͏��������Ȃ�
	if (From == To)											return;	//�ω������̏ꍇ�����������Ȃ�
	if (MotionLength <= 0)									return;	//���������̐��̏ꍇ�����������Ȃ�

	if (field[x][y].blockChangeMotion.Enable) {
		printLog_C(_T("�u���b�N�ω����[�V�������㏑�����܂�"));
		field[x][y].blockChangeMotion.Enable = FALSE;
	}

	field[x][y].blockChangeMotion.To = To;
	field[x][y].blockChangeMotion.From = From;
	field[x][y].blockChangeMotion.Length = MotionLength;
	field[x][y].blockChangeMotion.Count = 0;

	field[x][y].blockChangeMotion.Enable = TRUE;

	printLog_I(_T("�u���b�N�Ɂy�ω����[�V�����z��ݒ�[%d][%d]"), x, y);
}

//�ω����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
int Phase_GameMain::isBlock_PlayChangeMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].blockChangeMotion.Enable) {
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
	if (Next == GameCycle_NUM || Next == GameCycle_Update) {
		printLog_E(_T("�������s���ł�"));
		return;
	}

	if (gameCycle == GameCycle_Update) {
		//���łɎ��s����Ă���
		printLog_E(_T("���݃u���b�N���̍X�V���s���Ă邽�߃��N�G�X�g�͖�������܂�"));
	}

	//�u���b�N�v�Z�T�C�N���ֈڍs
	setGameCycle(GameCycle_Update);

	//�ڍs��̃Q�[���T�C�N�����L�^����
	Loop_Next = Next;

	//�v�Z���[�v�̏����ʒu��ݒ�
	Loop_No = 0;

	printLog_I(_T("�u���b�N�v�Z���[�v�ɓ���܂�(�I����=%d)"), Loop_Next);

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