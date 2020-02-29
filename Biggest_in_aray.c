#include <stdio.h>
int Buyuk(int dizi[],int n) {
	if (n > 0)
	{
		if (Buyuk(dizi, n - 1) < dizi[n])
		{
			return dizi[n];
		}
	}
	else
	{
		return dizi[n];
	}
}

int main() {
	int dizi[5] = { 1,10,28,4,5 };
	printf("%d", Buyuk(dizi,4));
}
