//TP 2016/2017: Tutorijal 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <iomanip>

int main ()
{
    double broj;
    do {
        std::cout << "Unesite prirodan broj ili 0 za kraj: ";
        while (!(std::cin >> broj)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Niste unijeli prirodan broj! " << std::endl;
            std::cout << "Unesite prirodan broj ili 0 za kraj: ";
        }
        
        if(broj==0) break;
        
        if(broj <0 || (broj - (int)broj)!=0) {
            std::cout << "Niste unijeli prirodan broj! " << std::endl;
            continue;
        }
 
        int suma=0;
        for(int i=1; i<broj; i++) if((int)broj%i==0) suma+=i;
        if(suma>broj) std::cout << "Broj " << broj <<" je obilan!" << std::endl;
        else if(suma==broj) std::cout << "Broj " << broj <<" je savrsen!" << std::endl;
        else if(suma<broj) std::cout << "Broj " << broj <<" je manjkav!" << std::endl;
        
    } while(broj!=0);
    std::cout << "Dovidjenja!";
    return 0;
}