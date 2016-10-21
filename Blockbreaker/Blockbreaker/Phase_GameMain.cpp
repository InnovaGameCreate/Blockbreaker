#include "stdafx.h"
#include "Phase_GameMain.h"

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
	Flag_Pause = FALSE;
	Flag_pauseRequest = FALSE;
}

//描画処理
void Phase_GameMain::Draw() {

	//描画先をゲーム画面にする
	SetDrawScreen(gameWindow);

	//画面一杯に四角形を描画する(後々テクスチャに置き換わる)
	DrawBox(0, 0, GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT, GetColor(0xb3, 0x65, 0xe5), TRUE);

	//落下中ブロックの描画
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				switch (fallBlockInfo.fallblock.BlockID[x][y]) {
				case BROCK_TYPE_RED:	//赤ブロック描画
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 0));
					break;
				case BROCK_TYPE_BLUE:	//青ブロック描画
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 0, 255));
					break;
				case BROCK_TYPE_GREEN:	//緑ブロック描画
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 255, 0));
					break;
				case BROCK_TYPE_PURPLE:	//紫ブロック描画
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 255));
					break;
				case BROCK_TYPE_YELLOW:	//黄色ブロック描画
					Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
					X += BLOCK_SIZE / 2.;
					Y += BLOCK_SIZE / 2.;
					DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 255, 0));
					break;
				}
				if (fallBlockInfo.fallblock.BlockID[x][y] == BROCK_TYPE_RED) {
					
					
				}
			}
		}
	}

	//デバッグ
#ifdef DEBUG_GAMEMAIN
	//縦横BLOCK_SIZE間隔で線を描画する
	for (int i = 1; i < BLOCK_WIDTHNUM; i++) {
		DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, GAMEWINDOW_HEIGHT, GetColor(0xff, 0xbf, 0x74));
	}
	for (int i = 1; i < BLOCK_HEIGHTNUM; i++) {
		DrawLine(0, i * BLOCK_SIZE, GAMEWINDOW_WIDTH, i * BLOCK_SIZE, GetColor(0xff, 0xbf, 0x74));
	}

	//落下ブロックの範囲を描画する
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Convert_Ingame_FromBlock(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), &X, &Y);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
				DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				DrawBox((int)(X + 2), (int)(Y + 2), (int)(X + BLOCK_SIZE - 1), (int)(Y + BLOCK_SIZE - 1), GetColor(0xef, 0xb8, 0x90), FALSE);
			}
		}
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

	if (isPaused()) {//ポーズ状態の時
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

	if (isPaused())	return;//ポーズ処理が入った場合は先に進まない


	//落下ブロックの落下処理
	if (isFallBlock_Enable()) {//落下ブロックが有効な時
		fallBlockInfo.Counter++;	//カウンタを加算
		if (isFallBlock_Falling()) {//落下中の場合
			fallBlockInfo.FallCount--;
			if (fallBlockInfo.Key_FlagFirstFall)	fallBlockInfo.FallCount -= 5;	//高速落下モードの場合カウントをさらに入れる
			if (fallBlockInfo.Key_LRMove > 0) {
				//右移動
				if (FallBlock_MoveX(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
				else							SoundEffect_Play(SE_TYPE_Graze);

			}
			if (fallBlockInfo.Key_LRMove < 0) {
				//左移動
				if (FallBlock_MoveX(-1))	SoundEffect_Play(SE_TYPE_Bulletfire2);		
				else						SoundEffect_Play(SE_TYPE_Graze);
			}
			if (fallBlockInfo.Key_LRRota > 0) {
				//時計回りに回転
				if (FallBlock_Rotate(1))	SoundEffect_Play(SE_TYPE_Bulletfire2);		
				else						SoundEffect_Play(SE_TYPE_Graze);
			}
			if (fallBlockInfo.Key_LRRota < 0) {
				//反時計回りに回転
				if (FallBlock_Rotate(-1))	SoundEffect_Play(SE_TYPE_Bulletfire2);		
				else						SoundEffect_Play(SE_TYPE_Graze);
			}

			if (fallBlockInfo.FallCount <= 0) {//カウント0以下で落下
				fallBlockInfo.FallCount = 60;	//カウントを戻す(ここで戻さないとFallBlock_MoveY関数で移動無効と判定され、うまく動かない)
				/*落下しようとして無理だったらカウントを0にし無効化する方針*/
				if (FallBlock_MoveY(1) == 0) {	//落下出来なかった
					fallBlockInfo.FallCount = 0;	//落下カウントの無効化
					printLog_I(_T("ブロックの落下終了"));
					Delete_FallBlock();
					SoundEffect_Play(SE_TYPE_DecisionSelect);
				}
			}
		}
		//キー入力による状態のリセット
		fallBlockInfo.Key_FlagFirstFall = FALSE;
		fallBlockInfo.Key_LRMove = 0;
		fallBlockInfo.Key_LRRota = 0;
	}
	else {
		fallBlockInfo.Counter--;
	}

	if (getFallBlock_Interval() > 120)	Create_FallBlock(NULL);//前回の落下ブロック終了から一定時間後に落下ブロックの再出現

}

//終了処理(描画処理)
void Phase_GameMain::Finalize_Draw() {
	DeleteGraph(gameWindow);
}

//終了処理(計算処理)
void Phase_GameMain::Finalize_Update() {

}

//キー処理
void Phase_GameMain::GameMain_Key() {

	//ポーズ処理
	if (getKeyBind(KEYBIND_PAUSE) == 1) {
		PauseRequest(!isPaused());	//ポーズ状態の反転
	}

	if (isPaused())	return;//ポーズ処理が入った場合は先に進まない

	if (isFallBlock_Falling()) {
		if (getKeyBind(KEYBIND_DOWN) > 0) {//高速落下モード
			fallBlockInfo.Key_FlagFirstFall = TRUE;
		}
		if (getKeyBind(KEYBIND_RIGHT) == 1) {//右移動
			fallBlockInfo.Key_LRMove++;
		}
		if (getKeyBind(KEYBIND_LEFT) == 1) {//左移動
			fallBlockInfo.Key_LRMove--;
		}
		if (getKeyBind(KEYBIND_ROTAL) == 1) {//反時計回り
			fallBlockInfo.Key_LRRota--;
		}
		if (getKeyBind(KEYBIND_ROTAR) == 1) {//時計回り
			fallBlockInfo.Key_LRRota++;
		}
	}
}

//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
void Phase_GameMain::Convert_Ingame_FromBlock(int blockX, int blockY, double *IngameX, double *IngameY) {
	if (IngameX != NULL) {
		*IngameX = blockX * BLOCK_SIZE;
	}
	if (IngameY != NULL) {
		*IngameY = blockY * BLOCK_SIZE;
	}
}

//ポーズ状態かどうかの取得(TRUEでポーズ)
int Phase_GameMain::isPaused() {
	return Flag_Pause;
}

//ポーズ状態のリクエスト
void Phase_GameMain::PauseRequest(int b_Flag) {
	b_Flag = (b_Flag) ? TRUE : FALSE;//不正な引数の対策

	Flag_pauseRequest = b_Flag;
	if (Flag_pauseRequest)	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ポーズリクエスト【有効】"));
	else					Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, LOG_NULL, _T("ポーズリクエスト【無効】"));
}

//落下ブロックが落下中かどうかの取得(TRUEで落下中)
int Phase_GameMain::isFallBlock_Falling() {
	if (!isFallBlock_Enable())	return FALSE;
	return (fallBlockInfo.FallCount > 0) ? TRUE : FALSE;
}

//落下ブロックが有効かどうかの取得(TRUEで有効)
int Phase_GameMain::isFallBlock_Enable() {
	return (fallBlockInfo.Enable) ? TRUE : FALSE;
}

//落下ブロックを生成する(戻り値:成功でTRUE)
int Phase_GameMain::Create_FallBlock(struct Fallblock_Pack *fallblock_Pack) {
	if (fallblock_Pack == NULL)	return FALSE;

	if (isFallBlock_Enable()) {
		printLog_C(_T("落下中のブロックがすでに存在するため、落下ブロックを新たに追加出来ませんでした"));
		return FALSE;
	}

	//落下ブロックの形状を設定する(暫定)
	/*十時マークそして0は無効、1は有効(赤ブロックになるように設定)*/
	fallBlockInfo.fallblock.BlockID[0][0] = BROCK_TYPE_NO;
	fallBlockInfo.fallblock.BlockID[1][0] = BROCK_TYPE_YELLOW;
	fallBlockInfo.fallblock.BlockID[2][0] = BROCK_TYPE_NO;

	fallBlockInfo.fallblock.BlockID[0][1] = BROCK_TYPE_PURPLE;
	fallBlockInfo.fallblock.BlockID[1][1] = BROCK_TYPE_RED;
	fallBlockInfo.fallblock.BlockID[2][1] = BROCK_TYPE_GREEN;

	fallBlockInfo.fallblock.BlockID[0][2] = BROCK_TYPE_NO;
	fallBlockInfo.fallblock.BlockID[1][2] = BROCK_TYPE_BLUE;
	fallBlockInfo.fallblock.BlockID[2][2] = BROCK_TYPE_NO;

	//落下カウントを60に設定
	fallBlockInfo.FallCount = 60;

	//落下ブロックのその他の情報の初期化
	fallBlockInfo.PlaceX = BLOCK_WIDTHNUM / 2;
	fallBlockInfo.PlaceY = 1;
	fallBlockInfo.Counter = 0;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	fallBlockInfo.Key_FlagFirstFall = FALSE;

	//有効
	fallBlockInfo.Enable = TRUE;

	printLog_I(_T("落下ブロックの【新規生成】"));
	return TRUE;
}

//落下ブロックの前回の落下からのインターバルの取得(落下ブロックが存在するときは0が返ります)
int Phase_GameMain::getFallBlock_Interval() {
	if (isFallBlock_Enable())	return 0;
	return (-fallBlockInfo.Counter);
}

//落下ブロックの無効化
void Phase_GameMain::Delete_FallBlock() {
	if (!isFallBlock_Enable())	return;	//そもそも有効で無い時は無視

	fallBlockInfo.Counter = 0;		//カウンタを0にもどす
	fallBlockInfo.Enable = FALSE;	//落下ブロックの無効化

	printLog_I(_T("落下ブロックの【消去】"));
}

//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
int Phase_GameMain::FallBlock_MoveX(int MoveVal) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

	//方針:だんだんMoveValを大きくしていく
	int Minus = FALSE;//マイナスフラグ
	if (MoveVal < 0) {
		//符号反転
		MoveVal = -MoveVal;
		Minus = TRUE;
	}

	for (int i = 0; i < MoveVal; i++) {
		//擬似的に移動したことにする
		int pX = 0;
		if (Minus)	pX = fallBlockInfo.PlaceX - (i + 1);	//負の方向
		else		pX = fallBlockInfo.PlaceX + (i + 1);	//正の方向

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.fallblock.BlockID[x][y] != BROCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), BROCK_TYPE_RED) != BROCK_TYPE_NO) {
						//他のブロックと重なっていた場合はループを抜ける
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						MoveVal = i;//最外のループも抜ける
					}
				}
			}
		}
	}

	//符号を元に戻す
	if (Minus) {
		MoveVal = -MoveVal;
	}

	//ずらしの反映
	fallBlockInfo.PlaceX += MoveVal;

	return MoveVal;
}

//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
int Phase_GameMain::FallBlock_MoveY(int MoveVal) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

												//方針:だんだんMoveValを大きくしていく
	int Minus = FALSE;//マイナスフラグ
	if (MoveVal < 0) {
		//符号反転
		MoveVal = -MoveVal;
		Minus = TRUE;
	}

	for (int i = 0; i < MoveVal; i++) {
		//擬似的に移動したことにする
		int pY = 0;
		if (Minus)	pY = fallBlockInfo.PlaceY - (i + 1);	//負の方向
		else		pY = fallBlockInfo.PlaceY + (i + 1);	//正の方向

															//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (fallBlockInfo.fallblock.BlockID[x][y] != BROCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), BROCK_TYPE_RED) != BROCK_TYPE_NO) {
						//他のブロックと重なっていた場合はループを抜ける
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						MoveVal = i;//最外のループも抜ける
					}
				}
			}
		}
	}

	//符号を元に戻す
	if (Minus) {
		MoveVal = -MoveVal;
	}

	//ずらしの反映
	fallBlockInfo.PlaceY += MoveVal;

	return MoveVal;
}

//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)
int Phase_GameMain::FallBlock_Rotate(int RotaVal) {
	if (!isFallBlock_Falling())		return 0;	//そもそも落下中で無い時は無視

												//方針:だんだんMoveValを大きくしていく
	int Minus = FALSE;//マイナスフラグ
	if (RotaVal < 0) {
		//符号反転
		RotaVal = -RotaVal;
		Minus = TRUE;
	}


	int FLAG = FALSE;
	for (int i = 0; i < RotaVal; i++) {
		//擬似的に回転したことにする
		BROCK_TYPE RotaBlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];
		if (Minus) {//反時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = fallBlockInfo.fallblock.BlockID[x][y];
				}
			}
		}
		else {//時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = fallBlockInfo.fallblock.BlockID[x][y];
				}
			}
		}

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (RotaBlockID[x][y] != BROCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), BROCK_TYPE_RED) != BROCK_TYPE_NO) {
						//他のブロックと重なっていた場合はループを抜ける
						x = FALLBLOCK_SIZE;
						y = FALLBLOCK_SIZE;
						RotaVal = i;
						FLAG = TRUE;//最外のループも抜ける
					}
				}
			}
		}

		if (FLAG) {
			break;
		}
		else {
			//回転を確定する
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					fallBlockInfo.fallblock.BlockID[x][y] = RotaBlockID[x][y];
				}
			}
		}

	}

	//符号を元に戻す
	if (Minus) {
		RotaVal = -RotaVal;
	}

	return RotaVal;
}

//指定した座標のブロックの取得(第3引数は画面外のブロックを判定したときの戻り値)
Phase_GameMain::BROCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, BROCK_TYPE OutGameBlock) {

	//画面外処理
	if (X < 0 || BLOCK_WIDTHNUM <= X)	return OutGameBlock;
	if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return OutGameBlock;


	//画面内のブロックの情報は未完成なので何も無い判定を返す
	return BROCK_TYPE_NO;

}