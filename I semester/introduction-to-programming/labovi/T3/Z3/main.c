#include <stdio.h>
/* Napisati program koji će ispisati brojeve koji su djeljivi sa 5, 7 ili 11, a koji su manji ili jednaki od nekog broja n koji je učitan sa tastature.
Brojeve treba ispisati od najvećeg prema najmanjem. Obavezno koristiti for petlju i if-else strukturu.
Primjer ulaza i izlaza programa:
Unesite broj n: 20
	20
	15
	14
	11
	10
	7
	5 
*/
int main() {
	int i, n;
	printf("Unesite broj n: ");
	scanf("%d", &n);
	for(i=n;i>0;i--)
	{
		if(i%5==0 || i%7==0 || i%11==0) printf("%d\n", i);
	}
	return 0;
}
