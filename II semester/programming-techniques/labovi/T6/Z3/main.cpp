/*
    TP 16/17 (Tutorijal 6, Zadatak 3)

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <vector>
#include <stdexcept>

int **KreirajTrougao(int n)
{

	if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
	int **p = nullptr;

	try {
		p = new int *[n];
		for(int i=0; i < n; ++i) p[i] = nullptr;

		for(int i=0; i < n; i++) {
			p[i] = new int [2*i+1];

			for(int j=0; j < 2*i+1; j++) {
				if(j<=i) p[i][j] = i+1-j;
				else p[i][j] = j-i+1;
			}
		}
		
	} catch(...) {
		for(int i=0; i < n ; i++) delete [] p[i];
		delete []p;
		throw std::bad_alloc();
	}

	return p;
}
int main ()
{
	try {
		int n;
		std::cout << "Koliko zelite redova: ";
		std::cin >> n;
		auto mat = KreirajTrougao(n);

		for(int i=0; i <n; i++) {
			for(int j=0; j < 2*i+1; j++) {
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
		
		for(int i=0; i < n ; i++) delete [] mat[i];
		delete []mat;
		
	} catch(std::domain_error exec) {
		std::cout << "Izuzetak: " << exec.what() << std::endl;
	} catch(...) {
		std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
	}
	return 0;
}