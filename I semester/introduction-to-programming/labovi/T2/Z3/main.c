#include <stdio.h>

int main(){
int dan, mjesec;
        printf("Dan: ");
        scanf("%d", &dan);
        printf("Mjesec: ");
        scanf("%d", &mjesec);

         /*if((dan>=20 && mjesec==1 || dan<=18 && mjesec==2)){
                printf("Znak je: Vodolija");

        }else if  */
        
        switch(mjesec){
        case 1:
            if(dan>=20 && dan<=31) printf("Vas znak je Vodolija!");
            if(dan>=1 && dan<=19) printf("Vas znak je Jarac! ");
            break;
        case 2:
            if(dan>=1 && dan<=18) printf("Vas znak je Vodolija!");
            if(dan>=19 && dan<=28) printf("Vas znak je Ribe!" );
            break;
        case 3:
            if(dan>=1 && dan<=20) printf("Vas znak je Ribe!");
            if(dan>=21 && dan<=31) printf("Vas znak je Ovan!");

            break;
        case 4:
            if(dan>=1 && dan<=19) printf("Vas znak je Ovan!");
            if(dan>=20 && dan<=30) printf("Vas znak je Bik!");

            break;
        case 5:
            if(dan>=1 && dan<=20) printf("Vas znak je Bik!");
            if(dan>=21 && dan<=31) printf("Vas znak je Blizanci!");
            break;
        case 6:
            if(dan>=1 && dan<=20) printf("Vas znak je Blizanci!");
            if(dan>=21 && dan<=30) printf("Vas znak je Rak!");
            break;
        case 7:
            if(dan>=1 && dan<=22) printf("Vas znak je Rak!");
            if(dan>=23 && dan<=31) printf("Vas znak je Lav!");
            break;
        case 8:
            if(dan>=1 && dan<=22) printf("Vas znak je Lav!");
            if(dan>=23 && dan<=31) printf("Vas znak je Djevica!");
            break;
        case 9:
            if(dan>=1 && dan<=22) printf("Vas znak je Djevica!");
            if(dan>=23 && dan<=30) printf("Vas znak je Vaga!");
            break;
        case 10:
            if(dan>=1 && dan<=22) printf("Vas znak je Vaga!");
            if(dan>=23 && dan<=31) printf("Vas znak je Skorpija!");
            break;
        case 11:
            if(dan>=1 && dan<=21) printf("Vas znak je Skoprija!");
            if(dan>=22 && dan<=30) printf("Vas znak je Strijelac!");
            break;
        case 12:
            if(dan>=1 && dan<=21) printf("Vas znak je Strijelac!");
            if(dan>=22 && dan<=31) printf("Vas znak je Jarac!");
            break;



        }

    return 0;
}