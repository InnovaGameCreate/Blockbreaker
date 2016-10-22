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

	//�t�B�[���h�u���b�N�̕`��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BROCK_TYPE_NO)		continue;//�����u���b�N�͕`�悵�Ȃ�
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

			switch (field[x][y].color) {
			case BROCK_TYPE_RED:	//�ԃu���b�N�`��
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 0));
				break;
			case BROCK_TYPE_BLUE:	//�u���b�N�`��
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 0, 255));
				break;
			case BROCK_TYPE_GREEN:	//�΃u���b�N�`��
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 255, 0));
				break;
			case BROCK_TYPE_PURPLE:	//���u���b�N�`��
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 255));
				break;
			case BROCK_TYPE_YELLOW:	//���F�u���b�N�`��
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 255, 0));
				break;
			}
		}
	}

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




	switch (gameCycle) {
	case GameCycle_FALL:
		if (getFallBlock_Interval() > 30)	Create_FallBlock(NULL);//�O��̗����u���b�N�I�������莞�Ԍ�ɗ����u���b�N�̍ďo��
		//�����u���b�N�̗�������
		if (Update_FallBlock()) {
			//����������͏d�̓T�C�N����
			Block_Gravity();		//�d�͂ɂ��u���b�N�̗�����ݒ�
			gameCycle = GameCycle_Gravity;
		
		}
		break;
	case GameCycle_Gravity:
		if (!isBlock_PlayMotion())	gameCycle = GameCycle_Delete;//�����T�C�N����
		break;
	case GameCycle_Delete:
		//�אڃu���b�N�̍폜
		if (Block_Delete() > 0) {
			//�������ꂽ�u���b�N�����݂���Ώd�͌v�Z
			Block_Gravity();
			gameCycle = GameCycle_Gravity;
		}
		else {
			gameCycle = GameCycle_FALL;
		}
		break;
	default:
		break;
	}



	//�ړ����[�V�����̃J�E���g�A�b�v�ƈړ��I���͖��������鏈��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
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
					continue;
				}
			}
		}
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
	//if (fallblock_Pack == NULL)	return FALSE;

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
					if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BROCK_TYPE_NO) {
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
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BROCK_TYPE_NO) {
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
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BROCK_TYPE_NO) {
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
			if (fallBlockInfo.fallblock.BlockID[x][y] != BROCK_TYPE_NO) {
				int fX, fY;		//�u���b�N�̃t�B�[���h��̈ʒu
				BROCK_TYPE fB;	//�ݒu����u���b�N�̎��
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
int Phase_GameMain::add_FraldBlock(int X, int Y, BROCK_TYPE brock_type) {
	//�u���b�N�����u���b�N�͐ݒu�s��
	if (brock_type == BROCK_TYPE_NO)					return FALSE;

	//�u���b�N�̏㏑���͎��s�ɂ���(��ʊO���u���b�N�L��Ɣ��肪�o��ݒ�ɂ���)
	if (getBlockColor(X, Y, TRUE) != BROCK_TYPE_NO)	return FALSE;

	//�u���b�N�̐ݒu
	field[X][Y].fall_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
	field[X][Y].move_flag = FALSE;	//�����l����ł����̂�������񂪈ꉞ���������Ƃ�
	field[X][Y].color = brock_type;	//�u���b�N�̒u������

	printLog_I(_T("�t�B�[���h�u���b�N�̐V�K����[%d][%d](type=%d)"), X, Y, brock_type);

	return TRUE;
}

//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���)
Phase_GameMain::BROCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock) {

	//��ʊO����(��ʊO�u���b�N����`����Ă��Ȃ��̂ŁA�ԃu���b�N���ݒu����Ă��邱�Ƃɂ���)
	if (X < 0 || BLOCK_WIDTHNUM <= X)	return (useOutScreenBlock) ? BROCK_TYPE_RED : BROCK_TYPE_NO;
	if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return (useOutScreenBlock) ? BROCK_TYPE_RED : BROCK_TYPE_NO;

	return field[X][Y].color;

}

//�t�B�[���h�u���b�N���d�͂ŗ���������
void Phase_GameMain::Block_Gravity() {


	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		//�񂲂ƂɃu���b�N�����R�s�[����
		field_info t[BLOCK_HEIGHTNUM];
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			t[y] = field[x][y];
			field[x][y].color = BROCK_TYPE_NO;
		}
		int Count = BLOCK_HEIGHTNUM - 1;
		//���̒i���瑶�݂���u���b�N����ג���(�t����)
		for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
			if (t[y].color != BROCK_TYPE_NO) {
				field[x][Count] = t[y];
				//�������[�V����(�J�E���g���ړ���Ay���ړ����ɂȂ�)
				Block_SetMotion(x, Count, x, y, x, Count, 0.3, 15);
				Count--;
			}
		}
	}

	printLog_I(_T("�u���b�N�ɏd�͌v�Z���s���܂���"));
}

//�t�B�[���h�u���b�N�𒼐ڍ폜����(�d�͌v�Z���s�����ǂ����̃t���O)
void Phase_GameMain::Block_Delete_Direct(int X, int Y, int CallGravityFlag) {
	//��ʊO����(��ʊO�u���b�N����`����Ă��Ȃ��̂ŁA�ԃu���b�N���ݒu����Ă��邱�Ƃɂ���)
	if (X < 0 || BLOCK_WIDTHNUM <= X)	return;
	if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return;

	field[X][Y].color = BROCK_TYPE_NO;
	printLog_I(_T("�u���b�N�́y�폜�z[%d][%d]"), X, Y);

	if (CallGravityFlag)	Block_Gravity();
}

//�A������t�B�[���h�u���b�N���폜����(���łɂ��ז��u���b�N�̏������s��)(���������u���b�N�̐�)
int Phase_GameMain::Block_Delete() {
	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BROCK_TYPE_NO) {//���O�u���b�N
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
					Block_Delete_Direct(x, y, FALSE);
					DelCount++;
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
	BROCK_TYPE bt = field[x][y].color;      //�u���b�N�̎�ނ��L�^����
	deleteFlag[x][y] = ID;					//�T���ς�(�T��ID��ݒ肷��)
	(*Counter)++;

	if (x + 1 < BLOCK_WIDTHNUM	&& field[x + 1][y].color == bt) SequenceCount(x + 1, y, ID, deleteFlag, Counter);
	if (y + 1 < BLOCK_HEIGHTNUM	&& field[x][y + 1].color == bt) SequenceCount(x, y + 1, ID, deleteFlag, Counter);
	if (x - 1 >= 0 && field[x - 1][y].color == bt) SequenceCount(x - 1, y, ID, deleteFlag, Counter);
	if (y - 1 >= 0 && field[x][y - 1].color == bt) SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//�t�B�[���h�̃u���b�N�Ƀ��[�V������ݒ肷��
void Phase_GameMain::Block_SetMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockColor(x, y) == BROCK_TYPE_NO)	return;	//�u���b�N�������̏ꍇ�͏��������Ȃ�
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

//���[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
int Phase_GameMain::isBlock_PlayMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color != BROCK_TYPE_NO && field[x][y].blockMoveMotion.Enable) {
				return TRUE;
			}
		}
	}

	return FALSE;
}