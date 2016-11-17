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
	//ここにメニュークラスを定義する
	class SelectItem_menu : public SelectItem
	{
	public:
		SelectItem_menu(int X, int Y) : SelectItem(X, Y) {};//コンストラクタ(スーパークラスのコンストラクタを明示的に呼んでいます)
	private:
		void Event_Select(int No) override;	//ポーズメニューのボタンが押されたとき(オーバーライド)
	};

	SelectItem_menu menu = SelectItem_menu(WINDOW_WIDTH/2, 700);	//メニュー項目クラス

	int Tex_backGround;	//背景画像


	void Key();				//キー処理
};

