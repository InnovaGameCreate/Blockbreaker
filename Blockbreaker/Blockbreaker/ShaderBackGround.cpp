//�V�F�[�_�֘A�H(�����Ă邩�悤�������)
//http://www.nicovideo.jp/watch/sm12147682
#include "MainFunc.h"

struct vertex_t {
	VERTEX2DSHADER Vert[6];
};


//�V�F�[�_�𗘗p���ď��ł���u���b�N��`��
vertex_t ColorWaveVertex;
static int ColorWavePShandle;//Windows���i���o�[�̃o�C�i���t�@�C���ւ̃n���h��
static int GrHandle;		//�ꎞ�`��p

static void Initialize_DeleteBlock();


//�V�F�[�_�֘A������
void ShaderBackGround_Initialize() {
	InitShader();//�V�F�[�_�[�n���h���̏�����

	Initialize_DeleteBlock();
	printLog_I(_T("�V�F�[�_�[�̏���������"));
}

//�V�F�[�_�𗘗p���ď��ł���u���b�N��`�悷��̏�����
static void Initialize_DeleteBlock() {

	//int t = GetValidShaderVersion();
	//printf("%d\n", t);
	//�s�N�Z���V�F�[�_�[�o���
	ColorWavePShandle = LoadPixelShader(_T("Data/Shader/ps_DeleteEffect.pso"));
	if (ColorWavePShandle == -1) {
		printLog_E(_T("�V�F�[�_�[�̃��[�h�Ɏ��s(Data/Shader/ps_DeleteEffect.pso)"));
	}

	GrHandle = MakeScreen(64, 64, TRUE);

	//���_�f�[�^�̏���(������)
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

	//���l
	/*
	dif�̓f�C�t���[�Y�J���[
	spc�̓X�y�L�����J���[
	rhw�͑����A�X�y�N�g��֘A�̒l
	su,sv�͂悭������Ȃ����ǃe�N�X�`�����W�֘A
	*/
}

//�V�F�[�_�𗘗p���ď��ł���u���b�N��`�悷��
void ShaderBackGround_DeleteBlock(double X, double Y, double place, int srcImage, int Effect1, int Effect2) {

	//������place���V�F�[�_�̏����ɍ��킹�Ē�������
	place = map(place, 0, 1, 1, -0.4);
	/*
	place��0�̎�1�ɂ���
	1�̎��A-0.4�ɂ���
	*/
	//float X1 = (float)X;
	//float Y1 = (float)Y;
	float X1 = (float)0;
	float Y1 = (float)0;

	int t = GetDrawScreen();

	SetDrawScreen(GrHandle);

	ClearDrawScreen();


	float RealX, RealY;	//���ۂ̃e�N�X�`���̑傫��
	GetGraphSizeF(srcImage, &RealX, &RealY);

	float W, H;	//���ۂ̃e�N�X�`���̑傫��
	W = Phase_GameMain::BLOCK_SIZE;
	H = Phase_GameMain::BLOCK_SIZE;
	W = RealX;
	H = RealY;

	//���_�f�[�^�̏���(UV���W���Čv�Z����)
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
	SetUsePixelShader(ColorWavePShandle);//�g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetPSConstSF(0, (float)place);

	SetUseTextureToShader(0, srcImage);//�g�p����e�N�X�`�����Z�b�g
	SetUseTextureToShader(1, Effect1);//�g�p����e�N�X�`�����Z�b�g
	SetUseTextureToShader(2, Effect2);//�g�p����e�N�X�`�����Z�b�g
	DrawPrimitive2DToShader(ColorWaveVertex.Vert, 6, DX_PRIMTYPE_TRIANGLELIST);//�`��
	SetUsePixelShader(-1);//�g�p����s�N�Z���V�F�[�_�[���Z�b�g


	SetDrawScreen(t);
	//���S���W�ɕϊ�
	X = X + Phase_GameMain::BLOCK_SIZE / 2.;
	Y = Y + Phase_GameMain::BLOCK_SIZE / 2.;
	//�u���b�N�̕`��
	DrawRectRotaGraphFast2((int)X, (int)Y, 0, 0, Phase_GameMain::BLOCK_SIZE, Phase_GameMain::BLOCK_SIZE, Phase_GameMain::BLOCK_SIZE/2, Phase_GameMain::BLOCK_SIZE / 2, 1, 0, GrHandle, TRUE, FALSE);
}
