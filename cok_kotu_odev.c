#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <time.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void lejant() {
	printf("Lejant:\n");
	printf(ANSI_COLOR_GREEN"S = Başlangıç \t"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN"G = Son \t"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE "# = Duvar \t" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW". = Yol \t"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"O = Gerçek Yol \n"ANSI_COLOR_RESET);
	printf("Devam etmek için bir tuşa basın");
}
void giris_cıkıs(int* dizi, int x, int y) {
	*((dizi + 0 * y) + 0) = 1;
	*((dizi + (y - 1) * y) + (x - 1)) = 2;
}
void Matrix_Yap(int* dizi, int x, int y) {		//random matrix generator
	for (int a = 0; a < x; a++)
	{
		for (int b = 0; b < y; b++) {
			if (a == 0 && b == 0)
			{
				*((dizi + y * a) + b) = 1;
			}
			else if (a == x - 1 && b == y - 1)
			{
				*((dizi + y * a) + b) = 2;
			}
			else
			{
				*((dizi + y * a) + b) = rand() % 2 + 3;
			}
		}
	}
}
void Geri_cevir(int* dizi, int x, int y) {		//Matrixleri orijinal haline döndürür
//	*((dizi + y * 0) + 0) = 1;
//	*((dizi + y * (x-1)) + (y*1)) = 2;
	for (int a = 0; a < x; a++)
	{
		for (int b = 0; b < y; b++) {
			if (*((dizi + y * a) + b) == 6)
			{
				if (a == 0 && b == 0)
				{
					*((dizi + y * a) + b) = 1;
				}
				else if (a == x - 1 && b == y - 1)
				{
					*((dizi + y * a) + b) = 2;
				}
				else
				{
					*((dizi + y * a) + b) = 4;
				}
			}

		}
	}
}
bool geldik_mi(int* a, int x, int y, int sutun_say) {		// Malum soru
	if (*((a + x * sutun_say) + y) == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Yaz(int* a, int x, int y) {		//matrix Yazdırılıyor
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) {
			if (*((a + i * y) + j) == 1)
			{
				printf(ANSI_COLOR_GREEN "S " ANSI_COLOR_RESET);
			}
			else if (*((a + i * y) + j) == 2)
			{
				printf(ANSI_COLOR_GREEN "G " ANSI_COLOR_RESET);
			}
			else if (*((a + i * y) + j) == 3)
			{
				printf(ANSI_COLOR_BLUE "# " ANSI_COLOR_RESET);
			}
			else if (*((a + i * y) + j) == 4)
			{
				printf(ANSI_COLOR_YELLOW". "ANSI_COLOR_RESET);
			}
			else if (*((a + i * y) + j) == 5)
			{
				printf("X");
			}
			else if (*((a + i * y) + j) == 6)
			{
				printf(ANSI_COLOR_RED "O " ANSI_COLOR_RESET);
			}
		}
		printf("\n");
	}
}
bool Yol_bul(int* a, int x, int y, int satir_say, int sutun_say) {		//yolumuzu bulduran
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (Yol_bul(a, x, y + 1, satir_say, sutun_say))		// sağ
				{
					return true;
				}
				if (Yol_bul(a, x + 1, y, satir_say, sutun_say))		//aşağı
				{
					return true;
				}
				if (Yol_bul(a, x, y - 1, satir_say, sutun_say))		//sol
				{
					return true;
				}
				if (Yol_bul(a, x - 1, y, satir_say, sutun_say))		//yukarı
				{
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}

//sağ
bool sag_sol_yukar_asag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sag_sol_yukar_asag(a, x, y + 1, satir_say, sutun_say, sayac))		// sağ
				{
					(*sayac)++;
					return true;
				}
				if (sag_sol_yukar_asag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (sag_sol_yukar_asag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sag_sol_yukar_asag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sag_sol_asag_yukar(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sag_sol_asag_yukar(a, x, y + 1, satir_say, sutun_say, sayac))		// sağ
				{
					(*sayac)++;
					return true;
				}
				if (sag_sol_asag_yukar(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (sag_sol_asag_yukar(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sag_sol_asag_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sag_asag_yukar_sol(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sag_asag_yukar_sol(a, x, y + 1, satir_say, sutun_say, sayac))		// sağ
				{
					(*sayac)++;
					return true;
				}
				if (sag_asag_yukar_sol(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sag_asag_yukar_sol(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sag_asag_yukar_sol(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sag_asag_sol_yukar(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sag_asag_sol_yukar(a, x, y + 1, satir_say, sutun_say, sayac))		// sağ
				{
					(*sayac)++;
					return true;
				}
				if (sag_asag_sol_yukar(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sag_asag_sol_yukar(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (sag_asag_sol_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sag_yukar_asag_sol(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sag_yukar_asag_sol(a, x, y + 1, satir_say, sutun_say, sayac))		// sağ
				{
					(*sayac)++;
					return true;
				}
				if (sag_yukar_asag_sol(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sag_yukar_asag_sol(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sag_yukar_asag_sol(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sag_yukar_sol_asag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sag_yukar_sol_asag(a, x, y + 1, satir_say, sutun_say, sayac))		// sağ
				{
					(*sayac)++;
					return true;
				}
				if (sag_yukar_sol_asag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sag_yukar_sol_asag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (sag_yukar_sol_asag(a, x + 1, y, satir_say, sutun_say, sayac))		//asağı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
//sol
bool sol_sag_yukar_asag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sol_sag_yukar_asag(a, x, y - 1, satir_say, sutun_say, sayac))		// sol
				{
					(*sayac)++;
					return true;
				}
				if (sol_sag_yukar_asag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (sol_sag_yukar_asag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sol_sag_yukar_asag(a, x + 1, y, satir_say, sutun_say, sayac))		//asağı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sol_sag_asag_yukar(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sol_sag_asag_yukar(a, x, y - 1, satir_say, sutun_say, sayac))		// sol
				{
					(*sayac)++;
					return true;
				}
				if (sol_sag_asag_yukar(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (sol_sag_asag_yukar(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sol_sag_asag_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sol_yukar_sag_asag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sol_yukar_sag_asag(a, x, y - 1, satir_say, sutun_say, sayac))		// sol
				{
					(*sayac)++;
					return true;
				}
				if (sol_yukar_sag_asag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sol_yukar_sag_asag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (sol_yukar_sag_asag(a, x + 1, y, satir_say, sutun_say, sayac))		//asağı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sol_yukar_asag_sag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sol_yukar_asag_sag(a, x, y - 1, satir_say, sutun_say, sayac))		// sol
				{
					(*sayac)++;
					return true;
				}
				if (sol_yukar_asag_sag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sol_yukar_asag_sag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sol_yukar_asag_sag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sol_asag_yukar_sag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sol_asag_yukar_sag(a, x, y - 1, satir_say, sutun_say, sayac))		// sol
				{
					(*sayac)++;
					return true;
				}
				if (sol_asag_yukar_sag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (sol_asag_yukar_sag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (sol_asag_yukar_sag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool sol_asag_sag_yukar(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (sol_asag_sag_yukar(a, x, y - 1, satir_say, sutun_say, sayac))		// sol
				{
					(*sayac)++;
					return true;
				}
				if (sol_asag_sag_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//aşaüı
				{
					(*sayac)++;
					return true;
				}
				if (sol_asag_sag_yukar(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (sol_asag_sag_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
//aşağı
bool asag_yukar_sol_sag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (asag_yukar_sol_sag(a, x + 1, y, satir_say, sutun_say, sayac))		// aşağı
				{
					(*sayac)++;
					return true;
				}
				if (asag_yukar_sol_sag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (asag_yukar_sol_sag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (asag_yukar_sol_sag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool asag_yukar_sag_sol(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (asag_yukar_sag_sol(a, x + 1, y, satir_say, sutun_say, sayac))		// aşağı
				{
					(*sayac)++;
					return true;
				}
				if (asag_yukar_sag_sol(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (asag_yukar_sag_sol(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (asag_yukar_sag_sol(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool asag_sol_sag_yukar(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (asag_sol_sag_yukar(a, x + 1, y, satir_say, sutun_say, sayac))		// aşağı
				{
					(*sayac)++;
					return true;
				}
				if (asag_sol_sag_yukar(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (asag_sol_sag_yukar(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (asag_sol_sag_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool asag_sol_yukar_sag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (asag_sol_yukar_sag(a, x + 1, y, satir_say, sutun_say, sayac))		// aşağı
				{
					(*sayac)++;
					return true;
				}
				if (asag_sol_yukar_sag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (asag_sol_yukar_sag(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (asag_sol_yukar_sag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool asag_sag_yukar_sol(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (asag_sag_yukar_sol(a, x + 1, y, satir_say, sutun_say, sayac))		// aşağı
				{
					(*sayac)++;
					return true;
				}
				if (asag_sag_yukar_sol(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (asag_sag_yukar_sol(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				if (asag_sag_yukar_sol(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool asag_sag_sol_yukar(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (asag_sag_sol_yukar(a, x + 1, y, satir_say, sutun_say, sayac))		// aşağı
				{
					(*sayac)++;
					return true;
				}
				if (asag_sag_sol_yukar(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (asag_sag_sol_yukar(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (asag_sag_sol_yukar(a, x - 1, y, satir_say, sutun_say, sayac))		//yukarı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
//yukarı
bool yukar_sol_sag_asag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (yukar_sol_sag_asag(a, x - 1, y, satir_say, sutun_say, sayac))		// yukarı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sol_sag_asag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sol_sag_asag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sol_sag_asag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool yukar_sol_asag_sag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (yukar_sol_asag_sag(a, x - 1, y, satir_say, sutun_say, sayac))		// yukarı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sol_asag_sag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sol_asag_sag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sol_asag_sag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool yukar_sag_sol_asag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (yukar_sag_sol_asag(a, x - 1, y, satir_say, sutun_say, sayac))		// yukarı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sag_sol_asag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sag_sol_asag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sag_sol_asag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool yukar_sag_asag_sol(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (yukar_sag_asag_sol(a, x - 1, y, satir_say, sutun_say, sayac))		// yukarı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sag_asag_sol(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sag_asag_sol(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_sag_asag_sol(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool yukar_asag_sag_sol(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (yukar_asag_sag_sol(a, x - 1, y, satir_say, sutun_say, sayac))		// yukarı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_asag_sag_sol(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_asag_sag_sol(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				if (yukar_asag_sag_sol(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool yukar_asag_sol_sag(int* a, int x, int y, int satir_say, int sutun_say, int* sayac) {
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a, x, y, sutun_say))
		{
			if (*((a + x * sutun_say) + y) == 4 || *((a + x * sutun_say) + y) == 1 || *((a + x * sutun_say) + y) == 2)
			{
				*((a + x * sutun_say) + y) = 6;
				if (yukar_asag_sol_sag(a, x - 1, y, satir_say, sutun_say, sayac))		// yukarı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_asag_sol_sag(a, x + 1, y, satir_say, sutun_say, sayac))		//aşağı
				{
					(*sayac)++;
					return true;
				}
				if (yukar_asag_sol_sag(a, x, y - 1, satir_say, sutun_say, sayac))		//sol
				{
					(*sayac)++;
					return true;
				}
				if (yukar_asag_sol_sag(a, x, y + 1, satir_say, sutun_say, sayac))		//sağ
				{
					(*sayac)++;
					return true;
				}
				*((a + x * sutun_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * sutun_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}

void en_kısa_yol(int* a, int x, int y) {
	int sayac1 = 0, sayac2 = 0, sayac3 = 0, sayac4 = 0, sayac5 = 0, sayac6 = 0, sayac7 = 0, sayac8 = 0, sayac9 = 0, sayac10 = 0, sayac11 = 0, sayac12 = 0, sayac13 = 0, sayac14 = 0, sayac15 = 0, sayac16 = 0, sayac17 = 0, sayac18 = 0, sayac19 = 0, sayac20 = 0, sayac21 = 0, sayac22 = 0, sayac23 = 0, sayac24 = 0;
	int min = 100000000000000;
	//sağ
	if (sag_sol_yukar_asag(a, 0, 0, x, y, &sayac1))
	{

	}
	else
	{
		sayac1 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sag_sol_asag_yukar(a, 0, 0, x, y, &sayac2))
	{
		if (sayac2 <= sayac1) {
			min = sayac2;
		}
	}
	else {
		sayac2 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sag_asag_yukar_sol(a, 0, 0, x, y, &sayac3))
	{
		if (sayac3 <= min)
		{
			min = sayac3;
		}
	}
	else
	{
		sayac3 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sag_asag_sol_yukar(a, 0, 0, x, y, &sayac4))
	{
		if (sayac4 <= min)
		{
			min = sayac4;
		}
	}
	else
	{
		sayac4 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sag_yukar_asag_sol(a, 0, 0, x, y, &sayac5))
	{
		if (sayac5 <= min)
		{
			min = sayac5;
		}
	}
	else
	{
		sayac5 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sag_yukar_sol_asag(a, 0, 0, x, y, &sayac6))
	{
		if (sayac6 <= min)
		{
			min = sayac6;
		}
	}
	else
	{
		sayac6 = NULL;
	}
	Geri_cevir(a, x, y);
	//sol
	if (sol_sag_yukar_asag(a, 0, 0, x, y, &sayac7))
	{
		if (sayac7 <= min)
		{
			min = sayac7;
		}
	}
	else
	{
		sayac7 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sol_sag_asag_yukar(a, 0, 0, x, y, &sayac8))
	{
		if (sayac8 <= min)
		{
			min = sayac8;
		}
	}
	else
	{
		sayac8 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sol_yukar_sag_asag(a, 0, 0, x, y, &sayac9))
	{
		if (sayac9 <= min)
		{
			min = sayac9;
		}
	}
	else
	{
		sayac9 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sol_yukar_asag_sag(a, 0, 0, x, y, &sayac10))
	{
		if (sayac10 <= min)
		{
			min = sayac10;
		}
	}
	else
	{
		sayac10 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sol_asag_yukar_sag(a, 0, 0, x, y, &sayac11))
	{
		if (sayac11 <= min)
		{
			min = sayac11;
		}
	}
	else
	{
		sayac11 = NULL;
	}
	Geri_cevir(a, x, y);
	if (sol_asag_sag_yukar(a, 0, 0, x, y, &sayac12))
	{
		if (sayac12 <= min)
		{
			min = sayac12;
		}
	}
	else
	{
		sayac12 = NULL;
	}
	Geri_cevir(a, x, y);
	//aşağı
	if (asag_yukar_sol_sag(a, 0, 0, x, y, &sayac13))
	{
		if (sayac13 <= min)
		{
			min = sayac13;
		}
	}
	else
	{
		sayac13 = NULL;
	}
	Geri_cevir(a, x, y);
	if (asag_yukar_sag_sol(a, 0, 0, x, y, &sayac14))
	{
		if (sayac14 <= min)
		{
			min = sayac14;
		}
	}
	else
	{
		sayac14 = NULL;
	}
	Geri_cevir(a, x, y);
	if (asag_sol_sag_yukar(a, 0, 0, x, y, &sayac15))
	{
		if (sayac15 <= min)
		{
			min = sayac15;
		}
	}
	else
	{
		sayac15 = NULL;
	}
	Geri_cevir(a, x, y);
	if (asag_sol_yukar_sag(a, 0, 0, x, y, &sayac16))
	{
		if (sayac16 <= min)
		{
			min = sayac16;
		}
	}
	else
	{
		sayac16 = NULL;
	}
	Geri_cevir(a, x, y);
	if (asag_sag_yukar_sol(a, 0, 0, x, y, &sayac17))
	{
		if (sayac17 <= min)
		{
			min = sayac17;
		}
	}
	else
	{
		sayac17 = NULL;
	}
	Geri_cevir(a, x, y);
	if (asag_sag_sol_yukar(a, 0, 0, x, y, &sayac18))
	{
		if (sayac18 <= min)
		{
			min = sayac18;
		}
	}
	else
	{
		sayac18 = NULL;
	}
	Geri_cevir(a, x, y);
	//yukarı
	if (yukar_sol_sag_asag(a, 0, 0, x, y, &sayac19))
	{
		if (sayac19 <= min)
		{
			min = sayac19;
		}
	}
	else
	{
		sayac19 = NULL;
	}
	Geri_cevir(a, x, y);
	if (yukar_sol_asag_sag(a, 0, 0, x, y, &sayac20))
	{
		if (sayac20 <= min)
		{
			min = sayac20;
		}
	}
	else
	{
		sayac20 = NULL;
	}
	Geri_cevir(a, x, y);
	if (yukar_sag_sol_asag(a, 0, 0, x, y, &sayac21))
	{
		if (sayac21 <= min)
		{
			min = sayac21;
		}
	}
	else
	{
		sayac21 = NULL;
	}
	Geri_cevir(a, x, y);
	if (yukar_sag_asag_sol(a, 0, 0, x, y, &sayac22))
	{
		if (sayac22 <= min)
		{
			min = sayac22;
		}
	}
	else
	{
		sayac22 = NULL;
	}
	Geri_cevir(a, x, y);
	if (yukar_asag_sag_sol(a, 0, 0, x, y, &sayac23))
	{
		if (sayac23 <= min)
		{
			min = sayac23;
		}
	}
	else
	{
		sayac23 = NULL;
	}
	Geri_cevir(a, x, y);
	if (yukar_asag_sol_sag(a, 0, 0, x, y, &sayac24))
	{
		if (sayac24 <= min)
		{
			min = sayac24;
		}
	}
	else
	{
		sayac24 = NULL;
	}
	Geri_cevir(a, x, y);
	//sag
	if (min == sayac1)
	{
		sag_sol_yukar_asag(a, 0, 0, x, y, &sayac1);
	}
	else if (min == sayac2)
	{
		sag_sol_asag_yukar(a, 0, 0, x, y, &sayac2);
	}
	else if (min == sayac3)
	{
		sag_asag_yukar_sol(a, 0, 0, x, y, &sayac3);
	}
	else if (min == sayac4)
	{
		sag_asag_sol_yukar(a, 0, 0, x, y, &sayac4);
	}
	else if (min == sayac5)
	{
		sag_yukar_asag_sol(a, 0, 0, x, y, &sayac5);
	}
	else if (min == sayac6)
	{
		sag_yukar_sol_asag(a, 0, 0, x, y, &sayac6);
	}
	//sol
	else if (min == sayac7)
	{
		sol_sag_yukar_asag(a, 0, 0, x, y, &sayac7);
	}
	else if (min == sayac8)
	{
		sol_sag_asag_yukar(a, 0, 0, x, y, &sayac8);
	}
	else if (min == sayac9)
	{
		sol_yukar_sag_asag(a, 0, 0, x, y, &sayac9);
	}
	else if (min == sayac10)
	{
		sol_yukar_asag_sag(a, 0, 0, x, y, &sayac10);
	}
	else if (min == sayac11)
	{
		sol_asag_yukar_sag(a, 0, 0, x, y, &sayac11);
	}
	else if (min == sayac12)
	{
		sol_asag_sag_yukar(a, 0, 0, x, y, &sayac12);
	}
	//aşağı
	else if (min == sayac13)
	{
		asag_yukar_sol_sag(a, 0, 0, x, y, &sayac13);
	}
	else if (min == sayac14)
	{
		asag_yukar_sag_sol(a, 0, 0, x, y, &sayac14);
	}
	else if (min == sayac15)
	{
		asag_sol_sag_yukar(a, 0, 0, x, y, &sayac15);
	}
	else if (min == sayac16)
	{
		asag_sol_yukar_sag(a, 0, 0, x, y, &sayac16);
	}
	else if (min == sayac17)
	{
		asag_sag_yukar_sol(a, 0, 0, x, y, &sayac17);
	}
	else if (min == sayac18)
	{
		asag_sag_sol_yukar(a, 0, 0, x, y, &sayac18);
	}
	//yukarı
	else if (min == sayac19)
	{
		yukar_sol_sag_asag(a, 0, 0, x, y, &sayac19);
	}
	else if (min == sayac20)
	{
		yukar_sol_asag_sag(a, 0, 0, x, y, &sayac20);
	}
	else if (min == sayac21)
	{
		yukar_sag_sol_asag(a, 0, 0, x, y, &sayac21);
	}
	else if (min == sayac22)
	{
		yukar_sag_asag_sol(a, 0, 0, x, y, &sayac22);
	}
	else if (min == sayac23)
	{
		yukar_asag_sag_sol(a, 0, 0, x, y, &sayac23);
	}
	else if (min == sayac24)
	{
		yukar_asag_sol_sag(a, 0, 0, x, y, &sayac24);
	}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Turkish");
	int secim = 0;
	int orj = 0;
	int counter = 0;
	int maze1[6][6] = {
		{1,3,3,3,3,3},
		{4,4,4,4,4,4},
		{3,4,3,4,3,4},
		{3,4,3,4,3,4},
		{4,4,4,3,3,3},
		{3,3,4,4,4,2}
	};
	int maze2[9][9] = {
		{1,3,3,3,3,3,3,3,3},
		{4,4,4,4,3,4,4,4,3},
		{3,4,3,4,3,3,3,4,3},
		{3,4,3,4,4,4,4,4,3},
		{3,4,3,3,3,3,3,4,3},
		{3,4,3,4,3,4,4,4,3},
		{3,4,3,4,3,4,3,3,3},
		{3,4,4,4,4,4,4,4,4},
		{3,3,3,3,3,3,3,3,2}
	};
	int maze3[5][11] = {
		{1,3,3,3,3,3,3,3,3,3,3},
		{4,4,4,4,3,4,4,4,4,4,3},
		{3,4,3,4,3,4,3,4,3,3,3},
		{3,4,3,4,4,4,3,4,4,4,4},
		{3,3,3,3,3,3,3,3,3,3,2}
	};
	int maze4[11][15] = {
		{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{4,4,3,4,4,4,4,4,4,4,3,4,4,4,3},
		{3,4,3,4,3,3,3,4,3,4,3,3,3,4,3},
		{3,4,3,4,3,4,4,4,3,4,4,4,4,4,3},
		{3,4,3,4,3,4,3,3,3,4,3,3,3,3,3},
		{3,4,3,4,3,4,4,4,3,4,3,4,4,4,3},
		{3,4,3,4,3,3,3,4,3,3,3,4,3,4,3},
		{3,4,3,4,3,4,3,4,4,4,4,4,3,4,3},
		{3,4,3,4,3,4,3,3,3,3,3,3,3,4,3},
		{3,4,4,4,4,4,3,4,4,4,4,4,4,4,4},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,2},
	};
	int maze5[6][12] = {
		{1,3,4,4,4,3,3,4,3,4,4,3},
		{4,3,4,4,4,4,4,3,4,3,3,3},
		{4,4,4,4,4,4,4,3,4,3,4,3},
		{3,4,3,4,3,4,3,4,4,4,4,4},
		{3,4,3,4,4,4,4,4,3,3,3,4},
		{4,4,4,3,4,4,4,4,4,4,4,2}
	};
	int maze6[9][9] = {
		{1,3,3,3,3,3,3,3,3},
		{4,3,4,4,4,4,4,4,3},
		{4,3,4,3,3,3,3,4,3},
		{4,3,4,4,4,3,3,4,3},
		{4,3,3,4,3,4,3,4,3},
		{4,4,3,4,4,4,3,4,3},
		{4,4,4,4,4,3,3,4,3},
		{3,3,3,3,3,3,3,4,3},
		{3,3,3,3,3,3,3,4,2}
	};
	while (1)
	{
		//ilk seçim ekranı
		printf("****************** Labirentler ***********************\n1)Labirent 1(6X6)\n2)Labirent 2(9X9)\n3)Labirent 3(5X11)\n4)Labirent 4(11X15)\n5)Labirent 5(6X12)\n6)Labirent 6\n7)Rastgele\n8)Seçmeli(En Büyük Matrix 31x31)\n9)Çıkış\nSeçim : ");
		scanf_s("%d", &secim);
		if (secim == 1)
		{
			//1.Matrix
			system("cls");
			printf("************************* 1.Labirent ************************\n");
			Yaz(maze1, 6, 6);
			printf("************************** Çözüm 1 **************************\n");
			en_kısa_yol(maze1, 6, 6);
			Yaz(maze1, 6, 6);
			printf("**************************************************************\n");
			lejant();
			Geri_cevir(maze1, 6, 6);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 2)
		{
			//2.matrix
			system("cls");
			printf("************************* 2.Labirent ************************\n");
			Yaz(maze2, 9, 9);
			printf("************************** Çözüm 2 **************************\n");
			en_kısa_yol(maze2, 9, 9);
			Yaz(maze2, 9, 9);
			printf("*************************************************************\n");
			lejant();
			Geri_cevir(maze2, 9, 9);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 3)
		{
			//3.Matrix
			system("cls");
			printf("************************* 3.Labirent ************************\n");
			Yaz(maze3, 5, 11);
			printf("************************** Çözüm 3 **************************\n");
			en_kısa_yol(maze3, 5, 11);
			Yaz(maze3, 5, 11);
			printf("*************************************************************\n");
//			printf("Lejant:\nS = Başlangıç \t G = Son \t # = Duvar \t . = Yol \t O = Gerçek Yol\nDevam etmek için bir tuşa basın\n");
			lejant();
			Geri_cevir(maze3, 5, 11);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 4)
		{
			//4.Matrix
			system("cls");
			printf("************************* 4.Labirent ************************\n");
			Yaz(maze4, 11, 15);
			printf("************************** Çözüm 4 **************************\n");
			en_kısa_yol(maze4, 11, 15);
			Yaz(maze4, 11, 15);
			printf("*************************************************************\n");
			lejant();
			Geri_cevir(maze4, 11, 15);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 5) {
			//5.Matrix
			system("cls");
			printf("************************* 5.Labirent ************************\n");
			Yaz(maze5, 6, 12);
			printf("************************** Çözüm 5 **************************\n");
			en_kısa_yol(maze5, 6, 12);
			Yaz(maze5, 6, 12);
			printf("*************************************************************\n");
			lejant();
			Geri_cevir(maze5, 6, 12);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 6) {
			//6.Matrix
			system("cls");
			printf("************************* 6.Labirent ************************\n");
			Yaz(maze6, 9, 9);
			printf("************************** Çözüm 6 **************************\n");
			en_kısa_yol(maze6, 9, 9);
			Yaz(maze6, 9, 9);
			printf("**************************************************************\n");
			lejant();
			Geri_cevir(maze6, 9, 9);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 7)
		{
			int x = 0, y = 0, counter = 0;
			while (1)
			{
				system("cls");
				printf("****************** Rastgele Labirent ***********************\n");
				printf("Satır ve Sütun değerlerini girin (Ne kadar büyük girerseniz bekleme süreniz o kadar uzun olur):\n");
				printf("Satır = ");
				scanf_s("%d", &x);
				printf("Sütun = ");
				scanf_s("%d", &y);
				if (x <= 0 || y <= 0) {
					printf("0 dan düşük olamaz !\n");
					Sleep(1000);
					system("cls");
					continue;
				}
				else
				{
					break;
				}
			}
			system("cls");
			int* rastgele = (int*)malloc(x * y * sizeof(int));
			clock_t begin = clock();
			while (1)
			{
				Matrix_Yap(rastgele, x, y);
				if (Yol_bul(rastgele, 0, 0, x, y))
				{
					printf("İsteklerinize uygun bir Labirent oluşturuldu !\n");
					system("cls");
					clock_t end = clock();
					double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
					printf("istatistikler :\n");
					printf("Deneme Sayısı = %d\t Geçen Süre = %f\n", counter, time_spent);
					printf("*********************** Oluşan Matrix ***********************\n");
					Geri_cevir(rastgele, x, y);
					Yaz(rastgele, x, y);
					en_kısa_yol(rastgele, x, y);
					printf("*********************** Çözüm Matrixi ************************\n");
					Yaz(rastgele, x, y);
					printf("**************************************************************\n");
					lejant();
					break;
				}
				++counter;
				continue;
			}
			//printf("Devam etmek için bir tuşa basın");
			getch();
			system("cls");
			//break;
			continue;
		}
		else if (secim == 8)
		{
			int satir = 0;
			int sutun = 0;
			printf("*********************** Seçmeli Labirent ***********************\n");
			printf("Orijinal Labirent :\n");
			int secmeli[31][31] = {
			   /*1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 */
		/*1*/	{1,3,3,3,3,3,3,3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
		/*2*/	{4,4,4,4,4,4,3,4,4, 4, 4, 4, 4, 4, 4, 4, 4 ,4 ,4 ,4 ,4 ,4 ,3, 4, 4 ,4, 3, 4, 4, 4, 3},
		/*3*/	{3,4,3,3,3,4,3,4,3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 4, 3, 4, 3, 3, 3, 4, 3},
		/*4*/	{3,4,3,4,4,4,3,4,3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 4, 4, 3, 4, 3},
		/*5*/	{3,4,3,4,3,3,3,4,3, 4, 3, 3, 3, 4, 3, 3, 3, 4, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3},
		/*6*/	{3,4,3,4,3,4,4,4,3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3},
		/*7*/	{3,4,3,3,3,4,3,3,3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 4, 3, 3, 3, 4, 3},
		/*8*/	{3,4,4,4,3,4,4,4,3, 4, 4, 4, 4, 4, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3},
		/*9*/	{3,3,3,4,3,3,3,4,3, 4, 3, 4, 3, 3, 3, 4, 3, 3, 3, 4, 3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3},
		/*10*/	{3,4,4,4,3,4,4,4,3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3},
		/*11*/	{3,4,3,4,3,4,3,3,3, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3, 4, 3},
		/*12*/	{3,4,3,4,3,4,4,4,4, 4, 3, 4, 3, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3, 4, 3},
		/*13*/	{3,4,3,3,3,3,3,3,3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 4, 3, 4, 3, 4, 3},
		/*14*/	{3,4,3,4,4,4,4,4,4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3, 4, 3},
		/*15*/	{3,4,3,4,3,3,3,3,3, 3, 3, 4, 3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3, 4, 3},
		/*16*/	{3,4,4,4,3,4,3,4,4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3},
		/*17*/	{3,4,3,3,3,4,3,4,3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 4, 3},
		/*18*/	{3,4,4,4,4,4,3,4,3, 4, 3, 4, 4, 4, 4, 4, 4, 4, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 3},
		/*19*/	{3,3,3,3,3,4,3,4,3, 4, 3, 4, 3, 4, 3, 3, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 3, 3, 4, 3},
		/*20*/	{3,4,4,4,4,4,3,4,3, 4, 3, 4, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 4, 4, 4, 4, 3, 4, 3},
		/*21*/	{3,4,3,3,3,3,3,4,3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 4, 3, 3, 3, 4, 3, 3, 3},
		/*22*/	{3,4,3,4,3,4,4,4,3, 4, 4, 4, 3, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 4, 4, 3},
		/*23*/	{3,4,3,4,3,4,3,3,3, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 4, 3, 4, 3, 4, 3, 4, 3, 3, 3, 4, 3},
		/*24*/	{3,4,3,4,3,4,4,4,3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 3, 4, 4, 4, 3, 4, 3, 4, 3},
		/*25*/	{3,4,3,4,3,3,3,4,3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 4, 3, 3, 3, 4, 3, 4, 3, 4, 3},
		/*26*/	{3,4,3,4,4,4,3,4,4, 4, 3, 4, 4, 4, 3, 4, 3, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 3, 4, 3},
		/*27*/	{3,4,3,3,3,4,3,3,3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3},
		/*28*/	{3,4,4,4,3,4,4,4,3, 4, 4, 4, 3, 4, 3, 4, 3, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 3},
		/*29*/	{3,3,3,4,3,3,3,4,3, 3, 3, 3, 3, 4, 3, 3, 3, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 4, 3, 4, 3},
		/*30*/	{3,4,4,4,4,4,4,4,4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4},
		/*31*/	{3,3,3,3,3,3,3,3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2}
			};
			Yaz(secmeli, 31, 31);
			while (1)
			{
				printf("Ne kadarını kullanmak istiyorsunuz ? (her zaman bir sonuç çıkamayabilir)\n");
				printf("satir = ");
				scanf_s("%d", &satir);
				printf("sutun = ");
				scanf_s("%d", &sutun);

				if ((satir > 31 || sutun > 31 || satir <= 0 || sutun <= 0))
				{
					printf("girilen sayı 31 ile 0 arasında olmak zorundadır (tavsiye : en az 3x3 yaparsanız daha güzel bir sonuç çıkar)\n");
					printf("Devam etmek için bir tuşa basın\n");
					getch();
					system("cls");
					continue;
				}
				else
				{
					break;
				}

			}
			
			system("cls");
			int* secili = (int*)calloc(satir * sutun , sizeof(int));
			for (int i = 0; i < satir; i++)
			{
				for (int j = 0; j < sutun; j++)
				{
					*((secili + sutun * i) + j) = secmeli[i][j];
				}
			}
			system("cls");
			//giris_cıkıs(secili,satir,sutun);
			*((secili + 0 * sutun) + 0) = 1;
			*(((secili + sutun * (satir - 1)) + (sutun - 1))) = 2;

			printf("**************** Elde Kalan Labirent ****************\n");
			Yaz(secili, satir, sutun);
			printf("*****************************************************\n");
			if (Yol_bul(secili,0,0,satir,sutun))
			{
				Yaz(secili, satir, sutun);
			}
			else
			{
				for (int i = satir - 1; i >= 0; i--)
				{
					//giris_cıkıs(secili, satir, sutun);
					*((secili + 0 * sutun) + 0) = 1;
					*(((secili + sutun * (satir - 1)) + (sutun - 1))) = 2;
					if (Yol_bul(secili, 0, 0, satir, sutun))
					{
						Geri_cevir(secili, satir, sutun);
						printf("********** Yolun Çıkması İçin Gerekli Olan Labirent **********\n");
						Yaz(secili, satir, sutun);
						printf("**************************************************************\n");
						en_kısa_yol(secili, satir, sutun);
						Yaz(secili, satir, sutun);
						break;
					}
					else
					{
						*((secili + sutun * i) + (sutun - 1)) = 4;
					}
				}
			}
			*((secili + 0 * sutun) + 0) = 1;
			*(((secili + sutun * (satir - 1)) + (sutun - 1))) = 2;
			if (Yol_bul(secili, 0, 0, satir, sutun))
			{
				Yaz(secili, satir, sutun);
			}
			else
			{
				for (int i = sutun - 1; i >= 0; i--)
				{
					//giris_cıkıs(secili, satir, sutun);
					*((secili + 0 * sutun) + 0) = 1;
					*(((secili + sutun * (satir - 1)) + (sutun - 1))) = 2;

					if (Yol_bul(secili, 0, 0, satir, sutun))
					{
						Geri_cevir(secili, satir, sutun);
						printf("********** Yolun Çıkması İçin Gerekli Olan Labirent **********\n");
						Yaz(secili, satir, sutun);
						printf("**************************************************************\n");
						en_kısa_yol(secili, satir, sutun);
						Yaz(secili, satir, sutun);
						break;
					}
					else
					{
						*((secili + sutun * (satir - 1)) + i) = 4;
					}
				}
			}
			lejant();
			getch();
			system("cls");
			continue;
		}
		else if (secim == 9)
		{
			printf("Çıkış yapılıyor...");
			exit("1");
		}
		
		else
		{
			printf("Yanlış seçim yaptınız !\n");
			Sleep(500);
			system("cls");
		}
	}
	return 0;
}
