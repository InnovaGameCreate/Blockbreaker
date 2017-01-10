#pragma once
//�����\�N���X

#ifdef _DEBUG
	#ifdef _WIN64
		#pragma comment(lib, "RandomTablex64_d.lib")
	#else
		#pragma comment(lib, "RandomTablex86_d.lib")
	#endif // WIN64
#else
	#ifdef _WIN64
		#pragma comment(lib, "RandomTablex64.lib")
	#else
		#pragma comment(lib, "RandomTablex86.lib")
	#endif // WIN64
#endif // _DEBUG

#include <random>
#include <vector>

namespace RandTable {
	const int VERSIONNO = 300;	//�o�[�W�����ԍ�
	class RandomTable
	{
	public:
		RandomTable();
		RandomTable(size_t tableSize);
		RandomTable(std::vector<unsigned int> *table);

		double getRand(double min, double max);						//�����\���w��͈̗͂����̎擾
		double getRand(double min, double max, int Place) const;	//�����\���w��͈̗͂������擾����(�����e�[�u���̈ʒu���w�肷��̂ŁA���������ׂē����ꍇ�͏�ɓ����l���Ԃ�܂�)
		void getRand_num(int min, int max, int * rand, int ranmd_num);	//�w�肵�����̔�薳���̗������擾����(int�^)(�擾����l�͈̔͂��傫���ꍇ�̓��������߂�����H���܂�)

		size_t getRandomTableSize() const;	//�����\�̑傫�����擾����
		std::vector<unsigned int> getRandomTableData() const;	//�����\�{�̂̃R�s�[���擾
	private:
		int Randomcounter;					//�����擾�̍ۂɎg�p����J�E���^�[
		std::vector<unsigned int> randomTable;		//�����\�{��
		unsigned int randomTable_MinVal;	//�����\�̍ŏ��l
		unsigned int randomTable_maxVal;	//�����\�̍ő�l

		void CreateRandomTable(size_t tableSize);	//�����e�[�u���̍쐬
		unsigned int getMin();		//�����e�[�u���ł̍ŏ��l���擾����
		unsigned int getMax();		//�����e�[�u���ł̍ő�l���擾����


		double map(long long v, long long sx, long long sn, double dx, double dn) const;//���l�͈̔͂�ʂ͈̔͂ɕϊ�����
	};

}