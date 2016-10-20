#pragma once


#ifndef PHASECONTROLLER_H_
#error PhaseController.h��Include���Ă�������
#endif // !PHASECONTROLLER_H_



class Phase_GameMain : public PhaseController
{

private:
	int gameWindow;	//�Q�[����ʂ�`�悷��n���h��
	int CursorX, CursorY;//�J�[�\���ʒu

	int Flag_Pause;			//�|�[�Y��Ԃ��ǂ���(�Q�[���̐i�s�����ׂĒ�~���܂�)(TRUE�Ń|�[�Y)
	int Flag_pauseRequest;	//�|�[�Y��Ԃ��ǂ����̃��N�G�X�g(�|�[�Y�����͂��ׂĂ̏����̍Ō�ōs������)



	void Draw();
	void Update();
	void GameMain_Key();
public:
	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	/*�ݒ�n*/
	int GameMain_CursorX_add(int Val);			//�J�[�\���ʒu�𑊑ΓI�Ɉړ�����(�߂�l:���ۂɈړ�������)
	int GameMain_CursorY_add(int Val);			//�J�[�\���ʒu�𑊑ΓI�Ɉړ�����(�߂�l:���ۂɈړ�������)
	void GameMain_PauseRequest(int b_Flag);		//�|�[�Y��Ԃ̃��N�G�X�g

	/*�擾�n*/
	int	GameMain_getCursorX();																			//�J�[�\���ʒu���擾����
	int	GameMain_getCursorY();																			//�J�[�\���ʒu���擾����
	void GameMain_Convert_Block_FromIngame(int blockX, int blockY, double *IngameX, double *IngameY);	//�u���b�N�̍��W�H����C���Q�[���̍��W�̍��[���擾����(�֐��I�ɏo�����߁A���݂��Ȃ��͂��̃u���b�N�ʒu���v�Z�o���܂�)
	int	GameMain_isPaused();
};

