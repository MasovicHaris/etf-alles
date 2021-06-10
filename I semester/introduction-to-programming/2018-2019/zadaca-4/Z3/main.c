// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int daj_sljedeci_broj(int br)
{
	
	static int a=0;  // statičke vrijednosti početnog intervala
	static int b=100;
	static int c=50;
	if(br!=0 && br!=1 && br!=-1) // ako se u mainu unese neko drugo slovo osim M V J
	{
		return c;  // vrati staru vrijednost c
	}
	if(br==0)
	{
	    return c;  // ako pogodimo to jest pošalje se J, funkcija "vrati C" al se ono ne ispiše već se u mainu ispiše "Pogodio sam!"
	}
	else if(br==1)  // ako se pošalje V, mora se mijenjat interval tako da se on suzi sa 0-100 na 50-100
	{
	    a=c;      // a postane 50 umjesto 0
	    c=(a+b)/2;   //  c=(50+100)/2 = 75 i to se vrati u main kao nova ponuda
	    return c;
	}
	
	else if(br==-1)
	{
	    b=c;    	//ako se pošalje M, mora se suzit interval sa 0-100 na 0-50
	    c=a+(b-a)/2;   // tako b postane 50 umjesto 100 -> c=0+(50-0)/2 = 25
	    return c;  // ponudi se 25
	    
	}
	
	else
	return 0;
	
}

int main()
{
    
    char slovo; //manje vece ili jednako
    int x=0;  //početna vrijednost za x koje se šalje u funkciju
    
    printf("Zamislite neki broj...");
    printf("\nDa li je taj broj %d? ", daj_sljedeci_broj(x)); // ispiše 50 jer je x=0 i 0 se pošalje u funkciju i ona vrati samo početno c;
   do
	 {
	    scanf(" %c", &slovo);
	    if(slovo=='M')
	    {
	    	x=-1;
	    	printf("Da li je taj broj %d? ", daj_sljedeci_broj(x));  //ako je broj manji, u funkciju se šalje -1 i to mijenja interval
	    	
	    }
	    
	    else if(slovo=='V')
	    {
	    	x=1;
	    	printf("Da li je taj broj %d? ", daj_sljedeci_broj(x));  // analogno za veće
	    }
	    else if(slovo=='J')
	    {
	    	printf("Pogodio sam!");
	    }
	    else
	    {
	    	printf("Pogresan unos, probajte ponovo.\n");//ako se unese neko drugo slovo potrebno je funkciji poslati neku vrijednost za koju ce ona vratiti samo stare vrijednosti iz prethodnog poziva
	    	x=3;                							//stavimo random x=3
	    	printf("Da li je taj broj %d? ", daj_sljedeci_broj(x)); // funkcija vrati staru vrijednost
	    }
    
      }while(slovo!='J'); // unos se izvrsava sve dok ne unesemo slovo J (jednako) i tad smo pogodili broj
    
    return 0;
}
