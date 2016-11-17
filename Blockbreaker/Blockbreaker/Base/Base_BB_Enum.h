#pragma once
//enum定義
//命名規則："enum名"+_+"大文字で始まる要素名"

//キーバインド
enum KEYBIND {
	KEYBIND_SELECT,			//項目の決定
	KEYBIND_PAUSE,			//キャンセル/ポーズ
	KEYBIND_ROTAL,			//落下するブロックを反時計回りに回転させる
	KEYBIND_ROTAR,			//落下するブロックを時計回りに回転させる
	KEYBIND_UP,				//項目選択:上
	KEYBIND_DOWN,			//項目選択:下/落下するブロックの加速
	KEYBIND_LEFT,			//項目選択:左/落下するブロックの左移動
	KEYBIND_RIGHT,			//項目選択:右/落下するブロックの右移動
	KEYBIND_NUM				//キーバインドの数
};

//フェーズ関係
enum FAZE {
	FAZE_Nothing,				//何も無し
	FAZE_TopMenu,				//トップメニュー
	FAZE_GameMain,				//実際のゲームプレイ画面
	FAZE_Manual,				//説明書画面
	FAZE_NUM					//フェーズの数
};

//アナログスティックの操作モードいるか？
enum ANALOGSTICKMODE {
	ANALOGSTICKMODE_NOMAL,	//使用する[倒し具合に応じて速さを変更する]
	ANALOGSTICKMODE_VECTOR,	//使用する[角度のみ取得し速さは一定にする]
	ANALOGSTICKMODE_NOUSE,	//使用しない
	ANALOGSTICKMODE_NUM		//要素の個数
};

//スレッド
enum THREAD {
	THREAD_Draw,			//描画スレッド
	THREAD_Update			//処理スレッド
};

//フォントの種類
//追加の命名規則："大文字で始まる要素名"の部分は"フォント名_フォントの設定(エッジ付き、フォントサイズなど)"になっています
enum FONTTYPE {
	FONTTYPE_GenJyuuGothicLHeavy_Edge25,	//源桑ゴシックL Heavyエッジ付きサイズ25
	FONTTYPE_GenJyuuGothicLHeavy_Edge30,	//源桑ゴシックL Heavyエッジ付きサイズ30
	FONTTYPE_GenJyuuGothicLHeavy_Edge35,	//源桑ゴシックL Heavyエッジ付きサイズ35
	FONTTYPE_GenJyuuGothicLHeavy_Edge40,	//源桑ゴシックL Heavyエッジ付きサイズ40
	FONTTYPE_GenJyuuGothicLHeavy_Edge50,	//源桑ゴシックL Heavyエッジ付きサイズ40
	FONTTYPE_GenJyuuGothicLHeavy_Edge60,	//源桑ゴシックL Heavyエッジ付きサイズ60
	FONTTYPE_GenJyuuGothicLHeavy_Edge70,	//源桑ゴシックL Heavyエッジ付きサイズ70
	FONTTYPE_GenJyuuGothicLHeavy_Edge80,	//源桑ゴシックL Heavyエッジ付きサイズ80

	FONTTYPE_SFSquareHeadCondensed_Edge15,	//SF Square Head Condensedエッジ付きサイズ15
	FONTTYPE_SFSquareHeadCondensed_Edge25,	//SF Square Head Condensedエッジ付きサイズ25
	FONTTYPE_SFSquareHeadCondensed_Edge35,	//SF Square Head Condensedエッジ付きサイズ35
	FONTTYPE_SFSquareHeadCondensed_Edge45,	//SF Square Head Condensedエッジ付きサイズ45
};