#include "BlockMoveMotion.h"
#include "MainFunc.h"

//移動モーションのデータ

BlockMoveMotion::BlockMoveMotion() {
	Delete();
}


BlockMoveMotion::~BlockMoveMotion() {

}

//移動モーションを新規生成する(TRUE成功)
int BlockMoveMotion::Create(int fromX, int fromY, int toX, int toY, double a, double maxSpeed) {
	if (fromX == toX && fromY == toY)	return FALSE;	//移動無しの場合も処理をしない
	if (a <= 0)							return FALSE;	//加速度が負の数の場合も処理をしない
	if (maxSpeed <= 0)					return FALSE;	//最大速度が負の数の場合も処理をしない

	if (isEnable()) {
		printLog_C(_T("ブロックの移動モーションを上書きします"));
		Delete();	//いったん削除する
	}

	ToX = toX;
	ToY = toY;
	FromX = fromX;
	FromY = fromY;
	acceleration = a;
	MaxSpeed = maxSpeed;
	Count = 0;

	Enable = TRUE;


	return TRUE;
}

//移動モーションの削除
void BlockMoveMotion::Delete() {
	Enable = FALSE;
}

//計算処理(移動中FALSE)
void BlockMoveMotion::Update() {
	//移動モーション
	if (Enable) {
		Count++;//カウントアップ
		//移動する距離の計算
		double fX, fY, tX, tY;
		Block_Field::Convert_Ingame_FromBlock(FromX, FromY, 0.5, 0.5, &fX, &fY);
		Block_Field::Convert_Ingame_FromBlock(ToX, ToY, 0.5, 0.5, &tX, &tY);
		double MD = getMoveDistance(acceleration, MaxSpeed, Count);	//現在の移動距離
		double FMD = getDistance(fX, fY, tX, tY);			//最終的な移動距離
		double Rota = getRotation(FromX, FromY, ToX, ToY);	//角度の計算
		//上の計算結果より、描画座標の計算
		ansX = fX + MD * cos(deg_to_rad(Rota));
		ansY = fY + MD * sin(deg_to_rad(Rota));
		if (FMD <= MD) {//移動完了
			Enable = FALSE;//移動を無効化
		}
	}
}

//移動モーションの座標位置の取得
double BlockMoveMotion::getPointX() {
	if (isEnable())	return ansX;
	else			return 0;
}

//移動モーションの座標位置の取得
double BlockMoveMotion::getPointY() {
	if (isEnable())	return ansY;
	else			return 0;
}

//移動モーションが有効かどうかの取得
int BlockMoveMotion::isEnable() {
	return ((Enable) ? TRUE : FALSE);
}

//移動先に設定した値を取得する
void BlockMoveMotion::getToPoint(int *toX, int *toY) {
	if (toX != NULL)	*toX = ToX;
	if (toY != NULL)	*toY = ToY;
}

//モーション自体をずらす
void BlockMoveMotion::Slide(int valX, int valY) {
	if (isEnable()) {//移動モーションが有効な場合は移動モーションに補正をかける
		FromX += valX;
		FromY += valY;
		ToX += valX;
		ToY += valY;
	}
}