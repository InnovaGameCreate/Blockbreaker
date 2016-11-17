#pragma once
class RandomTable
{
public:
	RandomTable();
	RandomTable(int tableSize);
	~RandomTable();
	double getRand(double min, double max);				//乱数表より指定範囲の乱数の取得
	double getRand(double min, double max, int Place);	//乱数表より指定範囲の乱数を取得する(乱数テーブルの位置を指定するので、引数がすべて同じ場合は常に同じ値が返ります)
	void getRand_num(int min, int max, int * rand, int ranmd_num);	//指定した個数の被り無しの乱数を取得する(int型)(取得する値の範囲が大きい場合はメモリをめっちゃ食います)
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

