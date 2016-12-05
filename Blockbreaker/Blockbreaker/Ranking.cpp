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
		if (rank[i].enable == FALSE) {
			rank[i].time = clear_time;
			_stprintf(rank[i].name, _T("%s"), clear_name);
			break;
		}
		else{
			if (rank[i].time <= rank[i - 1].time) {
				rank[i].time = clear_time;
				_stprintf(rank[i].name, _T("%s"), clear_name);

				rank_data temp_rank;
				temp_rank = rank[i-1];
				rank[i-1] = rank[i];
				rank[i] = temp_rank;
				break;
			}
			else {

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

	fread(rank, sizeof(rank), 40, fp);

	fclose(fp);
}