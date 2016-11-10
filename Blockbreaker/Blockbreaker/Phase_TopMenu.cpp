//トップメニュー関連

#include "MainFunc.h"


Phase_TopMenu::Phase_TopMenu() {
}


Phase_TopMenu::~Phase_TopMenu() {
}

//描画処理の初期化
void Phase_TopMenu::Init_Draw() {

}

//計算処理の初期化
void Phase_TopMenu::Init_Update() {

}

//描画処理
void Phase_TopMenu::Draw() {
	ClearDrawScreen();//描画内容の削除

}

//計算処理
void Phase_TopMenu::Update() {
	Key();	//キー処理を行う
}

//描画の終了処理
void Phase_TopMenu::Finalize_Draw() {

}

//計算の終了処理
void Phase_TopMenu::Finalize_Update() {

}

//キー処理
void Phase_TopMenu::Key() {
	if (getKeyBind(KEYBIND_SELECT) == 1) {
		//決定キーが押された時
		Changefaze(FAZE_GameMain, THREAD_Update);//フェーズ変更
	}
	else if (getKeyBind(KEYBIND_PAUSE) == 1) {
		//終了
		ExitGameRequest();
	}
}