#pragma once
#include "PhaseController.h"

#ifndef PHASECONTROLLER_H_
#error PhaseController.h��Include���Ă�������
#endif // !PHASECONTROLLER_H_



class Phase_GameMain : public PhaseController
{
public://�萔�Ƃ��̐錾
	static const int BLOCK_SIZE = 50;			//�u���b�N�̏c���̃s�N�Z���T�C�Y
	static const int BLOCK_WIDTHNUM = 14;		//���ۂ̃u���b�N�̉��̌�
	static const int BLOCK_HEIGHTNUM = 18;		//���ۂ̃u���b�N�̏c�̌�
	static const int BLOCK_PADDINGUP = 1;		//�`�悷��u���b�N�̊J�n�ʒu(��)
	static const int BLOCK_PADDINGDOWN = 0;		//�`�悷��u���b�N�̊J�n�ʒu(��)
	static const int BLOCK_PADDINGLEFT = 0;		//�`�悷��u���b�N�̊J�n�ʒu(��)
	static const int BLOCK_PADDINGRIGHT = 0;	//�`�悷��u���b�N�̊J�n�ʒu(�E)

	static const int  GAMEWINDOW_PADDINGX = 50;		//�Q�[����ʂ�X�����̃Y��
	static const int  GAMEWINDOW_PADDINGY = 55;		//�Q�[����ʂ�Y�����̃Y��
	static const int  GAMEWINDOW_WIDTH = (BLOCK_WIDTHNUM - (BLOCK_PADDINGLEFT + BLOCK_PADDINGRIGHT))*BLOCK_SIZE;		//�Q�[����ʂ̉���
	static const int  GAMEWINDOW_HEIGHT = (BLOCK_HEIGHTNUM - (BLOCK_PADDINGUP + BLOCK_PADDINGDOWN))*BLOCK_SIZE;		//�Q�[����ʂ̍���

	static const int FALLBLOCK_SIZE = 3;		//��������u���b�N�̑傫��
	static const int FALLBLOCK_CENTER = FALLBLOCK_SIZE/2;	//��������u���b�N�̒��S(�)�ʒu

	//�u���b�N�̎��
	enum BLOCK_TYPE {
		BLOCK_TYPE_NO,//�Ȃ�
		BLOCK_TYPE_RED,//��
		BLOCK_TYPE_BLUE,//��
		BLOCK_TYPE_YELLOW,//��
		BLOCK_TYPE_GREEN,//��
		BLOCK_TYPE_PURPLE,//��
		BLOCK_TYPE_TREE, //���؂̌`�̃u���b�N�i�אڂ���S�����̂ǂ������������Ƃ��Ɉꏏ�ɏ�����j
		BLOCK_TYPE_BLACK,//���F�̃u���b�N�F�u���܂ŐF���킩��Ȃ����������Ƃ��Ƀ����_���ŐF�����肷��
		BLOCK_TYPE_NOROUND,//�g�ň͂�ꂽ�u���b�N�i�񂹂Ȃ��j
		BLOCK_TYPE_RAINBOW,//���F�̃u���b�N(���̃u���b�N�Ɠ����F�ɂȂ�)
		BLOCK_TYPE_BOM,//���e(�ⓚ���p�Ŏ��͂̃u���b�N�j��)
		BLOCK_TYPE_DOWNMARK,//�����}�[�N�̃u���b�N(����2�i�ړ�������)
		BLOCK_TYPE_NUM		//�u���b�N�̎�ނ̐�(��ʊO�u���b�N)
	};

private:
	//�ړ����[�V�����̃f�[�^
	struct BlockMoveMotion {
		BlockMoveMotion() {
			Enable = FALSE;
		}
		int Enable;			//�ړ����[�V�������L�����ǂ���
		int FromX, FromY;	//�ړ������W
		int ToX, ToY;		//�ړ�����W
		int Count;			//�ړ��J�E���g(0�N�Z)
		double a;			//�����x
		double MaxSpeed;	//�ō����x
	};
	//�u���b�N�ω����[�V�����̃f�[�^
	struct BlockChangeMotion {
		BlockChangeMotion() {
			Enable = FALSE;
		}
		int Enable;			//�u���b�N�ω����[�V�������L�����ǂ���
		BLOCK_TYPE From;	//�u���b�N�ω����u���b�N
		BLOCK_TYPE To;		//�u���b�N�ω���u���b�N
		int Count;			//�u���b�N�ω��J�E���g(0�N�Z)
		int Length;			//�u���b�N�ω����[�V�������s������
	};
	struct field_info {
		BLOCK_TYPE color;//�u���b�N�̐F
		int fall_flag;//���������ǂ����̃t���O
		int move_flag;//�ړ������ǂ����̃t���O

		BlockMoveMotion blockMoveMotion;		//�������[�V����
		BlockChangeMotion blockChangeMotion;	//�u���b�N�ω����[�V����
	};

	struct Fallblock_Pack {
		BLOCK_TYPE BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];	//�c��FALLBLOCK_SIZE���̃u���b�N�̈�Ƃ��ău���b�N�̈ʒu�����L�^����
	};

	//�Q�[���T�C�N���̎���
	enum GameCycle {
		GameCycle_FALL,			//�u���b�N�̗���
		GameCycle_BeforeFALL,	//�u���b�N�̗����J�n�O
		GameCycle_Motion,		//�u���b�N�̃��[�V������
		GameCycle_BlockFunc,	//�u���b�N����(���E���F�u���b�N�̐F����)
		GameCycle_Delete,		//�u���b�N�̏�������
		GameCycle_NUM			//�Q�[���T�C�N���̌�(�ݒ薳��)
	};


	//�����u���b�N�̏��
	struct FallBlockInfo {
		FallBlockInfo() {
			Enable = FALSE;
			Counter = 0;
		}
		int Counter;			//�����u���b�N�̃J�E���^(��ɗL���ȕϐ��ł��I�I)(���̐��Ńu���b�N�����ł��Ă���̌o�߃t���[���A���̐��Ńu���b�N����������Ă���̎���)

		int Enable;				//���������ǂ���(TRUE�ŗ����u���b�N�L��)
		struct Fallblock_Pack fallblock;	//�����u���b�N�{�̂̏��
		
		int PlaceX, PlaceY;		//�����u���b�N�̒��S�ʒu�̍��W(�z���1,1�̏ꏊ)
		int FallCount;			//�����J�E���g�_�E��(0�ŗ�������)
		
		//�L�[���͂ɂ���Ԃ̕ۑ��p
		int Key_FlagFirstFall;	//�����������[�h(TRUE�ŗL��)
		int Key_LRMove;			//���E�ړ�(-1���A0�ړ������A1�E�ړ�)
		int Key_LRRota;			//��]�ړ�(-1�����v���A0��]�����A1���v���)
	};

	field_info field[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];


	int gameWindow;	//�Q�[����ʂ�`�悷��n���h��
	int Tex_BlockRED;		//�ԃu���b�N
	int Tex_BlockBLUE;		//�u���b�N
	int Tex_BlockYELLOW;	//���F�u���b�N
	int Tex_BlockGREEN;		//�΃u���b�N
	int Tex_BlockPURPLE;	//���u���b�N
	int Tex_BlockTREE;		//���؂̌`�u���b�N
	int Tex_BlockBLACK;		//���u���b�N
	int Tex_BlockRAINBOW;	//���F�u���b�N

	int BGM;				//BGM


	int Flag_Pause;			//�|�[�Y��Ԃ��ǂ���(�Q�[���̐i�s�����ׂĒ�~���܂�)(TRUE�Ń|�[�Y)
	int Flag_pauseRequest;	//�|�[�Y��Ԃ��ǂ����̃��N�G�X�g(�|�[�Y�����͂��ׂĂ̏����̍Ō�ōs������)

	
	FallBlockInfo fallBlockInfo;	//�����u���b�N�̏��
	FallBlockInfo waitBlockinfo[2];//�ҋ@�u���b�N�̏��

	GameCycle gameCycle;		//�Q�[���T�C�N��
	GameCycle NextgameCycle;	//���̃Q�[���T�C�N��(���[�V�����I����Ɉړ�����T�C�N��)

	RandomTable randomTable;	//�����e�[�u��

	void Draw();
	void DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type);	//�u���b�N��`�悷��(�C���Q�[�����W)
	void Update();
	int Update_FallBlock();			//�����u���b�N�̗�������(TRUE�ŗ����u���b�N�̗����I��)
	void GameMain_Key();

	void Block_Black_Func();		//�t�B�[���h�ɑ��݂��鍕�F�u���b�N�̐F�����肷��
	void Block_Rainbow_Func();		//�t�B�[���h�ɑ��݂�����F�u���b�N�̐F�����肷��

	int FallBlock_MoveX(int MoveVal);		//�����u���b�N��X�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int FallBlock_MoveY(int MoveVal);		//�����u���b�N��Y�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int FallBlock_Rotate(int RotaVal);		//�����u���b�N����]������(��]��1�Ŏ��v����90�x)(�߂�l�͎��ۂ̉�]��)
	void FallBlock_addField();				//�����u���b�N���t�B�[���h�u���b�N�ɕϊ�����(�܂�ݒu)
	void Block_Gravity(int InGameOnly = TRUE);	//�t�B�[���h�u���b�N���d�͂ŗ���������(TRUE�ŃQ�[����ʓ��̂�)
	int Block_Delete_Direct(int X, int Y, int CallGravityFlag = TRUE);		//�t�B�[���h�u���b�N���폜����(�d�͌v�Z���s�����ǂ����̃t���O)
	int Block_Delete_Type(int X, int Y, BLOCK_TYPE type, int CallGravityFlag = TRUE);	//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜
	int Block_Delete();							//�A������t�B�[���h�u���b�N���폜����(���łɂ��ז��u���b�N�̏������s��)(���������u���b�N�̐�)
	void SequenceCount(int x, int y, int ID, int n[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter);	//�אڂ��铯�F�u���b�N�̃J�E���g
	void Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);	//�t�B�[���h�̃u���b�N�Ƀ��[�V������ݒ肷��
	void Block_SetChangeMotion(int x, int y, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength);					//�t�B�[���h�̃u���b�N�ړ��Ƀ��[�V������ݒ肷��
	void setGameCycle(GameCycle gameCycle, GameCycle NextgameCycle = GameCycle_NUM);	//�Q�[���T�C�N����ݒ肷��(��2�����̓Q�[���T�C�N�������[�V�����̏ꍇ�̃��[�V�����I����Ɉړ�����T�C�N�������[�V�����ȊO�͖�������܂�)
	void Create_Wait_Block();//�ҋ@�u���b�N�̐���
	//BLOCK_TYPE Get_Block_Type(int h);
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock(struct Fallblock_Pack *fallblock_Pack);		//�����u���b�N�𐶐�����(�߂�l:������TRUE)
	int add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type);			//�t�B�[���h�Ƀu���b�N��ǉ�����

	/*�ݒ�n*/
	void PauseRequest(int b_Flag);		//�|�[�Y��Ԃ̃��N�G�X�g
	void Delete_FallBlock();			//�����u���b�N�̖�����

	/*�擾�n*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY);	//�u���b�N�̍��W�H����C���Q�[���̍��W�̍��[���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
	int	isPaused();					//�|�[�Y��Ԃ��ǂ����̎擾(TRUE�Ń|�[�Y)
	int isFallBlock_Falling();		//�����u���b�N�����������ǂ����̎擾(TRUE�ŗ�����)
	int isFallBlock_Enable();		//�����u���b�N���L�����ǂ����̎擾(TRUE�ŗL��)
	int getFallBlock_Interval();	//�����u���b�N�̑O��̗�������̃C���^�[�o���̎擾(�����u���b�N�����݂���Ƃ���0���Ԃ�܂�)
	BLOCK_TYPE getBlockColor(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE);	//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���TRUE����)(��4�����͎��ۂɕ`�悳���G���A�ȊO����ʊO�ɂ���ꍇTRUE,�u���b�N��񂪖����ʒu����ʊO�ɂ���ꍇ��FALSE��ݒ肷��)
	int isBlock_PlayMoveMotion();		//�ړ����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
	int isBlock_PlayChangeMotion();		//�ω����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
};

