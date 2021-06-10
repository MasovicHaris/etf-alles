// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
int br_cifara(long long int x)
{
	int brojac=0;
	
	while(x!=0)
	{
		brojac++;
		x/=10;
	}
	return brojac;
}

char* dvostruko (char *s)
{
	char *povrat=s;
	int kraj, poc;
	
	while(*s!='\0')  // klasican prolaz kroz string
	{
		if(*s>48 && *s<=57)  // trazimo samo brojeve koji ne pocinju nulom
		{
			char *p=s;    //    pokazivac na prvu cifru tog broja
			char *k=s;		//  pokazivac na prvu cifru broja koji dodje do zadnje cifre broja
			
			long long int r=0;
			
			while(*k>=48 && *k<=57)
			{
				int x=*s-48;		// broj se pretvara iz ASCII u pravu vrijednost
				
				r=r*10+x;        // kako idemo desno kroz niz kupimo cifre i pravimo pravi broj od njih
				s++;
				k++;				// pokazivac dodje do zadnje cifre broja
			}
			poc=br_cifara(r);    //racuna se broj cifara broja
			r=2*r;				// broj se mnozi sa 2
			kraj=br_cifara(r);  // provjerava se broj cifara broja kad se pomnozi sa 2
			
			if(kraj-poc==0)    // ako je broj cifara ostao isti radi se sljedece:
			{
				while(r!=0 && k>=p )		// broj se dijeli pa ne smije bit 0, a i zadnji pokazivac mora doc do prve cifre broja
				{
					int c=48+(r%10);  // broj se konvertuje u ASCII
					r/=10;
					*(k-1)=c;    // kako k stane mjesto iza posljednje cifre pa moramo pisat k-1 bukvalno upisujemo s desna na lijevo pomnozen broj sa 2
					k--;
				}
			}
			
			else if(kraj-poc==1) // ako se string treba prosirit
			{
				char *pozadi=s;      // novi pokazivac
				while(*pozadi!='\0')  // ide petlja da se stavi pokazivac na kraj prvobitnog stringa
				{
					pozadi++; 
				}  // pozadi je vec na kraju stringa, odnosno na mjestu gdje je '\0'
				while(pozadi>=s)  //idemo s desna na lijevo do mjesta iza zadnje cifre broja
				{
					*(pozadi+1)=*pozadi;  // pomjeramo sve udesno za 1 jer je 1 maksimalno sirenje stringa ne mozemo dobit 4cifren broj kad mnozimo sa 2
					pozadi--;
				}
				while(k>=p && r!=0) // pokazivac koji pokazuje iza zadnje cifre broja pokazuje sad na spejs stvoren pomjeranjem stringa i ne treba nam k-1
				{						// jer na to mjesto tacno moramo upisat odmah tu cifru koja se dobije kad se tipa 99 pomnozi sa 2
					int c=(r%10)+48;
					r/=10;
					*k=c;					// to je to, ne treba nam k-1
					k--;
				}
				
			}
		}
		
		if(*s=='\0')
		{
			break;
		}
		
		s++;
		
		
	}
	return povrat;
}
int main() {
	
	char tekst[100000]="999999999999999";
	printf("'%s'", dvostruko(tekst));
	return 0;
	
	
	
}
	

