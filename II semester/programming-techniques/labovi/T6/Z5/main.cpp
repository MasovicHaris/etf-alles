/*
    TP 16/17 (Tutorijal 6, Zadatak 5)

	Autotestovi by Kerim Hodzic. Prijave gresaka, pitanja
	i sugestije saljite na mail: khodzic2@etf.unsa.ba

	Napomene: testovi su konacni tek pred tutorijal
			  za krsenje zabrana dobiva se 0 bodova za zadatak

*/
#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>

typedef std::vector<std::deque<int>> Matrica;

Matrica KreirajMatricu(int br_redova, int br_kolona)
{
    return Matrica(br_redova, std::deque<int>(br_kolona));
}

template <typename kont>
auto KreirajDinamickuKopiju2D(kont &z) -> typename std::remove_reference<decltype(z[0][0])>::type** {
    typename std::remove_reference<decltype(z[0][0])>::type ** mat = nullptr;
    try {

        mat = new typename std::remove_reference<decltype(z[0][0])>::type* [z.size()];
        for(int i=0; i < z.size(); ++i) mat[i] = nullptr;

        for(int i=0; i< z.size(); ++i) {

            mat[i] = new typename std::remove_reference<decltype(z[0][0])>::type  [z[i].size()];

            for (int j = 0; j < z[i].size(); j++) {
                mat[i][j] = z[i][j];
            }
        }

    } catch (...) {
        for(int i=0; i < z.size() ; i++) delete [] mat[i];
        delete []mat;
        throw std::bad_alloc();
    }

    return mat;
}

int main()
{
    try {
        Matrica v;
        int broj;
        std::cout << "Unesite broj redova kvadratne matrice: ";
        std::cin >> broj;
        v = KreirajMatricu(broj, broj);
        int element;
        std::cout << "Unesite elemente matrice: ";
        for(int i=0; i< broj; i++) {
            for(int j=0; j< broj; j++) {
                std::cin >> element;
                v[i][j] = element;
            }
        }
        auto matrix = KreirajDinamickuKopiju2D(v);

        for(int i=0; i < v.size(); i++) {
            for(int j=0; j < v[i].size(); j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        
        for(int i=0; i < v.size() ; i++) delete [] matrix[i];
        delete []matrix;
    } catch(...) {
        std::cout<<"Nedovoljno memorije";
    }
    return 0;
}