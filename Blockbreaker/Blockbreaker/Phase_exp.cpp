#include "MainFunc.h"


Phase_exp::Phase_exp()
{
	
}

void Phase_exp::Draw()
{
	DrawGraph(0,0, tex_exp,FALSE);			//����摜�\��t��
}

void Phase_exp::Update()
{

	//�Q�[���p�b�h���L�[�{�[�h�̃L�[�������ꂽ�Ƃ��g�b�v��ʂ֖߂�
	if (getKeyBind(KEYBIND_PAUSE) == 1) phaseController.ChangefazeRequest(FAZE_TopMenu, 0, 0);
}

//������(�`�揈��)
void Phase_exp::Init_Draw()
{
	tex_exp = LoadGraph(_T("Data/image/expWindow.png"));	//����̉摜�\��t���Ă�������
	if (tex_exp == -1) printLog_E(_T("�t�@�C���̓ǂݍ��݂̎��s[���]"));
}

//�I������(�`��)
void Phase_exp::Fin_Draw() {
	DeleteGraph(tex_exp);
}