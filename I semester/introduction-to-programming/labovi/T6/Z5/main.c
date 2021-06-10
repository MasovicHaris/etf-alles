#include <stdio.h>
#define duzina 10
/*
Napisati program koji učitava matricu cijelih brojeva dimenzija 10x10 te pronalazi najmanji element na glavnoj dijagonali. */

int main() {
	int i, j;
	int mat[duzina][duzina];
	int min;
	for(i=0;i<duzina;i++)
	{
		for(j=0;j<duzina;j++)
		{
			scanf("%d", &mat[i][j]);
		}
	}
	
	min	= mat[0][0]; //printf("%d", min);
	for(i=0;i<duzina;i++)
	{
		for(j=0;j<duzina;j++)
		{
			if(i==j && mat[i][j]<min) min=mat[i][j];
		}
	}
	
	printf("%d", min);
	
	return 0;
}
