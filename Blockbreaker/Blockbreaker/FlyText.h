#pragma once
#include "Enum.h"

class FlyText {
public:
	int addFlyText(double CenterX, double Y, int limit, FONTTYPE font, unsigned int Color, TCHAR *fmt, ...);	//フライテキストの追加
	void Draw();		//フライテキストを描画する
	void Update();		//フライテキストの計算処理
	FlyText();
	~FlyText();
private:
	static const int FLYTEXT_MAXNUM = 100;

	struct Data {
		Data() {
			Enable = FALSE;
		}
		int Enable;			//有効かどうか
		TCHAR string[100];	//描画する文字列
		int fonthandle;		//描画するフォントハンドル(DXライブラリ)
		unsigned int Color;	//描画する文字列の色
		double x, y;		//文字列を描画する位置(左基準)
		int Count;			//フライテキストのカウントタ
		int Limit;			//フライテキストが消滅するカウント数
	};

	Data FlyTextData[FLYTEXT_MAXNUM];


	void Initialize(int i);	//指定したフライテキストを初期化
	int isEnable(int i);	//指定したフライテキストが有効かどうかの取得(TRUEで有効)
};