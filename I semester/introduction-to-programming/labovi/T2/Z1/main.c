#include <stdio.h>
#define PRITISAK_DONJA 65.0
#define PRITISAK_GORNJA 90.0
int main(){

		float pritisak;
        printf("Unesite vrijednost sistolickog pritiska: ");
        scanf("%f", &pritisak);
        if (pritisak > PRITISAK_DONJA && pritisak < PRITISAK_GORNJA){
        printf("Sistolicki pritisak je normalan!\n");
        }
        else{
            printf("Sistolicki pritisak nije normalan!\n");
        }
        return 0;
        
}
