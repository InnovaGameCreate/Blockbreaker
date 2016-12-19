#pragma once
//キーボードからの文字入力
#include <tchar.h>

/*キー入力のコールバック関数クラス*/
//キー入力が終了した時に呼ばれる
class KeyInputCallback_End {
public:
	virtual void operator()(TCHAR *str) = 0;
};


class KeyInput
{
public:
	KeyInput();
	void Start(int x, int y, KeyInputCallback_End *keyInputCallback_End);	//キーボード動作を開始する
	
	void Draw();	//描画
	void Update();	//更新処理

	int isEnable();					//キーボードが有効かどうかの取得
	void Key(unsigned int *key);	//キー操作
	TCHAR * getStr();				//入力されている文字列の取得
private:
	int Enable;	//有効かどうか

	int DrawCountTotal;		//ゲームが起動してから描画を行った回数
	int UpdateCount;		//キーボードが有効になってからの更新カウント

	int Select;	//現在選択しているボタン

	int len;	//現在入力済みの文字数

	int BackImage;	//背景イメージのハンドル

	int Select_BeforeEnter;	//決定キーに移動する前に選択されていたキー

	float DrawX, DrawY;	//描画位置
	
	TCHAR str[7];//入力された文字列

	KeyInputCallback_End *keyInputCallback_End;	//キー入力が終了した時に呼ばれるファンクタ

	void DrawFirst();	//初回描画時にのみ実行される
};

//キーボードに入力する文字列(!,?はDelキーと決定キー)
static TCHAR ch[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' , 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?' };
