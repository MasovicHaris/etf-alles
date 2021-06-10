/* 
    TP 16/17 (Tutorijal 7, Zadatak 10)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <functional>

int funmasha(int x){
	return 2*x; // vraca cijeli
}

std::function<int(int)> IteriranaFunkcija(int funmasha(int), int n){
	if(n <=0) return funmasha;
	return [funmasha, n](int x){ for(int i=0; i < n; i++) { x = funmasha(x); } return x; };
}

int main ()
{
	return 0;
}