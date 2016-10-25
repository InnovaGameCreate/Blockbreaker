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
};

//効果音の種類
//エクスプローラーでwavファイルを見て探しやすいように"大文字で始まる要素名"は実際のファイル名と一致させています
enum SE_TYPE {
	SE_TYPE_ChangeSelect,		//項目の選択肢を移動する時の音
	SE_TYPE_DecisionSelect,		//項目を決定した時の音
	SE_TYPE_ButtonCancel,		//項目をキャンセルした時の音
	SE_TYPE_OwnBarrier,			//自分がバリアを発動したときの音
	SE_TYPE_OwnDeath,			//自分が死亡した時の音
	SE_TYPE_Bulletfire1,		//敵が弾幕を発射したときの音1(連続用？)
	SE_TYPE_Bulletfire2,		//敵が弾幕を発射したときの音2(長い)
	SE_TYPE_Bulletfire3,		//敵が弾幕を発射したときの音3(鈴)
	SE_TYPE_Bulletfire4,		//敵が弾幕を発射したときの音4(レーザー)
	SE_TYPE_Bulletfire5,		//敵が弾幕を発射したときの音5(太鼓)
	SE_TYPE_Bulletfire6,		//敵が弾幕を発射したときの音6(反射)
	SE_TYPE_Bulletfire7,		//敵が弾幕を発射したときの音7(レーザー予兆)
	SE_TYPE_Shotfire,			//自機がショットを発射したときの音
	SE_TYPE_Shotfire2,			//自機がショットを発射したときの音2
	SE_TYPE_Graze,				//自機がかすりを入れたときの音
	SE_TYPE_ShotHit,			//自機のショットが敵に当たったときの音
	SE_TYPE_ShotHit2,			//自機のショットが敵に当たったときの音2
	SE_TYPE_EnemyDeath,			//敵が死亡したときの音
	SE_TYPE_EnemyDeath2,		//敵が死亡したときの音2
	SE_TYPE_Pause,				//ボーズボタン
	SE_TYPE_Itemget,			//アイテムを取得したときの音
	SE_TYPE_PowerUp,			//パワーアップしたときの音
	SE_TYPE_Timeout,			//制限時間の音
	SE_TYPE_Timeout2,			//制限時間の音2
	SE_TYPE_Extend,				//1アップの音
	SE_TYPE_bomb_Muteki,		//無敵ボムの音
	SE_TYPE_Bonus,				//ボーナスの音
	SE_TYPE_GetBomb,			//ボム取得の音
	SE_TYPE_bomb_DamageFloor,	//ダメージ床ボムの音
	SE_TYPE_bomb_BarrierFloor,	//バリア床ボムの音
	SE_TYPE_ChargeUP,			//チャージ攻撃の段階UPの音
	SE_TYPE_ChargeOK,			//チャージ攻撃のリキャスト完了の音
	SE_TYPE_Charge1,			//チャージ攻撃1の効果音
	SE_TYPE_Charge2,			//チャージ攻撃2の効果音
	SE_TYPE_NUM					//効果音の個数(指定した場合は効果音無し)
};