#include <stdio.h>
/*
Napišite funkciju sortiraj koja slaže po veličini niz realnih brojeva, 
pri čemu dimenzija niza nije unaprijed poznata nego predstavlja jedan od parametara funkcije. 
Napravite kratak glavni program koji testira ovu funkciju. Primjer algoritma za sortiranje nalazi se na početku Tutorijala 6.


Pri rješavanju zadatka obavezno koristiti pokazivačku aritmetiku.*/

void sortiraj(double *niz, int vel){
	
	double *pok, *pomocni;
	pok=niz;
	pomocni=niz+1;
	while(pok<niz+vel){
		while(pomocni<niz+vel)
		{
			if(*pok>*pomocni){
				double temp;
				temp=*pok;
				*pok=*pomocni;
				*pomocni=temp;
			}
			pomocni++;
		}
		pok++;
		pomocni=pok;
	}
	
}



int main() {
	int i; int vel;
	double niz[100];
	printf("Unesi niz za sortat: ");
	for(i=0;;i++)
	{
		scanf("%lf", &niz[i]);
		if(niz[i]==-1) break;
	}
	vel=i;
	sortiraj(niz, vel);
	
	for(i=0;i<vel;i++)
	{
		printf("%g ", niz[i]);
	} 
	
	return 0;
}
