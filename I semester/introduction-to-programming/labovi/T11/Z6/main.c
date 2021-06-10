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

struct Osoba {
		char ime[15];
		char prezime[20];
		int telefon;
};

struct Osoba unos_osobe(){
	struct Osoba o;
	printf("Unesite ime: "); unesi(o.ime, 15);
	printf("Unesite prezime: "); unesi(o.prezime, 20);
	printf("Unesite broj telefona: "); scanf("%d", &o.telefon);
	
	return o;
}

void ispis_osobe(struct Osoba o){
	printf("%s %s, Tel: %d\n", o.ime, o.prezime, o.telefon);
	
}


int main() {
	int i=0, k;
	int broj;
	struct Osoba imenik[100];
	do{
		printf("Pritisnite 1 za unos, 2 za ispis, 0 za izlaz: ");
		scanf("%d", &broj);
		if(broj==1){
			imenik[i] = unos_osobe();
			i++;
		}
		else if(broj==2){
			for(k=0;k<i;k++){ printf("\n%d. ", k+1); ispis_osobe(imenik[k]);}
		}
		
		
		
	}while(broj!=0);
	
	
	return 0;
}
