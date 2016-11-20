#include "Tex_Block.h"


Tex_Block::Tex_Block() {
}


Tex_Block::~Tex_Block() {
}

//描画の初期化
void Tex_Block::Init_Draw() {
	//ブロック画像
	if ((BlockRED = LoadGraph(_T("Data/Blocks/Block_RED.png"))) == -1)								printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED.png)"));
	if ((BlockRED_ARROW_X = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_X.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_X.png)"));
	if ((BlockRED_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_Y.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_Y.png)"));
	if ((BlockRED_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_XY.png)"));
	if ((BlockRED_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_RED_ARROW_XY2.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RED_ARROW_XY2.png)"));

	if ((BlockBLUE = LoadGraph(_T("Data/Blocks/Block_BLUE.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE.png)"));
	if ((BlockBLUE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_X.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_X.png)"));
	if ((BlockBLUE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_Y.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_Y.png)"));
	if ((BlockBLUE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_XY.png)"));
	if ((BlockBLUE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_BLUE_ARROW_XY2.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLUE_ARROW_XY2.png)"));

	if ((BlockYELLOW = LoadGraph(_T("Data/Blocks/Block_YELLOW.png"))) == -1)						printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW.png)"));
	if ((BlockYELLOW_ARROW_X = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_X.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_X.png)"));
	if ((BlockYELLOW_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_Y.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_Y.png)"));
	if ((BlockYELLOW_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_XY.png)"));
	if ((BlockYELLOW_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_YELLOW_ARROW_XY2.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_YELLOW_ARROW_XY2.png)"));

	if ((BlockGREEN = LoadGraph(_T("Data/Blocks/Block_GREEN.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN.png)"));
	if ((BlockGREEN_ARROW_X = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_X.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_X.png)"));
	if ((BlockGREEN_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_Y.png"))) == -1)			printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_Y.png)"));
	if ((BlockGREEN_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_XY.png)"));
	if ((BlockGREEN_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_GREEN_ARROW_XY2.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_GREEN_ARROW_XY2.png)"));

	if ((BlockPURPLE = LoadGraph(_T("Data/Blocks/Block_PURPLE.png"))) == -1)						printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE.png)"));
	if ((BlockPURPLE_ARROW_X = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_X.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_X.png)"));
	if ((BlockPURPLE_ARROW_Y = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_Y.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_Y.png)"));
	if ((BlockPURPLE_ARROW_XY = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY.png"))) == -1)		printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_XY.png)"));
	if ((BlockPURPLE_ARROW_XY2 = LoadGraph(_T("Data/Blocks/Block_PURPLE_ARROW_XY2.png"))) == -1)	printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_PURPLE_ARROW_XY2.png)"));

	if ((BlockTREE = LoadGraph(_T("Data/Blocks/Block_TREE.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_TREE.png)"));
	if ((BlockRAINBOW = LoadGraph(_T("Data/Blocks/Block_RAINBOW.png"))) == -1)						printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_RAINBOW.png)"));
	if ((BlockBOMB = LoadGraph(_T("Data/Blocks/Block_BOMB.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BOMB.png)"));
	if ((Block2BOMB = LoadGraph(_T("Data/Blocks/Block_2BOMB.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_2BOMB.png)"));
	if ((BlockBOMB_Color = LoadGraph(_T("Data/Blocks/Block_BOMB_Color.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BOMB_Color.png)"));
	if ((BlockBLACK = LoadGraph(_T("Data/Blocks/Block_BLACK.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_BLACK.png)"));


	if ((BlockBack = LoadGraph(_T("Data/Blocks/Block_Back.png"))) == -1)							printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_Back.png)"));
	if ((BlockFireEffect = LoadGraph(_T("Data/Blocks/Block_FireEffect.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_FireEffect.png)"));
	if ((BlockFireEffect2 = LoadGraph(_T("Data/Blocks/Block_FireEffect2.png"))) == -1)				printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_FireEffect2.png)"));
	if ((BlockCenterEffect = LoadGraph(_T("Data/Blocks/Block_CENTER.png"))) == -1)					printLog_E(_T("ファイルの読み込み失敗(Data/Blocks/Block_CENTER.png)"));
	
	printLog_I(_T("ブロック画像を読み込みました"));

}

//終了処理
void Tex_Block::Finalize_Draw() {
	DeleteGraph(BlockRED);
	DeleteGraph(BlockRED_ARROW_X);
	DeleteGraph(BlockRED_ARROW_Y);
	DeleteGraph(BlockRED_ARROW_XY);
	DeleteGraph(BlockRED_ARROW_XY2);
	DeleteGraph(BlockBLUE);
	DeleteGraph(BlockBLUE_ARROW_X);
	DeleteGraph(BlockBLUE_ARROW_Y);
	DeleteGraph(BlockBLUE_ARROW_XY);
	DeleteGraph(BlockBLUE_ARROW_XY2);
	DeleteGraph(BlockYELLOW);
	DeleteGraph(BlockYELLOW_ARROW_X);
	DeleteGraph(BlockYELLOW_ARROW_Y);
	DeleteGraph(BlockYELLOW_ARROW_XY);
	DeleteGraph(BlockYELLOW_ARROW_XY2);
	DeleteGraph(BlockGREEN);
	DeleteGraph(BlockGREEN_ARROW_X);
	DeleteGraph(BlockGREEN_ARROW_Y);
	DeleteGraph(BlockGREEN_ARROW_XY);
	DeleteGraph(BlockGREEN_ARROW_XY2);
	DeleteGraph(BlockPURPLE);
	DeleteGraph(BlockPURPLE_ARROW_X);
	DeleteGraph(BlockPURPLE_ARROW_Y);
	DeleteGraph(BlockPURPLE_ARROW_XY);
	DeleteGraph(BlockPURPLE_ARROW_XY2);
	DeleteGraph(BlockTREE);
	DeleteGraph(BlockBLACK);
	DeleteGraph(BlockRAINBOW);
	DeleteGraph(BlockFireEffect);
	DeleteGraph(BlockFireEffect2);
	DeleteGraph(BlockCenterEffect);
	DeleteGraph(BlockBOMB);
	DeleteGraph(Block2BOMB);
	DeleteGraph(BlockBOMB_Color);
	DeleteGraph(BlockBack);
}

//ブロックタイプよりテクスチャハンドルの取得
int Tex_Block::getTexture(BLOCK_TYPE type) {
	switch (type) {
	case BLOCK_TYPE_RED:	//赤ブロック
		return BlockRED;
	case BLOCK_TYPE_BLUE:	//青ブロック
		return BlockBLUE;
	case BLOCK_TYPE_GREEN:	//緑ブロック
		return BlockGREEN;
	case BLOCK_TYPE_PURPLE:	//紫ブロック
		return BlockPURPLE;
	case BLOCK_TYPE_RED_ARROW_X://赤(平行矢印)
		return BlockRED_ARROW_X;
	case BLOCK_TYPE_RED_ARROW_Y://赤(垂直矢印)
		return BlockRED_ARROW_Y;
	case BLOCK_TYPE_RED_ARROW_XY://赤(斜め右上)
		return BlockRED_ARROW_XY;
	case BLOCK_TYPE_RED_ARROW_XY2://赤(斜め右下)
		return BlockRED_ARROW_XY2;
	case BLOCK_TYPE_BLUE_ARROW_X://青(平行矢印)
		return BlockBLUE_ARROW_X;
	case BLOCK_TYPE_BLUE_ARROW_Y://青(垂直矢印)
		return BlockBLUE_ARROW_Y;
	case BLOCK_TYPE_BLUE_ARROW_XY://青(斜め右上)
		return BlockBLUE_ARROW_XY;
	case BLOCK_TYPE_BLUE_ARROW_XY2://青(斜め右下)
		return BlockBLUE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW_ARROW_X://黄(平行矢印)
		return BlockYELLOW_ARROW_X;
	case BLOCK_TYPE_YELLOW_ARROW_Y://黄(垂直矢印)
		return BlockYELLOW_ARROW_Y;
	case BLOCK_TYPE_YELLOW_ARROW_XY://黄(斜め右上)
		return BlockYELLOW_ARROW_XY;
	case BLOCK_TYPE_YELLOW_ARROW_XY2://黄(斜め右下)
		return BlockYELLOW_ARROW_XY2;
	case BLOCK_TYPE_GREEN_ARROW_X://緑(平行矢印)
		return BlockGREEN_ARROW_X;
	case BLOCK_TYPE_GREEN_ARROW_Y://緑(垂直矢印)
		return BlockGREEN_ARROW_Y;
	case BLOCK_TYPE_GREEN_ARROW_XY://緑(斜め右上)
		return BlockGREEN_ARROW_XY;
	case BLOCK_TYPE_GREEN_ARROW_XY2://緑(斜め右下)
		return BlockGREEN_ARROW_XY2;
	case BLOCK_TYPE_PURPLE_ARROW_X://紫(平行矢印)
		return BlockPURPLE_ARROW_X;
	case BLOCK_TYPE_PURPLE_ARROW_Y://紫(垂直矢印)
		return BlockPURPLE_ARROW_Y;
	case BLOCK_TYPE_PURPLE_ARROW_XY://紫(斜め右上)
		return BlockPURPLE_ARROW_XY;
	case BLOCK_TYPE_PURPLE_ARROW_XY2://紫(斜め右下)
		return BlockPURPLE_ARROW_XY2;
	case BLOCK_TYPE_YELLOW:	//黄色ブロック描画
		return BlockYELLOW;
	case BLOCK_TYPE_TREE:	//樹木ブロック
		return BlockTREE;
	case BLOCK_TYPE_BLACK:	//黒ブロック
		return BlockBLACK;
	case BLOCK_TYPE_RAINBOW://虹色ブロック
		return BlockRAINBOW;
	case BLOCK_TYPE_BOM://爆弾ブロック
		return BlockBOMB;
	case BLOCK_TYPE_2BOM://2爆弾ブロック
		return Block2BOMB;
	case BLOCK_TYPE_BOM_Color://同色爆弾ブロック
		return BlockBOMB_Color;
	}
	//printLog_E(_T("テクスチャ番号を取得できませんでした(BLOCK_TYPE=%d)"), type);
	return 0;
}

//炎エフェクト取得
int Tex_Block::getFireEffect() {
	return BlockFireEffect;
}

//炎2エフェクト取得
int Tex_Block::getFireEffect2() {
	return BlockFireEffect2;
}

//ブロックの中央エフェクトの取得
int Tex_Block::getCenterEffect() {
	return BlockCenterEffect;
}

//背景ブロックの取得
int Tex_Block::getBack() {
	return BlockBack;
}
