#pragma once
class PhaseController
{
private:
	virtual void Draw() = 0;			//描画処理
	virtual void Update() = 0;			//計算処理
	virtual void Update_Final() {};		//Update後に呼ばれる
public:
	PhaseController() {};			//コンストラクタ
	virtual ~PhaseController() {};	//デストラクタ

									//純粋仮想関数(必ずオーバーライドすること！！)
	virtual void Init_Draw() = 0;		//初期化(描画処理)
	virtual void Init_Update() = 0;		//初期化(計算処理)
	virtual void Finalize_Draw() = 0;	//終了処理(描画処理)
	virtual void Finalize_Update() = 0;	//終了処理(計算処理)

										//描画際に呼ばれる描画関数
	virtual void DrawFunc() final {
		Draw();
	}

	//描画際に呼ばれる描画関数
	virtual void UpdateFunc() final {
		Update_Final();
		Update();
	}

};

//規定のフェーズ
class Phase_Default : public PhaseController
{
public:
	Phase_Default();
	~Phase_Default();
	void Init_Draw();
	void Init_Update();
	void Draw();
	void Update();
	void Finalize_Draw();
	void Finalize_Update();
};