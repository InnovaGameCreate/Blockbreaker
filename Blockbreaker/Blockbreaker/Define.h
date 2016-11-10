#pragma once

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//定数・マクロ
//命名規則：定数はすべて大文字、単語と単語の間は_で区切る

//デバッグ設定の定義(使用しない場合はコメントアウト)
#ifdef DEBUG
//#define _DEBUG_GAMEMAIN_			//ゲームメインのデバッグ
#endif // DEBUG



#define GAMEVERSION _T("0.1")		//バージョン名

#define DRAWFPS 60					//描画FPS設定
#define UPDATEFPS 60				//処理FPS設定
#define WINDOW_WIDTH 1280			//画面の横幅
#define WINDOW_HEIGHT 960			//画面の高さ
#define TITLE _T("Blockbreaker")	//ウィンドウタイトル
#define PI (acos(-1.0))				//円周率
#define PIf ((float)acos(-1.0))		//円周率(float)

									//マクロ
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))	//配列の長さを求める

#define deg_to_rad(deg) (((deg)/360.)*2*PI)	//度からラジアンに変換
#define rad_to_deg(rad) (((rad)/2./PI)*360)	//ラジアンから度に変換