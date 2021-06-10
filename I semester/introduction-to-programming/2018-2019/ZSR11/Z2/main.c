// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
 
int jel_slovo(char* c)
{
    if(!((*c>='0' && *c<='9') || *c=='.' || *c==',' || *c=='\n' || *c=='\t' || *c==' '))
    {
        return 1;
    }
    return 0;
}
 
char* udvostruci_rijec(char* s1)
{
    char* poc=s1;
    char* p;
    char* k;
    int duzina=0;
    while(*s1!='\0')
    {
        if(jel_slovo(s1))
        {
            p=s1;
            duzina=0;
            while(jel_slovo(s1) && *s1!='\0')
            {
                s1++;
                duzina++;
            }
            k=s1;
            while(*k!='\0')
            {
                k++;
            }
            while(k>=s1)
            {
                *(k+duzina+1)=*k;
                k--;
            }
            k++;
            *k=' ';
            k++;
            do
            {
                *k=*p;
                k++;
                p++;
                duzina--;
            }
            while(duzina!=0);
            s1=k;
        }
       
        s1++;
    }
    return poc;
}
 
int main() {
   
    char niz[10000]="dobro veče";
    udvostruci_rijec(niz);
    printf("%s", niz);
   
    return 0;
}