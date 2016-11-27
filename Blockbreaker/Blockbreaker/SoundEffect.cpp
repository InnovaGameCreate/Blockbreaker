//効果音関係
#include "MainFunc.h"

//効果音の状態
struct SE_STATE {
	int Playing;	//再生中かどうか
	int Place;		//効果音の再生位置
};

//効果音の状態
struct SE_DATA {
	struct SE_STATE Bomb_Muteki;
	struct SE_STATE Bomb_DamageFloor;
	struct SE_STATE Bomb_BarrierFloor;
	struct SE_STATE EnemyDeath2;
	struct SE_STATE Charge1;
};



static int ButtonSelect;	//項目の選択肢を移動する時の音
static int ButtonDecision;	//項目を決定した時の音
static int ButtonCancel;	//項目をキャンセルした時の音
static int OwnBarrier;		//自分がバリアを発動したときの音
static int OwnDeath;		//自分が死亡した時の音
static int Bulletfire1;		//敵が弾幕を発射したときの音1(連射)
static int Bulletfire2;		//敵が弾幕を発射したときの音2
static int Bulletfire3;		//敵が弾幕を発射したときの音3
static int Bulletfire4;		//敵が弾幕を発射したときの音4
static int Bulletfire5;		//敵が弾幕を発射したときの音5
static int Bulletfire6;		//敵が弾幕を発射したときの音6
static int Bulletfire7;		//敵が弾幕を発射したときの音7
static int Shotfire;		//自機がショットを発射したときの音
static int Shotfire2;		//自機がショットを発射したときの音2
static int Graze;			//自機がかすりを入れたときの音
static int ShotHit;			//自機のショットが敵に当たったときの音
static int ShotHit2;		//自機のショットが敵に当たったときの音2
static int EnemyDeath;		//敵が死亡したときの音
static int EnemyDeath2;		//敵が死亡したときの音2
static int Pause;			//ボーズボタン
static int Itemget;			//アイテムを取得したときの音
static int PowerUp;			//パワーアップしたときの
static int Timeout;			//制限時間の音
static int Timeout2;		//制限時間の音2
static int Extend;			//1アップ時
static int Bomb_Muteki;		//無敵ボムの音
static int Bonus;			//ボーナス
static int GetBomb;			//ボム取得
static int Bomb_DamageFloor;//ダメージ床ボムの音
static int Bomb_BarrierFloor;//バリア床ボムの音
static int Charge_Up;		//チャージ攻撃の段階UPの音
static int Charge_OK;		//チャージ攻撃のリキャスト完了の音
static int Charge1;			//チャージ攻撃1の効果音
static int Charge2;			//チャージ攻撃2の効果音
static int Smallexplosion;	//小爆発

static struct SE_DATA data;				//効果音の状態
static struct SE_DATA Save_data;		//効果音の状態
static struct SE_DATA pause_data;		//効果音の状態(ポーズ中)

										//セーブを一度でもしたかどうかのフラグ
static int Saved;

//音量0～255
static int BGM_Volume;//管理のみここ！
static int SE_Volume;

//効果音が再生されたかどうかのフラグ(一応カウントアップする)
static unsigned int sE_playData[SE_TYPE_NUM];





//初期化
void SoundEffect_init() {

	data.Bomb_Muteki.Playing = 0;
	pause_data.Bomb_Muteki.Playing = 0;
	data.Bomb_DamageFloor.Playing = 0;
	pause_data.Bomb_DamageFloor.Playing = 0;
	data.Bomb_BarrierFloor.Playing = 0;
	pause_data.Bomb_BarrierFloor.Playing = 0;
	data.EnemyDeath2.Playing = 0;
	pause_data.EnemyDeath2.Playing = 0;
	data.Charge1.Playing = 0;;
	pause_data.Charge1.Playing = 0;;

	Saved = 0;
	BGM_Volume = 255;
	SE_Volume = 255;

	ButtonSelect = LoadSoundMemBase(_T("Data/SE/ChangeSelect.wav"), 1);
	if (ButtonSelect == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/ChangeSelect.wav)"));
	}
	ButtonDecision = LoadSoundMemBase(_T("Data/SE/DecisionSelect.wav"), 1);
	if (ButtonDecision == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/DecisionSelect.wav)"));
	}
	ButtonCancel = LoadSoundMemBase(_T("Data/SE/ButtonCancel.wav"), 1);
	if (ButtonCancel == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/ButtonCancel.wav)"));
	}
	OwnBarrier = LoadSoundMemBase(_T("Data/SE/OwnBarrier.wav"), 1);
	if (OwnBarrier == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/OwnBarrier.wav)"));
	}
	OwnDeath = LoadSoundMemBase(_T("Data/SE/OwnDeath.wav"), 1);
	if (OwnDeath == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/OwnDeath.wav)"));
	}
	Bulletfire1 = LoadSoundMemBase(_T("Data/SE/Bulletfire1.wav"), 1);
	if (Bulletfire1 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire1.wav)"));
	}
	Bulletfire2 = LoadSoundMemBase(_T("Data/SE/Bulletfire2.wav"), 1);
	if (Bulletfire2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire2.wav)"));
	}
	Bulletfire3 = LoadSoundMemBase(_T("Data/SE/Bulletfire3.wav"), 1);
	if (Bulletfire3 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire3.wav)"));
	}
	Bulletfire4 = LoadSoundMemBase(_T("Data/SE/Bulletfire4.wav"), 1);
	if (Bulletfire4 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire4.wav)"));
	}
	Bulletfire5 = LoadSoundMemBase(_T("Data/SE/Bulletfire5.wav"), 1);
	if (Bulletfire5 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire5.wav)"));
	}
	Bulletfire6 = LoadSoundMemBase(_T("Data/SE/Bulletfire6.wav"), 1);
	if (Bulletfire6 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire6.wav)"));
	}
	Bulletfire7 = LoadSoundMemBase(_T("Data/SE/Bulletfire7.wav"), 1);
	if (Bulletfire7 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bulletfire7.wav)"));
	}
	Shotfire = LoadSoundMemBase(_T("Data/SE/Shotfire.wav"), 1);
	if (Shotfire == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Shotfire.wav)"));
	}
	Shotfire2 = LoadSoundMemBase(_T("Data/SE/Shotfire2.wav"), 1);
	if (Shotfire2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Shotfire2.wav)"));
	}
	Graze = LoadSoundMemBase(_T("Data/SE/Graze.wav"), 1);
	if (Graze == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Graze.wav)"));
	}
	ShotHit = LoadSoundMemBase(_T("Data/SE/ShotHit.wav"), 1);
	if (ShotHit == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/ShotHit.wav)"));
	}
	ShotHit2 = LoadSoundMemBase(_T("Data/SE/ShotHit2.wav"), 1);
	if (ShotHit2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/ShotHit2.wav)"));
	}
	EnemyDeath = LoadSoundMemBase(_T("Data/SE/EnemyDeath.wav"), 1);
	if (EnemyDeath == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/EnemyDeath.wav)"));
	}
	EnemyDeath2 = LoadSoundMemBase(_T("Data/SE/EnemyDeath2.wav"), 1);
	if (EnemyDeath2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/EnemyDeath2.wav)"));
	}
	Pause = LoadSoundMemBase(_T("Data/SE/Pause.wav"), 1);
	if (Pause == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Pause.wav)"));
	}
	Itemget = LoadSoundMemBase(_T("Data/SE/Itemget.wav"), 1);
	if (Itemget == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Itemget.wav)"));
	}
	PowerUp = LoadSoundMemBase(_T("Data/SE/PowerUp.wav"), 1);
	if (PowerUp == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/PowerUp.wav)"));
	}
	Timeout = LoadSoundMemBase(_T("Data/SE/Timeout.wav"), 1);
	if (Timeout == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Timeout.wav)"));
	}
	Timeout2 = LoadSoundMemBase(_T("Data/SE/Timeout2.wav"), 1);
	if (Timeout2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Timeout2.wav)"));
	}
	Extend = LoadSoundMemBase(_T("Data/SE/Extend.wav"), 1);
	if (Extend == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Extend.wav)"));
	}
	Bomb_Muteki = LoadSoundMemBase(_T("Data/SE/BombMUTEKI.wav"), 1);
	if (Bomb_Muteki == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/BombMUTEKI.wav)"));
	}
	Bonus = LoadSoundMemBase(_T("Data/SE/Bonus.wav"), 1);
	if (Bonus == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Bonus.wav)"));
	}
	GetBomb = LoadSoundMemBase(_T("Data/SE/GetBomb.wav"), 1);
	if (GetBomb == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/GetBomb.wav)"));
	}
	Bomb_DamageFloor = LoadSoundMemBase(_T("Data/SE/BombDANAMEFLOOR.wav"), 1);
	if (Bomb_DamageFloor == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/BombDANAMEFLOOR.wav)"));
	}
	Bomb_BarrierFloor = LoadSoundMemBase(_T("Data/SE/BombBARRIER.wav"), 1);
	if (Bomb_BarrierFloor == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/BombBARRIER.wav)"));
	}
	Charge_Up = LoadSoundMemBase(_T("Data/SE/ChargeUp.wav"), 1);
	if (Charge_Up == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/ChargeUp.wav)"));
	}
	Charge_OK = LoadSoundMemBase(_T("Data/SE/ChargeOK.wav"), 1);
	if (Charge_OK == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/ChargeOK.wav)"));
	}
	Charge1 = LoadSoundMemBase(_T("Data/SE/Charge1.wav"), 10);
	if (Charge1 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Charge1.wav)"));
	}
	Charge2 = LoadSoundMemBase(_T("Data/SE/Charge2.wav"), 10);
	if (Charge2 == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/Charge2.wav)"));
	}
	Smallexplosion = LoadSoundMemBase(_T("Data/SE/small_explosion1.wav"), 10);
	if (Smallexplosion == -1) {
		Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("SEのロードに失敗(Data/SE/small_explosion1.wav)"));
	}
	
}

//効果音の計算処理ループ(効果音を鳴らすよりも前に呼ぶこと)
void SoundEffect_update() {
	for (int i = 0; i < SE_TYPE_NUM; i++) {
		sE_playData[i] = 0;
	}

}

//効果音の再生
void SoundEffect_Play(SE_TYPE type) {
	switch (type)
	{
	case SE_TYPE_ChangeSelect:
		PlaySoundMem(ButtonSelect, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_DecisionSelect:
		PlaySoundMem(ButtonDecision, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ButtonCancel:
		PlaySoundMem(ButtonCancel, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_OwnBarrier:
		PlaySoundMem(OwnBarrier, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_OwnDeath:
		PlaySoundMem(OwnDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire1:
		PlaySoundMem(Bulletfire1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire2:
		PlaySoundMem(Bulletfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire3:
		PlaySoundMem(Bulletfire3, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire4:
		PlaySoundMem(Bulletfire4, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire5:
		PlaySoundMem(Bulletfire5, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire6:
		PlaySoundMem(Bulletfire6, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire7:
		PlaySoundMem(Bulletfire7, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire:
		PlaySoundMem(Shotfire, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire2:
		PlaySoundMem(Shotfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Graze:
		PlaySoundMem(Graze, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit:
		if (CheckSoundMem(ShotHit) == 0)	PlaySoundMem(ShotHit, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit2:
		PlaySoundMem(ShotHit2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath:
		PlaySoundMem(EnemyDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath2:
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Pause:
		PlaySoundMem(Pause, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Itemget:
		PlaySoundMem(Itemget, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_PowerUp:
		PlaySoundMem(PowerUp, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout:
		PlaySoundMem(Timeout, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout2:
		PlaySoundMem(Timeout2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Extend:
		PlaySoundMem(Extend, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_Muteki:
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bonus:
		PlaySoundMem(Bonus, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_GetBomb:
		PlaySoundMem(GetBomb, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_DamageFloor:
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_BarrierFloor:
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeUP:
		PlaySoundMem(Charge_Up, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeOK:
		PlaySoundMem(Charge_OK, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge1:
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge2:
		PlaySoundMem(Charge2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Smallexplosion:
		PlaySoundMem(Smallexplosion, DX_PLAYTYPE_BACK);
		break;
	}
}

//効果音の再生(位置で音量が変わるやつ)(今は機能しない)
void SoundEffect_PlayPlace(SE_TYPE type, double plaxeX, double placeY) {
	switch (type)
	{
	case SE_TYPE_ChangeSelect:
		PlaySoundMem(ButtonSelect, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_DecisionSelect:
		PlaySoundMem(ButtonDecision, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ButtonCancel:
		PlaySoundMem(ButtonCancel, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_OwnBarrier:
		PlaySoundMem(OwnBarrier, DX_PLAYTYPE_BACK);
		break;
	case  SE_TYPE_OwnDeath:
		PlaySoundMem(OwnDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire1:
		PlaySoundMem(Bulletfire1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire2:
		PlaySoundMem(Bulletfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire3:
		PlaySoundMem(Bulletfire3, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire4:
		PlaySoundMem(Bulletfire4, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire5:
		PlaySoundMem(Bulletfire5, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire6:
		PlaySoundMem(Bulletfire6, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bulletfire7:
		PlaySoundMem(Bulletfire7, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire:
		PlaySoundMem(Shotfire, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Shotfire2:
		PlaySoundMem(Shotfire2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Graze:
		PlaySoundMem(Graze, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit:
		if (CheckSoundMem(ShotHit) == 0)	PlaySoundMem(ShotHit, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ShotHit2:
		PlaySoundMem(ShotHit2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath:
		PlaySoundMem(EnemyDeath, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_EnemyDeath2:
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Pause:
		PlaySoundMem(Pause, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Itemget:
		PlaySoundMem(Itemget, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_PowerUp:
		PlaySoundMem(PowerUp, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout:
		PlaySoundMem(Timeout, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Timeout2:
		PlaySoundMem(Timeout2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Extend:
		PlaySoundMem(Extend, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_Muteki:
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Bonus:
		PlaySoundMem(Bonus, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_GetBomb:
		PlaySoundMem(GetBomb, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_DamageFloor:
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_bomb_BarrierFloor:
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeUP:
		PlaySoundMem(Charge_Up, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_ChargeOK:
		PlaySoundMem(Charge_OK, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge1:
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Charge2:
		PlaySoundMem(Charge2, DX_PLAYTYPE_BACK);
		break;
	case SE_TYPE_Smallexplosion:
		PlaySoundMem(Smallexplosion, DX_PLAYTYPE_BACK);
		break;
	}
}

//効果音の状態の保存
void SoundEffect_Save() {
	Save_data.Bomb_Muteki.Playing = CheckSoundMem(Bomb_Muteki);	//SEの再生状態の保存
	if (Save_data.Bomb_Muteki.Playing) {
		Save_data.Bomb_Muteki.Place = GetSoundCurrentTime(Bomb_Muteki);
	}
	Save_data.Bomb_DamageFloor.Playing = CheckSoundMem(Bomb_DamageFloor);	//SEの再生状態の保存
	if (Save_data.Bomb_DamageFloor.Playing) {
		Save_data.Bomb_DamageFloor.Place = GetSoundCurrentTime(Bomb_DamageFloor);
	}
	Save_data.Bomb_BarrierFloor.Playing = CheckSoundMem(Bomb_BarrierFloor);	//SEの再生状態の保存
	if (Save_data.Bomb_BarrierFloor.Playing) {
		Save_data.Bomb_BarrierFloor.Place = GetSoundCurrentTime(Bomb_BarrierFloor);
	}
	Save_data.EnemyDeath2.Playing = CheckSoundMem(EnemyDeath2);	//SEの再生状態の保存
	if (Save_data.EnemyDeath2.Playing) {
		Save_data.EnemyDeath2.Place = GetSoundCurrentTime(EnemyDeath2);
	}
	Save_data.Charge1.Playing = CheckSoundMem(Charge1);	//SEの再生状態の保存
	if (Save_data.Charge1.Playing) {
		Save_data.Charge1.Place = GetSoundCurrentTime(Charge1);
	}
	Saved = 1;
}

//効果音の状態の復元
void SoundEffect_Load() {
	if (Saved == 0)	return;
	if (Save_data.Bomb_Muteki.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(Save_data.Bomb_Muteki.Place, Bomb_Muteki);
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.Bomb_DamageFloor.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(Save_data.Bomb_DamageFloor.Place, Bomb_DamageFloor);
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.Bomb_BarrierFloor.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(Save_data.Bomb_BarrierFloor.Place, Bomb_BarrierFloor);
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.EnemyDeath2.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(Save_data.EnemyDeath2.Place, EnemyDeath2);
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK, 0);
	}
	if (Save_data.Charge1.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(Save_data.Charge1.Place, Charge1);
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK, 0);
	}
}

//効果音をすべてポーズする
void SoundEffect_AllPause() {
	StopSoundMem(ButtonSelect);
	StopSoundMem(ButtonDecision);
	StopSoundMem(ButtonCancel);
	StopSoundMem(OwnBarrier);
	StopSoundMem(OwnDeath);
	StopSoundMem(Bulletfire1);
	StopSoundMem(Bulletfire2);
	StopSoundMem(Bulletfire3);
	StopSoundMem(Bulletfire4);
	StopSoundMem(Bulletfire5);
	StopSoundMem(Bulletfire6);
	StopSoundMem(Bulletfire7);
	StopSoundMem(Shotfire);
	StopSoundMem(Shotfire2);
	StopSoundMem(Graze);
	StopSoundMem(ShotHit);
	StopSoundMem(ShotHit2);
	StopSoundMem(EnemyDeath);
	StopSoundMem(EnemyDeath2);
	StopSoundMem(Pause);
	StopSoundMem(Itemget);
	StopSoundMem(PowerUp);
	StopSoundMem(Timeout);
	StopSoundMem(Timeout2);
	StopSoundMem(Extend);
	StopSoundMem(Bomb_Muteki);
	StopSoundMem(Bonus);
	StopSoundMem(GetBomb);
	StopSoundMem(Bomb_DamageFloor);
	StopSoundMem(Bomb_BarrierFloor);
	StopSoundMem(Charge_Up);
	StopSoundMem(Charge_OK);
	StopSoundMem(Charge1);
	StopSoundMem(Charge2);
	StopSoundMem(Smallexplosion);
}

//効果音の音量をすべて変更する(0～100)
void SoundEffect_SetSEVolume(int Volume) {
	int VolumePal = (int)(255 * (Volume / 100.));
	SE_Volume = VolumePal;
	ChangeVolumeSoundMem(VolumePal, ButtonSelect);
	ChangeVolumeSoundMem(VolumePal, ButtonDecision);
	ChangeVolumeSoundMem(VolumePal, ButtonCancel);
	ChangeVolumeSoundMem(VolumePal, OwnBarrier);
	ChangeVolumeSoundMem(VolumePal, OwnDeath);
	ChangeVolumeSoundMem(VolumePal, Bulletfire1);
	ChangeVolumeSoundMem(VolumePal, Bulletfire2);
	ChangeVolumeSoundMem(VolumePal, Bulletfire3);
	ChangeVolumeSoundMem(VolumePal, Bulletfire4);
	ChangeVolumeSoundMem(VolumePal, Bulletfire5);
	ChangeVolumeSoundMem(VolumePal, Bulletfire6);
	ChangeVolumeSoundMem(VolumePal, Bulletfire7);
	ChangeVolumeSoundMem(VolumePal, Shotfire);
	ChangeVolumeSoundMem(VolumePal, Shotfire2);
	ChangeVolumeSoundMem(VolumePal, Graze);
	ChangeVolumeSoundMem(VolumePal, ShotHit);
	ChangeVolumeSoundMem(VolumePal, ShotHit2);
	ChangeVolumeSoundMem(VolumePal, EnemyDeath);
	ChangeVolumeSoundMem(VolumePal, EnemyDeath2);
	ChangeVolumeSoundMem(VolumePal, Pause);
	ChangeVolumeSoundMem(VolumePal, Itemget);
	ChangeVolumeSoundMem(VolumePal, PowerUp);
	ChangeVolumeSoundMem(VolumePal, Timeout);
	ChangeVolumeSoundMem(VolumePal, Timeout2);
	ChangeVolumeSoundMem(VolumePal, Extend);
	ChangeVolumeSoundMem(VolumePal, Bomb_Muteki);
	ChangeVolumeSoundMem(VolumePal, Bonus);
	ChangeVolumeSoundMem(VolumePal, GetBomb);
	ChangeVolumeSoundMem(VolumePal, Bomb_DamageFloor);
	ChangeVolumeSoundMem(VolumePal, Bomb_BarrierFloor);
	ChangeVolumeSoundMem(VolumePal, Charge_Up);
	ChangeVolumeSoundMem(VolumePal, Charge_OK);
	ChangeVolumeSoundMem(VolumePal, Charge1);
	ChangeVolumeSoundMem(VolumePal, Charge2);
	ChangeVolumeSoundMem(VolumePal, Smallexplosion);
}

//効果音の音量取得(0～100)
int SoundEffect_GetSEVolume() {
	return (int)(100 * (SE_Volume / 255.));
}

//長い効果音の停止
void SoundEffect_LongSEStop() {
	StopSoundMem(Bomb_Muteki);
	SetSoundCurrentTime(0, Bomb_Muteki);
	StopSoundMem(Bomb_DamageFloor);
	SetSoundCurrentTime(0, Bomb_DamageFloor);
	StopSoundMem(Bomb_BarrierFloor);
	SetSoundCurrentTime(0, Bomb_BarrierFloor);
	StopSoundMem(EnemyDeath2);
	SetSoundCurrentTime(0, EnemyDeath2);
}

//長い効果音のポーズ
void SoundEffect_LongSEPause() {
	pause_data.Bomb_Muteki.Playing = CheckSoundMem(Bomb_Muteki);	//SEの再生状態の保存
	if (pause_data.Bomb_Muteki.Playing) {
		pause_data.Bomb_Muteki.Place = GetSoundCurrentTime(Bomb_Muteki);
		StopSoundMem(Bomb_Muteki);
	}
	pause_data.Bomb_DamageFloor.Playing = CheckSoundMem(Bomb_DamageFloor);	//SEの再生状態の保存
	if (pause_data.Bomb_DamageFloor.Playing) {
		pause_data.Bomb_DamageFloor.Place = GetSoundCurrentTime(Bomb_DamageFloor);
		StopSoundMem(Bomb_DamageFloor);
	}
	pause_data.Bomb_BarrierFloor.Playing = CheckSoundMem(Bomb_BarrierFloor);	//SEの再生状態の保存
	if (pause_data.Bomb_BarrierFloor.Playing) {
		pause_data.Bomb_BarrierFloor.Place = GetSoundCurrentTime(Bomb_BarrierFloor);
		StopSoundMem(Bomb_BarrierFloor);
	}
	pause_data.EnemyDeath2.Playing = CheckSoundMem(EnemyDeath2);	//SEの再生状態の保存
	if (pause_data.EnemyDeath2.Playing) {
		pause_data.EnemyDeath2.Place = GetSoundCurrentTime(EnemyDeath2);
		StopSoundMem(EnemyDeath2);
	}
	pause_data.Charge1.Playing = CheckSoundMem(Charge1);	//SEの再生状態の保存
	if (pause_data.Charge1.Playing) {
		pause_data.Charge1.Place = GetSoundCurrentTime(Charge1);
		StopSoundMem(Charge1);
	}
}

//長い効果音のレジューム
void SoundEffect_LongSEResume() {
	if (pause_data.Bomb_Muteki.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(pause_data.Bomb_Muteki.Place, Bomb_Muteki);
		PlaySoundMem(Bomb_Muteki, DX_PLAYTYPE_BACK, 0);
	}
	if (pause_data.Bomb_DamageFloor.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(pause_data.Bomb_DamageFloor.Place, Bomb_DamageFloor);
		PlaySoundMem(Bomb_DamageFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (pause_data.Bomb_BarrierFloor.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(pause_data.Bomb_BarrierFloor.Place, Bomb_BarrierFloor);
		PlaySoundMem(Bomb_BarrierFloor, DX_PLAYTYPE_BACK, 0);
	}
	if (pause_data.EnemyDeath2.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(pause_data.EnemyDeath2.Place, EnemyDeath2);
		PlaySoundMem(EnemyDeath2, DX_PLAYTYPE_BACK, FALSE);
	}
	if (pause_data.Charge1.Playing) {//BGM再生状態の復元
		SetSoundCurrentTime(pause_data.Charge1.Place, Charge1);
		PlaySoundMem(Charge1, DX_PLAYTYPE_BACK, FALSE);
	}
}

//多重で効果音の再生が行われる可能性があるときに使用する効果音の再生関数(1効果音あたり1フレームに一度までしか再生関数が呼ばれなくなる)
void SoundEffect_SafePlay(SE_TYPE type) {
	if (type < 0 || SE_TYPE_NUM <= type)	return;
	if (sE_playData[type] == 0) {//効果音をまだ鳴らしていないとき
		SoundEffect_Play(type);
	}
	sE_playData[type]++;//鳴らした回数のカウントアップ
}