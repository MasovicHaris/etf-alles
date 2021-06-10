#include <stdio.h>
#include <stdlib.h> /* Zbog funkcije exit() */

struct Student {
	char prezime[20];
	char ime[15];
	int  broj_bodova;
};

int main()
{
	struct Student studenti[300], tmp;
	FILE *ulaz, *izlaz;
	int i, j, k;

	/* Otvaranje datoteka */
	if ((ulaz = fopen("ispit.txt","r")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}

	if ((izlaz = fopen("ispit_sortiran.txt","w")) == NULL) {
		fclose(ulaz);
		printf("Greska pri otvaranju datoteke ispit_sortiran.txt");
		exit(1);
	}

	/* Ucitavanje datoteke u niz studenti */
	i=0;
	while (fscanf(ulaz,"%20s%15s%2d\n", studenti[i].prezime, studenti[i].ime, &studenti[i].broj_bodova) == 3 && i<300)
		i++;

	/* Sortiranje niza po broju bodova
	   Varijabla i je sada velicina niza */
	for (j=0; j<i-1; j++)
		for (k=j+1; k<i; k++)
			if (studenti[k].broj_bodova > studenti[j].broj_bodova) {
				tmp = studenti[j];
				studenti[j] = studenti[k];
				studenti[k] = tmp;
			}

	// Upis niza u datoteku
	for (j=0; j<i; j++)
		fprintf(izlaz,"%-20s%-15s%2d\n", studenti[j].prezime, studenti[j].ime, studenti[j].broj_bodova);

	printf ("Izlazna datoteka ispit_sortiran.txt je kreirana");
	fclose(ulaz);
	fclose(izlaz);
	return 0;
}
