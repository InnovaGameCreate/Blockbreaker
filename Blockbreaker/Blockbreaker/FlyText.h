#pragma once
#include "Enum.h"

class FlyText {
public:
	int addFlyText(double CenterX, double Y, int limit, FONTTYPE font, unsigned int Color, TCHAR *fmt, ...);	//�t���C�e�L�X�g�̒ǉ�
	void Draw();		//�t���C�e�L�X�g��`�悷��
	void Update();		//�t���C�e�L�X�g�̌v�Z����
	FlyText();
	~FlyText();
private:
	static const int FLYTEXT_MAXNUM = 100;

	struct Data {
		Data() {
			Enable = FALSE;
		}
		int Enable;			//�L�����ǂ���
		TCHAR string[100];	//�`�悷�镶����
		int fonthandle;		//�`�悷��t�H���g�n���h��(DX���C�u����)
		unsigned int Color;	//�`�悷�镶����̐F
		double x, y;		//�������`�悷��ʒu(���)
		int Count;			//�t���C�e�L�X�g�̃J�E���g�^
		int Limit;			//�t���C�e�L�X�g�����ł���J�E���g��
	};

	Data FlyTextData[FLYTEXT_MAXNUM];


	void Initialize(int i);	//�w�肵���t���C�e�L�X�g��������
	int isEnable(int i);	//�w�肵���t���C�e�L�X�g���L�����ǂ����̎擾(TRUE�ŗL��)
};