#pragma once
class Ranking
{
public:
	Ranking();
	void Add(int time, TCHAR name[]);
	void File();
private:
	int clear_time;	//クリアした時間を保存する変数
	TCHAR clear_name[16]; //クリアした人の名前を保存
	struct rank_data {
		int time;
		TCHAR name[16];
		int enable; //FALSEのとき無効
	};
	rank_data rank[40];
	
};

