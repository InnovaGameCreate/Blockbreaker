#pragma once
//enum��`
//�����K���F"enum��"+_+"�啶���Ŏn�܂�v�f��"

//�L�[�o�C���h
enum KEYBIND {
	KEYBIND_SELECT,			//���ڂ̌���
	KEYBIND_PAUSE,			//�L�����Z��/�|�[�Y
	KEYBIND_ROTAL,			//��������u���b�N�𔽎��v���ɉ�]������
	KEYBIND_ROTAR,			//��������u���b�N�����v���ɉ�]������
	KEYBIND_UP,				//���ڑI��:��
	KEYBIND_DOWN,			//���ڑI��:��/��������u���b�N�̉���
	KEYBIND_LEFT,			//���ڑI��:��/��������u���b�N�̍��ړ�
	KEYBIND_RIGHT,			//���ڑI��:�E/��������u���b�N�̉E�ړ�
	KEYBIND_NUM				//�L�[�o�C���h�̐�
};

//�t�F�[�Y�֌W
enum FAZE {
	FAZE_Nothing,				//��������
	FAZE_TopMenu,				//�g�b�v���j���[
	FAZE_GameMain,				//���ۂ̃Q�[���v���C���
	FAZE_Manual,				//���������
	FAZE_NUM					//�t�F�[�Y�̐�
};

//�A�i���O�X�e�B�b�N�̑��샂�[�h���邩�H
enum ANALOGSTICKMODE {
	ANALOGSTICKMODE_NOMAL,	//�g�p����[�|����ɉ����đ�����ύX����]
	ANALOGSTICKMODE_VECTOR,	//�g�p����[�p�x�̂ݎ擾�������͈��ɂ���]
	ANALOGSTICKMODE_NOUSE,	//�g�p���Ȃ�
	ANALOGSTICKMODE_NUM		//�v�f�̌�
};

//�X���b�h
enum THREAD {
	THREAD_Draw,			//�`��X���b�h
	THREAD_Update			//�����X���b�h
};

//�t�H���g�̎��
//�ǉ��̖����K���F"�啶���Ŏn�܂�v�f��"�̕�����"�t�H���g��_�t�H���g�̐ݒ�(�G�b�W�t���A�t�H���g�T�C�Y�Ȃ�)"�ɂȂ��Ă��܂�
enum FONTTYPE {
	FONTTYPE_GenJyuuGothicLHeavy_Edge25,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y25
	FONTTYPE_GenJyuuGothicLHeavy_Edge30,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y30
	FONTTYPE_GenJyuuGothicLHeavy_Edge35,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y35
	FONTTYPE_GenJyuuGothicLHeavy_Edge40,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y40
	FONTTYPE_GenJyuuGothicLHeavy_Edge50,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y40
	FONTTYPE_GenJyuuGothicLHeavy_Edge60,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y60
	FONTTYPE_GenJyuuGothicLHeavy_Edge70,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y70
	FONTTYPE_GenJyuuGothicLHeavy_Edge80,	//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y80

	FONTTYPE_SFSquareHeadCondensed_Edge15,	//SF Square Head Condensed�G�b�W�t���T�C�Y15
	FONTTYPE_SFSquareHeadCondensed_Edge25,	//SF Square Head Condensed�G�b�W�t���T�C�Y25
	FONTTYPE_SFSquareHeadCondensed_Edge35,	//SF Square Head Condensed�G�b�W�t���T�C�Y35
	FONTTYPE_SFSquareHeadCondensed_Edge45,	//SF Square Head Condensed�G�b�W�t���T�C�Y45
};