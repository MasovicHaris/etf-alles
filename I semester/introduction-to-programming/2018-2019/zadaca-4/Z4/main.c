// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>

int matrica_sadrzana(int A[][100], int nA, int mA, int B[][100], int nB, int mB)
{
	
	int i, j, k=0, l=0, poci, pocr, brojac=0, a, b;
	
	for(i=0; i<nB-1; i++)									//protiv onih testova sa nulom
	{
		for(j=0; j<mB; j++)
		{
			if(B[i][j]==0 && B[i+1][j]==0)
			return 0;
			
		}
	}
	
  	if(nA<nB || mA<mB)  //pretraga po matrici A, dok ne nađe odgovarajući element
	{
	return 0;
	}
	
	else
	{
			for(i=0; i<nA; i++)
			{
				for(j=0; j<mA; j++)
				{
					
					if(B[0][0]==A[i][j])    //ako nađe prvi element matrice B u matrici A, gleda sadrzi li je
					{
						k=0;
						l=0;
						poci=i;								// uzme pozicije prvog elementa matrice B u matrici A i krene sa pretragom
						pocr=j;
						for(a=poci; a<i+nB; a++)
						{
							for(b=pocr; b<j+mB; b++)
							{
								if(A[a][b]==B[k][l])			//ako je poklapanje, brojac se povecava, pretraga se vrsi u razmjerama matrice B
								{
									brojac++;
								}
								l++;
							}
							k++;
							l=0;
						}
							if(brojac==(nB*mB))			//ako je broj poklapanja jednak broju elemenata matrice B, vrati 1
							{
								return 1;
							}
					}
		
			
				}
				
				brojac=0;			// ako nije trazi dalje negdje da li je na nekoj drugoj poziciji u matrici A, prvi elemenat iz B
			}
			
		return 0;			// ako se finalno ne poklapa, vrati 0
		
	}

	
}



int main() {
	
printf("Huso kralj");
return 0;
}
