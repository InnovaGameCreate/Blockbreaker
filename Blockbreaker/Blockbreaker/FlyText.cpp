//#include "FlyText.h"
#include "MainFunc.h"

//フライテキストの表示


FlyText::FlyText() {
	AllDelete();
}


FlyText::~FlyText() {
}

//指定したフライテキストを初期化
void FlyText::Initialize(int num) {
	if (isEnable(num) == FALSE)	return;
	FlyTextData[num].Enable = FALSE;
}

//フライテキストの追加(戻り値は管理番号,-1の時は失敗)
int FlyText::addFlyText(double CenterX, double CenterY, int limit, FONTTYPE font, unsigned int Color, TCHAR *fmt, ...) {
	//空いている配列を探索する
	int temp = -1;
	for (int i = 0; i < FLYTEXT_MAXNUM; i++) {
		if (isEnable(i) == FALSE) {
			temp = i;
			break;
		}
	}

	//配列が探しきれなかった場合は失敗
	if (temp == -1)	return -1;

	//配列の初期化を行う
	Initialize(temp);

	//引数の書式付き文字列から文字列を生成する

	va_list arg;//引数を格納する場所
	va_start(arg, fmt);
	_vstprintf_s(FlyTextData[temp].string, fmt, arg);  //Printfに該当する部分
	va_end(arg);

	//その他の設定を反映する
	FlyTextData[temp].fonthandle = Font_getHandle(font);
	FlyTextData[temp].Color = Color;
	FlyTextData[temp].x = CenterX;
	FlyTextData[temp].y = CenterY;
	FlyTextData[temp].Count = 0;
	FlyTextData[temp].Limit = limit;

	//フライテキストを有効にする
	FlyTextData[temp].Enable = TRUE;
	return temp;
}

//指定したフライテキストが有効かどうかの取得(TRUEで有効)
int FlyText::isEnable(int num) {
	if (num < 0 || FLYTEXT_MAXNUM <= num)	return FALSE;
	return FlyTextData[num].Enable;
}

//フライテキストを描画する
void FlyText::Draw() {
	for (auto dat : FlyTextData) {
		if (dat.Enable) {
			double val = 0;
			val = dat.Count / (double)dat.Limit;
			int Alpha = 255;
			if (val > 0.7)	Alpha = (int)((1 - val) / 0.3 * 255);

			//中央座標なのでが記録されているので、描画位置を修正する
			float x = (float)(dat.x - GetDrawStringWidthToHandle(dat.string, (int)strlenDx(dat.string), dat.fonthandle) / 2.);	//中心座標から左端の座標に変換
			float y = (float)(dat.y - GetFontAscentToHandle(dat.fonthandle) / 2.);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
			DrawStringFToHandle((float)x, (float)(y - val * 20), dat.string, dat.Color, dat.fonthandle);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

//フライテキストの計算処理
void FlyText::Update() {
	for (auto &dat : FlyTextData) {
		if (dat.Enable) {
			dat.Count++;	//カウントを加算する
			if (dat.Limit < dat.Count) {
				//期限が来た場合はフライテキストを無効にする
				dat.Enable = FALSE;
			}
		}
	}
}

//フライテキストの全無効化
void FlyText::AllDelete() {
	for (auto dat : FlyTextData)	dat.Enable = FALSE;
}