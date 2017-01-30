#include "Block.h"
#include "MainFunc.h"
#include "Tex_Block.h"

Block::Block() { }


Block::~Block() { }

//初期化処理(計算処理)
void Block::Init_Update() {
	printLog_I(_T("Blockクラスの初期化(計算)"));
}

//初期化処理(描画処理)
void Block::Init_Draw() {

	printLog_I(_T("Blockクラスの初期化(描画)"));
}

//描画処理
void Block::Draw() {
	if (color == BLOCK_TYPE_NO)	return;
	Draw(((Phase_GameMain*)phaseController.getInstance())->getTex_Block()->getTexture(color), 1);
}

//描画処理(詳細設定)
void Block::Draw(int grHandle, double scale) {
	float Scale = (float)scale;
	Draw(DrawPlaceX, DrawPlaceY, grHandle, scale);
}

//描画処理(詳細設定2)
void Block::Draw(double centerX, double centerY, int grHandle, double scale) {
	float Scale = (float)scale;
	DrawRectRotaGraphFast2((int)centerX, (int)centerY, 0, 0,
		BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
		(float)Scale, 0, grHandle, TRUE, FALSE);
}

//ブロックの削除(TRUEで削除)
int Block::Delete_Block() {
	if (color == BLOCK_TYPE_NO || color == BLOCK_TYPE_NUM) {
		//そもそもブロックデータがない
		return FALSE;
	}

	//ブロックデータをブロック無しにする
	color = BLOCK_TYPE_NO;
	return TRUE;
}

//現在のブロックの種類を取得する
BLOCK_TYPE Block::getBlockType() {
	return color;
}

//現在のブロックのテクスチャハンドルを取得する
int Block::getBlockTexture() {
	return ((Phase_GameMain*)phaseController.getInstance())->getTex_Block()->getTexture(color);
}

//ブロックを設置する
/*
type:		設置するブロックの種類
override:	TRUEですでにブロックがおいてあっても設置する
before:		前に設置されていたブロック(NULL可能)
戻り値:		TRUEで設置成功
*/
int Block::addBlcok(BLOCK_TYPE type, int override, BLOCK_TYPE *before) {
	//現在のブロックの種類を取得する
	const BLOCK_TYPE NowType = color;

	//現在のブロック情報を代入しとく
	if (before != NULL)	*before = NowType;

	if (override == FALSE) {
		//上書きが無効な場合はブロックがすでに存在したら何もしない
		if (NowType != BLOCK_TYPE_NO)	return FALSE;
	}

	if (type == BLOCK_TYPE_NO || type == BLOCK_TYPE_NUM) {
		//設置不可ブロックなので、設置しない
		return FALSE;
	}

	//ブロックの設置
	color = type;

	return TRUE;//成功
}

//描画に必要な情報を更新する(描画する中心座標)
void Block::Update_DrawData(double drawPlaceX, double drawPlaceY) {
	DrawPlaceX = drawPlaceX;
	DrawPlaceY = drawPlaceY;
}

//描画位置Xを取得する
double Block::getDrawPlaceX() {
	return DrawPlaceX;
}

//描画位置Yを取得する
double Block::getDrawPlaceY() {
	return DrawPlaceY;
}

//指定した2個のブロックが同色ブロックかどうかの取得(TRUEで同色)(OnlyColorBlockをTRUEで色ブロックのみで判定する)
int Block::isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int OnlyColorBlock) {
	if (OnlyColorBlock) {//簡略計算でないとき
		//色の概念の無いブロックの場合
		if (type1 == BLOCK_TYPE_NO)			return FALSE;
		if (type1 == BLOCK_TYPE_TREE)		return FALSE;
		if (type1 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type1 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type1 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type1 == BLOCK_TYPE_BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_2BOM)		return FALSE;
		if (type1 == BLOCK_TYPE_BOM_Color)	return FALSE;
		if (type1 == BLOCK_TYPE_NUM)		return FALSE;

		if (type2 == BLOCK_TYPE_NO)			return FALSE;
		if (type2 == BLOCK_TYPE_TREE)		return FALSE;
		if (type2 == BLOCK_TYPE_BLACK)		return FALSE;
		if (type2 == BLOCK_TYPE_NOROUND)	return FALSE;
		if (type2 == BLOCK_TYPE_RAINBOW)	return FALSE;
		if (type2 == BLOCK_TYPE_BOM)		return FALSE;
		if (type2 == BLOCK_TYPE_2BOM)		return FALSE;
		if (type2 == BLOCK_TYPE_BOM_Color)	return FALSE;
		if (type2 == BLOCK_TYPE_NUM)		return FALSE;
	}

	//同色判定(同一ブロックの場合)
	if (type1 == type2)	return TRUE;

	//同色判定(基本ブロックに直して考えます)
	switch (type1) {
	case BLOCK_TYPE_RED_ARROW_X:
	case BLOCK_TYPE_RED_ARROW_Y:
	case BLOCK_TYPE_RED_ARROW_XY:
	case BLOCK_TYPE_RED_ARROW_XY2:
		type1 = BLOCK_TYPE_RED;
		break;
	case BLOCK_TYPE_BLUE_ARROW_X:
	case BLOCK_TYPE_BLUE_ARROW_Y:
	case BLOCK_TYPE_BLUE_ARROW_XY:
	case BLOCK_TYPE_BLUE_ARROW_XY2:
		type1 = BLOCK_TYPE_BLUE;
		break;
	case BLOCK_TYPE_YELLOW_ARROW_X:
	case BLOCK_TYPE_YELLOW_ARROW_Y:
	case BLOCK_TYPE_YELLOW_ARROW_XY:
	case BLOCK_TYPE_YELLOW_ARROW_XY2:
		type1 = BLOCK_TYPE_YELLOW;
		break;
	case BLOCK_TYPE_GREEN_ARROW_X:
	case BLOCK_TYPE_GREEN_ARROW_Y:
	case BLOCK_TYPE_GREEN_ARROW_XY:
	case BLOCK_TYPE_GREEN_ARROW_XY2:
		type1 = BLOCK_TYPE_GREEN;
		break;
	case BLOCK_TYPE_PURPLE_ARROW_X:
	case BLOCK_TYPE_PURPLE_ARROW_Y:
	case BLOCK_TYPE_PURPLE_ARROW_XY:
	case BLOCK_TYPE_PURPLE_ARROW_XY2:
		type1 = BLOCK_TYPE_PURPLE;
		break;
	}
	switch (type2) {
	case BLOCK_TYPE_RED_ARROW_X:
	case BLOCK_TYPE_RED_ARROW_Y:
	case BLOCK_TYPE_RED_ARROW_XY:
	case BLOCK_TYPE_RED_ARROW_XY2:
		type2 = BLOCK_TYPE_RED;
		break;
	case BLOCK_TYPE_BLUE_ARROW_X:
	case BLOCK_TYPE_BLUE_ARROW_Y:
	case BLOCK_TYPE_BLUE_ARROW_XY:
	case BLOCK_TYPE_BLUE_ARROW_XY2:
		type2 = BLOCK_TYPE_BLUE;
		break;
	case BLOCK_TYPE_YELLOW_ARROW_X:
	case BLOCK_TYPE_YELLOW_ARROW_Y:
	case BLOCK_TYPE_YELLOW_ARROW_XY:
	case BLOCK_TYPE_YELLOW_ARROW_XY2:
		type2 = BLOCK_TYPE_YELLOW;
		break;
	case BLOCK_TYPE_GREEN_ARROW_X:
	case BLOCK_TYPE_GREEN_ARROW_Y:
	case BLOCK_TYPE_GREEN_ARROW_XY:
	case BLOCK_TYPE_GREEN_ARROW_XY2:
		type2 = BLOCK_TYPE_GREEN;
		break;
	case BLOCK_TYPE_PURPLE_ARROW_X:
	case BLOCK_TYPE_PURPLE_ARROW_Y:
	case BLOCK_TYPE_PURPLE_ARROW_XY:
	case BLOCK_TYPE_PURPLE_ARROW_XY2:
		type2 = BLOCK_TYPE_PURPLE;
		break;
	}
	//同色判定
	if (type1 == type2)	return TRUE;

	return FALSE;
}

//有効かどうかの取得
int Block::isEnable() {
	if (color == BLOCK_TYPE_NO || color == BLOCK_TYPE_NUM) {
		//無効ブロック
		return FALSE;
	}
	return TRUE;
}