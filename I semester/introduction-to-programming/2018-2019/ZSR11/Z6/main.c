// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#define eps 0.00001
#include <math.h>

struct Tacka 
{		
		double x,y;			
};

struct Kruznica
{
	struct Tacka centar;
	double poluprecnik;
};

struct Kruznica obuhvat(struct Tacka* niz, int vel)
{
	int i;
	
	double sumax=0, sumay=0;
	
	for(i=0; i<vel; i++)
	{
		sumax+=niz[i].x;
		sumay+=niz[i].y;
	}
	sumax=(double)sumax/vel;
	sumay=(double)sumay/vel;
	
	double ppmax;
	
	ppmax=pow(sumax-niz[0].x,2) + pow(sumay-niz[0].y,2);
	ppmax=sqrt(ppmax);
	double pp;
	for(i=1; i<vel; i++)
	{
		pp=pow(sumax-niz[i].x,2) + pow(sumay-niz[i].y,2);
		pp=sqrt(pp);
		if(pp-ppmax>eps)
		{
			ppmax=pp;
		}
	}
	struct Kruznica d;
	d.centar.x=sumax;
	d.centar.y=sumay;
	d.poluprecnik=ppmax;
	return d;
}

void ispis_kruznice(struct Kruznica test)
{
	printf("(%.2f,%.2f) %.2f",test.centar.x, test.centar.y, test.poluprecnik);
}

int main() {
	printf("ZSR 11, Zadatak 6");
	return 0;
}
