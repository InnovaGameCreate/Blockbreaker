#pragma once
//����v�Z�֐�(�ʂɂ�荂���œ����Ƃ�����)

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
		/*�擾�n*/
		extern double PI();														//PI�̒l���擾
		extern double Rotation(double X1, double Y1, double X2, double Y2);		//2�_�Ԃ̊p�x�̎擾(�x)
		extern double getDistance(double X1, double Y1, double X2, double Y2);	//2�_�Ԃ̋��������߂�
		extern double getGraph_Triangle(int Cycle, int Count);					//�O�p�g�̎擾
		extern double getGraph_Sin(double frameVal, double Delta, double Shift);//�T�C���g�̎擾
		extern int Pot(int inSize);												//�w�肵���l���傫��2��n����擾
		extern double getMoveDistance(double a, double MaxSpeed, int Count);	//�����x�A�ő呬�x�A�ړ��J�n����̌o�ߎ��Ԃ��猻�݂̈ړ��������擾

		/*�ϊ��n*/
		extern double RadToDeg(double rad);										//���W�A����x�ɕϊ�����
		extern double DegToRad(double deg);										//�x�����W�A���ɕϊ�����
		extern double map(double v, double sx, double sn, double dx, double dn);//���l�͈̔͂�ʂ͈̔͂ɕϊ�����
		extern int circulating(int Src, int Min, int Max);						//�w�肵���͈͂Ŏw�肵���l���z������悤�ɕϊ�����(Min�ȏ�Max����)
		extern double circulating_d(double Src, double Min, double Max);		//�w�肵���͈͂Ŏw�肵���l���z������悤�ɕϊ�����(Min�ȏ�Max����)(double�^)
		extern double InRange(double val, double min, double max);				//����l���ő�l�𒴂���ꍇ�͍ő�l�ɁA�ŏ��l�������ꍇ�͍ŏ��l�ɂ���(double�^)
		extern double getDegrees(double nDegrees);								//-180�`180�̒l�ɕϊ�
		extern double PixpF_To_DegpF(double Speed, double R);					//���ʂ̑��x���p���x�ɕϊ�(�s�N�Z��/�t���[�����x/�t���[��)(�����͕��ʂ̑��x�A���a)
		extern double DegpF_To_PixpF(double DegSpeed, double R);				//�p���x�𕁒ʂ̑��x�ɕϊ�(�x/�t���[�����s�N�Z��/�t���[��)(�����͊p���x�A���a)
		extern void RGB_to_HSV(unsigned char r, unsigned char g, unsigned char b, double * H, double * S, double * V);	//RGB����HSV�ɕϊ�
		extern void RGB_to_HSL(unsigned char r, unsigned char g, unsigned char b, double * H, double * S, double * L);	//RGB����HSL�ɕϊ�
		extern void HSV_to_RGB(double H, double S, double V, unsigned char * R, unsigned char * G, unsigned char * B);	//HSV����RGB�ɕϊ�
		extern void HSL_to_RGB(double H, double S, double L, unsigned char * R, unsigned char * G, unsigned char * B);	//HSL����RGB�ɕϊ�
		extern unsigned int ConvertCollect1to4(unsigned char bit4, unsigned char bit3, unsigned char bit2, unsigned char bit1);	//1byte(unsigned char)�̒l4��4byte(unsigned int)1�ɕϊ�����
		extern void ConvertCollect4to1(const unsigned int src, unsigned char * bit4, unsigned char * bit3, unsigned char * bit2, unsigned char * bit1);	//4byte(unsigned int)1��1byte(unsigned char)�̒l4�ɕϊ�����


		/*�����蔻��n*/
		extern int collision_rect(double rectX, double rectY, double rectWidth, double rectHeight, double pX, double pY);	//XY�����ɕ��s�Ȏl�p�`�Ɠ_�̂����蔻��
		extern int collisionLC(double X1, double Y1, double X2, double Y2, double circleX, double circleY, double circleR, double * ans1X, double * ans1Y, double * ans2X, double * ans2Y);	//�~�ƒ����̌�_

		extern void Gradation_RGB(int R1, int G1, int B1, int R2, int G2, int B2, double X, int * ansR, int * ansG, int * ansB);	//RGB�J���[�ŃO���f�B�G�[�V����������(X�͖ړI�F�܂ł̊���(0�y��{�F�z�`100�y�ړI�F�z)


	}
}
