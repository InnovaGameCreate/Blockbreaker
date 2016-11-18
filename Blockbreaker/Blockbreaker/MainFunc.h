#pragma once
#include "Phase_GameMain.h"
#include "Phase_TopMenu.h"
#include "SelectItem.h"

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



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//enum定義
//命名規則："enum名"+_+"大文字で始まる要素名"

#include "Enum.h"


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*クラス*/


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//クラスのインスタンス(グローバル変数)
extern Phase_Default phase_Default;		//デフォルトのフェーズ
extern Phase_GameMain phase_GameMain;	//ゲームメインのフェーズ
extern Phase_TopMenu phase_TopMenu;		//トップメニューのフェーズ


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//関数群
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

/*FlyText.cpp*/
