#pragma once
#include "Enum.h"
#include "Tex_Block.h"

#include <string>
//ブロックの親クラス

class Block
{
public:
	Block();
	~Block();
	void Init_Update();	//初期化処理(計算処理)
	void Init_Draw();						//初期化処理(描画処理)

	void Draw();															//描画処理
	void Draw(int grHandle, double scale);									//描画処理(テクスチャ指定)
	static void Draw(double centerX, double centerY, int grHandle, double scale);	//描画処理(詳細設定2)

	void Update_DrawData(double drawPlaceX, double drawPlaceY);	//描画に必要な情報を設定する

	int addBlcok(BLOCK_TYPE type, int Override, BLOCK_TYPE *Before = NULL);	//ブロックを設置する

	int Delete_Block();				//ブロックの削除(TRUEで削除)

	BLOCK_TYPE getBlockType();		//現在のブロックの種類を取得する
	int getBlockTexture();			//現在のブロックのテクスチャハンドルを取得する

	static int isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int OnlyColorBlock);
	int isEnable();		//有効かどうかの取得
protected:
	double getDrawPlaceX();		//描画位置Xを取得する
	double getDrawPlaceY();		//描画位置Yを取得する

private:

	BLOCK_TYPE color;				//ブロックの種類
	double DrawPlaceX, DrawPlaceY;	//描画位置[インゲーム座標](マルチだと描画位置がずれる問題があったので)

};