// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <string.h>

struct Kurs 
{
    char valuta[5];
    float vrijednost;
};


float razmjena(struct Kurs p[], int velicina, const char* string, float iznos)
{
    
    int i=0; 
    for(i=0 ; i<velicina; i++)
    {
        if(strcmp(p[i].valuta, string)==0)
        {
            return p[i].vrijednost*iznos;
        }
    }
    return 0;
}


int main()
{
    return 0;
}