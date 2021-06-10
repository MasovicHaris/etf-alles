#include <stdio.h>
/* Napraviti funkciju drugi koja u datom nizu cijelih brojeva pronalazi
drugi po veličini i vraća indeks tog člana u nizu. U slučaju da niz ne sadrži drugi po veličini element funkcija treba vratiti broj -1.

Primjer ulaza i izlaza programa:


	Unesite niz brojeva: 10 5 4 9 8 3 -1
	Indeks drugog po velicini je: 3

Najveći element u unesenom nizu je 10, a drugi po veličini je 9.
Broj 9 se nalazi na 4. mjestu odnosno označen je indeksom 3 (prvi član ima indeks 0, drugi indeks 1 itd.) */


int drugi(int *niz, int vel)
{
	int max, max2;
	int i, brojac=0;
	max=*niz;

	for(i=0; i<vel; i++) {
		if(*(niz+i)>max) {
			max=*(niz+i);
		}
	}

	max2=0;

	for(i=0; i<vel; i++) {
		if(*(niz+i)==max) continue;
		else if(*(niz+i)>=max2) {
			max2=*(niz+i);
			brojac=i;
		}
	}

	if(max2!=0) return brojac;
	else return -1;

}



int main()
{
	int niz[100];
	int i=0;

	printf("Unesite niz brojeva: ");
	for (i=0;; i++) {
		scanf ("%d",&niz[i]);
		if (niz[i]==-1) break;
	}

	int vel;
	vel=i;
	printf("Indeks drugog po velicini je: %d", drugi(niz, vel));

	return 0;
}
