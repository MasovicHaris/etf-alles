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


char *izbaci_rijec(char* s, int n)
{
	char *reset = s;
	int neslovo=1, broj_rijeci=0;

	if(n<1) return s;

	while (*s != '\0') {

		if ( !(*s >= 'A' && *s <= 'Z' || *s >= 'a' && *s <= 'z') ) {
			neslovo = 1;
		} else if (neslovo == 1) {



			neslovo=0;
			broj_rijeci++;


			if (broj_rijeci==n) {

				char *kraj_rijeci = s;
				while (*kraj_rijeci != '\0' && (*kraj_rijeci >= 'A' && *kraj_rijeci <= 'Z' || *kraj_rijeci >= 'a' && *kraj_rijeci <= 'z')) kraj_rijeci++;

				char *poc = s;
				while (*poc != '\0') {

					*poc++ = *kraj_rijeci++;
					if(*kraj_rijeci=='\0') {
						*poc='\0';
						break;
					}


				}

			}
		}
		s++;
	}

	s = reset;
	return s;

}

int main()
{
	char a[80];
	int n;
	printf ("\nUnesite jednu rijec do 80 znakova (ENTER za kraj): ");
	unesi(a, 80);
	printf ("Koju rijec treba izbaciti: ");
	scanf ("%d", &n);
	printf("%s", izbaci_rijec(a, n));
	return 0;
}
