#pragma once
#include "MainFunc.h"

class Phase_TopMenu : public PCon::Phase_
{
public:
	Phase_TopMenu();
	~Phase_TopMenu();

	void Init_Draw()			override;	//初期化(描画)
	void Draw()					override;	//描画処理
	void Update()				override;	//計算処理
	void Fin_Draw()				override;	//描画の終了処理(描画)
private:
	//ここにメニュークラスを定義する
	class SelectItem_menu : public SelectItem
	{
	public:
		SelectItem_menu(int X, int Y) : SelectItem(X, Y) {};//コンストラクタ(スーパークラスのコンストラクタを明示的に呼んでいます)
	private:
		void Event_Select(int No) override;	//ポーズメニューのボタンが押されたとき(オーバーライド)
	};

	SelectItem_menu menu = SelectItem_menu(WINDOW_WIDTH /2, 700);	//メニュー項目クラス

	int Tex_backGround;	//背景画像


	void Key();				//キー処理
};

