#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void ekranTemizle() {
    printf("ekran temizleniyor");
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(1000);
    system("cls");
}

int main1()
{
    char ac,cýk = 'u',tem = 'u';
    int satir1, sutun1, sat, sut, c, g, s, d,mati[15][15], iki[3][3] = { 0 }, sonuc[25][25] = { 0 }, tops = 0, t, l = 0, assonuc[50][50] = { 0 },a,sato = 0,suto = 0;
    //int mati[5][5] = { {105,102,100,97,96},{103,99,103,101,102},{101,98,104,102,100},{99,101,106,104,99},{104,104,104,100,98} };
    //int iki[3][3] = { {0,-1,0},{-1,5,-1},{0,-1,0} };
    while (1)
    {
        printf("Satir ve sutun sayisini girin\n(max:15 min:3)\n\n");
        while (l < 1)
        {
            //satýr ve sütun sayýsýný alýyorum
            printf("Satir : ");
            scanf_s("%d", &satir1);
            printf("Sutun : ");
            scanf_s("%d", &sutun1);
            if (satir1 < 3 || sutun1 < 3 || satir1 > 15 || sutun1 > 15 || satir1 <= 0)
            {
                printf("satir veya sutun 0 veya daha ufak veya 3'ten ufak veya 15'ten buyuk bir deger olamaz ! \n\n\n");
                printf("Satir ve sutun sayisini girin\n(max 15)\n\n");
            }
            else
            {
                break;
            }
        }
        srand(time(NULL));
        printf("****************************** F Matrixi *************************** \n");
        for (c = 0; c < satir1; c++) {    //ilk matrisin sayýlarýný belirleyen ve çizen for
            for (d = 0; d < sutun1; d++) {
                mati[c][d] = rand() % 255;
                printf("%d\t", mati[c][d]);
            }
            printf("\n");
        }
        printf("********************************************************************* \n");
        printf("V matrixi nasil yazilsin ?\nKose degerleri 0 kullanilsin (A)\nSadece ortadaki deger (Kose degerleri 0 kenar degerleri -1) (B)\nHer deger kullanicidan girilecek (C)\n");

        while (1)
        {
            scanf_s(" %c", &ac);
            if (ac == 'a' || ac == 'A') {
                printf("koselere 0 degerleri atandi\n");
                printf("2. matrixin degerlerini girin\n");      //2.matrixin Köþeler 0

                for (c = 0; c < 3; c++) {
                    for (d = 0; d < 3; d++) {
                        if (c == 0 && d == 0) {
                            iki[c][d] = 0;
                        }
                        else if (c == 0 && d == 2)
                        {
                            iki[c][d] = 0;
                        }
                        else if (c == 2 && d == 0)
                        {
                            iki[c][d] = 0;
                        }
                        else if (c == 2 && d == 2)
                        {
                            iki[c][d] = 0;
                        }
                        else
                        {
                            scanf_s("%d", &iki[c][d]);
                        }
                    }
                }
                break;
            }
            else if (ac == 'c' || ac == 'C')
            {
                printf("hazirda bulunan her deger silindi.\n");
                printf("2. matrixin tum degerlerini girin\n");      //2. matrixin her deðerini gir

                for (c = 0; c < 3; c++) {
                    for (d = 0; d < 3; d++) {
                        printf("v matrixinin %d. satirindaki %d. sutunundaki degeri : ",c+1 ,d+1);
                        scanf_s("%d", &iki[c][d]);
                        printf("\n");
                    }
                }
                break;
            }
            else if (ac == 'b' || ac == 'B') {
                printf("koseler 0 degeri kenarlara ise -1 degeri atandi\n");
                printf("2. matrixin orta degerini girin\n");      //2.matrixin Ortasýný gir

                for (c = 0; c < 3; c++) {
                    for (d = 0; d < 3; d++) {
                        if (c == 0 && d == 0) {
                            iki[c][d] = 0;
                        }
                        else if (c == 0 && d == 2)
                        {
                            iki[c][d] = 0;
                        }
                        else if (c == 0 && d == 1)
                        {
                            iki[c][d] = -1;
                        }
                        else if (c == 1 && d == 0)
                        {
                            iki[c][d] = -1;
                        }
                        else if (c == 1 && d == 2)
                        {
                            iki[c][d] = -1;
                        }
                        else if (c == 2 && d == 1)
                        {
                            iki[c][d] = -1;
                        }
                        else if (c == 2 && d == 0)
                        {
                            iki[c][d] = 0;
                        }
                        else if (c == 2 && d == 2)
                        {
                            iki[c][d] = 0;
                        }
                        else
                        {
                            scanf_s("%d", &iki[c][d]);
                        }
                    }
                }
                break;
            }
            else {
                printf("Yanlis deger girdiniz !\n\n");
                printf("Kose degerleri 0 kullanilsin (A)\nSadece ortadaki deger (Kose degerleri 0 kenar degerleri -1) (B)\nHer deger kullanicidan girilecek (C)\n");
                continue;
            }
        }
        printf("****************************** V Matrixi ****************************** \n");
        for (g = 0; g < 3; g++) {  // 2.matrixi çizen for
            for (int h = 0; h < 3; h++) {
                printf("%d\t", iki[g][h]);
            }
            printf("\n");
        }
        printf("************************************************************************ \n");

        while (1)
        {
            printf("Sonuc matrixi yazdirilirken ;\nKenar degerleri f matrixinden kullanilsin  (A)\nKenar degerleri 0 kullanilsin  (B)\nKenar olmasin (sadece sonuclar yazdirilsin) (C)\n");
            char ac = 'Ü';
            scanf_s(" %c", &ac);
            if (ac == 'c' || ac == 'C')
            {
                printf("****************************** G Matrixi *************************** \n");
                for (sat = 0; sat < satir1 - 2; sat++)
                {
                    for (sut = 0; sut < sutun1 - 2; sut++)
                    {
                        tops = 0;
                        int sonuc[3][3] = { 0 };
                        for (c = 0; c < 3; c++) {           //sonuç arrayini oluþturan for
                            for (d = 0; d < 3; d++) {
                                sonuc[c][d] = mati[c + sat][d + sut] * iki[c][d];
                                tops = tops + sonuc[c][d];
                            }

                        }
                        //printf("%d\t", tops);
                        assonuc[sat][sut] = tops;
                        printf("%d\t", assonuc[sat][sut]);
                    }
                    printf("\n");
                }
                printf("*********************************************************************** \n");
                break;
            }
            else if (ac == 'A' || ac == 'a')
            {
                for (sato = 0; sato < satir1 - 2; sato++)
                {
                    for (suto = 0; suto < sutun1 - 2; suto++)
                    {
                        tops = 0;
                        int sonuc[3][3] = { 0 };
                        for (c = 0; c < 3; c++) {           //assonuç deðeri
                            for (d = 0; d < 3; d++) {
                                sonuc[c][d] = mati[c + sato][d + suto] * iki[c][d];
                                tops = tops + sonuc[c][d];
                            }

                        }
                        assonuc[sato][suto] = tops;
                    }
                }
                printf("****************************** G Matrixi *************************** \n");
                for (sat = 0; sat < satir1; sat++)
                {
                    if (sat == 0 || sat == satir1 - 1) {
                        for (sut = 0; sut < sutun1; sut++)
                        {
                            printf("%d\t", mati[sat][sut]);
                        }
                        printf("\n");
                    }
                    else
                    {
                        for (sut = 0; sut < sutun1; sut++)
                        {
                            if (sut == 0 || sut == sutun1 - 1) {
                                printf("%d\t", mati[sat][sut]);
                            }
                            else
                            {
                                printf("%d\t", assonuc[sat - 1][sut - 1]);
                            }
                        }
                        printf("\n");
                    }
                }
                printf("******************************************************************** \n");
                break;
            }
            else if (ac == 'B' || ac == 'b')
            {
                for (sato = 0; sato < satir1 - 2; sato++)
                {
                    for (suto = 0; suto < sutun1 - 2; suto++)
                    {
                        tops = 0;
                        int sonuc[3][3] = { 0 };
                        for (c = 0; c < 3; c++) {           //assonuç deðeri
                            for (d = 0; d < 3; d++) {
                                sonuc[c][d] = mati[c + sato][d + suto] * iki[c][d];
                                tops = tops + sonuc[c][d];
                            }

                        }
                        assonuc[sato][suto] = tops;
                    }
                }
                printf("****************************** G Matrixi *************************** \n");
                for (sat = 0; sat < satir1; sat++)
                {
                    if (sat == 0 || sat == satir1 - 1) {
                        for (sut = 0; sut < sutun1; sut++)
                        {
                            printf("0\t");
                        }
                        printf("\n");
                    }
                    else
                    {
                        for (sut = 0; sut < sutun1; sut++)
                        {
                            if (sut == 0 || sut == sutun1 - 1) {
                                printf("0\t");
                            }
                            else
                            {
                                printf("%d\t", assonuc[sat - 1][sut - 1]);
                            }
                        }
                        printf("\n");
                    }
                }
                printf("******************************************************************** \n");
                break;
            }
            else
            {
                printf("Yanlis deger girdiniz !\n\n");
                printf("Kenar degerleri f matrixinden mi kullanilsin ? (E/H)\n");
                continue;
            }
        }
        while (1)
        {
            printf("devam etmek istiyormusunuz ? (E/H)\n");
            scanf_s(" %c", &cýk);
            if (cýk == 'e' || cýk == 'E')
            {
                while (1)
                {
                    printf("ekran temizlensin mi ? (E/H)\n");
                    scanf_s(" %c", &tem);
                    if (tem == 'e' || tem == 'E')
                    {
                        ekranTemizle();
                        break;
                    }
                    else if (tem == 'h' || tem == 'H')
                    {
                        break;
                    }
                    else
                    {
                        printf("yanlis deger girdiniz.\n");
                        continue;
                    }
                }
                break;
            }
            else if (cýk == 'h' || cýk == 'H')
            {
                exit(1);
            }
            else
            {
                printf("Yanlis deger girdiniz !\n");
                continue;
            }
        }
    }
    return 0;
}