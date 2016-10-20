//���[�h��ʊ֌W

static int LoadScreen;//���[�h���
static int LoadScreen2;//���[�h���

//������
void LoadMenu_Initialize() {
	//���[�h��ʂ̃��[�h
	LoadScreen = LoadGraph(_T("Data/LoadMenu/LoadBack.png"));
	if (LoadScreen == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�摜���[�h���s(Data/LoadMenu/LoadBack.png)"));
	}
	//���[�h��ʂ̃��[�h2
	LoadScreen2 = LoadGraph(_T("Data/LoadMenu/LoadBack2.png"));
	if (LoadScreen2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("�摜���[�h���s(Data/LoadMenu/LoadBack2.png)"));
	}
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("���[�h��ʂ̏������ɐ���"));
}

//���[�h��ʂ̕\��
void LoadMenu_Draw() {
	//���[�h��ʂ̕`��
	DrawGraph(0, 0, LoadScreen, 0);

	DrawStringToHandle(760 + 4, 870 + 4, _T("Now Loading�c"), GetColor(30, 30, 30), Font_getHandle(FONTTYPE_GenJyuuGothicLHeavy_Edge70));
	DrawStringToHandle(760, 870, _T("Now Loading�c"), GetColor(0xcb, 0xff, 0x8e), Font_getHandle(FONTTYPE_GenJyuuGothicLHeavy_Edge70));
	ScreenFlip();		//����ʂ�\��ʂɔ��f
}

//���[�h��ʂ̕\��(�ŏ��̋N�����p)
void LoadMenu_Draw2() {
	//���[�h��ʂ̕`��
	DrawGraph(0, 0, LoadScreen2, 0);
	ScreenFlip();		//����ʂ�\��ʂɔ��f
}