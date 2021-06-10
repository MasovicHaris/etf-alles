#include <stdio.h>

int prva_rijec(char *s)
{
	int broj_rijeci=1, brojac=0;
	while(*s!='\0') {
		int dal_je_razmak=1;

		if(*s==' ' && *(s+1)!=' ' && *(s+1)!='\0') dal_je_razmak=1;
		else dal_je_razmak=0;

		if (dal_je_razmak==1) {
			broj_rijeci++;
		}

		s++;
		brojac++;

	}

	s=s-brojac;
	brojac=0;
	while(*s!='\0') {

		brojac++;
		if(*s==' ') {
			*s='\0';
			s--;
		}
		s++;
	}

	s=s-brojac;

	return broj_rijeci;
}

void unesi(char niz[], int velicina)
{
	char znak = getchar();
	if (znak == '\n') znak=getchar();
	int i = 0;
	while (i < velicina-1 && znak != '\n') {
		niz[i] = znak;
		i++;
		znak = getchar();
	}
	niz[i]='\0';
}

int main()
{
	char recenica[200];
	printf("Unesite recenicu (do 200 karaktera): ");
	unesi(recenica, 200);
	printf("Broj rijeci u recenici je: %d\n", prva_rijec(recenica));
	printf("%s", recenica);

	return 0;
}
