#pragma once

#include "Base_BB_Enum.h"	//enum定義(別ファイル)
#include "Base_BB_Define.h"	//define定義(別ファイル)

#include "Base_BB_PhaseController.h"
#include "Base_BB_FpsController.h"
#include "Base_BB_Log.h"
#include "Base_BB_RandomTable.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//構造体の宣言
//typedefするのはプログラム全体で使用するもののみにしてください。
//ファイル内でのみ使用する構造体はtypedefしないでください。(補完で出てきてうざいので)

//キーバインドの設定(DXライブラリのキーコード)
typedef struct KeyBind {
	int Key_ENTER;			//決定キー
	int Key_ENTER2;			//決定キー2
	int Key_PAUSE;			//キャンセル/ポーズ
	int Key_PAUSE2;			//キャンセル/ポーズ2
	int Key_RotateL;		//落下するブロックを反時計回りに回転させる
	int Key_RotateL2;		//落下するブロックを反時計回りに回転させる2
	int Key_RotateR;		//落下するブロックを時計回りに回転させる
	int Key_RotateR2;		//落下するブロックを時計回りに回転させる2
	int Key_UP;				//項目選択:上
	int Key_UP2;			//項目選択:上2
	int Key_DOWN;			//項目選択:下/落下するブロックの加速
	int Key_DOWN2;			//項目選択:下/落下するブロックの加速2
	int Key_LEFT;			//項目選択:左/落下するブロックの左移動
	int Key_LEFT2;			//項目選択:左/落下するブロックの左移動2
	int Key_RIGHT;			//項目選択:右/落下するブロックの右移動
	int Key_RIGHT2;			//項目選択:右/落下するブロックの右移動2
}KeyBind;

//キーバインドの設定(ゲームパッド)(DXライブラリのキーコード)
typedef struct KeyBindjoy {
	unsigned int Joy_ENTER[4];		//決定キー
	unsigned int Joy_PAUSE[4];		//キャンセル/ポーズ
	unsigned int Joy_RotateL[4];	//落下するブロックを反時計回りに回転させる
	unsigned int Joy_RotateR[4];	//落下するブロックを時計回りに回転させる
	unsigned int Joy_UP[4];			//項目選択:上
	unsigned int Joy_DOWN[4];		//項目選択:下/落下するブロックの加速
	unsigned int Joy_LEFT[4];		//項目選択:左/落下するブロックの左移動
	unsigned int Joy_RIGHT[4];		//項目選択:右/落下するブロックの右移動
}KeyBindjoy;

#define PolygonPoints2_MAX 30	//PolygonPoints2で扱える頂点の最大個数
//多角形の座標(辺の座標)なるべく時計回りで定義しよう(PolygonPoints2_MAX角形まで)
typedef struct {
private:
	int pointNum;	//頂点の数(0～PolygonPoints2_MAX)
public:
	double X[PolygonPoints2_MAX];
	double Y[PolygonPoints2_MAX];
	//○角形の取得
	int getpointNum() {
		return min(pointNum, PolygonPoints2_MAX);
	}
	//○角形の設定
	void SetpointNum(int pointnum) {
		if (pointnum < 0)	pointnum = 0;
		if (pointnum > PolygonPoints2_MAX) pointnum = PolygonPoints2_MAX;
		pointNum = pointnum;
	}
}PolygonPoints2;

//ベクトル関連
typedef struct {
	double x, y;
}Vec;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//関数群
/*MainLoop.cpp*/
void Base_BB_Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);	//ライブラリの初期化処理(最初に呼び出してください)(引数はWinMainと同じ)
void Base_BB_MainLoop();														//メインループ(戻りません)
void Base_BB_setFunc_InitAfterDXlibInit(void(*func)(void));								//DXライブラリの初期化が終わってから実行する初期化処理関数を設定する
void Base_BB_setFaze(FAZE FazeNo, PhaseController *phase);								//フェーズの定義を行う

extern void setKeybind(KeyBind *keyBind = NULL);								//キーバインドの設定(NULLで規定値)
extern void setUSEGAMEPAD(int type = 0);										//使用するゲームパッドの設定(引数省略で設定無し)
extern void	SetAnalogueStickMode(ANALOGSTICKMODE type = ANALOGSTICKMODE_NOUSE);	//ゲームパッドのアナログスティックの動作方法の設定
extern void setClearScreen(int Flag);											//画面のクリアを行うかどうか(0行わない)(するとこはします)
extern void SetDrawing_interval(int Mode);										//描画間隔の設定(0から項目順)
extern void SetWindowMode(int Mode);											//ウィンドウモードの設定(0から項目順)
extern void SetModeVSync(int Mode);												//垂直同期の設定(0から項目順)
extern void SetModeClear(int Mode);												//画面消去の設定(0から項目順)
extern void SetModeCursor(int Mode, int WinMode);								//マウスカーソルの設定(0から項目順)(ウィンドウモードの設定と同じ引数)
extern void SetModeMultiThread(int Mode);										//マルチスレッドでの動作の設定(0から項目順)
extern void SetTextureCut(int Mode);											//テクスチャの分割の設定(0から項目順)
extern void setKeybindjoy(KeyBindjoy *keyBindjoy);								//キーバインド設定(ゲームパッド)(NULLで規定値を設定)
extern void ExitGameRequest();													//プログラムを終了する

extern int	isMultiThread();						//マルチスレッドで動作するかどうかの取得(FALSEシングル)
extern int	gettUSEGAMEPAD();						//使用するゲームパッドの取得
extern unsigned int getKey(int KEYNO);				//キーの入力状態を取得する(DXライブラリで定義されているキーの番号)(戻り値：キーが押されている時間、押されていないときは0)
extern unsigned int getJoyKey(int JoyKeyNO);		//ゲームパッド入力状態の取得(DXライブラリで定義されているキーの番号)(戻り値：キーが押されている時間、押されていないときは0)(ゲームパッド用)
extern unsigned int getKeyBind(KEYBIND kEYBIND);	//キーバインドでのキー入力情報の取得(0押してない、1押した直後)
extern unsigned int getFrameCount(THREAD thread);	//ゲームが起動してからの経過フレーム数を取得する

extern void 		Changefaze(FAZE NO, THREAD FLAG, int arg = 0, int b_Wait_Loading = FALSE);	//フェーズ変更(変更したいフェーズ番号、呼び出しスレッド、引数1、描画スレッドのフェーズ変更処理の完了を処理スレッドが待機するかどうか)

/*StartDialog.cpp*/
extern void StartDialog_Initialize(HINSTANCE hInstance);	//初期化
extern void StartDialog_Show();								//起動設定画面の表示

/*LoadMenu.cpp*/
extern void LoadMenu_Initialize();		//初期化
extern void LoadMenu_Draw();			//ロード画面の表示
extern void LoadMenu_Draw2();			//ロード画面の表示(最初の起動時用)

/*Font.cpp*/
extern void Font_init();					//初期化
extern int Font_getHandle(FONTTYPE font);	//フォントハンドルの取得
extern void Font_DrawStringWithShadow(double x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);					//影付き文字列の描画
extern void Font_DrawStringCenterWithShadow(double Center_x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);	//影付き文字列描画(Xのみ中心指定)