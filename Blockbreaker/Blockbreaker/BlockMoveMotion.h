#pragma once
//�ړ����[�V�����̃f�[�^
class BlockMoveMotion
{
public:
	BlockMoveMotion();
	~BlockMoveMotion();

	int Create(int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);	//�ړ����[�V������V�K��������(TRUE����)
	void Delete();	//�ړ����[�V�����̍폜

	void Update();	//�v�Z����

	double getPointX();	//�ړ����[�V�����̍��W�ʒu�̎擾
	double getPointY();	//�ړ����[�V�����̍��W�ʒu�̎擾

	int isEnable();		//�ړ����[�V�������L�����ǂ����̎擾

	void getToPoint(int * toX, int * toY);	//�ړ���ɐݒ肵���l���擾����

	void Slide(int valX, int valY);	//���[�V�������̂����炷

private:
	int Enable;				//�ړ����[�V�������L�����ǂ���
	int FromX, FromY;		//�ړ������W
	int ToX, ToY;			//�ړ�����W
	int Count;				//�ړ��J�E���g(0�N�Z)
	double acceleration;	//�����x
	double MaxSpeed;		//�ō����x
	double ansX, ansY;		//�ړ����[�V�����ɂ��v�Z���ʂ̍��W�ʒu
};