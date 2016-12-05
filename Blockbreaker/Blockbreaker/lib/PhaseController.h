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

//フェーズクラスの親クラス
namespace SK {
	class Phase_
	{
	private:
		virtual void Draw();			//描画処理
		virtual void Update();			//計算処理
		virtual void Update_Final();	//Update後に呼ばれる
	public:
		//仮想関数
		virtual void Init_Draw();		//初期化(描画処理)
		virtual void Init_Update();		//初期化(計算処理)
		virtual void Finalize_Draw();	//終了処理(描画処理)
		virtual void Finalize_Update();	//終了処理(計算処理)

		virtual void DrawFunc() final;	//描画際に呼ばれる描画関数
		virtual void UpdateFunc() final;//描画際に呼ばれる描画関数
	};

	//フェーズコントローラーのコールバック専用クラス
	class PhaseController_Proc
	{
	public:
		virtual void Proc_ChangefazeUpdated(int Before, int After);	//計算スレッドのフェーズ移行が終了したとき
		virtual void Proc_ChangefazeDrawed(int Before, int After);	//描画スレッドのフェーズ移行が終了したとき
		virtual void Proc_DrawPauseing();							//描画スレッドが一時停止しているときに代わりに実行される
	};


	//フェーズコントローラーのメインクラス
	class PhaseController
	{
	public:
		PhaseController(int MaxNum);	//フェーズの最大数を指定して初期化する
		~PhaseController();

		void ChangefazeRequest(int NO, int arg);	//フェーズ変更リクエストを送る(Updateループの最初に実行されます)

		void Update();	//計算メインループ
		void Draw();	//描画メインループ

		void addFaze(int FazeNo, Phase_ * phase);	//フェーズの定義を行う

		void setCallBack(SK::PhaseController_Proc *Ploc);	//コールバッククラスを登録する
		void setMultiThread(int Flag);	//マルチスレッド動作を行うかどうかの設定
		int isMultiThread();	//マルチスレッド動作を行うかどうかの取得

		int getCurrantPhase();	//現在のフェーズを取得する
		int getTotalPhase();	//フェーズの最大数を取得
	private:
		//設定
		int Flag_MultiThread;	//マルチスレッド動作ならTRUE

								//フェーズ関連
		int CurrantFaze;		//現在のフェーズ
		int CurrantFaze_Draw;	//現在のフェーズ(描画)

								//フェーズ変更リクエスト関連
		int Request_Faze;			//変更先のフェーズ(-1で無効)
		int Request_arg;			//引数

									//状態制御関連
		int DrawPauseRequest = FALSE;		//描画のスキップのリクエスト
		int DrawPause = FALSE;				//描画のスキップ
		int UpdatePauseRequest = FALSE;		//計算のスキップのリクエスト
		int UpdatePause = FALSE;			//計算のスキップ

		void Request_DrawPause();			//描画の停止を要求し、停止するまで待機する
		void Request_UpdatePause();			//計算の停止を要求し、停止するまで待機する
		void ChangefazeUpdate();			//フェーズを変更する(Update)
		void ChangefazeDraw();				//フェーズを変更する(Draw)

		int PhaseMaxNum;		//フェーズの最大数
		Phase_ **Phase;			//フェーズ配列のポインタ(後に配列の先頭アドレスになる)
		Phase_ DefaultPhase_;	//デフォルトのフェーズ
		PhaseController_Proc *PhaseController_Proc;	//コールバック関数クラス

		int JudgeFazeNo(int FazeNo);		//指定した値がフェーズ配列の添え字として妥当かどうかの取得(TRUE妥当)
	};
}

