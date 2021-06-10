#include <stdio.h>
float maxtemp(float p[8])
{
	int i;
	float max=p[0];
	for(i=0;i<8;i++)
	{
		if(p[i]>max) max=p[i];
	}
	return max;
}

float prtemp(float p[8]){
	int i;
	float suma=0;
	for(i=0;i<8;i++)
	{
		suma+=p[i];
	}
	suma=suma/8;
	return suma;
}

int main() {
	int niz[8];
	printf("Unesite temperature: ");
	int i;
	for(i=0;i<8;i++)
	{
		scanf("%f", &niz[i]);
	}
	float temp1 = maxtemp(niz);
	printf("Maksimalna temperatura: %.1f\n", temp1);
	float temp2 = prtemp(niz);
	printf("Prosjecna temperatura: %.1f", temp2);
	return 0;
}
