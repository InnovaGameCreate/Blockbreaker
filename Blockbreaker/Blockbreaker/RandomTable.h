#pragma once
class RandomTable
{
public:
	RandomTable();
	RandomTable(int tableSize);
	~RandomTable();
	double getRand(double min, double max);	//乱数表より指定範囲の乱数の取得
private:
	int Randomcounter;					//乱数取得の際に使用するカウンター
	unsigned int *randomTable;			//乱数表
	unsigned int randomTable_MinVal;	//乱数表の最小値
	unsigned int randomTable_maxVal;	//乱数表の最大値
	int TableSize;	//乱数テーブルの大きさ

	void CreateRandomTable(int tableSize);	//乱数テーブルの作成
	unsigned int getMin();		//乱数テーブルでの最小値を取得する
	unsigned int getMax();		//乱数テーブルでの最大値を取得する
	double map(long long v, long long sx, long long sn, double dx, double dn);//数値の範囲を別の範囲に変換する
};

