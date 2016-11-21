#include "Block_Fall.h"
#include "MainFunc.h" 
//落下ブロックのクラス

Block_Fall::Block_Fall() {
	Enable = FALSE;
	Counter = 0;
}


Block_Fall::~Block_Fall() {
}

//落下ブロックの描画
void Block_Fall::Draw() {
	if (!isEnable())	return;	//無効の場合は何もしない

	for (int i = 0; i < ARRAY_LENGTH(BlockID_FallPoint); i++) {
		//有効なブロックのみ描画処理を入れる
		if (!BlockID_FallPoint[i].isEnable())	continue;
		BlockID_FallPoint[i].Draw(phase_GameMain.getTex_Block()->getBack(), 1);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		BlockID_FallPoint[i].Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//ブロックの落下予想地点にブロックを描画する
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		int ShadowDrawDFlag = FALSE;
		int yCount = 0;	//y方向に存在するブロックの数
		for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
			BlockID[x][y].Draw();
			if (x == 1 && y == 1 && Flag_Rotate) {
				//中心の場合かつ回転可能ブロックの場合
				//float Scale = 0.9 + getGraph_Sin(fallBlockInfo.Counter*5, 0.05, 0);
				float Scale = 1;
				BlockID[x][y].Draw(phase_GameMain.getTex_Block()->getCenterEffect(), Scale);
			}
		}
	}
}

//落下ブロック待機列の描画
void Block_Fall::Draw_WaitLine() {

	//描画の基準にする左上座標を初期値とし
	int placeX = 550;
	int placeY = 60;

	double Before_X = 0;	//直前の描画エリアの高さ
	double Scale = 1;

	for (int i = 0; i < min(ARRAY_LENGTH(waitBlockinfo), 5); i++) {
		placeY += (int)Before_X;
		if (i != 0)	Scale = 0.7;
		Before_X = BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale + 20;
		DrawBox(placeX, placeY, (int)(placeX + BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale), (int)(placeY + BLOCK_SIZE * (FALLBLOCK_SIZE + 2) * Scale), GetColor(10, 10, 10), TRUE);
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				double X, Y;
				Block_Field::Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);

				//縦にずらす
				X *= Scale;
				Y *= Scale;

				X += placeX + BLOCK_SIZE * Scale;
				Y += placeY + BLOCK_SIZE * Scale;
				waitBlockinfo[i].BlockID[x][y].Draw(X, Y, waitBlockinfo[i].BlockID[x][y].getBlockTexture(), Scale);
			}
		}
	}
}

//落下ブロックの計算処理(TRUEで落下完了した瞬間)
int Block_Fall::Update() {
	//カウンタの加算
	if (isEnable())	Counter++;	//有効な場合は正方向に加算する
	else			Counter--;	//無効な場合は負方向に加算する

	if (!isEnable())	return FALSE;//無効の場合はこれ以上処理を行わない

	FallCount--;	//一段落下するまでのカウントダウン
	if (Key_FlagFirstFall)	FallCount -= 20;	//高速落下モードの場合カウントをさらに入れる

	if (FallCount < 0)		FallCount = 0;		//落下カウントが0以下だと都合が悪いので
	if (Key_LRMove > 0) {
		//右移動
		if (FallBlock_MoveX(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);

	}
	if (Key_LRMove < 0) {
		//左移動
		if (FallBlock_MoveX(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);
	}
	if (Key_LRRota > 0) {
		//時計回りに回転
		if (FallBlock_Rotate(1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);
	}
	if (Key_LRRota < 0) {
		//反時計回りに回転
		if (FallBlock_Rotate(-1) != 0)	SoundEffect_Play(SE_TYPE_Bulletfire2);
		else							SoundEffect_Play(SE_TYPE_Graze);
	}

	if (FallCount <= 0) {//カウント0以下で落下
		FallCount = 60;	//カウントを戻す(ここで戻さないとFallBlock_MoveY関数で移動無効と判定され、うまく動かない)
										/*落下しようとして無理だったらカウントを0にし無効化する方針*/
		if (FallBlock_MoveY(1) == 0) {	//落下出来なかった
			FallCount = -1;	//落下カウントの無効化
			printLog_I(_T("ブロックの落下終了"));
			FallBlock_addField();	//フィールドに落下ブロックを設置
			SoundEffect_Play(SE_TYPE_DecisionSelect);
			return TRUE;
		}
	}

	//キー入力による状態のリセット
	Key_FlagFirstFall = FALSE;
	Key_LRMove = 0;
	Key_LRRota = 0;
	return FALSE;
}

//キー処理
void Block_Fall::Key() {
	if (isEnable()) {
		if (getKeyBind(KEYBIND_DOWN) > 0) {//高速落下モード
			Key_FlagFirstFall = TRUE;
		}
		if (getKeyBind(KEYBIND_RIGHT) == 1) {//右移動
			Key_LRMove++;
		}
		if (getKeyBind(KEYBIND_LEFT) == 1) {//左移動
			Key_LRMove--;
		}
		if (getKeyBind(KEYBIND_ROTAL) == 1) {//反時計回り
			Key_LRRota--;
		}
		if (getKeyBind(KEYBIND_ROTAR) == 1) {//時計回り
			Key_LRRota++;
		}
	}
}

//描画情報の更新
void Block_Fall::Update_DrawData(double paddingX, double paddingY) {
	//ブロックの落下予想地点のブロックの描画情報を更新
	int Count = 0;
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		int ShadowDrawDFlag = FALSE;
		int yCount = 0;	//y方向に存在するブロックの数
		for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
			//ブロックの落下予想地点の描画
			if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {

				//最上段のブロックのY座標を取得する
				int ansY = phase_GameMain.getBlock_Upper(PlaceX + (x - FALLBLOCK_CENTER)) - 1 - yCount;
				//実際の描画座標に書き換える
				double X, Y;
				Block_Field::Convert_Ingame_FromBlock(PlaceX + (x - FALLBLOCK_CENTER), ansY, 0.5, 0.5, &X, &Y);

				//フィールドのズレの部分を反映する
				X += paddingX;
				Y += paddingY;
				//ブロックを新規登録する
				BlockID_FallPoint[Count].addBlcok(BlockID[x][y].getBlockType(), TRUE);
				BlockID_FallPoint[Count].Update_DrawData(X, Y);
				Count++;
				yCount++;
			}
		}
	}
	//余った落下予想地点情報を何も無しブロックで初期化する
	for (int i = Count; i < ARRAY_LENGTH(BlockID_FallPoint); i++) {
		BlockID_FallPoint[i].Delete_Block();
	}

	//落下中ブロックの描画情報の更新
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		int ShadowDrawDFlag = FALSE;
		int yCount = 0;	//y方向に存在するブロックの数
		for (int y = FALLBLOCK_SIZE - 1; y >= 0; y--) {
			double X, Y;
			double Per = -(FallCount / 60.);
			Block_Field::Convert_Ingame_FromBlock(PlaceX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), 0.5, Per + 0.5, &X, &Y);

			//フィールドのズレの部分を反映する
			X += paddingX;
			Y += paddingY;
			//画面外に出てしまう場合はでないように調整する
			int Dan = 0;//ブロックが存在する段数
			for (int y2 = 0; y2 < FALLBLOCK_SIZE; y2++) {
				for (int x2 = 0; x2 < FALLBLOCK_SIZE; x2++) {
					if (BlockID[x2][y2].getBlockType() != BLOCK_TYPE_NO) {
						Dan = y2;
						//ループを抜ける
						x2 = FALLBLOCK_SIZE;
						y2 = FALLBLOCK_SIZE;
					}
				}
			}
			if (Y < (y - Dan + BLOCK_PADDINGUP)*BLOCK_SIZE + BLOCK_SIZE / 2) {
				Y = (y - Dan + BLOCK_PADDINGUP)*BLOCK_SIZE + BLOCK_SIZE / 2;
			}
			BlockID[x][y].Update_DrawData(X, Y);
		}
	}
}

//リスタート(初期化)
void Block_Fall::Restart() {
	//現在落下中のブロックの無効化
	Delete_FallBlock();

	//ブロック待機列の再生成
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo); i++) {
		Create_Wait_Block();
	}
}

//落下ブロックが落下中かどうかの取得(落下中＝有効)
int Block_Fall::isEnable() {
	return ((Enable) ? TRUE : FALSE);
}

//落下ブロックのインターバルの取得(落下中の場合は-1が返ります)
int Block_Fall::getInterval() {
	if (isEnable())	return -1;
	return -Counter;
}


//落下ブロックをX軸方向に移動(戻り値は実際の移動量)
int Block_Fall::FallBlock_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isEnable())		return 0;	//そもそも落下中で無い時は無視

	MoveVal = getFallBlockVal_MoveX(MoveVal, CollisionFieldBlock);

	//ずらしの反映
	PlaceX += MoveVal;

	return MoveVal;
}

//落下ブロックがX軸方向に移動可能かどうかの取得(|移動出来る量|<=MoveVal)(つまり0で移動不可)
int Block_Fall::getFallBlockVal_MoveX(int MoveVal, int CollisionFieldBlock) {
	if (!isEnable())		return FALSE;	//そもそも落下中で無い時は移動不可

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
		if (Minus)	pX = PlaceX - (i + 1);	//負の方向
		else		pX = PlaceX + (i + 1);	//正の方向

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {
					//ブロック有りの場合、フィールドブロックとの重なりを確認する
					if (CollisionFieldBlock) {//フィールドブロックとのあたり判定を有効にする場合
						if (phase_GameMain.getBlockColor(pX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//他のブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
					}
					else {
						if (phase_GameMain.getBlockColor(pX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
							//画面外ブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
					}
				}
			}
		}
	}
	//符号を元に戻す
	if (Minus) {
		MoveVal = -MoveVal;
	}

	return MoveVal;
}

//落下ブロックをY軸方向に移動(戻り値は実際の移動量)
int Block_Fall::FallBlock_MoveY(int MoveVal, int CollisionFieldBlock) {
	if (!isEnable())		return 0;	//そもそも落下中で無い時は無視

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
		if (Minus)	pY = PlaceY - (i + 1);	//負の方向
		else		pY = PlaceY + (i + 1);	//正の方向

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (CollisionFieldBlock) {//フィールドブロックとのあたり判定を有効にする場合
						if (phase_GameMain.getBlockColor(PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
							//他のブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
					}
					else {
						if (phase_GameMain.getBlockColor(PlaceX + (x - FALLBLOCK_CENTER), pY + (y - FALLBLOCK_CENTER), TRUE) == BLOCK_TYPE_NUM) {
							//画面外ブロックと重なっていた場合はループを抜ける
							x = FALLBLOCK_SIZE;
							y = FALLBLOCK_SIZE;
							MoveVal = i;//最外のループも抜ける
						}
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
	PlaceY += MoveVal;

	return MoveVal;
}

//落下ブロックを回転させる(回転量1で時計回りに90度)(戻り値は実際の回転量)
int Block_Fall::FallBlock_Rotate(int RotaVal) {
	if (!isEnable())		return 0;	//そもそも落下中で無い時は無視

	if (Flag_Rotate == FALSE)	return 0;//回転が無効の場合は回転しない

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
		Block RotaBlockID[FALLBLOCK_SIZE][FALLBLOCK_SIZE];
		if (Minus) {//反時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[y][(FALLBLOCK_SIZE - 1) - x] = BlockID[x][y];
				}
			}
		}
		else {//時計回りに90度
			for (int x = 0; x < FALLBLOCK_SIZE; x++) {
				for (int y = 0; y < FALLBLOCK_SIZE; y++) {
					RotaBlockID[(FALLBLOCK_SIZE - 1) - y][x] = BlockID[x][y];
				}
			}
		}

		//他のブロックとの重なりを計算する(枠外もブロックがあると考える)
		for (int x = 0; x < FALLBLOCK_SIZE; x++) {
			for (int y = 0; y < FALLBLOCK_SIZE; y++) {
				if (RotaBlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {//ブロック有りの場合、ブロックの重なりを確認する
					if (phase_GameMain.getBlockColor(PlaceX + (x - FALLBLOCK_CENTER), PlaceY + (y - FALLBLOCK_CENTER), TRUE) != BLOCK_TYPE_NO) {
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
					BlockID[x][y] = RotaBlockID[x][y];
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
void Block_Fall::FallBlock_addField() {
	if (!isEnable())	return;	//そもそも有効で無い時は無視

	//何も無しブロック以外はフィールドブロックに順次変換を行う
	for (int x = 0; x < FALLBLOCK_SIZE; x++) {
		for (int y = 0; y < FALLBLOCK_SIZE; y++) {
			if (BlockID[x][y].getBlockType() != BLOCK_TYPE_NO) {
				int fX, fY;		//ブロックのフィールド上の位置
				BLOCK_TYPE fB;	//設置するブロックの種類
				fX = PlaceX + (x - FALLBLOCK_CENTER);
				fY = PlaceY + (y - FALLBLOCK_CENTER);
				fB = BlockID[x][y].getBlockType();

				phase_GameMain.add_FraldBlock2(fX, fY, fB);

			}
		}
	}
	printLog_I(_T("落下ブロックの【設置】"));

	//落下ブロックの無効化処理
	Delete_FallBlock();

}

//落下ブロックの無効化
void Block_Fall::Delete_FallBlock() {
	if (!isEnable())	return;	//そもそも有効で無い時は無視

	Counter = 0;		//カウンタを0にもどす
	Enable = FALSE;		//落下ブロックの無効化

	printLog_I(_T("落下ブロックの【消去】"));
}

//落下ブロックを生成する(戻り値:成功でTRUE)
int Block_Fall::Create_FallBlock() {

	if (isEnable()) {
		printLog_C(_T("落下中のブロックがすでに存在するため、落下ブロックを新たに追加出来ませんでした"));
		return FALSE;
	}

	//ブロック待機列の先頭の要素から生成する

	//ブロック情報のコピー
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			BlockID[i][j] = waitBlockinfo[0].BlockID[i][j];
		}
	}

	//拡張設定のコピー
	PlaceX = waitBlockinfo[0].PlaceX;
	PlaceY = waitBlockinfo[0].PlaceY;
	Flag_Rotate = waitBlockinfo[0].Flag_Rotate;


	//落下カウントを60に設定
	FallCount = 60;

	//落下ブロックのその他の情報の初期化
	Counter = 0;
	Key_LRMove = 0;
	Key_LRRota = 0;
	Key_FlagFirstFall = FALSE;

	//描画情報を書き換える
	double paddingX, paddingY;
	phase_GameMain.getAllPadding(&paddingX, &paddingY);
	Update_DrawData(paddingX, paddingY);



	//有効
	Enable = TRUE;

	printLog_I(_T("落下ブロックの【新規生成】"));

	//ブロック待機列を進める
	Create_Wait_Block();

	return TRUE;
}

//落下ブロックの待機列の作成
void Block_Fall::Create_Wait_Block() {

	//列を詰める(先頭は0)
	for (int i = 0; i < ARRAY_LENGTH(waitBlockinfo) - 1; i++) {
		waitBlockinfo[i] = waitBlockinfo[i + 1];
	}



	//新規に作成する落下ブロックの配置パターンを決定する(0～)
	const int Percent = (int)(phase_GameMain.getRandomTable()->getRand(0, 100));
	int Pattern = 0;	//ブロックのパターン
	if (Percent < 24) {
		Pattern = 0;
	}
	else if (Percent < 48) {
		Pattern = 1;
	}
	else if (Percent < 72) {
		Pattern = 2;
	}
	else if (Percent < 96) {
		Pattern = 3;
	}
	else {
		Pattern = 4;
	}

	//ランダムに設置するブロックを2個決定する
	BLOCK_TYPE type1 = phase_GameMain.GetRandomBlockType_FALL();
	BLOCK_TYPE type2 = phase_GameMain.GetRandomBlockType_FALL();

	//最後尾待機ブロックの配置を初期化する
	for (int i = 0; i < FALLBLOCK_SIZE; i++) {
		for (int j = 0; j < FALLBLOCK_SIZE; j++) {
			waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[i][j].Delete_Block();
		}
	}

	//ブロックの特殊効果を設定する
	waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = TRUE;


	//先に決めたパターンよりブロックの配置を決定する(ついでにスポーン位置も)
	switch (Pattern) {
	case 0://縦で下側中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][0].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP + 1;
		//printLog_D(_T("縦で下側中心パターン"));
		break;
	case 1://縦で上側中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][2].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("縦で上側中心パターン"));
		break;
	case 2://横で左中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[2][1].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("横で左中心パターン"));
		break;
	case 3://横で右中心パターン
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[0][1].addBlcok(type1, TRUE);
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(type2, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//printLog_D(_T("横で右中心パターン"));
		break;
	case 4://同色爆弾の単体落下
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].BlockID[1][1].addBlcok(BLOCK_TYPE_BOM_Color, TRUE);

		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceX = BLOCK_WIDTHNUM / 2;
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].PlaceY = BLOCK_PADDINGUP;
		//無条件で回転不可
		waitBlockinfo[ARRAY_LENGTH(waitBlockinfo) - 1].Flag_Rotate = FALSE;
		break;
	default:
		printLog_E(_T("落下ブロック配置パターンが不明です"));
		break;
	}


	printLog_I(_T("ブロックの待機列を進めました"));
}

