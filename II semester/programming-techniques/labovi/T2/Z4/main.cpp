//TP 2016/2017: Tutorijal 2, Zadatak 4
#include <iostream>
#include <complex>

int main ()
{
    int n;
    std::cout << "Unesite broj elemenata: ";
    std::cin >> n;
    std::cout << std::endl;
    double R, X;
    std::complex <double> Z;
    std::complex <double> suma {0,0};
    int i=1;

    do { 

        std::cout << "R" << i << " = ";
        std::cin >> R;
        std::cout << "X" << i << " = ";
        std::cin >> X;

        Z = std::complex <double> {R,X};
        Z = 1./Z;
        suma +=Z;
        i++;
        std::cout << std::endl;

    } while(i<=n);

    std::cout << "Paralelna veza ovih elemenata ima R = "
              << std::real(1./suma) << " i X = "
              << std::imag(1./suma) << ".";
    return 0;
}