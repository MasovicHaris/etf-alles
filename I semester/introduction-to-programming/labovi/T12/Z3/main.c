#include <stdio.h>
#include <stdlib.h> /* Zbog funkcije exit() */

int main() {
	FILE *ulaz;
	int n=0, i, brPredmeta;
	int  indexi[1000]={0}, predmet[1000]={0}, ocjena[1000]={0};

	ulaz = fopen("ispiti.txt", "r");
	printf("Unesite predmet: ");
    scanf("%d", &brPredmeta);
	
	while ((fscanf (ulaz,"%d %d %d\n", &indexi[n], &predmet[n], &ocjena[n]) == 3) && (n < 1000)) {
        n++;
    }
    
	double prosjek=0, postotak=0;
	int broj=0, broj_polozenih=0;
	int suma=0;
	for(i=0;i<n;i++){
		
		if(brPredmeta ==  predmet[i]) {
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
	else printf("Zalimo, ali ne postoje podaci o predmetu sa brojem %d!", brPredmeta);
	
	fclose (ulaz);
	return 0;
}