#pragma once
#include "PhaseController.h"

class Phase_exp : public PCon::Phase_
{
	private:
		int tex_exp;
public:
	Phase_exp();
	void Draw()					override;	//�`�揈��
	void Update()				override;	//�v�Z����
	void Init_Draw()			override;	//������(�`�揈��)
	void Fin_Draw()				override;	//�I������(�`��)
};

