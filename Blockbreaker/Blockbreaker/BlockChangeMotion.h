#pragma once
//ブロック変化モーションのデータ
#include "Enum.h"


class BlockChangeMotion
{
public:
	BlockChangeMotion();
	~BlockChangeMotion();

	void Update();		//計算処理

	int Create(BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay);		//変化モーションの設定

	void Delete();		//変化モーションの削除

	int isEnable();						//変化モーションが有効かどうかの取得
	BlockChangeMotionType getType();	//変化モーションの種類を取得する
	BLOCK_TYPE getBlockType_From();		//変化元ブロックの種類を取得する
	BLOCK_TYPE getBlockType_To();		//変化先ブロックの種類を取得する
	double getChangeVal();				//変化の割合を取得する
	int getCount();						//カウントの取得
private:
	BlockChangeMotionType Type;	//ブロック変化モーションの種類
	BLOCK_TYPE From;			//ブロック変化元ブロック
	BLOCK_TYPE To;				//ブロック変化先ブロック
	int Count;					//ブロック変化カウント(0起算)
	int Length;					//ブロック変化モーションを行う時間
};

