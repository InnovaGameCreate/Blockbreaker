#pragma once
//構造体宣言用

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//構造体
//typedefするのはプログラム全体で使用するもののみにしてください。
//ファイル内でのみ使用する構造体はtypedefしないでください。(補完で出てきてうざいので)
//ブロック画像
typedef struct {
	int Tex_BlockBack;				//背景ブロック(ブロックの色をなるだけ正確に表示するための背景画像)
	int Tex_BlockRED;				//赤ブロック
	int Tex_BlockRED_ARROW_X;		//赤ブロック(平行矢印)
	int Tex_BlockRED_ARROW_Y;		//赤ブロック(垂直矢印)
	int Tex_BlockRED_ARROW_XY;		//赤ブロック(斜め右上)
	int Tex_BlockRED_ARROW_XY2;		//赤ブロック(斜め右下)
	int Tex_BlockBLUE;				//青ブロック
	int Tex_BlockBLUE_ARROW_X;		//青ブロック(平行矢印)
	int Tex_BlockBLUE_ARROW_Y;		//青ブロック(垂直矢印)
	int Tex_BlockBLUE_ARROW_XY;		//青ブロック(斜め右上)
	int Tex_BlockBLUE_ARROW_XY2;	//青ブロック(斜め右下)
	int Tex_BlockYELLOW;			//黄色ブロック
	int Tex_BlockYELLOW_ARROW_X;	//黄色ブロック(平行矢印)
	int Tex_BlockYELLOW_ARROW_Y;	//黄色ブロック(垂直矢印)
	int Tex_BlockYELLOW_ARROW_XY;	//黄色ブロック(斜め右上)
	int Tex_BlockYELLOW_ARROW_XY2;	//黄色ブロック(斜め右下)
	int Tex_BlockGREEN;				//緑ブロック
	int Tex_BlockGREEN_ARROW_X;		//緑ブロック(平行矢印)
	int Tex_BlockGREEN_ARROW_Y;		//緑ブロック(垂直矢印)
	int Tex_BlockGREEN_ARROW_XY;	//緑ブロック(斜め右上)
	int Tex_BlockGREEN_ARROW_XY2;	//緑ブロック(斜め右下)
	int Tex_BlockPURPLE;			//紫ブロック
	int Tex_BlockPURPLE_ARROW_X;	//紫ブロック(平行矢印)
	int Tex_BlockPURPLE_ARROW_Y;	//紫ブロック(垂直矢印)
	int Tex_BlockPURPLE_ARROW_XY;	//紫ブロック(斜め右上)
	int Tex_BlockPURPLE_ARROW_XY2;	//紫ブロック(斜め右下)
	int Tex_BlockTREE;				//樹木の形ブロック
	int Tex_BlockBLACK;				//黒ブロック
	int Tex_BlockRAINBOW;			//虹色ブロック
	int Tex_BlockBOMB;				//爆弾ブロック
	int Tex_Block2BOMB;				//2爆弾ブロック
	int Tex_BlockBOMB_Color;		//同色爆弾ブロック
	int Tex_BlockFireEffect;		//炎エフェクトブロック
	int Tex_BlockFireEffect2;		//炎エフェクトブロック2(炭)
	int Tex_BlockCenterEffect;		//回転の中心であることを分かるようにするエフェクト
}BlockTexData;
