#pragma once
//移動モーションのデータ
class BlockMoveMotion
{
public:
	BlockMoveMotion();
	~BlockMoveMotion();

	int Create(int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);	//移動モーションを新規生成する(TRUE成功)
	void Delete();	//移動モーションの削除

	void Update();	//計算処理

	double getPointX();	//移動モーションの座標位置の取得
	double getPointY();	//移動モーションの座標位置の取得

	int isEnable();		//移動モーションが有効かどうかの取得

	void getToPoint(int * toX, int * toY);	//移動先に設定した値を取得する

	void Slide(int valX, int valY);	//モーション自体をずらす

private:
	int Enable;				//移動モーションが有効かどうか
	int FromX, FromY;		//移動元座標
	int ToX, ToY;			//移動先座標
	int Count;				//移動カウント(0起算)
	double acceleration;	//加速度
	double MaxSpeed;		//最高速度
	double ansX, ansY;		//移動モーションによる計算結果の座標位置
};