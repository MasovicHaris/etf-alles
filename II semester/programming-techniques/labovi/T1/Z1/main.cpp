//TP 2016/2017: Tutorijal 1, Zadatak 1
#include <iostream>

int main ()
{
    int a, b, c, e;
    std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin >> a >> b >> c;
    std::cout << "Unesite sirinu plocice u centimetrima: ";
    std::cin >> e;

    a=a*100;
    b=b*100;
    c=c*100;
    double P1 = a*b + 2*a*c + 2*b*c;
    double P2 = e*e;
    double razlika;
    razlika = P1/P2;

    if((razlika - (int)razlika)==0)
       // std::cout << std::endl << "Za poplocavanje bazena dimenzija " << a/100 << "x" << b/100 << "x" << c/100 << "m sa plocicama dimenzija " << e <<"x" << e<<"cm potrebno je " << P1/P2 << " plocica.";
       std::cout << std::endl << "Za poplocavanje bazena dimenzija " << a/100 << "x" << b/100 << "x" << c/100 << "m sa plocicama dimenzija " << e <<"x" << e<<"cm"
       << std::endl <<"potrebno je " << razlika << " plocica.";
    else
       // std::cout << std::endl << "Poplocavanje bazena dimenzija " << a/100 << "x" << b/100 <<"x"<<c/100 << "m sa plocicama dimenzija " << e << "x" << e << "cm nije izvodljivo bez lomljenja plocica!";
        std::cout << std::endl << "Poplocavanje bazena dimenzija " << a/100 << "x" << b/100 <<"x"<<c/100 << "m sa plocicama dimenzija " << e << "x" << e << "cm" 
        << std::endl << "nije izvodljivo bez lomljenja plocica!";
    return 0;
}