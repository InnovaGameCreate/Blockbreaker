#pragma once
//�L�[�{�[�h����̕�������
#include <tchar.h>



class KeyInput
{
public:
	KeyInput();
	void Start();	//�L�[�{�[�h������J�n����
	
	void Draw(int x, int y);	//�`��

	int isEnable();		//�L�[�{�[�h���L�����ǂ����̎擾
	void Key();			//�L�[����
	TCHAR * getStr();	//���͂���Ă��镶����̎擾
private:
	int Enable;	//�L�����ǂ���

	int Select;	//���ݑI�����Ă���{�^��

	int len;	//���ݓ��͍ς݂̕�����
	
	TCHAR str[7];//���͂��ꂽ������
};

static TCHAR ch[] = { 'A', 'B', 'C', 'B', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' , 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
