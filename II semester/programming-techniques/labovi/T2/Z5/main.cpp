//TP 2016/2017: Tutorijal 2, Zadatak 5
#include <iostream>
#include <complex>
#include <cmath>
int main ()
{
    int n;
    const double PI(4*atan(1));
    std::cout << "Unesi broj elemenata: ";
    std::cin >> n;
    std::cout << std::endl;

    double B, F;
    std::complex <double> Z;
    std::complex <double> suma {0,0};
    int i=1;

    do {
        std::cout << "Z" << i << " = ";
        std::cin >> B;
        std::cout << "fi" << i <<" = ";
        std::cin >> F;
        F = F* PI/180;
        Z = std::polar(B,F);
 
        Z = 1./Z;
        suma +=Z;
        i++;

        std::cout << std::endl;
    } while(i<=n);

    suma = 1./suma;

    std::cout << "Paralelna veza ovih elemenata ima Z = "
              << std::abs(suma) << " i " << "fi = " << (std::arg(suma) * 180)/PI << ".";
    return 0;
}