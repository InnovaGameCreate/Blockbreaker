#pragma once


class Ranking_Draw : public PCon::Phase_
{
public:
	

	void Init_Draw()			override;	//������(�`��)
	void Draw()					override;	//�`�揈��
	//void Update()				override;	//�v�Z����
	//void Fin_Draw()				override;	//�`��̏I������(�`��)
private:
	
};

class Ranking
{
public:
	void Add(int time, TCHAR name[]);
	void Load();
	int isenable(int num);
private:
	struct rank_data {
		int time;
		TCHAR name[16];
		int enable; //FALSE�̂Ƃ�����
		rank_data();
	};
	rank_data rank[40];
};

extern Ranking Rank;

