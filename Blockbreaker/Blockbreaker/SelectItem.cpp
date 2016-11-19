#include "MainFunc.h"

//コンストラクタ
SelectItem::SelectItem(double x, double y)
{
	SelectedItem = 0;
	for (int i = 0; i < 20; i++) {
		data[i].enable = false;
	}
	X = x;
	Y = y;
	Enable = true;
	Select_Enable = true;
	SelectType = 0;
	Haba = 150;
	Centering = -1;
}

//項目の追加
int SelectItem::addItem(TCHAR *str, size_t len, FONTTYPE font) {
	int free = -1;
	for (int i = 0; i < 20; i++) {
		if (data[i].enable == false) {
			free = i;
			break;
		}
	}
	if (free == -1) {
		printLog_E(_T("要素が一杯です"));
		return -1;
	}
	_tcscpy_s(data[free].str, str);
	data[free].SelectEnable = true;
	data[free].font = font;
	data[free].enable = true;
	return 0;
}

//選択を有効・無効にする(キーで操作して項目を変えれない)
void SelectItem::setSelectEnable(int b_flag) {
	Select_Enable = (b_flag) ? true : false;
	if (Select_Enable)	printLog_I(_T("SelectItemの選択を【有効】に設定しました"));
	else				printLog_I(_T("SelectItemの選択を【無効】に設定しました"));
}

//選択肢自体を無効化
void SelectItem::setEnable(int b_flag) {
	Enable = (b_flag) ? true : false;
	if (Enable)	printLog_I(_T("SelectItemを【有効】に設定しました"));
	else		printLog_I(_T("SelectItemを【無効】に設定しました"));
}

//選択の状態を設定(0でスクロール1でスクロールしないやつ)
void SelectItem::setScrolltype(int type) {
	SelectType = type;
}

//特定の選択肢を選択可能にするかどうか(trueで可能)
void SelectItem::setItemEnable(bool b_Enable, int No) {
	if (isEnableItem(No)) {//項目が存在する場合
		data[No].SelectEnable = (b_Enable) ? true : false;
		if (data[No].SelectEnable == false && SelectedItem == No) {//無効にした場合かつ選択している場合、選択肢の位置を調整する
			int num = SelectedItem + 1;//次の項目を選択したことにする
			for (; num < 20; num++) {
				if (data[num].enable && data[num].SelectEnable)	break;
			}
			if (num < 20) {
				SelectedItem = num;//項目が正常なら選択肢を変える
				return;
			}
			//次の選択肢が無理だった場合
			num = SelectedItem - 1;//次の項目を選択したことにする
			for (; num >= 0; num--) {
				if (data[num].enable && data[num].SelectEnable)	break;
			}
			if (num >= 0) {
				SelectedItem = num;//項目が正常なら選択肢を変える
				return;
			}
			//次も前も無理だった場合
			//エラー
			printLog_E(_T("選択可能アイテムがありませんでした"));
		}
	}
}

//アイテムの幅を設定する
void SelectItem::sethaba(double haba) {
	Haba = haba;
}

//項目の中央位置の設定(-1で左、0で中央、1で右)
void SelectItem::setCenteringMode(int centeringMode) {
	if (centeringMode < 0) {
		Centering = -1;
	}
	else if(centeringMode > 0){
		Centering = 1;
	}
	else {
		Centering = 0;
	}
}

//項目の描画
void SelectItem::Draw() {
	double x = X;
	double y = Y;
	int Count = 0;//アイテムのカウント数
	for (int i = 0; i < 20; i++) {
		if (data[i].enable && data[i].SelectEnable) {
			unsigned int color = GetColor(240, 240, 240);
			int alpha = 128;//透過度
			if (i == SelectedItem && Enable)	color = GetColor(224, (unsigned int)(160 * getGraph_Triangle(120)), (unsigned int)(160 * getGraph_Triangle(120)));
			if (abs(getZettaichi(i)) == 2)							alpha = 128;
			else if (abs(getZettaichi(i)) == 1 && SelectType == 0)	alpha = 194;
			else if (i == SelectedItem)								alpha = 255;
			if (i != SelectedItem && Select_Enable == false)		alpha = 64;
			if (Enable == false)									alpha = 128;
			if (abs(getZettaichi(i)) >= 3 && SelectType == 0)		alpha = 0;
			if (SelectType == 0)	y = Y + (getZettaichi(i) * Haba);
			else					y = Y + (Count * Haba);
			data[i].Alpha = alpha;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			int Place_X = 0;
			if (Centering < 0) {
				Place_X = 0;
			}
			else if(Centering > 0){
				//描画予定の文字列の幅を取得する
				Place_X = -GetDrawStringWidthToHandle(data[i].str, ARRAY_LENGTH(data[i].str), Font_getHandle(data[i].font));
			}
			else {
				Place_X = -GetDrawStringWidthToHandle(data[i].str, ARRAY_LENGTH(data[i].str), Font_getHandle(data[i].font))/2;
			}
			DrawStringFToHandle((float)(Place_X + x + 4), (float)(y + 4), data[i].str, GetColor(30, 30, 30), Font_getHandle(data[i].font));
			DrawStringFToHandle((float)(Place_X + x), (float)y, data[i].str, color, Font_getHandle(data[i].font));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (i == SelectedItem) {
				Event_Draw(SelectedItem);
			}
			Count++;
		}
	}
}

//実際に選択している項目と現在描画している項目との実際の見た目の差を取得(選択無効項目を考慮した差になっているか取得)
int SelectItem::getZettaichi(int No) {
	//選択項目との絶対値の計算
	if (No == SelectedItem)	return 0;//選択している項目の場合は差0
	int Count = 0;
	//選択アイテムの後ろ部分の場合
	for (int i = SelectedItem; i < No; i++) {
		if (data[i].enable && data[i].SelectEnable) {
			Count++;
		}
	}
	//選択アイテムより前の場合
	for (int i = SelectedItem - 1; i >= No; i--) {
		if (data[i].enable && data[i].SelectEnable) {
			Count--;
		}
	}
	return Count;
}

//項目の更新(キー判定とか)
void SelectItem::Update() {
	if (Select_Enable == false)	return;
	if (Enable == false)		return;
	if (getKeyBind(KEYBIND_UP) == 1) {
		int num = SelectedItem - 1;//次の項目を選択したことにする
		for (; num >= 0; num--) {
			if (data[num].enable && data[num].SelectEnable)	break;
		}
		if (num >= 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);
			SelectedItem = num;//項目が正常なら選択肢を変える
		}
	}
	else if (getKeyBind(KEYBIND_DOWN) == 1) {
		int num = SelectedItem + 1;//次の項目を選択したことにする
		for (; num < 20; num++) {
			if (data[num].enable && data[num].SelectEnable)	break;
		}
		if (num < 20) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);
			SelectedItem = num;//項目が正常なら選択肢を変える
		}
	}
	else if (getKeyBind(KEYBIND_SELECT) == 1 ) {
		SoundEffect_Play(SE_TYPE_DecisionSelect);
		Event_Select(SelectedItem);	//項目が選択されたときの関数を呼ぶ
	}
}

//選択している項目の取得
int SelectItem::getSelecedtItem() {
	return SelectedItem;
}

//項目の選択
void SelectItem::setSelecedtItem(int No) {
	if (isEnableItem(No)) {
		SelectedItem = No;
		printLog_I(_T("SelectItemの初期選択を【%d】に設定しました"), SelectedItem);
	}
}

//指定された番号に項目が存在するかどうかの取得
bool SelectItem::isEnableItem(int No) {
	if (No < 0 || 20 <= No)	return false;
	return data[No].enable;
}

//最後に描画したときのα値を取得
int SelectItem::getItemAlpha(int No) {
	if (isEnableItem(No)) {
		return data[No].Alpha;
	}
	return 0;
}