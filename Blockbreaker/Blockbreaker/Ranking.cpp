#include "MainFunc.h"
#include "Ranking.h"
#include "errno.h"


Ranking::Ranking()
{
	clear_time = 0;

}
void Ranking::Add(int time, TCHAR name[])
{
	
	clear_time = time;
	_stprintf(clear_name, _T("%s"), name);

	/*配列にデータを保存*/
	for (int i = 0; i < ARRAY_LENGTH(rank); i++) {
		if (rank[i].enable == FALSE) {/*スコアが無効のとき入れる*/
			rank[i].time = clear_time;
			_stprintf(rank[i].name, _T("%s"), clear_name);
			rank[i].enable = TRUE;
			break;
		}
	}
	
	//ソート
	for (int i = 0; i < ARRAY_LENGTH(rank) - 1; i++) {
		for (int j = ARRAY_LENGTH(rank) - 1; j > i; j--) {
			if ((rank[j - 1].time > rank[j].time && rank[j].enable == TRUE && rank[j - 1].enable == TRUE) ||
				(rank[j].enable == TRUE && rank[j - 1].enable == FALSE)) {  /* 前の要素の方が大きかったら */
				rank_data temp = rank[j];        /* 交換する */
				rank[j] = rank[j - 1];
				rank[j - 1] = temp;
			}
		}
	}


	FILE *fp;
	/* ファイルをテキスト書き込みモードでオープン */
	if ((fp = fopen("ranking.a", "w")) == NULL) {
		printf("ファイルオープンエラー\n");
		printf("%d", errno);

		return;
	}

	fwrite(rank, sizeof(rank), 40, fp);

	fclose(fp);


	

}

void Ranking::File() {
	FILE *fp;

	/* ファイルをテキスト読み込みモードでオープン */
	if ((fp = fopen("ranking.a", "rb")) == NULL) {
		printf("ファイルオープンエラー\n");
		return;
		
	}

	fread(rank, sizeof(rank_data), 40, fp);

	fclose(fp);
}