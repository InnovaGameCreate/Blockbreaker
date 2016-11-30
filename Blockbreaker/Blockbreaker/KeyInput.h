#pragma once
//キーボードからの文字入力
#include <tchar.h>



class KeyInput
{
public:
	KeyInput();
	void Start();	//キーボード動作を開始する
	
	void Draw(int x, int y);	//描画

	int isEnable();		//キーボードが有効かどうかの取得
	void Key();			//キー操作
	TCHAR * getStr();	//入力されている文字列の取得
private:
	int Enable;	//有効かどうか

	int Select;	//現在選択しているボタン

	int len;	//現在入力済みの文字数
	
	TCHAR str[7];//入力された文字列
};

static TCHAR ch[] = { 'A', 'B', 'C', 'B', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' , 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
