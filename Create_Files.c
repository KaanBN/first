#include <stdio.h>
#include <time.h>
int main()
{
    int ay = 0;
    int i = 0;
    long long int j = 13155555535;  //başlangıç sayısı
    long long int x = 13199999979;
    FILE *files[2000];
    clock_t begin = clock();
    clock_t begin2 = clock();
    for (int i = 0; i < 10; i++)
    {
        int a = 0;
        printf("%d. dosya yazmaya baslandi\n",i+47);
        clock_t begin1 = clock();
        char filename[20];
        sprintf(filename, "D:\\dosyalar\\%d'th 44,444,444.txt", i+47);
        files[i] = fopen(filename,"w");
        for (j ; j < x; ++j) {
            fprintf(files[i],"%lli\n",j);       //şu anda yazılan sayı
        }
        x += 44444444;          //dosya başına kaç sayı arttırılacak    (değiştirme !)
        clock_t end1 = clock();
        double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
        clock_t end2 = clock();
        double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
        printf("%d. dosyayi yazdirmak icin gecen zaman : %lf\n\n",i+1,time_spent1);
        fclose(files[i]);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("butun dosyalari yazirmak icin gecen zaman : %lf\n",time_spent);
}
