#include "stdafx.h"
#include "Phase_GameMain.h"

//色
enum COLOR{RED, BLUE, YELLOW, GREEN, PURPLE};

struct field_info {
	int color;//ブロックの色
	int fall_flag;//落下中かどうかのフラグ
	int move_flag;//移動中かどうかのフラグ
};

struct field_info field[10][16];

Phase_GameMain::Phase_GameMain() {
}


Phase_GameMain::~Phase_GameMain() {
}

//初期化(描画処理)
void Phase_GameMain::Init_Draw() {
	//ゲーム画面の生成(後でシェーダを使いたいので2のn乗のサイズで作成します)
	if ((gameWindow = MakeScreen(Pot(GAMEWINDOW_WIDTH), Pot(GAMEWINDOW_HEIGHT), FALSE)) == -1)	printLog_E(_T("ウィンドウ作成に失敗しました"));
}

//初期化(計算処理)
void Phase_GameMain::Init_Update() {
	CursorX = 0;
	CursorY = 0;
	Flag_Pause = FALSE;
	Flag_pauseRequest = FALSE;
}

//描画処理
void Phase_GameMain::Draw() {

	//描画先をゲーム画面にする
	SetDrawScreen(gameWindow);

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawBox(0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, GetColor(0xb3, 0x65, 0xe5), TRUE);

	//カーソル位置に四角形の枠を描画
	{//スコープ面倒いので
		double X, Y;
		GameMain_Convert_Block_FromIngame(GameMain_getCursorX(), GameMain_getCursorY(), &X, &Y);
		DrawBox((int)X + 2, (int)Y + 2, (int)(X + BLOCK_SIZE - 2), (int)(Y + BLOCK_SIZE - 2), GetColor(0x07, 0xdb, 0x9d), FALSE);
		DrawLine((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 2), (int)(Y + BLOCK_SIZE - 2), GetColor(0x07, 0xdb, 0x9d));
		DrawLine((int)(X + 2), (int)(Y + BLOCK_SIZE - 2), (int)(X + BLOCK_SIZE - 2), (int)(Y + 2), GetColor(0x07, 0xdb, 0x9d));
	}

	//デバッグ
#ifdef DEBUG_GAMEMAIN
	//縦横70間隔で線を描画する
	for (int i = 1; i < BLOCK_WIDTHNUM; i++) {
		DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, GAMEWINDOW_HEIGHT, GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = 1; i < BLOCK_HEIGHTNUM; i++) {
		DrawLine(0, i * BLOCK_SIZE, GAMEWINDOW_WIDTH, i * BLOCK_SIZE, GetColor(0xff, 0xbf, 0x74));
	}
#endif // DEBUG_GAMEMAIN



	//描画先をバックスクリーンにする
	SetDrawScreen(DX_SCREEN_BACK);

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0x5b, 0x8e, 0xda), TRUE);


	//ゲーム画面を描画する
	DrawRectGraph(GAMEWINDOW_PADDINGX, GAMEWINDOW_PADDINGY, 0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, gameWindow, FALSE, FALSE);

	//デバッグ
#ifdef DEBUG_GAMEMAIN
	//マス目の番号を描画
	for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
		int Width = -GetDrawFormatStringWidthToHandle(Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
		Width += BLOCK_SIZE;
		Width /= 2;
		DrawFormatStringToHandle(GAMEWINDOW_PADDINGX + i*BLOCK_SIZE + Width, 30, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%d"), i);
	}
	for (int i = 0; i < BLOCK_HEIGHTNUM; i++) {
		DrawFormatStringToHandle(20, GAMEWINDOW_PADDINGY + i * BLOCK_SIZE + 15, GetColor(255, 255, 255), Font_getHandle(FONTTYPE_SFSquareHeadCondensed_Edge25), _T("%2d"), i);
	}
#endif // DEBUG_GAMEMAIN

	if (GameMain_isPaused()) {//ポーズ状態の時
							  //ポーズ状態と分かるように描画する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (getFrameCount(THREAD_Update) % 120 > 40)	Font_DrawStringCenterWithShadow(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30, _T("PAUSE"), GetColor(240, 240, 240), GetColor(20, 20, 20), FONTTYPE_GenJyuuGothicLHeavy_Edge60);
	}
}

//計算処理
void Phase_GameMain::Update() {
	//計算処理の最初に行いたい処理(多くなったら関数化？)
	//リクエストの反映

	Flag_Pause = Flag_pauseRequest;//リクエストの反映
	//ここまで


	GameMain_Key();	//キー処理

	if (GameMain_isPaused())	return;//ポーズ処理が入った場合は先に進まない
}

//終了処理(描画処理)
void Phase_GameMain::Finalize_Draw() {

}

//終了処理(計算処理)
void Phase_GameMain::Finalize_Update() {

}

//キー処理
void Phase_GameMain::GameMain_Key() {

	//ポーズ処理
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		GameMain_PauseRequest(!GameMain_isPaused());	//ポーズ状態の反転
	}

	if (GameMain_isPaused())	return;//ポーズ処理が入った場合は先に進まない


	static int Flag_DOWN = TRUE;	//下移動のSE関連のフラグ
	static int Flag_UP = TRUE;		//下移動のSE関連のフラグ
	static int Flag_RIGHT = TRUE;	//下移動のSE関連のフラグ
	static int Flag_LEFT = TRUE;		//下移動のSE関連のフラグ

										//キー入力なしの場合
	if (getKeyBind(KEYBIND_DOWN) == 0)	Flag_DOWN = TRUE;
	if (getKeyBind(KEYBIND_UP) == 0)	Flag_UP = TRUE;
	if (getKeyBind(KEYBIND_RIGHT) == 0)	Flag_RIGHT = TRUE;
	if (getKeyBind(KEYBIND_LEFT) == 0)	Flag_LEFT = TRUE;

	if (getKeyBind(KEYBIND_DOWN) == 1 || (getKeyBind(KEYBIND_DOWN) > 20 && getKeyBind(KEYBIND_DOWN) % 3 == 1)) {//下移動
		if (GameMain_CursorY_add(1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//移動した場合
		}
		else {
			if (Flag_DOWN) {
				SoundEffect_Play(SE_TYPE_Graze);	//移動出来なかったときかつフラグが立っているとき
				Flag_DOWN = FALSE;					//フラグをFALSEに
			}
		}
	}

	if (getKeyBind(KEYBIND_UP) == 1 || (getKeyBind(KEYBIND_UP) > 20 && getKeyBind(KEYBIND_UP) % 3 == 1)) {//上移動
		if (GameMain_CursorY_add(-1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//移動した場合
		}
		else {
			if (Flag_UP) {
				SoundEffect_Play(SE_TYPE_Graze);	//移動出来なかったときかつフラグが立っているとき
				Flag_UP = FALSE;					//フラグをFALSEに
			}
		}
	}

	if (getKeyBind(KEYBIND_RIGHT) == 1 || (getKeyBind(KEYBIND_RIGHT) > 20 && getKeyBind(KEYBIND_RIGHT) % 3 == 1)) {//右移動
		if (GameMain_CursorX_add(1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//移動した場合
		}
		else {
			if (Flag_RIGHT) {
				SoundEffect_Play(SE_TYPE_Graze);	//移動出来なかったときかつフラグが立っているとき
				Flag_RIGHT = FALSE;					//フラグをFALSEに
			}
		}
	}

	if (getKeyBind(KEYBIND_LEFT) == 1 || (getKeyBind(KEYBIND_LEFT) > 20 && getKeyBind(KEYBIND_LEFT) % 3 == 1)) {//左移動
		if (GameMain_CursorX_add(-1) != 0) {
			SoundEffect_Play(SE_TYPE_ChangeSelect);	//移動した場合
		}
		else {
			if (Flag_LEFT) {
				SoundEffect_Play(SE_TYPE_Graze);	//移動出来なかったときかつフラグが立っているとき
				Flag_LEFT = FALSE;					//フラグをFALSEに
			}
		}
	}
}

//カーソル位置を相対的に移動する
int Phase_GameMain::GameMain_CursorX_add(int Val) {
	//仮に移動したことにする
	int t = CursorX + Val;
	//画面外に出る場合は端で止まるようにValの値を調整する
	if (t < 0)	Val = 0 - CursorX;	//画面左側
	else if (t >= BLOCK_WIDTHNUM)	Val = (BLOCK_WIDTHNUM - 1) - CursorX;	//画面右側

																			//本ちゃん適用
	CursorX += Val;
	return Val;
}

//カーソル位置を相対的に移動する
int Phase_GameMain::GameMain_CursorY_add(int Val) {
	//仮に移動したことにする
	int t = CursorY + Val;
	//画面外に出る場合は端で止まるようにValの値を調整する
	if (t < 0)	Val = 0 - CursorY;	//画面上側
	else if (t >= BLOCK_HEIGHTNUM)	Val = (BLOCK_HEIGHTNUM - 1) - CursorY;	//画面下側

																			//本ちゃん適用
	CursorY += Val;
	return Val;
}

//カーソル位置を取得する
int Phase_GameMain::GameMain_getCursorX() {
	return CursorX;
}

//カーソル位置を取得する
int Phase_GameMain::GameMain_getCursorY() {
	return CursorY;
}

//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
void Phase_GameMain::GameMain_Convert_Block_FromIngame(int blockX, int blockY, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE;
	}
}

//ポーズ状態かどうかの取得(TRUEでポーズ)
int Phase_GameMain::GameMain_isPaused() {
	return Flag_Pause;
}

//ポーズ状態のリクエスト
void Phase_GameMain::GameMain_PauseRequest(int b_Flag) {
	b_Flag = (b_Flag) ? TRUE : FALSE;//不正な引数の対策

	Flag_pauseRequest = b_Flag;
	if (Flag_pauseRequest)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ポーズリクエスト【有効】"));
	else					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ポーズリクエスト【無効】"));
}