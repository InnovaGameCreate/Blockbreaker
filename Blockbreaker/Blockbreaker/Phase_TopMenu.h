#pragma once

#include "MainFunc.h"

class Phase_TopMenu : public PhaseController
{
public:
	Phase_TopMenu();
	~Phase_TopMenu();

	void Init_Draw();		//描画処理の初期化
	void Init_Update();		//計算処理の初期化
	void Draw();			//描画処理
	void Update();			//計算処理
	void Finalize_Draw();	//描画の終了処理
	void Finalize_Update();	//計算の終了処理
private:
	void Key();				//キー処理
};

