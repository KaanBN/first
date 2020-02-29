#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
float average(int *a,float lenght,float *l_all) {
	if (lenght > 0)
	{
		return (float)*(a + (int)lenght) / (float)*l_all + (float)average(a, lenght - 1, l_all);
	}
	else
	{
		return (float)*(a + (int)lenght) / (float)*l_all;
	}
}

int main() {
	float l_all = 0;
	float array_lgt = 0;
	while (1)
	{
		printf("How many number will be stored = ");
		scanf("%f", &array_lgt);
		if (array_lgt <= 0 || array_lgt > 200)
		{
			printf("Please enter valid number (0 < number < 200)\npress any button to continue\n");
			getch();
			system("cls");
			continue;
		}
		else
		{
			break;
		}
	}
	
	l_all = array_lgt;
	int* a = (int*)malloc(array_lgt * sizeof(int));
	for (int s = 0; s < (int)array_lgt; s++)
	{
		printf("a[%d] = ",s);
		scanf("%d", &a[s]);
	}
	printf("Average of the entered numbers = %f",average(a, array_lgt -1,&l_all));
}
