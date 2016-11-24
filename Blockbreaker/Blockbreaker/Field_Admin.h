#pragma once
#include "Define.h"
#include "Block_Field.h"

//�t�B�[���h�u���b�N�����N���X
class Field_Admin
{
public:
	void Init_Draw();	//������(�`�揈��)
	void Init_Update();	//������(�v�Z����)
	void Restart();		//���X�^�[�g����

	/*��{����*/
	void Draw_Block();	//�u���b�N�`�揈��
	void Draw_Lay();	//���[�U�[�G�t�F�N�g�`�揈��
	void key();			//�L�[����
	int Update_MoveMotion();	//�ړ����[�V�����̍X�V(�ړ����[�V�������s��ꂽ�Ƃ���TRUE)
	int Update_ChangeMotion();	//�ω����[�V�����̍X�V(�ω����[�V�������s��ꂽ�Ƃ���TRUE)
	int Update_AllMove();		//�S�̈ړ��̍X�V(TRUE�S�̈ړ��̍X�V���s����)
	void Update_Lay();			//�j������G�t�F�N�g�̍X�V
	void Update_DrawData();		//�`����̍X�V

	void ChainCount_Reset();	//�u���b�N�̃`�F�C���������Z�b�g����

	/*�u���b�N�ɕύX��������n*/
	int add_FieldBlock(int X, int Y, BLOCK_TYPE type, int Override = FALSE, int OutScreen = FALSE, BLOCK_TYPE *Before = NULL, int UseVirtualField = FALSE);	//�t�B�[���h�Ƀu���b�N��ݒu����
	void add_Under();						//������u���b�N���킢�Ă���
	void Gravity(int InGameOnly = TRUE);	//�t�B�[���h�u���b�N���d�͂ŗ���������
	void Delete_Lay();						//�j������Ńu���b�N��j�󂷂�
	int Delete_OutScreen();					//��ʊO�̃u���b�N�����ׂč폜����(���������u���b�N�̐�)
	int Delete_Join(const int Len = BLOCK_DELETE_LEN, int Flag_Event = TRUE);//�A������t�B�[���h�u���b�N���폜����(���łɏ����ɂ���Ĕ���������ʂ���������)(���������u���b�N�̐�)
	void Func_Black();						//�t�B�[���h�ɑ��݂��鍕�F�u���b�N�̐F�����肷��
	void Func_Rainbow();					//�t�B�[���h�ɑ��݂�����F�u���b�N�̐F�����肷��(�����珇��)
	void Func_BOMB();						//�t�B�[���h�ɑ��݂��锚�e�u���b�N�𔚔j����
	void Func_2BOMB();						//�t�B�[���h�ɑ��݂���2���e�u���b�N�𔚔j����
	void Func_BOMBColor();					//�t�B�[���h�ɑ��݂��铯�F���e�u���b�N�𔚔j����

	BlockMoveMotion * getBlockMoveMotion();	//�u���b�N�S�̈ړ��N���X�̃|�C���^���擾
	void getField_Padding(double * Field_PaddingX, double * Field_PaddingY);	//�t�B�[���h�S�̂̃Y�����擾����
	int isPlayingMoveMotion();				//�ړ����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
	int isPlayingChangeMotion();			//�ω����[�V�������̃u���b�N�����݂��邩�ǂ����̎擾(TRUE����)
	BLOCK_TYPE getBlockType(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE, int UseVirtualField = FALSE);	//�w�肵�����W�̃u���b�N�̎擾(��3�����͉�ʊO���u���b�N�Ƃ��Ĕ��肷�邩�ǂ���TRUE����)(��4�����͎��ۂɕ`�悳���G���A�ȊO����ʊO�ɂ���ꍇTRUE,�u���b�N��񂪖����ʒu����ʊO�ɂ���ꍇ��FALSE��ݒ肷��)
	int getUpperX(int x);					//�w�肵��X���W�̈�ԏ�̃u���b�N��Y���W���擾����(�����Ă�����W�݂̂Ŕ��f)
	int getmaxUpperX();						//�ő�̍����̃u���b�N��Y���W���擾����
	int getChain();							//���݂̃`�F�C�������擾����
private:
	Block_Field field[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];			//���ۂ̃t�B�[���h���
	Block_Field Virtualfield[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];	//�v�Z��̃t�B�[���h���UseVirtualField=TRUE�Ŏg�p

	BlockMoveMotion AllMovedata;	//�u���b�N�̑S�̈ړ��Ŏg�p����ϐ�

	PolygonPoints2 lay;				//�j������̃G�t�F�N�g���
	int Count_lay;					//�j������G�t�F�N�g�̌o�ߎ���

	int ChainCount;	//�u���b�N�̏����̃`�F�C����

	/*�u���b�N�ɕύX��������n*/
	void setBlock_Rect(int x, int y, int w, int h);	//�w�肵���G���A�Ƀu���b�N��ݒu����(�������肪����Ȃ��悤�ɐݒu���܂�)
	void AllMove(int X, int Y);						//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ�����(��ʊO�ɏo�Ă��܂��u���b�N�͏��ł��܂�)
	int Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int Delay = 0);		//�t�B�[���h�u���b�N���폜����
	int Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO);	//�w�肵�����W���w�肵���u���b�N�������ꍇ�ɍ폜

	/*���[�V�����ݒ�֌W*/
	void SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay);	//�t�B�[���h�̃u���b�N�ɕω����[�V������ݒ肷��(����P�̂Ŏg�p���Ď��̂��Ă��m��܂���)
	void SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int Delay = 0);			//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��
	void SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int Delay = 0);	//�t�B�[���h�̃u���b�N�ɕω����[�V����(�ʏ�)��ݒ肷��(�ω����w��)
	void SetChangeMotion_EXPLOSION(int x, int y, BLOCK_TYPE From, int Delay = 0);	//�t�B�[���h�̃u���b�N�ɕω����[�V����(����)��ݒ肷��
	void SetChangeMotion_SMALL(int x, int y, BLOCK_TYPE From, int Delay = 0);		//�t�B�[���h�̃u���b�N�ɕω����[�V����(�������Ȃ��ď�����)��ݒ肷��
	void SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);//�t�B�[���h�̃u���b�N�ړ��Ƀ��[�V������ݒ肷��

	void Virtualfield_Update();							//���z�t�B�[���h�����݂̃t�B�[���h�ƈ�v������
	void AllMoveRequest(int X, int Y);			//�t�B�[���h�S�̂̃u���b�N���w�肵���������ړ����郊�N�G�X�g������(�Q�[�����ꎞ��~���ē������܂�)
	
	/*�אڌ��v�Z�֌W*/
	void SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int * Counter, int UseVirtualField = FALSE);		//�אڂ��铯�F�u���b�N�Ƀ}�[�J�[��t����
	void CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField = FALSE);	//SequenceCount�Ŏg�p����}�[�J�[�e�[�u�����쐬����(�L���ȃG���A)(UseVirtualField=TRUE�ŉ��z�̖ʂ��g�p����)

																																				
	double Score_Scale(int len);//�אڂ���u���b�N�̏������ɃX�R�A�̔{�������߂�֐�

	
};

