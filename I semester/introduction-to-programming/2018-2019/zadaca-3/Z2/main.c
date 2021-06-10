// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>

char *zamijeni_min_max(char *s)
{
	char *prebrojavanje=s;  // pokazivac koji sluzi da prebroji broj karaktera u poslanom stringu
	int vel=0;				// brojac za te iste karaktere
	char *povrat = s;   // brojac na pocetak stringa
	int duzina1 = 0;		// duzina najduze rijeci
	int duzina2 = 0;		// duzina najkrace rijeci
	char *pocetak = s;		// pocetak rijeci
	char *kraj = s; 		// kraj krijeci
	char *kraj2 = s;        // kraj najkrace rijeci
	char *kraj1 = s;		// kraj najduze rijeci
	char *pocetak1 = s; 	//pocetak najduze rijeci
	char *pocetak2 = s;     //pocetak najkrace rijeci
	
	while(*prebrojavanje!='\0') // petlja za brojanje koliko karaktera ima pocetni string
	{
		vel++;
		prebrojavanje++;
	}
	vel=vel+1;  			//vel + 1 zbog '\0' karaktera
	
	
	while(*s != '\0')		//obicna petlja koja prolazi kroz string
	{
		if(!(*s==' ' || *s=='\0' || *s=='.' || *s==',' || *s=='!' || *s=='?' || *s==';')) // ako naleti na nesto osim znakova nabrojanih
		{
			pocetak = s;																	// stavlja pokazivac na mjesto tog slova/znaka, i to je pocetak rijeci
			while(!(*s==' ' || *s=='\0' || *s=='.' || *s==',' || *s=='!' || *s=='?' || *s==';'))  // od pocetaka rijeci ide do kraja te rijeci
			{
				kraj=s;							//stavi se pokazivac na kraj
				s++;
			}
			if(duzina1 < (kraj-pocetak+1))			//duzina te rijeci ako je veca od 0, a mora biti
			{
				pocetak1=pocetak;					//pocetak najduze rijeci se stavi na pocetno slovo te rijeci
				kraj1=kraj;							//analogno i kraj
				duzina1= (kraj-pocetak+1);			//duzina te rijeci postaje kao novi maximum
			}
		}
		if(*s=='\0')			//zbog upadanja u neinicijalizovano
		{
			break;
		}
		
		s++;
	}						// ovaj blok koda će naći najdužu riječ u stringu, i imat ćemo pokazivace na njenom pocetku i kraju
	
	duzina2 = duzina1;			//duzinu najkrace rijeci stavimo kao duzinu najduzu rijec u tom stringu
	
	s = povrat;				// s se vrati opet na pocetak stringa
	
	while(*s != '\0'){
		if(!(*s==' ' || *s=='\0' || *s=='.' || *s==',' || *s=='!' || *s=='?' || *s==';'))
		{
			pocetak=s;
			while(!(*s==' ' || *s=='\0' || *s=='.' || *s==',' || *s=='!' || *s=='?' || *s==';'))			//petlja slicna prethodnoj
			{
				kraj = s;
				s++;
			}
		}
		if(duzina2 > (kraj-pocetak+1))				//prvu manju rijec od najvece stavlja kao najkracu 
		{
			pocetak2 = pocetak;
			kraj2=kraj;
			duzina2= (kraj - pocetak +1);				// duzina2 postaje trenutno ta najkraca rijec dok se ne nađe manja od nje
		}
		if(*s=='\0')
		{
			break;
		}
		s++;
	}
	
	s=povrat;				// s se vrati na početak
	
	
	if(duzina1 == duzina2)   //ako se duzina najkrace i najduze rijeci poklapaju, vrati prvobitni string
	return povrat;
	
	// ALGORITAM ZAMJENE ODNOSNO SLAGANJA NOVOG STRINGA//
	
	char *novistring;						//deklarišemo novi string
	novistring=malloc(vel*sizeof(char));		//njegova veličina je ista kao i veličina početnog stringa
	
	char *p1=pocetak1;				// stavljamo tempove na mjesta pocetaka i krajeva najduze i najkrace rijeci
	char *p2=pocetak2;
	char *k1=kraj1;
	char *k2=kraj2;
	int i=0;						//sa i prolazimo kroz novoformirani string
	
	
	while(*s != '\0')		//klasicna petlja
	{
		if(s==pocetak2)		//ako s naleti na pocetak najkrace rijeci
		{
			while(p1<=k1)
			{
				novistring[i]=*p1;  //u novi string se upisuje na to mjesto, najduza rijec stringa
				p1++;
				i++;
			}
			s=k2+1;  // se se stavi na kraj najmanje rijeci na koju je naletio, i krece dalje kroz prvobitni string (da preskocimo najmanju rijec)
			continue;			//continue da se ne bi nista poslje ovog izvrsilo
		}
		
		if(s==pocetak1)							//ako s naleti na pocetak najduze rijeci
		{
			while(p2<=k2)
			{
				novistring[i]=*p2;					//u novi string se upisuje na to mjesto, najkraca rijec stringa
				p2++;
				i++;
			}
			s=k1+1;							// s se postavi na kraj najduze rijeci i moze da krene dalje kroz string
			continue;					//continue iz istog razloga
		}
		
		else
		{
			novistring[i]=*s;			//a ako ne naleti na te neke specificne pokazivace, string se kopira redom (1 na 1 kopiranje)
			s++;
			i++;
		}
	}
	
	novistring[i]='\0';			//postavimo terminator na kraj novog stringa
	char *temp=povrat;				//stavimo temp na mjesto pocetka prvobitnog stringa, pokazivac na pokazivac
	i=0;
	
	while(novistring[i]!='\0')		//ovom petljom se prepisuje novoformirani dobro poredani string u stari prvobitni string
	{
		*povrat=novistring[i];
		povrat++;
		i++;
		
	}
	
	*povrat='\0';  // terminator karakter
	
	free(novistring);  //oslobodi se novoformirani string radi curenja
	
	return temp;     //i vrati se temp kao pokazivac na pocetak starog stringa koji je sad izmjenjen onako kako uslov zadatka trazi
	
}

int main()
{
	
	
	char recenica[] = "Huso ima najduzi";
	printf ("'%s'\n", zamijeni_min_max(recenica));
	return 0;
	
	
}