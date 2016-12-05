#pragma region �v�Z��֗��ɂ���֐��Q
//�v�Z��֗��ɂ���֐��Q
//author:Kisogawa(2016/10/15)
#pragma endregion 

#include "MainHeader.h"

//���l�͈̔͂�ʂ͈̔͂ɕϊ�����
double map(double v, double sx, double sn, double dx, double dn) {
	return (v - sn) * (dx - dn) / (sx - sn) + dn;
}

//2�_�Ԃ̊p�x�̎擾(�x)
double getRotation(double X1, double Y1, double X2, double Y2) {
	double raziann = atan2(Y2 - Y1, X2 - X1);	//�p�x�̌v�Z(���W�A��)
	return fmod(rad_to_deg(raziann), 360);//�x�ɕϊ�����360�x�ȓ��ɔ[�߂�
}

//XY�����ɕ��s�Ȏl�p�`�Ɠ_�̂����蔻��
int collision_rect(double rectX, double rectY, double Width, double Height, double pX, double pY) {
	//�����̐�����ɂ��邩�ǂ���
	if (rectY + Height < pY) {
		return FALSE;
	}
	//���̐����E�ɂ��邩
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

//���p�`�Ɠ_�̂����蔻��
int collision_polygon2(PolygonPoints2 *polygon, double pointX, double pointY) {
	if (polygon == NULL) {
		return FALSE;
	}

	//�Ӗ��������(���_0�ȉ�)
	if (polygon->getpointNum() <= 0)
		return FALSE;

	//�Ӗ��������(�z��I�[�o�[)
	if (polygon->getpointNum() > PolygonPoints2_MAX)
		return FALSE;

	//�_�Ɠ_�̔���
	if (polygon->getpointNum() == 1)
		return ((pointX == polygon->X[0] && pointY == polygon->Y[0]) ? TRUE : FALSE);

	//�����̔���͏��FALSE���Ԃ����悤�ɂȂ��Ă��܂�
	if (polygon->getpointNum() == 2)
		return FALSE;

	//�O�p�`�ȏ�
	int Hit = FALSE;
	PolygonPoints2 po2 = *polygon;//���̍\���̂�j�󂷂邽�߁A�\���̂𕡐�����
	for (int i = 0; i < po2.getpointNum() - 2; i++) {//���_�̌������[�v����
													 //�����蔻����s��
		Hit |= collision_tri2(&po2, pointX, pointY);	//�_�����Z��OR���g�p����
		if (Hit)	break;//�����蔻�肪�������ꍇ�̓��[�v�𔲂���

						  //���X�g�����炷(0�͕ς��Ȃ�)
		for (int j = 1; j < po2.getpointNum() - 1; j++) {
			po2.X[j] = po2.X[j + 1];
			po2.Y[j] = po2.Y[j + 1];
		}
	}

	return ((Hit) ? TRUE : FALSE);
}

//�O�p�`�Ɠ_�̂����蔻��
int collision_tri2(PolygonPoints2 *tri, double pointX, double pointY) {
	if (tri == NULL)		return FALSE;	//��������������
	if (tri->getpointNum() < 3)	return FALSE;	//�O�p�`�ȉ��̌`�̏ꍇ

	Vec vec1, vec2, vec3;
	double PA, PB, PC; //�O��
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

//���p�`�Ɛ����̂����蔻��
int collision_polygon_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2) {
	if (polygon == NULL) {
		return FALSE;
	}

	if (polygon->getpointNum() == 0)
		return FALSE;
	//�_�͖��쐬
	if (polygon->getpointNum() == 1)
		return FALSE;

	if (polygon->getpointNum() == 2)
		return collision_line2(polygon, pointX1, pointY1, pointX2, pointY2);

	//�O�p�`�ȏ�
	//�����̒[�œ��O������s��
	if (collision_polygon2(polygon, pointX1, pointY1)) return TRUE;
	if (collision_polygon2(polygon, pointX2, pointY2)) return TRUE;

	//���_�̂����蔻�肪�����Ă��Ȃ��ꍇ�͒����̌�_�ł����蔻����s��
	PolygonPoints2 po2 = *polygon;//���̍\���̂�j�󂷂邽�߁A�\���̂𕡐�����
	for (int i = 0; i < po2.getpointNum(); i++) {//���_�̌������[�v����

		po2.X[0] = po2.X[i];
		po2.Y[0] = po2.Y[i];
		po2.X[1] = po2.X[(i + 1) % po2.getpointNum()];
		po2.Y[1] = po2.Y[(i + 1) % po2.getpointNum()];

		//�����蔻����s��
		if (collision_line2(&po2, pointX1, pointY1, pointX2, pointY2))	return TRUE;
	}
	return FALSE;
}

//�����Ɛ����̂����蔻��
int collision_line2(PolygonPoints2 *polygon, double pointX1, double pointY1, double pointX2, double pointY2) {
	if (polygon == NULL)			return FALSE;
	if (polygon->getpointNum() < 2)	return FALSE;
	//�����蔻�菈��
	double ta = (pointX1 - pointX2) * (polygon->Y[0] - pointY1) + (pointY1 - pointY2) * (pointX1 - polygon->X[0]),
		tb = (pointX1 - pointX2) * (polygon->Y[1] - pointY1) + (pointY1 - pointY2) * (pointX1 - polygon->X[1]),
		tc = (polygon->X[0] - polygon->X[1]) * (pointY1 - polygon->Y[0]) + (polygon->Y[0] - polygon->Y[1]) * (polygon->X[0] - pointX1),
		td = (polygon->X[0] - polygon->X[1]) * (pointY2 - polygon->Y[0]) + (polygon->Y[0] - polygon->Y[1]) * (polygon->X[0] - pointX2);

	if (ta * tb < 0 && tc * td < 0) {
		return TRUE;
	}

	return FALSE;
}

//�O�ς̌v�Z
double Cross_product(Vec *a, Vec *b) {
	return (a->x * b->y - a->y * b->x);
}

//�x�N�g���̐����v�Z
Vec Vector_component(double x, double y, double pointX, double pointY) {
	Vec vec;
	vec.x = x - pointX;
	vec.y = y - pointY;
	return vec;
}

//���p�`��`�悷��2(�e�N�X�`������)
void DrawPolygon2D_Notexture2(PolygonPoints2 *polygonPoints, unsigned int color, int fillFlag) {
	//���p�`���O�p�`�ɕ������`�悷��
	if (polygonPoints == NULL)	return;
	if (polygonPoints->getpointNum() <= 0 || PolygonPoints2_MAX < polygonPoints->getpointNum())	return;//�͈͊O

																									   //�_�̕`��
	if (polygonPoints->getpointNum() == 1) {
		DrawPixel((int)polygonPoints->X[0], (int)polygonPoints->Y[0], color);
		return;
	}

	//���̕`��
	if (polygonPoints->getpointNum() <= 2) {
		DrawLine((int)polygonPoints->X[0], (int)polygonPoints->Y[0], (int)polygonPoints->X[1], (int)polygonPoints->Y[1], color);
		return;
	}

	//�O�p�`�ȏ�
	for (int i = 0; i < polygonPoints->getpointNum() - 2; i++) {//���_�̌������[�v����
		DrawTriangle((int)polygonPoints->X[0], (int)polygonPoints->Y[0]
			, (int)polygonPoints->X[i + 1], (int)polygonPoints->Y[i + 1]
			, (int)polygonPoints->X[i + 2], (int)polygonPoints->Y[i + 2], color, fillFlag);
	}
}

//���̕`��(�ɍ��W)
void DrawLineAA_Polar(double X, double Y, double rota, double length, unsigned int Color, float Thicknes) {
	DrawLineAA((float)X, (float)Y, (float)(X + length*cos(deg_to_rad(rota))), (float)(Y + length*sin(deg_to_rad(rota))), Color, Thicknes);
}

//�w�肵���͈͂Ŏw�肵���l���z������悤�ɕϊ�����(Min�ȏ�Max����)
int circulating(int Src, int Min, int Max) {
	int Len = Max - Min;
	if (Len <= 0)	return Src;//�ӂȏꍇ�͌v�Z���Ȃ�
	Src %= Len;//���������̂��܂�����߂�
			   //���̐��̏ꍇ�͐��̐��ɂȂ�܂ŉ��Z����
	while (Src < 0) {
		Src += Len;
	}
	return (Min + Src);
}

//�w�肵���͈͂Ŏw�肵���l���z������悤�ɕϊ�����(Min�ȏ�Max����)(double�^)
double circulating_d(double Src, double Min, double Max) {
	double Len = Max - Min;
	if (Len <= 0)	return Src;//�ӂȏꍇ�͌v�Z���Ȃ�
	Src -= Min;
	Src = fmod(Src, Len);//���������̂��܂�����߂�
						 //���̐��̏ꍇ�͐��̐��ɂȂ�܂ŉ��Z����
	while (Src < 0) {
		Src += Len;
	}
	return (Min + Src);
}

//�w�肵���O���t�B�b�N�n���h����ClearDrawScreen���s��
void ClearDrawScreenTogrHandle(int grHandle) {
	//���݂̕`��n���h���̎擾
	const int CurrantDraw = GetDrawScreen();
	//�`����ύX����
	SetDrawScreen(grHandle);
	//�`����e�̍폜
	ClearDrawScreen();
	//�`����߂�
	SetDrawScreen(CurrantDraw);
}

// ��ʂ����ς��ɉ摜��`�悷��(zx, zy : ���炷�h�b�g��)(���[�v)
void DrawTileGraph(int zx, int zy, int GrHandle) {
	int w, h, NumX, NumY, dx, dy;

	// �摜�̃T�C�Y�𓾂�
	GetGraphSize(GrHandle, &w, &h);

	// ���炷�h�b�g�����摜�̃T�C�Y�Ŋ����āA���̗]��� zx, zy �ɑ������
	zx %= w;
	zy %= h;

	//���̐��̏ꍇ�͐��̐��ɂ���
	while (zx < 0)	zx += w;
	while (zy < 0)	zy += h;



	// �c���ɕ`�悷�鐔���Z�o����
	NumX = WINDOW_WIDTH / w + 2;
	NumY = WINDOW_HEIGHT / h + 2;

	// �������`��
	dy = zy - h;
	for (int i = 0; i < NumY; i++, dy += h) {
		dx = zx - w;
		for (int j = 0; j < NumX; j++, dx += w) {
			DrawGraph(dx, dy, GrHandle, FALSE);
		}
	}
}

//�w��̏��������Ő؂�̂Ă�(�f�J�������ł��܂��������͒m��܂���)
double CutDecimal(double src, int No) {
	if (No <= 0)		return src;	//�Ӗ��������
	if (No >= DBL_DIG)	return src;	//�L�������𒴂��Ă���
									//�L������[DBL_DIG]�I�ɐ؂�̂Ă�K�v�������ꍇ�͐؂�̂ĂȂ�
	long long Ns = powi64(10LL, DBL_DIG - No);
	if (src > Ns)	return src;		//���݂̗L�������𒴂��Ă���̂ŏ��������Ȃ�

	long long N = powi64(10LL, No);
	return (long long)(src * N) / (double)N;
}

//RGB�J���[�ŃO���f�B�G�[�V����������(X�͖ړI�F�܂ł̊����i0�y��{�F�z�`100�y�ړI�F�z�j)
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

//long long�^��pow�֐�(_Yx < 0�͔�Ή�)
long long powi64(long long _Left, int _Yx) {
	if (_Yx < 0)	return 0;
	long long N = 1;
	for (int i = 0; i < _Yx; i++) {
		N *= _Left;
	}
	return N;
}

//����l���ő�l�𒴂���ꍇ�͍ő�l�ɁA�ŏ��l�������ꍇ�͍ŏ��l�ɂ���(double�^)
double InRange(double val, double min, double max) {
	if (min > val)	return min;
	if (max < val)	return max;
	return val;
}

//����l(InVal)������l���S(Center)�Ɋg��E�k��(Ex)�����Ƃ��̒l���擾����
double ExpandValue(double InVal, double Center, double Ex) {
	//���S�Ƃ̕ψʂ����߂�
	double Delta = InVal - Center;
	//�{�����g�傷��
	Delta *= Ex;
	return Center + Delta;
}

//PolygonPoints�Ɏl�p�`��ݒ肷��
void PolygonPoints2_setRect(double x, double y, double w, double h, PolygonPoints2 *rect) {
	if (rect == NULL)	return;

	//����
	rect->X[0] = x;
	rect->Y[0] = y;

	//�E��
	rect->X[1] = x + w;
	rect->Y[1] = y;

	//�E��
	rect->X[2] = x + w;
	rect->Y[2] = y + h;

	//����
	rect->X[3] = x;
	rect->Y[3] = y + h;

	//�l�p�`�̐ݒ�
	rect->SetpointNum(4);

}

//�~�O���t�̂悤�ȉ~��`�悷��(���A�G��HP�o�[)(�`�悵�������S�ʒuX,Y,�������a,�`�悷��p�x)
void draw_Circle(double X, double Y, double R, int Kakudo) {
	double x, y;		//�v�Z���ʕۑ��p
	double x2, y2;		//�v�Z���ʕۑ��p
	int n = 180;//������
	int n2 = (int)(((Kakudo % 360) / 360.)*n);//������
	if (n2 == 0 && Kakudo / 360 >= 1)	n2 = n;//360�x�W���X�g�̎��͉~��`������
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

//�~�O���t�̂悤�ȉ~��`�悷��(�`�悵�������S�ʒuX,Y,�`�悷��360�x�ɑ΂��銄��,�O���t�����̃e�N�X�`��,�~�������̃e�N�X�`��)
void draw_Circle2(int X, int Y, double per, int Texture, int Texture2) {
	DrawCircleGauge(X, Y, 100, Texture, 100 - per);
	if (Texture2 != -1)	DrawCircleGauge(X, Y, 100, Texture2, 0);
}

//���̕`��(�ɍ��W)
inline void DrawArrow(double X, double Y, double vector, double length, unsigned int Color, float Thicknes) {
	DrawLineAA((float)X, (float)Y, (float)(X + length*cos(deg_to_rad(vector))), (float)(Y + length*sin(deg_to_rad(vector))), Color, Thicknes);

}

//�摜��3D��]�`��(�x�w��)
void DrawRotaImage3D(double X, double Y, double ExLate, double AngleX, double AngleY, double AngleZ, int grHandle) {
	//http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=2749

	VERTEX3D Vertex[6];
	VECTOR Angle, RotaAngle;//��]�x�N�g����X���q���̑���ɂ����]���x�N�g��
	MATRIX TransformMatrix;
	int DrawWindowX, DrawWindowY;
	GetDrawScreenSize(&DrawWindowX, &DrawWindowY);

	//�������_�ɂȂ�悤�ɕ␳��������
	Y = DrawWindowY - Y;

	//�����I�Ȋp�x�ɕϊ�
	AngleX = fmod(AngleX, 360.);
	AngleY = fmod(AngleY, 360.);
	AngleZ = fmod(AngleZ, 360.);

	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
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

	// ��]�p�����[�^�̐ݒ�
	Angle.x = (float)deg_to_rad(AngleX);
	Angle.y = (float)deg_to_rad(AngleY);
	Angle.z = (float)deg_to_rad(AngleZ);


	RotaAngle = VGet((float)cos(deg_to_rad(AngleY)), (float)sin(deg_to_rad(AngleY)), 0);


	// z����]�s��̍쐬�{xy���g��k���s��̍쐬�{xyz�g��k���s��̍쐬�{���W�ړ��s��̍쐬
	TransformMatrix = MGetRotZ(Angle.z);
	//TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
	TransformMatrix = MMult(TransformMatrix, MGetRotAxis(RotaAngle, Angle.x));
	//TransformMatrix = MMult(TransformMatrix, MGetRotX(Angle.x));
	//TransformMatrix = MGetIdent();
	//TransformMatrix = MMult(TransformMatrix, MGetScale(VGet(cos(Angle.x), cos(Angle.y), 1)));
	TransformMatrix = MMult(TransformMatrix, MGetScale(VGet((float)ExLate, (float)ExLate, (float)ExLate)));
	TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet((float)X, (float)Y, 0.0f)));

	// �s����g���ă��[���h���W���Z�o
	Vertex[0].pos = VTransform(VGet(-100.0f, 100.0f, 0.0f), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(100.0f, 100.0f, 0.0f), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(-100.0f, -100.0f, 0.0f), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(100.0f, -100.0f, 0.0f), TransformMatrix);

	Vertex[4].pos = Vertex[2].pos;
	Vertex[5].pos = Vertex[1].pos;

	// �s����g���Ė@�����Z�o
	Vertex[0].norm = VTransformSR(VGet(0.0f, 0.0f, -1.0f), TransformMatrix);
	Vertex[1].norm = Vertex[0].norm;
	Vertex[2].norm = Vertex[0].norm;
	Vertex[3].norm = Vertex[0].norm;
	Vertex[4].norm = Vertex[0].norm;
	Vertex[5].norm = Vertex[0].norm;

	// ���C�e�B���O�͍s��Ȃ�
	SetUseLighting(FALSE);

	// �Q�|���S���̕`��
	DrawPolygon3D(Vertex, 2, grHandle, TRUE);

}

//2�_�Ԃ̋��������߂�
double getDistance(double X1, double Y1, double X2, double Y2) {
	double dis2 = (X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1);//������2������߂�
	return sqrt(dis2);
}

//�~�ƒ����̌�_
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
	//�v�Z���s��
	double d = a * circleX + b * circleY + c;
	//�~�̒��S����̋�����2��
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

//�O�p�g��Ԃ�
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

//�T�C���g��Ԃ�(�t���[����������Ƃ��������ɂȂ�)
double getGraph_Sin(double frameVal, double Delta, double Shift) {
	frameVal = fmod(frameVal, 360);
	return sin(deg_to_rad(frameVal)) * Delta;
}

//-180�`180�̒l�ɕϊ�
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

//���ʂ̑��x���p���x�ɕϊ�(�s�N�Z��/�t���[�����x/�t���[��)(�����͕��ʂ̑��x�A���a)
double ConvertPixpF_To_DegpF(double Speed, double R) {
	//�p���x�����߂�(���W�A��)
	double redSpeed = Speed / R;
	return rad_to_deg(redSpeed);//�x�ɕϊ�
}

//�p���x�𕁒ʂ̑��x�ɕϊ�(�x/�t���[�����s�N�Z��/�t���[��)(�����͊p���x�A���a)
double ConvertDegpF_To_PixpF(double DegSpeed, double R) {
	//�p���x�����߂�(���W�A��)
	DegSpeed = fabs(DegSpeed);
	double redSpeed = deg_to_rad(DegSpeed);//���W�A���ɕϊ�
	return redSpeed*R;
}

//RGB����HSV�ɕϊ�
void RGB_to_HSV(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *V) {
	double max;
	double min;
	double R, G, B;

	// 0.0 - 1.0�i255�����j
	R = (double)r / 255;
	G = (double)g / 255;
	B = (double)b / 255;

	// �ő�l�E�ŏ��l
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

	// Hue�i�F���j
	if (max == R) {
		*H = 60 * (G - B) / (max - min);
	}
	else if (max == G) {
		*H = 60 * (B - R) / (max - min) + 120;
	}
	else {
		*H = 60 * (R - G) / (max - min) + 240;
	}
	if (max - min == 0) {//0���Z���������Ă���ꍇ
		*H = 0;
	}
	if (*H < 0.0) {
		*H += 360.0;
	}



	// Saturation�i�ʓx�j
	*S = (max - min) / max;
	// Value�i���x�j
	*V = max;

	//�l��100�i�K�ɕϊ�
	*S *= 100;
	*V *= 100;

}

//RGB����HSL�ɕϊ�
void RGB_to_HSL(unsigned char r, unsigned char g, unsigned char b, double *H, double *S, double *L) {
	unsigned char MaxVal = max(max(r, g), b);	//�ő�l�����߂�
	unsigned char MinVal = min(min(r, g), b);	//�ŏ��l�����߂�
	*H = 0;
	*S = 0;
	*L = (MaxVal + MinVal) / 2.;//L(�P�x)

	if (MaxVal != MinVal) {
		// H(�F��)  
		if (MaxVal == r) *H = 60. * (g - b) / (MaxVal - MinVal);
		if (MaxVal == g) *H = 60. * (b - r) / (MaxVal - MinVal) + 120;
		if (MaxVal == b) *H = 60. * (r - g) / (MaxVal - MinVal) + 240;

		// S(�ʓx)
		if (*L <= 127)	*S = (MaxVal - MinVal) / (double)(MaxVal + MinVal);
		else			*S = (MaxVal - MinVal) / (double)(510 - MaxVal - MinVal);
	}
	//S��L��100�i�K�ɕϊ�
	*S *= 100;
	*L *= (100 / 255.);


}

//HSV����RGB�ɕϊ�
void HSV_to_RGB(double H, double S, double V, unsigned char *R, unsigned char *G, unsigned char *B) {
	int Hi;
	double f, p, q, t;
	if (V < 0)		V = 0;
	if (V > 100)	V = 100;

	//0�`1�ɂ��ǂ�
	S /= 100;
	V /= 100;

	Hi = ((int)(H / 60)) % 6;
	f = H / 60 - Hi;
	p = V * (1 - S);
	q = V * (1 - f * S);
	t = V * (1 - (1 - f) * S);

	// 256�K���ɖ߂�
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

//HSL����RGB�ɕϊ�
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

//1byte(unsigned char)�̒l4��4byte(unsigned int)1�ɕϊ�����
unsigned int ConvertCollect1to4(unsigned char bit4, unsigned char bit3, unsigned char bit2, unsigned char bit1) {
	return (bit4 << 3 * 8) + (bit3 << 2 * 8) + (bit2 << 1 * 8) + bit1;
}

//4byte(unsigned int)1��1byte(unsigned char)�̒l4�ɕϊ�����
void ConvertCollect4to1(const unsigned int src, unsigned char *bit4, unsigned char *bit3, unsigned char *bit2, unsigned char *bit1) {
	if (bit4 != NULL)	*bit4 = (src & 0xff00'0000) >> 3 * 8;
	if (bit3 != NULL)	*bit3 = (src & 0x00ff'0000) >> 2 * 8;
	if (bit2 != NULL)	*bit2 = (src & 0x0000'ff00) >> 1 * 8;
	if (bit1 != NULL)	*bit1 = src & 0x0000'00ff;
}

//�w�肵���l���傫��2��n���Ԃ�
int Pot(int inSize) {
	int outSize = 1;
	while (outSize < inSize) outSize <<= 1;
	return outSize;
}

//�����x�A�ő呬�x�A�ړ��J�n����̌o�ߎ��Ԃ��猻�݂̈ړ��������v�Z����
double getMoveDistance(double a, double MaxSpeed, int Count) {
	//vt�O���t�̖ʐς��v�Z����Ηǂ�

	//���݂̃J�E���g���ōő呬�x�ɓ��B���Ă��邩�̊m�F
	double MaxSpeedCount = MaxSpeed / a;
	if (MaxSpeedCount >= Count) {//������
								 /*x=(1/2)*at^2*/
		double D = (1 / 2.)*a*Count*Count;
		return D;
	}
	else {

		//�ő呬�x�ɓ��B�����ꏊ�ł̃J�E���g���擾����
		double aD = (1 / 2.)*a*MaxSpeedCount*MaxSpeedCount;	//�������Ɉړ������������v�Z����
		double nD = MaxSpeed * (Count - MaxSpeedCount);		//�ő呬�x�œ��������^��
		return aD + nD;
	}
}