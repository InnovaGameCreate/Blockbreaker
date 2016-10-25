//�����̍��ڂ̒�������I�Ԃ��߂̃N���X
#pragma once

#include "MainFunc.h"
typedef void(*Callback_SelectItem_Selected)();	//�A�C�e����I�������Ƃ�
typedef void(*Callback_Draw)();					//�ǉ��ŉ����`�悷��
struct SelectItem_data {
	TCHAR str[100];//���ڂɕ\������镶��
	Callback_SelectItem_Selected func_SelectItem_Selected;	//���ڂ��I�����ꂽ�Ƃ��ɌĂ΂��R�[���o�b�N�֐�
	Callback_Draw func_Callback_Draw;						//�ǉ��̕`��֐�
	bool enable;//���̍��ڂ��L�����ǂ���
	int Alpha;	//�Ō�ɕ`�悵�����l
	bool SelectEnable;//�I���\���ǂ���
};


class SelectItem
{
private:
	double X, Y;//�\��������W
	struct SelectItem_data data[20];
	int SelectedItem;//���ݑI�����Ă���A�C�e���ԍ�
	bool Select_Enable;
	bool Enable;
	bool isEnableItem(int No);
	int SelectType;//�I���̏��(0�ŃX�N���[��1�ŃX�N���[�����Ȃ����)
	double Haba;
	int getZettaichi(int No);
public:
	SelectItem(double x, double y);	//�R���X�g���N�^(�\�����W)
	~SelectItem();
	int addItem(TCHAR *str, size_t len, Callback_SelectItem_Selected func, Callback_Draw drawfunc);//���ڂ̒ǉ�(������A���ڂ��I�����ꂽ�Ƃ��A�ǉ��̕`��֐�)
	void setSelectEnable(int b_flag);	//�I������I�ׂ�悤�ɂ��邩�ǂ���
	void setEnable(int b_flag);
	void setScrolltype(int type);	//�I���̏�Ԃ�ݒ�(0�ŃX�N���[��1�ŃX�N���[�����Ȃ����)
	void setItemEnable(bool b_Enable, int No);
	void sethaba(double haba);
	void Draw();					//�`��
	void Update();					//�v�Z
	int  getSelecedtItem();			//���ݑI�����Ă��鍀�ڂ̎擾
	void setSelecedtItem(int No);	//���ڂ̑I��
	int getItemAlpha(int No);		//�Ō�ɕ`�悵���Ƃ��̃��l���擾
};

