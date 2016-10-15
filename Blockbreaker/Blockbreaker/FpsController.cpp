//FPSコントロール関連
#include "FpsController.h"


FpsController::FpsController(int FPS) {
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("FpsControllerのコンストラクタが呼ばれました"));
	Initialize(FPS);
}

//初期化
void FpsController::Initialize(int fps) {
	mStartTime = 0;
	mCount = 0;
	FPS_Ave = 0;
	FPS = fps;
	VSyncWaitMode = false;
}

//フレームの経過時間の全処理前に実行する関数
void FpsController::Update_First() {
}

//フレームレートを維持するために待機時間を発生させる
void FpsController::Wait() {
	if (VSyncWaitMode)	return;	//垂直同期が有効な場合は処理しない

	int tookTime = GetNowCount() - mStartTime;			//かかった時間
	int waitT = mCount * 1000 / FPS - tookTime;			//待つべき時間

	//必ず待機時間60FPS以上にならないように待機時間を設ける(ループにかける時間が早すぎるとき)
	//if (waitT < 0)	waitT = 1000 / (FPS);

	//平均待機時間の計算
	if (waitT >= 0)	WaitTime += waitT;
	else			WaitTime = waitT;

	if (waitT > 0) {
		Sleep(waitT);	//待機
	}
}

//フレームの経過時間の全処理後に実行する関数
void FpsController::Update_Last() {
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		FPS_Ave = 1000. / ((t - mStartTime) / (double)N);	//平均FPSの計算
		WaitTime_Ave = WaitTime / (double)N;				//平均待機時間の計算
		WaitTime = 0;
		mCount = 0;
	}
	else {
	}
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	mCount++;			//カウンタのカウントアップ
	FrameCount++;	//経過フレームのカウントアップ
}

//垂直同期によりフレームの停止を行うかどうかの設定(TRUEで垂直同期を使用する、つまりこのモジュールで待機処理を行わない)
void FpsController::SetVSyncMode(int Flag) {
	VSyncWaitMode = (Flag) ? true : false;
}

//垂直同期によりフレームの停止を行うかどうかの取得(TRUEで垂直同期を使用する、つまりこのモジュールで待機処理を行わない)
int FpsController::GetVSyncMode() {
	return ((VSyncWaitMode) ? TRUE : FALSE);
}

//現在の平均FPSを取得する
double FpsController::GetFPS_Average() {
	return FPS_Ave;
}

//経過フレーム数を取得
unsigned int FpsController::GetFrameCount() {
	return FrameCount;
}

//1フレームあたりの平均待機時間の取得
double FpsController::GetWaitTime_Average() {
	return WaitTime_Ave;
}

//1フレームあたりの平均待機時間の割合の取得
double FpsController::GetWaitTime_Average_Par() {
	double f_Time;//1フレームにかける時間
	double par;//割合
	f_Time = 1000. / FPS;
	par = (GetWaitTime_Average() * 100) / f_Time - 100;
	if (par < 0)	par = -par;//マイナスなら符号逆転(0.00の時の符号が+-してうざかったから)
	return par;
}