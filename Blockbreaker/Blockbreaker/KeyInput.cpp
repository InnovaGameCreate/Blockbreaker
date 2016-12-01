#include "MainFunc.h"


KeyInput::KeyInput() {
	Enable = FALSE;
	Select = 0;
	len = 0;
}

//キーボード動作を開始する
void KeyInput::Start(int x, int y, KeyInputCallback_End *keyInputCallback_End) {
	if (isEnable())	return;
	DrawX = x;
	DrawY = y;
	KeyInput::keyInputCallback_End = keyInputCallback_End;
	len = 0;
	Select = 0;
	Select_BeforeEnter = 0;
	for (auto &dat : str)	dat = '_';
	str[ARRAY_LENGTH(str) - 1] = '\0';
	Enable = TRUE;
	printLog_I(_T("キーボードを有効にします"));
}

//キーボードが有効かどうかの取得
int KeyInput::isEnable() {
	return Enable;
}

//描画
void KeyInput::Draw() {
	if (!isEnable())	return;
	int x = DrawX;
	int y = DrawY;

	x -= 150;

	DrawBox(x, y, x + 300, y + 200, GetColor(255, 255, 255), TRUE);
	//文字の表を作成する
	for (int i = 0; i < ARRAY_LENGTH(ch); i++) {
		TCHAR str[10];
		if (ch[i] == '!')		_stprintf_s(str, _T("←"));
		else if (ch[i] == '?')	_stprintf_s(str, _T("決定"));
		else					_stprintf_s(str, _T("%c"), ch[i]);
		unsigned int color = GetColor(100, 200, 100);
		if (Select == i)	color = GetColor(200, 100, 100);

		//決定キーの場合のみ別で描画する
		if (ch[i] == '?') {
			Font_DrawStringCenterWithShadow(x + 150, y + 20 + (i / 9) * 40 + 15, str, color, GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge25);
		}
		else {
			Font_DrawStringCenterWithShadow(x + 20 + ((i % 9)) * 32, y + 20 + (i / 9) * 40, str, color, GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge25);
		}
	}
}

//キー操作
void KeyInput::Key(unsigned int *key) {
	if (!isEnable())	return;

	if (key[KEYBIND_RIGHT] == 1) {
		//右移動
		int Moved = Select + 1;//仮想的に移動先の座標を記録する
		if (Select / 9 != Moved / 9 || Moved >= ARRAY_LENGTH(ch)) {
			//行が変わる場合と、配列がオーバーする時は反対側に行く
			Moved = (Select / 9) * 9;	//反対側に行く
		}
		//移動を反映させる
		Select = Moved;
	}
	if (key[KEYBIND_LEFT] == 1) {
		//右移動
		int Moved = Select - 1;//仮想的に移動先の座標を記録する
		if (Select / 9 != Moved / 9 || Moved < 0) {
			Moved = ((Select / 9) * 9 + (9 - 1) < ARRAY_LENGTH(ch)) ? (Select / 9) * 9 + (9 - 1) : ARRAY_LENGTH(ch) - 1;	//反対側に行く
		}
		//移動を反映させる
		Select = Moved;
	}
	if (key[KEYBIND_DOWN] == 1) {
		//下移動
		int Moved = Select + 9;//仮想的に移動先の座標を記録する
		if (Moved >= ARRAY_LENGTH(ch)) {
			Moved = ARRAY_LENGTH(ch) - 1;
		}
		//移動先が決定キーの場合は移動元の場所を記録する
		if (ch[Moved] == '?' && Moved != Select)	Select_BeforeEnter = Select;
		Select = Moved;

	}
	if (key[KEYBIND_UP] == 1) {
		//上移動
		//移動元が決定キーの場合は移動元に戻る
		if (ch[Select] == '?' && Select != Select_BeforeEnter) {
			Select = Select_BeforeEnter;
		}
		else if (Select - 9 >= 0)				Select -= 9;
	}
	if (key[KEYBIND_SELECT] == 1) {
		if (ch[Select] == '!') {
			//文字の削除
			if (len > 0) {
				//入力文字がある場合のみ1文字削除する
				len--;
				str[len] = '_';
			}
		}
		else if (ch[Select] == '?') {
			//項目の決定
			Enable = FALSE;
			//ファンクタを呼び出す
			if(keyInputCallback_End != NULL)	keyInputCallback_End->operator()(str);
		}
		else {
			if (len < ARRAY_LENGTH(str) - 1) {
				//文字の追加入力
				str[len] = ch[Select];
				len++;
			}
		}
	}
}

//入力されている文字列の取得
TCHAR *KeyInput::getStr() {
	if(isEnable())	return str;
	else			return _T("");
}