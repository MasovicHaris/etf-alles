#include <stdio.h>

int strcmp(const char *s1, const char *s2)
{

	char *pok1;
	char *pok2;

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
