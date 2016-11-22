#include "Field_Admin.h"
#include "MainFunc.h"

//フィールドブロック統括クラス

//初期化(描画処理)
void Field_Admin::Init_Draw() {
	//全フィールドブロックの初期化を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Init_Draw();
		}
	}
}

//初期化(計算処理)
void Field_Admin::Init_Update() {
	//全フィールドブロックの初期化を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Init_Update();
		}
	}
}

//リスタート処理
void Field_Admin::Restart() {
	//全フィールドブロックのリスタート処理を行う
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].Restart();
		}
	}

	//適当にブロックを設置する(下から複数段)
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN - BLOCK_DEFAULT_VAL, BLOCK_WIDTHNUM_INGAME, BLOCK_DEFAULT_VAL);

	//仮想ブロックの更新を行う
	Virtualfield_Update();

	//レーザーエフェクトの初期化
	Count_lay = 0;
	lay.SetpointNum(0);
}


/*基本処理*/
//ブロック描画処理
void Field_Admin::Draw_Block() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {

			////ゲームオーバー時に下に落下させる
			//if (getPauseMode() == PauseMode_GameOver) {
			//	if (Count_Pause < 300)	Y += 1 / 2.*0.2*Count_Pause*Count_Pause;
			//	else					Y += 1 / 2.*0.2 * 300 * 300;
			//}

			field[x][y].Draw();
		}
	}
}

//レーザーエフェクト描画処理
void Field_Admin::Draw_Lay() {
	//破壊光線の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawPolygon2D_Notexture2(&lay, GetColor(200, 200, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//移動モーションの更新(移動モーションが行われたときはTRUE)
int Field_Admin::Update_MoveMotion() {
	int count = 0;//移動モーションが有効な数

	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].getMoveMotion()->Update();
			if (field[x][y].getMoveMotion()->isEnable())	count++;//有効な場合は加算
		}
	}

	return ((count > 0) ? TRUE : FALSE);
}

//変化モーションの更新(変化モーションが行われたときはTRUE)
int Field_Admin::Update_ChangeMotion() {
	int count = 0;//移動処理を行ったブロックの数

				  //変化モーションのカウントアップ
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			field[x][y].getChangeMotion()->Update();
			if (field[x][y].getChangeMotion()->isEnable())	count++;
		}
	}
	return ((count > 0) ? TRUE : FALSE);
}

//全体移動の更新(TRUE全体移動の更新が終わった瞬間)
int Field_Admin::Update_AllMove() {
	if (!AllMovedata.isEnable())	return FALSE;

	//ブロック全体移動が有効な場合は、通常の処理を実行せず、全体移動のカウントアップのみ行うようにする
	AllMovedata.Update();
	if (AllMovedata.isEnable() == FALSE) {
		//移動完了の時
		int ToX, ToY;
		AllMovedata.getToPoint(&ToX, &ToY);	//移動先に設定した座標を取得する
		AllMove(ToX, ToY);					//ブロック全体を移動する
		return TRUE;
	}

	return FALSE;
}

//破壊光線エフェクトの更新
void Field_Admin::Update_Lay() {
	if (lay.getpointNum() == 3) {
		Count_lay++;
		if (Count_lay < 15) {
			//何もしない
		}
		else if (Count_lay < 45) {
			//フレーム数の割合から位置を計算する
			lay.X[1] = GAMEWINDOW_WIDTH * ((Count_lay - 15) / 30.);
			lay.X[2] = GAMEWINDOW_WIDTH * ((Count_lay - 15) / 30.);
		}
		else if (Count_lay < 55) {
			lay.X[1] = GAMEWINDOW_WIDTH;
			lay.X[2] = GAMEWINDOW_WIDTH;
		}
		else {
			lay.SetpointNum(0);
		}
	}
}

//描画情報の更新
void Field_Admin::Update_DrawData() {
	double Field_PaddingX, Field_PaddingY;
	getField_Padding(&Field_PaddingX, &Field_PaddingY);

	//フィールドブロックの座標計算
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			//描画先の座標を計算する
			field[x][y].Update_DrawData(Field_PaddingX, Field_PaddingY, x, y);
		}
	}
}

//キー処理
void Field_Admin::key() {
	if (AllMovedata.isEnable())	return;//全体移動が有効な場合は処理をしない

	if (getKeyBind(KEYBIND_UP) == 1) {
		//ブロックの設置
		//自殺防止
		int Flag = TRUE;//死亡領域にブロックがあったらFALSEになる
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < GAMEOVER_BORDER + 1; y++) {
				if (getBlockType(x, y) != BLOCK_TYPE_NO) {
					//なんかブロックがある場合
					Flag = FALSE;
					break;
				}
			}
		}
		if (Flag)	add_Under();//上にブロックがない場合に実行される
	}
}


/*ブロックに変更を加える系*/
//指定したエリアにブロックを設置する(消去判定が入らないように設置します)
void Field_Admin::setBlock_Rect(int x, int y, int w, int h) {
	//仮想フィールド情報を更新する
	Virtualfield_Update();

	for (int bl_X = x; bl_X < x + w; bl_X++) {
		for (int bl_Y = y; bl_Y < y + h; bl_Y++) {
			BLOCK_TYPE bt;
			int Count = 0;

			do {
				Count = 0;
				bt = phase_GameMain.GetRandomBlockType_UNDER();//ランダムでブロックを決定し仮想設置する
				add_FieldBlock(bl_X, bl_Y, bt, TRUE, TRUE, NULL, TRUE);
				int BlockFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
				//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
				CreateSequenceCountTable(BlockFlag, 0, 0, BLOCK_WIDTHNUM, BLOCK_HEIGHTNUM, TRUE);
				SequenceCount(bl_X, bl_Y, 0, BlockFlag, &Count, TRUE);
			} while (Count >= BLOCK_DELETE_LEN);

			add_FieldBlock(bl_X, bl_Y, bt, FALSE, TRUE);//本番の設置
		}
	}
}

//フィールドにブロックを設置する
int Field_Admin::add_FieldBlock(int X, int Y, BLOCK_TYPE type, int Override, int OutScreen, BLOCK_TYPE *Before, int UseVirtualField) {
	//前に設置されていたブロックの情報を初期化する
	if (Before != NULL)	*Before = BLOCK_TYPE_NO;

	//現在設置されているブロックが画面外ブロック(つまり範囲外の座標が渡された)場合は何もしない
	if (getBlockType(X, Y, TRUE, !OutScreen, UseVirtualField) == BLOCK_TYPE_NUM)	return FALSE;

	//ブロックの設置を行う
	const int ans = ((UseVirtualField) ? Virtualfield[X][Y] : field[X][Y]).addBlcok(type, Override, Before);

	if (ans) {//ブロックの設置に成功した場合
		if (UseVirtualField)	printLog_I(_T("[仮想]フィールドブロック【新規生成】[%d][%d](type=%d)"), X, Y, type);
		else				printLog_I(_T("フィールドブロック【新規生成】[%d][%d](type=%d)"), X, Y, type);
	}

	return ans;
}

//下からブロックがわいてくる
void Field_Admin::add_Under() {
	if (AllMovedata.isEnable())	return;//すでに実行中の場合は処理をしない
	setBlock_Rect(BLOCK_PADDINGLEFT, BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN, BLOCK_WIDTHNUM_INGAME, 1);
	AllMoveRequest(0, -1);	//ブロック全体を移動
}

//フィールド全体のブロックを指定した分だけ移動する(画面外に出てしまうブロックは消滅します)
void Field_Admin::AllMove(int X, int Y) {
	//処理に無駄が多い…

	//左上移動
	if (X <= 0 && Y <= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を左上にずらしました(%d,%d)"), X, Y);
	}
	//左下移動
	else if (X <= 0 && Y >= 0) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を左下にずらしました(%d,%d)"), X, Y);
	}
	//右上移動
	else if (X >= 0 && Y <= 0) {
		for (int x = BLOCK_WIDTHNUM - 1; x >= 0; x--) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を右上にずらしました(%d,%d)"), X, Y);
	}
	//右下移動
	else if (X >= 0 && Y >= 0) {
		for (int x = BLOCK_WIDTHNUM - 1; x >= 0; x--) {
			for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
				if (0 <= x - X && x - X < BLOCK_WIDTHNUM && 0 <= y - Y && y - Y < BLOCK_HEIGHTNUM) {
					//範囲内なら普通にコピーする
					field[x][y] = field[x - X][y - Y];
					field[x][y].getMoveMotion()->Slide(X, Y);//移動モーションに補正をかける
				}
				else {
					//範囲外ならブロックの消去
					Delete_Direct(x, y);
				}
			}
		}
		printLog_I(_T("ブロック全体を右下にずらしました(%d,%d)"), X, Y);
	}

	//落下中ブロックも移動する(画面外には行きません)
	phase_GameMain.getfallBlockInfo()->MoveX(X, FALSE);
	phase_GameMain.getfallBlockInfo()->MoveY(Y, FALSE);

}

//フィールドブロックを直接削除する(削除されたらTRUE)
int Field_Admin::Delete_Direct(int X, int Y, BlockChangeMotionType PlayMotion, int Delay) {
	//現在のブロックの種類の取得(削除前)
	BLOCK_TYPE bt = getBlockType(X, Y, FALSE, FALSE);	//削除されるブロックの種類
	if (bt == BLOCK_TYPE_NO)	return FALSE;//ブロックがそもそも存在しない場合は何もしない
											 //ブロックの削除を行う


	int flag = field[X][Y].Delete_Block();

	if (flag) {
		//ブロックが削除された
		if (PlayMotion == BlockChangeMotionType_EXPLOSION) {
			SetChangeMotion_EXPLOSION(X, Y, bt, Delay);	//モーションの生成
		}
		else if (PlayMotion == BlockChangeMotionType_SMALL) {
			SetChangeMotion_SMALL(X, Y, bt, Delay);	//モーションの生成
		}
	}

	return ((flag) ? TRUE : FALSE);
}

//指定した座標が指定したブロックだった場合に削除(削除されたらTRUE)
int Field_Admin::Delete_Color(int X, int Y, BLOCK_TYPE type, BlockChangeMotionType PlayMotion) {
	if (!Block::isSameColorBlock(type, getBlockType(X, Y), FALSE))	return FALSE;//違う色のブロックの場合は削除しない

	return Delete_Direct(X, Y, PlayMotion);
}

//破壊光線でブロックを破壊する
void Field_Admin::Delete_Lay() {
	//レーザーのエフェクトを初期化する
	lay.SetpointNum(3);	//三角形を設定
	lay.X[0] = GAMEWINDOW_WIDTH / 2.;
	lay.Y[0] = 0 + BLOCK_SIZE * BLOCK_PADDINGUP;
	lay.X[1] = 0;
	lay.Y[1] = BLOCK_SIZE * 3 + BLOCK_SIZE * BLOCK_PADDINGUP;
	lay.X[2] = 0;
	lay.Y[2] = BLOCK_SIZE * 12 + BLOCK_SIZE * BLOCK_PADDINGUP;
	Count_lay = 0;

	//エフェクト範囲のブロックを抹消する
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		for (int y = BLOCK_PADDINGUP + 3; y < BLOCK_PADDINGUP + 12; y++) {
			Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION, x * 2 + 15);
		}
	}

	//スコアを減らす
	phase_GameMain.getScore()->addScore(1, -1'0000);
}

//連続するフィールドブロックを削除する(ついでに消去によって発動する効果も発動する)(消去したブロックの数)
int Field_Admin::Delete_Join(const int Len, int Flag_Event) {

	int DeleteBlockFlag = FALSE;	//削除されたらTRUE

									//画面内の存在するブロックのみで計算する
	int DeleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	CreateSequenceCountTable(DeleteFlag, BLOCK_PADDINGLEFT, BLOCK_PADDINGUP, BLOCK_WIDTHNUM_INGAME, BLOCK_HEIGHTNUM_INGAME);

	//削除前のブロックの一覧を作成する
	BLOCK_TYPE old[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM];
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			old[x][y] = getBlockType(x, y);
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

	//矢印ブロックの効果を先に発動する
	int DelCount = 0;
	if (Flag_Event) {
		for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
			for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
				if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
					if (Counter[DeleteFlag[x][y]] >= Len) {
						//水平の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_X ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_X ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_X ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_X ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_X) {
							//左端から右端までの一列を一括消去
							for (int i = 0; i < BLOCK_WIDTHNUM; i++) {
								if (Delete_Direct(i, y, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//フライテキストの生成
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(i, y, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
							}
						}
						//垂直の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_Y ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_Y) {
							//左端から右端までの一列を一括消去
							for (int i = 0; i < BLOCK_HEIGHTNUM; i++) {
								if (Delete_Direct(x, i, BlockChangeMotionType_EXPLOSION, abs(y - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//フライテキストの生成
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x, i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
							}
						}
						//右上の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_XY ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_XY) {
							//斜めに一括消去
							for (int i = 0; i < max(BLOCK_HEIGHTNUM, BLOCK_WIDTHNUM); i++) {
								if (Delete_Direct(x + i, y - i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//フライテキストの生成
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x + i, y - i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
								if (Delete_Direct(x - i, y + i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//フライテキストの生成
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x - i, y + i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
							}
						}
						//右下の矢印の場合
						if (old[x][y] == BLOCK_TYPE_BLUE_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_GREEN_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_PURPLE_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_RED_ARROW_XY2 ||
							old[x][y] == BLOCK_TYPE_YELLOW_ARROW_XY2) {
							//斜めに一括消去
							for (int i = 0; i < max(BLOCK_HEIGHTNUM, BLOCK_WIDTHNUM); i++) {
								if (Delete_Direct(x + i, y + i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//フライテキストの生成
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x + i, y + i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
								if (Delete_Direct(x - i, y - i, BlockChangeMotionType_EXPLOSION, abs(x - i) * 2)) {
									phase_GameMain.getScore()->addScore(0, SCORE_DEL_ARROW);
									DelCount++;
									DeleteBlockFlag = TRUE;
									//フライテキストの生成
									double X, Y;
									TCHAR text[30];
									Block_Field::Convert_Ingame_FromBlock(x - i, y - i, 0.5, 0.5, &X, &Y);
									_stprintf_s(text, _T("%d"), SCORE_DEL_ARROW);
									phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
								}
							}
						}
					}
				}
			}
		}
		//この時点で削除があった(つまり矢印ブロックで消された)
		if (DelCount > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
	}


	BlockChangeMotionType DelMotion = BlockChangeMotionType_SMALL;
	if (!Flag_Event) {
		DelMotion = BlockChangeMotionType_EXPLOSION;
	}
	//隣接しているブロックを削除する
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (0 <= DeleteFlag[x][y] && DeleteFlag[x][y] < ARRAY_LENGTH(Counter)) {//配列の範囲内
				if (Counter[DeleteFlag[x][y]] >= Len) {
					//削除
					if (Delete_Direct(x, y, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_NOMAL);
						DelCount++;
						DeleteBlockFlag = TRUE;
						//フライテキストの生成
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x, y, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}

					//ついでに隣接する樹木ブロックも削除
					if (Delete_Color(x, y - 1, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//上
						DeleteBlockFlag = TRUE;
						//フライテキストの生成
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x, y - 1, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_OPTION);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
					if (Delete_Color(x, y + 1, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//下
						DeleteBlockFlag = TRUE;
						//フライテキストの生成
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x, y + 1, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
					if (Delete_Color(x - 1, y, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//左
						DeleteBlockFlag = TRUE;
						//フライテキストの生成
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x - 1, y, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
					if (Delete_Color(x + 1, y, BLOCK_TYPE_TREE, DelMotion)) {
						phase_GameMain.getScore()->addScore(0, SCORE_DEL_OPTION);
						DelCount++;//右
						DeleteBlockFlag = TRUE;
						//フライテキストの生成
						double X, Y;
						TCHAR text[30];
						Block_Field::Convert_Ingame_FromBlock(x + 1, y, 0.5, 0.5, &X, &Y);
						_stprintf_s(text, _T("%d"), SCORE_DEL_NOMAL);
						phase_GameMain.getFlyText()->addFlyText(X, Y, 30, FONTTYPE_SFSquareHeadCondensed_Edge25, GetColor(150, 150, 150), text);
					}
				}
			}
		}
	}

	printLog_I(_T("隣接ブロックの削除計算を行いました(%dブロック)"), DelCount);

	if (DeleteBlockFlag) {
		//ブロックの消去判定が入れば
		ChainCount++;	//連鎖カウントを加算する
	}

	return DelCount;
}

//画面外のブロックをすべて削除する(消去したブロックの数)
int Field_Admin::Delete_OutScreen() {
	int count = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (getBlockType(x, y, TRUE, TRUE) == BLOCK_TYPE_NUM) {
				//画面外ブロックの場合は削除
				if (Delete_Direct(x, y)) {
					count++;
				}
			}
		}
	}

	printLog_I(_T("画面外のブロックをすべて削除(%d個)"), count);
	return count;
}


//仮想フィールドを現在のフィールドと一致させる
void Field_Admin::Virtualfield_Update() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			Virtualfield[x][y] = field[x][y];
		}
	}
	printLog_I(_T("仮想フィールドを更新しました"));
}

//フィールド全体のブロックを指定した分だけ移動するリクエストをする(ゲームを一時停止して動かします)
void Field_Admin::AllMoveRequest(int X, int Y) {
	if (AllMovedata.isEnable())	return;//すでにブロックが移動中の場合、無視する

	AllMovedata.Create(0, 0, X, Y, 0.1, 2);

	printLog_I(_T("ブロック全体移動が設定されました(%d,%d)"), X, Y);
}

//フィールドに存在する黒色ブロックの色を決定する
void Field_Admin::Func_Black() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BLACK) {//黒ブロックの時
				//確率でブロックのIDを書き換える
				int Val = (int)phase_GameMain.getRandomTable()->getRand(0, 100);
				if (Val < 20)		field[x][y].addBlcok(BLOCK_TYPE_RED, TRUE);		//赤色ブロック
				else if (Val < 40)	field[x][y].addBlcok(BLOCK_TYPE_BLUE, TRUE);	//青色ブロック
				else if (Val < 60)	field[x][y].addBlcok(BLOCK_TYPE_YELLOW, TRUE);	//黄色ブロック
				else if (Val < 80)	field[x][y].addBlcok(BLOCK_TYPE_GREEN, TRUE);	//緑色ブロック
				else 				field[x][y].addBlcok(BLOCK_TYPE_PURPLE, TRUE);	//紫色ブロック

				SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_BLACK, 0);	//変化モーションの設定
			}
		}
	}
}

//フィールドに存在する虹色ブロックの色を決定する(下から順に)
void Field_Admin::Func_Rainbow() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = BLOCK_HEIGHTNUM - 1; y >= 0; y--) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_RAINBOW) {//虹色ブロックの時
				if (getBlockType(x, y + 1) == BLOCK_TYPE_NO) {//下にブロックが無い
					
					//確率でブロックのIDを書き換える
					int Val = (int)phase_GameMain.getRandomTable()->getRand(0, 100);
					if (Val < 20)		field[x][y].addBlcok(BLOCK_TYPE_RED, TRUE);		//赤色ブロック
					else if (Val < 40)	field[x][y].addBlcok(BLOCK_TYPE_BLUE, TRUE);	//青色ブロック
					else if (Val < 60)	field[x][y].addBlcok(BLOCK_TYPE_YELLOW, TRUE);	//黄色ブロック
					else if (Val < 80)	field[x][y].addBlcok(BLOCK_TYPE_GREEN, TRUE);	//緑色ブロック
					else 				field[x][y].addBlcok(BLOCK_TYPE_PURPLE, TRUE);	//紫色ブロック
				}
				else {
					//下にブロックがある場合
					field[x][y].addBlcok(getBlockType(x, y + 1), TRUE);
				}
				//変化モーションの設定
				SetChangeMotion_NOMAL_From(x, y, BLOCK_TYPE_RAINBOW, 0);
			}
		}
	}
}

//フィールドに存在する爆弾ブロックを爆破する
void Field_Admin::Func_BOMB() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BOM) {//爆弾ブロックの時
															   //自身の削除
				if (Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION))	DeleteNum++;

				//周囲のブロックを削除する(爆弾ブロックは削除しない)
				if (getBlockType(x + 1, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 1, y, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x + 2, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 2, y, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}
				if (getBlockType(x - 1, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 1, y, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x - 2, y) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 2, y, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}
				if (getBlockType(x, y + 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y + 1, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x, y + 2) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y + 2, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}
				if (getBlockType(x, y - 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y - 1, BlockChangeMotionType_EXPLOSION, 5))	DeleteNum++;
				}
				if (getBlockType(x, y - 2) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x, y - 2, BlockChangeMotionType_EXPLOSION, 15))	DeleteNum++;
				}


				if (getBlockType(x - 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 1, y - 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
				if (getBlockType(x + 1, y - 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 1, y - 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
				if (getBlockType(x + 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x + 1, y + 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
				if (getBlockType(x - 1, y + 1) != BLOCK_TYPE_BOM) {
					if (Delete_Direct(x - 1, y + 1, BlockChangeMotionType_EXPLOSION, 10))	DeleteNum++;
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//フィールドに存在する2爆弾ブロックを爆破する
void Field_Admin::Func_2BOMB() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_2BOM) {//爆弾ブロックの時
																//自身の削除
				if (Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION))	DeleteNum++;

				//2個隣接しているブロックを破壊する
				DeleteNum += Delete_Join(2, FALSE);
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//フィールドに存在する同色爆弾ブロックを爆破する
void Field_Admin::Func_BOMBColor() {
	int DeleteNum = 0;
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getBlockType() == BLOCK_TYPE_BOM_Color) {//爆弾ブロックの時
																	 //自身の削除
				if (Delete_Direct(x, y, BlockChangeMotionType_EXPLOSION))	DeleteNum++;
				//真下のブロックの色を取得する
				BLOCK_TYPE under = getBlockType(x, y + 1);

				//同色ブロックを削除する
				for (int x2 = BLOCK_PADDINGLEFT; x2 < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x2++) {
					for (int y2 = BLOCK_PADDINGUP; y2 < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y2++) {
						Delete_Color(x2, y2, under, BlockChangeMotionType_EXPLOSION);
					}
				}
			}
		}
	}

	if (DeleteNum > 0)	SoundEffect_Play(SE_TYPE_Smallexplosion);
}

//フィールドブロックを重力で落下させる
void Field_Admin::Gravity(int InGameOnly) {
	int sX = 0, sY = 0;
	int eX = BLOCK_WIDTHNUM, eY = BLOCK_HEIGHTNUM;

	if (InGameOnly) {
		sX = BLOCK_PADDINGLEFT;
		sY = BLOCK_PADDINGUP;

		eX = BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT;
		eY = BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;
	}

	for (int x = sX; x < eX; x++) {
		//列ごとにブロック情報をコピーする
		Block_Field t[BLOCK_HEIGHTNUM];
		for (int y = sY; y < eY; y++) {
			t[y] = field[x][y];
			field[x][y].Delete_Block();	//いったんフィールドのブロック情報を削除する
		}
		int Count = eY - 1;
		//下の段から存在するブロックを並べ直す(逆順回し)
		for (int y = eY - 1; y >= sY; y--) {
			if (t[y].getBlockType() != BLOCK_TYPE_NO) {
				field[x][Count] = t[y];
				//落下モーション(カウントが移動先、yが移動元になる)
				SetMoveMotion(x, Count, x, y, x, Count, 0.3, 15);
				Count--;
			}
		}
	}

	printLog_I(_T("ブロックに重力計算を行いました"));
}

/*モーション設定関係*/
//フィールドのブロックに変化モーションを設定する(これ単体で使用して事故っても知りません)
void Field_Admin::SetChangeMotion(int x, int y, BlockChangeMotionType mtype, BLOCK_TYPE From, BLOCK_TYPE To, int MotionLength, int Delay) {
	if (getBlockType(x, y, TRUE, FALSE) == BLOCK_TYPE_NUM)	return;	//ブロックが画面外の場合は処理をしない

	int ans = field[x][y].getChangeMotion()->Create(mtype, From, To, MotionLength, Delay);

	if (ans)	printLog_I(_T("ブロックに【変化モーション】を設定[%d][%d]"), x, y);
}

//フィールドのブロックに変化モーション(通常)を設定する
void Field_Admin::SetChangeMotion_NOMAL(int x, int y, BLOCK_TYPE To, int Delay) {

	BLOCK_TYPE From = getBlockType(x, y, FALSE, FALSE);

	if (From == To)				return;		//変化先が同じ場合は処理をしない
	if (To == BLOCK_TYPE_NO)	return;		//変化先がブロック無しの場合は処理をしない(正しく描画出来ないため)

	const int MotionLength = 20;
	SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, From, To, MotionLength, Delay);
}

//フィールドのブロックに変化モーション(通常)を設定する(変化元指定)
void Field_Admin::SetChangeMotion_NOMAL_From(int x, int y, BLOCK_TYPE from, int Delay) {

	BLOCK_TYPE To = getBlockType(x, y, FALSE, FALSE);
	if (from == To)				return;		//変化先が同じ場合は処理をしない
	if (To == BLOCK_TYPE_NO)	return;		//変化先がブロック無しの場合は処理をしない(正しく描画出来ないため)

	const int MotionLength = 20;
	SetChangeMotion(x, y, BlockChangeMotionType_NOMAL, from, To, MotionLength, Delay);
}


//フィールドのブロックに変化モーション(爆発)を設定する
void Field_Admin::SetChangeMotion_EXPLOSION(int x, int y, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//ブロックが存在しない場合は無視


	const int MotionLength = 40;
	SetChangeMotion(x, y, BlockChangeMotionType_EXPLOSION, From, From, MotionLength, Delay);
}

//フィールドのブロックに変化モーション(小さくなって消える)を設定する
void Field_Admin::SetChangeMotion_SMALL(int x, int y, BLOCK_TYPE From, int Delay) {
	if (From == BLOCK_TYPE_NO)	return;//ブロックが存在しない場合は無視


	const int MotionLength = 15;
	SetChangeMotion(x, y, BlockChangeMotionType_SMALL, From, From, MotionLength, Delay);
}

//フィールドのブロック移動にモーションを設定する
void Field_Admin::SetMoveMotion(int x, int y, int FromX, int FromY, int ToX, int ToY, double a, double MaxSpeed) {
	if (getBlockType(x, y, FALSE, FALSE) == BLOCK_TYPE_NO)	return;	//ブロックが無効の場合は処理をしない

	int ans = field[x][y].getMoveMotion()->Create(FromX, FromY, ToX, ToY, a, MaxSpeed);

	if (ans)	printLog_I(_T("ブロックに【移動モーション】を設定(%d,%d)"), x, y);
}


/*隣接個数計算関係*/
//隣接する同色ブロックにマーカーを付ける
void Field_Admin::SequenceCount(int x, int y, int ID, int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int *Counter, int UseVirtualField) {
	if (deleteFlag == NULL)		return;		//マーカーを付けるテーブルがない場合
	if (deleteFlag[x][y] != -1)	return;		//未探索ブロックじゃない場合
	BLOCK_TYPE bt = ((UseVirtualField) ? Virtualfield[x][y].getBlockType() : field[x][y].getBlockType());	//ブロックの種類を記録する
	deleteFlag[x][y] = ID;	//探索済み(探索IDを設定する)
	(*Counter)++;

	int OnlyColor = TRUE;

	BLOCK_TYPE NextBlock = ((UseVirtualField) ? Virtualfield[x + 1][y] : field[x + 1][y]).getBlockType();
	if (x + 1 < BLOCK_WIDTHNUM	&& Block::isSameColorBlock(NextBlock, bt, OnlyColor))		SequenceCount(x + 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y + 1] : field[x][y + 1]).getBlockType();
	if (y + 1 < BLOCK_HEIGHTNUM	&& Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y + 1, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x - 1][y] : field[x - 1][y]).getBlockType();
	if (x - 1 >= 0 && Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x - 1, y, ID, deleteFlag, Counter);

	NextBlock = ((UseVirtualField) ? Virtualfield[x][y - 1] : field[x][y - 1]).getBlockType();
	if (y - 1 >= 0 && Block::isSameColorBlock(NextBlock, bt, OnlyColor))	SequenceCount(x, y - 1, ID, deleteFlag, Counter);
}

//SequenceCountで使用するマーカーテーブルを作成する(有効なエリア)(UseVirtualField=TRUEで仮想の面を使用する)
void Field_Admin::CreateSequenceCountTable(int deleteFlag[BLOCK_WIDTHNUM][BLOCK_HEIGHTNUM], int X, int Y, int W, int H, int UseVirtualField) {
	if (deleteFlag == NULL)	return;

	//隣接ブロック識別IDを記録する表の作成(-1未探索、BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM探索から除外)
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			const BLOCK_TYPE type = getBlockType(x, y, FALSE, FALSE, UseVirtualField);	//ブロックの種類を取得する
			if (!(X <= x && x < X + W && Y <= y && y < Y + H) ||	//範囲外
				type == BLOCK_TYPE_NO ||
				type == BLOCK_TYPE_NUM ||
				type == BLOCK_TYPE_TREE ||
				type == BLOCK_TYPE_BLACK ||
				type == BLOCK_TYPE_RAINBOW ||
				type == BLOCK_TYPE_BOM ||
				type == BLOCK_TYPE_2BOM ||
				type == BLOCK_TYPE_BOM_Color) {		//除外ブロック
				deleteFlag[x][y] = BLOCK_WIDTHNUM*BLOCK_HEIGHTNUM;
			}
			else {
				deleteFlag[x][y] = -1;
			}
		}
	}
}

//ブロックのチェイン数をリセットする
void Field_Admin::ChainCount_Reset() {
	ChainCount = 0;
	printLog_I(_T("チェイン数をリセットしました"));
}


/*取得系*/
//指定した座標のブロックの取得(第3引数は画面外をブロックとして判定するかどうかTRUE判定)(第4引数は実際に描画されるエリア以外を画面外にする場合TRUE,ブロック情報が無い位置を画面外にする場合はFALSEを設定する)
BLOCK_TYPE Field_Admin::getBlockType(int X, int Y, int useOutScreenBlock, int InGame, int UseVirtualField) {

	//画面外処理
	if (InGame) {
		//実際の描画エリアで判定
		if (X < BLOCK_PADDINGLEFT || (BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT) <= X)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
		if (Y < BLOCK_PADDINGUP || (BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN) <= Y)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
	}
	else {
		//フィールド情報から判定する
		if (X < 0 || BLOCK_WIDTHNUM <= X)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
		if (Y < 0 || BLOCK_HEIGHTNUM <= Y)	return (useOutScreenBlock) ? BLOCK_TYPE_NUM : BLOCK_TYPE_NO;
	}

	return ((UseVirtualField) ? Virtualfield[X][Y] : field[X][Y]).getBlockType();
}

//ブロック全体移動クラスのポインタを取得
BlockMoveMotion *Field_Admin::getBlockMoveMotion() {
	return &AllMovedata;
}

//フィールド全体のズレを取得する
void Field_Admin::getField_Padding(double *Field_PaddingX, double *Field_PaddingY) {
	//フィールド全体のズレを計算
	if (AllMovedata.isEnable()) {//全体ずらすが有効な場合
		if (Field_PaddingX != NULL)	*Field_PaddingX = AllMovedata.getPointX() - BLOCK_SIZE / 2.;
		if (Field_PaddingY != NULL)	*Field_PaddingY = AllMovedata.getPointY() - BLOCK_SIZE / 2.;
	}
	else {
		if (Field_PaddingX != NULL)	*Field_PaddingX = 0;
		if (Field_PaddingY != NULL)	*Field_PaddingY = 0;
	}
}

//移動モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Field_Admin::isPlayingMoveMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getMoveMotion()->isEnable()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//変化モーション中のブロックが存在するかどうかの取得(TRUE存在)
int Field_Admin::isPlayingChangeMotion() {
	for (int x = 0; x < BLOCK_WIDTHNUM; x++) {
		for (int y = 0; y < BLOCK_HEIGHTNUM; y++) {
			if (field[x][y].getChangeMotion()->isEnable()) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

//指定したX座標の一番上のブロックのY座標を取得する(見えている座標のみで判断)
int Field_Admin::getUpperX(int x) {
	for (int y = BLOCK_PADDINGUP; y < BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN; y++) {
		if (getBlockType(x, y) != BLOCK_TYPE_NO)	return y;
	}
	return BLOCK_HEIGHTNUM - BLOCK_PADDINGDOWN;//最下段の一段下の座標を返す
}

//最大の高さのブロックのY座標を取得する
int Field_Admin::getmaxUpperX() {
	int Max_Y = BLOCK_HEIGHTNUM;
	for (int x = BLOCK_PADDINGLEFT; x < BLOCK_WIDTHNUM - BLOCK_PADDINGRIGHT; x++) {
		Max_Y = min(Max_Y, getUpperX(x));
	}
	return Max_Y;
}

//現在のチェイン数を取得する
int Field_Admin::getChain() {
	return ChainCount;
}