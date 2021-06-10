#include <stdio.h>
#define PRITISAK_DONJA 65.0
#define PRITISAK_GORNJA 90.0
#define DPRITISAK_DONJA 105.0
#define DPRITISAK_GORNJA 140.0
#define Dpuls 65.0
#define Gpuls 80.0

int main() {
	float pritisak, dpritisak, puls;
        printf("Unesite sistolicki, dijastolicki pritisak i puls: ");
        scanf("%f %f %f", &pritisak, &dpritisak, &puls);
        if (pritisak > PRITISAK_DONJA && pritisak < PRITISAK_GORNJA){
        printf("SP: normalan\n");
        }
        else{
            printf("SP: nije normalan\n");
        }

        if (dpritisak > DPRITISAK_DONJA && dpritisak < DPRITISAK_GORNJA){
        printf("DP: normalan\n");
        }
        else{
            printf("DP: nije normalan\n");
        }

        if (puls > Dpuls && puls < Gpuls){
        printf("Puls: normalan\n");
        }
        else{
            printf("Puls: nije normalan\n");
        }
}
