#pragma region 計算を便利にする関数群
//計算を便利にする関数群
//author:Kisogawa(2016/10/15)
#pragma endregion 

#include "MainHeader.h"

//数値の範囲を別の範囲に変換する
double map(double v, double sx, double sn, double dx, double dn) {
	return (v - sn) * (dx - dn) / (sx - sn) + dn;
}

//2点間の角度の取得(度)
double getRotation(double X1, double Y1, double X2, double Y2) {
	double raziann = atan2(Y2 - Y1, X2 - X1);	//角度の計算(ラジアン)
	return fmod(rad_to_deg(raziann), 360);//度に変換して360度以内に納める
}

//XY方向に平行な四角形と点のあたり判定
int collision_rect(double rectX, double rectY, double Width, double Height, double pX, double pY) {
	//したの線より上にあるかどうか
	if (rectY + Height < pY) {
		return FALSE;
	}
	//左の線より右にあるか
	if (pX < rectX) {
		return FALSE;
	}
	if (rectX + Width < pX) {
		return FALSE;
	}
	if (pY < rectY) {
		return FALSE;
	}
	return TRUE;
}

//多角形と点のあたり判定
int collision_polygon2(PolygonPoints2 *polygon, double pointX, double pointY) {
	if (polygon == NULL) {
		return FALSE;
	}

	//意味分からん(頂点0個以下)
	if (polygon->getpointNum() <= 0)
		return FALSE;

	//意味分からん(配列オーバー)
	if (polygon->getpointNum() > PolygonPoints2_MAX)
		return FALSE;

	//点と点の判定
	if (polygon->getpointNum() == 1)
		return ((pointX == polygon->X[0] && pointY == polygon->Y[0]) ? TRUE : FALSE);

	//直線の判定は常にFALSEが返されるようになっています
	if (polygon->getpointNum() == 2)
		return FALSE;

	//三角形以上
	int Hit = FALSE;
	PolygonPoints2 po2 = *polygon;//元の構造体を破壊するため、構造体を複製する
	for (int i = 0; i < po2.getpointNum() - 2; i++) {//頂点の個数分ループする
													 //あたり判定を行う
		Hit |= collision_tri2(&po2, pointX, pointY);	//論理演算のORを使用する
		if (Hit)	break;//あたり判定が入った場合はループを抜ける

						  //リストをずらす(0は変えない)
		for (int j = 1; j < po2.getpointNum() - 1; j++) {
			po2.X[j] = po2.X[j + 1];
			po2.Y[j] = po2.Y[j + 1];
		}
	}

	return ((Hit) ? TRUE : FALSE);
}

//三角形と点のあたり判定
int collision_tri2(PolygonPoints2 *tri, double pointX, double pointY) {
	if (tri == NULL)		return FALSE;	//引数がおかしい
	if (tri->getpointNum() < 3)	return FALSE;	//三角形以下の形の場合

	Vec vec1, vec2, vec3;
	double PA, PB, PC; //外積
	vec1 = Vector_component(tri->X[0], tri->Y[0], pointX, pointY);
	vec2 = Vector_component(tri->X[1], tri->Y[1], pointX, pointY);
	vec3 = Vector_component(tri->X[2], tri->Y[2], pointX, pointY);
	PA = Cross_product(&vec1, &vec2);
	PB = Cross_product(&vec2, &vec3);
	PC = Cross_product(&vec3, &vec1);
	if ((PA >= 0 && PB >= 0 && PC >= 0) ||
		(PA <= 0 && PB <= 0 && PC <= 0)) {
		return TRUE;
	}
	return FALSE;
}

//多角形と線分のあたり判定
int collision_polygon_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2) {
	if (polygon == NULL) {
		return FALSE;
	}

	if (polygon->getpointNum() == 0)
		return FALSE;
	//点は未作成
	if (polygon->getpointNum() == 1)
		return FALSE;

	if (polygon->getpointNum() == 2)
		return collision_line2(polygon, pointX1, pointY1, pointX2, pointY2);

	//三角形以上
	//直線の端で内外判定を行う
	if (collision_polygon2(polygon, pointX1, pointY1)) return TRUE;
	if (collision_polygon2(polygon, pointX2, pointY2)) return TRUE;

	//頂点のあたり判定が入っていない場合は直線の交点であたり判定を行う
	PolygonPoints2 po2 = *polygon;//元の構造体を破壊するため、構造体を複製する
	for (int i = 0; i < po2.getpointNum(); i++) {//頂点の個数分ループする

		po2.X[0] = po2.X[i];
		po2.Y[0] = po2.Y[i];
		po2.X[1] = po2.X[(i + 1) % po2.getpointNum()];
		po2.Y[1] = po2.Y[(i + 1) % po2.getpointNum()];

		//あたり判定を行う
		if (collision_line2(&po2, pointX1, pointY1, pointX2, pointY2))	return TRUE;
	}
	return FALSE;
}

//線分と線分のあたり判定
int collision_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2) {
	if (polygon == NULL)			return FALSE;
	if (polygon->getpointNum() < 2)	return FALSE;
	//あたり判定処理
	double ta = (pointX1 - pointX2) * (polygon->Y[0] - pointY1) + (pointY1 - pointY2) * (pointX1 - polygon->X[0]),
		tb = (pointX1 - pointX2) * (polygon->Y[1] - pointY1) + (pointY1 - pointY2) * (pointX1 - polygon->X[1]),
		tc = (polygon->X[0] - polygon->X[1]) * (pointY1 - polygon->Y[0]) + (polygon->Y[0] - polygon->Y[1]) * (polygon->X[0] - pointX1),
		td = (polygon->X[0] - polygon->X[1]) * (pointY2 - polygon->Y[0]) + (polygon->Y[0] - polygon->Y[1]) * (polygon->X[0] - pointX2);

	if (ta * tb < 0 && tc * td < 0) {
		return TRUE;
	}

	return FALSE;
}

//外積の計算
double Cross_product(Vec *a, Vec *b) {
	return (a->x * b->y - a->y * b->x);
}

//ベクトルの成分計算
Vec Vector_component(double x, double y, double pointX, double pointY) {
	Vec vec;
	vec.x = x - pointX;
	vec.y = y - pointY;
	return vec;
}

//多角形を描画する2(テクスチャ無し)
void DrawPolygon2D_Notexture2(PolygonPoints2 *polygonPoints, unsigned int color, int fillFlag) {
	//多角形を三角形に分割しつつ描画する
	if (polygonPoints == NULL)	return;
	if (polygonPoints->getpointNum() <= 0 || PolygonPoints2_MAX < polygonPoints->getpointNum())	return;//範囲外

																									   //点の描画
	if (polygonPoints->getpointNum() == 1) {
		DrawPixel((int)polygonPoints->X[0], (int)polygonPoints->Y[0], color);
		return;
	}

	//線の描画
	if (polygonPoints->getpointNum() <= 2) {
		DrawLine((int)polygonPoints->X[0], (int)polygonPoints->Y[0], (int)polygonPoints->X[1], (int)polygonPoints->Y[1], color);
		return;
	}

	//三角形以上
	for (int i = 0; i < polygonPoints->getpointNum() - 2; i++) {//頂点の個数分ループする
		DrawTriangle((int)polygonPoints->X[0], (int)polygonPoints->Y[0]
			, (int)polygonPoints->X[i + 1], (int)polygonPoints->Y[i + 1]
			, (int)polygonPoints->X[i + 2], (int)polygonPoints->Y[i + 2], color, fillFlag);
	}
}

//線の描画(極座標)
void DrawLineAA_Polar(double X, double Y, double rota, double length, unsigned int Color, float Thicknes) {
	DrawLineAA((float)X, (float)Y, (float)(X + length*cos(deg_to_rad(rota))), (float)(Y + length*sin(deg_to_rad(rota))), Color, Thicknes);
}

//指定した範囲で指定した値を循環させるように変換する(Min以上Max未満)
int circulating(int Src, int Min, int Max) {
	int Len = Max - Min;
	if (Len <= 0)	return Src;//辺な場合は計算しない
	Src %= Len;//割った時のあまりを求める
			   //負の数の場合は正の数になるまで加算する
	while (Src < 0) {
		Src += Len;
	}
	return (Min + Src);
}

//指定した範囲で指定した値を循環させるように変換する(Min以上Max未満)(double型)
double circulating_d(double Src, double Min, double Max) {
	double Len = Max - Min;
	if (Len <= 0)	return Src;//辺な場合は計算しない
	Src -= Min;
	Src = fmod(Src, Len);//割った時のあまりを求める
						 //負の数の場合は正の数になるまで加算する
	while (Src < 0) {
		Src += Len;
	}
	return (Min + Src);
}

//指定したグラフィックハンドルにClearDrawScreenを行う
void ClearDrawScreenTogrHandle(int grHandle) {
	//現在の描画ハンドルの取得
	const int CurrantDraw = GetDrawScreen();
	//描画先を変更する
	SetDrawScreen(grHandle);
	//描画内容の削除
	ClearDrawScreen();
	//描画先を戻す
	SetDrawScreen(CurrantDraw);
}

// 画面いっぱいに画像を描画する(zx, zy : ずらすドット数)(ループ)
void DrawTileGraph(int zx, int zy, int GrHandle) {
	int w, h, NumX, NumY, dx, dy;

	// 画像のサイズを得る
	GetGraphSize(GrHandle, &w, &h);

	// ずらすドット数を画像のサイズで割って、その余りを zx, zy に代入する
	zx %= w;
	zy %= h;

	//負の数の場合は正の数にする
	while (zx < 0)	zx += w;
	while (zy < 0)	zy += h;



	// 縦横に描画する数を算出する
	NumX = WINDOW_WIDTH / w + 2;
	NumY = WINDOW_HEIGHT / h + 2;

	// 数だけ描画
	dy = zy - h;
	for (int i = 0; i < NumY; i++, dy += h) {
		dx = zx - w;
		for (int j = 0; j < NumX; j++, dx += w) {
			DrawGraph(dx, dy, GrHandle, FALSE);
		}
	}
}

//指定の小数桁数で切り捨てる(デカい数字でうまくいくかは知りません)
double CutDecimal(double src, int No) {
	if (No <= 0)		return src;	//意味分からん
	if (No >= DBL_DIG)	return src;	//有効桁数を超えている
									//有効桁数[DBL_DIG]的に切り捨てる必要が無い場合は切り捨てない
	long long Ns = powi64(10LL, DBL_DIG - No);
	if (src > Ns)	return src;		//現在の有効桁数を超えているので処理をしない

	long long N = powi64(10LL, No);
	return (long long)(src * N) / (double)N;
}

//RGBカラーでグラディエーションをする(Xは目的色までの割合（0【基本色】～100【目的色】）)
void Gradation_RGB(int R1, int G1, int B1, int R2, int G2, int B2, double X, int *ansR, int *ansG, int *ansB) {
	if (ansR != NULL) {
		*ansR = (int)((R2 - R1) * X / 100 + R1);
		if (*ansR < 0)		*ansR = 0;
		if (*ansR > 255)	*ansR = 255;
	}
	if (ansG != NULL) {
		*ansG = (int)((G2 - G1) * X / 100 + G1);
		if (*ansG < 0)		*ansG = 0;
		if (*ansG > 255)	*ansG = 255;
	}
	if (ansB != NULL) {
		*ansB = (int)((B2 - B1) * X / 100 + B1);
		if (*ansB < 0)		*ansB = 0;
		if (*ansB > 255)	*ansB = 255;
	}
}

//long long型のpow関数(_Yx < 0は非対応)
long long powi64(long long _Left, int _Yx) {
	if (_Yx < 0)	return 0;
	long long N = 1;
	for (int i = 0; i < _Yx; i++) {
		N *= _Left;
	}
	return N;
}

//ある値を最大値を超える場合は最大値に、最小値を下回る場合は最小値にする(double型)
double InRange(double val, double min, double max) {
	if (min > val)	return min;
	if (max < val)	return max;
	return val;
}

//ある値(InVal)をある値中心(Center)に拡大・縮小(Ex)したときの値を取得する
double ExpandValue(double InVal, double Center, double Ex) {
	//中心との変位を求める
	double Delta = InVal - Center;
	//倍率分拡大する
	Delta *= Ex;
	return Center + Delta;
}

//PolygonPointsに四角形を設定する
void PolygonPoints2_setRect(double x, double y, double w, double h, PolygonPoints2 *rect) {
	if (rect == NULL)	return;

	//左上
	rect->X[0] = x;
	rect->Y[0] = y;

	//右上
	rect->X[1] = x + w;
	rect->Y[1] = y;

	//右下
	rect->X[2] = x + w;
	rect->Y[2] = y + h;

	//左下
	rect->X[3] = x;
	rect->Y[3] = y + h;

	//四角形の設定
	rect->SetpointNum(4);

}

//円グラフのような円を描画する(旧、敵のHPバー)(描画したい中心位置X,Y,多分半径,描画する角度)
void draw_Circle(double X, double Y, double R, int Kakudo) {
	double x, y;		//計算結果保存用
	double x2, y2;		//計算結果保存用
	int n = 180;//分割数
	int n2 = (int)(((Kakudo % 360) / 360.)*n);//書く数
	if (n2 == 0 && Kakudo / 360 >= 1)	n2 = n;//360度ジャストの時は円を描くため
	int i = 0;

	unsigned int Cr = GetColor(0xff, 0xa3, 0x55);
	x = X + R*cos(-2.0*PI*i / n + PI * 1.5);
	y = Y + R*sin(-2.0*PI*i / n + PI * 1.5);
	for (i = 1; i < n2; i++) {
		x2 = X + R*cos(-2.0*PI*i / n + PI * 1.5);
		y2 = Y + R*sin(-2.0*PI*i / n + PI * 1.5);
		if (n == i + 1)	x2--;
		DrawLine((int)x, (int)y, (int)x2, (int)y2, Cr, 6);
		x = X + R*cos(-2.0*PI*i / n + PI * 1.5);
		y = Y + R*sin(-2.0*PI*i / n + PI * 1.5);
	}
	i = 0;
	double R2 = R + 3;
	unsigned int CrB = GetColor(0x6c, 0x44, 0x79);
	x = X + R2*cos(-2.0*PI*i / n + PI * 1.5);
	y = Y + R2*sin(-2.0*PI*i / n + PI * 1.5);
	for (i = 1; i < n; i++) {
		x2 = X + R2*cos(-2.0*PI*i / n + PI * 1.5);
		y2 = Y + R2*sin(-2.0*PI*i / n + PI * 1.5);
		if (n == i + 1)	x2--;
		DrawLine((int)x, (int)y, (int)x2, (int)y2, CrB, 2);
		x = X + R2*cos(-2.0*PI*i / n + PI * 1.5);
		y = Y + R2*sin(-2.0*PI*i / n + PI * 1.5);
	}
	i = 0;
	R2 = R - 3;
	x = X + R2*cos(-2.0*PI*i / n + PI * 1.5);
	y = Y + R2*sin(-2.0*PI*i / n + PI * 1.5);
	for (i = 1; i < n; i++) {
		x2 = X + R2*cos(-2.0*PI*i / n + PI * 1.5);
		y2 = Y + R2*sin(-2.0*PI*i / n + PI * 1.5);
		if (n == i + 1)	x2--;
		DrawLine((int)x, (int)y, (int)x2, (int)y2, CrB, 2);
		x = X + R2*cos(-2.0*PI*i / n + PI * 1.5);
		y = Y + R2*sin(-2.0*PI*i / n + PI * 1.5);
	}
}

//円グラフのような円を描画する(描画したい中心位置X,Y,描画する360度に対する割合,グラフ部分のテクスチャ,円周部分のテクスチャ)
void draw_Circle2(int X, int Y, double per, int Texture, int Texture2) {
	DrawCircleGauge(X, Y, 100, Texture, 100 - per);
	if (Texture2 != -1)	DrawCircleGauge(X, Y, 100, Texture2, 0);
}

//線の描画(極座標)
inline void DrawArrow(double X, double Y, double vector, double length, unsigned int Color, float Thicknes) {
	DrawLineAA((float)X, (float)Y, (float)(X + length*cos(deg_to_rad(vector))), (float)(Y + length*sin(deg_to_rad(vector))), Color, Thicknes);

}

//画像の3D回転描画(度指定)
void DrawRotaImage3D(double X, double Y, double ExLate, double AngleX, double AngleY, double AngleZ, int grHandle) {
	//http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=2749

	VERTEX3D Vertex[6];
	VECTOR Angle, RotaAngle;//回転ベクトルとX軸拝見の代わりにする回転軸ベクトル
	MATRIX TransformMatrix;
	int DrawWindowX, DrawWindowY;
	GetDrawScreenSize(&DrawWindowX, &DrawWindowY);

	//左下原点になるように補正をかける
	Y = DrawWindowY - Y;

	//現実的な角度に変換
	AngleX = fmod(AngleX, 360.);
	AngleY = fmod(AngleY, 360.);
	AngleZ = fmod(AngleZ, 360.);

	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	// 回転パラメータの設定
	Angle.x = (float)deg_to_rad(AngleX);
	Angle.y = (float)deg_to_rad(AngleY);
	Angle.z = (float)deg_to_rad(AngleZ);


	RotaAngle = VGet((float)cos(deg_to_rad(AngleY)), (float)sin(deg_to_rad(AngleY)), 0);


	// z軸回転行列の作成＋xy軸拡大縮小行列の作成＋xyz拡大縮小行列の作成＋座標移動行列の作成
	TransformMatrix = MGetRotZ(Angle.z);
	//TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
	TransformMatrix = MMult(TransformMatrix, MGetRotAxis(RotaAngle, Angle.x));
	//TransformMatrix = MMult(TransformMatrix, MGetRotX(Angle.x));
	//TransformMatrix = MGetIdent();
	//TransformMatrix = MMult(TransformMatrix, MGetScale(VGet(cos(Angle.x), cos(Angle.y), 1)));
	TransformMatrix = MMult(TransformMatrix, MGetScale(VGet((float)ExLate, (float)ExLate, (float)ExLate)));
	TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet((float)X, (float)Y, 0.0f)));

	// 行列を使ってワールド座標を算出
	Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), TransformMatrix);

	Vertex[4].pos = Vertex[2].pos;
	Vertex[5].pos = Vertex[1].pos;

	// 行列を使って法線を算出
	Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
	Vertex[1].norm = Vertex[0].norm;
	Vertex[2].norm = Vertex[0].norm;
	Vertex[3].norm = Vertex[0].norm;
	Vertex[4].norm = Vertex[0].norm;
	Vertex[5].norm = Vertex[0].norm;

	// ライティングは行わない
	SetUseLighting(FALSE);

	// ２ポリゴンの描画
	DrawPolygon3D(Vertex, 2, grHandle, TRUE);

}

//2点間の距離を求める
double getDistance(double X1, double Y1, double X2, double Y2) {
	double dis2 = (X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1);//距離の2乗を求める
	return sqrt(dis2);
}

//円と直線の交点
int collisionLC(double X1, double Y1, double X2, double Y2
	, double  circleX, double circleY, double circleR
	, Vec *ans1, Vec *ans2) {

	if (X1 == X2 || Y1 == Y2) {
		if (ans1 != NULL) {
			ans1->x = 0;
			ans1->y = 0;
		}
		if (ans2 != NULL) {
			ans2->x = 0;
			ans2->y = 0;
		}
		return 0;
	}
	double a = Y2 - Y1;
	double b = -(X2 - X1);
	double c = (X2*Y1 - X1*Y2);
	if (a == 0 && b == 0) {
		if (ans1 != NULL) {
			ans1->x = 0;
			ans1->y = 0;
		}
		if (ans2 != NULL) {
			ans2->x = 0;
			ans2->y = 0;
		}
		return 0;
	}
	//計算を行う
	double d = a * circleX + b * circleY + c;
	//円の中心からの距離の2乗
	double HQ2 = circleR*circleR - (d*d) / (a*a + b*b);

	if (ans1 != NULL) {
		ans1->x = ((-a*d + b*sqrt(((a*a + b*b)*(circleR*circleR) - d*d))) / (a*a + b*b) + circleX);
		ans1->y = ((-b*d - a*sqrt(((a*a + b*b)*(circleR*circleR) - d*d))) / (a*a + b*b) + circleY);
	}
	if (ans2 != NULL) {
		ans2->x = ((-a*d - b*sqrt(((a*a + b*b)*(circleR*circleR) - d*d))) / (a*a + b*b) + circleX);
		ans2->y = ((-b*d + a*sqrt(((a*a + b*b)*(circleR*circleR) - d*d))) / (a*a + b*b) + circleY);
	}
	return 1;

}

//三角波を返す
double getGraph_Triangle(int Cycle) {
	if (Cycle <= 1)	return 0;
	double tm = 0;
	double t = Cycle / 2;
	if (getFrameCount(THREAD_Update) % Cycle < t) {
		tm = (getFrameCount(THREAD_Update) % Cycle) / t;
	}
	else {
		tm = 2 - (getFrameCount(THREAD_Update) % Cycle) / t;
	}
	return tm;
}

//サイン波を返す(フレーム数を入れるといい感じになる)
double getGraph_Sin(double frameVal, double Delta, double Shift) {
	frameVal = fmod(frameVal, 360);
	return sin(deg_to_rad(frameVal)) * Delta;
}

//-180～180の値に変換
double getDegrees(double nDegrees) {
	nDegrees += 180;
	nDegrees = fmod(nDegrees, 360);
	if (nDegrees < 0) {
		nDegrees += 180;
	}
	else {
		nDegrees -= 180;
	}
	return nDegrees;
}

//普通の速度を角速度に変換(ピクセル/フレーム→度/フレーム)(引数は普通の速度、半径)
double ConvertPixpF_To_DegpF(double Speed, double R) {
	//角速度を求める(ラジアン)
	double redSpeed = Speed / R;
	return rad_to_deg(redSpeed);//度に変換
}

//角速度を普通の速度に変換(度/フレーム→ピクセル/フレーム)(引数は角速度、半径)
double ConvertDegpF_To_PixpF(double DegSpeed, double R) {
	//角速度を求める(ラジアン)
	DegSpeed = fabs(DegSpeed);
	double redSpeed = deg_to_rad(DegSpeed);//ラジアンに変換
	return redSpeed*R;
}

//RGBからHSVに変換
void RGB_to_HSV(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *V) {
	double max;
	double min;
	double R, G, B;

	// 0.0 - 1.0（255分率）
	R = (double)r / 255;
	G = (double)g / 255;
	B = (double)b / 255;

	// 最大値・最小値
	if (R >= G && R >= B) {
		max = R;
		min = (G < B) ? G : B;
	}
	else if (G >= R && G >= B) {
		max = G;
		min = (R < B) ? R : B;
	}
	else {
		max = B;
		min = (R < G) ? R : G;
	}

	// Hue（色相）
	if (max == R) {
		*H = 60 * (G - B) / (max - min);
	}
	else if (max == G) {
		*H = 60 * (B - R) / (max - min) + 120;
	}
	else {
		*H = 60 * (R - G) / (max - min) + 240;
	}
	if (max - min == 0) {//0除算が発生している場合
		*H = 0;
	}
	if (*H < 0.0) {
		*H += 360.0;
	}



	// Saturation（彩度）
	*S = (max - min) / max;
	// Value（明度）
	*V = max;

	//値を100段階に変換
	*S *= 100;
	*V *= 100;

}

//RGBからHSLに変換
void RGB_to_HSL(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *L) {
	unsigned char MaxVal = max(max(r, g), b);	//最大値を求める
	unsigned char MinVal = min(min(r, g), b);	//最小値を求める
	*H = 0;
	*S = 0;
	*L = (MaxVal + MinVal) / 2.;//L(輝度)

	if (MaxVal != MinVal) {
		// H(色相)  
		if (MaxVal == r) *H = 60. * (g - b) / (MaxVal - MinVal);
		if (MaxVal == g) *H = 60. * (b - r) / (MaxVal - MinVal) + 120;
		if (MaxVal == b) *H = 60. * (r - g) / (MaxVal - MinVal) + 240;

		// S(彩度)
		if (*L <= 127)	*S = (MaxVal - MinVal) / (double)(MaxVal + MinVal);
		else			*S = (MaxVal - MinVal) / (double)(510 - MaxVal - MinVal);
	}
	//SとLを100段階に変換
	*S *= 100;
	*L *= (100 / 255.);


}

//HSVからRGBに変換
void HSV_to_RGB(double H, double S, double V, unsigned char *R, unsigned char *G, unsigned char *B) {
	int Hi;
	double f, p, q, t;
	if (V < 0)		V = 0;
	if (V > 100)	V = 100;

	//0～1にもどす
	S /= 100;
	V /= 100;

	Hi = ((int)(H / 60)) % 6;
	f = H / 60 - Hi;
	p = V * (1 - S);
	q = V * (1 - f * S);
	t = V * (1 - (1 - f) * S);

	// 256階調に戻す
	V *= 255;
	p *= 255;
	q *= 255;
	t *= 255;

	switch (Hi) {
	case 0: *R = (unsigned char)V; *G = (unsigned char)t; *B = (unsigned char)p; break;
	case 1: *R = (unsigned char)q; *G = (unsigned char)V; *B = (unsigned char)p; break;
	case 2: *R = (unsigned char)p; *G = (unsigned char)V; *B = (unsigned char)t; break;
	case 3: *R = (unsigned char)p; *G = (unsigned char)q; *B = (unsigned char)V; break;
	case 4: *R = (unsigned char)t; *G = (unsigned char)p; *B = (unsigned char)V; break;
	case 5: *R = (unsigned char)V; *G = (unsigned char)p; *B = (unsigned char)q; break;
	}
}

//HSLからRGBに変換
void HSL_to_RGB(double H, double S, double L, unsigned char *R, unsigned char *G, unsigned char *B) {
	double max, min;
	*R = 0;
	*G = 0;
	*B = 0;

	double r = 0, g = 0, b = 0;

	H = fmod(H, 360);


	if (L <= 49) {
		max = 2.55 * (L + L * (S / 100));
		min = 2.55 * (L - L * (S / 100));
	}
	else {
		max = 2.55 * (L + (100 - L) * (S / 100));
		min = 2.55 * (L - (100 - L) * (S / 100));
	}

	if (H < 60) {
		r = max;
		g = (min + (max - min) * (H / 60));
		b = min;
	}
	else if (H >= 60 && H < 120) {
		r = (min + (max - min) * ((120 - H) / 60));
		g = max;
		b = min;
	}
	else if (H >= 120 && H < 180) {
		r = min;
		g = max;
		b = min + (max - min) * ((H - 120) / 60);
	}
	else if (H >= 180 && H < 240) {
		r = min;
		g = min + (max - min) * ((240 - H) / 60);
		b = max;
	}
	else if (H >= 240 && H < 300) {
		r = min + (max - min) * ((H - 240) / 60);
		g = min;
		b = max;
	}
	else if (H >= 300 && H < 360) {
		r = max;
		g = min;
		b = min + (max - min) * ((360 - H) / 60);
	}

	*R = (unsigned int)round(r);
	*G = (unsigned int)round(g);
	*B = (unsigned int)round(b);
}

//1byte(unsigned char)の値4個を4byte(unsigned int)1個に変換する
unsigned int ConvertCollect1to4(unsigned char bit4, unsigned char bit3, unsigned char bit2, unsigned char bit1) {
	return (bit4 << 3 * 8) + (bit3 << 2 * 8) + (bit2 << 1 * 8) + bit1;
}

//4byte(unsigned int)1個を1byte(unsigned char)の値4個に変換する
void ConvertCollect4to1(const unsigned int src, unsigned char *bit4, unsigned char *bit3, unsigned char *bit2, unsigned char *bit1) {
	if (bit4 != NULL)	*bit4 = (src & 0xff00'0000) >> 3 * 8;
	if (bit3 != NULL)	*bit3 = (src & 0x00ff'0000) >> 2 * 8;
	if (bit2 != NULL)	*bit2 = (src & 0x0000'ff00) >> 1 * 8;
	if (bit1 != NULL)	*bit1 = src & 0x0000'00ff;
}

//指定した値より大きい2のn乗を返す
int Pot(int inSize) {
	int outSize = 1;
	while (outSize < inSize) outSize <<= 1;
	return outSize;
}

//加速度、最大速度、移動開始からの経過時間から現在の移動距離を計算する
double getMoveDistance(double a, double MaxSpeed, int Count) {
	//vtグラフの面積を計算すれば良い

	//現在のカウント数で最大速度に到達しているかの確認
	double MaxSpeedCount = MaxSpeed / a;
	if (MaxSpeedCount >= Count) {//加速中
								 /*x=(1/2)*at^2*/
		double D = (1 / 2.)*a*Count*Count;
		return D;
	}
	else {

		//最大速度に到達した場所でのカウントを取得する
		double aD = (1 / 2.)*a*MaxSpeedCount*MaxSpeedCount;	//加速中に移動した距離を計算する
		double nD = MaxSpeed * (Count - MaxSpeedCount);		//最大速度で等速直線運動
		return aD + nD;
	}
}