#pragma once
#include "PhaseController.h"
#include "Phase_GameMain.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�萔�E�}�N��
//�����K���F�萔�͂��ׂđ啶���A�P��ƒP��̊Ԃ�_�ŋ�؂�

//�f�o�b�O�ݒ�̒�`(�g�p���Ȃ��ꍇ�̓R�����g�A�E�g)
#ifdef DEBUG
//#define DEBUG_GAMEMAIN	//�Q�[�����C���̃f�o�b�O
#endif // DEBUG


#define GAMEVERSION _T("0.0")		//�o�[�W������

#define DRAWFPS 60					//�`��FPS�ݒ�
#define UPDATEFPS 60				//����FPS�ݒ�
#define WINDOW_WIDTH 1280			//��ʂ̉���
#define WINDOW_HEIGHT 960			//��ʂ̍���
#define GAMEWINDOW_PADDINGX 50		//�Q�[����ʂ�X�����̃Y��
#define GAMEWINDOW_PADDINGY 55		//�Q�[����ʂ�Y�����̃Y��
#define GAMEWINDOW_WIDTH 700		//�Q�[����ʂ̉���
#define GAMEWINDOW_HEIGHT 850		//�Q�[����ʂ̍���
#define TITLE _T("Blockbreaker")	//�E�B���h�E�^�C�g��
#define PI (acos(-1.0))				//�~����
#define PIf ((float)acos(-1.0))		//�~����(float)

//�}�N��
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))	//�z��̒��������߂�

#define deg_to_rad(deg) (((deg)/360.)*2*PI)	//�x���烉�W�A���ɕϊ�
#define rad_to_deg(rad) (((rad)/2./PI)*360)	//���W�A������x�ɕϊ�

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�\����
//typedef����̂̓v���O�����S�̂Ŏg�p������݂̂̂ɂ��Ă��������B
//�t�@�C�����ł̂ݎg�p����\���̂�typedef���Ȃ��ł��������B(�⊮�ŏo�Ă��Ă������̂�)

//�L�[�o�C���h�̐ݒ�(DX���C�u�����̃L�[�R�[�h)
typedef struct KeyBind {
	int Key_ENTER;			//����L�[
	int Key_ENTER2;			//����L�[2
	int Key_PAUSE;			//�L�����Z��/�|�[�Y
	int Key_PAUSE2;			//�L�����Z��/�|�[�Y2
	int Key_RotateL;		//��������u���b�N�𔽎��v���ɉ�]������
	int Key_RotateL2;		//��������u���b�N�𔽎��v���ɉ�]������2
	int Key_RotateR;		//��������u���b�N�����v���ɉ�]������
	int Key_RotateR2;		//��������u���b�N�����v���ɉ�]������2
	int Key_UP;				//���ڑI��:��
	int Key_UP2;			//���ڑI��:��2
	int Key_DOWN;			//���ڑI��:��/��������u���b�N�̉���
	int Key_DOWN2;			//���ڑI��:��/��������u���b�N�̉���2
	int Key_LEFT;			//���ڑI��:��/��������u���b�N�̍��ړ�
	int Key_LEFT2;			//���ڑI��:��/��������u���b�N�̍��ړ�2
	int Key_RIGHT;			//���ڑI��:�E/��������u���b�N�̉E�ړ�
	int Key_RIGHT2;			//���ڑI��:�E/��������u���b�N�̉E�ړ�2
}KeyBind;

//�L�[�o�C���h�̐ݒ�(�Q�[���p�b�h)(DX���C�u�����̃L�[�R�[�h)
typedef struct KeyBindjoy {
	unsigned int Joy_ENTER[4];		//����L�[
	unsigned int Joy_PAUSE[4];		//�L�����Z��/�|�[�Y
	unsigned int Joy_RotateL[4];	//��������u���b�N�𔽎��v���ɉ�]������
	unsigned int Joy_RotateR[4];	//��������u���b�N�����v���ɉ�]������
	unsigned int Joy_UP[4];			//���ڑI��:��
	unsigned int Joy_DOWN[4];		//���ڑI��:��/��������u���b�N�̉���
	unsigned int Joy_LEFT[4];		//���ڑI��:��/��������u���b�N�̍��ړ�
	unsigned int Joy_RIGHT[4];		//���ڑI��:�E/��������u���b�N�̉E�ړ�
}KeyBindjoy;

#define PolygonPoints2_MAX 30	//PolygonPoints2�ň����钸�_�̍ő��
//���p�`�̍��W(�ӂ̍��W)�Ȃ�ׂ����v���Œ�`���悤(PolygonPoints2_MAX�p�`�܂�)
typedef struct {
private:
	int pointNum;	//���_�̐�(0�`PolygonPoints2_MAX)
public:
	double X[PolygonPoints2_MAX];
	double Y[PolygonPoints2_MAX];
	//���p�`�̎擾
	int getpointNum() {
		return min(pointNum, PolygonPoints2_MAX);
	}
	//���p�`�̐ݒ�
	void SetpointNum(int pointnum) {
		if (pointnum < 0)	pointnum = 0;
		if (pointnum > PolygonPoints2_MAX) pointnum = PolygonPoints2_MAX;
		pointNum = pointnum;
	}
}PolygonPoints2;

//�x�N�g���֘A
typedef struct {
	double x, y;
}Vec;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//enum��`
//�X���b�h�֌W
//�����K���F"enum��"+_+"�啶���Ŏn�܂�v�f��"
enum THREAD {
	THREAD_Draw,			//�`��X���b�h
	THREAD_Update			//�����X���b�h
};

//�L�[�o�C���h
enum KEYBIND {
	KEYBIND_SELECT,			//���ڂ̌���
	KEYBIND_PAUSE,			//�L�����Z��/�|�[�Y
	KEYBIND_ROTAL,			//��������u���b�N�𔽎��v���ɉ�]������
	KEYBIND_ROTAR,			//��������u���b�N�����v���ɉ�]������
	KEYBIND_UP,				//���ڑI��:��
	KEYBIND_DOWN,			//���ڑI��:��/��������u���b�N�̉���
	KEYBIND_LEFT,			//���ڑI��:��/��������u���b�N�̍��ړ�
	KEYBIND_RIGHT,			//���ڑI��:�E/��������u���b�N�̉E�ړ�
	KEYBIND_NUM				//�L�[�o�C���h�̐�
};

//�t�F�[�Y�֌W
enum FAZE {
	FAZE_Nothing,				//��������
	FAZE_TopMenu,				//�g�b�v���j���[
	FAZE_GameMain,				//���ۂ̃Q�[���v���C���
	FAZE_Manual,				//���������
	FAZE_NUM					//�t�F�[�Y�̐�
};

//�A�i���O�X�e�B�b�N�̑��샂�[�h���邩�H
enum ANALOGSTICKMODE {
	ANALOGSTICKMODE_NOMAL,	//�g�p����[�|����ɉ����đ�����ύX����]
	ANALOGSTICKMODE_VECTOR,	//�g�p����[�p�x�̂ݎ擾�������͈��ɂ���]
	ANALOGSTICKMODE_NOUSE,	//�g�p���Ȃ�
	ANALOGSTICKMODE_NUM		//�v�f�̌�
};

//���O�̎��
enum Log_Type {
	Log_Type_INFORMATION,	//���
	Log_Type_CAUTION,		//�x��(�v���O�������͓̂��������܂��낵���Ȃ����)
	Log_Type_ERROR,			//�G���[(�v���O�����̎��s�ɉe�����o�����)
#ifdef _DEBUG
	Log_Type_DEBUG			//�f�o�b�O�p�ɉ��ɏo�͂������
#endif // _DEBUG
};

//�t�H���g�̎��
//�ǉ��̖����K���F"�啶���Ŏn�܂�v�f��"�̕�����"�t�H���g��_�t�H���g�̐ݒ�(�G�b�W�t���A�t�H���g�T�C�Y�Ȃ�)"�ɂȂ��Ă��܂�
enum FONTTYPE {
	FONTTYPE_GenJyuuGothicLHeavy_Edge25,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y25
	FONTTYPE_GenJyuuGothicLHeavy_Edge30,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y30
	FONTTYPE_GenJyuuGothicLHeavy_Edge35,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y35
	FONTTYPE_GenJyuuGothicLHeavy_Edge40,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y40
	FONTTYPE_GenJyuuGothicLHeavy_Edge50,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y40
	FONTTYPE_GenJyuuGothicLHeavy_Edge60,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y60
	FONTTYPE_GenJyuuGothicLHeavy_Edge70,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y70
	FONTTYPE_GenJyuuGothicLHeavy_Edge80,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y80

	FONTTYPE_SFSquareHeadCondensed_Edge15,	//SF Square Head Condensed�G�b�W�t���T�C�Y15
	FONTTYPE_SFSquareHeadCondensed_Edge25,	//SF Square Head Condensed�G�b�W�t���T�C�Y25
	FONTTYPE_SFSquareHeadCondensed_Edge35,	//SF Square Head Condensed�G�b�W�t���T�C�Y35
};

//���ʉ��̎��
//�G�N�X�v���[���[��wav�t�@�C�������ĒT���₷���悤��"�啶���Ŏn�܂�v�f��"�͎��ۂ̃t�@�C�����ƈ�v�����Ă��܂�
enum SE_TYPE {
	SE_TYPE_ChangeSelect,		//���ڂ̑I�������ړ����鎞�̉�
	SE_TYPE_DecisionSelect,		//���ڂ����肵�����̉�
	SE_TYPE_ButtonCancel,		//���ڂ��L�����Z���������̉�
	SE_TYPE_OwnBarrier,			//�������o���A�𔭓������Ƃ��̉�
	SE_TYPE_OwnDeath,			//���������S�������̉�
	SE_TYPE_Bulletfire1,		//�G���e���𔭎˂����Ƃ��̉�1(�A���p�H)
	SE_TYPE_Bulletfire2,		//�G���e���𔭎˂����Ƃ��̉�2(����)
	SE_TYPE_Bulletfire3,		//�G���e���𔭎˂����Ƃ��̉�3(��)
	SE_TYPE_Bulletfire4,		//�G���e���𔭎˂����Ƃ��̉�4(���[�U�[)
	SE_TYPE_Bulletfire5,		//�G���e���𔭎˂����Ƃ��̉�5(����)
	SE_TYPE_Bulletfire6,		//�G���e���𔭎˂����Ƃ��̉�6(����)
	SE_TYPE_Bulletfire7,		//�G���e���𔭎˂����Ƃ��̉�7(���[�U�[�\��)
	SE_TYPE_Shotfire,			//���@���V���b�g�𔭎˂����Ƃ��̉�
	SE_TYPE_Shotfire2,			//���@���V���b�g�𔭎˂����Ƃ��̉�2
	SE_TYPE_Graze,				//���@�����������ꂽ�Ƃ��̉�
	SE_TYPE_ShotHit,			//���@�̃V���b�g���G�ɓ��������Ƃ��̉�
	SE_TYPE_ShotHit2,			//���@�̃V���b�g���G�ɓ��������Ƃ��̉�2
	SE_TYPE_EnemyDeath,			//�G�����S�����Ƃ��̉�
	SE_TYPE_EnemyDeath2,		//�G�����S�����Ƃ��̉�2
	SE_TYPE_Pause,				//�{�[�Y�{�^��
	SE_TYPE_Itemget,			//�A�C�e�����擾�����Ƃ��̉�
	SE_TYPE_PowerUp,			//�p���[�A�b�v�����Ƃ��̉�
	SE_TYPE_Timeout,			//�������Ԃ̉�
	SE_TYPE_Timeout2,			//�������Ԃ̉�2
	SE_TYPE_Extend,				//1�A�b�v�̉�
	SE_TYPE_bomb_Muteki,		//���G�{���̉�
	SE_TYPE_Bonus,				//�{�[�i�X�̉�
	SE_TYPE_GetBomb,			//�{���擾�̉�
	SE_TYPE_bomb_DamageFloor,	//�_���[�W���{���̉�
	SE_TYPE_bomb_BarrierFloor,	//�o���A���{���̉�
	SE_TYPE_ChargeUP,			//�`���[�W�U���̒i�KUP�̉�
	SE_TYPE_ChargeOK,			//�`���[�W�U���̃��L���X�g�����̉�
	SE_TYPE_Charge1,			//�`���[�W�U��1�̌��ʉ�
	SE_TYPE_Charge2,			//�`���[�W�U��2�̌��ʉ�
	SE_TYPE_NUM					//���ʉ��̌�(�w�肵���ꍇ�͌��ʉ�����)
};


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*�N���X*/


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�N���X�̃C���X�^���X(�O���[�o���ϐ�)
extern Phase_Default phase_Default;		//�f�t�H���g�̃t�F�[�Y
extern Phase_GameMain phase_GameMain;	//�Q�[�����C���̃t�F�[�Y


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�֐��Q
/*Blockbreakor.cpp*/
extern void setKeybind(KeyBind *keyBind = NULL);								//�L�[�o�C���h�̐ݒ�(NULL�ŋK��l)
extern void setUSEGAMEPAD(int type = 0);										//�g�p����Q�[���p�b�h�̐ݒ�(�����ȗ��Őݒ薳��)
extern void	SetAnalogueStickMode(ANALOGSTICKMODE type = ANALOGSTICKMODE_NOUSE);	//�Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓�����@�̐ݒ�
extern void setClearScreen(int Flag);											//��ʂ̃N���A���s�����ǂ���(0�s��Ȃ�)(����Ƃ��͂��܂�)
extern void SetDrawing_interval(int Mode);										//�`��Ԋu�̐ݒ�(0���獀�ڏ�)
extern void SetWindowMode(int Mode);											//�E�B���h�E���[�h�̐ݒ�(0���獀�ڏ�)
extern void SetModeVSync(int Mode);												//���������̐ݒ�(0���獀�ڏ�)
extern void SetModeClear(int Mode);												//��ʏ����̐ݒ�(0���獀�ڏ�)
extern void SetModeCursor(int Mode, int WinMode);								//�}�E�X�J�[�\���̐ݒ�(0���獀�ڏ�)(�E�B���h�E���[�h�̐ݒ�Ɠ�������)
extern void SetModeMultiThread(int Mode);										//�}���`�X���b�h�ł̓���̐ݒ�(0���獀�ڏ�)
extern void SetTextureCut(int Mode);											//�e�N�X�`���̕����̐ݒ�(0���獀�ڏ�)
extern void setKeybindjoy(KeyBindjoy *keyBindjoy);								//�L�[�o�C���h�ݒ�(�Q�[���p�b�h)(NULL�ŋK��l��ݒ�)

extern int	isMultiThread();						//�}���`�X���b�h�œ��삷�邩�ǂ����̎擾(FALSE�V���O��)
extern int	gettUSEGAMEPAD();						//�g�p����Q�[���p�b�h�̎擾
extern unsigned int getKey(int KEYNO);				//�L�[�̓��͏�Ԃ��擾����(DX���C�u�����Œ�`����Ă���L�[�̔ԍ�)(�߂�l�F�L�[��������Ă��鎞�ԁA������Ă��Ȃ��Ƃ���0)
extern unsigned int getJoyKey(int JoyKeyNO);		//�Q�[���p�b�h���͏�Ԃ̎擾(DX���C�u�����Œ�`����Ă���L�[�̔ԍ�)(�߂�l�F�L�[��������Ă��鎞�ԁA������Ă��Ȃ��Ƃ���0)(�Q�[���p�b�h�p)
extern unsigned int getKeyBind(KEYBIND kEYBIND);	//�L�[�o�C���h�ł̃L�[���͏��̎擾(0�����ĂȂ��A1����������)
extern unsigned int getFrameCount(THREAD thread);	//�Q�[�����N�����Ă���̌o�߃t���[�������擾����

extern void 		Changefaze(FAZE NO, THREAD FLAG, int arg = 0, int b_Wait_Loading = FALSE);	//�t�F�[�Y�ύX(�ύX�������t�F�[�Y�ԍ��A�Ăяo���X���b�h�A����1�A�`��X���b�h�̃t�F�[�Y�ύX�����̊����������X���b�h���ҋ@���邩�ǂ���)

/*Calculations.cpp*/
/*�ϊ��n*/
extern double		map(double v, double sx, double sn, double dx, double dn);		//���l�͈̔͂�ʂ͈̔͂ɕϊ�����
extern int			Pot(int inSize);												//�w�肵���l���傫��2��n���Ԃ�
extern double		getDegrees(double nDegrees);									//-180�`180�̒l�ɕϊ�
extern double		ConvertPixpF_To_DegpF(double Speed, double R);					//���ʂ̑��x���p���x�ɕϊ�(�s�N�Z��/�t���[�����x/�t���[��)(�����͕��ʂ̑��x�A���a)
extern double		ConvertDegpF_To_PixpF(double DegSpeed, double R);				//�p���x�𕁒ʂ̑��x�ɕϊ�(�x/�t���[�����s�N�Z��/�t���[��)(�����͊p���x�A���a)
extern int			circulating(int Src, int Min, int Max);							//�w�肵���͈͂Ŏw�肵���l���z������悤�ɕϊ�����(Min�ȏ�Max����)
extern double		circulating_d(double Src, double Min, double Max);				//�w�肵���͈͂Ŏw�肵���l���z������悤�ɕϊ�����(Min�ȏ�Max����)(double�^)
extern double		InRange(double val, double min, double max);					//����l���ő�l�𒴂���ꍇ�͍ő�l�ɁA�ŏ��l�������ꍇ�͍ŏ��l�ɂ���(double�^)
extern double		CutDecimal(double src, int No = 5);								//�w��̏��������Ő؂�̂Ă�(�f�J�������ł��܂��������͒m��܂���)
extern double		ExpandValue(double InVal, double Center, double Ex);			//����l(InVal)������l���S(Center)�Ɋg��E�k��(Ex)�����Ƃ��̒l���擾����
extern void			Gradation_RGB(int R1, int G1, int B1, int R2, int G2, int B2, double X, int *ansR, int *ansG, int *ansB);	//RGB�J���[�ŃO���f�B�G�[�V����������(X�͖ړI�F�܂ł̊���(0�y��{�F�z�`100�y�ړI�F�z)
extern void			RGB_to_HSV(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *V);				//RGB����HSV�ɕϊ�
extern void			RGB_to_HSL(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *L);				//RGB����HSL�ɕϊ�
extern void			HSV_to_RGB(double H, double S, double V, unsigned char *R, unsigned char *G, unsigned char *B);				//HSV����RGB�ɕϊ�
extern void			HSL_to_RGB(double H, double S, double L, unsigned char *R, unsigned char *G, unsigned char *B);				//HSL����RGB�ɕϊ�
extern unsigned int ConvertCollect1to4(unsigned char bit4, unsigned char bit3, unsigned char bit2, unsigned char bit1);								//1byte(unsigned char)�̒l4��4byte(unsigned int)1�ɕϊ�����
extern void			ConvertCollect4to1(const unsigned int src, unsigned char *bit4, unsigned char *bit3, unsigned char *bit2, unsigned char *bit1);	//4byte(unsigned int)1��1byte(unsigned char)�̒l4�ɕϊ�����
/*�`��n*/
extern void			ClearDrawScreenTogrHandle(int grHandle);						//�w�肵���O���t�B�b�N�n���h����ClearDrawScreen���s��(1�t���[����1����Ƃ��ĂԂƏd���Ȃ�܂�)
extern void			DrawTileGraph(int zx, int zy, int GrHandle);					// ��ʂ����ς��ɉ摜��`�悷��(zx, zy : ���炷�h�b�g��)(���[�v)
extern void			DrawRotaImage3D(double X, double Y, double ExLate, double AngleX, double AngleY, double AngleZ, int grHandle);	//�摜��3D��]�`��(�x�w��)
extern void			DrawPolygon2D_Notexture2(PolygonPoints2 *polygonPoints, unsigned int color, int fillFlag);	//���p�`��`�悷��2(�e�N�X�`������)
extern void			DrawLineAA_Polar(double X, double Y, double rota, double length, unsigned int Color, float Thicknes = 1.0f);//���̕`��(�ɍ��W)
extern void			draw_Circle(double X, double Y, double R, int Kakudo);						//�~�O���t�̂悤�ȉ~��`�悷��(���A�G��HP�o�[)(�`�悵�������S�ʒuX,Y,�������a,�`�悷��p�x)
extern void			draw_Circle2(int X, int Y, double per, int Texture, int Texture2);			//�~�O���t�̂悤�ȉ~��`�悷��(�`�悵�������S�ʒuX,Y,�`�悷��360�x�ɑ΂��銄��,�O���t�����̃e�N�X�`��,�~�������̃e�N�X�`��)
extern void			DrawArrow(double X, double Y, double vector, double length, unsigned int Color = GetColor(255, 255, 255), float Thickness = 1.0f);	//���̕`��(�ɍ��W)
/*�����蔻��*/
extern int			collision_rect(double rectX, double rectY, double Width, double Height, double pX, double pY);						//XY�����ɕ��s�Ȏl�p�`�Ɠ_�̂����蔻��
extern int			collision_polygon2(PolygonPoints2 *polygon, double pointX, double pointY);											//���p�`�Ɠ_�̂����蔻��
extern int			collision_tri2(PolygonPoints2 *tri, double pointX, double pointY);													//�O�p�`�Ɠ_�̂����蔻��
extern int			collision_polygon_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2);	//���p�`�Ɛ����̂����蔻��
extern int			collision_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2);			//�����Ɛ����̂����蔻��
extern int			collisionLC(double X1, double Y1, double X2, double Y2, double  circleX, double circleY, double circleR, Vec *ans1, Vec *ans2);//�~�ƒ����̌�_
/*���̑�*/
extern double		getRotation(double X1, double Y1, double X2, double Y2);			//2�_�Ԃ̊p�x�̎擾(�x)
extern double		getDistance(double X1, double Y1, double X2, double Y2);			//2�_�Ԃ̋��������߂�
extern double		getMoveDistance(double a, double MaxSpeed, int Count);				//�����x�A�ő呬�x�A�ړ��J�n����̌o�ߎ��Ԃ��猻�݂̈ړ��������v�Z����
extern double		Cross_product(Vec *a, Vec *b);										//�O�ς̌v�Z
extern Vec			Vector_component(double x, double y, double pointX, double pointY); //�x�N�g���̐����v�Z
extern long long	powi64(long long _Left, int _Yx);									//long long�^��pow�֐�(_Yx < 0�͔�Ή�)
extern double		getGraph_Triangle(int Cycle);										//�O�p�g��Ԃ�
extern double		getGraph_Sin(double frameVal, double Delta, double Shift);			//�T�C���g��Ԃ�(�t���[����������Ƃ��������ɂȂ�)
extern void			PolygonPoints2_setRect(double x, double y, double w, double h, PolygonPoints2 *rect);//PolygonPoints�Ɏl�p�`��ݒ肷��

/*LoadMenu.cpp*/
extern void LoadMenu_Initialize();		//������
extern void LoadMenu_Draw();			//���[�h��ʂ̕\��
extern void LoadMenu_Draw2();			//���[�h��ʂ̕\��(�ŏ��̋N�����p)

/*StartDialog.cpp*/
extern void StartDialog_Initialize(HINSTANCE hInstance);	//������
extern void StartDialog_Show();								//�N���ݒ��ʂ̕\��

/*Font.cpp*/
extern void Font_init();				//������
extern int Font_getHandle(FONTTYPE font);	//�t�H���g�n���h���̎擾
extern void Font_DrawStringWithShadow(double x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);					//�e�t��������̕`��
extern void Font_DrawStringCenterWithShadow(double Center_x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);	//�e�t��������`��(X�̂ݒ��S�w��)

/*SoundEffect*/
extern void SoundEffect_init();				//������
extern void SoundEffect_update();			//���ʉ��̌v�Z�������[�v(���ʉ���炷�����O�ɌĂԂ���)
extern void SoundEffect_Play(SE_TYPE type);	//���ʉ��̍Đ�
extern void SoundEffect_PlayPlace(SE_TYPE type, double plaxeX, double placeY);	//���ʉ��̍Đ�(�ʒu�ŉ��ʂ��ς����)(���͋@�\���Ȃ�)
extern void SoundEffect_Save();				//���ʉ��̏�Ԃ̕ۑ�
extern void SoundEffect_Load();				//���ʉ��̏�Ԃ̕���
extern void SoundEffect_AllPause();			//���ʉ������ׂă|�[�Y����
extern void SoundEffect_SetSEVolume(int Volume);	//���ʉ��̉��ʂ����ׂĕύX����(0�`100)
extern int SoundEffect_GetSEVolume();		//���ʉ��̉��ʎ擾(0�`100)
extern void SoundEffect_LongSEStop();		//�������ʉ��̒�~
extern void SoundEffect_LongSEPause();		//�������ʉ��̃|�[�Y
extern void SoundEffect_LongSEResume();		//�������ʉ��̃��W���[��
extern void SoundEffect_SafePlay(SE_TYPE type);	//���d�Ō��ʉ��̍Đ����s����\��������Ƃ��Ɏg�p������ʉ��̍Đ��֐�(1���ʉ�������1�t���[���Ɉ�x�܂ł����Đ��֐����Ă΂�Ȃ��Ȃ�)
