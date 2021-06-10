//TP 2016/2017: Tutorijal 2, Zadatak 3
#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: ";
    std::cin >> n;
    std::complex <double> Z;
    std::complex <double> suma {0,0};
    int i=1;
    std::cout << std::endl;
    do {
        std::cout << "Z_" << i << " = ";
        std::cin >> Z;

        Z = 1./Z;
        suma+=Z;
        ++i; 

    } while(i<=n);

    std::cout << std::endl << "Paralelna veza ovih elemenata ima impedansu Z_ = " << 1./suma << ".";
    return 0;
}