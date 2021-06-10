// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
	double cz=1200, cs=15, cn=70, porastz=0, porasts=0, porastn=0, nasum, novac=100000;
	int unos=3, petlja, izbor, kolicina, kolzlata=0, kolsrebra=0, kolnafte=0;
	srand(0);
	while(unos==3)
	{
		unos=0;
		petlja=0;
		while(petlja<5)
		{
			
			nasum=(rand()%2)/10.00;
			if(nasum==0)
			{
				porastz=porastz-0.1;
				cz=(cz*(100+porastz))/100;
			}
			else if(nasum!=0)
			{
				porastz=porastz+0.1;
				cz=(cz*(100+porastz))/100;
			}
			
			nasum=(rand()%2)/10.00;
			if(nasum==0)
			{
				porasts=porasts-0.1;
				cs=(cs*(100+porasts))/100;
			}
			else if(nasum!=0)
			{
				porasts=porasts+0.1;
				cs=(cs*(100+porasts))/100;
				
			}
			
				nasum=(rand()%2)/10.00;
				if(nasum==0)
				{
					porastn=porastn-0.1;
					cn=(cn*(100+porastn))/100;
				}
				else if(nasum!=0)
				{
					porastn=porastn+0.1;
					cn=(cn*(100+porastn))/100;
					
				}
			
			
			if(petlja==0)
			{
				printf("PON: Zlato $%.2f",cz);
				if((fabs(porastz)<0.00000001) || porastz>0)
				printf(" (+%.1f) Srebro $%.2f", fabs(porastz), cs);
				else
				printf(" (-%.1f) Srebro $%.2f", fabs(porastz), cs);
				if(porasts>0 || fabs(porasts)<0.00000001)
				printf(" (+%.1f) Nafta $%.2f", fabs(porasts), cn);
				else
				printf(" (-%.1f) Nafta $%.2f", fabs(porasts), cn);
				if(porastn>0 || fabs(porastn)<0.00000001)
				printf(" (+%.1f)\n", fabs(porastn));
				else
				printf(" (-%.1f)\n", fabs(porastn));
				
				
			}

			
			if(petlja==1)
			{
			printf("UTO: Zlato $%.2f", cz);
			if((fabs(porastz)<0.00000001) || porastz>0)
			printf(" (+%.1f) Srebro $%.2f", fabs(porastz), cs);
			else
			printf(" (-%.1f) Srebro $%.2f", fabs(porastz), cs);
			if(porasts>0 || fabs(porasts)<0.00000001)
			printf(" (+%.1f) Nafta $%.2f", fabs(porasts), cn);
			else
			printf(" (-%.1f) Nafta $%.2f", fabs(porasts), cn);
			if(porastn>0 || fabs(porastn)<0.00000001)
			printf(" (+%.1f)\n", fabs(porastn));
			else
			printf(" (-%.1f)\n", fabs(porastn));
		
			
			}
			
			if(petlja==2)
			{
				printf("SRI: Zlato $%.2f", cz);
				if((fabs(porastz)<0.00000001) || porastz>0)
				printf(" (+%.1f) Srebro $%.2f", fabs(porastz), cs);
				else
				printf(" (-%.1f) Srebro $%.2f", fabs(porastz), cs);
				if(porasts>0 || fabs(porasts)<0.00000001)
				printf(" (+%.1f) Nafta $%.2f", fabs(porasts), cn);
				else
				printf(" (-%.1f) Nafta $%.2f", fabs(porasts), cn);
				if(porastn>0 || fabs(porastn)<0.00000001)
				printf(" (+%.1f)\n", fabs(porastn));
				else
				printf(" (-%.1f)\n", fabs(porastn));
			
			}
		
			if(petlja==3)
			{
					printf("CET: Zlato $%.2f", cz);
					if((fabs(porastz)<0.00000001) || porastz>0)
					printf(" (+%.1f) Srebro $%.2f", fabs(porastz), cs);
					else
					printf(" (-%.1f) Srebro $%.2f", fabs(porastz), cs);
					if(porasts>0 || fabs(porasts)<0.00000001)
					printf(" (+%.1f) Nafta $%.2f", fabs(porasts), cn);
					else
					printf(" (-%.1f) Nafta $%.2f", fabs(porasts), cn);
					if(porastn>0 || fabs(porastn)<0.00000001)
					printf(" (+%.1f)\n", fabs(porastn));
					else
					printf(" (-%.1f)\n", fabs(porastn));
				
			}
	
			if(petlja==4)
			{
				printf("PET: Zlato $%.2f", cz);
				if((fabs(porastz)<0.00000001) || porastz>0)
				printf(" (+%.1f) Srebro $%.2f", fabs(porastz), cs);
				else
				printf(" (-%.1f) Srebro $%.2f", fabs(porastz), cs);
				if(porasts>0 || fabs(porasts)<0.00000001)
				printf(" (+%.1f) Nafta $%.2f", fabs(porasts), cn);
				else
				printf(" (-%.1f) Nafta $%.2f", fabs(porasts), cn);
				if(porastn>0 || fabs(porastn)<0.00000001)
				printf(" (+%.1f)\n", fabs(porastn));
				else
				printf(" (-%.1f)\n", fabs(porastn));
			
			}
			petlja++;
		}
		
		printf("\n");
		printf("\nImate:\nZlata: %d ($%.2f) Srebra: %d ($%.2f) Nafte: %d ($%.2f) Novca: $%.2f\n",kolzlata, kolzlata*cz, kolsrebra, cs*kolsrebra, kolnafte, cn*kolnafte, novac);
		printf("UKUPNO: $%.2f", novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte);
		if((novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte)-100000<0)
printf(" ($-%.2f)\n",fabs(novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte-100000));
		else
printf(" ($+%.2f)\n", fabs(novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte-100000));
printf("\n");



while(unos!=3)
{
	
	printf("\nUnesite izbor (1 - Kupi, 2 - Prodaj, 3 - Sljedeca sedmica, 0 - Kraj igre): ");
	scanf("%d", &unos);
	if(unos==3)
	printf("\n");
	if(unos==1)
	{
		printf("Sta kupujete (1 - Zlato, 2 - Srebro, 3 - Naftu): ");
		scanf("%d", &izbor);
		if(izbor==1)
		{
		printf("Koliko? ");
		scanf("%d", &kolicina);
		if(novac-cz*kolicina<0)
		{
		printf("Nemate toliko novca!\n");
		}
		else if(novac-cz*kolicina>=0)
		{
			novac=novac-(cz*kolicina);
			kolzlata=kolzlata+kolicina;
		
		}
		}
		
		if(izbor==2)
		{
		printf("Koliko? ");
		scanf("%d", &kolicina);
		if(novac-cs*kolicina<0)
		{
		printf("Nemate toliko novca!\n");
		}
		else if(novac-cs*kolicina>=0)
		{
			novac=novac-(cs*kolicina);
			kolsrebra=kolsrebra+kolicina;
		
		}
		}
		
		if(izbor==3)
		{
		printf("Koliko? ");
		scanf("%d", &kolicina);
		if(novac-cn*kolicina<0)
		{
		printf("Nemate toliko novca!\n");
		}
		else if(novac-cn*kolicina>=0)
		{
			novac=novac-(cn*kolicina);
			kolnafte=kolnafte+kolicina;
		
		
			
		}
		}
		else if(izbor<1 || izbor>3)
		printf("Pogresan izbor!");
		
		}
		
		else if(unos==2)
		{
			printf("Sta prodajete (1 - Zlato, 2 - Srebro, 3 - Naftu): ");
			scanf("%d", &izbor);
			if(izbor==1)
			{
			printf("Koliko? ");
			scanf("%d", &kolicina);
			if(kolzlata<kolicina)
			printf("Nemate toliko zlata!\n");
			else if(kolzlata>=kolicina)
			{
					
				novac=novac+(cz*kolzlata);
				kolzlata=kolzlata-kolicina;
				
				
			}
			}
			
			if(izbor==2)
			{
				printf("Koliko? ");	
				scanf("%d", &kolicina);
				if(kolsrebra<kolicina)
				
				printf("Nemate toliko srebra!\n");
				else if(kolsrebra>=kolicina)
				{
				novac=novac+(cs*kolsrebra);
					kolsrebra=kolsrebra-kolicina;
					
				}
			}
			
			if(izbor==3)
			{
				printf("Koliko? ");
				scanf("%d", &kolicina);
				if(kolnafte<kolicina)
				printf("Nemate toliko nafte!\n");
				else if(kolnafte>=kolicina)
				{
					
					novac=novac+(cn*kolnafte);
					kolnafte=kolnafte-kolicina;
				
					
						
				}
			}
			
			
			
		}
		
		else if(unos==0)
		{
			return 0;
		}
		
		else
		{
			if(unos!=3)
			{
				printf("Pogresan izbor!\n");
				unos=0;
			}
		}
		
		if(unos!=3)
		{
		
			printf("\nImate:\nZlata: %d ($%.2f) Srebra: %d ($%.2f) Nafte: %d ($%.2f) Novca: $%.2f", kolzlata, cz*kolzlata, kolsrebra, cs*kolsrebra, kolnafte, cn*kolnafte, novac);
		printf("\nUKUPNO: $%.2f", novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte);	
			if((novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte-100000)<0)
			printf(" ($-%.2f)\n", fabs(novac+cz*kolzlata+cs*kolsrebra+cn*kolnafte-100000));
			else
			printf(" ($+%.2f)\n", fabs(cz*kolzlata+cs*kolsrebra+cn*kolnafte+novac-100000));
			
			
		}
		
		if(unos!=3)
		unos=0;
		
		
		
	}
		
		
		
	}
	return 0;
	
}

		
		
	