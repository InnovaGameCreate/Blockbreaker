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
	void Key();				//�L�[����
};

