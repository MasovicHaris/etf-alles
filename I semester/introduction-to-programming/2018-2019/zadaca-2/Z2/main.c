// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int niz[100];
	int brojac=0, i, j, cifra, n, bulean, t, broj;
	printf("Unesite brojeve: ");
	
	for(i=0; i<100; i++)
	{
		scanf("%d", &niz[i]);
		brojac++;
		if(niz[i]==-1)
		{
			brojac--;
			break;
		}
	}
		n=0;
		i=0;
		while(n<brojac)
		{
			broj=niz[i];
			cifra=abs(broj)%10;
			bulean=1;
			
			do
			{
				if(cifra!=abs(broj)%10)
				{
					bulean=0;
					break;
				}
				broj=abs(broj)/10;
			
			}while(broj>0);
			
			if(bulean==0)
			{
				for(j=i;j<brojac-1;j++)
				{
				
				t=niz[j];
				niz[j]=niz[j+1];
				niz[j+1]=t;
				}
			
			}
		
		
		
		
			else
			{
			i++;
			}
				
			n++;	
			
		}
						
			printf("\nNakon preslaganja niz glasi:\n");	
					
	for(i=0; i<brojac; i++)
	{
		printf("%d", niz[i]);
		if(i>=brojac-1)
		{
			printf(".");
		}
		else 
		printf(",");
	}
	
	
	
	
	
	
}
