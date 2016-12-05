#pragma once
#include "Enum.h"
#include "Tex_Block.h"

#include <string>
//�u���b�N�̐e�N���X

class Block
{
public:
	Block();
	~Block();
	void Init_Update();	//����������(�v�Z����)
	void Init_Draw();						//����������(�`�揈��)

	void Draw();															//�`�揈��
	void Draw(int grHandle, double scale);									//�`�揈��(�e�N�X�`���w��)
	static void Draw(double centerX, double centerY, int grHandle, double scale);	//�`�揈��(�ڍאݒ�2)

	void Update_DrawData(double drawPlaceX, double drawPlaceY);	//�`��ɕK�v�ȏ���ݒ肷��

	int addBlcok(BLOCK_TYPE type, int Override, BLOCK_TYPE *Before = NULL);	//�u���b�N��ݒu����

	int Delete_Block();				//�u���b�N�̍폜(TRUE�ō폜)

	BLOCK_TYPE getBlockType();		//���݂̃u���b�N�̎�ނ��擾����
	int getBlockTexture();			//���݂̃u���b�N�̃e�N�X�`���n���h�����擾����

	static int isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int OnlyColorBlock);
	int isEnable();		//�L�����ǂ����̎擾
protected:
	double getDrawPlaceX();		//�`��ʒuX���擾����
	double getDrawPlaceY();		//�`��ʒuY���擾����

private:

	BLOCK_TYPE color;				//�u���b�N�̎��
	double DrawPlaceX, DrawPlaceY;	//�`��ʒu[�C���Q�[�����W](�}���`���ƕ`��ʒu��������肪�������̂�)

};