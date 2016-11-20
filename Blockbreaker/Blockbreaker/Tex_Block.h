#pragma once
class Tex_Block
{
public:
	Tex_Block();
	~Tex_Block();
	void Init_Draw();			//�`��̏�����
	void Finalize_Draw();		//�I������

	int getTexture(BLOCK_TYPE type);	//�u���b�N�^�C�v���e�N�X�`���n���h���̎擾
	/*�u���b�N�^�C�v�̑��݂��Ȃ��e�N�X�`���̎擾*/
	int getFireEffect();				//���G�t�F�N�g�擾
	int getFireEffect2();				//��2�G�t�F�N�g�擾
	int getCenterEffect();				//�u���b�N�̒����G�t�F�N�g�̎擾
	int getBack();						//�w�i�u���b�N�̎擾
private:
	int BlockBack;				//�w�i�u���b�N(�u���b�N�̐F���Ȃ邾�����m�ɕ\�����邽�߂̔w�i�摜)
	int BlockRED;				//�ԃu���b�N
	int BlockRED_ARROW_X;		//�ԃu���b�N(���s���)
	int BlockRED_ARROW_Y;		//�ԃu���b�N(�������)
	int BlockRED_ARROW_XY;		//�ԃu���b�N(�΂߉E��)
	int BlockRED_ARROW_XY2;		//�ԃu���b�N(�΂߉E��)
	int BlockBLUE;				//�u���b�N
	int BlockBLUE_ARROW_X;		//�u���b�N(���s���)
	int BlockBLUE_ARROW_Y;		//�u���b�N(�������)
	int BlockBLUE_ARROW_XY;		//�u���b�N(�΂߉E��)
	int BlockBLUE_ARROW_XY2;	//�u���b�N(�΂߉E��)
	int BlockYELLOW;			//���F�u���b�N
	int BlockYELLOW_ARROW_X;	//���F�u���b�N(���s���)
	int BlockYELLOW_ARROW_Y;	//���F�u���b�N(�������)
	int BlockYELLOW_ARROW_XY;	//���F�u���b�N(�΂߉E��)
	int BlockYELLOW_ARROW_XY2;	//���F�u���b�N(�΂߉E��)
	int BlockGREEN;				//�΃u���b�N
	int BlockGREEN_ARROW_X;		//�΃u���b�N(���s���)
	int BlockGREEN_ARROW_Y;		//�΃u���b�N(�������)
	int BlockGREEN_ARROW_XY;	//�΃u���b�N(�΂߉E��)
	int BlockGREEN_ARROW_XY2;	//�΃u���b�N(�΂߉E��)
	int BlockPURPLE;			//���u���b�N
	int BlockPURPLE_ARROW_X;	//���u���b�N(���s���)
	int BlockPURPLE_ARROW_Y;	//���u���b�N(�������)
	int BlockPURPLE_ARROW_XY;	//���u���b�N(�΂߉E��)
	int BlockPURPLE_ARROW_XY2;	//���u���b�N(�΂߉E��)
	int BlockTREE;				//���؂̌`�u���b�N
	int BlockBLACK;				//���u���b�N
	int BlockRAINBOW;			//���F�u���b�N
	int BlockBOMB;				//���e�u���b�N
	int Block2BOMB;				//2���e�u���b�N
	int BlockBOMB_Color;		//���F���e�u���b�N
	int BlockFireEffect;		//���G�t�F�N�g�u���b�N
	int BlockFireEffect2;		//���G�t�F�N�g�u���b�N2(�Y)
	int BlockCenterEffect;		//��]�̒��S�ł��邱�Ƃ𕪂���悤�ɂ���G�t�F�N�g
};