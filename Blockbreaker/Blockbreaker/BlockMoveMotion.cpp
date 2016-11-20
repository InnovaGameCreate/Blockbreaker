#include "BlockMoveMotion.h"
#include "MainFunc.h"

//�ړ����[�V�����̃f�[�^

BlockMoveMotion::BlockMoveMotion() {
	Delete();
}


BlockMoveMotion::~BlockMoveMotion() {

}

//�ړ����[�V������V�K��������(TRUE����)
int BlockMoveMotion::Create(int fromX, int fromY, int toX, int toY, double a, double maxSpeed) {
	if (fromX == toX && fromY == toY)	return FALSE;	//�ړ������̏ꍇ�����������Ȃ�
	if (a <= 0)							return FALSE;	//�����x�����̐��̏ꍇ�����������Ȃ�
	if (maxSpeed <= 0)					return FALSE;	//�ő呬�x�����̐��̏ꍇ�����������Ȃ�

	if (isEnable()) {
		printLog_C(_T("�u���b�N�̈ړ����[�V�������㏑�����܂�"));
		Delete();	//��������폜����
	}

	ToX = toX;
	ToY = toY;
	FromX = fromX;
	FromY = fromY;
	acceleration = a;
	MaxSpeed = maxSpeed;
	Count = 0;

	Enable = TRUE;


	return TRUE;
}

//�ړ����[�V�����̍폜
void BlockMoveMotion::Delete() {
	Enable = FALSE;
}

//�v�Z����(�ړ���FALSE)
void BlockMoveMotion::Update() {
	//�ړ����[�V����
	if (Enable) {
		Count++;//�J�E���g�A�b�v
		//�ړ����鋗���̌v�Z
		double fX, fY, tX, tY;
		Block_Field::Convert_Ingame_FromBlock(FromX, FromY, 0.5, 0.5, &fX, &fY);
		Block_Field::Convert_Ingame_FromBlock(ToX, ToY, 0.5, 0.5, &tX, &tY);
		double MD = getMoveDistance(acceleration, MaxSpeed, Count);	//���݂̈ړ�����
		double FMD = getDistance(fX, fY, tX, tY);			//�ŏI�I�Ȉړ�����
		double Rota = getRotation(FromX, FromY, ToX, ToY);	//�p�x�̌v�Z
		//��̌v�Z���ʂ��A�`����W�̌v�Z
		ansX = fX + MD * cos(deg_to_rad(Rota));
		ansY = fY + MD * sin(deg_to_rad(Rota));
		if (FMD <= MD) {//�ړ�����
			Enable = FALSE;//�ړ��𖳌���
		}
	}
}

//�ړ����[�V�����̍��W�ʒu�̎擾
double BlockMoveMotion::getPointX() {
	if (isEnable())	return ansX;
	else			return 0;
}

//�ړ����[�V�����̍��W�ʒu�̎擾
double BlockMoveMotion::getPointY() {
	if (isEnable())	return ansY;
	else			return 0;
}

//�ړ����[�V�������L�����ǂ����̎擾
int BlockMoveMotion::isEnable() {
	return ((Enable) ? TRUE : FALSE);
}

//�ړ���ɐݒ肵���l���擾����
void BlockMoveMotion::getToPoint(int *toX, int *toY) {
	if (toX != NULL)	*toX = ToX;
	if (toY != NULL)	*toY = ToY;
}

//���[�V�������̂����炷
void BlockMoveMotion::Slide(int valX, int valY) {
	if (isEnable()) {//�ړ����[�V�������L���ȏꍇ�͈ړ����[�V�����ɕ␳��������
		FromX += valX;
		FromY += valY;
		ToX += valX;
		ToY += valY;
	}
}