#pragma once

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�萔�E�}�N��
//�����K���F�萔�͂��ׂđ啶���A�P��ƒP��̊Ԃ�_�ŋ�؂�

//�f�o�b�O�ݒ�̒�`(�g�p���Ȃ��ꍇ�̓R�����g�A�E�g)
#ifdef DEBUG
//#define _DEBUG_GAMEMAIN_			//�Q�[�����C���̃f�o�b�O
#endif // DEBUG


#ifdef _DEBUG_GAMEMAIN_
const int DEBUG_GAMEMAIN = TRUE;	//�Q�[�����C���̃f�o�b�O(�ϐ���)
#else
const int DEBUG_GAMEMAIN = FALSE;	//�Q�[�����C���̃f�o�b�O(�ϐ���)
#endif // _DEBUG_GAMEMAIN_



#define GAMEVERSION _T("0.0")		//�o�[�W������

#define DRAWFPS 60					//�`��FPS�ݒ�
#define UPDATEFPS 60				//����FPS�ݒ�
#define WINDOW_WIDTH 1280			//��ʂ̉���
#define WINDOW_HEIGHT 960			//��ʂ̍���
#define TITLE _T("Blockbreaker")	//�E�B���h�E�^�C�g��
#define PI (acos(-1.0))				//�~����
#define PIf ((float)acos(-1.0))		//�~����(float)

									//�}�N��
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))	//�z��̒��������߂�

#define deg_to_rad(deg) (((deg)/360.)*2*PI)	//�x���烉�W�A���ɕϊ�
#define rad_to_deg(rad) (((rad)/2./PI)*360)	//���W�A������x�ɕϊ�