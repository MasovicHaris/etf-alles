#include <stdio.h>

int Faktorijel(int x){

	int i; int fakt=1;
	if(x>=1){
	for(i=1;i<=x;i++)
	{
		fakt=fakt*i;
	}
	} else fakt=1;
	
	return fakt;
}

int main() {
	int  n;
	int i;
	double x, suma=0;
	printf("Unesite broj n u intervalu [1, 12]: ");
	scanf("%d", &n);
	printf("Unesite realan broj x: ");
	scanf("%lf", &x);
	
	
	for(i=1;i<=n;i++)
	{
		suma= suma + (x/Faktorijel(i));
	} 
	printf("Suma od 1 do %d za x = %.3f je %.3f", n, x, suma);
	return 0;
}
