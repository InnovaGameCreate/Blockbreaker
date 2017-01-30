#include "Block.h"
#include "MainFunc.h"
#include "Tex_Block.h"

Block::Block() { }


Block::~Block() { }

//����������(�v�Z����)
void Block::Init_Update() {
	printLog_I(_T("Block�N���X�̏�����(�v�Z)"));
}

//����������(�`�揈��)
void Block::Init_Draw() {

	printLog_I(_T("Block�N���X�̏�����(�`��)"));
}

//�`�揈��
void Block::Draw() {
	if (color == BLOCK_TYPE_NO)	return;
	Draw(((Phase_GameMain*)phaseController.getInstance())->getTex_Block()->getTexture(color), 1);
}

//�`�揈��(�ڍאݒ�)
void Block::Draw(int grHandle, double scale) {
	float Scale = (float)scale;
	Draw(DrawPlaceX, DrawPlaceY, grHandle, scale);
}

//�`�揈��(�ڍאݒ�2)
void Block::Draw(double centerX, double centerY, int grHandle, double scale) {
	float Scale = (float)scale;
	DrawRectRotaGraphFast2((int)centerX, (int)centerY, 0, 0,
		BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
		(float)Scale, 0, grHandle, TRUE, FALSE);
}

//�u���b�N�̍폜(TRUE�ō폜)
int Block::Delete_Block() {
	if (color == BLOCK_TYPE_NO || color == BLOCK_TYPE_NUM) {
		//���������u���b�N�f�[�^���Ȃ�
		return FALSE;
	}

	//�u���b�N�f�[�^���u���b�N�����ɂ���
	color = BLOCK_TYPE_NO;
	return TRUE;
}

//���݂̃u���b�N�̎�ނ��擾����
BLOCK_TYPE Block::getBlockType() {
	return color;
}

//���݂̃u���b�N�̃e�N�X�`���n���h�����擾����
int Block::getBlockTexture() {
	return ((Phase_GameMain*)phaseController.getInstance())->getTex_Block()->getTexture(color);
}

//�u���b�N��ݒu����
/*
type:		�ݒu����u���b�N�̎��
override:	TRUE�ł��łɃu���b�N�������Ă����Ă��ݒu����
before:		�O�ɐݒu����Ă����u���b�N(NULL�\)
�߂�l:		TRUE�Őݒu����
*/
int Block::addBlcok(BLOCK_TYPE type, int override, BLOCK_TYPE *before) {
	//���݂̃u���b�N�̎�ނ��擾����
	const BLOCK_TYPE NowType = color;

	//���݂̃u���b�N���������Ƃ�
	if (before != NULL)	*before = NowType;

	if (override == FALSE) {
		//�㏑���������ȏꍇ�̓u���b�N�����łɑ��݂����牽�����Ȃ�
		if (NowType != BLOCK_TYPE_NO)	return FALSE;
	}

	if (type == BLOCK_TYPE_NO || type == BLOCK_TYPE_NUM) {
		//�ݒu�s�u���b�N�Ȃ̂ŁA�ݒu���Ȃ�
		return FALSE;
	}

	//�u���b�N�̐ݒu
	color = type;

	return TRUE;//����
}

//�`��ɕK�v�ȏ����X�V����(�`�悷�钆�S���W)
void Block::Update_DrawData(double drawPlaceX, double drawPlaceY) {
	DrawPlaceX = drawPlaceX;
	DrawPlaceY = drawPlaceY;
}

//�`��ʒuX���擾����
double Block::getDrawPlaceX() {
	return DrawPlaceX;
}

//�`��ʒuY���擾����
double Block::getDrawPlaceY() {
	return DrawPlaceY;
}

//�w�肵��2�̃u���b�N�����F�u���b�N���ǂ����̎擾(TRUE�œ��F)(OnlyColorBlock��TRUE�ŐF�u���b�N�݂̂Ŕ��肷��)
int Block::isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int OnlyColorBlock) {
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
	case BLOCK_TYPE_RED_ARROW_X:
	case BLOCK_TYPE_RED_ARROW_Y:
	case BLOCK_TYPE_RED_ARROW_XY:
	case BLOCK_TYPE_RED_ARROW_XY2:
		type1 = BLOCK_TYPE_RED;
		break;
	case BLOCK_TYPE_BLUE_ARROW_X:
	case BLOCK_TYPE_BLUE_ARROW_Y:
	case BLOCK_TYPE_BLUE_ARROW_XY:
	case BLOCK_TYPE_BLUE_ARROW_XY2:
		type1 = BLOCK_TYPE_BLUE;
		break;
	case BLOCK_TYPE_YELLOW_ARROW_X:
	case BLOCK_TYPE_YELLOW_ARROW_Y:
	case BLOCK_TYPE_YELLOW_ARROW_XY:
	case BLOCK_TYPE_YELLOW_ARROW_XY2:
		type1 = BLOCK_TYPE_YELLOW;
		break;
	case BLOCK_TYPE_GREEN_ARROW_X:
	case BLOCK_TYPE_GREEN_ARROW_Y:
	case BLOCK_TYPE_GREEN_ARROW_XY:
	case BLOCK_TYPE_GREEN_ARROW_XY2:
		type1 = BLOCK_TYPE_GREEN;
		break;
	case BLOCK_TYPE_PURPLE_ARROW_X:
	case BLOCK_TYPE_PURPLE_ARROW_Y:
	case BLOCK_TYPE_PURPLE_ARROW_XY:
	case BLOCK_TYPE_PURPLE_ARROW_XY2:
		type1 = BLOCK_TYPE_PURPLE;
		break;
	}
	switch (type2) {
	case BLOCK_TYPE_RED_ARROW_X:
	case BLOCK_TYPE_RED_ARROW_Y:
	case BLOCK_TYPE_RED_ARROW_XY:
	case BLOCK_TYPE_RED_ARROW_XY2:
		type2 = BLOCK_TYPE_RED;
		break;
	case BLOCK_TYPE_BLUE_ARROW_X:
	case BLOCK_TYPE_BLUE_ARROW_Y:
	case BLOCK_TYPE_BLUE_ARROW_XY:
	case BLOCK_TYPE_BLUE_ARROW_XY2:
		type2 = BLOCK_TYPE_BLUE;
		break;
	case BLOCK_TYPE_YELLOW_ARROW_X:
	case BLOCK_TYPE_YELLOW_ARROW_Y:
	case BLOCK_TYPE_YELLOW_ARROW_XY:
	case BLOCK_TYPE_YELLOW_ARROW_XY2:
		type2 = BLOCK_TYPE_YELLOW;
		break;
	case BLOCK_TYPE_GREEN_ARROW_X:
	case BLOCK_TYPE_GREEN_ARROW_Y:
	case BLOCK_TYPE_GREEN_ARROW_XY:
	case BLOCK_TYPE_GREEN_ARROW_XY2:
		type2 = BLOCK_TYPE_GREEN;
		break;
	case BLOCK_TYPE_PURPLE_ARROW_X:
	case BLOCK_TYPE_PURPLE_ARROW_Y:
	case BLOCK_TYPE_PURPLE_ARROW_XY:
	case BLOCK_TYPE_PURPLE_ARROW_XY2:
		type2 = BLOCK_TYPE_PURPLE;
		break;
	}
	//���F����
	if (type1 == type2)	return TRUE;

	return FALSE;
}

//�L�����ǂ����̎擾
int Block::isEnable() {
	if (color == BLOCK_TYPE_NO || color == BLOCK_TYPE_NUM) {
		//�����u���b�N
		return FALSE;
	}
	return TRUE;
}