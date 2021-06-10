/*
    TP 2016/2017 (Tutorijal 5, Zadatak 4)

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
#include <deque>
#include <algorithm>
#include <cmath>

int main ()
{

	unsigned int broj_el;
	std::cout << "Unesite broj elemenata: ";
	std::cin >> broj_el;
	std::deque<int> niz(broj_el);
	std::deque<int> odredisni(broj_el);

	std::deque<int>::iterator pok0;
	pok0 = odredisni.begin();

	std::deque<int>::iterator pok1;
	pok1 = niz.begin();
	std::cout << "Unesite elemente: ";
	std::for_each(pok1, pok1+broj_el, [](int &x) {
		std::cin >> x;
	});

	std::cout << "Najveci element deka je " << *(std::max_element(pok1, pok1 + broj_el)) << std::endl;
	int v = *(std::min_element(pok1, pok1 + broj_el));
	std::cout << "Najmanji element deka se pojavljuje " << std::count(pok1, pok1 + broj_el, v) << " puta u deku" << std::endl;
	std::cout << "U deku ima " << std::count_if(pok1, pok1 + broj_el, [](int &x) -> bool {
		if(std::sqrt(x) == round(std::sqrt(x))) return true;
		return false;
	}) << " brojeva koji su potpuni kvadrati" << std::endl;

	std::cout << "Prvi element sa najmanjim brojem cifara je " << *std::min_element(pok1, pok1 + broj_el, [](int &x, int &y) -> bool {

		int a(x), b(y);
		if(a<0) a*=-1;
		if(b<0) b*=-1;

		int brojac1=0, brojac2=0;
		brojac1 = std::log(a)/log(10) + 1 + 10e-10;
		brojac2 = std::log(b)/log(10) + 1 + 10e-10;
		return brojac1 < brojac2;
	}) << std::endl;

	std::cout << "Elementi koji nisu trocifreni su: ";
	std::deque<int>::iterator pokn = std::remove_copy_if(pok1, pok1+broj_el, pok0, [](int &y) -> bool {

		long long x = y;
		if(x<0) x*=-1;
		int brojac=0;
		if(x!=0) {
			brojac = std::log(x)/log(10) + 1 + 10e-10;
		}

		if(brojac == 3) return true;
		return false;
	});

	std::for_each(pok0, pokn, [] (int n) {
		std::cout << n << ' ';
	});
	return 0;
}