#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	int broj, random_num;
	
	srand(time(NULL));
	random_num = rand() % 100 + 1;
	
	
	// printf("%d", random_num);
	printf("Izabrao sam broj. Probaj ga pogoditi (-1 za izlaz).\n");
	LOOP:
	printf("Unesite broj: ");
	do{
		
		scanf("%d", &broj); 
		if(broj==-1){ printf("Kraj igre."); return 0; }
		else if(broj<0 || broj>100){ printf("Pogresan unos\n"); goto LOOP; }
		
		if(broj>random_num) printf("Broj je manji!\n");
		else if(broj<random_num) printf("Broj je veci!\n");
		
	}while(broj!=random_num); 
	
	printf("Pogodak!");
	return 0;
}
