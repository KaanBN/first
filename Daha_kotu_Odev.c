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
	printf("Devam etmek için bir tuşa basın\n");
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
void naber_naber(int* dizi, int num_x, int num_y) {
	printf("Dinamik moda girmek için \"d\" tuşuna basın.\n");
	char sa;
	int adet = 0;
	int deger = 0;
	int x = 0, y = 0;
	sa = getch();
	if (sa == 'd')
	{
		bas_dinamik :
		system("cls");
		printf("*************** Dinamik Moda Hoş Geldiniz ***************\n");
		printf("Orijinal Matrix : \n");
		Yaz(dizi, num_x, num_y);
		printf("Kaç adet değer değişecek ?(0 yazarak çıkabilirsiniz.)\n");
		scanf_s("%d", &adet);
		if (adet == 0)
		{
			system("cls");
			goto son;
		}
		else if (adet < 0 || adet > (num_x * num_y) )
		{
			printf("Geçersiz değer girdiniz");
			Sleep(1000);
			goto bas_dinamik;
		}
		for (int adet_s = 0; adet_s < adet; adet_s++)
		{
		bas_sa:
			system("cls");
			for (int i = 0; i < num_y; i++)
			{
				if (i < 10)
				{
					printf("%d ", i);
				}
				else if (i >= 10)
				{
					printf("%d", i);
				}
			}
			printf("\n");
			Yaz(dizi, num_x, num_y);
			printf("Değiştirmek istediğiniz değerin konumunu belirtin (UNUTMAYIN! diziler 0'dan başlar.)\n(-1 yazarak istediğiniz an çıkış yapabilirsiniz.)\n");
			printf("Hangi Satırda = ");
			scanf_s("%d", &x);
			if (x < -1 || x > num_x - 1)
			{
				printf("Geçersiz değer girdiniz !\n");
				Sleep(1000);
				goto bas_sa;
			}
			else if (x == -1)
			{
				system("cls");
				break;
			}
			printf("Hangi Sütunda = ");
			scanf_s("%d", &y);
			if (y < -1 || y > num_x - 1)
			{
				printf("Geçersiz değer girdiniz !\n");
				Sleep(1000);
				goto bas_sa;
			}
			else if (y == -1)
			{
				system("cls");
				
				break;
			}
			if ((x == 0 && y == 0) || (x == num_x - 1 && y == num_y - 1))
			{
				printf("Malesef başlangıç ve son değerlerini değiştiremezsiniz!\n");
				goto bas_sa;
			}
			printf("Yeni değer (3 = Duvar, 4 = Yol): ");
			scanf_s("%d", &deger);
			if (deger > 4 || deger < 3)
			{
				printf("Geçersiz Değer !\n");
				Sleep(1000);
				goto bas_sa;
			}
			system("cls");
			*((dizi + x * num_y) + y) = deger;
			
			system("cls");
		}
		printf("Yeni Matrix :\n");
		Yaz(dizi, num_x, num_y);
		printf("Devam etmek için bir tuşa basın\n");
		getch();
	son:
		system("cls");
	}

}



int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Turkish");
	int secim = 0;
	int counter = 0;
	int sayac = 0;
	int orj_maze1[6][6] = {
		{1,3,3,3,3,3},
		{4,4,4,4,4,4},
		{3,4,3,4,3,4},
		{3,4,3,4,3,4},
		{4,4,4,3,3,3},
		{3,3,4,4,4,2}
	};
	int orj_maze2[9][9] = {
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
	int orj_maze3[5][11] = {
		{1,3,3,3,3,3,3,3,3,3,3},
		{4,4,4,4,3,4,4,4,4,4,3},
		{3,4,3,4,3,4,3,4,3,3,3},
		{3,4,3,4,4,4,3,4,4,4,4},
		{3,3,3,3,3,3,3,3,3,3,2}
	};
	int orj_maze4[11][15] = {
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
	int orj_maze5[6][12] = {
		{1,3,4,4,4,3,3,4,3,4,4,3},
		{4,3,4,4,4,4,4,3,4,3,3,3},
		{4,4,4,4,4,4,4,3,4,3,4,3},
		{3,4,3,4,3,4,3,4,4,4,4,4},
		{3,4,3,4,4,4,4,4,3,3,3,4},
		{4,4,4,3,4,4,4,4,4,4,4,2}
	};
	int orj_maze6[9][9] = {
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
		printf("****************** Seçim Ekranı ***********************\n1)Labirent 1(6X6)\n2)Labirent 2(9X9)\n3)Labirent 3(5X11)\n4)Labirent 4(11X15)\n5)Labirent 5(6X12)\n6)Labirent 6(9X9)\n7)Rastgele\n8)Seçmeli(En Büyük Matrix 31x31)\n9)Kendiniz Yaratın(Sandbox)\n10)Orijinale Çevir\n11)Çıkış\nSeçim : ");
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
			naber_naber(maze1, 6, 6);
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
			naber_naber(maze2, 9, 9);
			
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
			naber_naber(maze3, 5, 11);
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
			naber_naber(maze4, 11, 15);
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
			naber_naber(maze5, 6, 12);
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
			naber_naber(maze6, 9, 9);
			system("cls");
			continue;
		}
		//rastgele
		else if (secim == 7)
		{
			int x = 0, y = 0, counter = 0;
			while (1)
			{
				system("cls");
				printf("****************** Rastgele Labirent ***********************\n");
				printf("Satır ve Sütun değerlerini girin (Ne kadar büyük girerseniz bekleme süreniz o kadar uzun olur):\n(0 değerini girerek çıkabilirsiiniz)\n");
				printf("Satır = ");
				scanf_s("%d", &x);
				if (x == 0)
				{
					system("cls");
					goto cıkıs;
				}
				else if (x < 2)
				{
					printf("1 ve 1 den düşük olamaz !\n");
					Sleep(1000);
					system("cls");
					continue;
				}
				else if (x > 15)
				{
					printf("15 ten büyük olamaz");
					Sleep(1000);
					system("cls");
					continue;
				}
				printf("Sütun = ");
				scanf_s("%d", &y);
				if (y == 0) {
					system("cls");
					goto cıkıs;
				}
				else if (y < 2)
				{
					printf("1 ve 1 den düşük olamaz !\n");
					Sleep(1000);
					system("cls");
					continue;
				}
				else if (y > 15)
				{
					printf("15 ten büyük olamaz");
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
		}	//rastgele
		//seçmeli
		else if (secim == 8)
		{
			system("cls");
			int duvar_sayac = 0;
			int satir = 0;
			int sutun = 0;
		secmeli_bas:
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

			while (1)		//satır sütun sayısı alınır
			{
				printf("Ne kadarını kullanmak istiyorsunuz ? (tavsiye : en az 4x4 yaparsanız daha güzel bir sonuç çıkar)\n0 yazarak çıkış yapabilirsiniz\n");
				printf("Satır = ");
				scanf_s("%d", &satir);
				if (satir == 0)
				{
					system("cls");
					goto cıkıs;
				}
				else if (satir > 31 || satir <= 2)
				{
					printf("girilen sayı 31 ile 3 arasında olmak zorundadır (tavsiye : en az 4x4 yaparsanız daha güzel bir sonuç çıkar)\n");
					printf("Devam etmek için bir tuşa basın\n");
					getch();
					system("cls");
					goto secmeli_bas;
				}
				printf("Sütun = ");
				scanf_s("%d", &sutun);

				if (sutun == 0)
				{
					system("cls");
					goto cıkıs;
				}
				else if (sutun > 31 || sutun <= 2)
				{
					printf("girilen sayı 31 ile 3 arasında olmak zorundadır (tavsiye : en az 4x4 yaparsanız daha güzel bir sonuç çıkar)\n");
					printf("Devam etmek için bir tuşa basın\n");
					getch();
					system("cls");
					goto secmeli_bas;
				}
				else
				{
					break;
				}

			}

			system("cls");
			int* secili = (int*)calloc(satir * sutun, sizeof(int));
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
			printf("\n\n");
			if (Yol_bul(secili, 0, 0, satir, sutun))
			{
				Yaz(secili, satir, sutun);
				goto devamke;
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
						printf("Kırılan duvar sayısı: %d\n", duvar_sayac);
						Yaz(secili, satir, sutun);
						printf("**************************************************************\n");
						en_kısa_yol(secili, satir, sutun);
						Yaz(secili, satir, sutun);
						printf("\n\n");
						break;
					}
					else
					{
						if (*((secili + sutun * i) + (sutun - 1)) == 3)
						{
							++duvar_sayac;
						}
						*((secili + sutun * i) + (sutun - 1)) = 4;
					}
				}
			}
			for (int i = 0; i < satir; i++)
			{
				for (int j = 0; j < sutun; j++)
				{
					*((secili + sutun * i) + j) = secmeli[i][j];
				}
			}
			*((secili + 0 * sutun) + 0) = 1;
			*(((secili + sutun * (satir - 1)) + (sutun - 1))) = 2;
			duvar_sayac = 0;
			if (Yol_bul(secili, 0, 0, satir, sutun))
			{
				Yaz(secili, satir, sutun);
				goto devamke;
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
						printf("Kırılan duvar sayısı: %d\n", duvar_sayac);
						Yaz(secili, satir, sutun);
						printf("**************************************************************\n");
						en_kısa_yol(secili, satir, sutun);
						Yaz(secili, satir, sutun);
						printf("\n\n");
						break;
					}
					else
					{
						if (*((secili + sutun * i) + (sutun - 1)) == 3)
						{
							++duvar_sayac;
						}
						*((secili + sutun * (satir - 1)) + i) = 4;
					}
				}
			}
		devamke:
			lejant();
			getch();
			system("cls");
			continue;
		}
		//sandbox
		else if (secim == 9)
		{
			while (1)
			{
				int satir = 0;
				int sutun = 0;
				system("cls");
				printf("************* Sandbox Moduna Hoş Geldiniz *************\n");
				printf(ANSI_COLOR_RED"> Burada kendi labirentinizi oluşturabilrisiniz. Ancak belli kurallara uyulmak zorundadır, yoksa labirent düzgün çalışmaz. <\n"ANSI_COLOR_RESET);
				printf(ANSI_COLOR_GREEN "1)Başlangıç yapacağınız yeri 1 ile işaretlemelisiniz ve 0x0 noktasında olmak zorundadır\n" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_GREEN "2)Labirentin son bulacağı yeri 2 ile işaretlemelisiniz ve sağ alt köşeye (SatırXSütun) Koymak zorundasınız\n" ANSI_COLOR_RESET);
				printf(ANSI_COLOR_BLUE"3)Duvarlar 3 ile işaret edilmeli\n"ANSI_COLOR_RESET);
				printf(ANSI_COLOR_YELLOW"4)Yollar 4 ile işaret edilmeli\n"ANSI_COLOR_RESET);
				printf("Okudum onaylıyorum.");
				getch();
				system("cls");
				printf("Satır ve sütun sayısını girin \n(0 girerek ise bu ekrandan çıkış yapabilirsiniz.)\n(Tavsiye : En az 4X4 girerseniz daha düzgün sonuçlar elde edersiniz.)\n");
				printf("Satır = ");
				scanf_s("%d", &satir);
				if (satir == 0)
				{
					system("cls");
					break;
				}
				printf("Sutun = ");
				scanf_s("%d", &sutun);
				if (satir == 0 || sutun == 0)
				{
					system("cls");
					break;
				}
				else if (satir < 0 || sutun < 0)
				{
					printf("Tabiki 0 dan düşük değer giremezsiniz.");
					getch();
					system("cls");
					continue;
				}
				else
				{
					int* sandbox = (int*)malloc(satir * sutun * sizeof(int));
					for (int i = 0; i < satir; i++)
					{
						for (int j = 0; j < sutun; j++) {
							if (i == 0 && j == 0)
							{
								*((sandbox + (_int64)sutun * i) + j) = 1;
								Yaz(sandbox, satir, sutun);
								system("cls");
							}
							else if (i == satir - 1 && j == sutun - 1)
							{
								*((sandbox + (_int64)sutun * i) + j) = 2;
								Yaz(sandbox, satir, sutun);
							}
							else
							{
							al:
								Yaz(sandbox, satir, sutun);
								printf("\n");
								printf("Çıkmak için istediğiniz an -1 değerini girebilirsiniz\n");
								printf("1 = Başlangıç \t 2 = Son \t 3 = Duvar \t 4 = Yol\n");
								printf("Şu an %d. satırın %d. elemanını yazdırıyorsunuz \n", i + 1, j + 1);
								scanf_s("%d", ((sandbox + sutun * i) + j));
								system("cls");
								if (*((sandbox + (_int64)sutun * i) + j) == -1)
								{
									goto cıkıs;
								}
								else if (*((sandbox + (_int64)sutun * i) + j) > 4 || *((sandbox + (_int64)sutun * i) + j) < -2 || *((sandbox + (_int64)sutun * i) + j) == 0)
								{
									printf("öyle bir değer bulunmamaktadır!\n");
									goto al;
								}
								else if (*((sandbox + (_int64)sutun * i) + j) == 1 || *((sandbox + (_int64)sutun * i) + j) == 2)
								{
									printf("Giriş ve çıkış zaten otomatik olarak belirlenmiştir\n");
									goto al;
								}
							}
						}
						printf("Yeni Satıra Geçiş Yaptınız!\n");
					}
					system("cls");
					printf("****************** Oluşturduğunuz Labirent ******************\n");
					Yaz(sandbox, satir, sutun);
					if (Yol_bul(sandbox, 0, 0, satir, sutun))
					{
						printf("************************* Sonuç *************************\n");
						en_kısa_yol(sandbox, satir, sutun);
						Yaz(sandbox, satir, sutun);
						lejant();
						getch();
						system("cls");
						break;
					}
					else
					{
						printf("Malesef çıkışı olmayan bir labirent girmiş bulunmaktasınız :(\nHernhangi bir tuşa basarak çıkış yapabilrisiniz.\n");
						getch();
						system("cls");
						break;
					}

				cıkıs:
					break;
				}
			}
		}
		else if (secim == 10)
		{
			system("cls");
			printf("Orijinale çevriliyor...Maze1\n");
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++) {
					maze1[i][j] = orj_maze1[i][j];
				}
			}
			printf("Orijinale çevriliyor...Maze2\n");
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++) {
					maze2[i][j] = orj_maze2[i][j];
				}
			}
			printf("Orijinale çevriliyor...Maze3\n");
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 11; j++) {
					maze3[i][j] = orj_maze3[i][j];
				}
			}
			printf("Orijinale çevriliyor...Maze4\n");
			for (int i = 0; i < 11; i++)
			{
				for (int j = 0; j < 15; j++) {
					maze4[i][j] = orj_maze4[i][j];
				}
			}
			printf("Orijinale çevriliyor...Maze5\n");
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 12; j++) {
					maze5[i][j] = orj_maze5[i][j];
				}
			}
			printf("Orijinale çevriliyor...Maze6\n");
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++) {
					maze6[i][j] = orj_maze6[i][j];
				}
			}
			printf("Bütün matrixler orijinal haline çevrildi\nDevam");
			getch();
			system("cls");
		}
		//çıkış
		else if (secim == 11)
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
