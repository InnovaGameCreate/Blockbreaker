#pragma once
#include "Define.h"
#include "Block.h"

//落下ブロックのクラス

class Block_Fall
{
public:
	Block_Fall();
	~Block_Fall();

	void Draw();			//落下ブロックの描画処理
	void Draw_WaitLine();	//落下ブロック待機列の描画
	int Update();	//落下ブロックの計算処理(TRUEで落下完了した瞬間)
	void Update_DrawData(double paddingX, double paddingY);	//描画情報の更新
	void Key();		//キー処理
	void Restart();	//リスタート(初期化)

	int Create_FallBlock();	//落下ブロックを生成する(戻り値:成功でTRUE)
	int FallBlock_MoveX(int MoveVal, int CollisionFieldBlock = TRUE);		//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
	int getFallBlockVal_MoveX(int MoveVal, int CollisionFieldBlock = TRUE);	//落下ブロックがX軸方向に移動可能かどうかの取得(|移動出来る量|<=MoveVal)(つまり0で移動不可)
	int FallBlock_MoveY(int MoveVal, int CollisionFieldBlock = TRUE);		//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
	int FallBlock_Rotate(int RotaVal);										//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)

	int isEnable();		//落下ブロックが落下中かどうかの取得(落下中＝有効)
	int getInterval();	//落下ブロックのインターバルの取得(落下中の場合は-1が返ります)

private:
	//落下ブロックの待機列の情報
	struct FallBlockInfo_Wait {
		Block BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];	//ブロック配置
		int PlaceX, PlaceY;		//落下ブロックの中心位置の座標(配列の1,1の場所)
		int Flag_Rotate;		//回転可能かどうか(TRUEで回転可能)
	};
	FallBlockInfo_Wait waitBlockinfo[3];	//待機ブロックの情報


	//落下ブロックの情報
	int Counter;			//落下ブロックのカウンタ(常に有効な変数です！！)(負の数でブロックが消滅してからの経過フレーム、正の数でブロックが生成されてからの時間)

	int Enable;				//落下中かどうか(TRUEで落下ブロック有効)
	Block BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];			//落下ブロック本体の情報
	Block BlockID_FallPoint[FALLBLOCK_SIZE*FALLBLOCK_SIZE];	//落下予想地点のブロック情報

	int PlaceX, PlaceY;		//落下ブロックの中心位置の座標(配列の1,1の場所)
	int FallCount;			//落下カウントダウン(0で落下する)
	int Flag_Rotate;		//回転可能かどうか(TRUEで回転可能)

	//キー入力による状態の保存用
	int Key_FlagFirstFall;	//高速落下モード(TRUEで有効)
	int Key_LRMove;			//左右移動(-1左、0移動無し、1右移動)
	int Key_LRRota;			//回転移動(-1反時計回り、0回転無し、1時計回り)

	void FallBlock_addField();												//落下ブロックをフィールドブロックに変換する(つまり設置)
	void Delete_FallBlock();												//落下ブロックの無効化
	void Create_Wait_Block();												//落下ブロックの待機列の作成
};