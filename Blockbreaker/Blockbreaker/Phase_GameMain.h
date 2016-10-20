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


	//色
	enum COLOR {
		NO,
		RED,
		BLUE,
		YELLOW,
		GREEN,
		PURPLE
	};

private:
	struct field_info {
		int color;//ブロックの色
		int fall_flag;//落下中かどうかのフラグ
		int move_flag;//移動中かどうかのフラグ
	};

	//落下ブロックの情報
	struct FallBlockInfo {
		FallBlockInfo() {
			Enable = FALSE;
			Counter = 0;
		}
		int Counter;			//落下ブロックのカウンタ(常に有効な変数です！！)(負の数でブロックが消滅してからの経過フレーム、正の数でブロックが生成されてからの時間)

		int Enable;			//落下中かどうか(TRUEで落下ブロック有効)

		COLOR BlockID[3][3];	//縦横3ずつのブロック領域としてブロックの位置情報を記録する
		int PlaceX, PlaceY;		//落下ブロックの中心位置の座標(配列の1,1の場所)
		int FallCount;			//落下カウントダウン(0で落下する)
		
		//キー入力による状態の保存用
		int Key_FlagFirstFall;			//高速落下モード(TRUEで有効)
		int Key_LRMove;				//左右移動(-1左、0移動無し、1右移動)
	};

	field_info field[10][16];


	int gameWindow;	//ゲーム画面を描画するハンドル

	int Flag_Pause;			//ポーズ状態かどうか(ゲームの進行がすべて停止します)(TRUEでポーズ)
	int Flag_pauseRequest;	//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)

	
	FallBlockInfo fallBlockInfo;	//落下ブロックの情報

	void Draw();
	void Update();
	void GameMain_Key();

	int isFallBlock_MoveX(int MoveVal);		//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
	int isFallBlock_MoveY(int MoveVal);		//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock();		//落下ブロックを生成する(戻り値:成功でTRUE)

	/*設定系*/
	void PauseRequest(int b_Flag);		//ポーズ状態のリクエスト
	void Delete_FallBlock();			//落下ブロックの無効化

	/*取得系*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY);	//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
	int	isPaused();					//ポーズ状態かどうかの取得(TRUEでポーズ)
	int isFallBlock_Falling();		//落下ブロックが落下中かどうかの取得(TRUEで落下中)
	int isFallBlock_Enable();		//落下ブロックが有効かどうかの取得(TRUEで有効)
	int getFallBlock_Interval();	//落下ブロックの前回の落下からのインターバルの取得(落下ブロックが存在するときは0が返ります)
	COLOR getBlockColor(int X, int Y, COLOR OutGameBlock);	//指定した座標のブロックの取得(第3引数は画面外のブロックを判定したときの戻り値)
};

