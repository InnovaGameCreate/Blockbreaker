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
#include <vector>
#include <stack>

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
		virtual void Initialize(int arg, void *arg2);	//初期化
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
		PhaseController();	//フェーズの最大数を指定して初期化する

		void ChangePhaseRequest(Phase_ *phaseInstance, DWORD LoadTime_Milliseconds, int arg = 0, void *arg2 = nullptr);	//フェーズ変更リクエストを送る
		void StackPhaseRequest(Phase_ *phaseInstance, DWORD LoadTime_Milliseconds, int arg = 0, void *arg2 = nullptr);	//フェーズスタックリクエストを送る

		void Update();	//計算メインループ
		void Draw();	//描画メインループ

		void setCallBack(PCon::PhaseController_Proc *Ploc);	//コールバッククラスを登録する
		void setMultiThread(int Flag);	//マルチスレッド動作を行うかどうかの設定
		int isMultiThread();	//マルチスレッド動作を行うかどうかの取得
		Phase_ *getInstance();		//現在のフェーズのインスタンスを直接取得する(危険)	

		void Load();			//ロード中に実行されるロード関数(呼ばないこと！！)

		int getVerNo() const;			//バージョンNoを取得する
	private:
		//ロード時の情報格納クラス
		struct LoadInfomation {
			LoadInfomation() {
				Loading = FALSE;
			}
			LoadInfomation(Phase_ *nextPhase, DWORD loadTime, int arg, void *arg2, unsigned int initializeCount, unsigned int finalizeCount) {
				LoadUpdateCount = 0;
				LoadDrawCount = 0;
				NextPhase = nextPhase;
				if (loadTime <= 0)	loadTime = 1;
				LoadTime = loadTime;
				Arg = arg;
				Arg2 = arg2;
				Fin_Update = nullptr;
				Fin_Draw = nullptr;
				Init_Update = nullptr;
				Init_Draw = nullptr;
				Init_Draw_ = nullptr;
				InitializeCount = initializeCount;
				FinalizeCount = finalizeCount;
				Loading = TRUE;
			}
			int Loading;					//ロード中かどうか
			Phase_ *Fin_Update;				//計算スレッドの終了処理を行うフェーズへのポインタ(nullで処理無し)
			Phase_ *Fin_Draw;				//描画スレッドの終了処理を行うフェーズへのポインタ(nullで処理無し)
			Phase_ *Init_Update;			//計算スレッドの初期化処理を行うフェーズへのポインタ(nullで処理無し)
			Phase_ *Init_Draw;				//描画スレッドの初期化処理を行うフェーズへのポインタ(nullで処理無し)
			Phase_ *Init_Draw_;				//描画スレッドの初期化処理を行うフェーズへのポインタ(nullで処理無し)2(こいつはややこしい)(無限ロードとかできる)
			int LoadUpdateCount;			//ロード時の計算カウント
			int LoadDrawCount;				//ロード時の描画カウント
			Phase_ *NextPhase;				//移動先フェーズのポインタ
			DWORD LoadTime;					//ロードにかける最小時間
			int Arg;						//引数
			void *Arg2;						//引数2
			DWORD StartTime;				//開始時刻
			unsigned int InitializeCount;	//初期化を行う回数(0で行わない)(pushをする回数)
			unsigned int FinalizeCount;		//終了処理を行う回数(0で行わない)(popをする回数)
		};
		//設定
		int Flag_MultiThread;	//マルチスレッド動作ならTRUE

		//フェーズ関連
		std::stack<Phase_*, std::vector<Phase_*>> CurrantPhase;	//フェーズ配列


		//フェーズ変更リクエスト関連
		Phase_* Request_Faze;			//変更先のフェーズ(-1で無効)
		DWORD Request_LoadTime;			//変更先のフェーズ(-1で無効)
		int Request_arg;				//引数
		void *Request_arg2;				//引数2
		int Request_InitializeCount;	//初期化を行う回数
		int Request_FinalizeCount;		//終了処理を行う回数


		//状態制御関連
		int UpdatePauseRequest = FALSE;		//計算のスキップのリクエスト
		int UpdatePause = FALSE;			//計算のスキップ

		void Request_UpdatePause();			//計算の停止を要求し、停止するまで待機する
		void ChangefazeDraw();				//フェーズを変更する(Draw)

		PhaseController_Proc *PhaseController_Proc;	//コールバック関数クラス

		HANDLE LoadThreadhandle;			//ロードスレッドのハンドル

		LoadInfomation loadInfomation;		//ロード情報
	};
}

/*フェーズ移行の手順
1.移行元のUpdate、Drawスレッドの終了処理関数が呼ばれる。(フリーズします)
2.共通終了処理関数がロード専用スレッドで呼ばれる。(主にメモリの解放？)(フリーズしません)
3.共通初期化処理関数がロード専用スレッドで呼ばれる。(主にメモリの取得？)(フリーズしません)
4.移行先のUpdate、Drawスレッドの初期化処理関数が呼ばれる。(フリーズします)
5.最低のロードにかける時間が経過するまでまで待機(フリーズしません)
*/