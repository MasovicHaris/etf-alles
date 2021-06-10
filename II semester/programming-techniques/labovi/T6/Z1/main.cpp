/*
    TP 16/17 (Tutorijal 6, Zadatak 1)

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <stdexcept>
#include <limits>

template <typename tip>
tip *GenerirajStepeneDvojke(int n)
{
	if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
	tip maxi = std::numeric_limits<tip>::max();
	tip *p = nullptr;
	try {
		p = new tip[n];
	} catch(...) {
		delete []p;
		throw std::runtime_error("Alokacija nije uspijela");
	} 
 
	tip pogon = 1;
	long long i;
	for(i=0; i < n ; ++i) {
		p[i] = pogon;
		if(pogon > maxi/2) {
			i++;
			break;
		}
		pogon *=2;
	}
	if(i!=n) {
		delete []p;
		throw std::overflow_error("Prekoracen dozvoljeni opseg");
	}
	return p;
}

int main()
{
	unsigned long long broj;
	std::cout << "Koliko zelite elemenata: ";
	std::cin >> broj;
	unsigned long long *temp = nullptr;
	try {
		temp = GenerirajStepeneDvojke<unsigned long long>(broj);
		auto i=broj;
		for(i=0; i< broj; i++) {
			std::cout << temp[i] << " ";
		}
		delete []temp;
	} catch(std::domain_error exec) {
		std::cout << "Izuzetak: " << exec.what() << std::endl;
	} catch(std::runtime_error exec) {
		std::cout << "Izuzetak: " << exec.what() << std::endl;
	} catch(std::overflow_error exec) {
		std::cout << "Izuzetak: " << exec.what() << std::endl;
	}
	return 0;
}