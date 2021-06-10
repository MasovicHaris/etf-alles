// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <string.h>

struct Oblik 
	{
		char naziv[20];
		int br_stranica;
		float stranice[300];
	};
	

void dodaj_oblik(struct Oblik o1)
{
	FILE* dat=fopen("oblici.dat", "rb");
	unsigned short br_oblika=0;
	int ucitano=fread(&br_oblika, sizeof(unsigned short), 1, dat);		//povecavanje broja oblika
	fclose(dat);
	br_oblika++;
	
	dat=fopen("oblici.dat", "r+b"); 
	int zapisano=fwrite(&br_oblika, sizeof(br_oblika), 1, dat); //promijeni valjda samo prvi broj u datoteci koji govori koliko oblika ima u njoj
	fclose(dat);
	
	dat=fopen("oblici.dat", "a+b");
	zapisano=fwrite(o1.naziv, 1, 20, dat);			//dodavanje na kraj
	fclose(dat);
	
	dat=fopen("oblici.dat", "a+b");
	zapisano=fwrite(&o1.br_stranica, 1, 1, dat);
	fclose(dat);

	int j=0;
	for(j=0; j<o1.br_stranica; j++)
	{
		dat=fopen("oblici.dat", "a+b");
		zapisano=fwrite(&o1.stranice[j], sizeof(float), 1, dat);
		fclose(dat);
	}

	
	
}

void izbaci_duple()
{
	short broj_obl=0;
    struct Oblik oblici[100];

    FILE* dat=fopen("oblici.dat", "rb");

    int ucitano= -1;
	ucitano = fread(&broj_obl, sizeof(unsigned short), 1, dat);        //imamo koliko ima oblika u datoteci
    int i=0, j=0;
    unsigned char br_str=0;			//unsigned jer je 0-255
    float str=0;			// zato jer je 4bajta
    for(i=0; i<broj_obl; i++)
    {
        ucitano=fread(&oblici[i].naziv, 1, 20, dat);
        oblici[i].naziv[ucitano] = 0;
        ucitano=fread(&br_str, 1, 1, dat);
        for(j=0; j<br_str; j++)
        {
            ucitano=fread(&str, sizeof(str), 1, dat);		//učitava se str po str
            oblici[i].stranice[j]=str;
        }
        oblici[i].br_stranica=br_str;
    }
    
    fclose(dat);
    
    int k=0;
    
    for(i=0; i<broj_obl; i++)
    {
    	for(j=0; j<broj_obl; j++)
    	{
    		if(j==i) continue;
    		if(strcmp(oblici[i].naziv, oblici[j].naziv)==0)
    		{
    			for(k=j; k<broj_obl-1; k++)
    			{
    				oblici[k]=oblici[k+1];
    			}
    			broj_obl--;
    			j--;
    		}
    	}
    }
    
    dat=fopen("oblici.dat", "wb");
	int zapisano=fwrite(&broj_obl, sizeof(broj_obl), 1, dat);
	fclose(dat);
	
	for(i=0; i<broj_obl; i++)
	{
		dat=fopen("oblici.dat", "a+b");
		zapisano=fwrite(oblici[i].naziv, 1, 20, dat);			//dodavanje na kraj
		fclose(dat);
		
		dat=fopen("oblici.dat", "a+b");
		zapisano=fwrite(&oblici[i].br_stranica, 1, 1, dat);
		fclose(dat);
		
		for(j=0; j<oblici[i].br_stranica; j++)
		{
			dat=fopen("oblici.dat", "a+b");
			zapisano=fwrite(&oblici[i].stranice[j], sizeof(float), 1, dat);
			fclose(dat);
		}
	
	}
    
}

struct Oblik daj_najveci()
{
	unsigned short broj_obl=0;
    struct Oblik oblici[100];

    FILE* dat=fopen("oblici.dat", "rb");

    int ucitano= -1;
	ucitano = fread(&broj_obl, sizeof(unsigned short), 1, dat);        //imamo koliko ima oblika u datoteci
    int i=0, j=0;
    unsigned char br_str=0;			//unsigned jer je 0-255
    float str=0;			// zato jer je 4bajta
    for(i=0; i<broj_obl; i++)
    {
        ucitano=fread(oblici[i].naziv, 1, 20, dat);
        oblici[i].naziv[ucitano] = 0;
        ucitano=fread(&br_str, 1, 1, dat);
        for(j=0; j<br_str; j++)
        {
            ucitano=fread(&str, sizeof(str), 1, dat);		//učitava se str po str
            oblici[i].stranice[j]=str;
        }
        oblici[i].br_stranica=br_str;
    }
    fclose(dat);
    
    double maxobim=-1;
    double obim=0;
    int pozicija=0;
    
    for(i=0; i<broj_obl; i++)
    {
    	obim=0;
    	for(j=0; j<oblici[i].br_stranica; j++)
    	{
    		obim+=oblici[i].stranice[j];
    	}
    	if(obim>maxobim)
    	{
    		maxobim=obim;
    		pozicija=i;
    	}
    	
    }
    
    return oblici[pozicija];
	
}

int main() 
{
 return 0;
	
}