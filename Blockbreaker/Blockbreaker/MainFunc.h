#pragma once
#include "Phase_GameMain.h"
#include "Phase_TopMenu.h"
#include "SelectItem.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*�O���錾(���̃w�b�_�t�@�C���ȊO�Ŏg�p�����N���X�A�\���̂�錾���Ă�������)*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�萔�E�}�N��
//�����K���F�萔�͂��ׂđ啶���A�P��ƒP��̊Ԃ�_�ŋ�؂�

#include "Define.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�\����
//typedef����̂̓v���O�����S�̂Ŏg�p������݂̂̂ɂ��Ă��������B
//�t�@�C�����ł̂ݎg�p����\���̂�typedef���Ȃ��ł��������B(�⊮�ŏo�Ă��Ă������̂�)



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//enum��`
//�����K���F"enum��"+_+"�啶���Ŏn�܂�v�f��"

#include "Enum.h"


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*�N���X*/


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�N���X�̃C���X�^���X(�O���[�o���ϐ�)
extern Phase_Default phase_Default;		//�f�t�H���g�̃t�F�[�Y
extern Phase_GameMain phase_GameMain;	//�Q�[�����C���̃t�F�[�Y
extern Phase_TopMenu phase_TopMenu;		//�g�b�v���j���[�̃t�F�[�Y


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�֐��Q
/*SoundEffect*/
extern void SoundEffect_init();				//������
extern void SoundEffect_update();			//���ʉ��̌v�Z�������[�v(���ʉ���炷�����O�ɌĂԂ���)
extern void SoundEffect_Play(SE_TYPE type);	//���ʉ��̍Đ�
extern void SoundEffect_PlayPlace(SE_TYPE type, double plaxeX, double placeY);	//���ʉ��̍Đ�(�ʒu�ŉ��ʂ��ς����)(���͋@�\���Ȃ�)
extern void SoundEffect_Save();				//���ʉ��̏�Ԃ̕ۑ�
extern void SoundEffect_Load();				//���ʉ��̏�Ԃ̕���
extern void SoundEffect_AllPause();			//���ʉ������ׂă|�[�Y����
extern void SoundEffect_SetSEVolume(int Volume);	//���ʉ��̉��ʂ����ׂĕύX����(0�`100)
extern int SoundEffect_GetSEVolume();		//���ʉ��̉��ʎ擾(0�`100)
extern void SoundEffect_LongSEStop();		//�������ʉ��̒�~
extern void SoundEffect_LongSEPause();		//�������ʉ��̃|�[�Y
extern void SoundEffect_LongSEResume();		//�������ʉ��̃��W���[��
extern void SoundEffect_SafePlay(SE_TYPE type);	//���d�Ō��ʉ��̍Đ����s����\��������Ƃ��Ɏg�p������ʉ��̍Đ��֐�(1���ʉ�������1�t���[���Ɉ�x�܂ł����Đ��֐����Ă΂�Ȃ��Ȃ�)

/*ShaderBackGround.cpp*/
extern void ShaderBackGround_Initialize();		//�V�F�[�_�֘A������
extern void ShaderBackGround_DeleteBlock(double X, double Y, double place, int srcImage, int Effect1, int Effect2);	//�V�F�[�_�𗘗p���ď��ł���u���b�N��`�悷��

/*FlyText.cpp*/
