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
	int pointNum;	//頂点の数(0〜PolygonPoints2_MAX)
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
extern void Base_BB_Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, TCHAR *GAMEVERNAME);	//ライブラリの初期化処理(最初に呼び出してください)(引数はWinMainと同じ)
extern void Base_BB_MainLoop();											//メインループ(戻りません)
extern void Base_BB_setFunc_InitAfterDXlibInit(void(*func)(void));		//DXライブラリの初期化が終わってから実行する初期化処理関数を設定する
extern void Base_BB_setFaze(FAZE FazeNo, PhaseController *phase);		//フェーズの定義を行う
extern int Base_BB_getWINDOW_WIDTH();									//設定している画面サイズの取得
extern int Base_BB_getWINDOW_HEIGHT();									//設定している画面サイズの取得
extern TCHAR *Base_BB_getGAMEVERSION();									//ゲームバージョンの取得

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

/*Calculations.cpp*/
/*変換系*/
extern double		map(double v, double sx, double sn, double dx, double dn);		//数値の範囲を別の範囲に変換する
extern int			Pot(int inSize);												//指定した値より大きい2のn乗を返す
extern double		getDegrees(double nDegrees);									//-180〜180の値に変換
extern double		ConvertPixpF_To_DegpF(double Speed, double R);					//普通の速度を角速度に変換(ピクセル/フレーム→度/フレーム)(引数は普通の速度、半径)
extern double		ConvertDegpF_To_PixpF(double DegSpeed, double R);				//角速度を普通の速度に変換(度/フレーム→ピクセル/フレーム)(引数は角速度、半径)
extern int			circulating(int Src, int Min, int Max);							//指定した範囲で指定した値を循環させるように変換する(Min以上Max未満)
extern double		circulating_d(double Src, double Min, double Max);				//指定した範囲で指定した値を循環させるように変換する(Min以上Max未満)(double型)
extern double		InRange(double val, double min, double max);					//ある値を最大値を超える場合は最大値に、最小値を下回る場合は最小値にする(double型)
extern double		CutDecimal(double src, int No = 5);								//指定の小数桁数で切り捨てる(デカい数字でうまくいくかは知りません)
extern double		ExpandValue(double InVal, double Center, double Ex);			//ある値(InVal)をある値中心(Center)に拡大・縮小(Ex)したときの値を取得する
extern void			Gradation_RGB(int R1, int G1, int B1, int R2, int G2, int B2, double X, int *ansR, int *ansG, int *ansB);	//RGBカラーでグラディエーションをする(Xは目的色までの割合(0【基本色】〜100【目的色】)
extern void			RGB_to_HSV(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *V);				//RGBからHSVに変換
extern void			RGB_to_HSL(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *L);				//RGBからHSLに変換
extern void			HSV_to_RGB(double H, double S, double V, unsigned char *R, unsigned char *G, unsigned char *B);				//HSVからRGBに変換
extern void			HSL_to_RGB(double H, double S, double L, unsigned char *R, unsigned char *G, unsigned char *B);				//HSLからRGBに変換
extern unsigned int ConvertCollect1to4(unsigned char bit4, unsigned char bit3, unsigned char bit2, unsigned char bit1);								//1byte(unsigned char)の値4個を4byte(unsigned int)1個に変換する
extern void			ConvertCollect4to1(const unsigned int src, unsigned char *bit4, unsigned char *bit3, unsigned char *bit2, unsigned char *bit1);	//4byte(unsigned int)1個を1byte(unsigned char)の値4個に変換する
																																					/*描画系*/
extern void			ClearDrawScreenTogrHandle(int grHandle);						//指定したグラフィックハンドルにClearDrawScreenを行う(1フレームに1万回とか呼ぶと重くなります)
extern void			DrawTileGraph(int zx, int zy, int GrHandle);					// 画面いっぱいに画像を描画する(zx, zy : ずらすドット数)(ループ)
extern void			DrawRotaImage3D(double X, double Y, double ExLate, double AngleX, double AngleY, double AngleZ, int grHandle);	//画像の3D回転描画(度指定)
extern void			DrawPolygon2D_Notexture2(PolygonPoints2 *polygonPoints, unsigned int color, int fillFlag);	//多角形を描画する2(テクスチャ無し)
extern void			DrawLineAA_Polar(double X, double Y, double rota, double length, unsigned int Color, float Thicknes = 1.0f);//線の描画(極座標)
extern void			draw_Circle(double X, double Y, double R, int Kakudo);						//円グラフのような円を描画する(旧、敵のHPバー)(描画したい中心位置X,Y,多分半径,描画する角度)
extern void			draw_Circle2(int X, int Y, double per, int Texture, int Texture2);			//円グラフのような円を描画する(描画したい中心位置X,Y,描画する360度に対する割合,グラフ部分のテクスチャ,円周部分のテクスチャ)
extern void			DrawArrow(double X, double Y, double vector, double length, unsigned int Color = GetColor(255, 255, 255), float Thickness = 1.0f);	//線の描画(極座標)
																																						/*あたり判定*/
extern int			collision_rect(double rectX, double rectY, double Width, double Height, double pX, double pY);						//XY方向に平行な四角形と点のあたり判定
extern int			collision_polygon2(PolygonPoints2 *polygon, double pointX, double pointY);											//多角形と点のあたり判定
extern int			collision_tri2(PolygonPoints2 *tri, double pointX, double pointY);													//三角形と点のあたり判定
extern int			collision_polygon_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2);	//多角形と線分のあたり判定
extern int			collision_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2);			//線分と線分のあたり判定
extern int			collisionLC(double X1, double Y1, double X2, double Y2, double  circleX, double circleY, double circleR, Vec *ans1, Vec *ans2);//円と直線の交点
																																				   /*その他*/
extern double		getRotation(double X1, double Y1, double X2, double Y2);			//2点間の角度の取得(度)
extern double		getDistance(double X1, double Y1, double X2, double Y2);			//2点間の距離を求める
extern double		getMoveDistance(double a, double MaxSpeed, int Count);				//加速度、最大速度、移動開始からの経過時間から現在の移動距離を計算する
extern double		Cross_product(Vec *a, Vec *b);										//外積の計算
extern Vec			Vector_component(double x, double y, double pointX, double pointY); //ベクトルの成分計算
extern long long	powi64(long long _Left, int _Yx);									//long long型のpow関数(_Yx < 0は非対応)
extern double		getGraph_Triangle(int Cycle);										//三角波を返す
extern double		getGraph_Sin(double frameVal, double Delta, double Shift);			//サイン波を返す(フレーム数を入れるといい感じになる)
extern void			PolygonPoints2_setRect(double x, double y, double w, double h, PolygonPoints2 *rect);//PolygonPointsに四角形を設定する
