#include <stdio.h>
#define BROJ_EL 5
/* Napisati program koju učitava 5 elemenata dva niza realnih brojeva A i B,
a zatim izračunava elemente trećeg niza C zadatog kao:

C{ciℝ|ci=2ai+bi,aiA,biB}

Drugim riječima, svaki element ci skupa C jednak je sumi odgovarajućih 
elemenata ai i bi iz skupova A i B pri čemu je ai pomnožen sa dva.

Na kraju je potrebno ispisati sve elemente nizova A, B i C.
Primjer ulaza i izlaza programa:
    Unesite clanove niza A: 1 2 3 4 5
    Unesite clanove niza B: 1 2 3 4 5
    Niz A glasi: 1.00, 2.00, 3.00, 4.00, 5.00
    Niz B glasi: 1.00, 2.00, 3.00, 4.00, 5.00
    Niz C glasi: 3.00, 6.00, 9.00, 12.00, 15.00 */
int main() {
    float niz1[BROJ_EL], niz2[BROJ_EL];
    float niz3[BROJ_EL];
    int i;
    /* unos i RACUNANJE */
    printf("Unesite clanove niza A: ");
	for(i=0;i<BROJ_EL;i++){
		scanf("%f", &niz1[i]);
	}
	printf("Unesite clanove niza B: ");
	for(i=0;i<BROJ_EL;i++){
		scanf("%f", &niz2[i]);
	}
	for(i=0;i<BROJ_EL;i++){
		niz3[i]=2*niz1[i]+niz2[i];
	}
	
	printf("Niz A glasi:");
	for(i=0;i<BROJ_EL;i++){
		if(i==BROJ_EL-1) printf(" %.2f", niz1[i]);
		else printf(" %.2f,", niz1[i]);
	}
	printf("\nNiz B glasi:");
	for(i=0;i<BROJ_EL;i++){
		if(i==BROJ_EL-1) printf(" %.2f", niz2[i]);
		else printf(" %.2f,", niz2[i]);
	}
	printf("\nNiz C glasi:");
	for(i=0;i<BROJ_EL;i++){
		if(i==BROJ_EL-1) printf(" %.2f", niz3[i]);
		else printf(" %.2f,", niz3[i]);
	}
	
	
	
	
	
	
	
	return 0;
}
