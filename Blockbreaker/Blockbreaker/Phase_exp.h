#pragma once
#include "PhaseController.h"

class Phase_exp :
	public SK::Phase_
{
	private:
		int tex_exp;
public:
	Phase_exp();
	void Draw()override;			//•`‰æˆ—
	void Update()override;			//ŒvZˆ—
	void Init_Draw()override;		//‰Šú‰»(•`‰æˆ—)
};

