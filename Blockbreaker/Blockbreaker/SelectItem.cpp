#include "MainFunc.h"



// �����I�e���v���[�g�̃C���X�^���X��
template class SelectItem<Phase_GameMain>;

//�R���X�g���N�^
template <typename T>
SelectItem<T>::SelectItem(double x, double y)
{
	SelectedItem = 0;
	for (int i = 0; i < 20; i++) {
		data[i].enable = false;
	}
	X = x;
	Y = y;
	Enable = true;
	Select_Enable = true;
	SelectType = 0;
	Haba = 150;
	Centering = -1;
}

//���ڂ̒ǉ�
template <typename T>
int SelectItem<T>::addItem(TCHAR *str, size_t len, Callback_SelectItem_Selected func, Callback_Draw drawfunc, FONTTYPE font) {
	int free = -1;
	for (int i = 0; i < 20; i++) {
		if (data[i].enable == false) {
			free = i;
			break;
		}
	}
	if (free == -1) {
		printLog_E(_T("�v�f����t�ł�"));
		return -1;
	}
	_tcscpy_s(data[free].str, str);
	data[free].func_SelectItem_Selected = func;
	data[free].func_Callback_Draw = drawfunc;
	data[free].Alpha = 0;
	data[free].SelectEnable = true;
	data[free].font = font;
	data[free].enable = true;
	return 0;
}

//�I����L���E�����ɂ���(�L�[�ő��삵�č��ڂ�ς���Ȃ�)
template <typename T>
void SelectItem<T>::setSelectEnable(int b_flag) {
	Select_Enable = (b_flag) ? true : false;
	if (Select_Enable)	printLog_I(_T("SelectItem�̑I�����y�L���z�ɐݒ肵�܂���"));
	else				printLog_I(_T("SelectItem�̑I�����y�����z�ɐݒ肵�܂���"));
}

//�I�������̂𖳌���
template <typename T>
void SelectItem<T>::setEnable(int b_flag) {
	Enable = (b_flag) ? true : false;
	if (Enable)	printLog_I(_T("SelectItem���y�L���z�ɐݒ肵�܂���"));
	else		printLog_I(_T("SelectItem���y�����z�ɐݒ肵�܂���"));
}

//�I���̏�Ԃ�ݒ�(0�ŃX�N���[��1�ŃX�N���[�����Ȃ����)
template <typename T>
void SelectItem<T>::setScrolltype(int type) {
	SelectType = type;
}

//����̑I������I���\�ɂ��邩�ǂ���(true�ŉ\)
template <typename T>
void SelectItem<T>::setItemEnable(bool b_Enable, int No) {
	if (isEnableItem(No)) {//���ڂ����݂���ꍇ
		data[No].SelectEnable = (b_Enable) ? true : false;
		if (data[No].SelectEnable == false && SelectedItem == No) {//�����ɂ����ꍇ���I�����Ă���ꍇ�A�I�����̈ʒu�𒲐�����
			int num = SelectedItem + 1;//���̍��ڂ�I���������Ƃɂ���
			for (; num < 20; num++) {
				if (data[num].enable && data[num].SelectEnable)	break;
			}
			if (num < 20) {
				SelectedItem = num;//���ڂ�����Ȃ�I������ς���
				return;
			}
			//���̑I�����������������ꍇ
			num = SelectedItem - 1;//���̍��ڂ�I���������Ƃɂ���
			for (; num >= 0; num--) {
				if (data[num].enable && data[num].SelectEnable)	break;
			}
			if (num >= 0) {
				SelectedItem = num;//���ڂ�����Ȃ�I������ς���
				return;
			}
			//�����O�������������ꍇ
			//�G���[
			printLog_E(_T("�I���\�A�C�e��������܂���ł���"));
		}
	}
}

//�A�C�e���̕���ݒ肷��
template <typename T>
void SelectItem<T>::sethaba(double haba) {
	Haba = haba;
}

//�Ăяo�����̃C���X�^���X��ݒ肷��
template <typename T>
void SelectItem<T>::setinstance(T *instance) {
	classObject = instance;
}

//���ڂ̒����ʒu�̐ݒ�(-1�ō��A0�Œ����A1�ŉE)
template <typename T>
void SelectItem<T>::setCenteringMode(int centeringMode) {
	if (centeringMode < 0) {
		Centering = -1;
	}
	else if(centeringMode > 0){
		Centering = 1;
	}
	else {
		Centering = 0;
	}
}

//���ڂ̕`��
template <typename T>
void SelectItem<T>::Draw() {
	double x = X;
	double y = Y;
	int Count = 0;//�A�C�e���̃J�E���g��
	for (int i = 0; i < 20; i++) {
		if (data[i].enable && data[i].SelectEnable) {
			unsigned int color = GetColor(240, 240, 240);
			int alpha = 128;//���ߓx
			if (i == SelectedItem && Enable)	color = GetColor(224, (unsigned int)(160 * getGraph_Triangle(120)), (unsigned int)(160 * getGraph_Triangle(120)));
			if (abs(getZettaichi(i)) == 2)							alpha = 128;
			else if (abs(getZettaichi(i)) == 1 && SelectType == 0)	alpha = 194;
			else if (i == SelectedItem)								alpha = 255;
			if (i != SelectedItem && Select_Enable == false)		alpha = 64;
			if (Enable == false)									alpha = 128;
			if (abs(getZettaichi(i)) >= 3 && SelectType == 0)		alpha = 0;
			if (SelectType == 0)	y = Y + (getZettaichi(i) * Haba);
			else					y = Y + (Count * Haba);
			data[i].Alpha = alpha;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			int Place_X = 0;
			if (Centering < 0) {
				Place_X = 0;
			}
			else if(Centering > 0){
				//�`��\��̕�����̕����擾����
				Place_X = -GetDrawStringWidthToHandle(data[i].str, ARRAY_LENGTH(data[i].str), Font_getHandle(data[i].font));
			}
			else {
				Place_X = -GetDrawStringWidthToHandle(data[i].str, ARRAY_LENGTH(data[i].str), Font_getHandle(data[i].font))/2;
			}
			DrawStringFToHandle((float)(Place_X + x + 4), (float)(y + 4), data[i].str, GetColor(30, 30, 30), Font_getHandle(data[i].font));
			DrawStringFToHandle((float)(Place_X + x), (float)y, data[i].str, color, Font_getHandle(data[i].font));
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (i == SelectedItem && data[i].func_Callback_Draw != NULL && classObject != NULL) {
				Callback_Draw rr = data[i].func_Callback_Draw;
				(classObject->*rr)();
			}
			Count++;
		}
	}
}

//���ۂɑI�����Ă��鍀�ڂƌ��ݕ`�悵�Ă��鍀�ڂƂ̎��ۂ̌����ڂ̍����擾(�I�𖳌����ڂ��l���������ɂȂ��Ă��邩�擾)
template <typename T>
int SelectItem<T>::getZettaichi(int No) {
	//�I�����ڂƂ̐�Βl�̌v�Z
	if (No == SelectedItem)	return 0;//�I�����Ă��鍀�ڂ̏ꍇ�͍�0
	int Count = 0;
	//�I���A�C�e���̌�땔���̏ꍇ
	for (int i = SelectedItem; i < No; i++) {
		if (data[i].enable && data[i].SelectEnable) {
			Count++;
		}
	}
	//�I���A�C�e�����O�̏ꍇ
	for (int i = SelectedItem - 1; i >= No; i--) {
		if (data[i].enable && data[i].SelectEnable) {
			Count--;
		}
	}
	return Count;
}

//���ڂ̍X�V(�L�[����Ƃ�)
template <typename T>
void SelectItem<T>::Update() {
	if (Select_Enable == false)	return;
	if (Enable == false)		return;
	if (getKeyBind(KEYBIND_UP) == 1) {
		int num = SelectedItem - 1;//���̍��ڂ�I���������Ƃɂ���
		for (; num >= 0; num--) {
			if (data[num].enable && data[num].SelectEnable)	break;
		}
		if (num >= 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);
			SelectedItem = num;//���ڂ�����Ȃ�I������ς���
		}
	}
	else if (getKeyBind(KEYBIND_DOWN) == 1) {
		int num = SelectedItem + 1;//���̍��ڂ�I���������Ƃɂ���
		for (; num < 20; num++) {
			if (data[num].enable && data[num].SelectEnable)	break;
		}
		if (num < 20) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);
			SelectedItem = num;//���ڂ�����Ȃ�I������ς���
		}
	}
	else if (getKeyBind(KEYBIND_SELECT) == 1 ) {
		SoundEffect_Play(SE_TYPE_DecisionSelect);
		if (data[SelectedItem].func_SelectItem_Selected != NULL && classObject != NULL) {
			Callback_SelectItem_Selected rr = data[SelectedItem].func_SelectItem_Selected;
			(classObject->*rr)();

		}
	}
}

//�I�����Ă��鍀�ڂ̎擾
template <typename T>
int SelectItem<T>::getSelecedtItem() {
	return SelectedItem;
}

//���ڂ̑I��
template <typename T>
void SelectItem<T>::setSelecedtItem(int No) {
	if (isEnableItem(No)) {
		SelectedItem = No;
		printLog_I(_T("SelectItem�̏����I�����y%d�z�ɐݒ肵�܂���"), SelectedItem);
	}
}

//�w�肳�ꂽ�ԍ��ɍ��ڂ����݂��邩�ǂ����̎擾
template <typename T>
bool SelectItem<T>::isEnableItem(int No) {
	if (No < 0 || 20 <= No)	return false;
	return data[No].enable;
}

//�Ō�ɕ`�悵���Ƃ��̃��l���擾
template <typename T>
int SelectItem<T>::getItemAlpha(int No) {
	if (isEnableItem(No)) {
		return data[No].Alpha;
	}
	return 0;
}