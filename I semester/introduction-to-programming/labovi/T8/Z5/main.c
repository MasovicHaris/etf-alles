#include <stdio.h>
#include <math.h>

void zaokruzi(double *niz, int vel) {

	
	double *p;
	p=niz;
	
	while (p < niz+vel) {
		
	*p = (*p)*10;
	if(*p<0) 
	{
		*p = round(*p-0.00001);
	}
	else 
	{
		*p = round(*p+0.00001);
	}
	
	*p/= 10;
	p++;
	}
}


int main() {
	double niz[100];
	int i, vel;
	printf("Koliko realnih brojeva cete unijeti? ");
	do{
		scanf("%d", &vel);
	} while (vel<1 || vel>100);
	printf("Unesite clanove niza: ");
		
	for (i=0; i<vel; i++) scanf("%lf", niz+i);

	zaokruzi(niz,vel);

	printf("Nakon zaokruzivanja niz glasi:\n");

	for (i=0; i<vel; i++) printf("%g ", *(niz+i));
		
	return 0;
}

