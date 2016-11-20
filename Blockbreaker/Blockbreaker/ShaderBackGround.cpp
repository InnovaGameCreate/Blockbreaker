//シェーダ関連？(何してるかよう分からん)
//http://www.nicovideo.jp/watch/sm12147682
#include "MainFunc.h"

struct vertex_t {
	VERTEX2DSHADER Vert[6];
};


//シェーダを利用して消滅するブロックを描画
vertex_t ColorWaveVertex;
static int ColorWavePShandle;//Windows風進捗バーのバイナリファイルへのハンドル
static int GrHandle;		//一時描画用

static void Initialize_DeleteBlock();


//シェーダ関連初期化
void ShaderBackGround_Initialize() {
	InitShader();//シェーダーハンドルの初期化

	Initialize_DeleteBlock();
	printLog_I(_T("シェーダーの初期化完了"));
}

//シェーダを利用して消滅するブロックを描画するの初期化
static void Initialize_DeleteBlock() {

	//int t = GetValidShaderVersion();
	//printf("%d\n", t);
	//ピクセルシェーダーバ･･･
	ColorWavePShandle = LoadPixelShader(_T("Data/Shader/ps_DeleteEffect.pso"));
	if (ColorWavePShandle == -1) {
		printLog_E(_T("シェーダーのロードに失敗(Data/Shader/ps_DeleteEffect.pso)"));
	}

	GrHandle = MakeScreen(64, 64, TRUE);

	//頂点データの準備(初期化)
	for (int i = 0; i < 4; i++) {
		ColorWaveVertex.Vert[i].pos = VGet(0.0f, 0.0f, 0.0f);
		ColorWaveVertex.Vert[i].rhw = 1.0f;
	}
	ColorWaveVertex.Vert[0].dif = GetColorU8(255, 255, 255, 255);
	ColorWaveVertex.Vert[0].spc = GetColorU8(0, 0, 0, 0);
	ColorWaveVertex.Vert[0].u = 0.0f; ColorWaveVertex.Vert[0].v = 0.0f;
	ColorWaveVertex.Vert[1].u = 1.0f; ColorWaveVertex.Vert[1].v = 0.0f;
	ColorWaveVertex.Vert[2].u = 0.0f; ColorWaveVertex.Vert[2].v = 1.0f;
	ColorWaveVertex.Vert[3].u = 1.0f; ColorWaveVertex.Vert[3].v = 1.0f;
	ColorWaveVertex.Vert[0].su = 0.0f; ColorWaveVertex.Vert[0].sv = 0.0f;
	ColorWaveVertex.Vert[1].su = 1.0f; ColorWaveVertex.Vert[1].sv = 0.0f;
	ColorWaveVertex.Vert[2].su = 0.0f; ColorWaveVertex.Vert[2].sv = 1.0f;
	ColorWaveVertex.Vert[3].su = 1.0f; ColorWaveVertex.Vert[3].sv = 1.0f;
	ColorWaveVertex.Vert[4] = ColorWaveVertex.Vert[2];
	ColorWaveVertex.Vert[5] = ColorWaveVertex.Vert[1];

	//備考
	/*
	difはデイフューズカラー
	spcはスペキュラカラー
	rhwは多分アスペクト比関連の値
	su,svはよく分からないけどテクスチャ座標関連
	*/
}

//シェーダを利用して消滅するブロックを描画する
void ShaderBackGround_DeleteBlock(double X, double Y, double place, int srcImage, int Effect1, int Effect2) {

	//引数のplaceをシェーダの処理に合わせて調整する
	place = map(place, 0, 1, 1, -0.4);
	/*
	placeが0の時1にする
	1の時、-0.4にする
	*/
	//float X1 = (float)X;
	//float Y1 = (float)Y;
	float X1 = (float)0;
	float Y1 = (float)0;

	int t = GetDrawScreen();

	SetDrawScreen(GrHandle);

	ClearDrawScreen();


	float RealX, RealY;	//実際のテクスチャの大きさ
	GetGraphSizeF(srcImage, &RealX, &RealY);

	float W, H;	//実際のテクスチャの大きさ
	W = BLOCK_SIZE;
	H = BLOCK_SIZE;
	W = RealX;
	H = RealY;

	//頂点データの準備(UV座標も再計算する)
	ColorWaveVertex.Vert[0].pos = VGet((float)(X1), (float)(Y1), 0.0f);
	//ColorWaveVertex.Vert[0].u = 0;	ColorWaveVertex.Vert[0].v = 0;
	ColorWaveVertex.Vert[1].pos = VGet((float)(X1 + W), (float)(Y1), 0.0f);
	//ColorWaveVertex.Vert[1].u = W / RealX;	ColorWaveVertex.Vert[1].v = 0;
	ColorWaveVertex.Vert[2].pos = VGet((float)(X1), (float)(Y1 + H), 0.0f);
	//ColorWaveVertex.Vert[2].u = 0;	ColorWaveVertex.Vert[2].v = H / RealY;
	ColorWaveVertex.Vert[3].pos = VGet((float)(X1 + W), (float)(Y1 + H), 0.0f);
	//ColorWaveVertex.Vert[3].u = W / RealX;	ColorWaveVertex.Vert[3].v = H / RealY;
	ColorWaveVertex.Vert[4] = ColorWaveVertex.Vert[2];
	ColorWaveVertex.Vert[5] = ColorWaveVertex.Vert[1];

	InitShaderConstantBuffer();
	SetUsePixelShader(ColorWavePShandle);//使用するピクセルシェーダーをセット
	SetPSConstSF(0, (float)place);

	SetUseTextureToShader(0, srcImage);//使用するテクスチャをセット
	SetUseTextureToShader(1, Effect1);//使用するテクスチャをセット
	SetUseTextureToShader(2, Effect2);//使用するテクスチャをセット
	DrawPrimitive2DToShader(ColorWaveVertex.Vert, 6, DX_PRIMTYPE_TRIANGLELIST);//描画
	SetUsePixelShader(-1);//使用するピクセルシェーダーをセット


	SetDrawScreen(t);

	//ブロックの描画
	DrawRectRotaGraphFast2((int)X, (int)Y, 0, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE/2, BLOCK_SIZE / 2, 1, 0, GrHandle, TRUE, FALSE);
}
