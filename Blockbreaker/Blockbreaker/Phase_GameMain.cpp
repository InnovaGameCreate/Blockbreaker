#include "stdafx.h"
#include "Phase_GameMain.h"

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
	Flag_Pause = FALSE;
	Flag_pauseRequest = FALSE;
}

//�`�揈��
void Phase_GameMain::Draw() {

	//�`�����Q�[����ʂɂ���
	SetDrawScreen(gameWindow);

	//��ʈ�t�Ɏl�p�`��`�悷��(��X�e�N�X�`���ɒu�������)
	DrawBox(0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, GetColor(0xb3, 0x65, 0xe5), TRUE);

	//�������u���b�N�̕`��
	if (isFallBlock_Enable()) {//�����u���b�N���L���Ȏ�
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				switch (fallBlockInfo.fallblock.BlockID[x][y]) {
				case BROCK_TYPE_RED:	//�ԃu���b�N�`��
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 0));
					break;
				case BROCK_TYPE_BLUE:	//�u���b�N�`��
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 0, 255));
					break;
				case BROCK_TYPE_GREEN:	//�΃u���b�N�`��
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 255, 0));
					break;
				case BROCK_TYPE_PURPLE:	//���u���b�N�`��
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 255));
					break;
				case BROCK_TYPE_YELLOW:	//���F�u���b�N�`��
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 255, 0));
					break;
				}
				if (fallBlockInfo.fallblock.BlockID[x][y] == BROCK_TYPE_RED) {
					
					
				}
			}
		}
	}

	//�f�o�b�O
#ifdef DEBUG_GAMEMAIN
	//�c��BLOCK_SIZE�Ԋu�Ő���`�悷��
	for (int i = 1; i < BLOCK_WIDTHNUM; i++) {
		DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, GAMEWINDOW_HEIGHT, GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = 1; i < BLOCK_HEIGHTNUM; i++) {
		DrawLine(0, i * BLOCK_SIZE, GAMEWINDOW_WIDTH, i * BLOCK_SIZE, GetColor(0xff, 0xbf, 0x74));
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

	if (isPaused()) {//�|�[�Y��Ԃ̎�
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

	if (isPaused())	return;//�|�[�Y�������������ꍇ�͐�ɐi�܂Ȃ�


	//�����u���b�N�̗�������
	if (isFallBlock_Enable()) {//�����u���b�N���L���Ȏ�
		fallBlockInfo.Counter++;	//�J�E���^�����Z
		if (isFallBlock_Falling()) {//�������̏ꍇ
			fallBlockInfo.FallCount--;
			if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 5;	//�����������[�h�̏ꍇ�J�E���g������ɓ����
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
					fallBlockInfo.FallCount = 0;	//�����J�E���g�̖�����
					printLog_I(_T("�u���b�N�̗����I��"));
					Delete_FallBlock();
					SoundEffect_Play(SE_TYPE_DecisionSelect);
				}
			}
		}
		//�L�[���͂ɂ���Ԃ̃��Z�b�g
		fallBlockInfo.Key_FlagFirstFall = FALSE;
		fallBlockInfo.Key_LRMove = 0;
		fallBlockInfo.Key_LRRota = 0;
	}
	else {
		fallBlockInfo.Counter--;
	}

	if (getFallBlock_Interval() > 120)	Create_FallBlock(NULL);//�O��̗����u���b�N�I�������莞�Ԍ�ɗ����u���b�N�̍ďo��

}

//�I������(�`�揈��)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);
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
	return (fallBlockInfo.FallCount > 0) ? TRUE : FALSE;
}

//�����u���b�N���L�����ǂ����̎擾(TRUE�ŗL��)
int Phase_GameMain::isFallBlock_Enable() {
	return (fallBlockInfo.Enable) ? TRUE : FALSE;
}

//�����u���b�N�𐶐�����(�߂�l:������TRUE)
int Phase_GameMain::Create_FallBlock(struct Fallblock_Pack *fallblock_Pack) {
	if (fallblock_Pack == NULL)	return FALSE;

	if (isFallBlock_Enable()) {
		printLog_C(_T("�������̃u���b�N�����łɑ��݂��邽�߁A�����u���b�N��V���ɒǉ��o���܂���ł���"));
		return FALSE;
	}

	//�����u���b�N�̌`���ݒ肷��(�b��)
	/*�\���}�[�N������0�͖����A1�͗L��(�ԃu���b�N�ɂȂ�悤�ɐݒ�)*/
	fallBlockInfo.fallblock.BlockID[0][0] = BROCK_TYPE_NO;
	fallBlockInfo.fallblock.BlockID[1][0] = BROCK_TYPE_YELLOW;
	fallBlockInfo.fallblock.BlockID[2][0] = BROCK_TYPE_NO;

	fallBlockInfo.fallblock.BlockID[0][1] = BROCK_TYPE_PURPLE;
	fallBlockInfo.fallblock.BlockID[1][1] = BROCK_TYPE_RED;
	fallBlockInfo.fallblock.BlockID[2][1] = BROCK_TYPE_GREEN;

	fallBlockInfo.fallblock.BlockID[0][2] = BROCK_TYPE_NO;
	fallBlockInfo.fallblock.BlockID[1][2] = BROCK_TYPE_BLUE;
	fallBlockInfo.fallblock.BlockID[2][2] = BROCK_TYPE_NO;

	//�����J�E���g��60�ɐݒ�
	fallBlockInfo.FallCount = 60;

	//�����u���b�N�̂��̑��̏��̏�����
	fallBlockInfo.PlaceX = BLOCK_WIDTHNUM / 2;
	fallBlockInfo.PlaceY = 1;
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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BROCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), BROCK_TYPE_RED) != BROCK_TYPE_NO) {
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
				if (fallBlockInfo.fallblock.BlockID[x][y] != BROCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), BROCK_TYPE_RED) != BROCK_TYPE_NO) {
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
		BROCK_TYPE RotaBlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];
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
				if (RotaBlockID[x][y] != BROCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), BROCK_TYPE_RED) != BROCK_TYPE_NO) {
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

//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO�̃u���b�N�𔻒肵���Ƃ��̖߂�l)
Phase_GameMain::BROCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, BROCK_TYPE OutGameBlock) {

	//��ʊO����
	if (X < 0 || BLOCK_WIDTHNUM <= X)	return OutGameBlock;
	if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return OutGameBlock;


	//��ʓ��̃u���b�N�̏��͖������Ȃ̂ŉ������������Ԃ�
	return BROCK_TYPE_NO;

}