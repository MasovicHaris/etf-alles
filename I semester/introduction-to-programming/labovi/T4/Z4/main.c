#include <stdio.h>

int main() {
	int mjesec, godina;
	int brojac=0;
	printf("Unesite mjesec: ");
	scanf("%d", &mjesec);
	printf("Unesite godinu: ");
	scanf("%d", &godina);
	
	switch(mjesec){
		case 1:
		printf("Januar %d, broj dana: 31", godina);
		break;
		case 2:
		
		if(godina%400==0) printf("Februar %d, broj dana: 29", godina);
		else if(godina%100==0) printf("Februar %d, broj dana: 28", godina);
		else if(godina%4==0) printf("Februar %d, broj dana: 29", godina);
		else printf("Februar %d, broj dana: 28", godina);
		
		
		break;
		
		case 3:
		printf("Mart %d, broj dana: 31", godina);
		break;
		case 4:
		printf("April %d, broj dana: 30", godina);
		break;
		case 5:
		printf("Maj %d, broj dana: 31", godina);
		break;
		case 6:
		printf("Juni %d, broj dana: 30", godina);
		break;
		case 7:
		printf("Juli %d, broj dana: 31", godina);
		break;
		case 8:
		printf("Avgust %d, broj dana: 31", godina);
		break;
		case 9:
		printf("Septembar %d, broj dana: 30", godina);
		break;
		case 10:
		printf("Oktobar %d, broj dana: 31", godina);
		break;
		case 11:
		printf("Novembar %d, broj dana: 30", godina);
		break;
		case 12:
		printf("Decembar %d, broj dana: 31", godina);
		break;
		
	}
	return 0;
}
