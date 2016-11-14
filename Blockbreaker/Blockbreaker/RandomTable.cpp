//�����e�[�u��(�ŏ��l�ȏ�ő�l����)
//author:Kisogawa(2016/09/20)

#include "RandomTable.h"

//������
RandomTable::RandomTable() {
	CreateRandomTable(50000);
}

//�����\�̑傫�����w�肵�ď�����
RandomTable::RandomTable(int tableSize) {
	CreateRandomTable(tableSize);
}

RandomTable::~RandomTable() {
	printLog_I(_T("�f�X�g���N�^���Ă΂�܂���"));
}


//�����e�[�u���̍쐬
void RandomTable::CreateRandomTable(int tableSize) {
	//�ϐ��̏�����
	randomTable = NULL;
	TableSize = 0;
	randomTable_MinVal = 0;
	randomTable_maxVal = 0;
	Randomcounter = 0;

	if (tableSize < 1) {
		printLog_E(_T("�����\�����������ď������ł��܂���ł���(size=%d)"), tableSize);
		return;
	}
	printLog_I(_T("�����\�𐶐����܂�(�e�[�u���T�C�Y�ɂ���Ă͎��Ԃ������鏈���ł�)"));
	//�����e�[�u���̑傫�����L�^����
	TableSize = tableSize;

	//�����e�[�u���̃������̈���m�ۂ���
	randomTable = new unsigned int[TableSize];

	std::random_device rnd;     // �񌈒�I�ȗ���������
	//�����\�̏�����
	for (int i = 0; i < TableSize; i++) {
		randomTable[i] = rnd();
	}

	//�ŏ��l���L�^
	randomTable_MinVal = getMin();
	//�ő�l���L�^
	randomTable_maxVal = getMax();
	printLog_I(_T("�����\�̐�������(size=%.2fKB)"), (sizeof(unsigned int) * TableSize) / 1024.);
}

//�����e�[�u���ł̍ŏ��l���擾����
unsigned int RandomTable::getMin() {
	if (randomTable == NULL)	return 0;
	unsigned int t = UINT_MAX;
	for (int i = 0; i < TableSize; i++) {
		if (t > randomTable[i])	t = randomTable[i];
	}
	return t;
}

//�����e�[�u���ł̍ő�l���擾����
unsigned int RandomTable::getMax() {
	if (randomTable == NULL)	return 0;
	unsigned int t = 0;
	for (int i = 0; i < TableSize; i++) {
		if (t < randomTable[i])	t = randomTable[i];
	}
	return t;
}

//���l�͈̔͂�ʂ͈̔͂ɕϊ�����
double RandomTable::map(long long v, long long sx, long long sn, double dx, double dn) {
	long long a = v - sn;
	double b = dx - dn;
	long long c = sx - sn;
	double d = (a) * (b);
	double e = (d) / (c);
	return e + dn;
}

//�����\���w��͈̗͂����̎擾
double RandomTable::getRand(double min, double max) {
	double r = getRand(min, max, Randomcounter);

	Randomcounter++;				//�w��ʒu�̗������擾
	Randomcounter %= TableSize;		//�����̈ʒu�J�E���^���z��O�ɏo�Ȃ��悤�ɗ]��v�Z���s��


	//�����\�̍ő�l�A�ŏ��l�A���͒l�̍ŏ��l�A�ő�l���w��͈̗͂������Z�o����
	return r;
}

//�����\���w��͈̗͂������擾����(�����e�[�u���̈ʒu���w�肷��̂ŁA���������ׂē����ꍇ�͏�ɓ����l���Ԃ�܂�)
double RandomTable::getRand(double min, double max, int Place) {
	if (randomTable == NULL)	return 0;
	if (TableSize < 1)	return 0;
	if (min == max)	return min;	//�ŏ��l�ƍő�l�������ꍇ�͍ŏ��l��Ԃ�(��������Ӗ�������ˁH�H)
	if (min > max) {//�ŏ��l�ƍő�l���t�̏ꍇ�A����ւ���
		double t = min;
		min = max;
		max = t;
	}
	Place %= TableSize;
	unsigned int r = randomTable[Place];	//�w��ʒu�̗������擾

	//�����\�̍ő�l�A�ŏ��l�A���͒l�̍ŏ��l�A�ő�l���w��͈̗͂������Z�o����
	return map(r, randomTable_MinVal, randomTable_maxVal + 1, min, max);
}

//�w�肵�����̔�薳���̗������擾����(int�^)(�擾����l�͈̔͂��傫���ꍇ�̓��������߂�����H���܂�)
void RandomTable::getRand_num(int min, int max, int *rand, int ranmd_num) {
	if (rand == NULL)		return;	//�����̒l����������
	if (ranmd_num <= 0)		return;	//�����̒l����������

	//�����̔z�������������
	for (int i = 0; i < ranmd_num; i++) {
		rand[i] = 0;
	}

	if (min > max) {//�ŏ��l�ƍő�l���t�̏ꍇ�A����ւ���
		int t = min;
		min = max;
		max = t;
	}
	//�ŏ��l�A�ő�l���琶���\�ȗ����̌����Z�o
	int len = abs(max - min);
	

	//�e�[�u�����쐬����
	int *table = new int[len];
	if (table == NULL)	return;		//�������̊m�ۂɎ��s
	for (int i = 0; i < len; i++) {
		table[i] = min + i;
	}

	//�e�[�u���̃V���b�t�����s��
	for (int i = 0; i < min(ranmd_num, len); i++) {
		int place = (int)getRand(0, len);
		if (place >= len) {
			place = len - 1;
			printLog_C(_T("�z��I�[�o�[�����m(�C���ς�)"));
		}
		//����ւ�
		int t = table[place];
		table[place] = table[i];
		table[i] = t;
	}

	//�z��ɋL�^����
	for (int i = 0; i < min(ranmd_num, len); i++) {
		rand[i] = table[i];
	}

	delete table;	//�������̈�̊J��
}