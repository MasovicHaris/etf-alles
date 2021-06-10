/*
    TP 16/17 (Tutorijal 6, Zadatak 4)

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <vector>
#include <stdexcept>

// int **a(new int*[n]);
// a[0] = new int[n * m];
// for(int i = 1; i < n; i++) a[i] = a[0] + m * i;

int **KreirajTrougao(int n)
{

	if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
	int **p = nullptr;
 
	try {
		p = new int *[n];
		p[0] = new int [n*n];
		p[0][0] = 1; 
		for(int i=1; i < n; i++) {
			
			p[i] = p[i-1] + 2*i-1;
			for(int j=0; j < 2*i+1; j++) {
				if(j<=i) p[i][j] = i-j+1;
				else p[i][j] = j-i+1;
			}
		}
	} catch(...) {
		delete []p;
		p = nullptr;
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
		int **mat = KreirajTrougao(n);

		for(int i=0; i <n; i++) {
			for(int j=0; j < 2*i+1; j++) {
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
	
		delete []mat[0];
		delete []mat;
		mat = nullptr; 
		
	} catch(std::domain_error exec) {
		std::cout << "Izuzetak: " << exec.what() << std::endl;
	} catch(...) {
		std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
	}
	return 0;
}