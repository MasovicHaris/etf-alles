// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int main() {
	int svota, pedeset, dvadeset, deset, pet, dvije, jedna, x, y, z, k, i;
	printf("Unesite iznos: ");
	scanf("%d", &svota);
	while(svota<=0)
	{
		printf("Pogresan unos.\n");
		printf("Unesite iznos: ");
		scanf("%d", &svota);
	}
	
	pedeset=svota/50;
	x=svota%50;
	dvadeset=x/20;
	y=x%20;
	deset=y/10;
	z=y%10;
	pet=z/5;
	k=z%5;
	dvije=k/2;
	i=k%2;
	jedna=i;
	printf("%d novcanica od 50 KM\n", pedeset);
	printf("%d novcanica od 20 KM\n", dvadeset);
	printf("%d novcanica od 10 KM\n", deset);
	printf("%d novcanica od 5 KM\n", pet);
	printf("%d novcanica od 2 KM\n", dvije);
	printf("%d novcanica od 1 KM\n", jedna);
	
	return 0;
}
