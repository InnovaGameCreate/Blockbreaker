#pragma once
#include "SelectItem.h"
#include "Define.h"

class Phase_GameMain : public PhaseController
{
public://�萔�Ƃ��̐錾
	static const int BLOCK_SIZE = 40;			//�u���b�N�̏c���̃s�N�Z���T�C�Y
	static const int BLOCK_WIDTHNUM = 11;		//���ۂ̃u���b�N�̉��̌�
	static const int BLOCK_HEIGHTNUM = 24;		//���ۂ̃u���b�N�̏c�̌�
	static const int BLOCK_PADDINGUP = 1;		//�`�悷��u���b�N�̊J�n�ʒu(��)
	static const int BLOCK_PADDINGDOWN = 1;		//�`�悷��u���b�N�̊J�n�ʒu(��)
	static const int BLOCK_PADDINGLEFT = 0;		//�`�悷��u���b�N�̊J�n�ʒu(��)
	static const int BLOCK_PADDINGRIGHT = 0;	//�`�悷��u���b�N�̊J�n�ʒu(�E)
	static const int BLOCK_WIDTHNUM_INGAME = BLOCK_WIDTHNUM - (BLOCK_PADDINGLEFT + BLOCK_PADDINGRIGHT);		//��ʓ��̉��̃u���b�N�̌�
	static const int BLOCK_HEIGHTNUM_INGAME = BLOCK_HEIGHTNUM - (BLOCK_PADDINGUP + BLOCK_PADDINGDOWN);		//��ʓ��̏c�̃u���b�N�̌�

	static const int GAMEWINDOW_PADDINGX = 70;	//�Q�[����ʂ�X�����̃Y��
	static const int GAMEWINDOW_PADDINGY = 40;	//�Q�[����ʂ�Y�����̃Y��
	static const int GAMEWINDOW_WIDTH = BLOCK_WIDTHNUM_INGAME*BLOCK_SIZE;	//�Q�[����ʂ̉���
	static const int GAMEWINDOW_HEIGHT = BLOCK_HEIGHTNUM_INGAME*BLOCK_SIZE;	//�Q�[����ʂ̍���

	static const int FALLBLOCK_SIZE = 3;		//��������u���b�N�̑傫��
	static const int GAMEOVER_BORDER = 4;		//�Q�[���I�[�o�[�ɂ���ꏊ
	static const int FALLBLOCK_CENTER = FALLBLOCK_SIZE/2;	//��������u���b�N�̒��S(�)�ʒu
	static const int BLOCK_DELETE_LEN = 3;//�폜���邽�߂ɕK�v�ȗאڂ���u���b�N�̌�

	//�u���b�N�̎��
	enum BLOCK_TYPE {
		BLOCK_TYPE_NO,//�Ȃ�
		BLOCK_TYPE_RED,//��
		BLOCK_TYPE_BLUE,//��
		BLOCK_TYPE_YELLOW,//��
		BLOCK_TYPE_GREEN,//��
		BLOCK_TYPE_PURPLE,//��
		//�����������u���b�N��
		BLOCK_TYPE_RED_ARROW_X,		//��(���s���)
		BLOCK_TYPE_RED_ARROW_Y,		//��(�������)
		BLOCK_TYPE_RED_ARROW_XY,	//��(�΂߉E��)
		BLOCK_TYPE_RED_ARROW_XY2,	//��(�΂߉E��)
		BLOCK_TYPE_BLUE_ARROW_X,	//��(���s���)
		BLOCK_TYPE_BLUE_ARROW_Y,	//��(�������)
		BLOCK_TYPE_BLUE_ARROW_XY,	//��(�΂߉E��)
		BLOCK_TYPE_BLUE_ARROW_XY2,	//��(�΂߉E��)
		BLOCK_TYPE_YELLOW_ARROW_X,	//��(���s���)
		BLOCK_TYPE_YELLOW_ARROW_Y,	//��(�������)
		BLOCK_TYPE_YELLOW_ARROW_XY,	//��(�΂߉E��)
		BLOCK_TYPE_YELLOW_ARROW_XY2,//��(�΂߉E��)
		BLOCK_TYPE_GREEN_ARROW_X,	//��(���s���)
		BLOCK_TYPE_GREEN_ARROW_Y,	//��(�������)
		BLOCK_TYPE_GREEN_ARROW_XY,	//��(�΂߉E��)
		BLOCK_TYPE_GREEN_ARROW_XY2,	//��(�΂߉E��)
		BLOCK_TYPE_PURPLE_ARROW_X,	//��(���s���)
		BLOCK_TYPE_PURPLE_ARROW_Y,	//��(�������)
		BLOCK_TYPE_PURPLE_ARROW_XY,	//��(�������)
		BLOCK_TYPE_PURPLE_ARROW_XY2,//��(�������)
		BLOCK_TYPE_TREE, //���؂̌`�̃u���b�N�i�אڂ���S�����̂ǂ������������Ƃ��Ɉꏏ�ɏ�����j
		BLOCK_TYPE_BLACK,//���F�̃u���b�N�F�u���܂ŐF���킩��Ȃ����������Ƃ��Ƀ����_���ŐF�����肷��
		BLOCK_TYPE_NOROUND,//�g�ň͂�ꂽ�u���b�N�i�񂹂Ȃ��j
		BLOCK_TYPE_RAINBOW,//���F�̃u���b�N(���̃u���b�N�Ɠ����F�ɂȂ�)
		BLOCK_TYPE_BOM,//���e(�ⓚ���p�Ŏ��͂̃u���b�N�j��)
		BLOCK_TYPE_NUM		//�u���b�N�̎�ނ̐�(��ʊO�u���b�N)
	};

	//�|�[�Y�̎��
	enum PauseMode {
		PauseMode_NO,		//�|�[�Y��ԂɂȂ��Ă��Ȃ�(�ʏ�)
		PauseMode_NOMAL,	//�ʏ�̔��C�[�Y(esc�Ń|�[�Y������)
		PauseMode_GameOver,	//�Q�[���I�[�o�[
		PauseMode_NUM		//��(���N�G�X�g����)
	};

	//�u���b�N�ω����[�V�����̎��
	enum BlockChangeMotionType {
		BlockChangeMotionType_NO,		//���[�V��������
		BlockChangeMotionType_NOMAL,	//�ʏ�(from����to��)
		BlockChangeMotionType_EXPLOSION,//����(����)
		BlockChangeMotionType_SMALL,	//�������Ȃ��ď�����
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
			Type = BlockChangeMotionType_NO;
		}
		BlockChangeMotionType Type;	//�u���b�N�ω����[�V�����̎��
		BLOCK_TYPE From;			//�u���b�N�ω����u���b�N
		BLOCK_TYPE To;				//�u���b�N�ω���u���b�N
		int Count;					//�u���b�N�ω��J�E���g(0�N�Z)
		int Length;					//�u���b�N�ω����[�V�������s������
	};
	struct field_info {
		BLOCK_TYPE color;//�u���b�N�̐F
		int fall_flag;//���������ǂ����̃t���O
		int move_flag;//�ړ������ǂ����̃t���O


		double DrawPlaceX, DrawPlaceY;			//�`��ʒu[�C���Q�[�����W](�}���`���ƕ`��ʒu��������肪�������̂�)
		BlockMoveMotion blockMoveMotion;		//�������[�V����
		BlockChangeMotion blockChangeMotion;	//�u���b�N�ω����[�V����
	};

	struct Fallblock_Pack {
		BLOCK_TYPE BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];	//�c��FALLBLOCK_SIZE���̃u���b�N�̈�Ƃ��ău���b�N�̈ʒu�����L�^����
	};

	//�X�R�A�֌W
	struct Score {
		/*
		0:�u���b�N�̏����ɂ��X�R�A
		1:���̑�
		*/
		int score[2];
		Score() { init(); }
		//�X�R�A�̏�����
		void init() {
			for (auto &data: score) {
				data = 0;
			}
		}
		//���v�X�R�A�̎擾
		int getScore() {
			int sum = 0;
			for (auto data : score) {
				sum += data;
			}
			return sum;
		}
		//�X�R�A�̉��Z
		void addScore(int No, int Score) {
			if (No < 0 || ARRAY_LENGTH(score) <= No)	return;
			score[No] += Score;
		}
	};

	//�Q�[���T�C�N���̎���
	enum GameCycle {
		GameCycle_FALL,			//�u���b�N�̗���
		GameCycle_BeforeFALL,	//�u���b�N�̗����J�n�O
		GameCycle_Update,		//�u���b�N�̌v�Z���[�v
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
		int Flag_Rotate;		//��]�\���ǂ���(TRUE�ŉ�]�\)
		
		//�L�[���͂ɂ���Ԃ̕ۑ��p
		int Key_FlagFirstFall;	//�����������[�h(TRUE�ŗL��)
		int Key_LRMove;			//���E�ړ�(-1���A0�ړ������A1�E�ړ�)
		int Key_LRRota;			//��]�ړ�(-1�����v���A0��]�����A1���v���)
	};

	field_info field[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];

	SelectItem<Phase_GameMain> pauseMenu = SelectItem<Phase_GameMain>(WINDOW_WIDTH/2, 600);	//�|�[�Y���j���[�̍���

	//�u���b�N�̌v�Z���[�v�Ŏg�p����ϐ�
	int Loop_No;			//�v�Z���[�v�̂ǂ̏��������Ă��邩(-1�Ōv�Z���[�v���g�p)
	GameCycle Loop_Next;	//�v�Z���[�v��Ɉڍs����Q�[���T�C�N��

	//�u���b�N�̑S�̈ړ��Ŏg�p����ϐ�
	BlockMoveMotion Block_AllMovedata;

	//�t���C�e�L�X�g�\���N���X
	FlyText flyText;

	//�X�R�A
	Score score;

	int ChainCount = 0;	//�A���J�E���g


	int gameWindow;	//�Q�[����ʂ�`�悷��n���h��
	int Tex_BlockRED;				//�ԃu���b�N
	int Tex_BlockRED_ARROW_X;		//�ԃu���b�N(���s���)
	int Tex_BlockRED_ARROW_Y;		//�ԃu���b�N(�������)
	int Tex_BlockRED_ARROW_XY;		//�ԃu���b�N(�΂߉E��)
	int Tex_BlockRED_ARROW_XY2;		//�ԃu���b�N(�΂߉E��)
	int Tex_BlockBLUE;				//�u���b�N
	int Tex_BlockBLUE_ARROW_X;		//�u���b�N(���s���)
	int Tex_BlockBLUE_ARROW_Y;		//�u���b�N(�������)
	int Tex_BlockBLUE_ARROW_XY;		//�u���b�N(�΂߉E��)
	int Tex_BlockBLUE_ARROW_XY2;	//�u���b�N(�΂߉E��)
	int Tex_BlockYELLOW;			//���F�u���b�N
	int Tex_BlockYELLOW_ARROW_X;	//���F�u���b�N(���s���)
	int Tex_BlockYELLOW_ARROW_Y;	//���F�u���b�N(�������)
	int Tex_BlockYELLOW_ARROW_XY;	//���F�u���b�N(�΂߉E��)
	int Tex_BlockYELLOW_ARROW_XY2;	//���F�u���b�N(�΂߉E��)
	int Tex_BlockGREEN;				//�΃u���b�N
	int Tex_BlockGREEN_ARROW_X;		//�΃u���b�N(���s���)
	int Tex_BlockGREEN_ARROW_Y;		//�΃u���b�N(�������)
	int Tex_BlockGREEN_ARROW_XY;	//�΃u���b�N(�΂߉E��)
	int Tex_BlockGREEN_ARROW_XY2;	//�΃u���b�N(�΂߉E��)
	int Tex_BlockPURPLE;			//���u���b�N
	int Tex_BlockPURPLE_ARROW_X;	//���u���b�N(���s���)
	int Tex_BlockPURPLE_ARROW_Y;	//���u���b�N(�������)
	int Tex_BlockPURPLE_ARROW_XY;	//���u���b�N(�΂߉E��)
	int Tex_BlockPURPLE_ARROW_XY2;	//���u���b�N(�΂߉E��)
	int Tex_BlockTREE;				//���؂̌`�u���b�N
	int Tex_BlockBLACK;				//���u���b�N
	int Tex_BlockRAINBOW;			//���F�u���b�N
	int Tex_BlockBOMB;				//���e�u���b�N
	int Tex_BlockFireEffect;		//���G�t�F�N�g�u���b�N
	int Tex_BlockFireEffect2;		//���G�t�F�N�g�u���b�N�̃}�X�N�摜
	int haikei;				//�w�i

	int BGM;				//BGM


	PauseMode Flag_Pause;				//�|�[�Y��Ԃ��ǂ���(�Q�[���̐i�s�����ׂĒ�~���܂�)
	PauseMode Flag_pauseRequest;		//�|�[�Y��Ԃ��ǂ����̃��N�G�X�g(�|�[�Y�����͂��ׂĂ̏����̍Ō�ōs������)

	
	FallBlockInfo fallBlockInfo;	//�����u���b�N�̏��
	FallBlockInfo waitBlockinfo[2];//�ҋ@�u���b�N�̏��

	GameCycle gameCycle;		//�Q�[���T�C�N��
	int gameCycleFirstCallFlag;	//�Q�[���T�C�N�����ύX���ꂽ�Ƃ���TRUE����������

	RandomTable randomTable;	//�����e�[�u��

	int Count_PlayTime;		//�o�߃t���[����(�|�[�Y�A�ꎞ��~�ȂǂŃJ�E���g�A�b�v���ꎞ��~����)
	int Count_Pause;		//�|�[�Y���̃J�E���^
	int Count_Turn;			//�o�߃^�[�����i�u���b�N�������ɉ��Z�j

	void Draw();
	void DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type, double Scale = 1);	//�u���b�N��`�悷��(�C���Q�[�����W)
	int Update_FieldBlock();		//�t�B�[���h�u���b�N�ׁ̍X�Ƃ����v�Z���[�v
	int Update_MoveMotion();		//�ړ����[�V�����̍X�V(�ړ����[�V�������s��ꂽ�Ƃ���TRUE)
	int Update_ChangeMotion();		//�ω����[�V�����̍X�V(�ω����[�V�������s��ꂽ�Ƃ���TRUE)
	void Update_Counter();			//�J�E���^�̃J�E���g�A�b�v
	void Update();
	void Update_Final();			//Update��ɌĂ΂��
	int Update_FallBlock();			//�����u���b�N�̗�������(TRUE�ŗ����u���b�N�̗����I��)
	void GameMain_Key();

	void Block_Black_Func();		//�t�B�[���h�ɑ��݂��鍕�F�u���b�N�̐F�����肷��
	void Block_Rainbow_Func();		//�t�B�[���h�ɑ��݂�����F�u���b�N�̐F�����肷��
	void Block_BOMB_Func();			//�t�B�[���h�ɑ��݂��锚�e�u���b�N�𔚔j����

	int FallBlock_MoveX(int MoveVal, int CollisionFieldBlock = TRUE);		//�����u���b�N��X�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int FallBlock_MoveY(int MoveVal, int CollisionFieldBlock = TRUE);		//�����u���b�N��Y�������Ɉړ�(�߂�l�͎��ۂ̈ړ���)
	int FallBlock_Rotate(int RotaVal);		//�����u���b�N����]������(��]��1�Ŏ��v����90�x)(�߂�l�͎��ۂ̉�]��)
	void FallBlock_addField();				//�����u���b�N���t�B�[���h�u���b�N�ɕϊ�����(�܂�ݒu)
	void Block_Gravity(int InGameOnly = TRUE);	//�t�B�[���h�u���b�N���d�͂ŗ���������(TRUE�ŃQ�[����ʓ��̂�)
	int Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int MotionLengh = 40);		//�t�B�[���h�u���b�N���폜����
	int Block_Delete_Type(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int MotionLengh = 40);	//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜
	int Block_Delete();							//�A������t�B�[���h�u���b�N���폜����(���łɏ����ɂ���Ĕ���������ʂ���������)(���������u���b�N�̐�)
	int Block_Delete_OutScreen();//��ʊO�̃u���b�N�����ׂč폜����(���������u���b�N�̐�)
	void under_Block();							//������u���b�N���킢�Ă���
	void SequenceCount(int x, int y, int ID, int n[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter);	//�אڂ��铯�F�u���b�N�̃J�E���g
	int isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int FirstFlag = FALSE);		//�w�肵��2�̃u���b�N�����F�u���b�N���ǂ����̎擾(TRUE�œ��F)(FirstFlag��TRUE�Ŋȗ��v�Z���܂�)
	void Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);					//�t�B�[���h�̃u���b�N�Ɉړ����[�V������ݒ肷��
	void Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength);	//�t�B�[���h�̃u���b�N�ɕω����[�V������ݒ肷��(����P�̂Ŏg�p���Ď��̂��Ă��m��܂���)
	void Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength);				//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��
	void Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength);			//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��(�ω����w��)
	void Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength);							//�t�B�[���h�̃u���b�N�ɕω����[�V����(����)��ݒ肷��
	void Block_SetChangeMotion_SMALL(int x, int y, int MotionLength);								//�t�B�[���h�̃u���b�N�ɕω����[�V����(�������Ȃ��ď�����)��ݒ肷��
	void setGameCycle(GameCycle gameCycle);			//�Q�[���T�C�N����ݒ肷��
	void UpdateBlockRequest(GameCycle Next);		//�u���b�N�����X�V����悤�Ƀ��N�G�X�g
	void Block_AllMoveRequest(int X, int Y);		//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ����郊�N�G�X�g������(�Q�[�����ꎞ��~���ē������܂�)
	void Block_AllMove(int X, int Y);				//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ�����(��ʊO�ɏo�Ă��܂��u���b�N�͏��ł��܂�)
	int JudgeGameOver();							//�Q�[���I�[�o�[�ɂȂ��Ă��邩�ǂ����̊m�F
	int getBlockTexture(BLOCK_TYPE type);			//�u���b�N�^�C�v���e�N�X�`���n���h���̎擾
	void Create_Wait_Block();//�ҋ@�u���b�N�̐���
	void pauseMenu_Cannel();						//�|�[�Y�����{�^���������ꂽ�Ƃ�
	void pauseMenu_ReStart();						//��蒼���{�^���������ꂽ�Ƃ�
	void pauseMenu_End();							//�Q�[���I���{�^���������ꂽ�Ƃ�
	//BLOCK_TYPE Get_Block_Type(int h);
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock(struct Fallblock_Pack *fallblock_Pack);		//�����u���b�N�𐶐�����(�߂�l:������TRUE)
	int add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int Override = FALSE, int OutScreen = FALSE, BlockChangeMotionType MotionType = BlockChangeMotionType_NO, int MotionLengh = 40, BLOCK_TYPE *Before = NULL);			//�t�B�[���h�Ƀu���b�N��ǉ�(�폜)����(�ړ����[�V�����͍폜����܂�)

	/*�ݒ�n*/
	void PauseRequest(PauseMode pauseMode);	//�|�[�Y��Ԃ̃��N�G�X�g
	void Delete_FallBlock();				//�����u���b�N�̖�����

	/*�擾�n*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double * IngameX, double * IngameY);	//�u���b�N�̍��W�H����C���Q�[���̍��W�̍��[���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
	PauseMode getPauseMode();		//�|�[�Y��Ԃ̎擾
	int isFallBlock_Falling();		//�����u���b�N�����������ǂ����̎擾(TRUE�ŗ�����)
	int isFallBlock_Enable();		//�����u���b�N���L�����ǂ����̎擾(TRUE�ŗL��)
	int getFallBlock_Interval();	//�����u���b�N�̑O��̗�������̃C���^�[�o���̎擾(�����u���b�N�����݂���Ƃ���0���Ԃ�܂�)
	BLOCK_TYPE getBlockColor(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE);	//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���TRUE����)(��4�����͎��ۂɕ`�悳���G���A�ȊO����ʊO�ɂ���ꍇTRUE,�u���b�N��񂪖����ʒu����ʊO�ɂ���ꍇ��FALSE��ݒ肷��)
	int isBlock_PlayMoveMotion();		//�ړ����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
	int isBlock_PlayChangeMotion();		//�ω����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
	void Restart();						//���X�^�[�g
	void RestoreGraphCallback();		//�t���X�N���[���ɕ��A���ɌĂ΂��
};

