#include <stdio.h>
#include <math.h>

/*Napišite funkciju "obrnut" koja vraća primljeni pozitivan cijeli broj okrenut naopako.
Npr. ako se funkcija pozove sa vrijednošću 12345 (dvanaest hiljada tristo četrdeset i pet), treba vratiti broj 54321 (pedeset četiri hiljade tristo dvadeset i jedan).
Pri tome nije dozvoljeno koristiti nizove niti raditi bilo kakav ispis u funkciji! Napravite i kraći program koji testira tu funkciju */

int obrnut(int broj){
	int zadnja;
	int obrnutbroj=0;
	int k=0;
	while(broj!=0){
		
		zadnja=broj%10;
		
		obrnutbroj*=10;
		
		obrnutbroj+=zadnja;
		
		
		
		
		k++;
		broj/=10;
	}
	return obrnutbroj;
}

int main() {
	return 0;
}
