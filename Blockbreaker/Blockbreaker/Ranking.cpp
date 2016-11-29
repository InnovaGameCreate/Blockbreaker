#include "MainFunc.h"
#include "Ranking.h"


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
		else {
			
		};
	}


}
