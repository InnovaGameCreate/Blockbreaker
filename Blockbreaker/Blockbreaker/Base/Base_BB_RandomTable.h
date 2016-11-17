#pragma once
class RandomTable
{
public:
	RandomTable();
	RandomTable(int tableSize);
	~RandomTable();
	double getRand(double min, double max);				//�����\���w��͈̗͂����̎擾
	double getRand(double min, double max, int Place);	//�����\���w��͈̗͂������擾����(�����e�[�u���̈ʒu���w�肷��̂ŁA���������ׂē����ꍇ�͏�ɓ����l���Ԃ�܂�)
	void getRand_num(int min, int max, int * rand, int ranmd_num);	//�w�肵�����̔�薳���̗������擾����(int�^)(�擾����l�͈̔͂��傫���ꍇ�̓��������߂�����H���܂�)
private:
	int Randomcounter;					//�����擾�̍ۂɎg�p����J�E���^�[
	unsigned int *randomTable;			//�����\
	unsigned int randomTable_MinVal;	//�����\�̍ŏ��l
	unsigned int randomTable_maxVal;	//�����\�̍ő�l
	int TableSize;	//�����e�[�u���̑傫��

	void CreateRandomTable(int tableSize);	//�����e�[�u���̍쐬
	unsigned int getMin();		//�����e�[�u���ł̍ŏ��l���擾����
	unsigned int getMax();		//�����e�[�u���ł̍ő�l���擾����
	double map(long long v, long long sx, long long sn, double dx, double dn);//���l�͈̔͂�ʂ͈̔͂ɕϊ�����
};

