#include <stdio.h>

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

char *zamijeni1(char* s)
{
	char *reset = s;
	int duzina = 4;
	while (*s != '\0') {
		if (*s == '1') {
			char* kraj = s;
			while (*kraj != '\0') kraj++;
			while (kraj > s) {
				*(kraj+duzina) = *kraj;
				kraj--;
			}
			*s++ = 'j';
			*s++ = 'e';
			*s++ = 'd';
			*s++ = 'a';
			*s = 'n';
		}
		s++;
	}
	return reset;
}
int main()
{
	char tekst[100];
	printf("Unesite tekst: ");
	unesi(tekst, 100);
	zamijeni1(tekst);
	printf("Nakon zamjene: %s", tekst);
	return 0;
}