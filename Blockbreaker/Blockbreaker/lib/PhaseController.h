#pragma once
//�t�F�[�Y�R���g���[���[
//���C�u�����̓ǂݍ���
#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "PhaseControllerx64_d.lib")
	#else
		#pragma comment(lib, "PhaseControllerx86_d.lib")
	#endif // _WIN64
#else
	#ifdef _WIN64
		#pragma comment(lib, "PhaseControllerx64.lib")
	#else
		#pragma comment(lib, "PhaseControllerx86.lib")
	#endif // _WIN64
#endif // _DEBUG

#include <Windows.h>
#include <process.h>

//�t�F�[�Y�N���X�̐e�N���X
namespace PCon {
	class Phase_
	{
	private:
		virtual void Draw();			//�`�揈��
		virtual void Update();			//�v�Z����
		virtual void Update_Final();	//Update��ɌĂ΂��
	public:
		//���z�֐�
		virtual void Initialize(int arg);		//������(�v�Z����)
		virtual void Finalize();		//�I������(�v�Z����)

		virtual void DrawFunc() final;	//�`��ۂɌĂ΂��`��֐�
		virtual void UpdateFunc() final;//�`��ۂɌĂ΂��`��֐�
	};

	//�t�F�[�Y�R���g���[���[�̃R�[���o�b�N��p�N���X
	class PhaseController_Proc
	{
	public:
		virtual void Proc_Changefazed(int Before, int After);	//�t�F�[�Y�ڍs���I�������Ƃ�
		virtual void Proc_DrawPauseing(int count);				//�`��X���b�h���ꎞ��~���Ă���Ƃ��ɑ���Ɏ��s�����(���[�h���Ƃ�)
		virtual void Proc_UpdatePauseing(int count);			//�v�Z�X���b�h���ꎞ��~���Ă���Ƃ��ɑ���Ɏ��s�����(���[�h���Ƃ�)
	};


	//�t�F�[�Y�R���g���[���[�̃��C���N���X
	class PhaseController
	{
	public:
		static const int VerNo;			//�o�[�W�����ԍ�

		PhaseController(int MaxNum);	//�t�F�[�Y�̍ő吔���w�肵�ď���������
		~PhaseController();

		void ChangefazeRequest(int NO, DWORD LoadTime_Milliseconds, int arg);	//�t�F�[�Y�ύX���N�G�X�g�𑗂�(Update���[�v�̍ŏ��Ɏ��s����܂�)

		void Update();	//�v�Z���C�����[�v
		void Draw();	//�`�惁�C�����[�v

		void addFaze(int FazeNo, Phase_ * phase);	//�t�F�[�Y�̒�`���s��

		void setCallBack(PCon::PhaseController_Proc *Ploc);	//�R�[���o�b�N�N���X��o�^����
		void setMultiThread(int Flag);	//�}���`�X���b�h������s�����ǂ����̐ݒ�
		int isMultiThread();	//�}���`�X���b�h������s�����ǂ����̎擾

		int getCurrantPhase();	//���݂̃t�F�[�Y���擾����
		int getTotalPhase();	//�t�F�[�Y�̍ő吔���擾

		void Load();			//���[�h���Ɏ��s����郍�[�h�֐�(�Ă΂Ȃ����ƁI�I)
	private:
		//�ݒ�
		int Flag_MultiThread;	//�}���`�X���b�h����Ȃ�TRUE

		//�t�F�[�Y�֘A
		int CurrantFaze;		//���݂̃t�F�[�Y

		//�t�F�[�Y�ύX���N�G�X�g�֘A
		int Request_Faze;			//�ύX��̃t�F�[�Y(-1�Ŗ���)
		DWORD Request_LoadTime;		//�ύX��̃t�F�[�Y(-1�Ŗ���)
		int Request_arg;			//����

		int LoadUpdateCount;		//���[�h���̌v�Z�J�E���g
		int LoadDrawCount;			//���[�h���̕`��J�E���g

		//��Ԑ���֘A
		int DrawPauseRequest = FALSE;		//�`��̃X�L�b�v�̃��N�G�X�g
		int DrawPause = FALSE;				//�`��̃X�L�b�v

		void Request_DrawPause();			//�`��̒�~��v�����A��~����܂őҋ@����
		void ChangefazeUpdate();			//�t�F�[�Y��ύX����(Update)

		int PhaseMaxNum;		//�t�F�[�Y�̍ő吔
		Phase_ **Phase;			//�t�F�[�Y�z��̃|�C���^(��ɔz��̐擪�A�h���X�ɂȂ�)
		Phase_ DefaultPhase_;	//�f�t�H���g�̃t�F�[�Y
		PhaseController_Proc *PhaseController_Proc;	//�R�[���o�b�N�֐��N���X

		HANDLE LoadThreadhandle;	//���[�h�X���b�h�̃n���h��

		int JudgeFazeNo(int FazeNo);		//�w�肵���l���t�F�[�Y�z��̓Y�����Ƃ��đÓ����ǂ����̎擾(TRUE�Ó�)

	};
}

