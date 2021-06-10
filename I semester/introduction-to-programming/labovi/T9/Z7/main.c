#include <stdio.h>

char* velika(char* s)
{
	int brojac=0;
	while(*s!='\0') {
		if (*s >= 'A' && *s <= 'Z') *s += 'a' - 'A';
		s++;
		brojac++;
	}

	s=s-brojac;

	return s;
}

int strcmp(const char *s1, const char *s2, int velikamala)
{

	char *pok1;
	char *pok2;

	if(velikamala==0) {
		velika(s1);
		velika(s2);
	}

	pok1=s1;
	pok2=s2;


	while(*pok1!='\0' && *pok2!='\0') {

		if(*pok1>*pok2) return 1;
		if(*pok1<*pok2) return -1;

		pok1++;
		pok2++;
	}

	if(*pok1!='\0') return 1;
	if(*pok2!='\0') return -1;

	return 0;
}






int main()
{
	return 0;
}
