#pragma once
#include "SelectItem.h"
#include "Define.h"
#include "Block_Field.h"
#include "BlockMoveMotion.h"
#include "Block_Fall.h"
#include "Tex_Block.h"

class Phase_GameMain : public PhaseController
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



private:
	//ここにポーズメニュー表示時に出す選択肢のクラスを定義する
	class SelectItem_pause : public SelectItem
	{
	public:
		SelectItem_pause(int X, int Y) : SelectItem(X, Y) {};//コンストラクタ(スーパークラスのコンストラクタを明示的に呼んでいます)
	private:
		void Event_Select(int No) override;	//ポーズメニューのボタンが押されたとき(オーバーライド)
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
			for (auto &data: score) {
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

	//ゲームサイクルの識別
	enum GameCycle {
		GameCycle_FALL,			//ブロックの落下
		GameCycle_BeforeFALL,	//ブロックの落下開始前
		GameCycle_Update,		//ブロックの計算ループ
		GameCycle_NUM			//ゲームサイクルの個数(設定無し)
	};



	

	Block_Field field[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	Block_Field Virtualfield[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];	//計算上のフィールド情報UseVirtualField=TRUEで使用

	SelectItem_pause pauseMenu = SelectItem_pause(Base_BB_getWINDOW_WIDTH()/2, 600);	//ポーズメニューの項目

	//ブロックの計算ループで使用する変数
	int Loop_No;			//計算ループのどの処理をしているか(-1で計算ループ未使用)
	GameCycle Loop_Next;	//計算ループ後に移行するゲームサイクル

	//ブロックの全体移動で使用する変数
	BlockMoveMotion Block_AllMovedata;

	//フライテキスト表示クラス
	FlyText flyText;

	//スコア
	Score score;

	int ChainCount = 0;	//連鎖カウント


	int gameWindow;	//ゲーム画面を描画するハンドル
	Tex_Block tex_Block;		//ブロックのテクスチャ
	int haikei;						//背景
	int Tex_FieldBack;			//フィールド背景

	int BGM;				//BGM


	PauseMode Flag_Pause;				//ポーズ状態かどうか(ゲームの進行がすべて停止します)
	PauseMode Flag_pauseRequest;		//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)

	
	Block_Fall fallBlockInfo;				//落下ブロックの情報

	PolygonPoints2 lay;			//破壊光線のエフェクト情報
	int Count_lay;				//破壊光線エフェクトの経過時間

	GameCycle gameCycle;		//ゲームサイクル
	int gameCycleFirstCallFlag;	//ゲームサイクルが変更されたときにTRUEが代入される

	RandomTable randomTable;	//乱数テーブル

	int Count_PlayTime;		//実際に操作をしている経過フレーム数(ポーズ、ブロック落下時以外でカウントアップが一時停止する)
	int Count_GameTime;		//ゲーム経過フレーム数(ポーズでカウントアップが一時停止する)
	int Count_Time;			//ゲーム経過フレーム数
	int Count_Pause;		//ポーズ時のカウンタ
	int Count_Turn;			//経過ターン数（ブロック落下時に加算）

	void Draw();
	void Draw_FieldBlock();			//フィールドブロックの描画
	void Draw_Status();				//ステータスの描画
	void Draw_NextFallBlock();		//次の落下ブロックの描画
	int Update_FieldBlock();		//フィールドブロックの細々とした計算ループ
	int Update_MoveMotion();		//移動モーションの更新(移動モーションが行われたときはTRUE)
	int Update_ChangeMotion();		//変化モーションの更新(変化モーションが行われたときはTRUE)
	void Update_Lay_BlockDel();		//破壊光線エフェクトの更新
	void Update_Counter();			//カウンタのカウントアップ
	void Update();
	void Update_Final();			//Update後に呼ばれる
	void GameMain_Key();

	void Block_Black_Func();		//フィールドに存在する黒色ブロックの色を決定する
	void Block_Rainbow_Func();		//フィールドに存在する虹色ブロックの色を決定する
	void Block_BOMB_Func();			//フィールドに存在する爆弾ブロックを爆破する
	void Block_2BOMB_Func();		//フィールドに存在するスリー爆弾ブロックを爆破する
	void Block_BOMBColor_Func();	//フィールドに存在する同色爆弾ブロックを爆破する

	void Block_Gravity(int InGameOnly = TRUE);	//フィールドブロックを重力で落下させる(TRUEでゲーム画面内のみ)
	int Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int MotionLengh = 40, int Delay = 0);		//フィールドブロックを削除する
	int Block_Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int MotionLengh = 40);	//指定した座標が指定したブロックだった場合に削除
	int Block_Delete(int Len = BLOCK_DELETE_LEN, int Flag_Event = TRUE);	//連続するフィールドブロックを削除する(Flag_EventをTRUEで消去によって発動する効果も発動する)(消去したブロックの数)
	int Block_Delete_OutScreen();//画面外のブロックをすべて削除する(消去したブロックの数)
	void under_Block();							//下からブロックがわいてくる
	void Lay_BlockDel();						//破壊光線でブロックを破壊する
	void SequenceCount(int x, int y, int ID, int n[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter, int UseVirtualField = FALSE);	//隣接する同色ブロックのカウント
	void CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField = FALSE);	//SequenceCountで使用するマーカーテーブルを作成する(有効なエリア)(UseVirtualField=TRUEで仮想の面を使用する)
	void Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);					//フィールドのブロックに移動モーションを設定する
	void Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay);	//フィールドのブロックに変化モーションを設定する(これ単体で使用して事故っても知りません)
	void Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength, int Delay);				//フィールドのブロックに変化モーション(通常)を設定する
	void Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength, int Delay);			//フィールドのブロックに変化モーション(通常)を設定する(変化元指定)
	void Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength, BLOCK_TYPE From, int Delay);							//フィールドのブロックに変化モーション(爆発)を設定する
	void Block_SetChangeMotion_SMALL(int x, int y, int MotionLength, BLOCK_TYPE From, int Delay);								//フィールドのブロックに変化モーション(小さくなって消える)を設定する
	void setGameCycle(GameCycle gameCycle);			//ゲームサイクルを設定する
	void UpdateBlockRequest(GameCycle Next);		//ブロック情報を更新するようにリクエスト
	void Block_AllMoveRequest(int X, int Y);		//フィールド全体のブロックを指定した分だけ移動するリクエストをする(ゲームを一時停止して動かします)
	void Block_AllMove(int X, int Y);				//フィールド全体のブロックを指定した分だけ移動する(画面外に出てしまうブロックは消滅します)
	int JudgeGameOver();							//ゲームオーバーになっているかどうかの確認
	int JudgeGameClear();							//ゲームクリアかどうかの確認(TRUEゲームクリア)
	Phase_GameMain::BLOCK_TYPE GetRandomBlockType_UNDER();	//ランダムでブロックの種類を返す(下から沸いてくるブロック用)
	void Virtualfield_Update();						//仮想フィールドを現在のフィールドと一致させる
	void setBlock_Rect(int x, int y, int w, int h);	//指定したエリアにブロックを設置する(消去判定が入らないように、かつ上書き無しで設置します)
	int getBlock_maxUpper();						//最大の高さのブロックのY座標を取得する
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int add_FraldBlock2(int X, int Y, BLOCK_TYPE brock_type, int Override = FALSE, int OutScreen = FALSE, BLOCK_TYPE *Before = NULL, int UseVirtualField = FALSE);			//フィールドにブロックを追加する

	/*設定系*/
	void Request_Pause(PauseMode pauseMode);	//ポーズ状態のリクエスト

	/*取得系*/
	PauseMode getPauseMode();		//ポーズ状態の取得
	int getCountPlayTime();			//実際に操作をしている経過フレーム数を取得する
	int getCountGameTime();			//ゲームの経過フレーム数を取得(クリアで停止します)
	int getCountTime();				//ゲームの経過フレーム数を取得(クリアしても停止しません)
	BLOCK_TYPE getBlockColor(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE, int UseVirtualField = FALSE);	//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
	int isBlock_PlayMoveMotion();		//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
	int isBlock_PlayChangeMotion();		//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
	void Restart();						//リスタート
	void RestoreGraphCallback();		//フルスクリーンに復帰時に呼ばれる
	int getBlock_Upper(int x);			//指定したX座標の一番上のブロックのY座標を取得する(見えている座標のみで判断)
	BLOCK_TYPE GetRandomBlockType_FALL();			//ランダムでブロックの種類を返す
	Tex_Block *getTex_Block();			//テクスチャの情報の取得
	RandomTable *getRandomTable();		//乱数表の取得
};

