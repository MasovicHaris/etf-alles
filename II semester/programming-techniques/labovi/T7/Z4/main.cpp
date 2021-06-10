/* 
    TP 16/17 (Tutorijal 7, Zadatak 4)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory>

int main ()
{
	// veliki  unique pametni
	// manji  shared pametni
	try{
		int broj_recenica;
		std::cout << "Koliko zelite recenica: ";
		std::cin >> broj_recenica;
		std::cin.ignore(10000, '\n'); // Zbog '\n' u spremniku!
		std::cout << "Unesite recenice: " << std::endl;
		std::unique_ptr<std::shared_ptr<std::string>[]> recenice(new std::shared_ptr<std::string> [broj_recenica]); 
		for(int i = 0; i < broj_recenica; i++) recenice[i] = nullptr;
		for(int i = 0; i < broj_recenica; i++) {
 					recenice[i] = std::make_shared<std::string>();
					std::getline(std::cin, *recenice[i]);
			
		}
		std::cout << "Sortirane recenice: " << std::endl;
		std::sort(recenice.get(), recenice.get() + broj_recenica, [](const std::shared_ptr<std::string> &a, const std::shared_ptr<std::string> &b) {
 			return *a.get() < *b.get();
		});
		
		for(int i = 0; i < broj_recenica; ++i) std::cout << *recenice[i] << std::endl;
		
	}catch(...){
		std::cout << "Problemi s memorijom!";
	}
	return 0;
}