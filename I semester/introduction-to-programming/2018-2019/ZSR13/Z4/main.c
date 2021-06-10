// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <string.h>

struct Grad {
	char naziv[20];
	int br_stanovnika;
};

struct Drzava {
	char naziv[50];
	struct Grad glavni;
};

struct Regija {
	char naziv[50];
	struct Grad glavni;
};


int filtriraj(struct Drzava drzave[], int vel1, struct Regija regije[], int vel2)
{
	int i=0, j=0;
	int k=0;
	char slovo;
	
	for(i=0; i<vel1; i++)
	{
		for(j=0; j<vel2; j++)
		{
			slovo=drzave[i].naziv[0];
			if(strcmp(drzave[i].glavni.naziv, regije[j].glavni.naziv)==0 || slovo=='Z' || drzave[i].glavni.br_stanovnika<10000)
			{
				for(k=i; k<vel1-1; k++)
				{
					drzave[k]=drzave[k+1];
				}
				vel1--;
				k=-1;
				break;
			}
		}
		if(k==-1) {i--; k=-2;}
	}
	return vel1;
}

int ucitaj_drzave(struct Drzava drzave[], int vel)
{
	int velicina;
	FILE* dat=fopen("drzave.dat", "rb");
	velicina=fread(drzave, (int)(sizeof(struct Drzava)), vel, dat);
	fclose(dat);
	return velicina;
}

int ucitaj_regije(struct Regija regije[], int vel)
{
	int velicina=0, i=0;
	FILE* ulaz=fopen("regije.txt", "r");
	if(ulaz==NULL) return 0;
	char naziv_regije[50];
	char naziv_grada[20];
	int c=314, broj, j=0;
	while(c!=EOF)
	{
		i=-1;
		do {
			if(i<49) i++;
			c=fgetc(ulaz);
			if(c==',') break;
			naziv_regije[i]=c;
		}while(c != EOF);
			naziv_regije[i]='\0';
			
		i=-1;
		do{
			if(i<19) i++;
			c=fgetc(ulaz);
			if(c==',') break;
			naziv_grada[i]=c;
		}while(c!=EOF);
			naziv_grada[i]='\0';
		i=fscanf(ulaz,"%d", &broj);
		c=fgetc(ulaz);
		strcpy(regije[j].naziv, naziv_regije);
		strcpy(regije[j].glavni.naziv, naziv_grada);
		regije[j].glavni.br_stanovnika=broj;
		j++;
		velicina++;
		if(velicina>=vel) break;
	}
	fclose(ulaz);
	
	return velicina;
}
struct Grad max_glavni(struct Drzava drzave[], int vel)
{
	int max=drzave[0].glavni.br_stanovnika;
	int pozicija=0, i=0;
	for(i=0; i<vel; i++)
	{
		if(drzave[i].glavni.br_stanovnika>max) {max=drzave[i].glavni.br_stanovnika; pozicija=i;}
	}
	return drzave[pozicija].glavni;
}

void drzave_regije(struct Drzava drzave[], int vel1, struct Regija regije[], int vel2)
{
	struct Grad temp=max_glavni(drzave, vel1);
	int i=0;
	for(i=0; i<vel2; i++)
	{
		if(strcmp(temp.naziv, regije[i].glavni.naziv)==0)
		{
			printf("%s\n", regije[i].naziv);
		}
	}
}

void zapisi_regije(struct Regija regije[], int vel)
{
	FILE* izlaz=fopen("regije.txt", "w");
	if(izlaz==0) return;
	int i=0;
	for(i=0; i<vel; i++)
	{
		fprintf(izlaz, "%s,%s,%d\n", regije[i].naziv, regije[i].glavni.naziv, regije[i].glavni.br_stanovnika);
	}
	fclose(izlaz);
}

int main() 
{
	struct Drzava niz1[] = {
		{"Mozambik", { "Maputo", 9999}},
		{"Zimbabve", { "Harare", 345126}},
		{"Zambija", { "Lusaka", 10001}},
		{"Bosna i Hercegovina", { "Sarajevo", 507327}},
		{"Nauru", { "Yaren", 701}},
		{"Kanada", { "Otava", 883389}},
		{"Zelenortska republika", { "Praia", 114111}},
		{"Nigerija", { "Abuja", 900543}}
	};
	
	FILE* dat=fopen("drzave.dat", "wb");
	int zapisano=fwrite(niz1, sizeof(struct Drzava), 8, dat);
	fclose(dat);

}
