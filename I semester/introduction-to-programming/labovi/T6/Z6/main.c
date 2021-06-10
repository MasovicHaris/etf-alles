#include <stdio.h>

int main() {
	int A, B, i, j;
	double niz[100][100];
	double suma=0;
	printf("Unesite dimenzije matrice: ");
	scanf("%d %d", &A, &B);
	printf("Unesite elemente matrice: ");
	for(i=0;i<A;i++)
	{
		for(j=0;j<B;j++)
		{
			scanf("%lf", &niz[i][j]);
		}
	}
	
	for(i=0;i<A;i++)
	{
		for(j=0;j<B;j++)
		{
			if(i==0 || i==A-1) suma+=niz[i][j];
			else if((j==0 || j==B-1) && (i>0 && i<A)) suma+=niz[i][j];
		}
	}
	
	printf("Suma elemenata na rubu je %.2f", suma);
	
	
	return 0;
}
