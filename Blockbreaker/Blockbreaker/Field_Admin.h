#pragma once
#include "Define.h"
#include "Block_Field.h"

//フィールドブロック統括クラス
class Field_Admin
{
public:
	void Init_Draw();	//初期化(描画処理)
	void Init_Update();	//初期化(計算処理)
	void Restart();		//リスタート処理

	/*基本処理*/
	void Draw_Block();	//ブロック描画処理
	void Draw_Lay();	//レーザーエフェクト描画処理
	void key();			//キー処理
	int Update_MoveMotion();	//移動モーションの更新(移動モーションが行われたときはTRUE)
	int Update_ChangeMotion();	//変化モーションの更新(変化モーションが行われたときはTRUE)
	int Update_AllMove();		//全体移動の更新(TRUE全体移動の更新を行った)
	void Update_Lay();			//破壊光線エフェクトの更新
	void Update_DrawData();		//描画情報の更新

	void ChainCount_Reset();	//ブロックのチェイン数をリセットする

	/*ブロックに変更を加える系*/
	int add_FieldBlock(int X, int Y, BLOCK_TYPE type, int Override = FALSE, int OutScreen = FALSE, BLOCK_TYPE *Before = NULL, int UseVirtualField = FALSE);	//フィールドにブロックを設置する
	void add_Under();						//下からブロックがわいてくる
	void Gravity(int InGameOnly = TRUE);	//フィールドブロックを重力で落下させる
	void Delete_Lay();						//破壊光線でブロックを破壊する
	int Delete_OutScreen();					//画面外のブロックをすべて削除する(消去したブロックの数)
	int Delete_Join(const int Len = BLOCK_DELETE_LEN, int Flag_Event = TRUE);//連続するフィールドブロックを削除する(ついでに消去によって発動する効果も発動する)(消去したブロックの数)
	void Func_Black();						//フィールドに存在する黒色ブロックの色を決定する
	void Func_Rainbow();					//フィールドに存在する虹色ブロックの色を決定する(下から順に)
	void Func_BOMB();						//フィールドに存在する爆弾ブロックを爆破する
	void Func_2BOMB();						//フィールドに存在する2爆弾ブロックを爆破する
	void Func_BOMBColor();					//フィールドに存在する同色爆弾ブロックを爆破する

	BlockMoveMotion * getBlockMoveMotion();	//ブロック全体移動クラスのポインタを取得
	void getField_Padding(double * Field_PaddingX, double * Field_PaddingY);	//フィールド全体のズレを取得する
	int isPlayingMoveMotion();				//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
	int isPlayingChangeMotion();			//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
	BLOCK_TYPE getBlockType(int X, int Y, int useOutScreenBlock = FALSE, int InGame = TRUE, int UseVirtualField = FALSE);	//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
	int getUpperX(int x);					//指定したX座標の一番上のブロックのY座標を取得する(見えている座標のみで判断)
	int getmaxUpperX();						//最大の高さのブロックのY座標を取得する
	int getChain();							//現在のチェイン数を取得する
private:
	Block_Field field[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];			//実際のフィールド情報
	Block_Field Virtualfield[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];	//計算上のフィールド情報UseVirtualField=TRUEで使用

	BlockMoveMotion AllMovedata;	//ブロックの全体移動で使用する変数

	PolygonPoints2 lay;				//破壊光線のエフェクト情報
	int Count_lay;					//破壊光線エフェクトの経過時間

	int ChainCount;	//ブロックの消去のチェイン数

	/*ブロックに変更を加える系*/
	void setBlock_Rect(int x, int y, int w, int h);	//指定したエリアにブロックを設置する(消去判定が入らないように設置します)
	void AllMove(int X, int Y);						//フィールド全体のブロックを指定した分だけ移動する(画面外に出てしまうブロックは消滅します)
	int Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO, int Delay = 0);		//フィールドブロックを削除する
	int Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion = BlockChangeMotionType_NO);	//指定した座標が指定したブロックだった場合に削除

	/*モーション設定関係*/
	void SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay);	//フィールドのブロックに変化モーションを設定する(これ単体で使用して事故っても知りません)
	void SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int Delay = 0);			//フィールドのブロックに変化モーション(通常)を設定する
	void SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int Delay = 0);	//フィールドのブロックに変化モーション(通常)を設定する(変化元指定)
	void SetChangeMotion_EXPLOSION(int x, int y, BLOCK_TYPE From, int Delay = 0);	//フィールドのブロックに変化モーション(爆発)を設定する
	void SetChangeMotion_SMALL(int x, int y, BLOCK_TYPE From, int Delay = 0);		//フィールドのブロックに変化モーション(小さくなって消える)を設定する
	void SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed);//フィールドのブロック移動にモーションを設定する

	void Virtualfield_Update();							//仮想フィールドを現在のフィールドと一致させる
	void AllMoveRequest(int X, int Y);			//フィールド全体のブロックを指定した分だけ移動するリクエストをする(ゲームを一時停止して動かします)
	
	/*隣接個数計算関係*/
	void SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int * Counter, int UseVirtualField = FALSE);		//隣接する同色ブロックにマーカーを付ける
	void CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField = FALSE);	//SequenceCountで使用するマーカーテーブルを作成する(有効なエリア)(UseVirtualField=TRUEで仮想の面を使用する)

																																				
	double Score_Scale(int len);//隣接するブロックの消す時にスコアの倍率を求める関数

	
};

