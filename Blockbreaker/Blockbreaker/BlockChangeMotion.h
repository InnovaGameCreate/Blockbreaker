#pragma once
//�u���b�N�ω����[�V�����̃f�[�^
#include "Enum.h"


class BlockChangeMotion
{
public:
	BlockChangeMotion();
	~BlockChangeMotion();

	void Update();		//�v�Z����

	int Create(BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay);		//�ω����[�V�����̐ݒ�

	void Delete();		//�ω����[�V�����̍폜

	int isEnable();						//�ω����[�V�������L�����ǂ����̎擾
	BlockChangeMotionType getType();	//�ω����[�V�����̎�ނ��擾����
	BLOCK_TYPE getBlockType_From();		//�ω����u���b�N�̎�ނ��擾����
	BLOCK_TYPE getBlockType_To();		//�ω���u���b�N�̎�ނ��擾����
	double getChangeVal();				//�ω��̊������擾����
	int getCount();						//�J�E���g�̎擾
private:
	BlockChangeMotionType Type;	//�u���b�N�ω����[�V�����̎��
	BLOCK_TYPE From;			//�u���b�N�ω����u���b�N
	BLOCK_TYPE To;				//�u���b�N�ω���u���b�N
	int Count;					//�u���b�N�ω��J�E���g(0�N�Z)
	int Length;					//�u���b�N�ω����[�V�������s������
};

