//#include "FlyText.h"
#include "MainFunc.h"

//�t���C�e�L�X�g�̕\��


FlyText::FlyText() {
}


FlyText::~FlyText() {
}

//�w�肵���t���C�e�L�X�g��������
void FlyText::Initialize(int num) {
	if (isEnable(num) == FALSE)	return;
	FlyTextData[num].Enable = FALSE;
}

//�t���C�e�L�X�g�̒ǉ�(�߂�l�͊Ǘ��ԍ�,-1�̎��͎��s)
int FlyText::addFlyText(double CenterX, double CenterY, int limit, FONTTYPE font, unsigned int Color, TCHAR *fmt, ...) {
	//�󂢂Ă���z���T������
	int temp = -1;
	for (int i = 0; i < FLYTEXT_MAXNUM; i++) {
		if (isEnable(i) == FALSE) {
			temp = i;
			break;
		}
	}

	//�z�񂪒T������Ȃ������ꍇ�͎��s
	if (temp == -1)	return -1;

	//�z��̏��������s��
	Initialize(temp);

	//�����̏����t�������񂩂當����𐶐�����

	va_list arg;//�������i�[����ꏊ
	va_start(arg, fmt);
	_vstprintf_s(FlyTextData[temp].string, fmt, arg);  //Printf�ɊY�����镔��
	va_end(arg);

	//���̑��̐ݒ�𔽉f����
	FlyTextData[temp].fonthandle = Font_getHandle(font);
	FlyTextData[temp].Color = Color;
	FlyTextData[temp].x = CenterX;
	FlyTextData[temp].y = CenterY;
	FlyTextData[temp].Count = 0;
	FlyTextData[temp].Limit = limit;

	//�t���C�e�L�X�g��L���ɂ���
	FlyTextData[temp].Enable = TRUE;
	return temp;
}

//�w�肵���t���C�e�L�X�g���L�����ǂ����̎擾(TRUE�ŗL��)
int FlyText::isEnable(int num) {
	if (num < 0 || FLYTEXT_MAXNUM <= num)	return FALSE;
	return FlyTextData[num].Enable;
}

//�t���C�e�L�X�g��`�悷��
void FlyText::Draw() {
	for (auto dat : FlyTextData) {
		if (dat.Enable) {
			double val = 0;
			val = dat.Count / (double)dat.Limit;
			int Alpha = 255;
			if (val > 0.7)	Alpha = (int)((1 - val) / 0.3 * 255);

			//�������W�Ȃ̂ł��L�^����Ă���̂ŁA�`��ʒu���C������
			float x = (float)(dat.x - GetDrawStringWidthToHandle(dat.string, (int)strlenDx(dat.string), dat.fonthandle) / 2.);	//���S���W���獶�[�̍��W�ɕϊ�
			float y = (float)(dat.y - GetFontAscentToHandle(dat.fonthandle) / 2.);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
			DrawStringFToHandle((float)dat.x, (float)(dat.y - val * 20), dat.string, dat.Color, dat.fonthandle);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

//�t���C�e�L�X�g�̌v�Z����
void FlyText::Update() {
	for (auto &dat : FlyTextData) {
		if (dat.Enable) {
			dat.Count++;	//�J�E���g�����Z����
			if (dat.Limit < dat.Count) {
				//�����������ꍇ�̓t���C�e�L�X�g�𖳌��ɂ���
				dat.Enable = FALSE;
			}
		}
	}
}