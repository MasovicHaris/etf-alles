#include <stdio.h>
#include <stdlib.h> /* Zbog funkcije exit() */
#include <string.h>

int n=0;

void unesi(char niz[], int velicina){
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

void unesi_fajl(FILE *ulaz, char niz[], int velicina){
	char znak = fgetc(ulaz);
	if (znak == '\n') znak = fgetc(ulaz);
	int i = 0;
	while (i < velicina-1 && znak != '\n' && znak != EOF) {
		niz[i] = znak;
		i++;
		znak = fgetc(ulaz);
	}
	niz[i]='\0';

}

struct predmeti {
	int index;
	int broj_predmeta;
	char naziv_predmeta[1000];
};



void ispis(){
	FILE *ulaz;
	FILE *ulazdva;
	int  i;
	int  indexi[1000]= {0}, predmet[1000]= {0}, ocjena[1000]= {0};

	struct predmeti predmetix[100];

	char predmet1[1000];
	ulaz = fopen("ispiti.txt", "r");
	ulazdva = fopen("predmeti.txt", "r");

	if (ulaz == NULL) {
		printf("Greska prilikom otvaranja datoteke 'ispiti.txt'! \n");
		exit(1);
	}

	if (ulazdva == NULL) {
		printf("Greska prilikom otvaranja datoteke 'predmeti.txt'! \n");
		exit(1);
	}

	n=0;
	while ((fscanf (ulazdva ,"%d ", &predmetix[n].broj_predmeta) == 1) && (n < 1000)) {
		unesi_fajl(ulazdva, predmetix[n].naziv_predmeta, 1000);
		n++;
	}
	
	int pamti=0;
	do{
	printf("Unesite predmet: ");
	unesi(predmet1,1000);
	
	for(i=0; i<n; i++) {

		if(strcmp(predmetix[i].naziv_predmeta, predmet1)==0) {
			pamti = predmetix[i].broj_predmeta;
		}

	}
	if(pamti==0) {
		printf("Nepostojeci predmet!");
	}
	}while(pamti==0);
	
	n=0;

	while ((fscanf (ulaz ,"%d %d %d\n", &indexi[n], &predmet[n], &ocjena[n]) == 3) && (n < 1000)) {
		n++;
	}


	double prosjek=0, postotak=0;
	int broj=0, broj_polozenih=0;
	int suma=0;
	for(i=0; i<n; i++) {

		if( predmet[i] == pamti) {
			broj++;
			suma+=ocjena[i];
			if(ocjena[i]>=6 && ocjena[i]<=10) broj_polozenih++;
		}

	}

	if(broj!=0) {
		prosjek = (double)suma/broj;
		postotak = (double)broj_polozenih*100/broj;

		printf("Prosjecna ocjena: %.2f",  prosjek);
		printf("\nProlaznost: %g%%\n", postotak);
	} else printf("Zalimo, ali ne postoje podaci o predmetu %s!", predmet1);

	fclose (ulaz);
	fclose (ulazdva);
}

void statistiku_osobe(){
	FILE *ulaz;
	FILE *ulazdva;
	int  i;
	int  indexi[1000]= {0}, predmet[1000]= {0}, ocjena[1000]= {0};


	char predmet1[1000];
	ulaz = fopen("ispiti.txt", "r");

	if (ulaz == NULL) {
		printf("Greska prilikom otvaranja datoteke 'ispiti.txt'! \n");
		exit(1);
	}

	
	int br_ocjena=0;
	double suma=0;
	while ((fscanf (ulaz ,"%d %d %d\n", &indexi[n], &predmet[n], &ocjena[n]) == 3) && (n < 1000)) {
		n++;
	}
	
	
	int broj_indeksa, br_prolaznih_ocjena=0;
	double prosjek, prolaznost;
			printf("Unesite broj indexa: ");
            scanf("%d", &broj_indeksa);
            
            for(i=0; i<n; i++) {
                if(indexi[i] == broj_indeksa) {
                    suma+=ocjena[i];
                    br_ocjena++;
                    if(ocjena[i] >= 6 && ocjena[i] <= 10)
                        br_prolaznih_ocjena++;
                }
            }
            if (suma == 0) {
                printf("Zalimo, ali ne postoje podaci o studentu sa brojem indexa %d!\n",broj_indeksa);
                return;
            }
            prosjek = (double)suma/br_ocjena;
            prolaznost = (double)br_prolaznih_ocjena/br_ocjena*100;
            printf("Student je slusao %d predmeta, a polozio %d (%g%%).", br_ocjena, br_prolaznih_ocjena, prolaznost);
            printf("\nProsjecna ocjena polozenih predmeta je %.1f\n", prosjek);
            
     fclose(ulaz);
}

int main(){
	int opcija;
	do {
		printf("Unesite 1 za statistiku studenta, 2 za statistiku predmeta, 0 za izlaz: ");
		scanf("%d", &opcija);
		switch(opcija) {
		case 1:
			statistiku_osobe();
			break;
		case 2:
			ispis();
			break;
		case 0:
			break;
		default:
			printf("Nepoznata opcija\n");
		}
	} while (opcija != 0);

	return 0;
}