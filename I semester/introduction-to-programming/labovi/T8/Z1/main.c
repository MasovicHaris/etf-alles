#include <stdio.h>

int f(int *a, int b){
	int c;
	c=*a+b;
	*a=*a+5;
	b=b+5;
	return c;
}



int main() {
	int a=1, b=1, c;
	printf("\nPrije funkcije f:a=%d, b=%d",a,b);
	c=f(&a,b);
	printf("\nPoslije funkcije f: a=%d b=%d c=%d",a,b,c);
	return 0;
}
