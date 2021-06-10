/*
    TP 2016/2017 (Tutorijal 5, Zadatak 3)

	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.

	NAPOMENA: autotestovi ce biti konacni TEK pred pocetak tutorijala,
	          odnosno mogu se do tada mijenjati, pa su studenti u toku
			  tutorijala duzni da ponovo testiraju SVE zadatke!

	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.

			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>


void Unesi(int &x)
{
	std::cin >> x;
}

bool funkcion(int &x)
{
	if(std::sqrt(x) == round(std::sqrt(x))) return true;
	return false;
} 

bool boolovska1(int &x, int &y)
{
	int a(x), b(y);
	if(a<0) a*=-1;
	if(b<0) b*=-1;

	int brojac1=0, brojac2=0;
	brojac1 = std::log(a)/log(10) + 1 + 10e-10;
	brojac2 = std::log(b)/log(10) + 1 + 10e-10;
	return brojac1 < brojac2;
}

bool boolovska2(int &y)
{
	long long x = y;
	if(x<0) x*=-1;
	int brojac=0;
	if(x!=0){
	brojac = std::log(x)/log(10) + 1 + 10e-10;
	}
	
	if(brojac == 3) return true;
	return false;
}

int main ()
{
	int niz[1000];
	int *pok1 = niz;
	int broj_el;
	int niz2[1000];
	int *pok2 = niz2;

	std::cout << "Unesite broj elemenata (max. 1000): ";
	std::cin >> broj_el;
	std::cout << "Unesite elemente: ";
	std::for_each(pok1, pok1 + broj_el, Unesi);
	niz[broj_el] = '\0'; // ne nužno

	std::cout << "Najveci element niza je " << *(std::max_element(pok1, pok1 + broj_el)) << std::endl;

	int v = *(std::min_element(pok1, pok1 + broj_el));

	std::cout << "Najmanji element niza se pojavljuje " << std::count(pok1, pok1 + broj_el, v) << " puta u nizu" << std::endl;
	std::cout << "U nizu ima " << std::count_if(pok1, pok1 + broj_el, funkcion) << " brojeva koji su potpuni kvadrati" << std::endl;
	std::cout << "Prvi element sa najmanjim brojem cifara je " << *std::min_element(pok1, pok1 + broj_el, boolovska1) << std::endl;

	std::cout << "Elementi koji nisu trocifreni su: ";
	int *pokn = std::remove_copy_if(pok1, pok1+broj_el, pok2, boolovska2);
	std::for_each(pok2, pokn, [] (int n) {
		std::cout << n << ' ';
	});
	return 0;
}