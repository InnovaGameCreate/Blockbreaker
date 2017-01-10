#pragma once
//乱数表クラス

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
	const int VERSIONNO = 300;	//バージョン番号
	class RandomTable
	{
	public:
		RandomTable();
		RandomTable(size_t tableSize);
		RandomTable(std::vector<unsigned int> *table);

		double getRand(double min, double max);						//乱数表より指定範囲の乱数の取得
		double getRand(double min, double max, int Place) const;	//乱数表より指定範囲の乱数を取得する(乱数テーブルの位置を指定するので、引数がすべて同じ場合は常に同じ値が返ります)
		void getRand_num(int min, int max, int * rand, int ranmd_num);	//指定した個数の被り無しの乱数を取得する(int型)(取得する値の範囲が大きい場合はメモリをめっちゃ食います)

		size_t getRandomTableSize() const;	//乱数表の大きさを取得する
		std::vector<unsigned int> getRandomTableData() const;	//乱数表本体のコピーを取得
	private:
		int Randomcounter;					//乱数取得の際に使用するカウンター
		std::vector<unsigned int> randomTable;		//乱数表本体
		unsigned int randomTable_MinVal;	//乱数表の最小値
		unsigned int randomTable_maxVal;	//乱数表の最大値

		void CreateRandomTable(size_t tableSize);	//乱数テーブルの作成
		unsigned int getMin();		//乱数テーブルでの最小値を取得する
		unsigned int getMax();		//乱数テーブルでの最大値を取得する


		double map(long long v, long long sx, long long sn, double dx, double dn) const;//数値の範囲を別の範囲に変換する
	};

}