#include "MainFunc.h"


KeyInput::KeyInput() {
	Enable = FALSE;
	Select = 0;
}

//キーボード動作を開始する
void KeyInput::Start() {
	Enable = TRUE;
	str[0] = '\0';
	for (auto &dat : str)	dat = '_';
	str[ARRAY_LENGTH(str) - 1] = '\n';
	printLog_I(_T("キーボードを有効にします"));
}

//キーボードが有効かどうかの取得
int KeyInput::isEnable() {
	return Enable;
}

//描画
void KeyInput::Draw(int x, int y) {
	if (!isEnable())	return;

	x -= 150;

	DrawBox(x, y, x + 300, y + 200, GetColor(255, 255, 255), TRUE);
	//文字の表を作成する
	for (int i = 0; i < ARRAY_LENGTH(ch); i++) {
		TCHAR str[10];
		_stprintf_s(str, _T("%c"), ch[i]);
		unsigned int color = GetColor(100, 200, 100);
		if (Select == i)	color = GetColor(200, 100, 100);
		Font_DrawStringCenterWithShadow(x + 20 + ((i % 9)) * 32, y + 20 + (i / 9) * 40, str, color, GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge25);
	}
}

//キー操作
void KeyInput::Key() {
	if (getKeyBind(KEYBIND_RIGHT) == 1) {
		//右移動
		if (Select / 9 == (Select + 1) / 9 && Select + 1 < ARRAY_LENGTH(ch))	Select++;
	}
	if (getKeyBind(KEYBIND_LEFT) == 1) {
		//右移動
		if (Select / 9 == (Select - 1) / 9 && Select > 0)	Select--;
	}
	if (getKeyBind(KEYBIND_DOWN) == 1) {
		//下移動
		if(Select + 9 < ARRAY_LENGTH(ch))	Select += 9;
	}
	if (getKeyBind(KEYBIND_UP) == 1) {
		//上移動
		if (Select - 9 >= 0)				Select -= 9;
	}
	if (getKeyBind(KEYBIND_SELECT) == 1) {
		if (len < ARRAY_LENGTH(str)-1) {
			str[len] = ch[Select];
			len++;
		}
	}
}

//入力されている文字列の取得
TCHAR *KeyInput::getStr() {
	return str;
}