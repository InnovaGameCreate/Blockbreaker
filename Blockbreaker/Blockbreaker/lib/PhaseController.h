#pragma once
//フェーズコントローラー
//ライブラリの読み込み
#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "PhaseControllerx64_d.lib")
	#else
		#pragma comment(lib, "PhaseControllerx86_d.lib")
	#endif // _WIN64
#else
	#ifdef _WIN64
		#pragma comment(lib, "PhaseControllerx64.lib")
	#else
		#pragma comment(lib, "PhaseControllerx86.lib")
	#endif // _WIN64
#endif // _DEBUG

#include <Windows.h>
#include <process.h>

//フェーズクラスの親クラス
namespace PCon {
	class Phase_
	{
	private:
		virtual void Draw();			//描画処理
		virtual void Update();			//計算処理
		virtual void Update_Final();	//Update後に呼ばれる
	public:
		//仮想関数
		virtual void Initialize(int arg);		//初期化(計算処理)
		virtual void Finalize();		//終了処理(計算処理)

		virtual void DrawFunc() final;	//描画際に呼ばれる描画関数
		virtual void UpdateFunc() final;//描画際に呼ばれる描画関数
	};

	//フェーズコントローラーのコールバック専用クラス
	class PhaseController_Proc
	{
	public:
		virtual void Proc_Changefazed(int Before, int After);	//フェーズ移行が終了したとき
		virtual void Proc_DrawPauseing(int count);				//描画スレッドが一時停止しているときに代わりに実行される(ロード中とか)
		virtual void Proc_UpdatePauseing(int count);			//計算スレッドが一時停止しているときに代わりに実行される(ロード中とか)
	};


	//フェーズコントローラーのメインクラス
	class PhaseController
	{
	public:
		static const int VerNo;			//バージョン番号

		PhaseController(int MaxNum);	//フェーズの最大数を指定して初期化する
		~PhaseController();

		void ChangefazeRequest(int NO, DWORD LoadTime_Milliseconds, int arg);	//フェーズ変更リクエストを送る(Updateループの最初に実行されます)

		void Update();	//計算メインループ
		void Draw();	//描画メインループ

		void addFaze(int FazeNo, Phase_ * phase);	//フェーズの定義を行う

		void setCallBack(PCon::PhaseController_Proc *Ploc);	//コールバッククラスを登録する
		void setMultiThread(int Flag);	//マルチスレッド動作を行うかどうかの設定
		int isMultiThread();	//マルチスレッド動作を行うかどうかの取得

		int getCurrantPhase();	//現在のフェーズを取得する
		int getTotalPhase();	//フェーズの最大数を取得

		void Load();			//ロード中に実行されるロード関数(呼ばないこと！！)
	private:
		//設定
		int Flag_MultiThread;	//マルチスレッド動作ならTRUE

		//フェーズ関連
		int CurrantFaze;		//現在のフェーズ

		//フェーズ変更リクエスト関連
		int Request_Faze;			//変更先のフェーズ(-1で無効)
		DWORD Request_LoadTime;		//変更先のフェーズ(-1で無効)
		int Request_arg;			//引数

		int LoadUpdateCount;		//ロード時の計算カウント
		int LoadDrawCount;			//ロード時の描画カウント

		//状態制御関連
		int DrawPauseRequest = FALSE;		//描画のスキップのリクエスト
		int DrawPause = FALSE;				//描画のスキップ

		void Request_DrawPause();			//描画の停止を要求し、停止するまで待機する
		void ChangefazeUpdate();			//フェーズを変更する(Update)

		int PhaseMaxNum;		//フェーズの最大数
		Phase_ **Phase;			//フェーズ配列のポインタ(後に配列の先頭アドレスになる)
		Phase_ DefaultPhase_;	//デフォルトのフェーズ
		PhaseController_Proc *PhaseController_Proc;	//コールバック関数クラス

		HANDLE LoadThreadhandle;	//ロードスレッドのハンドル

		int JudgeFazeNo(int FazeNo);		//指定した値がフェーズ配列の添え字として妥当かどうかの取得(TRUE妥当)

	};
}

