#pragma once
#include "Phase_GameMain.h"
#include "Phase_TopMenu.h"
#include "SelectItem.h"
#include "KeyInput.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*前方宣言(このヘッダファイル以外で使用されるクラス、構造体を宣言してください)*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//定数・マクロ
//命名規則：定数はすべて大文字、単語と単語の間は_で区切る

#include "Define.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//構造体
//typedefするのはプログラム全体で使用するもののみにしてください。
//ファイル内でのみ使用する構造体はtypedefしないでください。(補完で出てきてうざいので)
#include "Struct.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//enum定義
//命名規則："enum名"+_+"大文字で始まる要素名"

#include "Enum.h"


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*クラス*/


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//クラスのインスタンス(グローバル変数)
extern Phase_GameMain phase_GameMain;			//ゲームメインのフェーズ
extern Phase_TopMenu phase_TopMenu;				//トップメニューのフェーズ
extern SK::PhaseController phaseController;		//フェーズコントローラー
extern SK::FpsController fpsController_Draw;	//FPSコントローラー
extern SK::FpsController fpsController_Update;	//FPSコントローラー


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//関数群
/*Blockbreaker.cpp*/
extern unsigned int getKeyBind(KEYBIND kEYBIND);	//キーバインドでのキー入力情報の取得(0押してない、1押した直後)
extern void ExitGameRequest();						//終了リクエスト
extern unsigned int getKey(int KEYNO);				//キーの入力状態を取得する(DXライブラリで定義されているキーの番号)(戻り値：キーが押されている時間、押されていないときは0)
extern unsigned int getJoyKey(int JoyKeyNO);		//ゲームパッド入力状態の取得(DXライブラリで定義されているキーの番号)(戻り値：キーが押されている時間、押されていないときは0)(ゲームパッド用)
extern int gettUSEGAMEPAD();						//使用するゲームパッドの取得
extern void setKeyImputStart(int X, int Y, KeyInputCallback_End *keyInputCallback_End);//キー入力を有効にする
extern TCHAR *getKeyImputStr();						//入力されているキーの取得
extern int isKeyImputEnable();						//キーボード入力が有効かどうかの取得


extern void setKeybind(KeyBind *keyBind);	//キーバインドの設定(NULLで規定値)
extern void setKeybindjoy(KeyBindjoy *keyBindjoy);//キーバインド設定(ゲームパッド)(NULLで規定値を設定)
extern void setUSEGAMEPAD(int type);		//使用するゲームパッドの設定(0で設定無し)
extern void SetAnalogueStickMode(ANALOGSTICKMODE type);	//ゲームパッドのアナログスティックの動作方法の設定
extern void setClearScreen(int Flag);		//画面のクリアを行うかどうか(FALSE行わない)(するとこはします)
extern void SetWindowMode(int Mode);		//ウィンドウモードの設定(0から項目順)
extern void SetDrawing_interval(int Mode);	//描画間隔の設定(0から項目順)
extern void SetModeVSync(int Mode);			//垂直同期の設定(0から項目順)
extern void SetModeClear(int Mode);			//画面消去の設定(0から項目順)
extern void SetModeCursor(int Mode, int WinMode);	//マウスカーソルの設定(0から項目順)(ウィンドウモードの設定と同じ引数)
extern void SetModeMultiThread(int Mode);	//マルチスレッドの設定(0から項目順)
extern void SetTextureCut(int Mode);		//テクスチャの分割の設定(0から項目順)

/*StartDialog.cpp*/
extern void StartDialog_Initialize(HINSTANCE hInstance);	//初期化
extern void StartDialog_Show();								//起動設定画面の表示

/*SoundEffect*/
extern void SoundEffect_init();				//初期化
extern void SoundEffect_update();			//効果音の計算処理ループ(効果音を鳴らすよりも前に呼ぶこと)
extern void SoundEffect_Play(SE_TYPE type);	//効果音の再生
extern void SoundEffect_PlayPlace(SE_TYPE type, double plaxeX, double placeY);	//効果音の再生(位置で音量が変わるやつ)(今は機能しない)
extern void SoundEffect_Save();				//効果音の状態の保存
extern void SoundEffect_Load();				//効果音の状態の復元
extern void SoundEffect_AllPause();			//効果音をすべてポーズする
extern void SoundEffect_SetSEVolume(int Volume);	//効果音の音量をすべて変更する(0～100)
extern int SoundEffect_GetSEVolume();		//効果音の音量取得(0～100)
extern void SoundEffect_LongSEStop();		//長い効果音の停止
extern void SoundEffect_LongSEPause();		//長い効果音のポーズ
extern void SoundEffect_LongSEResume();		//長い効果音のレジューム
extern void SoundEffect_SafePlay(SE_TYPE type);	//多重で効果音の再生が行われる可能性があるときに使用する効果音の再生関数(1効果音あたり1フレームに一度までしか再生関数が呼ばれなくなる)

/*ShaderBackGround.cpp*/
extern void ShaderBackGround_Initialize();		//シェーダ関連初期化
extern void ShaderBackGround_DeleteBlock(double X, double Y, double place, int srcImage, int Effect1, int Effect2);	//シェーダを利用して消滅するブロックを描画する

/*Font.cpp*/
extern void Font_init();					//初期化
extern int Font_getHandle(FONTTYPE font);	//フォントハンドルの取得
extern void Font_DrawStringWithShadow(double x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);					//影付き文字列の描画
extern void Font_DrawStringCenterWithShadow(double Center_x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding = 3, unsigned int EdgeColor = 0U, int VerticalFlag = FALSE);	//影付き文字列描画(Xのみ中心指定)

/*LoadMenu.cpp*/
extern void LoadMenu_Initialize();		//初期化
extern void LoadMenu_Draw();			//ロード画面の表示
extern void LoadMenu_Draw2();			//ロード画面の表示(最初の起動時用)
