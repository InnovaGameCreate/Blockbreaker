#pragma once

#include "Base_BB_Enum.h"	//enum��`(�ʃt�@�C��)
#include "Base_BB_Define.h"	//define��`(�ʃt�@�C��)

#include "Base_BB_PhaseController.h"
#include "Base_BB_FpsController.h"
#include "Base_BB_Log.h"
#include "Base_BB_RandomTable.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�\���̂̐錾
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
//�֐��Q
/*MainLoop.cpp*/
void Base_BB_Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);	//���C�u�����̏���������(�ŏ��ɌĂяo���Ă�������)(������WinMain�Ɠ���)
void Base_BB_MainLoop();														//���C�����[�v(�߂�܂���)
void Base_BB_setFunc_InitAfterDXlibInit(void(*func)(void));								//DX���C�u�����̏��������I����Ă�����s���鏉���������֐���ݒ肷��
void Base_BB_setFaze(FAZE FazeNo, PhaseController *phase);								//�t�F�[�Y�̒�`���s��

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
extern void ExitGameRequest();													//�v���O�������I������

extern int	isMultiThread();						//�}���`�X���b�h�œ��삷�邩�ǂ����̎擾(FALSE�V���O��)
extern int	gettUSEGAMEPAD();						//�g�p����Q�[���p�b�h�̎擾
extern unsigned int getKey(int KEYNO);				//�L�[�̓��͏�Ԃ��擾����(DX���C�u�����Œ�`����Ă���L�[�̔ԍ�)(�߂�l�F�L�[��������Ă��鎞�ԁA������Ă��Ȃ��Ƃ���0)
extern unsigned int getJoyKey(int JoyKeyNO);		//�Q�[���p�b�h���͏�Ԃ̎擾(DX���C�u�����Œ�`����Ă���L�[�̔ԍ�)(�߂�l�F�L�[��������Ă��鎞�ԁA������Ă��Ȃ��Ƃ���0)(�Q�[���p�b�h�p)
extern unsigned int getKeyBind(KEYBIND kEYBIND);	//�L�[�o�C���h�ł̃L�[���͏��̎擾(0�����ĂȂ��A1����������)
extern unsigned int getFrameCount(THREAD thread);	//�Q�[�����N�����Ă���̌o�߃t���[�������擾����

extern void 		Changefaze(FAZE NO, THREAD FLAG, int arg = 0, int b_Wait_Loading = FALSE);	//�t�F�[�Y�ύX(�ύX�������t�F�[�Y�ԍ��A�Ăяo���X���b�h�A����1�A�`��X���b�h�̃t�F�[�Y�ύX�����̊����������X���b�h���ҋ@���邩�ǂ���)

/*StartDialog.cpp*/
extern void StartDialog_Initialize(HINSTANCE hInstance);	//������
extern void StartDialog_Show();								//�N���ݒ��ʂ̕\��

/*LoadMenu.cpp*/
extern void LoadMenu_Initialize();		//������
extern void LoadMenu_Draw();			//���[�h��ʂ̕\��
extern void LoadMenu_Draw2();			//���[�h��ʂ̕\��(�ŏ��̋N�����p)

/*Font.cpp*/
extern void Font_init();					//������
extern int Font_getHandle(FONTTYPE font);	//�t�H���g�n���h���̎擾
extern void Font_DrawStringWithShadow(double x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);					//�e�t��������̕`��
extern void Font_DrawStringCenterWithShadow(double Center_x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);	//�e�t��������`��(X�̂ݒ��S�w��)