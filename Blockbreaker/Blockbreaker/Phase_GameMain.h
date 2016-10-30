#pragma once
#include "SelectItem.h"
#include "Define.h"

class Phase_GameMain : public PhaseController
{
public://定数とかの宣言
	static const int BLOCK_SIZE = 40;			//ブロックの縦横のピクセルサイズ
	static const int BLOCK_WIDTHNUM = 11;		//実際のブロックの横の個数
	static const int BLOCK_HEIGHTNUM = 24;		//実際のブロックの縦の個数
	static const int BLOCK_PADDINGUP = 1;		//描画するブロックの開始位置(上)
	static const int BLOCK_PADDINGDOWN = 1;		//描画するブロックの開始位置(下)
	static const int BLOCK_PADDINGLEFT = 0;		//描画するブロックの開始位置(左)
	static const int BLOCK_PADDINGRIGHT = 0;	//描画するブロックの開始位置(右)
	static const int BLOCK_WIDTHNUM_INGAME = BLOCK_WIDTHNUM - (BLOCK_PADDINGLEFT + BLOCK_PADDINGRIGHT);		//画面内の横のブロックの個数
	static const int BLOCK_HEIGHTNUM_INGAME = BLOCK_HEIGHTNUM - (BLOCK_PADDINGUP + BLOCK_PADDINGDOWN);		//画面内の縦のブロックの個数

	static const int GAMEWINDOW_PADDINGX = 70;	//ゲーム画面のX方向のズレ
	static const int GAMEWINDOW_PADDINGY = 32;	//ゲーム画面のY方向のズレ
	static const int GAMEWINDOW_WIDTH = BLOCK_WIDTHNUM_INGAME*BLOCK_SIZE;	//ゲーム画面の横幅
	static const int GAMEWINDOW_HEIGHT = BLOCK_HEIGHTNUM_INGAME*BLOCK_SIZE;	//ゲーム画面の高さ

	static const int FALLBLOCK_SIZE = 3;		//落下するブロックの大きさ
	static const int GAMEOVER_BORDER = 4;		//ゲームオーバーにする場所
	static const int FALLBLOCK_CENTER = FALLBLOCK_SIZE/2;	//落下するブロックの中心(基準)位置

	//ブロックの種類
	enum BLOCK_TYPE {
		BLOCK_TYPE_NO,//なし
		BLOCK_TYPE_RED,//赤
		BLOCK_TYPE_BLUE,//青
		BLOCK_TYPE_YELLOW,//黄
		BLOCK_TYPE_GREEN,//緑
		BLOCK_TYPE_PURPLE,//紫
		//ここから特殊ブロック↓
		BLOCK_TYPE_RED_ARROW_X,		//赤(平行矢印)
		BLOCK_TYPE_RED_ARROW_Y,		//赤(垂直矢印)
		BLOCK_TYPE_RED_ARROW_XY,	//赤(斜め右上)
		BLOCK_TYPE_RED_ARROW_XY2,	//赤(斜め右下)
		BLOCK_TYPE_BLUE_ARROW_X,	//青(平行矢印)
		BLOCK_TYPE_BLUE_ARROW_Y,	//青(垂直矢印)
		BLOCK_TYPE_BLUE_ARROW_XY,	//青(斜め右上)
		BLOCK_TYPE_BLUE_ARROW_XY2,	//青(斜め右下)
		BLOCK_TYPE_YELLOW_ARROW_X,	//黄(平行矢印)
		BLOCK_TYPE_YELLOW_ARROW_Y,	//黄(垂直矢印)
		BLOCK_TYPE_YELLOW_ARROW_XY,	//黄(斜め右上)
		BLOCK_TYPE_YELLOW_ARROW_XY2,//黄(斜め右下)
		BLOCK_TYPE_GREEN_ARROW_X,	//緑(平行矢印)
		BLOCK_TYPE_GREEN_ARROW_Y,	//緑(垂直矢印)
		BLOCK_TYPE_GREEN_ARROW_XY,	//緑(斜め右上)
		BLOCK_TYPE_GREEN_ARROW_XY2,	//緑(斜め右下)
		BLOCK_TYPE_PURPLE_ARROW_X,	//紫(平行矢印)
		BLOCK_TYPE_PURPLE_ARROW_Y,	//紫(垂直矢印)
		BLOCK_TYPE_PURPLE_ARROW_XY,	//紫(垂直矢印)
		BLOCK_TYPE_PURPLE_ARROW_XY2,//紫(垂直矢印)
		BLOCK_TYPE_TREE, //樹木の形のブロック（隣接する４方向のどこかが消えたときに一緒に消える）
		BLOCK_TYPE_BLACK,//黒色のブロック：置くまで色がわからない→おいたときにランダムで色が決定する
		BLOCK_TYPE_NOROUND,//枠で囲われたブロック（回せない）
		BLOCK_TYPE_RAINBOW,//虹色のブロック(下のブロックと同じ色になる)
		BLOCK_TYPE_BOM,//爆弾(問答無用で周囲のブロック破壊)
		BLOCK_TYPE_NUM		//ブロックの種類の数(画面外ブロック)
	};

	//ポーズの種類
	enum PauseMode {
		PauseMode_NO,		//ポーズ状態になっていない(通常)
		PauseMode_NOMAL,	//通常の尾イーズ(escでポーズするやつ)
		PauseMode_GameOver,	//ゲームオーバー
		PauseMode_NUM		//個数(リクエスト無し)
	};

	//ブロック変化モーションの種類
	enum BlockChangeMotionType {
		BlockChangeMotionType_NO,		//モーション無し
		BlockChangeMotionType_NOMAL,	//通常(fromからtoへ)
		BlockChangeMotionType_EXPLOSION,//爆発(消滅)
		BlockChangeMotionType_SMALL,	//小さくなって消える
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
			Type = BlockChangeMotionType_NO;
		}
		BlockChangeMotionType Type;	//ブロック変化モーションの種類
		BLOCK_TYPE From;			//ブロック変化元ブロック
		BLOCK_TYPE To;				//ブロック変化先ブロック
		int Count;					//ブロック変化カウント(0起算)
		int Length;					//ブロック変化モーションを行う時間
	};
	struct field_info {
		BLOCK_TYPE color;//ブロックの色
		int fall_flag;//落下中かどうかのフラグ
		int move_flag;//移動中かどうかのフラグ


		double DrawPlaceX, DrawPlaceY;			//描画位置[インゲーム座標](マルチだと描画位置がずれる問題があったので)
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
		GameCycle_Update,		//ブロックの計算ループ
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

	SelectItem<Phase_GameMain> pauseMenu = SelectItem<Phase_GameMain>(WINDOW_WIDTH/2, 600);	//ポーズメニューの項目

	//ブロックの計算ループで使用する変数
	int Loop_No;			//計算ループのどの処理をしているか(-1で計算ループ未使用)
	GameCycle Loop_Next;	//計算ループ後に移行するゲームサイクル

	//ブロックの全体移動で使用する変数
	BlockMoveMotion Block_AllMovedata;

	//フライテキスト表示クラス
	FlyText flyText;


	int gameWindow;	//ゲーム画面を描画するハンドル
	int Tex_BlockRED;				//赤ブロック
	int Tex_BlockRED_ARROW_X;		//赤ブロック(平行矢印)
	int Tex_BlockRED_ARROW_Y;		//赤ブロック(垂直矢印)
	int Tex_BlockRED_ARROW_XY;		//赤ブロック(斜め右上)
	int Tex_BlockRED_ARROW_XY2;		//赤ブロック(斜め右下)
	int Tex_BlockBLUE;				//青ブロック
	int Tex_BlockBLUE_ARROW_X;		//青ブロック(平行矢印)
	int Tex_BlockBLUE_ARROW_Y;		//青ブロック(垂直矢印)
	int Tex_BlockBLUE_ARROW_XY;		//青ブロック(斜め右上)
	int Tex_BlockBLUE_ARROW_XY2;	//青ブロック(斜め右下)
	int Tex_BlockYELLOW;			//黄色ブロック
	int Tex_BlockYELLOW_ARROW_X;	//黄色ブロック(平行矢印)
	int Tex_BlockYELLOW_ARROW_Y;	//黄色ブロック(垂直矢印)
	int Tex_BlockYELLOW_ARROW_XY;	//黄色ブロック(斜め右上)
	int Tex_BlockYELLOW_ARROW_XY2;	//黄色ブロック(斜め右下)
	int Tex_BlockGREEN;				//緑ブロック
	int Tex_BlockGREEN_ARROW_X;		//緑ブロック(平行矢印)
	int Tex_BlockGREEN_ARROW_Y;		//緑ブロック(垂直矢印)
	int Tex_BlockGREEN_ARROW_XY;	//緑ブロック(斜め右上)
	int Tex_BlockGREEN_ARROW_XY2;	//緑ブロック(斜め右下)
	int Tex_BlockPURPLE;			//紫ブロック
	int Tex_BlockPURPLE_ARROW_X;	//紫ブロック(平行矢印)
	int Tex_BlockPURPLE_ARROW_Y;	//紫ブロック(垂直矢印)
	int Tex_BlockPURPLE_ARROW_XY;	//紫ブロック(斜め右上)
	int Tex_BlockPURPLE_ARROW_XY2;	//紫ブロック(斜め右下)
	int Tex_BlockTREE;				//樹木の形ブロック
	int Tex_BlockBLACK;				//黒ブロック
	int Tex_BlockRAINBOW;			//虹色ブロック
	int Tex_BlockBOMB;				//爆弾ブロック
	int Tex_BlockFireEffect;		//炎エフェクトブロック
	int Tex_BlockFireEffect2;		//炎エフェクトブロックのマスク画像
	int haikei;				//背景

	int BGM;				//BGM


	PauseMode Flag_Pause;				//ポーズ状態かどうか(ゲームの進行がすべて停止します)
	PauseMode Flag_pauseRequest;		//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)

	
	FallBlockInfo fallBlockInfo;	//落下ブロックの情報
	FallBlockInfo waitBlockinfo[2];//待機ブロックの情報

	GameCycle gameCycle;		//ゲームサイクル
	int gameCycleFirstCallFlag;	//ゲームサイクルが変更されたときにTRUEが代入される

	RandomTable randomTable;	//乱数テーブル

	int Count_PlayTime;		//経過フレーム数(ポーズ、一時停止などでカウントアップが一時停止する)
	int Count_Pause;		//ポーズ時のカウンタ
	int Count_Turn;			//経過ターン数（ブロック落下時に加算）

	void Draw();
	void DrawBlock(double CenterX, double CenterY, BLOCK_TYPE type, double Scale = 1);	//ブロックを描画する(インゲーム座標)
	int Update_FieldBlock();		//フィールドブロックの細々とした計算ループ
	int Update_MoveMotion();		//移動モーションの更新(移動モーションが行われたときはTRUE)
	int Update_ChangeMotion();		//変化モーションの更新(変化モーションが行われたときはTRUE)
	void Update_Counter();			//カウンタのカウントアップ
	void Update();
	void Update_Final();			//Update後に呼ばれる
	int Update_FallBlock();			//落下ブロックの落下処理(TRUEで落下ブロックの落下終了)
	void GameMain_Key();

	void Block_Black_Func();		//フィールドに存在する黒色ブロックの色を決定する
	void Block_Rainbow_Func();		//フィールドに存在する虹色ブロックの色を決定する
	void Block_BOMB_Func();			//フィールドに存在する爆弾ブロックを爆破する

	int FallBlock_MoveX(int MoveVal, int CollisionFieldBlock = TRUE);		//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
	int FallBlock_MoveY(int MoveVal, int CollisionFieldBlock = TRUE);		//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
	int FallBlock_Rotate(int RotaVal);		//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)
	void FallBlock_addField();				//落下ブロックをフィールドブロックに変換する(つまり設置)
	void Block_Gravity(int InGameOnly = TRUE);	//フィールドブロックを重力で落下させる(TRUEでゲーム画面内のみ)
	int Block_Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int MotionLengh = 40);		//フィールドブロックを削除する
	int Block_Delete_Type(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int MotionLengh = 40);	//指定した座標が指定したブロックだった場合に削除
	int Block_Delete();							//連続するフィールドブロックを削除する(ついでに消去によって発動する効果も発動する)(消去したブロックの数)
	int Block_Delete_OutScreen();//画面外のブロックをすべて削除する(消去したブロックの数)
	void under_Block();							//下からブロックがわいてくる
	void SequenceCount(int x, int y, int ID, int n[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter);	//隣接する同色ブロックのカウント
	int isSameColorBlock(BLOCK_TYPE type1, BLOCK_TYPE type2, int FirstFlag = FALSE);		//指定した2個のブロックが同色ブロックかどうかの取得(TRUEで同色)(FirstFlagがTRUEで簡略計算します)
	void Block_SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);					//フィールドのブロックに移動モーションを設定する
	void Block_SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength);	//フィールドのブロックに変化モーションを設定する(これ単体で使用して事故っても知りません)
	void Block_SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int MotionLength);				//フィールドのブロックに変化モーション(通常)を設定する
	void Block_SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int MotionLength);			//フィールドのブロックに変化モーション(通常)を設定する(変化元指定)
	void Block_SetChangeMotion_EXPLOSION(int x, int y, int MotionLength);							//フィールドのブロックに変化モーション(爆発)を設定する
	void Block_SetChangeMotion_SMALL(int x, int y, int MotionLength);								//フィールドのブロックに変化モーション(小さくなって消える)を設定する
	void setGameCycle(GameCycle gameCycle);			//ゲームサイクルを設定する
	void UpdateBlockRequest(GameCycle Next);		//ブロック情報を更新するようにリクエスト
	void Block_AllMoveRequest(int X, int Y);		//フィールド全体のブロックを指定した分だけ移動するリクエストをする(ゲームを一時停止して動かします)
	void Block_AllMove(int X, int Y);				//フィールド全体のブロックを指定した分だけ移動する(画面外に出てしまうブロックは消滅します)
	int JudgeGameOver();							//ゲームオーバーになっているかどうかの確認
	int getBlockTexture(BLOCK_TYPE type);			//ブロックタイプよりテクスチャハンドルの取得
	void Create_Wait_Block();//待機ブロックの生成
	void pauseMenu_Cannel();						//ポーズ解除ボタンが押されたとき
	void pauseMenu_ReStart();						//やり直すボタンが押されたとき
	void pauseMenu_End();							//ゲーム終了ボタンが押されたとき
	//BLOCK_TYPE Get_Block_Type(int h);
public:


	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	int Create_FallBlock(struct Fallblock_Pack *fallblock_Pack);		//落下ブロックを生成する(戻り値:成功でTRUE)
	int add_FraldBlock(int X, int Y, BLOCK_TYPE brock_type, int Override = FALSE, int OutScreen = FALSE, BlockChangeMotionType MotionType = BlockChangeMotionType_NO, int MotionLengh = 40, BLOCK_TYPE *Before = NULL);			//フィールドにブロックを追加(削除)する(移動モーションは削除されます)

	/*設定系*/
	void PauseRequest(PauseMode pauseMode);	//ポーズ状態のリクエスト
	void Delete_FallBlock();				//落下ブロックの無効化

	/*取得系*/
	void Convert_Ingame_FromBlock(int blockX, int blockY, double XVal, double YVal, double * IngameX, double * IngameY);	//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
	PauseMode getPauseMode();		//ポーズ状態の取得
	int isFallBlock_Falling();		//落下ブロックが落下中かどうかの取得(TRUEで落下中)
	int isFallBlock_Enable();		//落下ブロックが有効かどうかの取得(TRUEで有効)
	int getFallBlock_Interval();	//落下ブロックの前回の落下からのインターバルの取得(落下ブロックが存在するときは0が返ります)
	BLOCK_TYPE getBlockColor(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE);	//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
	int isBlock_PlayMoveMotion();		//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
	int isBlock_PlayChangeMotion();		//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
	void Restart();						//リスタート
	void RestoreGraphCallback();		//フルスクリーンに復帰時に呼ばれる
};

