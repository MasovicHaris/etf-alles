#include <stdio.h>

/* 
 Napišite program koji sa tastature učitava neki pozitivan cijeli broj, 
 a zatim ispisuje najveću i najmanju cifru tog broja.
 Petljom do-while spriječite da se unose negativni brojevi.


Primjer ulaza i izlaza:
    Unesite broj: 49527
    Najveca cifra je 9 a najmanja je 2.
 */ 
 
int main() {
	int n;
	LOOP:
	do{
		int min, max, broj;
		printf("Unesite broj: ");
		scanf("%d", &n);
		if(n<0) goto LOOP;
		//	printf("Poz");
		broj=n%10;
		n/=10;
		max=broj; min=broj;
		
		while(n>0){
			broj=n%10;
			n/=10;
			if(broj>max) max=broj;
			else if(broj<min) min=broj;
		}
		
			printf("Najveca cifra je %d a najmanja je %d.", max, min);
	} while(n<0);
	return 0;
}
