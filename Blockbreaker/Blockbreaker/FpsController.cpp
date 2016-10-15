//FPS�R���g���[���֘A
#include "FpsController.h"


FpsController::FpsController(int FPS) {
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("FpsController�̃R���X�g���N�^���Ă΂�܂���"));
	Initialize(FPS);
}

//������
void FpsController::Initialize(int fps) {
	mStartTime = 0;
	mCount = 0;
	FPS_Ave = 0;
	FPS = fps;
	VSyncWaitMode = false;
}

//�t���[���̌o�ߎ��Ԃ̑S�����O�Ɏ��s����֐�
void FpsController::Update_First() {
}

//�t���[�����[�g���ێ����邽�߂ɑҋ@���Ԃ𔭐�������
void FpsController::Wait() {
	if (VSyncWaitMode)	return;	//�����������L���ȏꍇ�͏������Ȃ�

	int tookTime = GetNowCount() - mStartTime;			//������������
	int waitT = mCount * 1000 / FPS - tookTime;			//�҂ׂ�����

	//�K���ҋ@����60FPS�ȏ�ɂȂ�Ȃ��悤�ɑҋ@���Ԃ�݂���(���[�v�ɂ����鎞�Ԃ���������Ƃ�)
	//if (waitT < 0)	waitT = 1000 / (FPS);

	//���ϑҋ@���Ԃ̌v�Z
	if (waitT >= 0)	WaitTime += waitT;
	else			WaitTime = waitT;

	if (waitT > 0) {
		Sleep(waitT);	//�ҋ@
	}
}

//�t���[���̌o�ߎ��Ԃ̑S������Ɏ��s����֐�
void FpsController::Update_Last() {
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		FPS_Ave = 1000. / ((t - mStartTime) / (double)N);	//����FPS�̌v�Z
		WaitTime_Ave = WaitTime / (double)N;				//���ϑҋ@���Ԃ̌v�Z
		WaitTime = 0;
		mCount = 0;
	}
	else {
	}
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	mCount++;			//�J�E���^�̃J�E���g�A�b�v
	FrameCount++;	//�o�߃t���[���̃J�E���g�A�b�v
}

//���������ɂ��t���[���̒�~���s�����ǂ����̐ݒ�(TRUE�Ő����������g�p����A�܂肱�̃��W���[���őҋ@�������s��Ȃ�)
void FpsController::SetVSyncMode(int Flag) {
	VSyncWaitMode = (Flag) ? true : false;
}

//���������ɂ��t���[���̒�~���s�����ǂ����̎擾(TRUE�Ő����������g�p����A�܂肱�̃��W���[���őҋ@�������s��Ȃ�)
int FpsController::GetVSyncMode() {
	return ((VSyncWaitMode) ? TRUE : FALSE);
}

//���݂̕���FPS���擾����
double FpsController::GetFPS_Average() {
	return FPS_Ave;
}

//�o�߃t���[�������擾
unsigned int FpsController::GetFrameCount() {
	return FrameCount;
}

//1�t���[��������̕��ϑҋ@���Ԃ̎擾
double FpsController::GetWaitTime_Average() {
	return WaitTime_Ave;
}

//1�t���[��������̕��ϑҋ@���Ԃ̊����̎擾
double FpsController::GetWaitTime_Average_Par() {
	double f_Time;//1�t���[���ɂ����鎞��
	double par;//����
	f_Time = 1000. / FPS;
	par = (GetWaitTime_Average() * 100) / f_Time - 100;
	if (par < 0)	par = -par;//�}�C�i�X�Ȃ畄���t�](0.00�̎��̕�����+-���Ă�������������)
	return par;
}