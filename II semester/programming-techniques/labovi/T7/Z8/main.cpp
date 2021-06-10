/* 
    TP 16/17 (Tutorijal 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <algorithm>

std::string IzvrniBezRazmaka(const std::string &recenica){
	std::string novi;
	std::remove_copy(recenica.rbegin(), recenica.rend(), std::back_inserter(novi), ' ');
	return novi;
}

int main ()
{
	return 0;
}