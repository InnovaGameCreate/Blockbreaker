//複数の項目の中から一つを選ぶためのクラス
#pragma once

#include "MainFunc.h"
typedef void(*Callback_SelectItem_Selected)();	//アイテムを選択したとき
typedef void(*Callback_Draw)();					//追加で何か描画する
struct SelectItem_data {
	TCHAR str[100];//項目に表示される文字
	Callback_SelectItem_Selected func_SelectItem_Selected;	//項目が選択されたときに呼ばれるコールバック関数
	Callback_Draw func_Callback_Draw;						//追加の描画関数
	bool enable;//その項目が有効かどうか
	int Alpha;	//最後に描画したα値
	bool SelectEnable;//選択可能かどうか
};


class SelectItem
{
private:
	double X, Y;//表示する座標
	struct SelectItem_data data[20];
	int SelectedItem;//現在選択しているアイテム番号
	bool Select_Enable;
	bool Enable;
	bool isEnableItem(int No);
	int SelectType;//選択の状態(0でスクロール1でスクロールしないやつ)
	double Haba;
	int getZettaichi(int No);
public:
	SelectItem(double x, double y);	//コンストラクタ(表示座標)
	~SelectItem();
	int addItem(TCHAR *str, size_t len, Callback_SelectItem_Selected func, Callback_Draw drawfunc);//項目の追加(文字列、項目が選択されたとき、追加の描画関数)
	void setSelectEnable(int b_flag);	//選択肢を選べるようにするかどうか
	void setEnable(int b_flag);
	void setScrolltype(int type);	//選択の状態を設定(0でスクロール1でスクロールしないやつ)
	void setItemEnable(bool b_Enable, int No);
	void sethaba(double haba);
	void Draw();					//描画
	void Update();					//計算
	int  getSelecedtItem();			//現在選択している項目の取得
	void setSelecedtItem(int No);	//項目の選択
	int getItemAlpha(int No);		//最後に描画したときのα値を取得
};

