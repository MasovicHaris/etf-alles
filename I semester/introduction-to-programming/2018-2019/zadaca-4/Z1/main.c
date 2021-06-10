// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>

int oduzmi_cifre(int niz[], int br)
{
	int i, tk, r;
	
	for(i=0; i<br; i++)
	{
		tk=1;
		r=0;
		if(niz[i]/10==0) //ako je clan niza jednocifren treba se 0 ispisat
		{
			niz[i]=0;
		}
		else
		{
		do
		{
			if(niz[i]<0) //ako je clan niza negativan, treba se apsulutna uzet
			{
				niz[i]=abs(niz[i]);
			}
			int c=(niz[i]%10); //zadnja cifra
			niz[i]/=10;
			int b=(niz[i]%10); //predzadnja cifra
			r=r+tk*(abs(c-b)); //rezultat sa tezinskim koeficijentom
			tk=tk*10; // tezinski se povecava kako bi dobijali dobar broj
			
		}while(niz[i]>9); //kad clan niza bude manji od 10 to znaci da nema cifre sa lijeva s kojom se moze oduzet, niz se u svakoj iteraciji dijeli jednonm
		
		niz[i]=r; //clan niza postaje rezultat :D
		}
		
	}
	
	return 0;
	
	
}


int main() {
	
	printf("Huso kralj");
}