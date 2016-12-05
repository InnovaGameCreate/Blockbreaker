
//トップメニュー関連

#include "MainFunc.h"


Phase_TopMenu::Phase_TopMenu() {//要れた順番に0~ 1ずつ増える
	menu.addItem(_T("スタート"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	menu.addItem(_T("操作方法"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	menu.addItem(_T("ゲーム終了"), 5, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	menu.setScrolltype(1);
	menu.sethaba(50);
	menu.setCenteringMode(0);
}

Phase_TopMenu::~Phase_TopMenu() {}

//描画処理の初期化
void Phase_TopMenu::Init_Draw() {
	if ((Tex_backGround = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/image/colorbom.png)"));
	menu.setControlEnable(TRUE);
	menu.setEnable(TRUE);
}

//計算処理の初期化
void Phase_TopMenu::Init_Update() {

}

//描画処理
void Phase_TopMenu::Draw() {
	
	DrawGraph(0, 0, Tex_backGround, FALSE);


	menu.Draw();
}

//計算処理
void Phase_TopMenu::Update() {
	Key();	//キー処理を行う
	menu.Update();
}

//描画の終了処理
void Phase_TopMenu::Finalize_Draw() {

}

//計算の終了処理
void Phase_TopMenu::Finalize_Update() {

}

//キー処理
void Phase_TopMenu::Key() {

}

//ポーズメニューの項目が選択されたときに実行される
void Phase_TopMenu::SelectItem_menu::Event_Select(int No) {
	switch (No) {
	case 0:	//ゲームスタート
		phaseController.ChangefazeRequest(FAZE_GameMain, 0);//フェーズ変更
		break;
	case 1://説明画面に移行

		break;
	case 2://ゲーム終了
		ExitGameRequest();
		break;
	}
}