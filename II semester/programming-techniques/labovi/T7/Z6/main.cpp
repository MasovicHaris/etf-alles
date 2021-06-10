/* 
    TP 16/17 (Tutorijal 7, Zadatak 6)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <list>
template <typename tipliste>
std::list<tipliste> SortirajListu(std::list<tipliste> &stara){ // autotestovi nisu po postavci.. 
	for(auto i = stara.begin(); i != stara.end(); i++){
		for(auto j = i; j != stara.end(); j++){
			if(*i > *j) {
			
				auto temp = *i;
				*i = *j;
				*j = temp;
				
			}
		}
	}
	return stara;
} 



int main ()
{
	int broj;
	int element;
	std::cout << "Koliko ima elemenata: ";
	std::cin >> broj;
	std::cout << "Unesite elemente: ";
	std::list<int> lista;
	for(int i=0; i < broj; i++){
		std::cin >> element;
		lista.push_back(element);
	}
	
	std::list<int> nova;
	nova = SortirajListu(lista);
	std::cout << "Sortirana lista: ";
	for(auto x : nova) std::cout << x << " ";
	return 0;
}