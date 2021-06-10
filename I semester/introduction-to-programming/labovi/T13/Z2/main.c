#include <stdio.h>
#include <stdlib.h> /* Zbog funkcije exit() */

struct Student {
	char prezime[20];
	char ime[15];
	int  broj_bodova1;
	int  broj_bodova2;
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

	if ((izlaz = fopen("usmeni.txt","w")) == NULL) {
		fclose(ulaz);
		printf("Greska pri otvaranju datoteke ispit_sortiran.txt");
		exit(1);
	}

	/* Ucitavanje datoteke u niz studenti */
	i=0;
	while (fscanf(ulaz,"%20s%15s%2d %2d\n", studenti[i].prezime, studenti[i].ime, &studenti[i].broj_bodova1, &studenti[i].broj_bodova2) == 4 && i<300)
		i++;
		
		
	for (j=0; j<i-1; j++)
		for (k=j+1; k<i; k++)
			if (studenti[k].broj_bodova1 + studenti[k].broj_bodova2 > studenti[j].broj_bodova1 + studenti[j].broj_bodova2) {
				tmp = studenti[j];
				studenti[j] = studenti[k];
				studenti[k] = tmp;
			}	
		
		
	// Upis niza u datoteku
	for (j=0; j<i; j++)
	{
		if(studenti[j].broj_bodova1>=10 && studenti[j].broj_bodova2>=10)
		fprintf(izlaz,"%-15s%-10s%2d\n", studenti[j].prezime, studenti[j].ime, studenti[j].broj_bodova1 + studenti[j].broj_bodova2);
	}
	
	fclose(ulaz);
	fclose(izlaz);
	printf ("Izlazna datoteka usmeni.txt je kreirana\n");

	return 0;
}

