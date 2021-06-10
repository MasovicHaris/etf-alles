/*
    TP 2016/2017 (Tutorijal 5, Zadatak 7)

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
#include <stdexcept>

template <typename tip>
auto SumaBloka(tip it1, tip it2) -> decltype(*it1 + *it2)
{
	if(it1 == it2) throw std::range_error("Blok je prazan");
	auto suma = *it1++;
	while(it1 != it2) {
		suma += *it1;
		it1++;
	}
	return suma;
}
int main ()
{
	try {
		std::deque<double> d {1,2,3,4,5,6,7,8,9};
		std::cout<<"Suma bloka je: " << SumaBloka(d.begin(), d.end());
	} catch(std::range_error izuzetak) {
		std::cout << izuzetak.what() << std::endl;
	}
	return 0;
}