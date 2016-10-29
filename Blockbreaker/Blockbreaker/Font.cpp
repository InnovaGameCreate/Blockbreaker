//�t�H���g�֌W
#include "MainFunc.h"

static int GenJyuuGothicLHeavy_Edge25;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y25
static int GenJyuuGothicLHeavy_Edge30;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y30
static int GenJyuuGothicLHeavy_Edge35;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y35
static int GenJyuuGothicLHeavy_Edge40;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y40
static int GenJyuuGothicLHeavy_Edge50;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y50
static int GenJyuuGothicLHeavy_Edge60;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y60
static int GenJyuuGothicLHeavy_Edge70;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y70
static int GenJyuuGothicLHeavy_Edge80;//���K�S�V�b�NL Heavy�G�b�W�t���T�C�Y80

static int SFSquareHeadCondensed_Edge15;//SF Square Head Condensed�G�b�W�t���T�C�Y15
static int SFSquareHeadCondensed_Edge25;//SF Square Head Condensed�G�b�W�t���T�C�Y25
static int SFSquareHeadCondensed_Edge35;//SF Square Head Condensed�G�b�W�t���T�C�Y35

static int LiadFlag = 0;

//������
void Font_init() {
	if (LiadFlag == 0) {
		// ********** �t�H���g�̃��[�h **********
		{
			TCHAR *filename = _T("Data/Fonts/GenJyuuGothicL-Heavy.ttf");
			// �t�@�C���̃T�C�Y�𓾂�
			LONGLONG fsize = FileRead_size(filename);
			if(fsize == -1)	Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("�t�@�C���T�C�Y�̓ǂݍ��݂Ɏ��s"));
			DWORD FontFileSize = (DWORD)fsize;
			// �t�H���g�t�@�C�����J��
			int FontFileHandle = FileRead_open(filename);
			// �t�H���g�f�[�^�i�[�p�̃������̈���m��
			void *Buffer = malloc(FontFileSize);
			if (Buffer == NULL) {
				Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("�������̊m�ۂɎ��s���܂���"));
			}
			else {
				// �t�H���g�t�@�C�����ۂ��ƃ������ɓǂݍ���
				FileRead_read(Buffer, FontFileSize, FontFileHandle);
				//�t�@�C�������
				FileRead_close(FontFileHandle);
				// AddFontMemResourceEx�����p
				DWORD font_num = 0;
				// �������ɓǂݍ��񂾃t�H���g�f�[�^���V�X�e���ɒǉ�
				if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) <= 0) {
					// �t�H���g�Ǎ��G���[����
					Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("�t�H���g���V�X�e���ɒǉ��o���܂���ł���"));
				}
				free(Buffer);
			}
		}

		{
			TCHAR *filename = _T("Data/Fonts/SF_Square_Head_Condensed.ttf");
			// �t�@�C���̃T�C�Y�𓾂�
			DWORD FontFileSize = (DWORD)FileRead_size(filename);
			// �t�H���g�t�@�C�����J��
			int FontFileHandle = FileRead_open(filename);
			// �t�H���g�f�[�^�i�[�p�̃������̈���m��
			void *Buffer = malloc(FontFileSize);
			if (Buffer == NULL) {
				Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("�������̊m�ۂɎ��s���܂���"));
			}
			else {
				// �t�H���g�t�@�C�����ۂ��ƃ������ɓǂݍ���
				FileRead_read(Buffer, FontFileSize, FontFileHandle);
				//�t�@�C�������
				FileRead_close(FontFileHandle);
				// AddFontMemResourceEx�����p
				DWORD font_num = 0;
				// �������ɓǂݍ��񂾃t�H���g�f�[�^���V�X�e���ɒǉ�
				if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) <= 0) {
					// �t�H���g�Ǎ��G���[����
					Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("�t�H���g���V�X�e���ɒǉ��o���܂���ł���"));
				}
			}
			free(Buffer);
		}


		ChangeFont(_T("���K�S�V�b�NL Heavy"), DX_CHARSET_DEFAULT);
		ChangeFont(_T("SF Square Head Condensed"), DX_CHARSET_DEFAULT);

		ChangeFontType(DX_FONTTYPE_EDGE);
		LiadFlag = 1;
	}

	GenJyuuGothicLHeavy_Edge25 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 25, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge30 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 30, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge35 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 35, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge40 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 40, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge50 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 50, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge60 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 60, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge70 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 70, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge80 = CreateFontToHandle(_T("���K�S�V�b�NL Heavy"), 80, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);

	SFSquareHeadCondensed_Edge15 = CreateFontToHandle(_T("SF Square Head Condensed"), 15, -1, DX_FONTTYPE_EDGE, -1, 1, 0, -1);
	SFSquareHeadCondensed_Edge25 = CreateFontToHandle(_T("SF Square Head Condensed"), 25, -1, DX_FONTTYPE_EDGE, -1, 1, 0, -1);
	SFSquareHeadCondensed_Edge35 = CreateFontToHandle(_T("SF Square Head Condensed"), 35, -1, DX_FONTTYPE_EDGE, -1, 1, 0, -1);
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("Fonts�̏�������������"));


}

//�e�t��������̕`��
void Font_DrawStringWithShadow(double x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding, unsigned int EdgeColor, int VerticalFlag) {
	DrawStringToHandle((int)(x + padding), (int)(y + padding), String, ShadowColor, Font_getHandle(Fonttype), EdgeColor, VerticalFlag);
	DrawStringToHandle((int)x, (int)y, String, Color, Font_getHandle(Fonttype), EdgeColor, VerticalFlag);
}

//�e�t��������`��(X�̂ݒ��S�w��)
void Font_DrawStringCenterWithShadow(double Center_x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding, unsigned int EdgeColor, int VerticalFlag) {
	double Width = GetDrawStringWidthToHandle(String, (int)_tcslen(String), Font_getHandle(Fonttype));
	Width /= 2.;
	Font_DrawStringWithShadow(Center_x - Width, y, String, Color, ShadowColor, Fonttype, padding, EdgeColor, VerticalFlag);
}

//�t�H���g�̃n���h���擾
int Font_getHandle(FONTTYPE font) {
	switch (font) {
	case FONTTYPE_GenJyuuGothicLHeavy_Edge25:
		return GenJyuuGothicLHeavy_Edge25;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge30:
		return GenJyuuGothicLHeavy_Edge30;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge35:
		return GenJyuuGothicLHeavy_Edge35;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge40:
		return GenJyuuGothicLHeavy_Edge40;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge50:
		return GenJyuuGothicLHeavy_Edge50;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge60:
		return GenJyuuGothicLHeavy_Edge60;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge70:
		return GenJyuuGothicLHeavy_Edge70;
	case FONTTYPE_GenJyuuGothicLHeavy_Edge80:
		return GenJyuuGothicLHeavy_Edge80;
	case FONTTYPE_SFSquareHeadCondensed_Edge15:
		return SFSquareHeadCondensed_Edge15;
	case FONTTYPE_SFSquareHeadCondensed_Edge25:
		return SFSquareHeadCondensed_Edge25;
	case FONTTYPE_SFSquareHeadCondensed_Edge35:
		return SFSquareHeadCondensed_Edge35;
	}
	return 0;
}