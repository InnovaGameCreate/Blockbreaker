#include "MainFunc.h"
#include "Ranking.h"
#include "errno.h"

static int LoadRanking;//ロード画面
static int LoadRanking2;//ロード画面

Ranking Rank;
TCHAR str[100];
TCHAR str2[100];



/*コンストラクタ*/
Ranking::rank_data::rank_data()
{
	enable = 0;
}

void Ranking::Add(int time, TCHAR name[])
{
	for (int k = 0; k<ARRAY_LENGTH(rank); k++) {
		if (rank[k].enable != TRUE) {
			rank[k].enable = 0;
		}
	}

	/*配列にデータを保存*/
	for (int i = 0; i < ARRAY_LENGTH(rank); i++) {
		if (rank[i].enable == FALSE) {/*スコアが無効のとき入れる*/
			rank[i].time = time;
			_stprintf(rank[i].name, _T("%s"), name);
			rank[i].enable = TRUE;
			break;
		}
		printf("%s\n", rank[i].name);
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
	if ((fp = fopen("ranking", "wb")) == NULL) {
		printf("ファイルオープンエラー\n");

		return;
	}

	fwrite(rank, sizeof(rank), 40, fp);

	fclose(fp);

}


void Ranking::Load() {
	FILE *fp;

	/* ファイルをテキスト読み込みモードでオープン */
	if ((fp = fopen("ranking", "rb")) == NULL) {
		printf("ファイルオープンエラー\n");
		return;
		
	}

	fread(rank, sizeof(rank_data), 40, fp);

	fclose(fp);
}

void Ranking_Draw::Init_Draw() {
	LoadRanking = LoadGraph(_T("Data/image/TopMenu.png"));
	if (LoadRanking == -1) {
		printLog_E(_T("画像ロード失敗(Data/LoadMenu/TopMenu.png)"));
	}
	LoadRanking2 = LoadGraph(_T("Data/image/title.png"));
	if (LoadRanking2 == -1) {
		printLog_E(_T("画像ロード失敗(Data/LoadMenu/title.png)"));
	}
}

void Ranking_Draw::Draw() {
	
	ClearDrawScreen();

	DrawGraph(0, 0, LoadRanking, 0);
	DrawGraph(350, 0, LoadRanking2, 0);

	int number;
	TCHAR rank[20];

	for (int i = 0; i < 10; i++) {

		
		_stprintf_s(rank, _T("%d"), i+1);

		number = Rank.isenable(i);
		
		if (number == TRUE) {
			Font_DrawStringWithShadow(400, 200 + (100 * i), str, GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
			Font_DrawStringWithShadow(800, 200 + (100 * i), str2, GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
			Font_DrawStringWithShadow(300, 200 + (100 * i), rank, GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
		}
	}

}


int Ranking::isenable(int num) {
	_stprintf(str, _T("%s"), rank[num].name);
	_stprintf_s(str2, _T("%.2f"), rank[num].time / 100.0);
	return rank[num].enable;
}