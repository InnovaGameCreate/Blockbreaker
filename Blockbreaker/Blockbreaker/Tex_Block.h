#pragma once
class Tex_Block
{
public:
	Tex_Block();
	~Tex_Block();
	void Init_Draw();			//描画の初期化
	void Finalize_Draw();		//終了処理

	int getTexture(BLOCK_TYPE type);	//ブロックタイプよりテクスチャハンドルの取得
	/*ブロックタイプの存在しないテクスチャの取得*/
	int getFireEffect();				//炎エフェクト取得
	int getFireEffect2();				//炎2エフェクト取得
	int getCenterEffect();				//ブロックの中央エフェクトの取得
	int getBack();						//背景ブロックの取得
private:
	int BlockBack;				//背景ブロック(ブロックの色をなるだけ正確に表示するための背景画像)
	int BlockRED;				//赤ブロック
	int BlockRED_ARROW_X;		//赤ブロック(平行矢印)
	int BlockRED_ARROW_Y;		//赤ブロック(垂直矢印)
	int BlockRED_ARROW_XY;		//赤ブロック(斜め右上)
	int BlockRED_ARROW_XY2;		//赤ブロック(斜め右下)
	int BlockBLUE;				//青ブロック
	int BlockBLUE_ARROW_X;		//青ブロック(平行矢印)
	int BlockBLUE_ARROW_Y;		//青ブロック(垂直矢印)
	int BlockBLUE_ARROW_XY;		//青ブロック(斜め右上)
	int BlockBLUE_ARROW_XY2;	//青ブロック(斜め右下)
	int BlockYELLOW;			//黄色ブロック
	int BlockYELLOW_ARROW_X;	//黄色ブロック(平行矢印)
	int BlockYELLOW_ARROW_Y;	//黄色ブロック(垂直矢印)
	int BlockYELLOW_ARROW_XY;	//黄色ブロック(斜め右上)
	int BlockYELLOW_ARROW_XY2;	//黄色ブロック(斜め右下)
	int BlockGREEN;				//緑ブロック
	int BlockGREEN_ARROW_X;		//緑ブロック(平行矢印)
	int BlockGREEN_ARROW_Y;		//緑ブロック(垂直矢印)
	int BlockGREEN_ARROW_XY;	//緑ブロック(斜め右上)
	int BlockGREEN_ARROW_XY2;	//緑ブロック(斜め右下)
	int BlockPURPLE;			//紫ブロック
	int BlockPURPLE_ARROW_X;	//紫ブロック(平行矢印)
	int BlockPURPLE_ARROW_Y;	//紫ブロック(垂直矢印)
	int BlockPURPLE_ARROW_XY;	//紫ブロック(斜め右上)
	int BlockPURPLE_ARROW_XY2;	//紫ブロック(斜め右下)
	int BlockTREE;				//樹木の形ブロック
	int BlockBLACK;				//黒ブロック
	int BlockRAINBOW;			//虹色ブロック
	int BlockBOMB;				//爆弾ブロック
	int Block2BOMB;				//2爆弾ブロック
	int BlockBOMB_Color;		//同色爆弾ブロック
	int BlockFireEffect;		//炎エフェクトブロック
	int BlockFireEffect2;		//炎エフェクトブロック2(炭)
	int BlockCenterEffect;		//回転の中心であることを分かるようにするエフェクト
};