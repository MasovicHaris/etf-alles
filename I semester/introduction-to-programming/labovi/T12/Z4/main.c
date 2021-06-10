#include <stdio.h>
#include <stdlib.h> /* Zbog funkcije exit() */
#include <string.h>
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

void unesi_fajl(FILE *ulaz, char niz[], int velicina)
{
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
    int broj_predmeta;
    char naziv_predmeta[1000];
};



int main() {
	FILE *ulaz;
	FILE *ulazdva;
	int n=0, i;
	int  indexi[1000]={0}, predmet[1000]={0}, ocjena[1000]={0};
	
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
    
	
	while ((fscanf (ulazdva ,"%d ", &predmetix[n].broj_predmeta) == 1) && (n < 1000)) {
		unesi_fajl(ulazdva, predmetix[n].naziv_predmeta, 1000);
        n++;
    }
    int nepostojeci=0;
    int pamti=0;
    do{
    printf("Unesite predmet: ");
	unesi(predmet1,1000);
		
		
    
    
    for(i=0;i<n;i++){
		
		if(strcmp(predmetix[i].naziv_predmeta, predmet1)==0) {
			pamti = predmetix[i].broj_predmeta;
		}
		
	}
	if(pamti==0) { printf("Nepostojeci predmet!"); }
    }while(pamti==0);
    n=0;
    
    while ((fscanf (ulaz ,"%d %d %d\n", &indexi[n], &predmet[n], &ocjena[n]) == 3) && (n < 1000)) {
        n++;
    }
    
    
	double prosjek=0, postotak=0;
	int broj=0, broj_polozenih=0;
	int suma=0;
	for(i=0;i<n;i++){
		
		if( predmet[i] == pamti) {
			broj++;
			suma+=ocjena[i];
			if(ocjena[i]>=6 && ocjena[i]<=10) broj_polozenih++;
		}
		
	}
	
	if(broj!=0){
		prosjek = (double)suma/broj;
		postotak = (double)broj_polozenih*100/broj;
	
	printf("Prosjecna ocjena: %.2f",  prosjek);
	printf("\nProlaznost: %g%%", postotak);
	}
	else printf("Zalimo, ali ne postoje podaci o predmetu %s!", predmet1);
	
	fclose (ulaz);
	fclose (ulazdva);
	return 0;
}