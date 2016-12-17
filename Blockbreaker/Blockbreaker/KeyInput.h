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
	void Update();	//�X�V����

	int isEnable();					//�L�[�{�[�h���L�����ǂ����̎擾
	void Key(unsigned int *key);	//�L�[����
	TCHAR * getStr();				//���͂���Ă��镶����̎擾
private:
	int Enable;	//�L�����ǂ���

	int DrawCountTotal;		//�Q�[�����N�����Ă���`����s������
	int UpdateCount;		//�L�[�{�[�h���L���ɂȂ��Ă���̍X�V�J�E���g

	int Select;	//���ݑI�����Ă���{�^��

	int len;	//���ݓ��͍ς݂̕�����

	int BackImage;	//�w�i�C���[�W�̃n���h��

	int Select_BeforeEnter;	//����L�[�Ɉړ�����O�ɑI������Ă����L�[

	float DrawX, DrawY;	//�`��ʒu
	
	TCHAR str[7];//���͂��ꂽ������

	KeyInputCallback_End *keyInputCallback_End;	//�L�[���͂��I���������ɌĂ΂��t�@���N�^

	void DrawFirst();	//����`�掞�ɂ̂ݎ��s�����
};

//�L�[�{�[�h�ɓ��͂��镶����(!,?��Del�L�[�ƌ���L�[)
static TCHAR ch[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' , 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?' };
