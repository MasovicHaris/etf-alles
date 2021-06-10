/* 
    TP 2016/2017 (Tutorijal 5, Zadatak 2)
	
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
#include <deque>

template <typename prviTip, typename drugiTp>
drugiTp RazmijeniBlokove(prviTip pocetak_bloka, prviTip kraj_bloka, drugiTp kraj_bloka_novog){
	 
	while(pocetak_bloka != kraj_bloka){
		auto pomocni = *pocetak_bloka;
		*pocetak_bloka = *kraj_bloka_novog; 
		*kraj_bloka_novog = pomocni;
		
		pocetak_bloka++;
		kraj_bloka_novog++;
	}
	
	return kraj_bloka_novog;
}

int main ()
{	
	std::vector<int> a{1,2,3,4,5};
	std::vector<int> b{6,7,8,9,10};
	 
	RazmijeniBlokove(a.begin(), a.end(), b.begin());
	std::cout << "a: ";
	for(auto &x : a) std::cout << x << " ";
	std::cout << std::endl << "b: ";
	for(auto &x : b) std::cout << x << " ";
	std::cout << std::endl;	
	return 0;
}