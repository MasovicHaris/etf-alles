#include <stdio.h>
#define duzina 10
/* Napisati program koji najprije traži da se unesu dva niza pozitivnih cijelih brojeva A i B.
Unos niza se prekida kada korisnik unese broj -1, a maksimalan broj elemenata u nizovima je 10. 
Nakon unosa, nizove A i B je potrebno spojiti u novi niz C. Konačno, tako formirani niz C treba ispisati na ekranu. 

Ovaj zadatak je vrlo jednostavno riješiti bez korištenja niza C, no za vježbu pokušajte ga uraditi tačno po koracima koji su dati iznad.
Primjer ulaza i izlaza:
	Unesite elemente niza A: 5 3 8 -1
	Unesite elemente niza B: 2 3 1 5 1 -1
	Niz C glasi: 5,3,8,2,3,1,5,1
Napomena: U gornjem primjeru demonstrirana je pojava da se više uzastopnih naredbi scanf može izvršiti tako što se 
vrijednosti unose razdvojene razmakom. Npr. ako kod glasi:
	scanf("%d",&a);
	scanf("%d",&b);
	scanf("%d",&c);
korisnik može kucati
	1 2 3 (Enter)
i ova tri broja će biti upisana u varijable a, b i c respektivno. */

int main() {
	int niz1[duzina], niz2[duzina];
	int i, brojac1=0, brojac2=0, brojac3=0;
	int niz3[20];
	printf("Unesite elemente niza A: ");
	for(i=0;i<duzina;i++)
	{
		scanf("%d", &niz1[i]);
		if(niz1[i]==-1) { 
			brojac1=i; break; } else brojac1=duzina;
	}
	
	printf("Unesite elemente niza B: ");
	for(i=0;i<duzina;i++)
	{
		scanf("%d", &niz2[i]);
		if(niz2[i]==-1) { 
			brojac2=i; break; } else brojac2=duzina;
	}
	
	//printf("%d %d ", brojac1, brojac2);
	

	
	
	for(i=0;i<brojac1;i++)
	{
		niz3[brojac3]=niz1[i]; 
		brojac3++; 
	}
	
	for(i=0;i<brojac2;i++)
	{
		niz3[brojac3]=niz2[i];
		brojac3++;
	}
	
	//printf("%d\n", brojac3);
	printf("Niz C glasi: ");
	for(i=0;i<brojac3;i++)
	{
		if(i==brojac3-1) printf("%d", niz3[i]);	
		else printf("%d,", niz3[i]);
	}
	
	
	return 0;
}
