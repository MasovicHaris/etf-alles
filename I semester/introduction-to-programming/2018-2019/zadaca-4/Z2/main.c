// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



double parallel_max(double *niz, double *kraj)
{
	
	if(niz==kraj-1)
	{
		return *niz;
	}
	int sirina=kraj-niz;

	if(parallel_max(niz, niz+sirina/2)>parallel_max((sirina/2)+niz, kraj))
	return parallel_max(niz, niz+sirina/2);
	else
	return parallel_max((sirina/2)+niz, kraj);

	
}






int main() {
	printf("Zadaća 3, Zadatak 2");
	return 0;
}
