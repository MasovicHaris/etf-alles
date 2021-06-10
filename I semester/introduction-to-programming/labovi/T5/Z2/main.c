#include <stdio.h>
#define BROJ_EL 10
int main() {
	int niz[BROJ_EL], suma1, suma2, i;
	int min, max, brojac=0;
	float presjek, presjek2;
	
	for(i=0;i<BROJ_EL;i++){
		printf("Unesite %d. cijeli broj: ", i+1);
		scanf("%d", &niz[i]);
	}
	
	
	suma1=0; 
	suma2=0;
	
	min=niz[0];
	max=niz[0];
	
	for(i=0;i<BROJ_EL;i++) 
	{
		if(niz[i]>max) max=niz[i];
		if(niz[i]<min) min=niz[i];
		
		
		suma1=suma1 + niz[i];
		if(niz[i]%2==0) { suma2=suma2 + niz[i]; brojac++; }
	
	
	}
		if(brojac==0) brojac=1;
		presjek = (float)suma1/BROJ_EL;
		presjek2 = (float)suma2/(brojac);
		
		printf("Srednja vrijednost unesenih brojeva je %.2f.\n", presjek);
		printf("Srednja vrijednost parnih brojeva je %.2f.\n", presjek2);
		printf("Najveci element je %d a najmanji %d.", max, min);
	
	return 0;
}