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

	/*�z��Ƀf�[�^��ۑ�*/
	for (int i = 0; i < ARRAY_LENGTH(rank); i++) {
		if (rank[i].enable == FALSE) {/*�X�R�A�������̂Ƃ������*/
			rank[i].time = clear_time;
			_stprintf(rank[i].name, _T("%s"), clear_name);
			rank[i].enable = TRUE;
			break;
		}
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
	if ((fp = fopen("ranking.a", "w")) == NULL) {
		printf("�t�@�C���I�[�v���G���[\n");
		printf("%d", errno);

		return;
	}

	fwrite(rank, sizeof(rank), 40, fp);

	fclose(fp);


	

}

void Ranking::File() {
	FILE *fp;

	/* �t�@�C�����e�L�X�g�ǂݍ��݃��[�h�ŃI�[�v�� */
	if ((fp = fopen("ranking.a", "rb")) == NULL) {
		printf("�t�@�C���I�[�v���G���[\n");
		return;
		
	}

	fread(rank, sizeof(rank_data), 40, fp);

	fclose(fp);
}