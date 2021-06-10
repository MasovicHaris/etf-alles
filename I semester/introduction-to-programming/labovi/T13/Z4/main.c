#include <stdio.h>
#include <stdlib.h> /* Zbog funkcije exit() */

struct Student {
	char prezime[20];
	char ime[15];
	int  broj_bodova1;
	int  broj_bodova2;
};

void sortiraj(){
	struct Student studenti[300], tmp;
	FILE *ulaz;
	int i, j, k;

	/* Otvaranje datoteka */
	if ((ulaz = fopen("ispit.txt","r")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}

	/* Ucitavanje datoteke u niz studenti */
	i=0;
	while (fscanf(ulaz,"%20s%15s%2d %2d\n", studenti[i].prezime, studenti[i].ime, &studenti[i].broj_bodova1, &studenti[i].broj_bodova2) == 4 && i<300)
		i++;
	fclose(ulaz);
	
	if ((ulaz = fopen("ispit.txt","w")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}
	for (j=0; j<i-1; j++)
		for (k=j+1; k<i; k++)
			if (studenti[k].broj_bodova1 + studenti[k].broj_bodova2 > studenti[j].broj_bodova1 + studenti[j].broj_bodova2 ) {
				tmp = studenti[j];
				studenti[j] = studenti[k];
				studenti[k] = tmp;
			}
			
			
	for (j=0; j<i; j++)
		fprintf(ulaz,"%-20s%-15s%2d %2d\n", studenti[j].prezime, studenti[j].ime, studenti[j].broj_bodova1, studenti[j].broj_bodova2);
	fclose(ulaz);
}

void upisi(){
	struct Student studentx;
	FILE *ulaz;
	char c;
	/* Otvaranje datoteka */
	if ((ulaz = fopen("ispit.txt","a+")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}
	c = fgetc(ulaz);
	while(c!=EOF) c = fgetc(ulaz);
	
	printf("Unesite ime: ");
	scanf("%s",studentx.ime);
	printf("Unesite prezime: ");
	scanf("%s",studentx.prezime);
	printf("Unesite broj bodova na I parcijalnom: ");
	scanf("%d", &studentx.broj_bodova1);
	printf("Unesite broj bodova na II parcijalnom: ");
	scanf("%d", &studentx.broj_bodova2);
		
		
	// Upis niza u datoteku
	fprintf(ulaz,"%-20s%-15s%2d %2d\n", studentx.prezime, studentx.ime, studentx.broj_bodova1, studentx.broj_bodova2);
	
	fclose(ulaz);
	sortiraj();
}

void ispis(){
	struct Student studenti[300];
	FILE *ulaz;
	int i, j;

	/* Otvaranje datoteka */
	if ((ulaz = fopen("ispit.txt","r")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}
	i=0;
	while (fscanf(ulaz,"%20s%15s%2d %2d\n", studenti[i].prezime, studenti[i].ime, &studenti[i].broj_bodova1, &studenti[i].broj_bodova2) == 4 && i<300)
		i++;
		
	for(j=0;j<i;j++){
	//	if(studenti[j].broj_bodova1>=10 && studenti[j].broj_bodova2>=10)
		printf("%d. %s %s - %d, %d\n", j+1, studenti[j].ime, studenti[j].prezime, studenti[j].broj_bodova1, studenti[j].broj_bodova2);
	}
	
	fclose(ulaz);
	sortiraj();
}

void brisi(){
	int n=0;
	
	printf("Unesite redni broj studenta kojeg zelite obrisati: ");
	scanf("%d", &n);
	
	struct Student studenti[300], tmp;
	FILE *ulaz;
	int i, j, k;

	/* Otvaranje datoteka */
	if ((ulaz = fopen("ispit.txt","r")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}

	/* Ucitavanje datoteke u niz studenti */
	i=0;
	while (fscanf(ulaz,"%20s%15s%2d %2d\n", studenti[i].prezime, studenti[i].ime, &studenti[i].broj_bodova1, &studenti[i].broj_bodova2) == 4 && i<300)
		i++;
	fclose(ulaz);
	
	int pamti=0;
	for(j=0; j<i; j++) {

		if(j==n) {
			printf("Student %s %s obrisan\n", studenti[j].ime, studenti[j].prezime);
			pamti=1;
			for (k=j; k<i-1; k++) {
				studenti[k] = studenti[k+1];
			}
			i--;
		}
	}
	
	if(pamti==0) { printf("Student sa rednim brojem %d ne postoji!\n", n); return; }
	
	if ((ulaz = fopen("ispit.txt","w")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}
	
	for (j=0; j<i; j++)
		fprintf(ulaz,"%-20s%-15s%2d %2d\n", studenti[j].prezime, studenti[j].ime, studenti[j].broj_bodova1, studenti[j].broj_bodova2);
	
	fclose(ulaz);
	sortiraj();
}

void izmjena(){
	int n=0;
	struct Student studenti[300], tmp;
	printf("Unesite redni broj studenta kojeg zelite mijenjati: ");
	scanf("%d", &n);
	printf("Unesite novo ime: "); scanf("%s", tmp.ime);
	printf("Unesite novo prezime: "); scanf("%s", tmp.prezime);
	printf("Unesite novi broj bodova (I parcijalni): "); scanf("%d", &tmp.broj_bodova1);
	printf("Unesite novi broj bodova (II parcijalni): "); scanf("%d", &tmp.broj_bodova2);
	
	FILE *ulaz;
	int i, j, k;

	/* Otvaranje datoteka */
	if ((ulaz = fopen("ispit.txt","r")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}

	/* Ucitavanje datoteke u niz studenti */
	i=0;
	while (fscanf(ulaz,"%20s%15s%2d %2d\n", studenti[i].prezime, studenti[i].ime, &studenti[i].broj_bodova1, &studenti[i].broj_bodova2) == 4 && i<300)
		i++;
	fclose(ulaz);
	
	int pamti=0;
	for(j=0;j<i;j++){
		
		if(n==j){
			pamti = 1;
			studenti[j] = tmp;
		}
		
	}
	
	if(pamti==0) { printf("Student sa rednim brojem %d ne postoji!\n", n); return; }
	
	
	if ((ulaz = fopen("ispit.txt","w")) == NULL) {
		printf("Greska pri otvaranju datoteke ispit.txt");
		exit(1);
	}
	
	for (j=0; j<i; j++)
		fprintf(ulaz,"%-20s%-15s%2d %2d\n", studenti[j].prezime, studenti[j].ime, studenti[j].broj_bodova1, studenti[j].broj_bodova2);
	
	fclose(ulaz);
	sortiraj();
}

int main(){
	int opcija=0;
	do{
		printf("Unesite 1 za dodavanje, 2 za brisanje, 3 za izmjenu, 4 za ispis, 0 za izlaz: ");
		scanf("%d", &opcija);
	
	if(opcija==1) upisi(); 
	if(opcija==2) brisi();
	if(opcija==3) izmjena();
    if(opcija==4) ispis();
    
	}while(opcija!=0);
	
	return 0;
}