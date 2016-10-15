#pragma once
class FpsController
{
public:
	FpsController(int FPS);
	void Update_First();		//フレームの経過時間の全処理前に実行する関数
	void Update_Last();			//フレームの経過時間の全処理後に実行する関数
	void Wait();				//フレームレートを維持するために待機時間を発生させる

	void SetVSyncMode(int Flag);	//垂直同期によりフレームの停止を行うかどうかの設定(TRUEで垂直同期を使用する、つまりこのモジュールで待機処理を行わない)

	double GetFPS_Average();			//現在の平均FPSを取得する
	unsigned int GetFrameCount();		//経過フレーム数を取得
	double GetWaitTime_Average();		//1フレームあたりの平均待機時間の取得
	double GetWaitTime_Average_Par();	//1フレームあたりの平均待機時間の割合の取得
	int GetVSyncMode();					//垂直同期によりフレームの停止を行うかどうかの取得(TRUEで垂直同期を使用する、つまりこのモジュールで待機処理を行わない)
private:
	int mStartTime;				//測定開始時刻
	int mCount;					//カウンタ
	static const int N = 60;	//平均をとるサンプル数
	int FPS;					//目標FPS
	int WaitTime;				//待機時間
	bool VSyncWaitMode;			//垂直同期の待機を行う設定(trueで垂直同期を使用する)

	double FPS_Ave;				//平均fps
	double WaitTime_Ave;		//平均待機時間

	unsigned int FrameCount;	//経過フレームカウント

	void Initialize(int fps);	//初期化
};