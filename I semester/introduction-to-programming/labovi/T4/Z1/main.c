#include <stdio.h>
#include <math.h>

int main() {
	
	float a,b,c, x1, x2, x1Re, x2Re, x1Im, x2Im, t, D;
	printf("\n Unesite koeficijente kvadratne jednadzbe a,b,c:");
	scanf("%f %f %f", &a, &b, &c);
	D= b*b - 4.0*a*c;
	
	if(D>0)
	{
		t=sqrt(D);
		x1= (-b + t)/(2*a);
		x2= (-b - t)/(2*a);
		printf("\n Rjesenja su: x1=%f   x2=%f\n", x1, x2);
	    
	}
	else if(D==0)
	{
		x1=-b/(2*a);
		printf("\n Rjesenja su: x1=x2=%f", x1);
	    
	}else
	{
		t=sqrt(-D);
		x1Re=-b/(2*a);
		x2Re=x1Re;
		x1Im=t/(2*a);
		x2Im=-x1Im;
		printf("\n Rjesenja su: x1 = (%f,%f)\n", x1Re, x1Im);
		printf(" x2 = (%f,%f)\n", x2Re, x2Im);
	    
	}
	
	
	return 0;
}
