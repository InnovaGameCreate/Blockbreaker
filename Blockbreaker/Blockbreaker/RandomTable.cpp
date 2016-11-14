//乱数テーブル(最小値以上最大値未満)
//author:Kisogawa(2016/09/20)

#include "RandomTable.h"

//初期化
RandomTable::RandomTable() {
	CreateRandomTable(50000);
}

//乱数表の大きさを指定して初期化
RandomTable::RandomTable(int tableSize) {
	CreateRandomTable(tableSize);
}

RandomTable::~RandomTable() {
	printLog_I(_T("デストラクタが呼ばれました"));
}


//乱数テーブルの作成
void RandomTable::CreateRandomTable(int tableSize) {
	//変数の初期化
	randomTable = NULL;
	TableSize = 0;
	randomTable_MinVal = 0;
	randomTable_maxVal = 0;
	Randomcounter = 0;

	if (tableSize < 1) {
		printLog_E(_T("乱数表が小さすぎて初期化できませんでした(size=%d)"), tableSize);
		return;
	}
	printLog_I(_T("乱数表を生成します(テーブルサイズによっては時間がかかる処理です)"));
	//乱数テーブルの大きさを記録する
	TableSize = tableSize;

	//乱数テーブルのメモリ領域を確保する
	randomTable = new unsigned int[TableSize];

	std::random_device rnd;     // 非決定的な乱数生成器
	//乱数表の初期化
	for (int i = 0; i < TableSize; i++) {
		randomTable[i] = rnd();
	}

	//最小値を記録
	randomTable_MinVal = getMin();
	//最大値を記録
	randomTable_maxVal = getMax();
	printLog_I(_T("乱数表の生成完了(size=%.2fKB)"), (sizeof(unsigned int) * TableSize) / 1024.);
}

//乱数テーブルでの最小値を取得する
unsigned int RandomTable::getMin() {
	if (randomTable == NULL)	return 0;
	unsigned int t = UINT_MAX;
	for (int i = 0; i < TableSize; i++) {
		if (t > randomTable[i])	t = randomTable[i];
	}
	return t;
}

//乱数テーブルでの最大値を取得する
unsigned int RandomTable::getMax() {
	if (randomTable == NULL)	return 0;
	unsigned int t = 0;
	for (int i = 0; i < TableSize; i++) {
		if (t < randomTable[i])	t = randomTable[i];
	}
	return t;
}

//数値の範囲を別の範囲に変換する
double RandomTable::map(long long v, long long sx, long long sn, double dx, double dn) {
	long long a = v - sn;
	double b = dx - dn;
	long long c = sx - sn;
	double d = (a) * (b);
	double e = (d) / (c);
	return e + dn;
}

//乱数表より指定範囲の乱数の取得
double RandomTable::getRand(double min, double max) {
	double r = getRand(min, max, Randomcounter);

	Randomcounter++;				//指定位置の乱数を取得
	Randomcounter %= TableSize;		//乱数の位置カウンタが配列外に出ないように余剰計算を行う


	//乱数表の最大値、最小値、入力値の最小値、最大値より指定範囲の乱数を算出する
	return r;
}

//乱数表より指定範囲の乱数を取得する(乱数テーブルの位置を指定するので、引数がすべて同じ場合は常に同じ値が返ります)
double RandomTable::getRand(double min, double max, int Place) {
	if (randomTable == NULL)	return 0;
	if (TableSize < 1)	return 0;
	if (min == max)	return min;	//最小値と最大値が同じ場合は最小値を返す(乱数する意味無いよね？？)
	if (min > max) {//最小値と最大値が逆の場合、入れ替える
		double t = min;
		min = max;
		max = t;
	}
	Place %= TableSize;
	unsigned int r = randomTable[Place];	//指定位置の乱数を取得

	//乱数表の最大値、最小値、入力値の最小値、最大値より指定範囲の乱数を算出する
	return map(r, randomTable_MinVal, randomTable_maxVal + 1, min, max);
}

//指定した個数の被り無しの乱数を取得する(int型)(取得する値の範囲が大きい場合はメモリをめっちゃ食います)
void RandomTable::getRand_num(int min, int max, int *rand, int ranmd_num) {
	if (rand == NULL)		return;	//引数の値がおかしい
	if (ranmd_num <= 0)		return;	//引数の値がおかしい

	//引数の配列を初期化する
	for (int i = 0; i < ranmd_num; i++) {
		rand[i] = 0;
	}

	if (min > max) {//最小値と最大値が逆の場合、入れ替える
		int t = min;
		min = max;
		max = t;
	}
	//最小値、最大値から生成可能な乱数の個数を算出
	int len = abs(max - min);
	

	//テーブルを作成する
	int *table = new int[len];
	if (table == NULL)	return;		//メモリの確保に失敗
	for (int i = 0; i < len; i++) {
		table[i] = min + i;
	}

	//テーブルのシャッフルを行う
	for (int i = 0; i < min(ranmd_num, len); i++) {
		int place = (int)getRand(0, len);
		if (place >= len) {
			place = len - 1;
			printLog_C(_T("配列オーバーを検知(修復済み)"));
		}
		//入れ替え
		int t = table[place];
		table[place] = table[i];
		table[i] = t;
	}

	//配列に記録する
	for (int i = 0; i < min(ranmd_num, len); i++) {
		rand[i] = table[i];
	}

	delete table;	//メモリ領域の開放
}