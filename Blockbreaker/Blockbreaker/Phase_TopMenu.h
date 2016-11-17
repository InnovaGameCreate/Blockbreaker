#pragma once
#include "MainFunc.h"

class Phase_TopMenu : public PhaseController
{
public:
	Phase_TopMenu();
	~Phase_TopMenu();

	void Init_Draw();		//�`�揈���̏�����
	void Init_Update();		//�v�Z�����̏�����
	void Draw();			//�`�揈��
	void Update();			//�v�Z����
	void Finalize_Draw();	//�`��̏I������
	void Finalize_Update();	//�v�Z�̏I������
private:
	//�����Ƀ��j���[�N���X���`����
	class SelectItem_menu : public SelectItem
	{
	public:
		SelectItem_menu(int X, int Y) : SelectItem(X, Y) {};//�R���X�g���N�^(�X�[�p�[�N���X�̃R���X�g���N�^�𖾎��I�ɌĂ�ł��܂�)
	private:
		void Event_Select(int No) override;	//�|�[�Y���j���[�̃{�^���������ꂽ�Ƃ�(�I�[�o�[���C�h)
	};

	SelectItem_menu menu = SelectItem_menu(WINDOW_WIDTH/2, 700);	//���j���[���ڃN���X

	int Tex_backGround;	//�w�i�摜


	void Key();				//�L�[����
};

