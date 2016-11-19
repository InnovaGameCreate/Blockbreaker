#pragma once

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//定数・マクロ
//命名規則：定数はすべて大文字、単語と単語の間は_で区切る

//デバッグ設定の定義(使用しない場合はコメントアウト)
#ifdef DEBUG
//#define _DEBUG_GAMEMAIN_			//ゲームメインのデバッグ
#endif // DEBUG



#define GAMEVERSION _T("0.1")		//バージョン名

#define WINDOW_WIDTH (Base_BB_getWINDOW_WIDTH())
#define WINDOW_HEIGHT (Base_BB_getWINDOW_HEIGHT())