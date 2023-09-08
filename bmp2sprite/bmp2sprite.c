//
// bmp2sprite
// 16色のビットマップファイルからスプライト用のアセンブラソースを生成するツール
// Copyright 2023 CHIKUWA TEIKOKU
//
// bmp2sprite <in:BITMAP FILE NAME> <out:PATTERN FILE NAME>
//
//   <in:BITMAP FILE NAME>		入力するビットマップファイル名(256x192までの8の倍数のサイズ)
//   <out:PATTERN FILE NAME>	出力するパターンデータのアセンブラソースファイル名
//
// ex.
//   bmp2sprite example.bmp example_sprite.asm
//


#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// ビットマップファイルの情報ヘッダ
//
struct BMPINFOHEADER {
	int				isize;  // ヘッダーのサイズのバイト数
	int				width;  // 画像の横幅
	int				height; // 画像の縦幅
	unsigned short	planes;	// 面の数
	unsigned short	bits;   // １ピクセルあたりのビット数
	unsigned int	ctype;  // 圧縮形式
	unsigned int	gsize;  // 画像のデータサイズ
	int				xppm;   // １ｍあたりのピクセル数（横）
	int				yppm;   // １ｍあたりのピクセル数（縦）
	unsigned int	cnum;   // カラーテーブル
	unsigned int	inum;   // カラーインデックス
};


int main(int argc, char* argv[])
{
	int ret_code = 0;
	FILE* fp_input = NULL;
	FILE* fp_ptn = NULL;
	char file_header[14];
	struct BMPINFOHEADER info_header;
	unsigned char color_palette[64];
	unsigned char read_buf;
	unsigned char bmp_data[256 * 192];
	int char_code = 0;
	int color_1 = 0;
	int color_2 = 0;

	unsigned char sprite_pat[16][16][16];
	unsigned char sprite_found[16];
	int sprite_no = 0;


	ret_code++;
	if (argc < 3) {
		fprintf(stderr, "USAGE: bmp2sprite <in:BITMAP FILE NAME> <out:PATTERN FILE NAME>\n");
		goto LABEL_END;
	}

	// ビットマップファイルをオープンする
	ret_code++;
	if (NULL == (fp_input = fopen(argv[1], "rb"))) {
		fprintf(stderr, "ERROR: FILE OPEN ERROR: %s\n", argv[1]);
		goto LABEL_END;
	}

	// ファイルヘッダを読み込む
	ret_code++;
	if (sizeof(file_header) != fread(file_header, 1, sizeof(file_header), fp_input)) {
		fprintf(stderr, "ERROR: INVALID FILE HEADER.\n");
		goto LABEL_END;
	}

	// 先頭の2バイトをチェックする
	ret_code++;
	if (strncmp(file_header, "BM", 2)) {
		fprintf(stderr, "ERROR: INPUT FILE IS NOT BITMAP.\n");
		goto LABEL_END;
	}

	// 情報ヘッダを読み込む
	ret_code++;
	if (sizeof(info_header) != fread(&info_header, 1, sizeof(info_header), fp_input)) {
		fprintf(stderr, "ERROR: INVALID BITMAP FILE HEADER.\n");
		goto LABEL_END;
	}

	printf("INPUT FILE INFO: width=%d, height=%d, bits=%d, colors=%d, compress=%d\n", info_header.width, info_header.height, (int)info_header.bits, info_header.cnum, info_header.ctype);

	ret_code++;
	// 画像サイズのチェック
//	if (info_header.width > 256 || info_header.height > 192 || info_header.width % 8 != 0 || info_header.height % 8 != 0)
	if (info_header.width % 16 != 0 || info_header.height % 16 != 0)
	{
		fprintf(stderr, "ERROR: INVALID BITMAP WIDTH OR HEIGHT.\n");
		goto LABEL_END;
	}

	// 4ビット(16色)カラーだけ
	ret_code++;
	if (4 != info_header.bits) {
		fprintf(stderr, "ERROR: INPUT BITMAP FILE IS NOT 4BIT COLOR.\n");
		goto LABEL_END;
	}

	// 圧縮はNG
	ret_code++;
	if (info_header.ctype) {
		fprintf(stderr, "ERROR: COMPRESS TYPE IS NOT SURPORTED.\n");
		goto LABEL_END;
	}

	// パレット情報は使用しないのでスキップする
	ret_code++;
	if (sizeof(color_palette) != fread(color_palette, 1, sizeof(color_palette), fp_input)) {
		fprintf(stderr, "ERROR: COULD NOT READ PALETTE DATA.\n");
		goto LABEL_END;
	}


	// 画像データの下から上に向けて読み込む
	ret_code++;
	for (int i = info_header.height - 1; 0 <= i; i--) {
		for (int j = 0; j < info_header.width / 2; j++) // 1バイトに2ドット分なのでwidthの半分
		{
			fread(&read_buf, 1, 1, fp_input);
			bmp_data[i * info_header.width + j * 2] = read_buf >> 4;		// 上位4ビットが左
			bmp_data[i * info_header.width + j * 2 + 1] = read_buf & 0x0F;	// 下位4ビットが右
		}
	}


	// パターンジェネレータ・テーブル用のアセンブラソースを書き込みモードでオープン
	ret_code++;
	if (NULL == (fp_ptn = fopen(argv[2], "w"))) {
		fprintf(stderr, "ERROR: FILE OPEN ERROR: %s\n", argv[2]);
		goto LABEL_END;
	}


	ret_code++;
	fprintf(fp_ptn, "; **** FOR SPRITE PATTERN GENERATOR TABLE ****\n\n");

	// 読み込んだビットマップデータを使ってPCGのパターンと色のデータを出力する
	ret_code++;
	for (int y = 0; y < info_header.height / 16; y++)
	{
		for (int x = 0; x < info_header.width / 16; x++)
		{
			memset(sprite_pat, '0', 16 * 16 * 16);
			memset(sprite_found, 0, 16);

			// 16x16ドット毎に組み立てていく
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					// ドットの色
					color_1 = bmp_data[(y * 16 + i) * info_header.width + x * 16 + j];

					// 透明以外の場合はビットを立てる
					if (color_1 != 0)
					{
						sprite_pat[color_1][i][j] = '1';
						sprite_found[color_1] = 1;
					}
				}
			}

			for (int c = 1; c < 16; c++)
			{
				if (sprite_found[c] == 0) continue;

				fprintf(fp_ptn, "; NO=%d COLOR=%d\n", sprite_no, c);

				// 左側の8x16
				for (int i = 0; i < 16; i++)
				{
					// パターンデータを2進数で出力する
					fprintf(fp_ptn, "DEFB    0b");
					for (int j = 0; j < 8; j++)
					{
						fprintf(fp_ptn, "%c", sprite_pat[c][i][j]);
					}
					fprintf(fp_ptn, "\n");
				}

				// 右側の8x16
				for (int i = 0; i < 16; i++)
				{
					// パターンデータを2進数で出力する
					fprintf(fp_ptn, "DEFB    0b");
					for (int j = 8; j < 16; j++)
					{
						fprintf(fp_ptn, "%c", sprite_pat[c][i][j]);
					}
					fprintf(fp_ptn, "\n");
				}

				fprintf(fp_ptn, "\n");

				sprite_no++;
			}

			char_code++;
		}
	}

	ret_code = 0;


LABEL_END:
	if (fp_input) fclose(fp_input);
	if (fp_ptn) fclose(fp_ptn);

	printf("DONE.\n");

	return ret_code;
}
