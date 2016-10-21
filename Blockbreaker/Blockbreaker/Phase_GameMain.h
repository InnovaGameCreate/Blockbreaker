#pragma once


#ifndef PHASECONTROLLER_H_
#error PhaseController.hをIncludeしてください
#endif // !PHASECONTROLLER_H_



class Phase_GameMain : public PhaseController
{
public://定数とかの宣言
	static const int BLOCK_SIZE = 50;		//ブロックの縦横のピクセルサイズ
	static const int BLOCK_WIDTHNUM = 14;	//ブロックの横の個数
	static const int BLOCK_HEIGHTNUM = 17;	//ブロックの縦の個数
	static const int FALLBLOCK_SIZE = 3;	//落下するブロックの大きさ
	static const int FALLBLOCK_CENTER = FALLBLOCK_SIZE/2;	//落下するブロックの中心(基準)位置

	//色
	enum BROCK_TYPE {
		BROCK_TYPE_NO,
		BROCK_TYPE_RED,
		BROCK_TYPE_BLUE,
		BROCK_TYPE_YELLOW,
		BROCK_TYPE_GREEN,
		BROCK_TYPE_PURPLE,
	};

private:
	struct field_info {
		BROCK_TYPE color;//ブロックの色
		int fall_flag;//落下中かどうかのフラグ
		int move_flag;//移動中かどうかのフラグ
	};

	struct Fallblock_Pack {
		BROCK_TYPE BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];	//縦横FALLBLOCK_SIZEずつのブロック領域としてブロックの位置情報を記録する

	};

	//落下ブロックの情報
	struct FallBlockInfo {
		FallBlockInfo() {
			Enable = FALSE;
			Counter = 0;
		}
		int Counter;			//落下ブロックのカウンタ(常に有効な変数です！！)(負の数でブロックが消滅してからの経過フレーム、正の数でブロックが生成されてからの時間)

		int Enable;				//落下中かどうか(TRUEで落下ブロック有効)
		struct Fallblock_Pack fallblock;	//落下ブロック本体の情報
		
		int PlaceX, PlaceY;		//落下ブロックの中心位置の座標(配列の1,1の場所)
		int FallCount;			//落下カウントダウン(0で落下する)
		
		//キー入力による状態の保存用
		int Key_FlagFirstFall;	//高速落下モード(TRUEで有効)
		int Key_LRMove;			//左右移動(-1左、0移動無し、1右移動)
		int Key_LRRota;			//回転移動(-1反時計回り、0回転無し、1時計回り)
	};

	field_info field[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];


	int gameWindow;	//ゲーム画面を描画するハンドル

	int Flag_Pause;			//ポーズ状態かどうか(ゲームの進行がすべて停止します)(TRUEでポーズ)
	int Flag_pauseRequest;	//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)

	
	FallBlockInfo fallBlockInfo;	//落下ブロックの情報

	void Draw();
	void Update();
	void Update_FallBlock();			//落下ブロックの落下処理
	void GameMain_Key();

	int FallBlock_MoveX(int MoveVal);		//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
	int FallBlock_MoveY(int MoveVal);		//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
	int FallBlock_Rotate(int RotaVal);		//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)
	void FallBlock_addField();				//落下ブロックをフィールドブロックに変換する(つまり設置)
	void Block_Gravity();					//フィールドブロックを重力で落下させる
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock(struct Fallblock_Pack *fallblock_Pack);		//落下ブロックを生成する(戻り値:成功でTRUE)
	int add_FraldBlock(int X, int Y, BROCK_TYPE brock_type);							//フィールドにブロックを追加する

	/*設定系*/
	void PauseRequest(int b_Flag);		//ポーズ状態のリクエスト
	void Delete_FallBlock();			//落下ブロックの無効化

	/*取得系*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY);	//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
	int	isPaused();					//ポーズ状態かどうかの取得(TRUEでポーズ)
	int isFallBlock_Falling();		//落下ブロックが落下中かどうかの取得(TRUEで落下中)
	int isFallBlock_Enable();		//落下ブロックが有効かどうかの取得(TRUEで有効)
	int getFallBlock_Interval();	//落下ブロックの前回の落下からのインターバルの取得(落下ブロックが存在するときは0が返ります)
	BROCK_TYPE getBlockColor(int X, int Y, int useOutScreenBlock = FALSE);	//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうか)
};

