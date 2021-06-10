/* 
    TP 16/17 (Tutorijal 7, Zadatak 2)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
int main ()
{
	try{
		int broj_recenica;
		std::cout << "Koliko zelite recenica: ";
		std::cin >> broj_recenica;
		std::cin.ignore(10000, '\n'); // Zbog '\n' u spremniku!
		char **recenice = nullptr;
		std::cout << "Unesite recenice: " << std::endl;
		recenice = new char *[broj_recenica]; // kreira odma nullptr
		for(int i = 0; i < broj_recenica; i++) recenice[i] = nullptr;
		for(int i = 0; i < broj_recenica; i++) {
 					char radni_prostor[1000];
 					std::cin.getline(radni_prostor, 1000);
 					recenice[i] = new char[strlen(radni_prostor) + 1];
 					strcpy(recenice[i], radni_prostor);
		}
		std::cout << "Sortirane recenice: " << std::endl;
		std::sort(recenice, recenice + broj_recenica, [](const char *a, const char *b) {
 			return strcmp(a, b) <= 0;
		});
		
		for(int i = 0; i < broj_recenica; ++i) std::cout << recenice[i] << std::endl;

		
		for(int i = 0; i < broj_recenica; i++) delete[] recenice[i];
		for(int i = 0; i < broj_recenica; i++) recenice[i] = nullptr;
		delete[] recenice;
		recenice = nullptr;
		
	}catch(...){
		std::cout << "Problemi s memorijom!";
	}
	return 0;
}