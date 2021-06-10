/*
    TP 2016/2017 (Tutorijal 5, Zadatak 6)

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
#include <vector>
#include <algorithm>

int pomocna(long long broj, int &suma)
{  
	if(broj ==0) return suma;
	else {
		suma += broj%10;
		return pomocna(broj/10, suma);
	}
}

int suma(long long broj)
{
	int suma(0);
	return pomocna(broj, suma);
}

bool testiraj(long long h, long long p)
{
	long long x(h);
	long long y(p);

	if(x<0) x*=-1;
	if(y<0) y*=-1;

	int suma1(0);
	suma1 = suma(x);
	int suma2(0);
	suma2 = suma(y);

	if( suma1 == suma2 && h<p) return true;
	else if(suma1 != suma2 ) return suma1 < suma2;
	else return false;
}

int main ()
{
	int broj;
	int trazeni;
	std::cout << "Unesite broj elemenata: ";
	std::cin >> broj;
	std::cout << "Unesite elemente: ";

	std::vector <long long> niz(broj);
	std::vector <long long>:: iterator pok;
	pok = niz.begin();
	std::for_each(pok, pok+broj, [](long long &x) {
		std::cin >> x;
	});

	std::cout << "Niz sortiran po sumi cifara glasi: ";
	std::sort(pok, pok+broj, testiraj);

	std::for_each(pok, pok+broj, [](long long &x) {
		std::cout << x << " ";
	});
	std::cout << std::endl << "Unesite broj koji trazite: ";
	std::cin >> trazeni;

	if(std::binary_search(pok, pok+broj, trazeni, testiraj)) {
		std::cout << "Trazeni broj nalazi se na poziciji " << std::lower_bound(pok, pok + broj, trazeni, testiraj) - niz.begin();
	} else std::cout << "Trazeni broj ne nalazi se u nizu!";
	return 0;
}