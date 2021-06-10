#include <stdio.h>
#define PI 3.14


int main()
{
    float R, P, V; float Pk;

    printf("Unesi poluprecnik: ");
    scanf("%f", &R);
    P=(R*R)*PI;
    V=(4./3)*R*R*R*PI;
    Pk=4*R*R*PI;
    
    printf("\n Povrsina kruga sa poluprecnikom %2f je %.2f", R,P);
    printf("\n Zapremina kugle sa poluprecnikom %2f je %.2f", R,V);
    printf("\n Povrsina lopte je: %.2f", Pk);
    return 0;
}