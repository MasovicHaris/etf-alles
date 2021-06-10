/*
    TP 16/17 (Tutorijal 12, Zadatak 5)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
int main ()
{
	int n;
	std::cout << "Koliko zelite elemenata: ";
	std::cin >> n;
	std::vector<double> vektor(n);
	std::cout << "Unesite elemente: ";
	for(int i=0; i < n; i++) std::cin >> vektor[i];
//	std::transform(vektor.begin(), vektor.end(), vektor.begin(), std::bind1st(std::divides<double>(), 1)); 							// 1 nacin 
	std::transform(vektor.begin(), vektor.end(), vektor.begin(), std::bind(std::divides<double>(), 1, std::placeholders::_1));		// 2 nacin
	std::cout << "Transformirani elementi: ";
	for(int i=0; i < n; i++) std::cout << vektor[i] << " "; 
	return 0;  
}