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
#include <mutex>

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
		virtual void Initialize(int arg);	//初期化
		virtual void Init_Update();			//初期化(計算スレッド)
		virtual void Init_Draw();			//初期化(描画スレッド)
		virtual int Init_Draw_();			//初期化(ダミー描画スレッド)(戻り値がTRUEの時、ロード終了ってことになるという非常にややこしい関数)
		virtual void Finalize();			//終了処理
		virtual void Fin_Update();			//終了処理(計算スレッド)
		virtual void Fin_Draw();			//終了処理(描画スレッド)

		virtual void DrawFunc() final;	//描画際に呼ばれる描画関数
		virtual void UpdateFunc() final;//描画際に呼ばれる描画関数
	};

	//フェーズコントローラーのコールバック専用クラス
	class PhaseController_Proc
	{
	public:
		virtual void Proc_Changefazed(int Before, int After, DWORD LoadTime, DWORD SetTime);	//フェーズ移行が終了したとき
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
		//ロード時の情報格納クラス
		struct LoadInfomation {
			LoadInfomation() {
				Loading = FALSE;
			}
			LoadInfomation(int beforePhase, int nextPhase, DWORD loadTime, int arg) {
				Loading = TRUE;
				LoadUpdateCount = 0;
				LoadDrawCount = 0;
				BeforePhase = beforePhase;
				NextPhase = nextPhase;
				if (loadTime <= 0)	loadTime = 1;
				LoadTime = loadTime;
				Arg = arg;
				Fin_FinUpdate = FALSE;
				Fin_FinDraw = FALSE;
				Prepar_Init = FALSE;
				Fin_InitUpdate = FALSE;
				Fin_InitDraw = FALSE;
				Fin_InitDraw_ = FALSE;
			}
			int Loading;				//ロード中かどうか
			int Fin_FinUpdate;			//計算スレッドの終了処理が終わったかどうかのフラグ
			int Fin_FinDraw;			//描画スレッドの終了処理が終わったかどうかのフラグ
			int Prepar_Init;			//初期化処理の一部が完了し、各スレッドで初期化処理が行える状態になったフラグ
			int Fin_InitUpdate;			//計算スレッドの初期化処理が終わったかどうかのフラグ
			int Fin_InitDraw;			//描画スレッドの初期化処理が終わったかどうかのフラグ
			int Fin_InitDraw_;			//描画スレッドの初期化処理が終わったかどうかのフラグ2(こいつはややこしい)
			int LoadUpdateCount;		//ロード時の計算カウント
			int LoadDrawCount;			//ロード時の描画カウント
			int BeforePhase;			//移動元フェーズ
			int NextPhase;				//移動先フェーズ
			DWORD LoadTime;				//ロードにかける最小時間
			int Arg;					//引数
			DWORD StartTime;			//開始時刻
		};
		//設定
		int Flag_MultiThread;	//マルチスレッド動作ならTRUE

		//フェーズ関連
		int CurrantFaze;		//現在のフェーズ

		//フェーズ変更リクエスト関連
		int Request_Faze;			//変更先のフェーズ(-1で無効)
		DWORD Request_LoadTime;		//変更先のフェーズ(-1で無効)
		int Request_arg;			//引数


		//状態制御関連
		int UpdatePauseRequest = FALSE;		//計算のスキップのリクエスト
		int UpdatePause = FALSE;			//計算のスキップ

		void Request_UpdatePause();	//計算の停止を要求し、停止するまで待機する
		void ChangefazeDraw();		//フェーズを変更する(Draw)

		int PhaseMaxNum;		//フェーズの最大数
		Phase_ **Phase;			//フェーズ配列のポインタ(後に配列の先頭アドレスになる)
		Phase_ DefaultPhase_;	//デフォルトのフェーズ
		PhaseController_Proc *PhaseController_Proc;	//コールバック関数クラス

		HANDLE LoadThreadhandle;	//ロードスレッドのハンドル

		LoadInfomation loadInfomation;	//ロード情報

		int JudgeFazeNo(int FazeNo);		//指定した値がフェーズ配列の添え字として妥当かどうかの取得(TRUE妥当)

	};
}

/*フェーズ移行の手順
1.移行元のUpdate、Drawスレッドの終了処理関数が呼ばれる。(フリーズします)
2.共通終了処理関数がロード専用スレッドで呼ばれる。(主にメモリの解放？)(フリーズしません)
3.共通初期化処理関数がロード専用スレッドで呼ばれる。(主にメモリの取得？)(フリーズしません)
4.移行先のUpdate、Drawスレッドの初期化処理関数が呼ばれる。(フリーズします)
5.最低のロードにかける時間が経過するまでまで待機(フリーズしません)
*/