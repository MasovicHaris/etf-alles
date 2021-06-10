#include <stdio.h>
#include <stdlib.h>

struct Osoba {
		char ime[15];
		char prezime[20];
		int telefon;
};

struct Osoba unos_osobe(){
	struct Osoba o;
	printf("Unesite ime: "); scanf("%s", o.ime);
	printf("Unesite prezime: "); scanf("%s", o.prezime);
	printf("Unesite broj telefona: "); scanf("%d", &o.telefon);
	
	return o;
}


void upisi(){
	struct Osoba imenik;
	imenik = unos_osobe();
	FILE *ulaz;
	char c;
	/* Otvaranje datoteka */
	if ((ulaz = fopen("imenik.txt","a+")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}
	c = fgetc(ulaz);
	while(c!=EOF) c = fgetc(ulaz);
	// Upis niza u datoteku
	fprintf(ulaz,"%-15s%-20s%6d\n", imenik.ime, imenik.prezime, imenik.telefon);
	fclose(ulaz);
}

void ispis(){
	printf("\n");
	struct Osoba studenti[300];
	FILE *ulaz;
	int i, j;

	/* Otvaranje datoteka */
	if ((ulaz = fopen("imenik.txt","r")) == NULL) {
		printf("Greska pri otvaranju datoteke imenik.txt");
		exit(1);
	}
	i=0;
	while (fscanf(ulaz,"%15s%20s%6d\n", studenti[i].ime, studenti[i].prezime, &studenti[i].telefon) == 3 && i<300)
		i++;
		
	for(j=0;j<i;j++){
	//	if(studenti[j].broj_bodova1>=10 && studenti[j].broj_bodova2>=10)
		printf("%d. %s %s, Tel: %d\n", j+1, studenti[j].ime, studenti[j].prezime, studenti[j].telefon);
	}
	
	fclose(ulaz);
}

int main() {
	int broj;
	do{
		printf("Pritisnite 1 za unos, 2 za ispis, 0 za izlaz: ");
		scanf("%d", &broj);
		if(broj==1){
			upisi();
		}
		else if(broj==2){
			ispis();
		}
		
		
		
	}while(broj!=0);
	
	
	return 0;
}
