//���ʉ��֌W

//���ʉ��̏��
struct SE_STATE {
	int Playing;	//�Đ������ǂ���
	int Place;		//���ʉ��̍Đ��ʒu
};

//���ʉ��̏��
struct SE_DATA {
	struct SE_STATE Bomb_Muteki;
	struct SE_STATE Bomb_DamageFloor;
	struct SE_STATE Bomb_BarrierFloor;
	struct SE_STATE EnemyDeath2;
	struct SE_STATE Charge1;
};



static int ButtonSelect;	//���ڂ̑I�������ړ����鎞�̉�
static int ButtonDecision;	//���ڂ����肵�����̉�
static int ButtonCancel;	//���ڂ��L�����Z���������̉�
static int OwnBarrier;		//�������o���A�𔭓������Ƃ��̉�
static int OwnDeath;		//���������S�������̉�
static int Bulletfire1;		//�G���e���𔭎˂����Ƃ��̉�1(�A��)
static int Bulletfire2;		//�G���e���𔭎˂����Ƃ��̉�2
static int Bulletfire3;		//�G���e���𔭎˂����Ƃ��̉�3
static int Bulletfire4;		//�G���e���𔭎˂����Ƃ��̉�4
static int Bulletfire5;		//�G���e���𔭎˂����Ƃ��̉�5
static int Bulletfire6;		//�G���e���𔭎˂����Ƃ��̉�6
static int Bulletfire7;		//�G���e���𔭎˂����Ƃ��̉�7
static int Shotfire;		//���@���V���b�g�𔭎˂����Ƃ��̉�
static int Shotfire2;		//���@���V���b�g�𔭎˂����Ƃ��̉�2
static int Graze;			//���@�����������ꂽ�Ƃ��̉�
static int ShotHit;			//���@�̃V���b�g���G�ɓ��������Ƃ��̉�
static int ShotHit2;		//���@�̃V���b�g���G�ɓ��������Ƃ��̉�2
static int EnemyDeath;		//�G�����S�����Ƃ��̉�
static int EnemyDeath2;		//�G�����S�����Ƃ��̉�2
static int Pause;			//�{�[�Y�{�^��
static int Itemget;			//�A�C�e�����擾�����Ƃ��̉�
static int PowerUp;			//�p���[�A�b�v�����Ƃ���
static int Timeout;			//�������Ԃ̉�
static int Timeout2;		//�������Ԃ̉�2
static int Extend;			//1�A�b�v��
static int Bomb_Muteki;		//���G�{���̉�
static int Bonus;			//�{�[�i�X
static int GetBomb;			//�{���擾
static int Bomb_DamageFloor;//�_���[�W���{���̉�
static int Bomb_BarrierFloor;//�o���A���{���̉�
static int Charge_Up;		//�`���[�W�U���̒i�KUP�̉�
static int Charge_OK;		//�`���[�W�U���̃��L���X�g�����̉�
static int Charge1;			//�`���[�W�U��1�̌��ʉ�
static int Charge2;			//�`���[�W�U��2�̌��ʉ�

static struct SE_DATA data;				//���ʉ��̏��
static struct SE_DATA Save_data;		//���ʉ��̏��
static struct SE_DATA pause_data;		//���ʉ��̏��(�|�[�Y��)

										//�Z�[�u����x�ł��������ǂ����̃t���O
static int Saved;

//����0�`255
static int BGM_Volume;//�Ǘ��݂̂����I
static int SE_Volume;

//���ʉ����Đ����ꂽ���ǂ����̃t���O(�ꉞ�J�E���g�A�b�v����)
static unsigned int sE_playData[SE_TYPE_NUM];





//������
void SoundEffect_init() {

	data.Bomb_Muteki.Playing = 0;
	pause_data.Bomb_Muteki.Playing = 0;
	data.Bomb_DamageFloor.Playing = 0;
	pause_data.Bomb_DamageFloor.Playing = 0;
	data.Bomb_BarrierFloor.Playing = 0;
	pause_data.Bomb_BarrierFloor.Playing = 0;
	data.EnemyDeath2.Playing = 0;
	pause_data.EnemyDeath2.Playing = 0;
	data.Charge1.Playing = 0;;
	pause_data.Charge1.Playing = 0;;

	Saved = 0;
	BGM_Volume = 255;
	SE_Volume = 255;

	ButtonSelect = LoadSoundMemBase(_T("Data/SE/ChangeSelect.wav"), 1);
	if (ButtonSelect == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/ChangeSelect.wav)"));
	}
	ButtonDecision = LoadSoundMemBase(_T("Data/SE/DecisionSelect.wav"), 1);
	if (ButtonDecision == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/DecisionSelect.wav)"));
	}
	ButtonCancel = LoadSoundMemBase(_T("Data/SE/ButtonCancel.wav"), 1);
	if (ButtonCancel == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/ButtonCancel.wav)"));
	}
	OwnBarrier = LoadSoundMemBase(_T("Data/SE/OwnBarrier.wav"), 1);
	if (OwnBarrier == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/OwnBarrier.wav)"));
	}
	OwnDeath = LoadSoundMemBase(_T("Data/SE/OwnDeath.wav"), 1);
	if (OwnDeath == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/OwnDeath.wav)"));
	}
	Bulletfire1 = LoadSoundMemBase(_T("Data/SE/Bulletfire1.wav"), 1);
	if (Bulletfire1 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire1.wav)"));
	}
	Bulletfire2 = LoadSoundMemBase(_T("Data/SE/Bulletfire2.wav"), 1);
	if (Bulletfire2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire2.wav)"));
	}
	Bulletfire3 = LoadSoundMemBase(_T("Data/SE/Bulletfire3.wav"), 1);
	if (Bulletfire3 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire3.wav)"));
	}
	Bulletfire4 = LoadSoundMemBase(_T("Data/SE/Bulletfire4.wav"), 1);
	if (Bulletfire4 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire4.wav)"));
	}
	Bulletfire5 = LoadSoundMemBase(_T("Data/SE/Bulletfire5.wav"), 1);
	if (Bulletfire5 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire5.wav)"));
	}
	Bulletfire6 = LoadSoundMemBase(_T("Data/SE/Bulletfire6.wav"), 1);
	if (Bulletfire6 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire6.wav)"));
	}
	Bulletfire7 = LoadSoundMemBase(_T("Data/SE/Bulletfire7.wav"), 1);
	if (Bulletfire7 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bulletfire7.wav)"));
	}
	Shotfire = LoadSoundMemBase(_T("Data/SE/Shotfire.wav"), 1);
	if (Shotfire == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Shotfire.wav)"));
	}
	Shotfire2 = LoadSoundMemBase(_T("Data/SE/Shotfire2.wav"), 1);
	if (Shotfire2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Shotfire2.wav)"));
	}
	Graze = LoadSoundMemBase(_T("Data/SE/Graze.wav"), 1);
	if (Graze == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Graze.wav)"));
	}
	ShotHit = LoadSoundMemBase(_T("Data/SE/ShotHit.wav"), 1);
	if (ShotHit == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/ShotHit.wav)"));
	}
	ShotHit2 = LoadSoundMemBase(_T("Data/SE/ShotHit2.wav"), 1);
	if (ShotHit2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/ShotHit2.wav)"));
	}
	EnemyDeath = LoadSoundMemBase(_T("Data/SE/EnemyDeath.wav"), 1);
	if (EnemyDeath == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/EnemyDeath.wav)"));
	}
	EnemyDeath2 = LoadSoundMemBase(_T("Data/SE/EnemyDeath2.wav"), 1);
	if (EnemyDeath2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/EnemyDeath2.wav)"));
	}
	Pause = LoadSoundMemBase(_T("Data/SE/Pause.wav"), 1);
	if (Pause == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Pause.wav)"));
	}
	Itemget = LoadSoundMemBase(_T("Data/SE/Itemget.wav"), 1);
	if (Itemget == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Itemget.wav)"));
	}
	PowerUp = LoadSoundMemBase(_T("Data/SE/PowerUp.wav"), 1);
	if (PowerUp == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/PowerUp.wav)"));
	}
	Timeout = LoadSoundMemBase(_T("Data/SE/Timeout.wav"), 1);
	if (Timeout == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Timeout.wav)"));
	}
	Timeout2 = LoadSoundMemBase(_T("Data/SE/Timeout2.wav"), 1);
	if (Timeout2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Timeout2.wav)"));
	}
	Extend = LoadSoundMemBase(_T("Data/SE/Extend.wav"), 1);
	if (Extend == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Extend.wav)"));
	}
	Bomb_Muteki = LoadSoundMemBase(_T("Data/SE/BombMUTEKI.wav"), 1);
	if (Bomb_Muteki == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/BombMUTEKI.wav)"));
	}
	Bonus = LoadSoundMemBase(_T("Data/SE/Bonus.wav"), 1);
	if (Bonus == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Bonus.wav)"));
	}
	GetBomb = LoadSoundMemBase(_T("Data/SE/GetBomb.wav"), 1);
	if (GetBomb == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/GetBomb.wav)"));
	}
	Bomb_DamageFloor = LoadSoundMemBase(_T("Data/SE/BombDANAMEFLOOR.wav"), 1);
	if (Bomb_DamageFloor == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/BombDANAMEFLOOR.wav)"));
	}
	Bomb_BarrierFloor = LoadSoundMemBase(_T("Data/SE/BombBARRIER.wav"), 1);
	if (Bomb_BarrierFloor == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/BombBARRIER.wav)"));
	}
	Charge_Up = LoadSoundMemBase(_T("Data/SE/ChargeUp.wav"), 1);
	if (Charge_Up == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/ChargeUp.wav)"));
	}
	Charge_OK = LoadSoundMemBase(_T("Data/SE/ChargeOK.wav"), 1);
	if (Charge_OK == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/ChargeOK.wav)"));
	}
	Charge1 = LoadSoundMemBase(_T("Data/SE/Charge1.wav"), 10);
	if (Charge1 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Charge1.wav)"));
	}
	Charge2 = LoadSoundMemBase(_T("Data/SE/Charge2.wav"), 10);
	if (Charge2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("SE�̃��[�h�Ɏ��s(Data/SE/Charge2.wav)"));
	}

}

//���ʉ��̌v�Z�������[�v(���ʉ���炷�����O�ɌĂԂ���)
void SoundEffect_update() {
	for (int i = 0; i < SE_TYPE_NUM; i++) {
		sE_playData[i] = 0;
	}

}

//���ʉ��̍Đ�
void SoundEffect_Play(SE_TYPE type) {
	switch (type)
	{
	case SE_TYPE_ChangeSelect:
		PlaySoundMem(ButtonSelect, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_DecisionSelect:
		PlaySoundMem(ButtonDecision, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ButtonCancel:
		PlaySoundMem(ButtonCancel, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_OwnBarrier:
		PlaySoundMem(OwnBarrier, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_OwnDeath:
		PlaySoundMem(OwnDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire1:
		PlaySoundMem(Bulletfire1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire2:
		PlaySoundMem(Bulletfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire3:
		PlaySoundMem(Bulletfire3, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire4:
		PlaySoundMem(Bulletfire4, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire5:
		PlaySoundMem(Bulletfire5, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire6:
		PlaySoundMem(Bulletfire6, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire7:
		PlaySoundMem(Bulletfire7, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire:
		PlaySoundMem(Shotfire, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire2:
		PlaySoundMem(Shotfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Graze:
		PlaySoundMem(Graze, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit:
		if (CheckSoundMem(ShotHit) == 0)	PlaySoundMem(ShotHit, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit2:
		PlaySoundMem(ShotHit2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath:
		PlaySoundMem(EnemyDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath2:
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Pause:
		PlaySoundMem(Pause, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Itemget:
		PlaySoundMem(Itemget, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_PowerUp:
		PlaySoundMem(PowerUp, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout:
		PlaySoundMem(Timeout, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout2:
		PlaySoundMem(Timeout2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Extend:
		PlaySoundMem(Extend, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_Muteki:
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bonus:
		PlaySoundMem(Bonus, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_GetBomb:
		PlaySoundMem(GetBomb, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_DamageFloor:
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_BarrierFloor:
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeUP:
		PlaySoundMem(Charge_Up, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeOK:
		PlaySoundMem(Charge_OK, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge1:
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge2:
		PlaySoundMem(Charge2, DX_PLAYTYPE_BACK);
		break;
	}
}

//���ʉ��̍Đ�(�ʒu�ŉ��ʂ��ς����)(���͋@�\���Ȃ�)
void SoundEffect_PlayPlace(SE_TYPE type, double plaxeX, double placeY) {
	switch (type)
	{
	case SE_TYPE_ChangeSelect:
		PlaySoundMem(ButtonSelect, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_DecisionSelect:
		PlaySoundMem(ButtonDecision, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ButtonCancel:
		PlaySoundMem(ButtonCancel, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_OwnBarrier:
		PlaySoundMem(OwnBarrier, DX_PLAYTYPE_BACK);
		break;
	case  SE_TYPE_OwnDeath:
		PlaySoundMem(OwnDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire1:
		PlaySoundMem(Bulletfire1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire2:
		PlaySoundMem(Bulletfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire3:
		PlaySoundMem(Bulletfire3, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire4:
		PlaySoundMem(Bulletfire4, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire5:
		PlaySoundMem(Bulletfire5, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire6:
		PlaySoundMem(Bulletfire6, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire7:
		PlaySoundMem(Bulletfire7, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire:
		PlaySoundMem(Shotfire, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire2:
		PlaySoundMem(Shotfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Graze:
		PlaySoundMem(Graze, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit:
		if (CheckSoundMem(ShotHit) == 0)	PlaySoundMem(ShotHit, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit2:
		PlaySoundMem(ShotHit2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath:
		PlaySoundMem(EnemyDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath2:
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Pause:
		PlaySoundMem(Pause, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Itemget:
		PlaySoundMem(Itemget, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_PowerUp:
		PlaySoundMem(PowerUp, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout:
		PlaySoundMem(Timeout, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout2:
		PlaySoundMem(Timeout2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Extend:
		PlaySoundMem(Extend, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_Muteki:
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bonus:
		PlaySoundMem(Bonus, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_GetBomb:
		PlaySoundMem(GetBomb, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_DamageFloor:
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_BarrierFloor:
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeUP:
		PlaySoundMem(Charge_Up, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeOK:
		PlaySoundMem(Charge_OK, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge1:
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge2:
		PlaySoundMem(Charge2, DX_PLAYTYPE_BACK);
		break;
	}
}

//���ʉ��̏�Ԃ̕ۑ�
void SoundEffect_Save() {
	Save_data.Bomb_Muteki.Playing = CheckSoundMem(Bomb_Muteki);	//SE�̍Đ���Ԃ̕ۑ�
	if (Save_data.Bomb_Muteki.Playing) {
		Save_data.Bomb_Muteki.Place = GetSoundCurrentTime(Bomb_Muteki);
	}
	Save_data.Bomb_DamageFloor.Playing = CheckSoundMem(Bomb_DamageFloor);	//SE�̍Đ���Ԃ̕ۑ�
	if (Save_data.Bomb_DamageFloor.Playing) {
		Save_data.Bomb_DamageFloor.Place = GetSoundCurrentTime(Bomb_DamageFloor);
	}
	Save_data.Bomb_BarrierFloor.Playing = CheckSoundMem(Bomb_BarrierFloor);	//SE�̍Đ���Ԃ̕ۑ�
	if (Save_data.Bomb_BarrierFloor.Playing) {
		Save_data.Bomb_BarrierFloor.Place = GetSoundCurrentTime(Bomb_BarrierFloor);
	}
	Save_data.EnemyDeath2.Playing = CheckSoundMem(EnemyDeath2);	//SE�̍Đ���Ԃ̕ۑ�
	if (Save_data.EnemyDeath2.Playing) {
		Save_data.EnemyDeath2.Place = GetSoundCurrentTime(EnemyDeath2);
	}
	Save_data.Charge1.Playing = CheckSoundMem(Charge1);	//SE�̍Đ���Ԃ̕ۑ�
	if (Save_data.Charge1.Playing) {
		Save_data.Charge1.Place = GetSoundCurrentTime(Charge1);
	}
	Saved = 1;
}

//���ʉ��̏�Ԃ̕���
void SoundEffect_Load() {
	if (Saved == 0)	return;
	if (Save_data.Bomb_Muteki.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(Save_data.Bomb_Muteki.Place, Bomb_Muteki);
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.Bomb_DamageFloor.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(Save_data.Bomb_DamageFloor.Place, Bomb_DamageFloor);
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.Bomb_BarrierFloor.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(Save_data.Bomb_BarrierFloor.Place, Bomb_BarrierFloor);
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.EnemyDeath2.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(Save_data.EnemyDeath2.Place, EnemyDeath2);
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.Charge1.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(Save_data.Charge1.Place, Charge1);
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK, 0);
	}
}

//���ʉ������ׂă|�[�Y����
void SoundEffect_AllPause() {
	StopSoundMem(ButtonSelect);
	StopSoundMem(ButtonDecision);
	StopSoundMem(ButtonCancel);
	StopSoundMem(OwnBarrier);
	StopSoundMem(OwnDeath);
	StopSoundMem(Bulletfire1);
	StopSoundMem(Bulletfire2);
	StopSoundMem(Bulletfire3);
	StopSoundMem(Bulletfire4);
	StopSoundMem(Bulletfire5);
	StopSoundMem(Bulletfire6);
	StopSoundMem(Bulletfire7);
	StopSoundMem(Shotfire);
	StopSoundMem(Shotfire2);
	StopSoundMem(Graze);
	StopSoundMem(ShotHit);
	StopSoundMem(ShotHit2);
	StopSoundMem(EnemyDeath);
	StopSoundMem(EnemyDeath2);
	StopSoundMem(Pause);
	StopSoundMem(Itemget);
	StopSoundMem(PowerUp);
	StopSoundMem(Timeout);
	StopSoundMem(Timeout2);
	StopSoundMem(Extend);
	StopSoundMem(Bomb_Muteki);
	StopSoundMem(Bonus);
	StopSoundMem(GetBomb);
	StopSoundMem(Bomb_DamageFloor);
	StopSoundMem(Bomb_BarrierFloor);
	StopSoundMem(Charge_Up);
	StopSoundMem(Charge_OK);
	StopSoundMem(Charge1);
	StopSoundMem(Charge2);
}

//���ʉ��̉��ʂ����ׂĕύX����(0�`100)
void SoundEffect_SetSEVolume(int Volume) {
	int VolumePal = (int)(255 * (Volume / 100.));
	SE_Volume = VolumePal;
	ChangeVolumeSoundMem(VolumePal, ButtonSelect);
	ChangeVolumeSoundMem(VolumePal, ButtonDecision);
	ChangeVolumeSoundMem(VolumePal, ButtonCancel);
	ChangeVolumeSoundMem(VolumePal, OwnBarrier);
	ChangeVolumeSoundMem(VolumePal, OwnDeath);
	ChangeVolumeSoundMem(VolumePal, Bulletfire1);
	ChangeVolumeSoundMem(VolumePal, Bulletfire2);
	ChangeVolumeSoundMem(VolumePal, Bulletfire3);
	ChangeVolumeSoundMem(VolumePal, Bulletfire4);
	ChangeVolumeSoundMem(VolumePal, Bulletfire5);
	ChangeVolumeSoundMem(VolumePal, Bulletfire6);
	ChangeVolumeSoundMem(VolumePal, Bulletfire7);
	ChangeVolumeSoundMem(VolumePal, Shotfire);
	ChangeVolumeSoundMem(VolumePal, Shotfire2);
	ChangeVolumeSoundMem(VolumePal, Graze);
	ChangeVolumeSoundMem(VolumePal, ShotHit);
	ChangeVolumeSoundMem(VolumePal, ShotHit2);
	ChangeVolumeSoundMem(VolumePal, EnemyDeath);
	ChangeVolumeSoundMem(VolumePal, EnemyDeath2);
	ChangeVolumeSoundMem(VolumePal, Pause);
	ChangeVolumeSoundMem(VolumePal, Itemget);
	ChangeVolumeSoundMem(VolumePal, PowerUp);
	ChangeVolumeSoundMem(VolumePal, Timeout);
	ChangeVolumeSoundMem(VolumePal, Timeout2);
	ChangeVolumeSoundMem(VolumePal, Extend);
	ChangeVolumeSoundMem(VolumePal, Bomb_Muteki);
	ChangeVolumeSoundMem(VolumePal, Bonus);
	ChangeVolumeSoundMem(VolumePal, GetBomb);
	ChangeVolumeSoundMem(VolumePal, Bomb_DamageFloor);
	ChangeVolumeSoundMem(VolumePal, Bomb_BarrierFloor);
	ChangeVolumeSoundMem(VolumePal, Charge_Up);
	ChangeVolumeSoundMem(VolumePal, Charge_OK);
	ChangeVolumeSoundMem(VolumePal, Charge1);
	ChangeVolumeSoundMem(VolumePal, Charge2);
}

//���ʉ��̉��ʎ擾(0�`100)
int SoundEffect_GetSEVolume() {
	return (int)(100 * (SE_Volume / 255.));
}

//�������ʉ��̒�~
void SoundEffect_LongSEStop() {
	StopSoundMem(Bomb_Muteki);
	SetSoundCurrentTime(0, Bomb_Muteki);
	StopSoundMem(Bomb_DamageFloor);
	SetSoundCurrentTime(0, Bomb_DamageFloor);
	StopSoundMem(Bomb_BarrierFloor);
	SetSoundCurrentTime(0, Bomb_BarrierFloor);
	StopSoundMem(EnemyDeath2);
	SetSoundCurrentTime(0, EnemyDeath2);
}

//�������ʉ��̃|�[�Y
void SoundEffect_LongSEPause() {
	pause_data.Bomb_Muteki.Playing = CheckSoundMem(Bomb_Muteki);	//SE�̍Đ���Ԃ̕ۑ�
	if (pause_data.Bomb_Muteki.Playing) {
		pause_data.Bomb_Muteki.Place = GetSoundCurrentTime(Bomb_Muteki);
		StopSoundMem(Bomb_Muteki);
	}
	pause_data.Bomb_DamageFloor.Playing = CheckSoundMem(Bomb_DamageFloor);	//SE�̍Đ���Ԃ̕ۑ�
	if (pause_data.Bomb_DamageFloor.Playing) {
		pause_data.Bomb_DamageFloor.Place = GetSoundCurrentTime(Bomb_DamageFloor);
		StopSoundMem(Bomb_DamageFloor);
	}
	pause_data.Bomb_BarrierFloor.Playing = CheckSoundMem(Bomb_BarrierFloor);	//SE�̍Đ���Ԃ̕ۑ�
	if (pause_data.Bomb_BarrierFloor.Playing) {
		pause_data.Bomb_BarrierFloor.Place = GetSoundCurrentTime(Bomb_BarrierFloor);
		StopSoundMem(Bomb_BarrierFloor);
	}
	pause_data.EnemyDeath2.Playing = CheckSoundMem(EnemyDeath2);	//SE�̍Đ���Ԃ̕ۑ�
	if (pause_data.EnemyDeath2.Playing) {
		pause_data.EnemyDeath2.Place = GetSoundCurrentTime(EnemyDeath2);
		StopSoundMem(EnemyDeath2);
	}
	pause_data.Charge1.Playing = CheckSoundMem(Charge1);	//SE�̍Đ���Ԃ̕ۑ�
	if (pause_data.Charge1.Playing) {
		pause_data.Charge1.Place = GetSoundCurrentTime(Charge1);
		StopSoundMem(Charge1);
	}
}

//�������ʉ��̃��W���[��
void SoundEffect_LongSEResume() {
	if (pause_data.Bomb_Muteki.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(pause_data.Bomb_Muteki.Place, Bomb_Muteki);
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK, 0);
	}
	if (pause_data.Bomb_DamageFloor.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(pause_data.Bomb_DamageFloor.Place, Bomb_DamageFloor);
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (pause_data.Bomb_BarrierFloor.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(pause_data.Bomb_BarrierFloor.Place, Bomb_BarrierFloor);
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (pause_data.EnemyDeath2.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(pause_data.EnemyDeath2.Place, EnemyDeath2);
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK, FALSE);
	}
	if (pause_data.Charge1.Playing) {//BGM�Đ���Ԃ̕���
		SetSoundCurrentTime(pause_data.Charge1.Place, Charge1);
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK, FALSE);
	}
}

//���d�Ō��ʉ��̍Đ����s����\��������Ƃ��Ɏg�p������ʉ��̍Đ��֐�(1���ʉ�������1�t���[���Ɉ�x�܂ł����Đ��֐����Ă΂�Ȃ��Ȃ�)
void SoundEffect_SafePlay(SE_TYPE type) {
	if (type < 0 || SE_TYPE_NUM <= type)	return;
	if (sE_playData[type] == 0) {//���ʉ����܂��炵�Ă��Ȃ��Ƃ�
		SoundEffect_Play(type);
	}
	sE_playData[type]++;//�炵���񐔂̃J�E���g�A�b�v
}