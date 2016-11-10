//�g�b�v���j���[�֘A

#include "MainFunc.h"


Phase_TopMenu::Phase_TopMenu() {
	menu.addItem(_T("�X�^�[�g"), 4, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	menu.addItem(_T("�Q�[���I��"), 5, FONTTYPE_GenJyuuGothicLHeavy_Edge50);
	menu.setScrolltype(1);
	menu.sethaba(50);
	menu.setCenteringMode(0);
}

Phase_TopMenu::~Phase_TopMenu() {}

//�`�揈���̏�����
void Phase_TopMenu::Init_Draw() {
	if ((Tex_backGround = LoadGraph(_T("Data/image/colorbom.png"))) == -1)	printLog_E(_T("�t�@�C���̓ǂݍ��ݎ��s(Data/image/colorbom.png)"));
	menu.setEnable(TRUE);
}

//�v�Z�����̏�����
void Phase_TopMenu::Init_Update() {

}

//�`�揈��
void Phase_TopMenu::Draw() {
	
	DrawGraph(0, 0, Tex_backGround, FALSE);


	menu.Draw();
}

//�v�Z����
void Phase_TopMenu::Update() {
	Key();	//�L�[�������s��
	menu.Update();
}

//�`��̏I������
void Phase_TopMenu::Finalize_Draw() {

}

//�v�Z�̏I������
void Phase_TopMenu::Finalize_Update() {

}

//�L�[����
void Phase_TopMenu::Key() {

}

//�|�[�Y���j���[�̍��ڂ��I�����ꂽ�Ƃ��Ɏ��s�����
void Phase_TopMenu::SelectItem_menu::Event_Select(int No) {
	switch (No) {
	case 0:	//�Q�[���X�^�[�g
		Changefaze(FAZE_GameMain, THREAD_Update);//�t�F�[�Y�ύX
		break;
	case 1://�Q�[���I��
		ExitGameRequest();
		break;
	}
}