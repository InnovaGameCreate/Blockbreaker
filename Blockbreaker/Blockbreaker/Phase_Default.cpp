//規定のフェーズ
#include "MainFunc.h"

Phase_Default::Phase_Default() {};

Phase_Default::~Phase_Default() {};

void Phase_Default::Init_Draw() {};

void Phase_Default::Init_Update() {};

void Phase_Default::Draw() {};

void Phase_Default::Update() { 
	Changefaze(FAZE_GameMain, THREAD_Update);
};

void Phase_Default::Finalize_Draw() {};

void Phase_Default::Finalize_Update() {};
