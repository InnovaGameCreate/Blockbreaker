#include "Block_Fall.h"
#include "MainFunc.h" 
//�����u���b�N�̃N���X

Block_Fall::Block_Fall() {
	Enable = FALSE;
	Counter = 0;
}


Block_Fall::~Block_Fall() {
}

//�����u���b�N�̕`��
void Block_Fall::Draw() {
	if (!isEnable())	return;	//�����̏ꍇ�͉������Ȃ�

	for (int i = 0; i < ARRAY_LENGTH(BlockID_FallPoint); i++) {
		//�L���ȃu���b�N�̂ݕ`�揈��������
		if (!BlockID_FallPoint[i].isEnable())	continue;
		BlockID_FallPoint[i].Draw(phase_GameMain.getTex_Block()->getBack(), 1);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		BlockID_FallPoint[i].Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//�u���b�N�̗����\�z�n�_�Ƀu���b�N��`�悷��
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		int ShadowDrawDFlag = FALSE;
		int yCount = 0;	//y�����ɑ��݂���u���b�N�̐�
		for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
			BlockID[x][y].Draw();
			if (x == 1 && y == 1 && Flag_Rotate) {
				//���S�̏ꍇ����]�\�u���b�N�̏ꍇ
				//float Scale = 0.9 + getGraph_Sin(fallBlockInfo.Counter*5, 0.05, 0);
				float Scale = 1;
				BlockID[x][y].Draw(phase_GameMain.getTex_Block()->getCenterEffect(), Scale);
			}
		}
	}
}

//�����u���b�N�ҋ@��̕`��
void Block_Fall::Draw_WaitLine() {

	//�`��̊�ɂ��鍶����W�������l�Ƃ�
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
				Block_Field::Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);

				//�c�ɂ��炷
				X *= Scale;
				Y *= Scale;

				X += placeX + BLOCK_SIZE * Scale;
				Y += placeY + BLOCK_SIZE * Scale;
				waitBlockinfo[i].BlockID[x][y].Draw(X, Y, waitBlockinfo[i].BlockID[x][y].getBlockTexture(), Scale);
			}
		}
	}
}

//�����u���b�N�̌v�Z����(TRUE�ŗ������������u��)
int Block_Fall::Update() {
	//�J�E���^�̉��Z
	if (isEnable())	Counter++;	//�L���ȏꍇ�͐������ɉ��Z����
	else			Counter--;	//�����ȏꍇ�͕������ɉ��Z����

	if (!isEnable())	return FALSE;//�����̏ꍇ�͂���ȏ㏈�����s��Ȃ�

	FallCount--;	//��i��������܂ł̃J�E���g�_�E��
	if (Key_FlagFirstFall)	FallCount -= 20;	//�����������[�h�̏ꍇ�J�E���g������ɓ����

	if (FallCount < 0)		FallCount = 0;		//�����J�E���g��0�ȉ����Ɠs���������̂�
	if (Key_LRMove > 0) {
		//�E�ړ�
		if (FallBlock_MoveX(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);

	}
	if (Key_LRMove < 0) {
		//���ړ�
		if (FallBlock_MoveX(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);
	}
	if (Key_LRRota > 0) {
		//���v���ɉ�]
		if (FallBlock_Rotate(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);
	}
	if (Key_LRRota < 0) {
		//�����v���ɉ�]
		if (FallBlock_Rotate(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);
	}

	if (FallCount <= 0) {//�J�E���g0�ȉ��ŗ���
		FallCount = 60;	//�J�E���g��߂�(�����Ŗ߂��Ȃ���FallBlock_MoveY�֐��ňړ������Ɣ��肳��A���܂������Ȃ�)
										/*�������悤�Ƃ��Ė�����������J�E���g��0�ɂ�������������j*/
		if (FallBlock_MoveY(1) == 0) {	//�����o���Ȃ�����
			FallCount = -1;	//�����J�E���g�̖�����
			printLog_I(_T("�u���b�N�̗����I��"));
			FallBlock_addField();	//�t�B�[���h�ɗ����u���b�N��ݒu
			SoundEffect_Play(SE_TYPE_DecisionSelect);
			return TRUE;
		}
	}

	//�L�[���͂ɂ���Ԃ̃��Z�b�g
	Key_FlagFirstFall = FALSE;
	Key_LRMove = 0;
	Key_LRRota = 0;
	return FALSE;
}

//�L�[����
void Block_Fall::Key() {
	if (isEnable()) {
		if (getKeyBind(KEYBIND_DOWN) > 0) {//�����������[�h
			Key_FlagFirstFall = TRUE;
		}
		if (getKeyBind(KEYBIND_RIGHT) == 1) {//�E�ړ�
			Key_LRMove++;
		}
		if (getKeyBind(KEYBIND_LEFT) == 1) {//���ړ�
			Key_LRMove--;
		}
		if (getKeyBind(KEYBIND_ROTAL) == 1) {//�����v���
			Key_LRRota--;
		}
		if (getKeyBind(KEYBIND_ROTAR) == 1) {//���v���
			Key_LRRota++;
		}
	}
}

//�`����̍X�V
void Block_Fall::Update_DrawData(double paddingX, double paddingY) {
	//�u���b�N�̗����\�z�n�_�̃u���b�N�̕`������X�V
	int Count = 0;
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		int ShadowDrawDFlag = FALSE;
		int yCount = 0;	//y�����ɑ��݂���u���b�N�̐�
		for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
			//�u���b�N�̗����\�z�n�_�̕`��
			if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {

				//�ŏ�i�̃u���b�N��Y���W���擾����
				int ansY = phase_GameMain.getBlock_Upper(PlaceX + (x - FALLBLOCK_CENTER)) - 1 - yCount;
				//���ۂ̕`����W�ɏ���������
				double X, Y;
				Block_Field::Convert_Ingame_FromBlock(PlaceX + (x - FALLBLOCK_CENTER), ansY, 0.5, 0.5, &X, &Y);

				//�t�B�[���h�̃Y���̕����𔽉f����
				X += paddingX;
				Y += paddingY;
				//�u���b�N��V�K�o�^����
				BlockID_FallPoint[Count].addBlcok(BlockID[x][y].getBlockType(), TRUE);
				BlockID_FallPoint[Count].Update_DrawData(X, Y);
				Count++;
				yCount++;
			}
		}
	}
	//�]���������\�z�n�_�������������u���b�N�ŏ���������
	for (int i = Count; i < ARRAY_LENGTH(BlockID_FallPoint); i++) {
		BlockID_FallPoint[i].Delete_Block();
	}

	//�������u���b�N�̕`����̍X�V
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		int ShadowDrawDFlag = FALSE;
		int yCount = 0;	//y�����ɑ��݂���u���b�N�̐�
		for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
			double X, Y;
			double Per = -(FallCount / 60.);
			Block_Field::Convert_Ingame_FromBlock(PlaceX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), 0.5, Per + 0.5, &X, &Y);

			//�t�B�[���h�̃Y���̕����𔽉f����
			X += paddingX;
			Y += paddingY;
			//��ʊO�ɏo�Ă��܂��ꍇ�͂łȂ��悤�ɒ�������
			int Dan = 0;//�u���b�N�����݂���i��
			for (int y2 = 0; y2 < FALLBLOCK_SIZE; y2++) {
				for (int x2 = 0; x2 < FALLBLOCK_SIZE; x2++) {
					if (BlockID[x2][y2].getBlockType() != BLOCK_TYPE_NO) {
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
			BlockID[x][y].Update_DrawData(X, Y);
		}
	}
}

//���X�^�[�g(������)
void Block_Fall::Restart() {
	//���ݗ������̃u���b�N�̖�����
	Delete_FallBlock();

	//�u���b�N�ҋ@��̍Đ���
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo); i++) {
		Create_Wait_Block();
	}
}

//�����u���b�N�����������ǂ����̎擾(���������L��)
int Block_Fall::isEnable() {
	return ((Enable) ? TRUE : FALSE);
}

//�����u���b�N�̃C���^�[�o���̎擾(�������̏ꍇ��-1���Ԃ�܂�)
int Block_Fall::getInterval() {
	if (isEnable())	return -1;
	return -Counter;
}


//�����u���b�N��X�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
int Block_Fall::FallBlock_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isEnable())		return 0;	//���������������Ŗ������͖���

	MoveVal = getFallBlockVal_MoveX(MoveVal, CollisionFieldBlock);

	//���炵�̔��f
	PlaceX += MoveVal;

	return MoveVal;
}

//�����u���b�N��X�������Ɉړ��\���ǂ����̎擾(|�ړ��o�����|<=MoveVal)(�܂�0�ňړ��s��)
int Block_Fall::getFallBlockVal_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isEnable())		return FALSE;	//���������������Ŗ������͈ړ��s��

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
		if (Minus)	pX = PlaceX - (i + 1);	//���̕���
		else		pX = PlaceX + (i + 1);	//���̕���

		//���̃u���b�N�Ƃ̏d�Ȃ���v�Z����(�g�O���u���b�N������ƍl����)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {
					//�u���b�N�L��̏ꍇ�A�t�B�[���h�u���b�N�Ƃ̏d�Ȃ���m�F����
					if (CollisionFieldBlock) {//�t�B�[���h�u���b�N�Ƃ̂����蔻���L���ɂ���ꍇ
						if (phase_GameMain.getBlockColor(pX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//�ŊO�̃��[�v��������
						}
					}
					else {
						if (phase_GameMain.getBlockColor(pX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
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
int Block_Fall::FallBlock_MoveY(int MoveVal, int CollisionFieldBlock) {
	if (!isEnable())		return 0;	//���������������Ŗ������͖���

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
		if (Minus)	pY = PlaceY - (i + 1);	//���̕���
		else		pY = PlaceY + (i + 1);	//���̕���

		//���̃u���b�N�Ƃ̏d�Ȃ���v�Z����(�g�O���u���b�N������ƍl����)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (CollisionFieldBlock) {//�t�B�[���h�u���b�N�Ƃ̂����蔻���L���ɂ���ꍇ
						if (phase_GameMain.getBlockColor(PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//���̃u���b�N�Əd�Ȃ��Ă����ꍇ�̓��[�v�𔲂���
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//�ŊO�̃��[�v��������
						}
					}
					else {
						if (phase_GameMain.getBlockColor(PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
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
	PlaceY += MoveVal;

	return MoveVal;
}

//�����u���b�N����]������(��]��1�Ŏ��v����90�x)(�߂�l�͎��ۂ̉�]��)
int Block_Fall::FallBlock_Rotate(int RotaVal) {
	if (!isEnable())		return 0;	//���������������Ŗ������͖���

	if (Flag_Rotate == FALSE)	return 0;//��]�������̏ꍇ�͉�]���Ȃ�

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
		Block RotaBlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];
		if (Minus) {//�����v����90�x
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = BlockID[x][y];
				}
			}
		}
		else {//���v����90�x
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = BlockID[x][y];
				}
			}
		}

		//���̃u���b�N�Ƃ̏d�Ȃ���v�Z����(�g�O���u���b�N������ƍl����)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (RotaBlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {//�u���b�N�L��̏ꍇ�A�u���b�N�̏d�Ȃ���m�F����
					if (phase_GameMain.getBlockColor(PlaceX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
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
					BlockID[x][y] = RotaBlockID[x][y];
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
void Block_Fall::FallBlock_addField() {
	if (!isEnable())	return;	//���������L���Ŗ������͖���

	//���������u���b�N�ȊO�̓t�B�[���h�u���b�N�ɏ����ϊ����s��
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
			if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {
				int fX, fY;		//�u���b�N�̃t�B�[���h��̈ʒu
				BLOCK_TYPE fB;	//�ݒu����u���b�N�̎��
				fX = PlaceX + (x - FALLBLOCK_CENTER);
				fY = PlaceY + (y - FALLBLOCK_CENTER);
				fB = BlockID[x][y].getBlockType();

				phase_GameMain.add_FraldBlock2(fX, fY, fB);

			}
		}
	}
	printLog_I(_T("�����u���b�N�́y�ݒu�z"));

	//�����u���b�N�̖���������
	Delete_FallBlock();

}

//�����u���b�N�̖�����
void Block_Fall::Delete_FallBlock() {
	if (!isEnable())	return;	//���������L���Ŗ������͖���

	Counter = 0;		//�J�E���^��0�ɂ��ǂ�
	Enable = FALSE;		//�����u���b�N�̖�����

	printLog_I(_T("�����u���b�N�́y�����z"));
}

//�����u���b�N�𐶐�����(�߂�l:������TRUE)
int Block_Fall::Create_FallBlock() {

	if (isEnable()) {
		printLog_C(_T("�������̃u���b�N�����łɑ��݂��邽�߁A�����u���b�N��V���ɒǉ��o���܂���ł���"));
		return FALSE;
	}

	//�u���b�N�ҋ@��̐擪�̗v�f���琶������

	//�u���b�N���̃R�s�[
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			BlockID[i][j] = waitBlockinfo[0].BlockID[i][j];
		}
	}

	//�g���ݒ�̃R�s�[
	PlaceX = waitBlockinfo[0].PlaceX;
	PlaceY = waitBlockinfo[0].PlaceY;
	Flag_Rotate = waitBlockinfo[0].Flag_Rotate;


	//�����J�E���g��60�ɐݒ�
	FallCount = 60;

	//�����u���b�N�̂��̑��̏��̏�����
	Counter = 0;
	Key_LRMove = 0;
	Key_LRRota = 0;
	Key_FlagFirstFall = FALSE;

	//�`���������������
	double paddingX, paddingY;
	phase_GameMain.getAllPadding(&paddingX, &paddingY);
	Update_DrawData(paddingX, paddingY);



	//�L��
	Enable = TRUE;

	printLog_I(_T("�����u���b�N�́y�V�K�����z"));

	//�u���b�N�ҋ@���i�߂�
	Create_Wait_Block();

	return TRUE;
}

//�����u���b�N�̑ҋ@��̍쐬
void Block_Fall::Create_Wait_Block() {

	//����l�߂�(�擪��0)
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo) - 1; i++) {
		waitBlockinfo[i] = waitBlockinfo[i + 1];
	}



	//�V�K�ɍ쐬���闎���u���b�N�̔z�u�p�^�[�������肷��(0�`)
	const int Percent = (int)(phase_GameMain.getRandomTable()->getRand(0, 100));
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

	//�����_���ɐݒu����u���b�N��2���肷��
	BLOCK_TYPE type1 = phase_GameMain.GetRandomBlockType_FALL();
	BLOCK_TYPE type2 = phase_GameMain.GetRandomBlockType_FALL();

	//�Ō���ҋ@�u���b�N�̔z�u������������
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[i][j].Delete_Block();
		}
	}

	//�u���b�N�̓�����ʂ�ݒ肷��
	waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = TRUE;


	//��Ɍ��߂��p�^�[�����u���b�N�̔z�u�����肷��(���łɃX�|�[���ʒu��)
	switch (Pattern) {
	case 0://�c�ŉ������S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][0].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP + 1;
		//printLog_D(_T("�c�ŉ������S�p�^�[��"));
		break;
	case 1://�c�ŏ㑤���S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][2].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("�c�ŏ㑤���S�p�^�[��"));
		break;
	case 2://���ō����S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[2][1].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("���ō����S�p�^�[��"));
		break;
	case 3://���ŉE���S�p�^�[��
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[0][1].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("���ŉE���S�p�^�[��"));
		break;
	case 4://���F���e�̒P�̗���
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(BLOCK_TYPE_BOM_Color, TRUE);

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

