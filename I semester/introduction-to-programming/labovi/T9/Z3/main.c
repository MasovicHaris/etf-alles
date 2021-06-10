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


int prebroji(char* s, char znak)
{
	int broj = 0;
	while (*s != '\0') {
		if (*s == znak)
			broj++;
		s++;
	}
	return broj;
}


int duzina(char* s)
{
	int brojac=0;
	while(*s!='\0') {

		brojac++;
		s++;
	}

	return brojac;

}


int samoglasnici(char *s)
{

	int brojac=0;
	while(*s!='\0') {

		if(*s=='a' || *s=='A' || *s=='e' || *s=='E' || *s=='i' || *s=='I' || *s=='o' || *s=='O' || *s=='u' || *s=='U') brojac++;
		s++;
	}

	return brojac;


}





int main()
{
	char a[80],c;
	printf ("Unesite jednu rijec do 80 znakova (ENTER za kraj): \n");
	unesi(a, 80);
	printf ("\nKoji znak treba prebrojati: ");
	scanf ("%c", &c);

	printf("\nUnesena rijec sadrzi %d znakova.\n", duzina(a));

	printf ("Broj znakova %c je: %d\n",c,prebroji(a,c));

	printf("Broj samoglasnika je: %d", samoglasnici(a));

	return 0;
}