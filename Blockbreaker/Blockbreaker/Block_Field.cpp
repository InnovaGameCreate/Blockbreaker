#include "Tex_Block.h"
#include "Block_Field.h"
#include "MainFunc.h"
//フィールド用のブロッククラス

Block_Field::Block_Field() {

}


Block_Field::~Block_Field() {

}

//初期化(計算処理)
void Block_Field::Init_Update() {
	Block::Init_Update();

	Restart();
}

//初期化(描画処理)
void Block_Field::Init_Draw() {

}

//描画
void Block_Field::Draw() {

	switch (blockChangeMotion.getType()) {
	case BlockChangeMotionType_NO:
		//変化モーション無しの場合は無難に描画する
		Block::Draw();
		break;
	case BlockChangeMotionType_NOMAL:
		//普通の変化モーション(モーション前は普通に描画されます)

		//変化前のブロックを描画する
		Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), 1);
		//変化量に応じて半透明で描画する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(blockChangeMotion.getChangeVal() * 255));
		Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_To()), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	case BlockChangeMotionType_EXPLOSION:
		//爆発(シェーダに頑張ってもらう)
		if (blockChangeMotion.getCount() < 0) {//モーション前は普通に描画
			Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), 1);
		}
		else {
			ShaderBackGround_DeleteBlock(getDrawPlaceX(), getDrawPlaceY(), blockChangeMotion.getChangeVal()
				, phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), phase_GameMain.getTex_Block()->getFireEffect(), phase_GameMain.getTex_Block()->getFireEffect2());
		}
		break;
	case BlockChangeMotionType_SMALL:
		//小さくなる(モーション前は普通に描画されます)
		Block::Draw(phase_GameMain.getTex_Block()->getTexture(blockChangeMotion.getBlockType_From()), (float)(1 - blockChangeMotion.getChangeVal()));

		break;
	}
}

//リスタート時の初期化
void Block_Field::Restart() {
	//基本削除を行う
	Delete_Block();
	Delete_ChangeMotion();
	Delete_MoveMotion();
}

void Block_Field::Update_DrawData(double paddingX, double paddingY, int x, int y) {
	double plintX, pointY;

	//移動モーションが有効な場合は移動モーションの座標を使用する
	if (blockMoveMotion.isEnable()) {
		plintX = blockMoveMotion.getPointX();
		pointY = blockMoveMotion.getPointY();
	}
	else {
		//通常時
		Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &plintX, &pointY);
	}

	Block::Update_DrawData(plintX + paddingX, pointY + paddingY);
}

//変化モーションの削除
void Block_Field::Delete_ChangeMotion() {
	blockChangeMotion.Delete();
}

//移動モーションの削除
void Block_Field::Delete_MoveMotion() {
	blockMoveMotion.Delete();
}

//ブロックの座標？からインゲームの座標を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
void Block_Field::Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE + XVal*BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE + YVal*BLOCK_SIZE;
	}
}

//移動モーションのクラスのポインタを取得
BlockMoveMotion *Block_Field::getMoveMotion() {
	return &blockMoveMotion;
}

//変化モーションのクラスのポインタを取得
BlockChangeMotion *Block_Field::getChangeMotion() {
	return &blockChangeMotion;
}

