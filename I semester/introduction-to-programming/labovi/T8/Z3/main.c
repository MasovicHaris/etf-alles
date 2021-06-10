#include <stdio.h>
/*
 Modificirati prethodni program (zadatak 2.) tako da broj mjerenja nije konstantan (osam) nego se unosi sa tastature.


Da bi se ove funkcije mogle koristiti i u drugim programima, 
trebate proslijediti funkcijama broj mjerenja kao parametar, npr. za funkciju maxtemp() prototip sada treba biti:
float maxtemp(float p[], int br);*/

float maxtemp(float *niz, int vel)
{
	int i;
	float max=*niz;
	for(i=0;i<vel;i++)
	{
		if(*(niz+i)>max) max=*(niz+i);
	}
	return max;
}

float prtemp(float *niz, int vel){
	int i;
	float suma=0;
	for(i=0;i<vel;i++)
	{
		suma+=*(niz+i);
	}
	suma=suma/vel;
	return suma;
}

int main() {
    int vel;
    int niz[100];
    
    printf("Unesite broj mjerenja: ");
    scanf("%d", &vel);
	printf("Unesite temperature: ");
	int i;
	for(i=0;i<vel;i++)
	{
		scanf("%f", niz+i);
	}
	float temp1 = maxtemp(niz,vel);
	printf("Maksimalna temperatura: %.1f\n", temp1);
	float temp2 = prtemp(niz,vel);
	printf("Prosjecna temperatura: %.1f", temp2);
	return 0;
}
