// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <string.h>

struct Prodavnica {
	char naziv[100];
	int ID;	
};


struct Artikal {
	char naziv[100];
	double cijena;
	int prodavnica;
};	


int ucitaj_artikle (struct Artikal *niz, int kap)
{
	
	FILE* dat=fopen("artikli.bin", "rb");
	if(dat==NULL) return 0;
	int ucitano=fread(niz, sizeof(struct Artikal), kap, dat);
	if(ferror(dat)) return 0;
	
	fclose(dat);
	
	return ucitano;
}

int ucitaj_prodavnice (struct Prodavnica *niz, int kap)
{
	
	int velicina=0, i=0;
	FILE* ulaz=fopen("prodavnice.txt", "r");
	if(ulaz==NULL) return 0;
	char naziv_prodavnice[100];
	int c=314, broj, j=0;
	while(c!=EOF)
	{
		i=-1;
		do {
			if(i<99) i++;
			c=fgetc(ulaz);
			if(c==',') break;
			naziv_prodavnice[i]=c;
		}while(c != EOF);
			naziv_prodavnice[i]='\0';

		i=fscanf(ulaz,"%d", &broj);
		c=fgetc(ulaz);
		strcpy(niz[j].naziv, naziv_prodavnice);
		niz[j].ID=broj;
		j++;
		velicina++;
		if(velicina>=kap) break;
	}
	fclose(ulaz);
	
	return velicina;
	
}

int izbaci_skupe (struct Prodavnica *p, int np, struct Artikal *a, int na)
{
	
	int i=0, j=0;
	
	double suma=0, prosjek=0;
	
	for(i=0; i<na; i++)
	{
		suma+=a[i].cijena;
	}
	prosjek=(double)suma/na;
	
	int br_art=0, k=0;
	double prosjek_p;
	
	for(i=0; i<np; i++)
	{
		br_art=0;
		suma=0;
		prosjek_p=0;
		
		for(j=0; j<na; j++)
		{
			if(p[i].ID==a[j].prodavnica)
			{
				suma+=a[j].cijena;
				br_art++;
			}
		}
		prosjek_p=(double)suma/br_art;
		if(prosjek_p>prosjek)
		{
			for(k=i; k<np-1; k++)
			{
				p[k]=p[k+1];
			}
			np--;
			i--;
		}
	}
	
	return np;
	
}

int sacuvaj (struct Prodavnica *p, int n, const char *ime_datoteke)
{
	
	FILE* dat=fopen(ime_datoteke, "ab");
	if(dat==NULL) return 0;
	
	int zapisano=fwrite(p, sizeof(struct Prodavnica), n, dat);
	if(ferror(dat)) return 0;
	
	fclose(dat);
	return 1;
}


int main() {
	printf("ZSR 13, Zadatak 11");
	return 0;
}
