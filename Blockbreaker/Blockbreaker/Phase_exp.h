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
	void Initialize(int arg)	override;	//‰Šú‰»(•`‰æˆ—)
	void Finalize()				override;	//I—¹ˆ—(•`‰æ)
};

