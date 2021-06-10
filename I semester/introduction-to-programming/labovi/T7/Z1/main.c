#include <stdio.h>

void crtaj(int duzina)
{
	int i;
	for(i=1;i<=duzina;i++){
		printf("*");
	}
	
}

int main() {
	int i, niz[5];
	
	printf("\n Unesite vrijednosti za grafikon\n");
	for(i=0;i<5;i++)
	{
		printf("%d vrijednost: ", i+1);
		scanf("%d", &niz[i]);
	}
	printf("\n     ^\n     |");
	for(i=0;i<5;i++){
		printf("\n     |");
		crtaj(niz[i]);
		printf(" %d", niz[i]);
		printf("\n     |");
		
		
	}
	printf("----------------------------->\n");
	return 0;
}
