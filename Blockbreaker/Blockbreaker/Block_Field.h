#pragma once
#include "Tex_Block.h"
#include "Block.h"
#include "BlockMoveMotion.h"
#include "BlockChangeMotion.h"

//フィールド用のブロッククラス

class Block_Field : public Block
{
public:
	Block_Field();
	~Block_Field();
	void Init_Update();	//初期化(計算処理)
	void Init_Draw();				//初期化(描画処理)
	void Restart();					//リスタート時の初期化

	void Draw();			//描画

	void Update_DrawData(double paddingX, double paddingY, int x, int y);	//描画情報の更新

	/*削除系*/
	void Delete_ChangeMotion();	//変化モーションの削除
	void Delete_MoveMotion();	//移動モーションの削除


	BlockChangeMotion *getChangeMotion();	//変化モーションのクラスのポインタを取得
	BlockMoveMotion *getMoveMotion();		//移動モーションのクラスのポインタを取得

	static void Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double * IngameX, double * IngameY);
private:




	BlockMoveMotion blockMoveMotion;		//落下モーション
	BlockChangeMotion blockChangeMotion;	//ブロック変化モーション



};