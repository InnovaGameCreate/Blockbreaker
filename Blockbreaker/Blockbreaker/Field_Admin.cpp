#include "Field_Admin.h"
#include "MainFunc.h"

//�t�B�[���h�u���b�N�����N���X

//������(�`�揈��)
void Field_Admin::Init_Draw() {
	//�S�t�B�[���h�u���b�N�̏��������s��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Init_Draw();
		}
	}
}

//������(�v�Z����)
void Field_Admin::Init_Update() {
	//�S�t�B�[���h�u���b�N�̏��������s��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Init_Update();
		}
	}
}

//���X�^�[�g����
void Field_Admin::Restart() {
	//�S�t�B�[���h�u���b�N�̃��X�^�[�g�������s��
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Restart();
		}
	}

	//�K���Ƀu���b�N��ݒu����(�����畡���i)
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL, BLOCK_WIDTHNUM_INGAME, BLOCK_DEFAULT_VAL);

	//���z�u���b�N�̍X�V���s��
	Virtualfield_Update();

	//���[�U�[�G�t�F�N�g�̏�����
	Count_lay = 0;
	lay.SetpointNum(0);
}


/*��{����*/
//�u���b�N�`�揈��
void Field_Admin::Draw_Block() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {

			////�Q�[���I�[�o�[���ɉ��ɗ���������
			//if (getPauseMode() == PauseMode_GameOver) {
			//	if (Count_Pause < 300)	Y += 1 / 2.*0.2*Count_Pause*Count_Pause;
			//	else					Y += 1 / 2.*0.2 * 300 * 300;
			//}

			field[x][y].Draw();
		}
	}
}

//���[�U�[�G�t�F�N�g�`�揈��
void Field_Admin::Draw_Lay() {
	//�j������̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawPolygon2D_Notexture2(&lay, GetColor(200, 200, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�ړ����[�V�����̍X�V(�ړ����[�V�������s��ꂽ�Ƃ���TRUE)
int Field_Admin::Update_MoveMotion() {
	int count = 0;//�ړ����[�V�������L���Ȑ�

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].getMoveMotion()->Update();
			if (field[x][y].getMoveMotion()->isEnable())	count++;//�L���ȏꍇ�͉��Z
		}
	}

	return ((count > 0) ? TRUE : FALSE);
}

//�ω����[�V�����̍X�V(�ω����[�V�������s��ꂽ�Ƃ���TRUE)
int Field_Admin::Update_ChangeMotion() {
	int count = 0;//�ړ��������s�����u���b�N�̐�

				  //�ω����[�V�����̃J�E���g�A�b�v
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].getChangeMotion()->Update();
			if (field[x][y].getChangeMotion()->isEnable())	count++;
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//�S�̈ړ��̍X�V(TRUE�S�̈ړ��̍X�V���I������u��)
int Field_Admin::Update_AllMove() {
	if (!AllMovedata.isEnable())	return FALSE;

	//�u���b�N�S�̈ړ����L���ȏꍇ�́A�ʏ�̏��������s�����A�S�̈ړ��̃J�E���g�A�b�v�̂ݍs���悤�ɂ���
	AllMovedata.Update();
	if (AllMovedata.isEnable() == FALSE) {
		//�ړ������̎�
		int ToX, ToY;
		AllMovedata.getToPoint(&ToX, &ToY);	//�ړ���ɐݒ肵�����W���擾����
		AllMove(ToX, ToY);					//�u���b�N�S�̂��ړ�����
		return TRUE;
	}

	return FALSE;
}

//�j������G�t�F�N�g�̍X�V
void Field_Admin::Update_Lay() {
	if (lay.getpointNum() == 3) {
		Count_lay++;
		if (Count_lay < 15) {
			//�������Ȃ�
		}
		else if (Count_lay < 45) {
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

//�`����̍X�V
void Field_Admin::Update_DrawData() {
	double Field_PaddingX, Field_PaddingY;
	getField_Padding(&Field_PaddingX, &Field_PaddingY);

	//�t�B�[���h�u���b�N�̍��W�v�Z
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//�`���̍��W���v�Z����
			field[x][y].Update_DrawData(Field_PaddingX, Field_PaddingY, x, y);
		}
	}
}

//�L�[����
void Field_Admin::key() {
	if (AllMovedata.isEnable())	return;//�S�̈ړ����L���ȏꍇ�͏��������Ȃ�

	if (getKeyBind(KEYBIND_UP) == 1) {
		//�u���b�N�̐ݒu
		//���E�h�~
		int Flag = TRUE;//���S�̈�Ƀu���b�N����������FALSE�ɂȂ�
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < GAMEOVER_BORDER + 1; y++) {
				if (getBlockType(x, y) != BLOCK_TYPE_NO) {
					//�Ȃ񂩃u���b�N������ꍇ
					Flag = FALSE;
					break;
				}
			}
		}
		if (Flag)	add_Under();//��Ƀu���b�N���Ȃ��ꍇ�Ɏ��s�����
	}
}


/*�u���b�N�ɕύX��������n*/
//�w�肵���G���A�Ƀu���b�N��ݒu����(�������肪����Ȃ��悤�ɐݒu���܂�)
void Field_Admin::setBlock_Rect(int x, int y, int w, int h) {
	//���z�t�B�[���h�����X�V����
	Virtualfield_Update();

	for (int bl_X = x; bl_X < x + w; bl_X++) {
		for (int bl_Y = y; bl_Y < y + h; bl_Y++) {
			BLOCK_TYPE bt;
			int Count = 0;

			do {
				Count = 0;
				bt = phase_GameMain.GetRandomBlockType_UNDER();//�����_���Ńu���b�N�����肵���z�ݒu����
				add_FieldBlock(bl_X, bl_Y, bt, TRUE, TRUE, NULL, TRUE);
				int BlockFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
				//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
				CreateSequenceCountTable(BlockFlag, 0, 0, BLOCK_WIDTHNUM, BLOCK_HEIGHTNUM, TRUE);
				SequenceCount(bl_X, bl_Y, 0, BlockFlag, &Count, TRUE);
			} while (Count >= BLOCK_DELETE_LEN);

			add_FieldBlock(bl_X, bl_Y, bt, FALSE, TRUE);//�{�Ԃ̐ݒu
		}
	}
}

//�t�B�[���h�Ƀu���b�N��ݒu����
int Field_Admin::add_FieldBlock(int X, int Y, BLOCK_TYPE type, int Override, int OutScreen, BLOCK_TYPE *Before, int UseVirtualField) {
	//�O�ɐݒu����Ă����u���b�N�̏�������������
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;

	//���ݐݒu����Ă���u���b�N����ʊO�u���b�N(�܂�͈͊O�̍��W���n���ꂽ)�ꍇ�͉������Ȃ�
	if (getBlockType(X, Y, TRUE, !OutScreen, UseVirtualField) == BLOCK_TYPE_NUM)	return FALSE;

	//�u���b�N�̐ݒu���s��
	const int ans = ((UseVirtualField) ? Virtualfield[X][Y] : field[X][Y]).addBlcok(type, Override, Before);

	if (ans) {//�u���b�N�̐ݒu�ɐ��������ꍇ
		if (UseVirtualField)	printLog_I(_T("[���z]�t�B�[���h�u���b�N�y�V�K�����z[%d][%d](type=%d)"), X, Y, type);
		else				printLog_I(_T("�t�B�[���h�u���b�N�y�V�K�����z[%d][%d](type=%d)"), X, Y, type);
	}

	return ans;
}

//������u���b�N���킢�Ă���
void Field_Admin::add_Under() {
	if (AllMovedata.isEnable())	return;//���łɎ��s���̏ꍇ�͏��������Ȃ�
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN, BLOCK_WIDTHNUM_INGAME, 1);
	AllMoveRequest(0, -1);	//�u���b�N�S�̂��ړ�
}

//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ�����(��ʊO�ɏo�Ă��܂��u���b�N�͏��ł��܂�)
void Field_Admin::AllMove(int X, int Y) {
	//�����ɖ��ʂ������c

	//����ړ�
	if (X <= 0 && Y <= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//�͈͓��Ȃ畁�ʂɃR�s�[����
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//�ړ����[�V�����ɕ␳��������
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Delete_Direct(x, y);
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
					field[x][y].getMoveMotion()->Slide(X, Y);//�ړ����[�V�����ɕ␳��������
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Delete_Direct(x, y);
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
					field[x][y].getMoveMotion()->Slide(X, Y);//�ړ����[�V�����ɕ␳��������
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Delete_Direct(x, y);
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
					field[x][y].getMoveMotion()->Slide(X, Y);//�ړ����[�V�����ɕ␳��������
				}
				else {
					//�͈͊O�Ȃ�u���b�N�̏���
					Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("�u���b�N�S�̂��E���ɂ��炵�܂���(%d,%d)"), X, Y);
	}

	//�������u���b�N���ړ�����(��ʊO�ɂ͍s���܂���)
	phase_GameMain.getfallBlockInfo()->MoveX(X, FALSE);
	phase_GameMain.getfallBlockInfo()->MoveY(Y, FALSE);

}

//�t�B�[���h�u���b�N�𒼐ڍ폜����(�폜���ꂽ��TRUE)
int Field_Admin::Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int Delay) {
	//���݂̃u���b�N�̎�ނ̎擾(�폜�O)
	BLOCK_TYPE bt = getBlockType(X, Y, FALSE, FALSE);	//�폜�����u���b�N�̎��
	if (bt == BLOCK_TYPE_NO)	return FALSE;//�u���b�N�������������݂��Ȃ��ꍇ�͉������Ȃ�
											 //�u���b�N�̍폜���s��


	int flag = field[X][Y].Delete_Block();

	if (flag) {
		//�u���b�N���폜���ꂽ
		if (PlayMotion == BlockChangeMotionType_EXPLOSION) {
			SetChangeMotion_EXPLOSION(X, Y, bt, Delay);	//���[�V�����̐���
		}
		else if (PlayMotion == BlockChangeMotionType_SMALL) {
			SetChangeMotion_SMALL(X, Y, bt, Delay);	//���[�V�����̐���
		}
	}

	return ((flag) ? TRUE : FALSE);
}

//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜(�폜���ꂽ��TRUE)
int Field_Admin::Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion) {
	if (!Block::isSameColorBlock(type, getBlockType(X, Y), FALSE))	return FALSE;//�Ⴄ�F�̃u���b�N�̏ꍇ�͍폜���Ȃ�

	return Delete_Direct(X, Y, PlayMotion);
}

//�j������Ńu���b�N��j�󂷂�
void Field_Admin::Delete_Lay() {
	//���[�U�[�̃G�t�F�N�g������������
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
			Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, x * 2 + 15);
		}
	}

	//�X�R�A�����炷
	phase_GameMain.getScore()->addScore(1, -1'0000);
}

//�A������t�B�[���h�u���b�N���폜����(���łɏ����ɂ���Ĕ���������ʂ���������)(���������u���b�N�̐�)
int Field_Admin::Delete_Join(const int Len, int Flag_Event) {

	int DeleteBlockFlag = FALSE;	//�폜���ꂽ��TRUE

									//��ʓ��̑��݂���u���b�N�݂̂Ōv�Z����
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	CreateSequenceCountTable(DeleteFlag, BLOCK_PADDINGLEFT, BLOCK_PADDINGUP, BLOCK_WIDTHNUM_INGAME, BLOCK_HEIGHTNUM_INGAME);

	//�폜�O�̃u���b�N�̈ꗗ���쐬����
	BLOCK_TYPE old[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			old[x][y] = getBlockType(x, y);
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
								if (Delete_Direct(i, y, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//�t���C�e�L�X�g�̐���
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(i, y, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
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
								if (Delete_Direct(x, i, BlockChangeMotionType_EXPLOSION, abs(y - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//�t���C�e�L�X�g�̐���
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x, i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
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
								if (Delete_Direct(x + i, y - i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//�t���C�e�L�X�g�̐���
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
								if (Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//�t���C�e�L�X�g�̐���
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x - i, y + i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
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
								if (Delete_Direct(x + i, y + i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//�t���C�e�L�X�g�̐���
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
								if (Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//�t���C�e�L�X�g�̐���
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x - i, y - i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
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
	if (!Flag_Event) {
		DelMotion = BlockChangeMotionType_EXPLOSION;
	}
	//�אڂ��Ă���u���b�N���폜����
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//�z��͈͓̔�
				if (Counter[DeleteFlag[x][y]] >= Len) {
					//�폜
					if (Delete_Direct(x, y, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_NOMAL);
						DelCount++;
						DeleteBlockFlag = TRUE;
						//�t���C�e�L�X�g�̐���
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}

					//���łɗאڂ�����؃u���b�N���폜
					if (Delete_Color(x, y - 1, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//��
						DeleteBlockFlag = TRUE;
						//�t���C�e�L�X�g�̐���
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_OPTION);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
					if (Delete_Color(x, y + 1, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//��
						DeleteBlockFlag = TRUE;
						//�t���C�e�L�X�g�̐���
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
					if (Delete_Color(x - 1, y, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//��
						DeleteBlockFlag = TRUE;
						//�t���C�e�L�X�g�̐���
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
					if (Delete_Color(x + 1, y, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//�E
						DeleteBlockFlag = TRUE;
						//�t���C�e�L�X�g�̐���
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x + 1, y, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
				}
			}
		}
	}

	printLog_I(_T("�אڃu���b�N�̍폜�v�Z���s���܂���(%d�u���b�N)"), DelCount);

	if (DeleteBlockFlag) {
		//�u���b�N�̏������肪�����
		ChainCount++;	//�A���J�E���g�����Z����
	}

	return DelCount;
}

//��ʊO�̃u���b�N�����ׂč폜����(���������u���b�N�̐�)
int Field_Admin::Delete_OutScreen() {
	int count = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (getBlockType(x, y, TRUE, TRUE) == BLOCK_TYPE_NUM) {
				//��ʊO�u���b�N�̏ꍇ�͍폜
				if (Delete_Direct(x, y)) {
					count++;
				}
			}
		}
	}

	printLog_I(_T("��ʊO�̃u���b�N�����ׂč폜(%d��)"), count);
	return count;
}


//���z�t�B�[���h�����݂̃t�B�[���h�ƈ�v������
void Field_Admin::Virtualfield_Update() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			Virtualfield[x][y] = field[x][y];
		}
	}
	printLog_I(_T("���z�t�B�[���h���X�V���܂���"));
}

//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ����郊�N�G�X�g������(�Q�[�����ꎞ��~���ē������܂�)
void Field_Admin::AllMoveRequest(int X, int Y) {
	if (AllMovedata.isEnable())	return;//���łɃu���b�N���ړ����̏ꍇ�A��������

	AllMovedata.Create(0, 0, X, Y, 0.1, 2);

	printLog_I(_T("�u���b�N�S�̈ړ����ݒ肳��܂���(%d,%d)"), X, Y);
}

//�t�B�[���h�ɑ��݂��鍕�F�u���b�N�̐F�����肷��
void Field_Admin::Func_Black() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BLACK) {//���u���b�N�̎�
				//�m���Ńu���b�N��ID������������
				int Val = (int)phase_GameMain.getRandomTable()->getRand(0, 100);
				if (Val < 20)		field[x][y].addBlcok(BLOCK_TYPE_RED, TRUE);		//�ԐF�u���b�N
				else if (Val < 40)	field[x][y].addBlcok(BLOCK_TYPE_BLUE, TRUE);	//�F�u���b�N
				else if (Val < 60)	field[x][y].addBlcok(BLOCK_TYPE_YELLOW, TRUE);	//���F�u���b�N
				else if (Val < 80)	field[x][y].addBlcok(BLOCK_TYPE_GREEN, TRUE);	//�ΐF�u���b�N
				else 				field[x][y].addBlcok(BLOCK_TYPE_PURPLE, TRUE);	//���F�u���b�N

				SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_BLACK, 0);	//�ω����[�V�����̐ݒ�
			}
		}
	}
}

//�t�B�[���h�ɑ��݂�����F�u���b�N�̐F�����肷��(�����珇��)
void Field_Admin::Func_Rainbow() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_RAINBOW) {//���F�u���b�N�̎�
				if (getBlockType(x, y + 1) == BLOCK_TYPE_NO) {//���Ƀu���b�N������
					
					//�m���Ńu���b�N��ID������������
					int Val = (int)phase_GameMain.getRandomTable()->getRand(0, 100);
					if (Val < 20)		field[x][y].addBlcok(BLOCK_TYPE_RED, TRUE);		//�ԐF�u���b�N
					else if (Val < 40)	field[x][y].addBlcok(BLOCK_TYPE_BLUE, TRUE);	//�F�u���b�N
					else if (Val < 60)	field[x][y].addBlcok(BLOCK_TYPE_YELLOW, TRUE);	//���F�u���b�N
					else if (Val < 80)	field[x][y].addBlcok(BLOCK_TYPE_GREEN, TRUE);	//�ΐF�u���b�N
					else 				field[x][y].addBlcok(BLOCK_TYPE_PURPLE, TRUE);	//���F�u���b�N
				}
				else {
					//���Ƀu���b�N������ꍇ
					field[x][y].addBlcok(getBlockType(x, y + 1), TRUE);
				}
				//�ω����[�V�����̐ݒ�
				SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_RAINBOW, 0);
			}
		}
	}
}

//�t�B�[���h�ɑ��݂��锚�e�u���b�N�𔚔j����
void Field_Admin::Func_BOMB() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BOM) {//���e�u���b�N�̎�
															   //���g�̍폜
				if (Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION))	DeleteNum++;

				//���͂̃u���b�N���폜����(���e�u���b�N�͍폜���Ȃ�)
				if (getBlockType(x + 1, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 1, y, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 2, y, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}
				if (getBlockType(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 1, y, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 2, y, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}
				if (getBlockType(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y + 1, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y + 2, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}
				if (getBlockType(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y - 1, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y - 2, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}


				if (getBlockType(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 1, y - 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
				if (getBlockType(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 1, y - 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
				if (getBlockType(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 1, y + 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
				if (getBlockType(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 1, y + 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//�t�B�[���h�ɑ��݂���2���e�u���b�N�𔚔j����
void Field_Admin::Func_2BOMB() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_2BOM) {//���e�u���b�N�̎�
																//���g�̍폜
				if (Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION))	DeleteNum++;

				//2�אڂ��Ă���u���b�N��j�󂷂�
				DeleteNum += Delete_Join(2, FALSE);
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//�t�B�[���h�ɑ��݂��铯�F���e�u���b�N�𔚔j����
void Field_Admin::Func_BOMBColor() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BOM_Color) {//���e�u���b�N�̎�
																	 //���g�̍폜
				if (Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION))	DeleteNum++;
				//�^���̃u���b�N�̐F���擾����
				BLOCK_TYPE under = getBlockType(x, y + 1);

				//���F�u���b�N���폜����
				for (int x2 = BLOCK_PADDINGLEFT; x2 < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x2++) {
					for (int y2 = BLOCK_PADDINGUP; y2 < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y2++) {
						Delete_Color(x2, y2, under, BlockChangeMotionType_EXPLOSION);
					}
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//�t�B�[���h�u���b�N���d�͂ŗ���������
void Field_Admin::Gravity(int InGameOnly) {
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
		Block_Field t[BLOCK_HEIGHTNUM];
		for (int y = sY; y < eY; y++) {
			t[y] = field[x][y];
			field[x][y].Delete_Block();	//��������t�B�[���h�̃u���b�N�����폜����
		}
		int Count = eY - 1;
		//���̒i���瑶�݂���u���b�N����ג���(�t����)
		for (int y = eY - 1; y >= sY; y--) {
			if (t[y].getBlockType() != BLOCK_TYPE_NO) {
				field[x][Count] = t[y];
				//�������[�V����(�J�E���g���ړ���Ay���ړ����ɂȂ�)
				SetMoveMotion(x, Count, x, y, x, Count, 0.3, 15);
				Count--;
			}
		}
	}

	printLog_I(_T("�u���b�N�ɏd�͌v�Z���s���܂���"));
}

/*���[�V�����ݒ�֌W*/
//�t�B�[���h�̃u���b�N�ɕω����[�V������ݒ肷��(����P�̂Ŏg�p���Ď��̂��Ă��m��܂���)
void Field_Admin::SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay) {
	if (getBlockType(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//�u���b�N����ʊO�̏ꍇ�͏��������Ȃ�

	int ans = field[x][y].getChangeMotion()->Create(mtype, From, To, MotionLength, Delay);

	if (ans)	printLog_I(_T("�u���b�N�Ɂy�ω����[�V�����z��ݒ�[%d][%d]"), x, y);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��
void Field_Admin::SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int Delay) {

	BLOCK_TYPE From = getBlockType(x, y, FALSE, FALSE);

	if (From == To)				return;		//�ω��悪�����ꍇ�͏��������Ȃ�
	if (To == BLOCK_TYPE_NO)	return;		//�ω��悪�u���b�N�����̏ꍇ�͏��������Ȃ�(�������`��o���Ȃ�����)

	const int MotionLength = 20;
	SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, From, To, MotionLength, Delay);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��(�ω����w��)
void Field_Admin::SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int Delay) {

	BLOCK_TYPE To = getBlockType(x, y, FALSE, FALSE);
	if (from == To)				return;		//�ω��悪�����ꍇ�͏��������Ȃ�
	if (To == BLOCK_TYPE_NO)	return;		//�ω��悪�u���b�N�����̏ꍇ�͏��������Ȃ�(�������`��o���Ȃ�����)

	const int MotionLength = 20;
	SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, from, To, MotionLength, Delay);
}


//�t�B�[���h�̃u���b�N�ɕω����[�V����(����)��ݒ肷��
void Field_Admin::SetChangeMotion_EXPLOSION(int x, int y, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//�u���b�N�����݂��Ȃ��ꍇ�͖���


	const int MotionLength = 40;
	SetChangeMotion(x, y, BlockChangeMotionType_EXPLOSION, From, From, MotionLength, Delay);
}

//�t�B�[���h�̃u���b�N�ɕω����[�V����(�������Ȃ��ď�����)��ݒ肷��
void Field_Admin::SetChangeMotion_SMALL(int x, int y, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//�u���b�N�����݂��Ȃ��ꍇ�͖���


	const int MotionLength = 15;
	SetChangeMotion(x, y, BlockChangeMotionType_SMALL, From, From, MotionLength, Delay);
}

//�t�B�[���h�̃u���b�N�ړ��Ƀ��[�V������ݒ肷��
void Field_Admin::SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockType(x, y, FALSE, FALSE) == BLOCK_TYPE_NO)	return;	//�u���b�N�������̏ꍇ�͏��������Ȃ�

	int ans = field[x][y].getMoveMotion()->Create(FromX, FromY, ToX, ToY, a, MaxSpeed);

	if (ans)	printLog_I(_T("�u���b�N�Ɂy�ړ����[�V�����z��ݒ�(%d,%d)"), x, y);
}


/*�אڌ��v�Z�֌W*/
//�אڂ��铯�F�u���b�N�Ƀ}�[�J�[��t����
void Field_Admin::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter, int UseVirtualField) {
	if (deleteFlag == NULL)		return;		//�}�[�J�[��t����e�[�u�����Ȃ��ꍇ
	if (deleteFlag[x][y] != -1)	return;		//���T���u���b�N����Ȃ��ꍇ
	BLOCK_TYPE bt = ((UseVirtualField) ? Virtualfield[x][y].getBlockType() : field[x][y].getBlockType());	//�u���b�N�̎�ނ��L�^����
	deleteFlag[x][y] = ID;	//�T���ς�(�T��ID��ݒ肷��)
	(*Counter)++;

	int OnlyColor = TRUE;

	BLOCK_TYPE NextBlock = ((UseVirtualField) ? Virtualfield[x + 1][y] : field[x + 1][y]).getBlockType();
	if (x + 1 < BLOCK_WIDTHNUM	&& Block::isSameColorBlock(NextBlock, bt, OnlyColor))		SequenceCount(x + 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y + 1] : field[x][y + 1]).getBlockType();
	if (y + 1 < BLOCK_HEIGHTNUM	&& Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x - 1][y] : field[x - 1][y]).getBlockType();
	if (x - 1 >= 0 && Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y - 1] : field[x][y - 1]).getBlockType();
	if (y - 1 >= 0 && Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//SequenceCount�Ŏg�p����}�[�J�[�e�[�u�����쐬����(�L���ȃG���A)(UseVirtualField=TRUE�ŉ��z�̖ʂ��g�p����)
void Field_Admin::CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField) {
	if (deleteFlag == NULL)	return;

	//�אڃu���b�N����ID���L�^����\�̍쐬(-1���T���ABLOCK_WIDTHNUM*BLOCK_HEIGHTNUM�T�����珜�O)
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			const BLOCK_TYPE type = getBlockType(x, y, FALSE, FALSE, UseVirtualField);	//�u���b�N�̎�ނ��擾����
			if (!(X <= x && x < X + W && Y <= y && y < Y + H) ||	//�͈͊O
				type == BLOCK_TYPE_NO ||
				type == BLOCK_TYPE_NUM ||
				type == BLOCK_TYPE_TREE ||
				type == BLOCK_TYPE_BLACK ||
				type == BLOCK_TYPE_RAINBOW ||
				type == BLOCK_TYPE_BOM ||
				type == BLOCK_TYPE_2BOM ||
				type == BLOCK_TYPE_BOM_Color) {		//���O�u���b�N
				deleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				deleteFlag[x][y] = -1;
			}
		}
	}
}

//�u���b�N�̃`�F�C���������Z�b�g����
void Field_Admin::ChainCount_Reset() {
	ChainCount = 0;
	printLog_I(_T("�`�F�C���������Z�b�g���܂���"));
}


/*�擾�n*/
//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���TRUE����)(��4�����͎��ۂɕ`�悳���G���A�ȊO����ʊO�ɂ���ꍇTRUE,�u���b�N��񂪖����ʒu����ʊO�ɂ���ꍇ��FALSE��ݒ肷��)
BLOCK_TYPE Field_Admin::getBlockType(int X, int Y, int useOutScreenBlock, int InGame, int UseVirtualField) {

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

	return ((UseVirtualField) ? Virtualfield[X][Y] : field[X][Y]).getBlockType();
}

//�u���b�N�S�̈ړ��N���X�̃|�C���^���擾
BlockMoveMotion *Field_Admin::getBlockMoveMotion() {
	return &AllMovedata;
}

//�t�B�[���h�S�̂̃Y�����擾����
void Field_Admin::getField_Padding(double *Field_PaddingX, double *Field_PaddingY) {
	//�t�B�[���h�S�̂̃Y�����v�Z
	if (AllMovedata.isEnable()) {//�S�̂��炷���L���ȏꍇ
		if (Field_PaddingX != NULL)	*Field_PaddingX = AllMovedata.getPointX() - BLOCK_SIZE / 2.;
		if (Field_PaddingY != NULL)	*Field_PaddingY = AllMovedata.getPointY() - BLOCK_SIZE / 2.;
	}
	else {
		if (Field_PaddingX != NULL)	*Field_PaddingX = 0;
		if (Field_PaddingY != NULL)	*Field_PaddingY = 0;
	}
}

//�ړ����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
int Field_Admin::isPlayingMoveMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getMoveMotion()->isEnable()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�ω����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
int Field_Admin::isPlayingChangeMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getChangeMotion()->isEnable()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//�w�肵��X���W�̈�ԏ�̃u���b�N��Y���W���擾����(�����Ă�����W�݂̂Ŕ��f)
int Field_Admin::getUpperX(int x) {
	for (int y = BLOCK_PADDINGUP; y < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y++) {
		if (getBlockType(x, y) != BLOCK_TYPE_NO)	return y;
	}
	return BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;//�ŉ��i�̈�i���̍��W��Ԃ�
}

//�ő�̍����̃u���b�N��Y���W���擾����
int Field_Admin::getmaxUpperX() {
	int Max_Y = BLOCK_HEIGHTNUM;
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		Max_Y = min(Max_Y, getUpperX(x));
	}
	return Max_Y;
}

//���݂̃`�F�C�������擾����
int Field_Admin::getChain() {
	return ChainCount;
}