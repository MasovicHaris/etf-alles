#include <stdio.h>
/* 4.  Napravite program "Snijeg" koji, za uneseni broj n, na ekranu iscrtava uzorak od n×n zvjezdica koja su naizmjenično razmaknute sa po jednim razmakom. 

Primjer ulaza i izlaza programa

Unesite broj n: 5
	* * * * *
	 * * * * *
	* * * * *
	 * * * * *
	* * * * * */
	
int main() {
	int i, j, n;
	printf("Unesite broj n: ");
	scanf("%d", &n);
	
	for(i=0;i<n;i++)
	{	
		for(j=0;j<n;j++){
			if(i%2==0 && j%2==0) { printf("*");} 
			else if(i%2==0 && j%2==1){ printf(" * "); }
			else if(i%2==1 && j%2==0) printf(" * ");
			else printf("*");
		}
		printf("\n");
	}
}
