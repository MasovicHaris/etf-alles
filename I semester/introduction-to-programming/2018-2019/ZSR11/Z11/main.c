// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <string.h>
struct Student {
char ime[20], prezime[20];
int ocjene[50];
	int br_ocjena;
};

float daj_prosjek(struct Student p, int broj_ocjena)
{
	int suma=0;
	int i=0;
	if(broj_ocjena==0) return 5;
		for(i=0; i<broj_ocjena; i++)
	{
		suma=suma+p.ocjene[i];
		if(p.ocjene[i]==5) return 5;
	}
	return (double)suma/broj_ocjena;
}

int uporedi_ime(struct Student p, struct Student s)
{
	if(strcmp(p.prezime, s.prezime)==0)
	{
		return strcmp(p.ime, s.ime);
	}
	else return strcmp(p.prezime, s.prezime);
	
}
void printaj(struct Student p)
{
				printf("%s ", p.prezime);
				printf("%s", p.ime);
				printf("\n");
}

int genijalci(struct Student p[], int velicina, float prosjek)
{
	
	int i=0;
	int j=0;
	int indeks1=-1;
	int indeks2=-1;
	int indeks3=-1;
	int pom_velicina=0;
	float max_prosjek=0;
	for(i=0; i<velicina; i++)
	{
		if(daj_prosjek(p[i], p[i].br_ocjena)<prosjek)
		{
			for(j=i; j<velicina-1; j++)
			{
				p[j]=p[j+1];
			}
			velicina--;
			i--;
		}
	}
	if(velicina==0) return 0;
	else
	{
		max_prosjek=-1;
		if(velicina<3) pom_velicina=velicina;
		else if(velicina>=3) pom_velicina=3;
		
		for(i=0; i<pom_velicina; i++)
		{
			for(j=0; j<velicina; j++)
			{
				if(j==indeks1 || j==indeks2 || j==indeks3) continue;
				if(max_prosjek<=daj_prosjek(p[j], p[j].br_ocjena) && i==0) {max_prosjek=daj_prosjek(p[j], p[j].br_ocjena); indeks1=j;}
				if(max_prosjek<=daj_prosjek(p[j], p[j].br_ocjena) && i==1) {max_prosjek=daj_prosjek(p[j], p[j].br_ocjena); indeks2=j;}
				if(max_prosjek<=daj_prosjek(p[j], p[j].br_ocjena) && i==2) {max_prosjek=daj_prosjek(p[j], p[j].br_ocjena); indeks3=j;}
			}
			max_prosjek=-1;
		}
		if(velicina==1)
		{
			printaj(p[0]);
		}
		else if(velicina==2)
		{
			if(daj_prosjek(p[indeks1], p[indeks1].br_ocjena)==daj_prosjek(p[indeks2], p[indeks2].br_ocjena))
			{
				if(uporedi_ime(p[indeks1], p[indeks2])<=0)
				{
					printaj(p[indeks1]);
					printaj(p[indeks2]);
				}
				else
				{
					printaj(p[indeks2]);
					printaj(p[indeks1]);
				}
			}
			else
			{
			printaj(p[indeks1]); printaj(p[indeks2]);
			}
		}
		else if(velicina>=3)
		{
			if(daj_prosjek(p[indeks1], p[indeks1].br_ocjena)==daj_prosjek(p[indeks2], p[indeks2].br_ocjena) && daj_prosjek(p[indeks2], p[indeks2].br_ocjena)==daj_prosjek(p[indeks3], p[indeks3].br_ocjena))
			{
				if(uporedi_ime(p[indeks1], p[indeks2])<=0 && uporedi_ime(p[indeks1], p[indeks3])<=0)
				{
					printaj(p[indeks1]);
					
					if(uporedi_ime(p[indeks2], p[indeks3])<=0)
					{
						printaj(p[indeks2]);
						printaj(p[indeks3]);
					}
					else
					{
						printaj(p[indeks3]);
						printaj(p[indeks2]);
					}
				}
			}
			else if(daj_prosjek(p[indeks1], p[indeks1].br_ocjena)==daj_prosjek(p[indeks2], p[indeks2].br_ocjena) && daj_prosjek(p[indeks1], p[indeks1].br_ocjena)!=daj_prosjek(p[indeks3], p[indeks3].br_ocjena))
			{
				if(uporedi_ime(p[indeks1], p[indeks2])<=0)
				{
					printaj(p[indeks1]);
					printaj(p[indeks2]);
					printaj(p[indeks3]);
				}
				else
				{
					printaj(p[indeks2]);
					printaj(p[indeks1]);
					printaj(p[indeks3]);
				}
			}
				else if(daj_prosjek(p[indeks2], p[indeks2].br_ocjena)==daj_prosjek(p[indeks3], p[indeks3].br_ocjena) && daj_prosjek(p[indeks2], p[indeks2].br_ocjena)!=daj_prosjek(p[indeks1], p[indeks1].br_ocjena))
			{
				if(uporedi_ime(p[indeks2], p[indeks3])<=0)
				{
					printaj(p[indeks1]);
					printaj(p[indeks2]);
					printaj(p[indeks3]);
				}
				else
				{
					printaj(p[indeks1]);
					printaj(p[indeks3]);
					printaj(p[indeks2]);
				}
			}
			else
			{
					printaj(p[indeks1]);
					printaj(p[indeks2]);
					printaj(p[indeks3]);
			}
		}
	}
	return velicina;
}

int main() 
{
	/* AT7: Test izbacivanja + samo dva studenta ispunjavaju uslov */
struct Student studenti[3] = {
	{ "Beba", "Bebic", { 6,6,6,6,6}, 5},
	{ "Mujo", "Mujic", { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8}, 29}, 
	{ "Fata", "Fatic", { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8}, 29}, 
};
genijalci(studenti, 3, 7.0);
	return 0;
}
