#include <stdio.h>
#include <math.h>
int n;
long long faktorijel(int x){
	
	int i; 
	long long fakt=1;
	if(x>=1){
	for(i=1;i<=x;i++)
	{
		fakt=fakt*i;
	}
	} else fakt=1;
	
	return fakt;
}


int pascal(int x, int y){
	int paskal=0;
	x--; y--;
	paskal= faktorijel(x)/(faktorijel(y)*faktorijel(x-y));
	
	return paskal;
}

int main() {
	
	int i, j;
	printf("Unesite n: \n"); scanf("%d", &n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i>j || i==j)	printf("%-4d", pascal(i,j));
		}
	printf("\n");
	}
	return 0;
}
