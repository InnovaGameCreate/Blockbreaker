#include "Tex_Block.h"


Tex_Block::Tex_Block() {
}


Tex_Block::~Tex_Block() {
}

//�`��̏�����
void Tex_Block::Init_Draw() {
	//�u���b�N�摜
	if ((BlockRED = LoadGraph(_T("Data/Blocks/Block_RED.png"))) == -1)								printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED.png)"));
	if ((BlockRED_ARROW_X = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_X.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_X.png)"));
	if ((BlockRED_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_Y.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_Y.png)"));
	if ((BlockRED_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_XY.png)"));
	if ((BlockRED_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY2.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RED_ARROW_XY2.png)"));

	if ((BlockBLUE = LoadGraph(_T("Data/Blocks/Block_BLUE.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE.png)"));
	if ((BlockBLUE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_X.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_X.png)"));
	if ((BlockBLUE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_Y.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_Y.png)"));
	if ((BlockBLUE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_XY.png)"));
	if ((BlockBLUE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY2.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLUE_ARROW_XY2.png)"));

	if ((BlockYELLOW = LoadGraph(_T("Data/Blocks/Block_YELLOW.png"))) == -1)						printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW.png)"));
	if ((BlockYELLOW_ARROW_X = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_X.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_X.png)"));
	if ((BlockYELLOW_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_Y.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_Y.png)"));
	if ((BlockYELLOW_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_XY.png)"));
	if ((BlockYELLOW_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY2.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_YELLOW_ARROW_XY2.png)"));

	if ((BlockGREEN = LoadGraph(_T("Data/Blocks/Block_GREEN.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN.png)"));
	if ((BlockGREEN_ARROW_X = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_X.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_X.png)"));
	if ((BlockGREEN_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_Y.png"))) == -1)			printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_Y.png)"));
	if ((BlockGREEN_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_XY.png)"));
	if ((BlockGREEN_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY2.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_GREEN_ARROW_XY2.png)"));

	if ((BlockPURPLE = LoadGraph(_T("Data/Blocks/Block_PURPLE.png"))) == -1)						printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE.png)"));
	if ((BlockPURPLE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_X.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_X.png)"));
	if ((BlockPURPLE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_Y.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_Y.png)"));
	if ((BlockPURPLE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY.png"))) == -1)		printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_XY.png)"));
	if ((BlockPURPLE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY2.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_PURPLE_ARROW_XY2.png)"));

	if ((BlockTREE = LoadGraph(_T("Data/Blocks/Block_TREE.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_TREE.png)"));
	if ((BlockRAINBOW = LoadGraph(_T("Data/Blocks/Block_RAINBOW.png"))) == -1)						printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_RAINBOW.png)"));
	if ((BlockBOMB = LoadGraph(_T("Data/Blocks/Block_BOMB.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BOMB.png)"));
	if ((Block2BOMB = LoadGraph(_T("Data/Blocks/Block_2BOMB.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_2BOMB.png)"));
	if ((BlockBOMB_Color = LoadGraph(_T("Data/Blocks/Block_BOMB_Color.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BOMB_Color.png)"));
	if ((BlockBLACK = LoadGraph(_T("Data/Blocks/Block_BLACK.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_BLACK.png)"));


	if ((BlockBack = LoadGraph(_T("Data/Blocks/Block_Back.png"))) == -1)							printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_Back.png)"));
	if ((BlockFireEffect = LoadGraph(_T("Data/Blocks/Block_FireEffect.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_FireEffect.png)"));
	if ((BlockFireEffect2 = LoadGraph(_T("Data/Blocks/Block_FireEffect2.png"))) == -1)				printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_FireEffect2.png)"));
	if ((BlockCenterEffect = LoadGraph(_T("Data/Blocks/Block_CENTER.png"))) == -1)					printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/Blocks/Block_CENTER.png)"));
	
	printLog_I(_T("�u���b�N�摜��ǂݍ��݂܂���"));

}

//�I������
void Tex_Block::Finalize_Draw() {
	DeleteGraph(BlockRED);
	DeleteGraph(BlockRED_ARROW_X);
	DeleteGraph(BlockRED_ARROW_Y);
	DeleteGraph(BlockRED_ARROW_XY);
	DeleteGraph(BlockRED_ARROW_XY2);
	DeleteGraph(BlockBLUE);
	DeleteGraph(BlockBLUE_ARROW_X);
	DeleteGraph(BlockBLUE_ARROW_Y);
	DeleteGraph(BlockBLUE_ARROW_XY);
	DeleteGraph(BlockBLUE_ARROW_XY2);
	DeleteGraph(BlockYELLOW);
	DeleteGraph(BlockYELLOW_ARROW_X);
	DeleteGraph(BlockYELLOW_ARROW_Y);
	DeleteGraph(BlockYELLOW_ARROW_XY);
	DeleteGraph(BlockYELLOW_ARROW_XY2);
	DeleteGraph(BlockGREEN);
	DeleteGraph(BlockGREEN_ARROW_X);
	DeleteGraph(BlockGREEN_ARROW_Y);
	DeleteGraph(BlockGREEN_ARROW_XY);
	DeleteGraph(BlockGREEN_ARROW_XY2);
	DeleteGraph(BlockPURPLE);
	DeleteGraph(BlockPURPLE_ARROW_X);
	DeleteGraph(BlockPURPLE_ARROW_Y);
	DeleteGraph(BlockPURPLE_ARROW_XY);
	DeleteGraph(BlockPURPLE_ARROW_XY2);
	DeleteGraph(BlockTREE);
	DeleteGraph(BlockBLACK);
	DeleteGraph(BlockRAINBOW);
	DeleteGraph(BlockFireEffect);
	DeleteGraph(BlockFireEffect2);
	DeleteGraph(BlockCenterEffect);
	DeleteGraph(BlockBOMB);
	DeleteGraph(Block2BOMB);
	DeleteGraph(BlockBOMB_Color);
	DeleteGraph(BlockBack);
}

//�u���b�N�^�C�v���e�N�X�`���n���h���̎擾
int Tex_Block::getTexture(BLOCK_TYPE type) {
	switch (type) {
	case BLOCK_TYPE_RED:	//�ԃu���b�N
		return BlockRED;
	case BLOCK_TYPE_BLUE:	//�u���b�N
		return BlockBLUE;
	case BLOCK_TYPE_GREEN:	//�΃u���b�N
		return BlockGREEN;
	case BLOCK_TYPE_PURPLE:	//���u���b�N
		return BlockPURPLE;
	case BLOCK_TYPE_RED_ARROW_X://��(���s���)
		return BlockRED_ARROW_X;
	case BLOCK_TYPE_RED_ARROW_Y://��(�������)
		return BlockRED_ARROW_Y;
	case BLOCK_TYPE_RED_ARROW_XY://��(�΂߉E��)
		return BlockRED_ARROW_XY;
	case BLOCK_TYPE_RED_ARROW_XY2://��(�΂߉E��)
		return BlockRED_ARROW_XY2;
	case BLOCK_TYPE_BLUE_ARROW_X://��(���s���)
		return BlockBLUE_ARROW_X;
	case BLOCK_TYPE_BLUE_ARROW_Y://��(�������)
		return BlockBLUE_ARROW_Y;
	case BLOCK_TYPE_BLUE_ARROW_XY://��(�΂߉E��)
		return BlockBLUE_ARROW_XY;
	case BLOCK_TYPE_BLUE_ARROW_XY2://��(�΂߉E��)
		return BlockBLUE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW_ARROW_X://��(���s���)
		return BlockYELLOW_ARROW_X;
	case BLOCK_TYPE_YELLOW_ARROW_Y://��(�������)
		return BlockYELLOW_ARROW_Y;
	case BLOCK_TYPE_YELLOW_ARROW_XY://��(�΂߉E��)
		return BlockYELLOW_ARROW_XY;
	case BLOCK_TYPE_YELLOW_ARROW_XY2://��(�΂߉E��)
		return BlockYELLOW_ARROW_XY2;
	case BLOCK_TYPE_GREEN_ARROW_X://��(���s���)
		return BlockGREEN_ARROW_X;
	case BLOCK_TYPE_GREEN_ARROW_Y://��(�������)
		return BlockGREEN_ARROW_Y;
	case BLOCK_TYPE_GREEN_ARROW_XY://��(�΂߉E��)
		return BlockGREEN_ARROW_XY;
	case BLOCK_TYPE_GREEN_ARROW_XY2://��(�΂߉E��)
		return BlockGREEN_ARROW_XY2;
	case BLOCK_TYPE_PURPLE_ARROW_X://��(���s���)
		return BlockPURPLE_ARROW_X;
	case BLOCK_TYPE_PURPLE_ARROW_Y://��(�������)
		return BlockPURPLE_ARROW_Y;
	case BLOCK_TYPE_PURPLE_ARROW_XY://��(�΂߉E��)
		return BlockPURPLE_ARROW_XY;
	case BLOCK_TYPE_PURPLE_ARROW_XY2://��(�΂߉E��)
		return BlockPURPLE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW:	//���F�u���b�N�`��
		return BlockYELLOW;
	case BLOCK_TYPE_TREE:	//���؃u���b�N
		return BlockTREE;
	case BLOCK_TYPE_BLACK:	//���u���b�N
		return BlockBLACK;
	case BLOCK_TYPE_RAINBOW://���F�u���b�N
		return BlockRAINBOW;
	case BLOCK_TYPE_BOM://���e�u���b�N
		return BlockBOMB;
	case BLOCK_TYPE_2BOM://2���e�u���b�N
		return Block2BOMB;
	case BLOCK_TYPE_BOM_Color://���F���e�u���b�N
		return BlockBOMB_Color;
	}
	//printLog_E(_T("�e�N�X�`���ԍ����擾�ł��܂���ł���(BLOCK_TYPE=%d)"), type);
	return 0;
}

//���G�t�F�N�g�擾
int Tex_Block::getFireEffect() {
	return BlockFireEffect;
}

//��2�G�t�F�N�g�擾
int Tex_Block::getFireEffect2() {
	return BlockFireEffect2;
}

//�u���b�N�̒����G�t�F�N�g�̎擾
int Tex_Block::getCenterEffect() {
	return BlockCenterEffect;
}

//�w�i�u���b�N�̎擾
int Tex_Block::getBack() {
	return BlockBack;
}
