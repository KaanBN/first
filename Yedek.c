#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
void Matrix_Yap(int* dizi, int x, int y) {		//random matrix generator
	for (int a = 0; a < x; a++)
	{
		for (int b = 0; b < y; b++) {
			if (a == 0 && b == 0)
			{
				*((dizi + x * a) + b) = 1;
			}
			else if (a == x-1 && b == y-1)
			{
				*((dizi + x * a) + b) = 2;
			}
			else
			{
				*((dizi + x * a) + b) = rand() % 2 + 3;
			}
		}
	}
}
void Geri_cevir(int* dizi,int x,int y) {		//Matrixleri orijinal haline döndürür
	for (int a = 0; a < x; a++)
	{
		for (int b = 0; b < y; b++) {
			if (*((dizi + x * a) + b) == 6)
			{
				if (a == 0 && b == 0)
				{
					*((dizi + x * a) + b) = 1;
				}
				else if (a == x - 1 && b == y - 1)
				{
					*((dizi + x * a) + b) = 2;
				}
				else
				{
					*((dizi + x * a) + b) = 4;
				}
			}
		}
	}
}
bool geldik_mi(int *a,int x,int y,int satir_say) {		// Malum soru
	if (*((a + x * satir_say) + y) == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Yaz(int *a,int x,int y) {		//matrix Yazdırılıyor
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y;j++) {
			if (*((a + i * y) + j) == 1)
			{
				printf("S");
			}
			else if (*((a + i * y) + j) == 2)
			{
				printf("G");
			}
			else if (*((a + i * y) + j) == 3)
			{
				printf("#");
			}
			else if (*((a + i * y) + j) == 4)
			{
				printf(".");
			}
			else if (*((a + i * y) + j) == 5)
			{
				printf("X");
			}
			else if (*((a + i * y) + j) == 6)
			{
				printf("O");
			}
		}
		printf("\n");
	}
}
bool Yol_bul(int *a,int x,int y,int satir_say,int sutun_say) {		//yolumuzu bulduran
	if (x >= 0 && x < satir_say && y >= 0 && y < sutun_say)
	{
		if (!geldik_mi(a,x,y,satir_say))
		{
			if (*((a + x * satir_say) + y) == 4 || *((a + x * satir_say) + y) == 1 || *((a + x * satir_say) + y) == 2)
			{
				*((a + x * satir_say) + y) = 6;
				if (Yol_bul(a, x, y + 1,satir_say,sutun_say))		// sağ
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
				*((a + x * satir_say) + y) = 4;		//gidilip olmayan yerler
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			*((a + x * satir_say) + y) = 6;		//sonu da O yapıyor
			return true;
		}
	}
	else
	{
		return false;
	}
}
int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Turkish");
	int secim = 0;
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
		{4,4,3,4,3,4,4,4,3},
		{3,4,3,4,3,3,3,4,3},
		{3,4,3,4,4,4,4,4,3},
		{3,4,3,3,3,3,3,4,3},
		{3,4,3,4,3,4,4,4,3},
		{3,4,3,4,3,4,3,3,3},
		{3,4,4,4,4,4,4,4,4},
		{3,3,3,3,3,3,3,3,2}
	};
	while (1)
	{
		//ilk seçim ekranı
		printf("****************** Bulmacalar ***********************\n1.Bulmaca\n2.Bulmaca\n3.Rastgele\n4.Çıkış\nSeçim : ");
		scanf_s("%d", &secim);
		if (secim == 1)
		{
			//1.Matrixi yazdıran yapan
			system("cls");
			printf("*************************\n");
			printf("1.Bulmaca :\n");
			Yaz(maze1, 6, 6);
			printf("*************************\n");
			printf("1.Çözüm : \n");
			Yol_bul(maze1, 0, 0, 6, 6);
			Yaz(maze1, 6, 6);
			printf("*************************\n");
			printf("Lejant:\nS = Başlangıç \t G = Son \t # = Duvar \t . = Yol \t O = Gerçek Yol\nDevam etmek için bir tuşa basın\n");
			Geri_cevir(maze1, 6, 6);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 2)
		{
			system("cls");
			printf("*************************\n");
			printf("1.Bulmaca :\n");
			Yaz(maze2, 9, 9);
			printf("*************************\n");
			printf("1.Çözüm : \n");
			Yol_bul(maze2, 0, 0, 9, 9);
			Yaz(maze2, 9, 9);
			printf("*************************\n");
			printf("Lejant:\nS = Başlangıç \t G = Son \t # = Duvar \t . = Yol \t O = Gerçek Yol\nDevam etmek için bir tuşa basın\n");
			Geri_cevir(maze2, 6, 6);
			getch();
			system("cls");
			continue;
		}
		else if (secim == 3)
		{
			int counter = 0;
			int x = 0;
			int y = 0;
			printf("****************************Rastgele Seçim****************************\nX ve Y değerlerini girin\nX = ");
			scanf_s("%d", &x);
			printf("Y = ");
			scanf_s("%d", &y);
			int* rastgele = (int*)malloc(x * y * sizeof(int));
			while (true)
			{
				Matrix_Yap(rastgele, x, y);
				if (Yol_bul(rastgele, 0, 0, x, y))
				{
					system("cls");
					printf("Sonuç oluşana kadar %d defa denendi\n", counter);
					printf("*************************\n");
					printf("Oluşan Matrix : \n");
					Geri_cevir(rastgele, x, y);
					Yaz(rastgele, x, y);
					printf("*************************\n");
					printf("Çözüm : \n");
					Yol_bul(rastgele, 0, 0, x, y);
					Yaz(rastgele, x, y);
					printf("*************************\n");
					printf("Lejant:\nS = Başlangıç \t G = Son \t # = Duvar \t . = Yol \t O = Gerçek Yol\nDevam etmek için bir tuşa basın\n");
					Geri_cevir(rastgele, x, y);
					getch();
					system("cls");
					break;
				}
				else
				{
					counter++;
					continue;
				}
			}
			continue;
		}
		else if (secim == 4)
		{
			printf("Çıkış yapılıyor...");
			exit("0");
		}
		else
		{
			printf("Yanlış seçim yaptınız !\n");
			Sleep(500);
			system("cls");
		}
	}
}
