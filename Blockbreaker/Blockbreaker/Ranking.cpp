#include "MainFunc.h"
#include "Ranking.h"
#include "errno.h"

static int LoadRanking;//���[�h���
static int LoadRanking2;//���[�h���

Ranking Rank;
TCHAR str[100];
TCHAR str2[100];



/*�R���X�g���N�^*/
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

	/*�z��Ƀf�[�^��ۑ�*/
	for (int i = 0; i < ARRAY_LENGTH(rank); i++) {
		if (rank[i].enable == FALSE) {/*�X�R�A�������̂Ƃ������*/
			rank[i].time = time;
			_stprintf(rank[i].name, _T("%s"), name);
			rank[i].enable = TRUE;
			break;
		}
		printf("%s\n", rank[i].name);
	}
	
	//�\�[�g
	for (int i = 0; i < ARRAY_LENGTH(rank) - 1; i++) {
		for (int j = ARRAY_LENGTH(rank) - 1; j > i; j--) {
			if ((rank[j - 1].time > rank[j].time && rank[j].enable == TRUE && rank[j - 1].enable == TRUE) ||
				(rank[j].enable == TRUE && rank[j - 1].enable == FALSE)) {  /* �O�̗v�f�̕����傫�������� */
				rank_data temp = rank[j];        /* �������� */
				rank[j] = rank[j - 1];
				rank[j - 1] = temp;
			}
		}
	}


	FILE *fp;
	/* �t�@�C�����e�L�X�g�������݃��[�h�ŃI�[�v�� */
	if ((fp = fopen("ranking", "wb")) == NULL) {
		printf("�t�@�C���I�[�v���G���[\n");

		return;
	}

	fwrite(rank, sizeof(rank), 40, fp);

	fclose(fp);

}


void Ranking::Load() {
	FILE *fp;

	/* �t�@�C�����e�L�X�g�ǂݍ��݃��[�h�ŃI�[�v�� */
	if ((fp = fopen("ranking", "rb")) == NULL) {
		printf("�t�@�C���I�[�v���G���[\n");
		return;
		
	}

	fread(rank, sizeof(rank_data), 40, fp);

	fclose(fp);
}

void Ranking_Draw::Init_Draw() {
	LoadRanking = LoadGraph(_T("Data/image/TopMenu.png"));
	if (LoadRanking == -1) {
		printLog_E(_T("�摜���[�h���s(Data/LoadMenu/TopMenu.png)"));
	}
	LoadRanking2 = LoadGraph(_T("Data/image/title.png"));
	if (LoadRanking2 == -1) {
		printLog_E(_T("�摜���[�h���s(Data/LoadMenu/title.png)"));
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