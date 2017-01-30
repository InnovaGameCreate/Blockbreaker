#pragma once


class Ranking_Draw : public PCon::Phase_
{
public:
	

	void Init_Draw()			override;	//‰Šú‰»(•`‰æ)
	void Draw()					override;	//•`‰æˆ—
	//void Update()				override;	//ŒvZˆ—
	//void Fin_Draw()				override;	//•`‰æ‚ÌI—¹ˆ—(•`‰æ)
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
		int enable; //FALSE‚Ì‚Æ‚«–³Œø
		rank_data();
	};
	rank_data rank[40];
};

extern Ranking Rank;

