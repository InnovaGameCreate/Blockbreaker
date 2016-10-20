#pragma once


#ifndef PHASECONTROLLER_H_
#error PhaseController.h��Include���Ă�������
#endif // !PHASECONTROLLER_H_



class Phase_GameMain : public PhaseController
{
public://�萔�Ƃ��̐錾
	static const int BLOCK_SIZE = 50;		//�u���b�N�̏c���̃s�N�Z���T�C�Y
	static const int BLOCK_WIDTHNUM = 14;	//�u���b�N�̉��̌�
	static const int BLOCK_HEIGHTNUM = 17;	//�u���b�N�̏c�̌�


	//�F
	enum COLOR {
		NO,
		RED,
		BLUE,
		YELLOW,
		GREEN,
		PURPLE
	};

private:
	struct field_info {
		int color;//�u���b�N�̐F
		int fall_flag;//���������ǂ����̃t���O
		int move_flag;//�ړ������ǂ����̃t���O
	};

	//�����u���b�N�̏��
	struct FallBlockInfo {
		FallBlockInfo() {
			Enable = FALSE;
			Counter = 0;
		}
		int Counter;			//�����u���b�N�̃J�E���^(��ɗL���ȕϐ��ł��I�I)(���̐��Ńu���b�N�����ł��Ă���̌o�߃t���[���A���̐��Ńu���b�N����������Ă���̎���)

		int Enable;			//���������ǂ���(TRUE�ŗ����u���b�N�L��)

		COLOR BlockID[3][3];	//�c��3���̃u���b�N�̈�Ƃ��ău���b�N�̈ʒu�����L�^����
		int PlaceX, PlaceY;		//�����u���b�N�̒��S�ʒu�̍��W(�z���1,1�̏ꏊ)
		int FallCount;			//�����J�E���g�_�E��(0�ŗ�������)
		
		//�L�[���͂ɂ���Ԃ̕ۑ��p
		int Key_FlagFirstFall;			//�����������[�h(TRUE�ŗL��)
		int Key_LRMove;				//���E�ړ�(-1���A0�ړ������A1�E�ړ�)
	};

	field_info field[10][16];


	int gameWindow;	//�Q�[����ʂ�`�悷��n���h��

	int Flag_Pause;			//�|�[�Y��Ԃ��ǂ���(�Q�[���̐i�s�����ׂĒ�~���܂�)(TRUE�Ń|�[�Y)
	int Flag_pauseRequest;	//�|�[�Y��Ԃ��ǂ����̃��N�G�X�g(�|�[�Y�����͂��ׂĂ̏����̍Ō�ōs������)

	
	FallBlockInfo fallBlockInfo;	//�����u���b�N�̏��

	void Draw();
	void Update();
	void GameMain_Key();

	int isFallBlock_MoveX(int MoveVal);		//�����u���b�N��X�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int isFallBlock_MoveY(int MoveVal);		//�����u���b�N��Y�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock();		//�����u���b�N�𐶐�����(�߂�l:������TRUE)

	/*�ݒ�n*/
	void PauseRequest(int b_Flag);		//�|�[�Y��Ԃ̃��N�G�X�g
	void Delete_FallBlock();			//�����u���b�N�̖�����

	/*�擾�n*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY);	//�u���b�N�̍��W�H����C���Q�[���̍��W�̍��[���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
	int	isPaused();					//�|�[�Y��Ԃ��ǂ����̎擾(TRUE�Ń|�[�Y)
	int isFallBlock_Falling();		//�����u���b�N�����������ǂ����̎擾(TRUE�ŗ�����)
	int isFallBlock_Enable();		//�����u���b�N���L�����ǂ����̎擾(TRUE�ŗL��)
	int getFallBlock_Interval();	//�����u���b�N�̑O��̗�������̃C���^�[�o���̎擾(�����u���b�N�����݂���Ƃ���0���Ԃ�܂�)
	COLOR getBlockColor(int X, int Y, COLOR OutGameBlock);	//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO�̃u���b�N�𔻒肵���Ƃ��̖߂�l)
};

