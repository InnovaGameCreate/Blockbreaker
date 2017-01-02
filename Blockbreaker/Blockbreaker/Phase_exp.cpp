#include "MainFunc.h"


Phase_exp::Phase_exp()
{
	
}

void Phase_exp::Draw()
{
	DrawGraph(0,0, tex_exp,FALSE);			//取説画像貼り付け
}

void Phase_exp::Update()
{

	//ゲームパッドかキーボードのキーが押されたときトップ画面へ戻る
	if (getKeyBind(KEYBIND_PAUSE) == 1) phaseController.ChangefazeRequest(FAZE_TopMenu, 0, 0);
}

//初期化(描画処理)
void Phase_exp::Init_Draw()
{
	tex_exp = LoadGraph(_T("Data/image/expWindow.png"));	//取説の画像貼り付けてください
	if (tex_exp == -1) printLog_E(_T("ファイルの読み込みの失敗[取説]"));
}

//終了処理(描画)
void Phase_exp::Fin_Draw() {
	DeleteGraph(tex_exp);
}