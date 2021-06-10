/* 
    TP 16/17 (Tutorijal 7, Zadatak 3)
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
int main ()
{
	try{
		int broj_recenica;
		std::cout << "Koliko zelite recenica: ";
		std::cin >> broj_recenica;
		std::cin.ignore(10000, '\n'); // Zbog '\n' u spremniku!
		std::string **recenice = nullptr;
		std::cout << "Unesite recenice: " << std::endl;
		recenice = new std::string *[broj_recenica]; // kreira odma nullptr
		for(int i = 0; i < broj_recenica; i++) recenice[i] = nullptr;
		for(int i = 0; i < broj_recenica; i++) {
 					recenice[i] = new std::string();
					std::getline(std::cin, *recenice[i]);
			
		}
		std::cout << "Sortirane recenice: " << std::endl;
		std::sort(recenice, recenice + broj_recenica, [](const std::string *a, const std::string *b) {
 			return *a < *b;
		});
		
		for(int i = 0; i < broj_recenica; ++i) std::cout << *recenice[i] << std::endl;

		
		for(int i = 0; i < broj_recenica; i++) delete recenice[i];
		for(int i = 0; i < broj_recenica; i++) recenice[i] = nullptr;
		delete[] recenice;
		recenice = nullptr;
		
	}catch(...){
		std::cout << "Problemi s memorijom!";
	}
	return 0;
}