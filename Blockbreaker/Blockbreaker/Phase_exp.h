#pragma once
#include "PhaseController.h"

class Phase_exp : public PCon::Phase_
{
	private:
		int tex_exp;
public:
	Phase_exp();
	void Draw()					override;	//•`‰æˆ—
	void Update()				override;	//ŒvZˆ—
	void Init_Draw()			override;	//‰Šú‰»(•`‰æˆ—)
	void Fin_Draw()				override;	//I—¹ˆ—(•`‰æ)
};

