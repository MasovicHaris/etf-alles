#include <stdio.h>
/* Napišite program koji omogućuje korisniku da unese proizvoljan broj 
cijelih brojeva sa tastature, pri čemu broj -1 označava kraj unosa.
Zatim se na ekranu ispisuje koliko unesenih brojeva je djeljivo sa 5, sa 7 i sa 11. 
Primjer ulaza i izlaza:
    Unesite brojeve:
    2
    5
    6
    16
    5
    22
    35
    55
    56
    -1
    Djeljivih sa 5: 4
    Djeljivih sa 7: 2
    Djeljivih sa 11: 2 */
    // 5 7 11 35 77 385
int main() {
    int n;
    int b1=0, b2=0, b3=0;
    printf("Unesite brojeve:\n");
	do{
	    scanf("%d", &n);
	    if(n%5==0) b1++;
	    if(n%7==0) b2++;
	    if(n%11==0) b3++;
	    
	    
	    
	    
	    
	}while(n!=-1);
	
	printf("Djeljivih sa 5: %d\n", b1);
	printf("Djeljivih sa 7: %d\n", b2);
	printf("Djeljivih sa 11: %d\n", b3);
	
	
	
	return 0;
}
