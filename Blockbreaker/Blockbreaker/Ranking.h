#pragma once
class Ranking
{
public:
	Ranking();
	void Add(int time, TCHAR name[]);
	void File();
private:
	int clear_time;	//�N���A�������Ԃ�ۑ�����ϐ�
	TCHAR clear_name[16]; //�N���A�����l�̖��O��ۑ�
	struct rank_data {
		int time;
		TCHAR name[16];
		int enable; //FALSE�̂Ƃ�����
	};
	rank_data rank[40];
	
};

