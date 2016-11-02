//�����̍��ڂ̒�������I�Ԃ��߂̃N���X(�I�[�o�[���C�h���Ďg�p����)
#pragma once
#include "MainFunc.h"
#include "Enum.h"

class SelectItem
{
private:
	struct SelectItem_data {
		TCHAR str[100];//���ڂɕ\������镶��
		bool enable;//���̍��ڂ��L�����ǂ���
		int Alpha;	//�Ō�ɕ`�悵�����l
		bool SelectEnable;//�I���\���ǂ���
		FONTTYPE font;	//���ڂ̕`��Ɏg�p����t�H���g
	};

	double X, Y;//�\��������W
	struct SelectItem_data data[20];
	int SelectedItem;//���ݑI�����Ă���A�C�e���ԍ�
	bool Select_Enable;
	bool Enable;
	bool isEnableItem(int No);
	int SelectType;//�I���̏��(0�ŃX�N���[��1�ŃX�N���[�����Ȃ����)
	double Haba;
	int Centering;	//���ڂ̑�����ʒu(-1�ō��A0�Œ����A1�ŉE)
	int getZettaichi(int No);
public:
	SelectItem(double x, double y);	//�R���X�g���N�^(�\�����W)
	int addItem(TCHAR *str, size_t len, FONTTYPE font = FONTTYPE_GenJyuuGothicLHeavy_Edge60);//���ڂ̒ǉ�(������A���ڂ��I�����ꂽ�Ƃ��A�ǉ��̕`��֐�)
	void setSelectEnable(int b_flag);	//�I������I�ׂ�悤�ɂ��邩�ǂ���
	void setCenteringMode(int centeringMode);	//���ڂ̒����ʒu�̐ݒ�
	void setEnable(int b_flag);
	void setScrolltype(int type);	//�I���̏�Ԃ�ݒ�(0�ŃX�N���[��1�ŃX�N���[�����Ȃ����)
	void setItemEnable(bool b_Enable, int No);
	void sethaba(double haba);
	void Draw();					//�`��
	void Update();					//�v�Z
	int  getSelecedtItem();			//���ݑI�����Ă��鍀�ڂ̎擾
	void setSelecedtItem(int No);	//���ڂ̑I��
	int getItemAlpha(int No);		//�Ō�ɕ`�悵���Ƃ��̃��l���擾

	virtual void Event_Select(int ItemNo) {};		//�I�����ڂ��I�����ꂽ�Ƃ��Ɏ��s�����
	virtual void Event_Draw(int ItemNo) {};			//���ݑI�����Ă��鍀�ڂ��`�悳�ꂽ�Ƃ��Ɏ��s�����
};