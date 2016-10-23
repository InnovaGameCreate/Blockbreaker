#pragma once
#include "PhaseController.h"

#ifndef PHASECONTROLLER_H_
#error PhaseController.hをIncludeしてください
#endif // !PHASECONTROLLER_H_



class Phase_GameMain : public PhaseController
{
public://定数とかの宣言
	static const int BLOCK_SIZE = 50;			//ブロックの縦横のピクセルサイズ
	static const int BLOCK_WIDTHNUM = 14;		//実際のブロックの横の個数
	static const int BLOCK_HEIGHTNUM = 18;		//実際のブロックの縦の個数
	static const int BLOCK_PADDINGUP = 1;		//描画するブロックの開始位置(上)
	static const int BLOCK_PADDINGDOWN = 0;		//描画するブロックの開始位置(下)
	static const int BLOCK_PADDINGLEFT = 0;		//描画するブロックの開始位置(左)
	static const int BLOCK_PADDINGRIGHT = 0;	//描画するブロックの開始位置(右)

	static const int  GAMEWINDOW_PADDINGX = 50;		//ゲーム画面のX方向のズレ
	static const int  GAMEWINDOW_PADDINGY = 55;		//ゲーム画面のY方向のズレ
	static const int  GAMEWINDOW_WIDTH = (BLOCK_WIDTHNUM - (BLOCK_PADDINGLEFT + BLOCK_PADDINGRIGHT))*BLOCK_SIZE;		//ゲーム画面の横幅
	static const int  GAMEWINDOW_HEIGHT = (BLOCK_HEIGHTNUM - (BLOCK_PADDINGUP + BLOCK_PADDINGDOWN))*BLOCK_SIZE;		//ゲーム画面の高さ

	static const int FALLBLOCK_SIZE = 3;		//落下するブロックの大きさ
	static const int FALLBLOCK_CENTER = FALLBLOCK_SIZE/2;	//落下するブロックの中心(基準)位置

	//ブロックの種類
	enum BLOCK_TYPE {
		BLOCK_TYPE_NO,//なし
		BLOCK_TYPE_RED,//赤
		BLOCK_TYPE_BLUE,//青
		BLOCK_TYPE_YELLOW,//黄
		BLOCK_TYPE_GREEN,//緑
		BLOCK_TYPE_PURPLE,//紫
		BLOCK_TYPE_TREE, //樹木の形のブロック（隣接する４方向のどこかが消えたときに一緒に消える）
		BLOCK_TYPE_BLACK,//黒色のブロック：置くまで色がわからない→おいたときにランダムで色が決定する
		BLOCK_TYPE_NOROUND,//枠で囲われたブロック（回せない）
		BLOCK_TYPE_RAINBOW,//虹色のブロック(下のブロックと同じ色になる)
		BLOCK_TYPE_BOM,//爆弾(問答無用で周囲のブロック破壊)
		BLOCK_TYPE_DOWNMARK,//下矢印マークのブロック(下に2段移動させる)
		BLOCK_TYPE_NUM		//ブロックの種類の数(画面外ブロック)
	};

private:
	//移動モーションのデータ
	struct BlockMoveMotion {
		BlockMoveMotion() {
			Enable = FALSE;
		}
		int Enable;			//移動モーションが有効かどうか
		int FromX, FromY;	//移動元座標
		int ToX, ToY;		//移動先座標
		int Count;			//移動カウント(0起算)
		double a;			//加速度
		double MaxSpeed;	//最高速度
	};
	//ブロック変化モーションのデータ
	struct BlockChangeMotion {
		BlockChangeMotion() {
			Enable = FALSE;
		}
		int Enable;			//ブロック変化モーションが有効かどうか
		BLOCK_TYPE From;	//ブロック変化元ブロック
		BLOCK_TYPE To;		//ブロック変化先ブロック
		int Count;			//ブロック変化カウント(0起算)
		int Length;			//ブロック変化モーションを行う時間
	};
	struct field_info {
		BLOCK_TYPE color;//ブロックの色
		int fall_flag;//落下中かどうかのフラグ
		int move_flag;//移動中かどうかのフラグ

		BlockMoveMotion blockMoveMotion;		//落下モーション
		BlockChangeMotion blockChangeMotion;	//ブロック変化モーション
	};

	struct Fallblock_Pack {
		BLOCK_TYPE BlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];	//縦横FALLBLOCK_SIZEずつのブロック領域としてブロックの位置情報を記録する
	};

	//ゲームサイクルの識別
	enum GameCycle {
		GameCycle_FALL,			//ブロックの落下
		GameCycle_BeforeFALL,	//ブロックの落下開始前
		GameCycle_Motion,		//ブロックのモーション中
		GameCycle_BlockFunc,	//ブロック効果(黒・虹色ブロックの色判定)
		GameCycle_Delete,		//ブロックの消去判定
		GameCycle_NUM			//ゲームサイクルの個数(設定無し)
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
	int Tex_BlockRED;		//赤ブロック
	int Tex_BlockBLUE;		//青ブロック
	int Tex_BlockYELLOW;	//黄色ブロック
	int Tex_BlockGREEN;		//緑ブロック
	int Tex_BlockPURPLE;	//紫ブロック
	int Tex_BlockTREE;		//樹木の形ブロック
	int Tex_BlockBLACK;		//黒ブロック
	int Tex_BlockRAINBOW;	//虹色ブロック

	int BGM;				//BGM


	int Flag_Pause;			//ポーズ状態かどうか(ゲームの進行がすべて停止します)(TRUEでポーズ)
	int Flag_pauseRequest;	//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)

	
	FallBlockInfo fallBlockInfo;	//落下ブロックの情報
	FallBlockInfo waitBlockinfo[2];//待機ブロックの情報

	GameCycle gameCycle;		//ゲームサイクル
	GameCycle NextgameCycle;	//次のゲームサイクル(モーション終了後に移動するサイクル)

	RandomTable randomTable;	//乱数テーブル

	void Draw();
	void DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type);	//ブロックを描画する(インゲーム座標)
	void Update();
	int Update_FallBlock();			//落下ブロックの落下処理(TRUEで落下ブロックの落下終了)
	void GameMain_Key();

	void Block_Black_Func();		//フィールドに存在する黒色ブロックの色を決定する
	void Block_Rainbow_Func();		//フィールドに存在する虹色ブロックの色を決定する

	int FallBlock_MoveX(int MoveVal);		//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
	int FallBlock_MoveY(int MoveVal);		//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
	int FallBlock_Rotate(int RotaVal);		//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)
	void FallBlock_addField();				//落下ブロックをフィールドブロックに変換する(つまり設置)
	void Block_Gravity(int InGameOnly = TRUE);	//フィールドブロックを重力で落下させる(TRUEでゲーム画面内のみ)
	int Block_Delete_Direct(int X, int Y, int CallGravityFlag = TRUE);		//フィールドブロックを削除する(重力計算を行うかどうかのフラグ)
	int Block_Delete_Type(int X, int Y, BLOCK_TYPE type, int CallGravityFlag = TRUE);	//指定した座標が指定したブロックだった場合に削除
	int Block_Delete();							//連続するフィールドブロックを削除する(ついでにお邪魔ブロックの処理も行う)(消去したブロックの数)
	void SequenceCount(int x, int y, int ID, int n[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter);	//隣接する同色ブロックのカウント
	void Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);	//フィールドのブロックにモーションを設定する
	void Block_SetChangeMotion(int x, int y, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength);					//フィールドのブロック移動にモーションを設定する
	void setGameCycle(GameCycle gameCycle, GameCycle NextgameCycle = GameCycle_NUM);	//ゲームサイクルを設定する(第2引数はゲームサイクルがモーションの場合のモーション終了後に移動するサイクル※モーション以外は無視されます)
	void Create_Wait_Block();//待機ブロックの生成
	//BLOCK_TYPE Get_Block_Type(int h);
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock(struct Fallblock_Pack *fallblock_Pack);		//落下ブロックを生成する(戻り値:成功でTRUE)
	int add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type);			//フィールドにブロックを追加する

	/*設定系*/
	void PauseRequest(int b_Flag);		//ポーズ状態のリクエスト
	void Delete_FallBlock();			//落下ブロックの無効化

	/*取得系*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY);	//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
	int	isPaused();					//ポーズ状態かどうかの取得(TRUEでポーズ)
	int isFallBlock_Falling();		//落下ブロックが落下中かどうかの取得(TRUEで落下中)
	int isFallBlock_Enable();		//落下ブロックが有効かどうかの取得(TRUEで有効)
	int getFallBlock_Interval();	//落下ブロックの前回の落下からのインターバルの取得(落下ブロックが存在するときは0が返ります)
	BLOCK_TYPE getBlockColor(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE);	//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
	int isBlock_PlayMoveMotion();		//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
	int isBlock_PlayChangeMotion();		//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
};

