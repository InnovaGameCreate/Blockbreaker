#pragma once

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//定数・マクロ
//命名規則：定数はすべて大文字、単語と単語の間は_で区切る

//デバッグ設定の定義(使用しない場合はコメントアウト)
#ifdef DEBUG
//#define _DEBUG_GAMEMAIN_			//ゲームメインのデバッグ
#endif // DEBUG

#define PI (acos(-1.0))				//円周率
#define PIf ((float)acos(-1.0))		//円周率(float)

#define GAMEVERSION _T("0.3")		//バージョン名

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))	//配列の長さを求める

#define WINDOW_WIDTH 1280			//画面の横幅
#define WINDOW_HEIGHT 960			//画面の高さ
#define FPS_DRAW 60					//描画フレームレート
#define FPS_UPDATE 60				//計算フレームレート
#define TITLE _T("Blockbreaker")	//ウィンドウタイトル

static const int BLOCK_SIZE = 40;			//ブロックの縦横のピクセルサイズ
static const int BLOCK_WIDTHNUM = 11;		//実際のブロックの横の個数
static const int BLOCK_HEIGHTNUM = 24;		//実際のブロックの縦の個数
static const int BLOCK_PADDINGUP = 1;		//描画するブロックの開始位置(上)
static const int BLOCK_PADDINGDOWN = 1;		//描画するブロックの開始位置(下)
static const int BLOCK_PADDINGLEFT = 0;		//描画するブロックの開始位置(左)
static const int BLOCK_PADDINGRIGHT = 0;	//描画するブロックの開始位置(右)
static const int BLOCK_WIDTHNUM_INGAME = BLOCK_WIDTHNUM - (BLOCK_PADDINGLEFT + BLOCK_PADDINGRIGHT);		//画面内の横のブロックの個数
static const int BLOCK_HEIGHTNUM_INGAME = BLOCK_HEIGHTNUM - (BLOCK_PADDINGUP + BLOCK_PADDINGDOWN);		//画面内の縦のブロックの個数

static const int GAMEWINDOW_PADDINGX = 70;	//ゲーム画面のX方向のズレ
static const int GAMEWINDOW_PADDINGY = 40;	//ゲーム画面のY方向のズレ
static const int GAMEWINDOW_WIDTH = BLOCK_WIDTHNUM_INGAME*BLOCK_SIZE;	//ゲーム画面の横幅
static const int GAMEWINDOW_HEIGHT = BLOCK_HEIGHTNUM_INGAME*BLOCK_SIZE;	//ゲーム画面の高さ

static const int FALLBLOCK_SIZE = 3;		//落下するブロックの大きさ
static const int GAMEOVER_BORDER = 5;		//ゲームオーバーにする場所
static const int FALLBLOCK_CENTER = FALLBLOCK_SIZE / 2;	//落下するブロックの中心(基準)位置
static const int BLOCK_DELETE_LEN = 4;			//削除するために必要な隣接するブロックの個数
static const int BLOCK_DEFAULT_VAL = 6;			//ブロックの初期積載量

/*各スコア*/
static const int SCORE_DEL_ARROW = 50;	//矢印ブロックによって消去された時のスコア
static const int SCORE_DEL_NOMAL = 100;	//普通に消えた
static const int SCORE_DEL_OPTION = 80;	//隣接ブロックとして消えた