#include "Tex_Block.h"
#include "Block_Field.h"
#include "MainFunc.h"
//�t�B�[���h�p�̃u���b�N�N���X

Block_Field::Block_Field() {

}


Block_Field::~Block_Field() {

}

//������(�v�Z����)
void Block_Field::Init_Update() {
	Block::Init_Update();

	Restart();
}

//������(�`�揈��)
void Block_Field::Init_Draw() {

}

//�`��
void Block_Field::Draw() {

	switch (blockChangeMotion.getType()) {
	case BlockChangeMotionType_NO:
		//�ω����[�V���������̏ꍇ�͖���ɕ`�悷��
		Block::Draw();
		break;
	case BlockChangeMotionType_NOMAL:
		//���ʂ̕ω����[�V����(���[�V�����O�͕��ʂɕ`�悳��܂�)

		//�ω��O�̃u���b�N��`�悷��
		Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), 1);
		//�ω��ʂɉ����Ĕ������ŕ`�悷��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(blockChangeMotion.getChangeVal() * 255));
		Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_To()), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	case BlockChangeMotionType_EXPLOSION:
		//����(�V�F�[�_�Ɋ撣���Ă��炤)
		if (blockChangeMotion.getCount() < 0) {//���[�V�����O�͕��ʂɕ`��
			Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), 1);
		}
		else {
			ShaderBackGround_DeleteBlock(getDrawPlaceX(), getDrawPlaceY(), blockChangeMotion.getChangeVal()
				, phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), phase_GameMain.getTex_Block()->getFireEffect(), phase_GameMain.getTex_Block()->getFireEffect2());
		}
		break;
	case BlockChangeMotionType_SMALL:
		//�������Ȃ�(���[�V�����O�͕��ʂɕ`�悳��܂�)
		Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), (float)(1 - blockChangeMotion.getChangeVal()));

		break;
	}
}

//���X�^�[�g���̏�����
void Block_Field::Restart() {
	//��{�폜���s��
	Delete_Block();
	Delete_ChangeMotion();
	Delete_MoveMotion();
}

void Block_Field::Update_DrawData(double paddingX, double paddingY, int x, int y) {
	double plintX, pointY;

	//�ړ����[�V�������L���ȏꍇ�͈ړ����[�V�����̍��W���g�p����
	if (blockMoveMotion.isEnable()) {
		plintX = blockMoveMotion.getPointX();
		pointY = blockMoveMotion.getPointY();
	}
	else {
		//�ʏ펞
		Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &plintX, &pointY);
	}

	Block::Update_DrawData(plintX + paddingX, pointY + paddingY);
}

//�ω����[�V�����̍폜
void Block_Field::Delete_ChangeMotion() {
	blockChangeMotion.Delete();
}

//�ړ����[�V�����̍폜
void Block_Field::Delete_MoveMotion() {
	blockMoveMotion.Delete();
}

//�u���b�N�̍��W�H����C���Q�[���̍��W���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
void Block_Field::Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE + XVal*BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE + YVal*BLOCK_SIZE;
	}
}

//�ړ����[�V�����̃N���X�̃|�C���^���擾
BlockMoveMotion *Block_Field::getMoveMotion() {
	return &blockMoveMotion;
}

//�ω����[�V�����̃N���X�̃|�C���^���擾
BlockChangeMotion *Block_Field::getChangeMotion() {
	return &blockChangeMotion;
}

