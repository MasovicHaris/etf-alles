#include <stdio.h>
#include <string.h>

void unesi(char niz[], int velicina)
{
	int i = 0;
	char znak = getchar();
	if (znak == '\n') znak=getchar();
	while (i < velicina-1 && znak != '\n') {
		niz[i] = znak;
		i++;
		znak = getchar();
	}
	niz[i]='\0';
}

char *zamijeni_broj(char* s, int n)
{
	int i=0;
	char *a[] = {"nula","jedan","dva","tri","cetiri","pet","sest","sedam","osam","devet"};
	int duzine[]={4,5,3,3,6,3,4,5,4,5};
	char *reset = s;
	while (*s != '\0') {
		if (*s - 48 == n) {
	
			char* kraj = s;
			while (*kraj != '\0') kraj++;
			while (kraj > s) {
				*(kraj+duzine[n]-1) = *kraj;
				kraj--;
			}
			for (i = 0; i < duzine[n]; ++i) *s++ = a[n][i];
			s--;
			
		}
		s++;
	}
	s=reset;
	return s;
}
int main()
{
	char tekst[100];
	int n;
	printf("Unesite tekst: ");
	unesi(tekst, 100);
	printf("Unesite n: ");
	scanf("%d", &n);
	zamijeni_broj(tekst, n);
	printf("Nakon zamjene: %s", tekst);
	return 0;
}