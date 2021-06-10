// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
int velike(char *s)
{
	
	while(*s!='\0')
	{
		if(*s==125)
		{
			return 0;
		}
		if(*s==123)
		{
			while(*s!=125)
			{
				s++;
				if(*s==123 || *s=='\0')
				{
					return 0;
				}
			}
			
		}
		
		s++;
	}
	

	return 1;

}

int srednje(char *p)
{
	
	while(*p!='\0')  //obican prolaz kroz string
	{	
		if(*p==93)
		{
			return 0;
		}
		if(*p==91) //naleti na prvu srednju 
		{
			
			while(*p!=93)
			{
				p++;
				if(*p==91 || *p==123 || *p==125 || *p=='\0')
				{
					return 0;
				}
				
			}
	
		}
		p++;
		
	}
	
	return 1;
	
	
	
}





int provjeri_zagrade(char *s)
{
	int srednje_zagrade=0, velike_zagrade=0;
	char *povratak=s;   //pokazivac na prvi clan stringa
	
	while(*s!='\0')   //obican prolaz kroz string
	{
		if(*s==41)		//ako naleti na ) prvo, vrati 0
		{
			return 0;
		}
		if(*s==40) //naleti na prvu malu zagradu (
		{
			s++;  //pomjeri se pokazivac za jedno mjesto kako ona ne bi sama sebe gledala
			while(*s!=41)  // sve dok ne naiđe na )
			{
				if(*s==91 || *s==40 || *s==93 || *s==123 || *s==125 || *s=='\0') //ako se bilo koja zagrada osim ) pojavi vrati 0
				{
					return 0;
				}
				
				s++;
			}

		}
		
		
		s++;
		
	}
	 //ako su male zagrade dobre
	srednje_zagrade=srednje(povratak);  //poziva se funkcija koja analogno malim provjerava srednje zagrade
	if(srednje_zagrade==0)  //funkcija ako vrati 0, srednje zagrade nisu dobre i glavna funkcija vrati 0
	{
		return 0;
	}
	
	if(srednje_zagrade==1) // ako funkcija za srednje vrati 1, onda se poziva funkcija koja provjerava velike zagrade
	{
		
		velike_zagrade=velike(povratak);
		
		if(velike_zagrade==0)   // ako su loše, vrati glavna funkcija 0
		{
			return 0;
		}
		
		else if(velike_zagrade==1) // ako su i one dobre, vrati glavna funkcija 1
		{
			return 1;
		}
		
		
		
		
	}
	
		return 1; // ovaj return zbog moguceg nepojavljivanja zagrada uopste u stringu, mora vratit 1 po uslovu zadatka
	
}



int main() {
	
	char test[1000]="nigga {we [made(it) dal]} je moguce (da) ovo radi";
	printf("%d", provjeri_zagrade(test));
	return 0;	
	
}

