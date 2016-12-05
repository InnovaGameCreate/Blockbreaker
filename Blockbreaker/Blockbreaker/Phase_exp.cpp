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
	if (getKeyBind(KEYBIND_SELECT) == 1) phaseController.ChangefazeRequest(FAZE_TopMenu,0);
}

void Phase_exp::Init_Draw()
{
	tex_exp = LoadGraph(_T("Data/image/colorbom.png"));	//取説の画像貼り付けてください
	if (tex_exp == -1) printLog_E(_T("ファイルの読み込みの失敗[取説]"));
	Sleep(500);
}