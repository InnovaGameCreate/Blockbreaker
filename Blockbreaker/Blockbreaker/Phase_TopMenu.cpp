//�g�b�v���j���[�֘A

#include "MainFunc.h"


Phase_TopMenu::Phase_TopMenu() {
}


Phase_TopMenu::~Phase_TopMenu() {
}

//�`�揈���̏�����
void Phase_TopMenu::Init_Draw() {

}

//�v�Z�����̏�����
void Phase_TopMenu::Init_Update() {

}

//�`�揈��
void Phase_TopMenu::Draw() {
	ClearDrawScreen();//�`����e�̍폜

}

//�v�Z����
void Phase_TopMenu::Update() {
	Key();	//�L�[�������s��
}

//�`��̏I������
void Phase_TopMenu::Finalize_Draw() {

}

//�v�Z�̏I������
void Phase_TopMenu::Finalize_Update() {

}

//�L�[����
void Phase_TopMenu::Key() {
	if (getKeyBind(KEYBIND_SELECT) == 1) {
		//����L�[�������ꂽ��
		Changefaze(FAZE_GameMain, THREAD_Update);//�t�F�[�Y�ύX
	}
	else if (getKeyBind(KEYBIND_PAUSE) == 1) {
		//�I��
		ExitGameRequest();
	}
}