#pragma once
//enum定義
//命名規則："enum名"+_+"大文字で始まる要素名"

////キーバインド
//enum KEYBIND {
//	KEYBIND_SELECT,			//項目の決定
//	KEYBIND_PAUSE,			//キャンセル/ポーズ
//	KEYBIND_ROTAL,			//落下するブロックを反時計回りに回転させる
//	KEYBIND_ROTAR,			//落下するブロックを時計回りに回転させる
//	KEYBIND_UP,				//項目選択:上
//	KEYBIND_DOWN,			//項目選択:下/落下するブロックの加速
//	KEYBIND_LEFT,			//項目選択:左/落下するブロックの左移動
//	KEYBIND_RIGHT,			//項目選択:右/落下するブロックの右移動
//	KEYBIND_NUM				//キーバインドの数
//};
//
////フェーズ関係
//enum FAZE {
//	FAZE_Nothing,				//何も無し
//	FAZE_TopMenu,				//トップメニュー
//	FAZE_GameMain,				//実際のゲームプレイ画面
//	FAZE_Manual,				//説明書画面
//	FAZE_NUM					//フェーズの数
//};
//
////アナログスティックの操作モードいるか？
//enum ANALOGSTICKMODE {
//	ANALOGSTICKMODE_NOMAL,	//使用する[倒し具合に応じて速さを変更する]
//	ANALOGSTICKMODE_VECTOR,	//使用する[角度のみ取得し速さは一定にする]
//	ANALOGSTICKMODE_NOUSE,	//使用しない
//	ANALOGSTICKMODE_NUM		//要素の個数
//};
//
//
////フォントの種類
////追加の命名規則："大文字で始まる要素名"の部分は"フォント名_フォントの設定(エッジ付き、フォントサイズなど)"になっています
//enum FONTTYPE {
//	FONTTYPE_GenJyuuGothicLHeavy_Edge25,	//源桑ゴシックL Heavyエッジ付きサイズ25
//	FONTTYPE_GenJyuuGothicLHeavy_Edge30,	//源桑ゴシックL Heavyエッジ付きサイズ30
//	FONTTYPE_GenJyuuGothicLHeavy_Edge35,	//源桑ゴシックL Heavyエッジ付きサイズ35
//	FONTTYPE_GenJyuuGothicLHeavy_Edge40,	//源桑ゴシックL Heavyエッジ付きサイズ40
//	FONTTYPE_GenJyuuGothicLHeavy_Edge50,	//源桑ゴシックL Heavyエッジ付きサイズ40
//	FONTTYPE_GenJyuuGothicLHeavy_Edge60,	//源桑ゴシックL Heavyエッジ付きサイズ60
//	FONTTYPE_GenJyuuGothicLHeavy_Edge70,	//源桑ゴシックL Heavyエッジ付きサイズ70
//	FONTTYPE_GenJyuuGothicLHeavy_Edge80,	//源桑ゴシックL Heavyエッジ付きサイズ80
//
//	FONTTYPE_SFSquareHeadCondensed_Edge15,	//SF Square Head Condensedエッジ付きサイズ15
//	FONTTYPE_SFSquareHeadCondensed_Edge25,	//SF Square Head Condensedエッジ付きサイズ25
//	FONTTYPE_SFSquareHeadCondensed_Edge35,	//SF Square Head Condensedエッジ付きサイズ35
//	FONTTYPE_SFSquareHeadCondensed_Edge45,	//SF Square Head Condensedエッジ付きサイズ45
//};

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
	SE_TYPE_Smallexplosion,		////小爆発の効果音
	SE_TYPE_NUM					//効果音の個数(指定した場合は効果音無し)
};

//ブロックの種類
enum BLOCK_TYPE {
	BLOCK_TYPE_NO,//なし
	BLOCK_TYPE_RED,//赤
	BLOCK_TYPE_BLUE,//青
	BLOCK_TYPE_YELLOW,//黄
	BLOCK_TYPE_GREEN,//緑
	BLOCK_TYPE_PURPLE,//紫
	/*ここから特殊ブロック↓*/
	BLOCK_TYPE_RED_ARROW_X,		//赤(平行矢印)
	BLOCK_TYPE_RED_ARROW_Y,		//赤(垂直矢印)
	BLOCK_TYPE_RED_ARROW_XY,	//赤(斜め右上)
	BLOCK_TYPE_RED_ARROW_XY2,	//赤(斜め右下)
	BLOCK_TYPE_BLUE_ARROW_X,	//青(平行矢印)
	BLOCK_TYPE_BLUE_ARROW_Y,	//青(垂直矢印)
	BLOCK_TYPE_BLUE_ARROW_XY,	//青(斜め右上)
	BLOCK_TYPE_BLUE_ARROW_XY2,	//青(斜め右下)
	BLOCK_TYPE_YELLOW_ARROW_X,	//黄(平行矢印)
	BLOCK_TYPE_YELLOW_ARROW_Y,	//黄(垂直矢印)
	BLOCK_TYPE_YELLOW_ARROW_XY,	//黄(斜め右上)
	BLOCK_TYPE_YELLOW_ARROW_XY2,//黄(斜め右下)
	BLOCK_TYPE_GREEN_ARROW_X,	//緑(平行矢印)
	BLOCK_TYPE_GREEN_ARROW_Y,	//緑(垂直矢印)
	BLOCK_TYPE_GREEN_ARROW_XY,	//緑(斜め右上)
	BLOCK_TYPE_GREEN_ARROW_XY2,	//緑(斜め右下)
	BLOCK_TYPE_PURPLE_ARROW_X,	//紫(平行矢印)
	BLOCK_TYPE_PURPLE_ARROW_Y,	//紫(垂直矢印)
	BLOCK_TYPE_PURPLE_ARROW_XY,	//紫(斜め右上)
	BLOCK_TYPE_PURPLE_ARROW_XY2,//紫(斜め右下)
	BLOCK_TYPE_TREE,		//樹木の形のブロック（隣接する４方向のどこかが消えたときに一緒に消える）
	BLOCK_TYPE_BLACK,		//黒色のブロック：置くまで色がわからない→おいたときにランダムで色が決定する
	BLOCK_TYPE_NOROUND,		//枠で囲われたブロック（回せない）
	BLOCK_TYPE_RAINBOW,		//虹色のブロック(下のブロックと同じ色になる)
	BLOCK_TYPE_BOM,			//爆弾(問答無用で周囲のブロック破壊)
	BLOCK_TYPE_2BOM,		//2爆弾(2ブロック隣接で消去する)
	BLOCK_TYPE_BOM_Color,	//同色爆弾(真下と同色のブロックを消去する)
	BLOCK_TYPE_NUM			//ブロックの種類の数(画面外ブロック)
};

//ブロック変化モーションの種類
enum BlockChangeMotionType {
	BlockChangeMotionType_NO,		//モーション無し
	BlockChangeMotionType_NOMAL,	//通常(fromからtoへ)
	BlockChangeMotionType_EXPLOSION,//爆発(消滅)
	BlockChangeMotionType_SMALL,	//小さくなって消える
};