#pragma once

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<��>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//�萔�E�}�N��
//�����K���F�萔�͂��ׂđ啶���A�P��ƒP��̊Ԃ�_�ŋ�؂�

#define PI (acos(-1.0))				//�~����
#define PIf ((float)acos(-1.0))		//�~����(float)

//�}�N��
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))	//�z��̒��������߂�

#define deg_to_rad(deg) (((deg)/360.)*2*PI)	//�x���烉�W�A���ɕϊ�
#define rad_to_deg(rad) (((rad)/2./PI)*360)	//���W�A������x�ɕϊ�