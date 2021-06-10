#include <stdio.h>

char* velika(char* s)
{
	int brojac=0;
	while(*s!='\0') {
		if (*s >= 'a' && *s <= 'z') *s += 'A' - 'a';
		s++;
		brojac++;
	}

	s=s-brojac;

	return s;
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
	char a[100];
	printf("Unesite neki tekst: ");
	unesi(a,100);
	printf("%s", velika(a));
	return 0;
}
