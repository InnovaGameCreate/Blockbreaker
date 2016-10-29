//フォント関係
#include "MainFunc.h"

static int GenJyuuGothicLHeavy_Edge25;//源桑ゴシックL Heavyエッジ付きサイズ25
static int GenJyuuGothicLHeavy_Edge30;//源桑ゴシックL Heavyエッジ付きサイズ30
static int GenJyuuGothicLHeavy_Edge35;//源桑ゴシックL Heavyエッジ付きサイズ35
static int GenJyuuGothicLHeavy_Edge40;//源桑ゴシックL Heavyエッジ付きサイズ40
static int GenJyuuGothicLHeavy_Edge50;//源桑ゴシックL Heavyエッジ付きサイズ50
static int GenJyuuGothicLHeavy_Edge60;//源桑ゴシックL Heavyエッジ付きサイズ60
static int GenJyuuGothicLHeavy_Edge70;//源桑ゴシックL Heavyエッジ付きサイズ70
static int GenJyuuGothicLHeavy_Edge80;//源桑ゴシックL Heavyエッジ付きサイズ80

static int SFSquareHeadCondensed_Edge15;//SF Square Head Condensedエッジ付きサイズ15
static int SFSquareHeadCondensed_Edge25;//SF Square Head Condensedエッジ付きサイズ25
static int SFSquareHeadCondensed_Edge35;//SF Square Head Condensedエッジ付きサイズ35

static int LiadFlag = 0;

//初期化
void Font_init() {
	if (LiadFlag == 0) {
		// ********** フォントのロード **********
		{
			TCHAR *filename = _T("Data/Fonts/GenJyuuGothicL-Heavy.ttf");
			// ファイルのサイズを得る
			LONGLONG fsize = FileRead_size(filename);
			if(fsize == -1)	Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("ファイルサイズの読み込みに失敗"));
			DWORD FontFileSize = (DWORD)fsize;
			// フォントファイルを開く
			int FontFileHandle = FileRead_open(filename);
			// フォントデータ格納用のメモリ領域を確保
			void *Buffer = malloc(FontFileSize);
			if (Buffer == NULL) {
				Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("メモリの確保に失敗しました"));
			}
			else {
				// フォントファイルを丸ごとメモリに読み込む
				FileRead_read(Buffer, FontFileSize, FontFileHandle);
				//ファイルを閉じる
				FileRead_close(FontFileHandle);
				// AddFontMemResourceEx引数用
				DWORD font_num = 0;
				// メモリに読み込んだフォントデータをシステムに追加
				if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) <= 0) {
					// フォント読込エラー処理
					Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("フォントをシステムに追加出来ませんでした"));
				}
				free(Buffer);
			}
		}

		{
			TCHAR *filename = _T("Data/Fonts/SF_Square_Head_Condensed.ttf");
			// ファイルのサイズを得る
			DWORD FontFileSize = (DWORD)FileRead_size(filename);
			// フォントファイルを開く
			int FontFileHandle = FileRead_open(filename);
			// フォントデータ格納用のメモリ領域を確保
			void *Buffer = malloc(FontFileSize);
			if (Buffer == NULL) {
				Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("メモリの確保に失敗しました"));
			}
			else {
				// フォントファイルを丸ごとメモリに読み込む
				FileRead_read(Buffer, FontFileSize, FontFileHandle);
				//ファイルを閉じる
				FileRead_close(FontFileHandle);
				// AddFontMemResourceEx引数用
				DWORD font_num = 0;
				// メモリに読み込んだフォントデータをシステムに追加
				if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) <= 0) {
					// フォント読込エラー処理
					Log_print(Log_Type_ERROR, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("フォントをシステムに追加出来ませんでした"));
				}
			}
			free(Buffer);
		}


		ChangeFont(_T("源桑ゴシックL Heavy"), DX_CHARSET_DEFAULT);
		ChangeFont(_T("SF Square Head Condensed"), DX_CHARSET_DEFAULT);

		ChangeFontType(DX_FONTTYPE_EDGE);
		LiadFlag = 1;
	}

	GenJyuuGothicLHeavy_Edge25 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 25, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge30 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 30, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge35 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 35, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge40 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 40, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge50 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 50, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge60 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 60, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge70 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 70, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);
	GenJyuuGothicLHeavy_Edge80 = CreateFontToHandle(_T("源桑ゴシックL Heavy"), 80, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2, 0, -1);

	SFSquareHeadCondensed_Edge15 = CreateFontToHandle(_T("SF Square Head Condensed"), 15, -1, DX_FONTTYPE_EDGE, -1, 1, 0, -1);
	SFSquareHeadCondensed_Edge25 = CreateFontToHandle(_T("SF Square Head Condensed"), 25, -1, DX_FONTTYPE_EDGE, -1, 1, 0, -1);
	SFSquareHeadCondensed_Edge35 = CreateFontToHandle(_T("SF Square Head Condensed"), 35, -1, DX_FONTTYPE_EDGE, -1, 1, 0, -1);
	Log_print(Log_Type_INFORMATION, _T(__FILE__), _T(__FUNCTION__), __LINE__, 0, _T("Fontsの初期化処理完了"));


}

//影付き文字列の描画
void Font_DrawStringWithShadow(double x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding, unsigned int EdgeColor, int VerticalFlag) {
	DrawStringToHandle((int)(x + padding), (int)(y + padding), String, ShadowColor, Font_getHandle(Fonttype), EdgeColor, VerticalFlag);
	DrawStringToHandle((int)x, (int)y, String, Color, Font_getHandle(Fonttype), EdgeColor, VerticalFlag);
}

//影付き文字列描画(Xのみ中心指定)
void Font_DrawStringCenterWithShadow(double Center_x, double y, const TCHAR *String, unsigned int Color, unsigned int ShadowColor, FONTTYPE Fonttype, double padding, unsigned int EdgeColor, int VerticalFlag) {
	double Width = GetDrawStringWidthToHandle(String, (int)_tcslen(String), Font_getHandle(Fonttype));
	Width /= 2.;
	Font_DrawStringWithShadow(Center_x - Width, y, String, Color, ShadowColor, Fonttype, padding, EdgeColor, VerticalFlag);
}

//フォントのハンドル取得
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