#include "BlockChangeMotion.h"


BlockChangeMotion::BlockChangeMotion() {
	Type = BlockChangeMotionType_NO;
}


BlockChangeMotion::~BlockChangeMotion() {}

//�ω����[�V�����̐ݒ�(TRUE�Ő���)
int BlockChangeMotion::Create(BlockChangeMotionType mtype, BLOCK_TYPE from, BLOCK_TYPE to, int motionLength, int delay) {
	if (motionLength <= 0)									return FALSE;	//���������̐��̏ꍇ�����������Ȃ�

	if (Type != BlockChangeMotionType_NO) {
		printLog_C(_T("�u���b�N�ω����[�V�������㏑�����܂�"));
		Delete();
	}

	To = to;
	From = from;
	Length = motionLength;
	Count = -delay;

	Type = mtype;

	return TRUE;
}

//�ω����[�V�����̍폜
void BlockChangeMotion::Delete() {
	Type = BlockChangeMotionType_NO;
}

//�ω����[�V�������L�����ǂ����̎擾
int BlockChangeMotion::isEnable() {
	return ((getType() == BlockChangeMotionType_NO) ? FALSE : TRUE);
}

//�ω����[�V�����̎�ނ��擾����
BlockChangeMotionType BlockChangeMotion::getType() {
	return Type;
}

//�v�Z����
void BlockChangeMotion::Update() {
	if (!isEnable())	return;	//�ω����[�V�����������̏ꍇ�͉������Ȃ�

	//�ω����[�V����
	Count++;//�J�E���g�A�b�v
	if (Count > Length) {//���[�V��������
		Type = BlockChangeMotionType_NO;//�ω����[�V�����𖳌���
	}
}

//�ω����u���b�N�̎�ނ��擾����
BLOCK_TYPE BlockChangeMotion::getBlockType_From() {
	if (!isEnable())	return BLOCK_TYPE_NO;
	return From;
}

//�ω���u���b�N�̎�ނ��擾����
BLOCK_TYPE BlockChangeMotion::getBlockType_To() {
	if (!isEnable())	return BLOCK_TYPE_NO;
	return To;
}

//�ω��̊������擾����
double BlockChangeMotion::getChangeVal(){
	if (!isEnable())	return 0;
	if (Count < 0)		return 0;	//���̐��̎���0
	return Count / (double)Length;
}

//�J�E���g�̎擾
int BlockChangeMotion::getCount() {
	if (!isEnable())	return 0;
	return Count;
}