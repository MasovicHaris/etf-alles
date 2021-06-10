#include <stdio.h>

int main(){ 
int brojac=0;
        int a, b, c;
        printf("Unesite tri broja: ");
        scanf("%d %d %d", &a, &b, &c);
        if((a>=50 && a<=200) && (b>=50 && b<=200) && (c>=50 && c<=200))
        {
            if(a==b && a==c && b==c) brojac=1;
            if(a!=b) brojac++; if(a!=c) brojac++; if(b!=c) brojac++;
            if(a>b) {
                    int x;
                    x=b;
                    b=a;
                    a=x;

            }
            if(a>c) {
                    int x;
                    x=c;
                    c=a;
                    a=x;
            }
            if(b>c) {
                    int x;
                    x=c;
                    c=b;
                    b=x;
            }

            printf("Brojevi poredani po velicini glase: %d,%d,%d\n", a, b, c);
            if(brojac==1) printf("Unesen je %d razlicit broj", brojac);
            else printf("Unesena su %d razlicita broja", brojac);
        }else{
            printf("Svi brojevi nisu iz intervala 50 do 200");
        }
    
        // preko petlji
       /*
        int x[3]; int i,j;
            printf("Unesi 3 broja: ");
            for(i=0;i<3;i++)
            {
                scanf("%d", &x[i]);
            }

            int brojac=0;
            if((x[0]>=50 && x[0]<=200)&&(x[1]>=50 && x[1]<=200)&&(x[2]>=50 && x[2]<=200)){
                if(x[0]!=x[1]) brojac++; if(x[0]!=x[2]) brojac++; if(x[1]!=x[2]) brojac++;
                    printf("Sortirani brojevi preko for petlji: ");
                    for(i=0; i<3;i++){
                        for(j=i+1;j<3;j++)
                        {
                            
                            if(x[i]>x[j]){
                                int p;
                                p=x[j];
                                x[j]=x[i];
                                x[i]=p;
                            }
                        }

                        printf("%d ", x[i]);
                    }
                    printf("Broj razlicitih brojeva %d", brojac);
            }else{
                printf("Ne valjaju intervali");
            }
        
        */
        return 0;
}