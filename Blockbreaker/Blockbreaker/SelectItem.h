//複数の項目の中から一つを選ぶためのクラス(オーバーライドして使用する)
#pragma once
#include "Enum.h"

class SelectItem
{
private:
	struct SelectItem_data {
		TCHAR str[100];//項目に表示される文字
		bool enable;//その項目が有効かどうか
		int Alpha;	//最後に描画したα値
		bool SelectEnable;//選択可能かどうか
		FONTTYPE font;	//項目の描画に使用するフォント
	};

	double X, Y;//表示する座標
	struct SelectItem_data data[20];
	int SelectedItem;//現在選択しているアイテム番号
	bool Select_Enable;	//通常通りの描画を行うが選択肢の変更が出来ない状態
	bool ControlEnable;	//項目の描画は行うが選択は出来ない状態
	bool Enable;		//可視状態かどうか(FALSEで不可視状態になりコントロールも失う)
	bool isEnableItem(int No);
	int SelectType;		//選択の状態(0でスクロール1でスクロールしないやつ)
	double Haba;
	int Centering;	//項目の揃える位置(-1で左、0で中央、1で右)
	int getZettaichi(int No);
public:
	SelectItem(double x, double y);				//コンストラクタ(表示座標)
	int addItem(TCHAR *str, size_t len, FONTTYPE font = FONTTYPE_GenJyuuGothicLHeavy_Edge60);//項目の追加(文字列、項目が選択されたとき、追加の描画関数)
	void setSelectEnable(int b_flag);			//選択肢を選べるようにするかどうか
	void setCenteringMode(int centeringMode);	//項目の中央位置の設定
	void setControlEnable(int b_flag);
	void setEnable(int flag);		//このモジュール自体を有効状態にするかどうかの設定
	void setScrolltype(int type);	//選択の状態を設定(0でスクロール1でスクロールしないやつ)
	void setItemEnable(bool b_Enable, int No);
	void sethaba(double haba);
	void Draw();					//描画
	void Update();					//計算
	int  getSelecedtItem();			//現在選択している項目の取得
	void setSelecedtItem(int No);	//項目の選択
	int getItemAlpha(int No);		//最後に描画したときのα値を取得
	int isEnable();					//このモジュール自体が有効かどうかの取得

	virtual void Event_Select(int ItemNo) {};		//選択項目が選択されたときに実行される
	virtual void Event_Draw(int ItemNo) {};			//現在選択している項目が描画されたときに実行される
};