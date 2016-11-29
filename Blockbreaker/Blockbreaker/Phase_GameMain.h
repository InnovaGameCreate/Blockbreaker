#pragma once
#include "SelectItem.h"
#include "Define.h"
#include "Block_Field.h"
#include "BlockMoveMotion.h"
#include "Block_Fall.h"
#include "Tex_Block.h"
#include "Field_Admin.h"

class Phase_GameMain : public SK::Phase_
{
public://定数とかの宣言




	//ポーズの種類
	enum PauseMode {
		PauseMode_NO,			//ポーズ状態になっていない(通常)
		PauseMode_NOMAL,		//通常のポーズ(escでポーズするやつ)
		PauseMode_GameOver,		//ゲームオーバー
		PauseMode_GameClear,	//ゲームクリア
		PauseMode_NUM			//個数(リクエスト無し)
	};

	//スコア関係
	struct Score {
		/*
		0:ブロックの消去によるスコア
		1:破壊光線による減点
		2:その他
		*/
		int score[3];
		Score() { init(); }
		//スコアの初期化
		void init() {
			for (auto &data : score) {
				data = 0;
			}
		}
		//合計スコアの取得
		int getScore() {
			int sum = 0;
			for (auto data : score) {
				sum += data;
			}
			return sum;
		}
		//スコアの加算
		void addScore(int No, int Score) {
			if (No < 0 || ARRAY_LENGTH(score) <= No)	return;
			score[No] += Score;
		}
	};

private:
	//ここにポーズメニュー表示時に出す選択肢のクラスを定義する
	class SelectItem_pause : public SelectItem
	{
	public:
		SelectItem_pause(int X, int Y) : SelectItem(X, Y) {};//コンストラクタ(スーパークラスのコンストラクタを明示的に呼んでいます)
	private:
		void Event_Select(int No) override;	//ポーズメニューのボタンが押されたとき(オーバーライド)
	};

	//ゲームサイクルの識別
	enum GameCycle {
		GameCycle_FALL,			//ブロックの落下
		GameCycle_BeforeFALL,	//ブロックの落下開始前
		GameCycle_Update,		//ブロックの計算ループ
		GameCycle_NUM			//ゲームサイクルの個数(設定無し)
	};


	Field_Admin Field;	//フィールド情報


	SelectItem_pause pauseMenu = SelectItem_pause(WINDOW_WIDTH/2, 600);	//ポーズメニューの項目

	//ブロックの計算ループで使用する変数
	int Loop_No;			//計算ループのどの処理をしているか(-1で計算ループ未使用)
	GameCycle Loop_Next;	//計算ループ後に移行するゲームサイクル


	//フライテキスト表示クラス
	FlyText flyText;

	//スコア
	Score score;

	int gameWindow;	//ゲーム画面を描画するハンドル
	Tex_Block tex_Block;		//ブロックのテクスチャ
	int haikei;						//背景
	int Tex_FieldBack;			//フィールド背景

	int BGM;				//BGM


	PauseMode Flag_Pause;				//ポーズ状態かどうか(ゲームの進行がすべて停止します)
	PauseMode Flag_pauseRequest;		//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)

	
	Block_Fall fallBlockInfo;				//落下ブロックの情報


	GameCycle gameCycle;		//ゲームサイクル
	int gameCycleFirstCallFlag;	//ゲームサイクルが変更されたときにTRUEが代入される

	SK::RandomTable randomTable;	//乱数テーブル

	int Count_PlayTime;		//実際に操作をしている経過フレーム数(ポーズ、ブロック落下時以外でカウントアップが一時停止する)
	int Count_GameTime;		//ゲーム経過フレーム数(ポーズでカウントアップが一時停止する)
	int Count_Time;			//ゲーム経過フレーム数
	int Count_Pause;		//ポーズ時のカウンタ
	int Count_Turn;			//経過ターン数（ブロック落下時に加算）

	void Draw();
	void Draw_Status();				//ステータスの描画
	void Draw_ClearScreen();		//クリア画面の追加描画
	int Update_FieldBlock();		//フィールドブロックの細々とした計算ループ
	void Update_Counter();			//カウンタのカウントアップ
	void Update();
	void Update_Final();			//Update後に呼ばれる
	void GameMain_Key();

	void setGameCycle(GameCycle gameCycle);			//ゲームサイクルを設定する
	void UpdateBlockRequest(GameCycle Next);		//ブロック情報を更新するようにリクエスト
	int JudgeGameOver();							//ゲームオーバーになっているかどうかの確認
	int JudgeGameClear();							//ゲームクリアかどうかの確認(TRUEゲームクリア)
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();


	/*設定系*/
	void Request_Pause(PauseMode pauseMode);	//ポーズ状態のリクエスト

	/*取得系*/
	PauseMode getPauseMode();		//ポーズ状態の取得
	int getCountPlayTime();			//実際に操作をしている経過フレーム数を取得する
	int getCountGameTime();			//ゲームの経過フレーム数を取得(クリアで停止します)
	int getCountTime();				//ゲームの経過フレーム数を取得(クリアしても停止しません)
	void Restart();						//リスタート
	void RestoreGraphCallback();		//フルスクリーンに復帰時に呼ばれる
	BLOCK_TYPE GetRandomBlockType_FALL();			//ランダムでブロックの種類を返す
	Tex_Block *getTex_Block();			//テクスチャの情報の取得
	SK::RandomTable *getRandomTable();		//乱数表の取得
	Block_Fall *getfallBlockInfo();		//落下ブロッククラスのポインタ取得
	Phase_GameMain::Score *getScore();	//スコアクラスのインスタンスの取得
	FlyText *getFlyText();				//フライテキストのインスタンスの取得
	Field_Admin *getField();			//フィールドブロックのインスタンスの取得
	int isDebugMode();					//デバッグが有効かどうかの取得
	BLOCK_TYPE GetRandomBlockType_UNDER();	//ランダムでブロックの種類を返す(下から沸いてくるブロック用)
};

