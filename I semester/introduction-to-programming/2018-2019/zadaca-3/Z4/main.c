// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

void unesi(char niz[], int velicina) {
    char znak = getchar();
    if (znak == '\n') znak=getchar();
    int i = 0;
    while (i < velicina-1 && znak != '\n') {
        niz[i] = znak;
        i++;
        znak = getchar();
    }
    niz[i]='\0';
}

int main() 
{

int sirina, visina;

char string[200];
char matrica[30][6000];

scanf("%d", &sirina);
scanf("\n%d", &visina);
unesi(string, 200);
printf("\n");
int i, j;

for(i=0; i<visina; i++)
{
    for(j=0; j<=sirina*27; j++)
    {
        matrica[i][j]=getchar();
    }

}

int start=0;
char *p=string;
char *k=string;
    for(i=0; i<visina; i++)
    {
        while(*p!='\0')
        {
            if(*p>='a' && *p<='z')
            {
                start=*p-97;
            }
              else if(*p>='A' && *p<='Z')
             {
                 start=*p-65;
             }
             else
             {
                 start=26;
             }
                j=0;
            while(j<sirina)
            {
                printf("%c", matrica[i][start*sirina+j]);
                j++;
            }

            p++;
        }
        printf("\n");
        p=k;
        
    }



return 0;

}
