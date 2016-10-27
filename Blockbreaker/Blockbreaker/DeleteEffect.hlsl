//Windowsの進捗ゲージ的な

float PlaceY : register(c0); //光らせる場所

struct PS_INPUT //入力値の構造体
{
	float4 Diffuse : COLOR0;
	float4 Specular : COLOR1;
	float2 TexCoords0 : TEXCOORD0;
	float2 TexCoords1 : TEXCOORD1;
};

struct PS_OUTPUT //出力値の構造体
{
	float4 Output : COLOR0;
};

sampler sampler0 : register(s0); //サンプラー
sampler sampler1 : register(s1); //サンプラー
sampler sampler2 : register(s2); //サンプラー

//アルファブレンドを行う(透過情報はソースのものが直接適用されます)
float4 Alphablend(float4 src, float4 color)
{
	float4 blended; //アルファブレンド後の画像
	float As = color.a / 1.;
	blended = src * (1 - As) + color * As; //アルファブレンドを行う
	blended.a = src.a; //透過値はソースに一致させる
	return blended;
}

PS_OUTPUT main(PS_INPUT psin)
{
	PS_OUTPUT psout; //返り値用
	float4 texc; //テクスチャ用(ブロック)
	float4 texFire; //テクスチャ用(炎)
	float4 texFire2; //テクスチャ用(焦げ跡)
	float4 Blend; //ブレンド後画像(焦げ跡適用後)
	float4 Blend2; //ブレンド後画像(炎適用後)
	float Place2 = PlaceY+0.4;	//燃えて消える部分の場所
	float Size = 0.2;
	texc = tex2D(sampler0, psin.TexCoords0);
	texFire = tex2D(sampler1, psin.TexCoords0);
	texFire2 = tex2D(sampler2, psin.TexCoords0);
	
	psout.Output = tex2D(sampler0, psin.TexCoords0);

	//psout.Output.a = 0.5;

	//return psout;


	//PlaceY;


	//位置より上に重ねるアルファピクセルの用意

	//焦げ跡を先に作成する(上のみを透過させる)
	{
		//対象位置よりアルファ値の計算
		float endSize = 1 / Size;
		float Value = (psin.TexCoords0.y - (PlaceY - Size + (Size * 2) * psin.TexCoords0.y)) * endSize;
		if (Value > 1)
			Value = 1;
		if (Value < 0)
			Value = 0;
		texFire2.a = Value;
		Blend = Alphablend(texc, texFire2);

	}

		//炎
	{
		float endSize = 1 / Size;
		float Value = (abs(psin.TexCoords0.y - (PlaceY - Size + (Size * 2) * psin.TexCoords0.y))) * endSize;
		if (Value > 1)
			Value = 1;
		texFire.a = (1 - Value);
		//アルファブレンドを行う
		Blend2 = Alphablend(Blend, texFire);
	}

	//燃えて消える部分
	{
		//対象位置よりアルファ値の計算
		float endSize = 1 / Size;
		float Value = (psin.TexCoords0.y - (Place2 - Size + (Size * 2) * psin.TexCoords0.y)) * endSize;
		if (Value > 1)
			Value = 1;
		if (Value < 0)
			Value = 0;
		if (Blend2.a > 1 - Value)
			Blend2.a = (1 - Value);

	}
	psout.Output = Blend2;


	return psout;
}
