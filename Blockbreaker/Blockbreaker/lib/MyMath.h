#pragma once
//自作計算関数(別により高速で動くとか無い)

#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "MyMathx64_d.lib")
	#else
		#pragma comment(lib, "MyMathx86_d.lib")
	#endif // WIN64
#else
	#ifdef _WIN64
		#pragma comment(lib, "MyMathx64.lib")
	#else
		#pragma comment(lib, "MyMathx86.lib")
	#endif // WIN64
#endif // _DEBUG

#include <math.h>

namespace SK {
	namespace Math {
		/*取得系*/
		extern double PI();														//PIの値を取得
		extern double Rotation(double X1, double Y1, double X2, double Y2);		//2点間の角度の取得(度)
		extern double getDistance(double X1, double Y1, double X2, double Y2);	//2点間の距離を求める
		extern double getGraph_Triangle(int Cycle, int Count);					//三角波の取得
		extern double getGraph_Sin(double frameVal, double Delta, double Shift);//サイン波の取得
		extern int Pot(int inSize);												//指定した値より大きい2のn乗を取得
		extern double getMoveDistance(double a, double MaxSpeed, int Count);	//加速度、最大速度、移動開始からの経過時間から現在の移動距離を取得

		/*変換系*/
		extern double RadToDeg(double rad);										//ラジアンを度に変換する
		extern double DegToRad(double deg);										//度をラジアンに変換する
		extern double map(double v, double sx, double sn, double dx, double dn);//数値の範囲を別の範囲に変換する
		extern int circulating(int Src, int Min, int Max);						//指定した範囲で指定した値を循環させるように変換する(Min以上Max未満)
		extern double circulating_d(double Src, double Min, double Max);		//指定した範囲で指定した値を循環させるように変換する(Min以上Max未満)(double型)
		extern double InRange(double val, double min, double max);				//ある値を最大値を超える場合は最大値に、最小値を下回る場合は最小値にする(double型)
		extern double getDegrees(double nDegrees);								//-180～180の値に変換
		extern double PixpF_To_DegpF(double Speed, double R);					//普通の速度を角速度に変換(ピクセル/フレーム→度/フレーム)(引数は普通の速度、半径)
		extern double DegpF_To_PixpF(double DegSpeed, double R);				//角速度を普通の速度に変換(度/フレーム→ピクセル/フレーム)(引数は角速度、半径)
		extern void RGB_to_HSV(unsigned char r, unsigned char g, unsigned char b, double * H, double * S, double * V);	//RGBからHSVに変換
		extern void RGB_to_HSL(unsigned char r, unsigned char g, unsigned char b, double * H, double * S, double * L);	//RGBからHSLに変換
		extern void HSV_to_RGB(double H, double S, double V, unsigned char * R, unsigned char * G, unsigned char * B);	//HSVからRGBに変換
		extern void HSL_to_RGB(double H, double S, double L, unsigned char * R, unsigned char * G, unsigned char * B);	//HSLからRGBに変換
		extern unsigned int ConvertCollect1to4(unsigned char bit4, unsigned char bit3, unsigned char bit2, unsigned char bit1);	//1byte(unsigned char)の値4個を4byte(unsigned int)1個に変換する
		extern void ConvertCollect4to1(const unsigned int src, unsigned char * bit4, unsigned char * bit3, unsigned char * bit2, unsigned char * bit1);	//4byte(unsigned int)1個を1byte(unsigned char)の値4個に変換する


		/*あたり判定系*/
		extern int collision_rect(double rectX, double rectY, double rectWidth, double rectHeight, double pX, double pY);	//XY方向に平行な四角形と点のあたり判定
		extern int collisionLC(double X1, double Y1, double X2, double Y2, double circleX, double circleY, double circleR, double * ans1X, double * ans1Y, double * ans2X, double * ans2Y);	//円と直線の交点

		extern void Gradation_RGB(int R1, int G1, int B1, int R2, int G2, int B2, double X, int * ansR, int * ansG, int * ansB);	//RGBカラーでグラディエーションをする(Xは目的色までの割合(0【基本色】～100【目的色】)


	}
}
