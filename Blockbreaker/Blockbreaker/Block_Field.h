#pragma once
#include "Tex_Block.h"
#include "Block.h"
#include "BlockMoveMotion.h"
#include "BlockChangeMotion.h"

//�t�B�[���h�p�̃u���b�N�N���X

class Block_Field : public Block
{
public:
	Block_Field();
	~Block_Field();
	void Init_Update();	//������(�v�Z����)
	void Init_Draw();				//������(�`�揈��)
	void Restart();					//���X�^�[�g���̏�����

	void Draw();			//�`��

	void Update_DrawData(double paddingX, double paddingY, int x, int y);	//�`����̍X�V

	/*�폜�n*/
	void Delete_ChangeMotion();	//�ω����[�V�����̍폜
	void Delete_MoveMotion();	//�ړ����[�V�����̍폜


	BlockChangeMotion *getChangeMotion();	//�ω����[�V�����̃N���X�̃|�C���^���擾
	BlockMoveMotion *getMoveMotion();		//�ړ����[�V�����̃N���X�̃|�C���^���擾

	static void Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double * IngameX, double * IngameY);
private:




	BlockMoveMotion blockMoveMotion;		//�������[�V����
	BlockChangeMotion blockChangeMotion;	//�u���b�N�ω����[�V����



};