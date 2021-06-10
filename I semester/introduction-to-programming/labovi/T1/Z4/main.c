#include <stdio.h>
#define PI 3.14

// obim O=a+b+c;
// povrsina P=2ab+2ac+2bc;

int main()
{
    float a, b, c, zapreminaK, povrsinaK;
    printf("Unesi stranice a, b, c: ");
    scanf("%f %f %f", &a, &b, &c);
    
    // kvadar
    povrsinaK=2*a*b+2*a*c+2*b*c;
    zapreminaK=a*b*c;
    printf("%f %f", povrsinaK, zapreminaK);
    
    float r, h, zapreminaV, povrsinaV;
    printf("\nUnesite poluprecnik i visinu: ");
    scanf("%f %f", &r, &h);
    povrsinaV=2*r*PI*h;
    zapreminaV=r*r*PI*h;
    
    printf("%f %f", povrsinaV, zapreminaV);
    
    
    // povrsina1 + povrsina2 - 2*r*r*PI
    
    
    float povrsina, zapremina;
    povrsina=povrsinaV+povrsinaK;
    zapremina=zapreminaV+zapreminaK;
    printf("\n Povrsina i Zapremina: %.2f %.2f", povrsina, zapremina);
    
    
    
    return 0;
}