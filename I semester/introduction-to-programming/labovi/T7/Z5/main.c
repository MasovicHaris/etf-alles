#include <stdio.h>
#include <math.h>
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


double sinus(double x, int n){
	int i;
	double suma=0;
	for(i=1;i<=n;i++)
	{
		suma+=(pow(-1,i-1)*pow(x, 2*i-1))/(faktorijel(2*i-1));
	}
	return suma;
	
}


int main() {
	double x;
	int n; 
	printf("Unesite x: \n"); scanf("%lf", &x);
	printf("Unesite n: \n"); scanf("%d", &n);
	double y=sin(x);
	printf("sin(x)=%f\n", y);
	double k=sinus(x,n);
	printf("sinus(x)=%f\n", k);
	
	double razlika=0, razlikap;
	
	razlika=fabs(y-k);
	razlikap=razlika*100;
	
	printf("Razlika: %f (%.2f%%).", razlika, razlikap);
	
	
	return 0;
}
