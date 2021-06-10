/*
    TP 16/17 (Tutorijal 6, Zadatak 2)

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <vector>

template <typename tip>
auto KreirajIzvrnutiNiz(tip it1, tip it2) -> typename std::remove_reference<decltype(*it1)>::type *
{

	int brojac=0;
	tip it3 = it1;
	while(it3!=it2){
		brojac++;
		it3++;
	}
	typename std::remove_reference<decltype(*it1)>::type *p = nullptr;
	try {
		p = new typename std::remove_reference<decltype(*it1)>::type [brojac];
	} catch(...) {
		delete []p;
		throw std::bad_alloc();
	}

	int k=0;
	tip novi = it1;
	while(novi != it2) {
		p[brojac -k-1] = *novi;
		k++;
		novi++;
	}

	return p;
}

int main ()
{
	try {
		std::vector <double> vektor;
		unsigned int broj;
		double element;
		std::cout << "Koliko zelite elemenata: ";
		std::cin >> broj;
		vektor.resize(broj);
		std::cout << "Unesite elemente: ";
		for(int i=0; i < broj; ++i) {
			std::cin >> element;
			vektor[i] = element;
		}
		std::cout << "Kreirani niz: ";

		auto magic = KreirajIzvrnutiNiz(vektor.begin(), vektor.end());

		for(int i=0; i < broj; i++) std::cout << magic[i] << " ";
		delete []magic;
	} catch(...) {
		std::cout << "Nedovoljno memorije!";
	}
	return 0;
}