#pragma once


class Ranking_Draw : public PCon::Phase_
{
public:
	

	void Init_Draw()			override;	//初期化(描画)
	void Draw()					override;	//描画処理
	//void Update()				override;	//計算処理
	//void Fin_Draw()				override;	//描画の終了処理(描画)
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
		int enable; //FALSEのとき無効
		rank_data();
	};
	rank_data rank[40];
};

extern Ranking Rank;

