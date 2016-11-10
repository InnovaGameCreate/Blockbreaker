#pragma once

#include "MainFunc.h"

class Phase_TopMenu : public PhaseController
{
public:
	Phase_TopMenu();
	~Phase_TopMenu();

	void Init_Draw();		//•`‰æˆ—‚Ì‰Šú‰»
	void Init_Update();		//ŒvZˆ—‚Ì‰Šú‰»
	void Draw();			//•`‰æˆ—
	void Update();			//ŒvZˆ—
	void Finalize_Draw();	//•`‰æ‚ÌI—¹ˆ—
	void Finalize_Update();	//ŒvZ‚ÌI—¹ˆ—
private:
	void Key();				//ƒL[ˆ—
};

