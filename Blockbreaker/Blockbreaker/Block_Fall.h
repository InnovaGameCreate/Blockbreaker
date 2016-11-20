#pragma once
#include "Define.h"
#include "Block.h"

//�����u���b�N�̃N���X

class Block_Fall
{
public:
	Block_Fall();
	~Block_Fall();

	void Draw();			//�����u���b�N�̕`�揈��
	void Draw_WaitLine();	//�����u���b�N�ҋ@��̕`��
	int Update();	//�����u���b�N�̌v�Z����(TRUE�ŗ������������u��)
	void Update_DrawData(double paddingX, double paddingY);	//�`����̍X�V
	void Key();		//�L�[����
	void Restart();	//���X�^�[�g(������)

	int Create_FallBlock();	//�����u���b�N�𐶐�����(�߂�l:������TRUE)
	int FallBlock_MoveX(int MoveVal, int CollisionFieldBlock = TRUE);		//�����u���b�N��X�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int getFallBlockVal_MoveX(int MoveVal, int CollisionFieldBlock = TRUE);	//�����u���b�N��X�������Ɉړ��\���ǂ����̎擾(|�ړ��o�����|<=MoveVal)(�܂�0�ňړ��s��)
	int FallBlock_MoveY(int MoveVal, int CollisionFieldBlock = TRUE);		//�����u���b�N��Y�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int FallBlock_Rotate(int RotaVal);										//�����u���b�N����]������(��]��1�Ŏ��v����90�x)(�߂�l�͎��ۂ̉�]��)

	int isEnable();		//�����u���b�N�����������ǂ����̎擾(���������L��)
	int getInterval();	//�����u���b�N�̃C���^�[�o���̎擾(�������̏ꍇ��-1���Ԃ�܂�)

private:
	//�����u���b�N�̑ҋ@��̏��
	struct FallBlockInfo_Wait {
		Block BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];	//�u���b�N�z�u
		int PlaceX, PlaceY;		//�����u���b�N�̒��S�ʒu�̍��W(�z���1,1�̏ꏊ)
		int Flag_Rotate;		//��]�\���ǂ���(TRUE�ŉ�]�\)
	};
	FallBlockInfo_Wait waitBlockinfo[3];	//�ҋ@�u���b�N�̏��


	//�����u���b�N�̏��
	int Counter;			//�����u���b�N�̃J�E���^(��ɗL���ȕϐ��ł��I�I)(���̐��Ńu���b�N�����ł��Ă���̌o�߃t���[���A���̐��Ńu���b�N����������Ă���̎���)

	int Enable;				//���������ǂ���(TRUE�ŗ����u���b�N�L��)
	Block BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];			//�����u���b�N�{�̂̏��
	Block BlockID_FallPoint[FALLBLOCK_SIZE*FALLBLOCK_SIZE];	//�����\�z�n�_�̃u���b�N���

	int PlaceX, PlaceY;		//�����u���b�N�̒��S�ʒu�̍��W(�z���1,1�̏ꏊ)
	int FallCount;			//�����J�E���g�_�E��(0�ŗ�������)
	int Flag_Rotate;		//��]�\���ǂ���(TRUE�ŉ�]�\)

	//�L�[���͂ɂ���Ԃ̕ۑ��p
	int Key_FlagFirstFall;	//�����������[�h(TRUE�ŗL��)
	int Key_LRMove;			//���E�ړ�(-1���A0�ړ������A1�E�ړ�)
	int Key_LRRota;			//��]�ړ�(-1�����v���A0��]�����A1���v���)

	void FallBlock_addField();												//�����u���b�N���t�B�[���h�u���b�N�ɕϊ�����(�܂�ݒu)
	void Delete_FallBlock();												//�����u���b�N�̖�����
	void Create_Wait_Block();												//�����u���b�N�̑ҋ@��̍쐬
};