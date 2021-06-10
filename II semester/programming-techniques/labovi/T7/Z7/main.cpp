/* 
    TP 16/17 (Tutorijal 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>

template <typename tip>
std::set<tip> Presjek(std::set<tip> skup1, std::set<tip> skup2){
	std::set<tip> novi;
	
	typename std::set<tip>::iterator it1(skup1.begin()), it2(skup1.end());
	while(it1 != it2){
		if(skup2.find(*it1) != skup2.end()){
			novi.insert(*it1);	
		}
		it1++;
	}
	
	return novi;
	
}

template <typename tip>
std::set<tip> Unija(std::set<tip> skup1, std::set<tip> skup2){
	std::set<tip> novi;
	
	typename std::set<tip>::iterator it1(skup1.begin()), it2(skup1.end());
	typename std::set<tip>::iterator it21(skup2.begin()), it22(skup2.end());
	
	while(it1 != it2){ novi.insert(*it1); it1++; }
	while(it21 != it22) { novi.insert(*it21); it21++; }
	
	return novi;
}



int main ()
{
	return 0;
}