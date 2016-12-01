#pragma once
//�L�[�{�[�h����̕�������
#include <tchar.h>

/*�L�[���͂̃R�[���o�b�N�֐��N���X*/
//�L�[���͂��I���������ɌĂ΂��
class KeyInputCallback_End {
public:
	virtual void operator()(TCHAR *str) = 0;
};


class KeyInput
{
public:
	KeyInput();
	void Start(int x, int y, KeyInputCallback_End *keyInputCallback_End);	//�L�[�{�[�h������J�n����
	
	void Draw();	//�`��

	int isEnable();					//�L�[�{�[�h���L�����ǂ����̎擾
	void Key(unsigned int *key);	//�L�[����
	TCHAR * getStr();				//���͂���Ă��镶����̎擾
private:
	int Enable;	//�L�����ǂ���

	int Select;	//���ݑI�����Ă���{�^��

	int len;	//���ݓ��͍ς݂̕�����

	int Select_BeforeEnter;	//����L�[�Ɉړ�����O�ɑI������Ă����L�[

	int DrawX, DrawY;	//�`��ʒu
	
	TCHAR str[7];//���͂��ꂽ������

	KeyInputCallback_End *keyInputCallback_End;	//�L�[���͂��I���������ɌĂ΂��t�@���N�^
};

//�L�[�{�[�h�ɓ��͂��镶����(!,?��Del�L�[�ƌ���L�[)
static TCHAR ch[] = { 'A', 'B', 'C', 'B', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' , 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?' };
