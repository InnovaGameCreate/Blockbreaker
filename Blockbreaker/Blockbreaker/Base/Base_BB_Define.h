#pragma once

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<○>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//定数・マクロ
//命名規則：定数はすべて大文字、単語と単語の間は_で区切る

#define PI (acos(-1.0))				//円周率
#define PIf ((float)acos(-1.0))		//円周率(float)

//マクロ
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))	//配列の長さを求める

#define deg_to_rad(deg) (((deg)/360.)*2*PI)	//度からラジアンに変換
#define rad_to_deg(rad) (((rad)/2./PI)*360)	//ラジアンから度に変換