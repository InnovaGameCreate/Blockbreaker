#pragma once
#include "PhaseController.h"

class Phase_exp : public PCon::Phase_
{
	private:
		int tex_exp;
public:
	Phase_exp();
	void Draw()					override;	//描画処理
	void Update()				override;	//計算処理
	void Init_Draw()			override;	//初期化(描画処理)
	void Fin_Draw()				override;	//終了処理(描画)
};

