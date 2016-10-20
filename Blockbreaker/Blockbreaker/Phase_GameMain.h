#pragma once


#ifndef PHASECONTROLLER_H_
#error PhaseController.hをIncludeしてください
#endif // !PHASECONTROLLER_H_



class Phase_GameMain : public PhaseController
{

private:
	int gameWindow;	//ゲーム画面を描画するハンドル
	int CursorX, CursorY;//カーソル位置

	int Flag_Pause;			//ポーズ状態かどうか(ゲームの進行がすべて停止します)(TRUEでポーズ)
	int Flag_pauseRequest;	//ポーズ状態かどうかのリクエスト(ポーズ処理はすべての処理の最後で行うため)



	void Draw();
	void Update();
	void GameMain_Key();
public:
	Phase_GameMain();
	~Phase_GameMain();
	void Init_Draw();
	void Init_Update();
	void Finalize_Draw();
	void Finalize_Update();

	/*設定系*/
	int GameMain_CursorX_add(int Val);			//カーソル位置を相対的に移動する(戻り値:実際に移動した量)
	int GameMain_CursorY_add(int Val);			//カーソル位置を相対的に移動する(戻り値:実際に移動した量)
	void GameMain_PauseRequest(int b_Flag);		//ポーズ状態のリクエスト

	/*取得系*/
	int	GameMain_getCursorX();																			//カーソル位置を取得する
	int	GameMain_getCursorY();																			//カーソル位置を取得する
	void GameMain_Convert_Block_FromIngame(int blockX, int blockY, double *IngameX, double *IngameY);	//ブロックの座標？からインゲームの座標の左端を取得する(関数的に出すため、存在しないはずのブロック位置も計算出来ます)
	int	GameMain_isPaused();
};

