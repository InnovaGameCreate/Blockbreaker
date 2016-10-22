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

	//フィールドブロックの描画
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BROCK_TYPE_NO)		continue;//無効ブロックは描画しない
			//描画先の座標を計算する
			double X, Y;
			if (field[x][y].blockMoveMotion.Enable) {
				//移動モーション有り
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, &X, &Y);	//移動元座標の計算
				double D = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//現在の移動距離の計算
				double Rota = getRotation(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY);
				//上の計算結果より、描画座標の計算
				X += D * cos(deg_to_rad(Rota));
				Y += D * sin(deg_to_rad(Rota));
			}
			else {
				//移動モーション無し
				Convert_Ingame_FromBlock(x, y, &X, &Y);
			}

			//中心座標に変換
			X += BLOCK_SIZE / 2.;
			Y += BLOCK_SIZE / 2.;

			switch (field[x][y].color) {
			case BROCK_TYPE_RED:	//赤ブロック描画
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 0));
				break;
			case BROCK_TYPE_BLUE:	//青ブロック描画
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 0, 255));
				break;
			case BROCK_TYPE_GREEN:	//緑ブロック描画
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(0, 255, 0));
				break;
			case BROCK_TYPE_PURPLE:	//紫ブロック描画
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 0, 255));
				break;
			case BROCK_TYPE_YELLOW:	//黄色ブロック描画
				DrawCircle((int)X, (int)Y, BLOCK_SIZE / 2, GetColor(255, 255, 0));
				break;
			}
		}
	}

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




	switch (gameCycle) {
	case GameCycle_FALL:
		if (getFallBlock_Interval() > 30)	Create_FallBlock(NULL);//前回の落下ブロック終了から一定時間後に落下ブロックの再出現
		//落下ブロックの落下処理
		if (Update_FallBlock()) {
			//落下完了後は重力サイクルへ
			Block_Gravity();		//重力によるブロックの落下を設定
			gameCycle = GameCycle_Gravity;
		
		}
		break;
	case GameCycle_Gravity:
		if (!isBlock_PlayMotion())	gameCycle = GameCycle_Delete;//消去サイクルへ
		break;
	case GameCycle_Delete:
		//隣接ブロックの削除
		if (Block_Delete() > 0) {
			//消去されたブロックが存在すれば重力計算
			Block_Gravity();
			gameCycle = GameCycle_Gravity;
		}
		else {
			gameCycle = GameCycle_FALL;
		}
		break;
	default:
		break;
	}



	//移動モーションのカウントアップと移動終了は無効化する処理
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].blockMoveMotion.Enable) {
				field[x][y].blockMoveMotion.Count++;//カウントアップ
				//移動する距離の計算
				double fX, fY, tX, tY;
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.FromX, field[x][y].blockMoveMotion.FromY, &fX, &fY);
				Convert_Ingame_FromBlock(field[x][y].blockMoveMotion.ToX, field[x][y].blockMoveMotion.ToY, &tX, &tY);
				double FMD = getDistance(fX, fY, tX, tY);	//最終的な移動距離
				double MD = getMoveDistance(field[x][y].blockMoveMotion.a, field[x][y].blockMoveMotion.MaxSpeed, field[x][y].blockMoveMotion.Count);	//現在の移動距離
				if (FMD <= MD) {//移動完了
					field[x][y].blockMoveMotion.Enable = FALSE;//移動を無効化
					continue;
				}
			}
		}
	}




}

//落下ブロックの落下処理(TRUEで落下ブロックの落下終了)
int Phase_GameMain::Update_FallBlock() {
	if (!isFallBlock_Enable()) {
		//無効の時はインターバルカウントを加算し終了
		fallBlockInfo.Counter--;
		return FALSE;
	}

	//以下有効なとき
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
				FallBlock_addField();	//フィールドに落下ブロックを設置
				SoundEffect_Play(SE_TYPE_DecisionSelect);
				return TRUE;
			}
		}
	}

	//キー入力による状態のリセット
	fallBlockInfo.Key_FlagFirstFall = FALSE;
	fallBlockInfo.Key_LRMove = 0;
	fallBlockInfo.Key_LRRota = 0;
	return FALSE;
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
	//if (fallblock_Pack == NULL)	return FALSE;

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
					if (getBlockColor(pX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BROCK_TYPE_NO) {
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
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BROCK_TYPE_NO) {
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
					if (getBlockColor(fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER), fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BROCK_TYPE_NO) {
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

//落下ブロックをフィールドブロックに変換する(つまり設置)
void Phase_GameMain::FallBlock_addField() {
	if (!isFallBlock_Enable())	return;	//そもそも有効で無い時は無視

	//何も無しブロック以外はフィールドブロックに順次変換を行う
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
			if (fallBlockInfo.fallblock.BlockID[x][y] != BROCK_TYPE_NO) {
				int fX, fY;		//ブロックのフィールド上の位置
				BROCK_TYPE fB;	//設置するブロックの種類
				fX = fallBlockInfo.PlaceX + (x - FALLBLOCK_CENTER);
				fY = fallBlockInfo.PlaceY + (y - FALLBLOCK_CENTER);
				fB = fallBlockInfo.fallblock.BlockID[x][y];

				add_FraldBlock(fX, fY, fB);

			}
		}
	}
	printLog_I(_T("落下ブロックの【設置】"));

	//落下ブロックの無効化処理
	Delete_FallBlock();

}

//フィールドにブロックを追加する(成功でTRUE,失敗でFALSE)(上書き禁止)
int Phase_GameMain::add_FraldBlock(int X, int Y, BROCK_TYPE brock_type) {
	//ブロック無しブロックは設置不可
	if (brock_type == BROCK_TYPE_NO)					return FALSE;

	//ブロックの上書きは失敗にする(画面外もブロック有りと判定が出る設定にする)
	if (getBlockColor(X, Y, TRUE) != BROCK_TYPE_NO)	return FALSE;

	//ブロックの設置
	field[X][Y].fall_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
	field[X][Y].move_flag = FALSE;	//初期値これでいいのか分からんが一応初期化しとく
	field[X][Y].color = brock_type;	//ブロックの置き換え

	printLog_I(_T("フィールドブロックの新規生成[%d][%d](type=%d)"), X, Y, brock_type);

	return TRUE;
}

//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうか)
Phase_GameMain::BROCK_TYPE Phase_GameMain::getBlockColor(int X, int Y, int useOutScreenBlock) {

	//画面外処理(画面外ブロックが定義されていないので、赤ブロックが設置されていることにする)
	if (X < 0 || BLOCK_WIDTHNUM <= X)	return (useOutScreenBlock) ? BROCK_TYPE_RED : BROCK_TYPE_NO;
	if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return (useOutScreenBlock) ? BROCK_TYPE_RED : BROCK_TYPE_NO;

	return field[X][Y].color;

}

//フィールドブロックを重力で落下させる
void Phase_GameMain::Block_Gravity() {


	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		//列ごとにブロック情報をコピーする
		field_info t[BLOCK_HEIGHTNUM];
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			t[y] = field[x][y];
			field[x][y].color = BROCK_TYPE_NO;
		}
		int Count = BLOCK_HEIGHTNUM - 1;
		//下の段から存在するブロックを並べ直す(逆順回し)
		for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
			if (t[y].color != BROCK_TYPE_NO) {
				field[x][Count] = t[y];
				//落下モーション(カウントが移動先、yが移動元になる)
				Block_SetMotion(x, Count, x, y, x, Count, 0.3, 15);
				Count--;
			}
		}
	}

	printLog_I(_T("ブロックに重力計算を行いました"));
}

//フィールドブロックを直接削除する(重力計算を行うかどうかのフラグ)
void Phase_GameMain::Block_Delete_Direct(int X, int Y, int CallGravityFlag) {
	//画面外処理(画面外ブロックが定義されていないので、赤ブロックが設置されていることにする)
	if (X < 0 || BLOCK_WIDTHNUM <= X)	return;
	if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return;

	field[X][Y].color = BROCK_TYPE_NO;
	printLog_I(_T("ブロックの【削除】[%d][%d]"), X, Y);

	if (CallGravityFlag)	Block_Gravity();
}

//連続するフィールドブロックを削除する(ついでにお邪魔ブロックの処理も行う)(消去したブロックの数)
int Phase_GameMain::Block_Delete() {
	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color == BROCK_TYPE_NO) {//除外ブロック
				DeleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				DeleteFlag[x][y] = -1;
			}
		}
	}

	//隣接ブロックの計算を行う
	int Counter[BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM];	//IDごとの隣接カウント数
	int ID = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (DeleteFlag[x][y] == -1) {//未探索ブロック
				Counter[ID] = 0;
				SequenceCount(x, y, ID, DeleteFlag, &(Counter[ID]));
				ID++;
			}
		}
	}



	//4以上隣接しているブロックは削除する
	int DelCount = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
				if (Counter[DeleteFlag[x][y]] >= 3) {
					//削除
					Block_Delete_Direct(x, y, FALSE);
					DelCount++;
				}
			}
		}
	}

	printLog_I(_T("隣接ブロックの削除計算を行いました(%dブロック)"), DelCount);


	return DelCount;
}

//隣接する同色ブロックにマーカーを付ける
void Phase_GameMain::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter) {
	if (deleteFlag[x][y] != -1)	return;		//未探索ブロックじゃない場合
	BROCK_TYPE bt = field[x][y].color;      //ブロックの種類を記録する
	deleteFlag[x][y] = ID;					//探索済み(探索IDを設定する)
	(*Counter)++;

	if (x + 1 < BLOCK_WIDTHNUM	&& field[x + 1][y].color == bt) SequenceCount(x + 1, y, ID, deleteFlag, Counter);
	if (y + 1 < BLOCK_HEIGHTNUM	&& field[x][y + 1].color == bt) SequenceCount(x, y + 1, ID, deleteFlag, Counter);
	if (x - 1 >= 0 && field[x - 1][y].color == bt) SequenceCount(x - 1, y, ID, deleteFlag, Counter);
	if (y - 1 >= 0 && field[x][y - 1].color == bt) SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//フィールドのブロックにモーションを設定する
void Phase_GameMain::Block_SetMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockColor(x, y) == BROCK_TYPE_NO)	return;	//ブロックが無効の場合は処理をしない
	if (FromX == ToX && FromY == ToY)			return;	//移動無しの場合も処理をしない
	if (a <= 0)									return;	//加速度が負の数の場合も処理をしない
	if (MaxSpeed <= 0)							return;	//最大速度が負の数の場合も処理をしない

	if (field[x][y].blockMoveMotion.Enable) {
		printLog_C(_T("ブロックの移動モーションを上書きします"));
		field[x][y].blockMoveMotion.Enable = FALSE;
	}

	field[x][y].blockMoveMotion.ToX = ToX;
	field[x][y].blockMoveMotion.ToY = ToY;
	field[x][y].blockMoveMotion.FromX = FromX;
	field[x][y].blockMoveMotion.FromY = FromY;
	field[x][y].blockMoveMotion.a = a;
	field[x][y].blockMoveMotion.MaxSpeed = MaxSpeed;
	field[x][y].blockMoveMotion.Count = 0;

	field[x][y].blockMoveMotion.Enable = TRUE;

	printLog_I(_T("ブロックに【移動モーション】を設定"));
}

//モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Phase_GameMain::isBlock_PlayMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].color != BROCK_TYPE_NO && field[x][y].blockMoveMotion.Enable) {
				return TRUE;
			}
		}
	}

	return FALSE;
}