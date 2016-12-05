#pragma once
#include <Windows.h>
#pragma comment (lib, "winmm.lib")

#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "FpsControllerx64_d.lib")
	#else
		#pragma comment(lib, "FpsControllerx86_d.lib")
	#endif // WIN64
#else
	#ifdef _WIN64
		#pragma comment(lib, "FpsControllerx64.lib")
	#else
		#pragma comment(lib, "FpsControllerx86.lib")
	#endif // WIN64
#endif // _DEBUG

namespace SK {
	const int VerNo = 100;		//�o�[�W�����ԍ�


	class FpsController
	{
	public:
		FpsController(int FPS);
		void Update_First();		//�t���[���̌o�ߎ��Ԃ̑S�����O�Ɏ��s����֐�
		void Update_Last();			//�t���[���̌o�ߎ��Ԃ̑S������Ɏ��s����֐�
		void Wait();				//�t���[�����[�g���ێ����邽�߂ɑҋ@���Ԃ𔭐�������

		void SetVSyncMode(int Flag);	//���������ɂ��t���[���̒�~���s�����ǂ����̐ݒ�(TRUE�Ő����������g�p����A�܂肱�̃��W���[���őҋ@�������s��Ȃ�)

		double GetFPS_Average();			//���݂̕���FPS���擾����
		unsigned int GetFrameCount();		//�o�߃t���[�������擾
		double GetWaitTime_Average();		//1�t���[��������̕��ϑҋ@���Ԃ̎擾
		double GetWaitTime_Average_Par();	//1�t���[��������̕��ϑҋ@���Ԃ̊����̎擾
		int GetVSyncMode();					//���������ɂ��t���[���̒�~���s�����ǂ����̎擾(TRUE�Ő����������g�p����A�܂肱�̃��W���[���őҋ@�������s��Ȃ�)
		int isDebug();						//�f�o�b�O���L�����ǂ����̎擾(TRUE�f�o�b�O�L��)
		int isx86();						//32Bit�Ȃ�TRUE

		unsigned int *getCounter();			//�J�E���^���Ǘ�����ϐ��̃|�C���^���擾����(�댯)
	private:
		DWORD mStartTime;			//����J�n����
		int mCount;					//�J�E���^
		static const int N = 60;	//���ς��Ƃ�T���v����
		int FPS;					//�ڕWFPS
		int WaitTime;				//�ҋ@����
		bool VSyncWaitMode;			//���������̑ҋ@���s���ݒ�(true�Ő����������g�p����)

		double FPS_Ave;				//����fps
		double WaitTime_Ave;		//���ϑҋ@����


		unsigned int FrameCount;	//�o�߃t���[���J�E���g


		void Initialize(int fps);	//������

	};
}