#include <stdio.h>
#define duzina 10
/*
Napravite program učivata matricu cijelih brojeva dimenzija 10x10, 
a zatim pronalazi red sa najvećim i red sa najmanjim elementom. 
Ako se oba elementa nalaze u istom redu, program treba ispisati poruku "Najveci i najmanji element se nalaze u istom redu" 
i završiti s radom. U suprotnom, potrebno je zamijeniti mjesta ta dva reda u matrici i ispisati tako modifikovanu matricu na ekranu. 
*/

int main() {
	int niz[duzina][duzina];
	int i, j;
	int brojac1=0, brojac2=0;
	printf("Unesite elemente matrice: ");
	for(i=0;i<duzina;i++)
	{
		for(j=0;j<duzina;j++)
		{
			scanf("%d", &niz[i][j]);
		}
	}
	
	int max=niz[0][0];
	int min=niz[0][0];
	for(i=0;i<duzina;i++)
	{
		for(j=0;j<duzina;j++)
		{
			if(niz[i][j]>max) { max=niz[i][j]; brojac1=i; }
			if(niz[i][j]<min) { min=niz[i][j]; brojac2=i; }
			
		}
	}
	
	// printf("%d %d", brojac1, brojac2);
	
	
		if(brojac1==brojac2) printf("Najmanji i najveci element se nalaze u istom redu."); 
		else{
		
		for(i=0;i<duzina;i++)
		{
			
				
				double x;
				x=niz[brojac1][i];
				niz[brojac1][i] = niz[brojac2][i]; 
				niz[brojac2][i] = x;
					
				
			
		}
			printf("Nakon zamjene matrica glasi: \n");
			for(i=0;i<duzina;i++)
			{
				for(j=0;j<duzina;j++)
				{
					printf("%d ", niz[i][j]);
			
				}
				printf("\n");
			}
			
			
		}
		
	
	
	
	
	
	
	
	
	return 0;
}
