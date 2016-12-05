#include "MainFunc.h"


KeyInput::KeyInput() {
	Enable = FALSE;
	Select = 0;
	len = 0;
	DrawCountTotal = 0;
	BackImage = 0;
}

//�L�[�{�[�h������J�n����
void KeyInput::Start(int x, int y, KeyInputCallback_End *keyInputCallback_End) {
	if (isEnable())	return;
	DrawX = (float)x;
	DrawY = (float)y;
	KeyInput::keyInputCallback_End = keyInputCallback_End;
	len = 0;
	Select = 0;
	Select_BeforeEnter = 0;
	UpdateCount = 0;
	for (auto &dat : str)	dat = '_';
	str[ARRAY_LENGTH(str) - 1] = '\0';
	Enable = TRUE;
	printLog_I(_T("�L�[�{�[�h��L���ɂ��܂�"));
}

//�L�[�{�[�h���L�����ǂ����̎擾
int KeyInput::isEnable() {
	return Enable;
}

//�`��
void KeyInput::Draw() {
	if (!isEnable())	return;
	DrawCountTotal++;	//�`��J�E���g
	if (DrawCountTotal == 1)	DrawFirst();	//����`�掞�Ɏ��s�����
	float x = DrawX;
	float y = DrawY;
	int Alpha = 255;	//���ߒl

	//�������W�������W�ɕς���
	x -= 150;

	//�J�E���^���`��ʒuY�𒲐�����
	if (UpdateCount < 30) {
		double val = UpdateCount / 30.;
		Alpha = (int)(255 * val);
		val = 1 - val;	//�����𔽓]������
		y = y + (float)(20 * val);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);
	DrawGraphF(x, y, BackImage, FALSE);
	//�����̕\���쐬����
	for (int i = 0; i < ARRAY_LENGTH(ch); i++) {
		TCHAR str[10];
		if (ch[i] == '!')		_stprintf_s(str, _T("��"));
		else if (ch[i] == '?')	_stprintf_s(str, _T("����"));
		else					_stprintf_s(str, _T("%c"), ch[i]);
		unsigned int color = GetColor(100, 200, 100);
		if (Select == i)	color = GetColor(200, 100, 100);

		//����L�[�̏ꍇ�̂ݕʂŕ`�悷��
		if (ch[i] == '?') {
			Font_DrawStringCenterWithShadow(x + 150, y + 20 + (i / 9) * 40 + 15, str, color, GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge25);
		}
		else {
			Font_DrawStringCenterWithShadow(x + 20 + ((i % 9)) * 32, y + 20 + (i / 9) * 40, str, color, GetColor(10, 10, 10), FONTTYPE_GenJyuuGothicLHeavy_Edge25);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�X�V����
void KeyInput::Update() {
	if (!isEnable())	return;
	UpdateCount++;
}

//�L�[����
void KeyInput::Key(unsigned int *key) {
	if (!isEnable())		return;
	if (UpdateCount < 30)	return;	//�O��30�t���[���͏o������艽�����Ȃ�

	if (key[KEYBIND_RIGHT] == 1) {
		//�E�ړ�
		int Moved = Select + 1;//���z�I�Ɉړ���̍��W���L�^����
		if (Select / 9 != Moved / 9 || Moved >= ARRAY_LENGTH(ch)) {
			//�s���ς��ꍇ�ƁA�z�񂪃I�[�o�[���鎞�͔��Α��ɍs��
			Moved = (Select / 9) * 9;	//���Α��ɍs��
		}
		//�ړ��𔽉f������
		Select = Moved;
	}
	if (key[KEYBIND_LEFT] == 1) {
		//�E�ړ�
		int Moved = Select - 1;//���z�I�Ɉړ���̍��W���L�^����
		if (Select / 9 != Moved / 9 || Moved < 0) {
			Moved = ((Select / 9) * 9 + (9 - 1) < ARRAY_LENGTH(ch)) ? (Select / 9) * 9 + (9 - 1) : ARRAY_LENGTH(ch) - 1;	//���Α��ɍs��
		}
		//�ړ��𔽉f������
		Select = Moved;
	}
	if (key[KEYBIND_DOWN] == 1) {
		//���ړ�
		int Moved = Select + 9;//���z�I�Ɉړ���̍��W���L�^����
		if (Moved >= ARRAY_LENGTH(ch)) {
			Moved = ARRAY_LENGTH(ch) - 1;
		}
		//�ړ��悪����L�[�̏ꍇ�͈ړ����̏ꏊ���L�^����
		if (ch[Moved] == '?' && Moved != Select)	Select_BeforeEnter = Select;
		Select = Moved;

	}
	if (key[KEYBIND_UP] == 1) {
		//��ړ�
		//�ړ���������L�[�̏ꍇ�͈ړ����ɖ߂�
		if (ch[Select] == '?' && Select != Select_BeforeEnter) {
			Select = Select_BeforeEnter;
		}
		else if (Select - 9 >= 0)				Select -= 9;
	}
	if (key[KEYBIND_SELECT] == 1) {
		if (ch[Select] == '!') {
			//�����̍폜
			if (len > 0) {
				//���͕���������ꍇ�̂�1�����폜����
				len--;
				str[len] = '_';
			}
		}
		else if (ch[Select] == '?') {
			//���ڂ̌���
			Enable = FALSE;
			//�t�@���N�^���Ăяo��
			if(keyInputCallback_End != NULL)	keyInputCallback_End->operator()(str);
		}
		else {
			if (len < ARRAY_LENGTH(str) - 1) {
				//�����̒ǉ�����
				str[len] = ch[Select];
				len++;
			}
		}
	}
}

//���͂���Ă��镶����̎擾
TCHAR *KeyInput::getStr() {
	if(isEnable())	return str;
	else			return _T("");
}

//����`�掞�ɂ̂ݎ��s�����
void KeyInput::DrawFirst() {
	//�w�i�e�N�X�`���̃��[�h���s��
	if ((BackImage = LoadGraph(_T("Data/image/KeyBoadBack.png"))) == -1)	printLog_E(_T("�t�@�C���̃��[�h�Ɏ��s���܂����B(Data/image/KeyBoadBack.png)"));
}