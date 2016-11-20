#include "BlockChangeMotion.h"


BlockChangeMotion::BlockChangeMotion() {
	Type = BlockChangeMotionType_NO;
}


BlockChangeMotion::~BlockChangeMotion() {}

//変化モーションの設定(TRUEで成功)
int BlockChangeMotion::Create(BlockChangeMotionType mtype, BLOCK_TYPE from, BLOCK_TYPE to, int motionLength, int delay) {
	if (motionLength <= 0)									return FALSE;	//長さが負の数の場合も処理をしない

	if (Type != BlockChangeMotionType_NO) {
		printLog_C(_T("ブロック変化モーションを上書きします"));
		Delete();
	}

	To = to;
	From = from;
	Length = motionLength;
	Count = -delay;

	Type = mtype;

	return TRUE;
}

//変化モーションの削除
void BlockChangeMotion::Delete() {
	Type = BlockChangeMotionType_NO;
}

//変化モーションが有効かどうかの取得
int BlockChangeMotion::isEnable() {
	return ((getType() == BlockChangeMotionType_NO) ? FALSE : TRUE);
}

//変化モーションの種類を取得する
BlockChangeMotionType BlockChangeMotion::getType() {
	return Type;
}

//計算処理
void BlockChangeMotion::Update() {
	if (!isEnable())	return;	//変化モーションが無効の場合は何もしない

	//変化モーション
	Count++;//カウントアップ
	if (Count > Length) {//モーション完了
		Type = BlockChangeMotionType_NO;//変化モーションを無効化
	}
}

//変化元ブロックの種類を取得する
BLOCK_TYPE BlockChangeMotion::getBlockType_From() {
	if (!isEnable())	return BLOCK_TYPE_NO;
	return From;
}

//変化先ブロックの種類を取得する
BLOCK_TYPE BlockChangeMotion::getBlockType_To() {
	if (!isEnable())	return BLOCK_TYPE_NO;
	return To;
}

//変化の割合を取得する
double BlockChangeMotion::getChangeVal(){
	if (!isEnable())	return 0;
	if (Count < 0)		return 0;	//負の数の時は0
	return Count / (double)Length;
}

//カウントの取得
int BlockChangeMotion::getCount() {
	if (!isEnable())	return 0;
	return Count;
}