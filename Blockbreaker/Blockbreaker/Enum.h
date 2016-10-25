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
};

//���ʉ��̎��
//�G�N�X�v���[���[��wav�t�@�C�������ĒT���₷���悤��"�啶���Ŏn�܂�v�f��"�͎��ۂ̃t�@�C�����ƈ�v�����Ă��܂�
enum SE_TYPE {
	SE_TYPE_ChangeSelect,		//���ڂ̑I�������ړ����鎞�̉�
	SE_TYPE_DecisionSelect,		//���ڂ����肵�����̉�
	SE_TYPE_ButtonCancel,		//���ڂ��L�����Z���������̉�
	SE_TYPE_OwnBarrier,			//�������o���A�𔭓������Ƃ��̉�
	SE_TYPE_OwnDeath,			//���������S�������̉�
	SE_TYPE_Bulletfire1,		//�G���e���𔭎˂����Ƃ��̉�1(�A���p�H)
	SE_TYPE_Bulletfire2,		//�G���e���𔭎˂����Ƃ��̉�2(����)
	SE_TYPE_Bulletfire3,		//�G���e���𔭎˂����Ƃ��̉�3(��)
	SE_TYPE_Bulletfire4,		//�G���e���𔭎˂����Ƃ��̉�4(���[�U�[)
	SE_TYPE_Bulletfire5,		//�G���e���𔭎˂����Ƃ��̉�5(����)
	SE_TYPE_Bulletfire6,		//�G���e���𔭎˂����Ƃ��̉�6(����)
	SE_TYPE_Bulletfire7,		//�G���e���𔭎˂����Ƃ��̉�7(���[�U�[�\��)
	SE_TYPE_Shotfire,			//���@���V���b�g�𔭎˂����Ƃ��̉�
	SE_TYPE_Shotfire2,			//���@���V���b�g�𔭎˂����Ƃ��̉�2
	SE_TYPE_Graze,				//���@�����������ꂽ�Ƃ��̉�
	SE_TYPE_ShotHit,			//���@�̃V���b�g���G�ɓ��������Ƃ��̉�
	SE_TYPE_ShotHit2,			//���@�̃V���b�g���G�ɓ��������Ƃ��̉�2
	SE_TYPE_EnemyDeath,			//�G�����S�����Ƃ��̉�
	SE_TYPE_EnemyDeath2,		//�G�����S�����Ƃ��̉�2
	SE_TYPE_Pause,				//�{�[�Y�{�^��
	SE_TYPE_Itemget,			//�A�C�e�����擾�����Ƃ��̉�
	SE_TYPE_PowerUp,			//�p���[�A�b�v�����Ƃ��̉�
	SE_TYPE_Timeout,			//�������Ԃ̉�
	SE_TYPE_Timeout2,			//�������Ԃ̉�2
	SE_TYPE_Extend,				//1�A�b�v�̉�
	SE_TYPE_bomb_Muteki,		//���G�{���̉�
	SE_TYPE_Bonus,				//�{�[�i�X�̉�
	SE_TYPE_GetBomb,			//�{���擾�̉�
	SE_TYPE_bomb_DamageFloor,	//�_���[�W���{���̉�
	SE_TYPE_bomb_BarrierFloor,	//�o���A���{���̉�
	SE_TYPE_ChargeUP,			//�`���[�W�U���̒i�KUP�̉�
	SE_TYPE_ChargeOK,			//�`���[�W�U���̃��L���X�g�����̉�
	SE_TYPE_Charge1,			//�`���[�W�U��1�̌��ʉ�
	SE_TYPE_Charge2,			//�`���[�W�U��2�̌��ʉ�
	SE_TYPE_NUM					//���ʉ��̌�(�w�肵���ꍇ�͌��ʉ�����)
};