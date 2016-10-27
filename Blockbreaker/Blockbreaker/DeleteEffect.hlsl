//Windows�̐i���Q�[�W�I��

float PlaceY : register(c0); //���点��ꏊ

struct PS_INPUT //���͒l�̍\����
{
	float4 Diffuse : COLOR0;
	float4 Specular : COLOR1;
	float2 TexCoords0 : TEXCOORD0;
	float2 TexCoords1 : TEXCOORD1;
};

struct PS_OUTPUT //�o�͒l�̍\����
{
	float4 Output : COLOR0;
};

sampler sampler0 : register(s0); //�T���v���[
sampler sampler1 : register(s1); //�T���v���[
sampler sampler2 : register(s2); //�T���v���[

//�A���t�@�u�����h���s��(���ߏ��̓\�[�X�̂��̂����ړK�p����܂�)
float4 Alphablend(float4 src, float4 color)
{
	float4 blended; //�A���t�@�u�����h��̉摜
	float As = color.a / 1.;
	blended = src * (1 - As) + color * As; //�A���t�@�u�����h���s��
	blended.a = src.a; //���ߒl�̓\�[�X�Ɉ�v������
	return blended;
}

PS_OUTPUT main(PS_INPUT psin)
{
	PS_OUTPUT psout; //�Ԃ�l�p
	float4 texc; //�e�N�X�`���p(�u���b�N)
	float4 texFire; //�e�N�X�`���p(��)
	float4 texFire2; //�e�N�X�`���p(�ł���)
	float4 Blend; //�u�����h��摜(�ł��ՓK�p��)
	float4 Blend2; //�u�����h��摜(���K�p��)
	float Place2 = PlaceY+0.4;	//�R���ď����镔���̏ꏊ
	float Size = 0.2;
	texc = tex2D(sampler0, psin.TexCoords0);
	texFire = tex2D(sampler1, psin.TexCoords0);
	texFire2 = tex2D(sampler2, psin.TexCoords0);
	
	psout.Output = tex2D(sampler0, psin.TexCoords0);

	//psout.Output.a = 0.5;

	//return psout;


	//PlaceY;


	//�ʒu����ɏd�˂�A���t�@�s�N�Z���̗p��

	//�ł��Ղ��ɍ쐬����(��݂̂𓧉߂�����)
	{
		//�Ώۈʒu���A���t�@�l�̌v�Z
		float endSize = 1 / Size;
		float Value = (psin.TexCoords0.y - (PlaceY - Size + (Size * 2) * psin.TexCoords0.y)) * endSize;
		if (Value > 1)
			Value = 1;
		if (Value < 0)
			Value = 0;
		texFire2.a = Value;
		Blend = Alphablend(texc, texFire2);

	}

		//��
	{
		float endSize = 1 / Size;
		float Value = (abs(psin.TexCoords0.y - (PlaceY - Size + (Size * 2) * psin.TexCoords0.y))) * endSize;
		if (Value > 1)
			Value = 1;
		texFire.a = (1 - Value);
		//�A���t�@�u�����h���s��
		Blend2 = Alphablend(Blend, texFire);
	}

	//�R���ď����镔��
	{
		//�Ώۈʒu���A���t�@�l�̌v�Z
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
