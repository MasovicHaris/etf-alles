//TP 2016/2017: Tutorijal 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

bool DaLiJeProst(int broj)
{
    if(broj<=0 || broj==1) return false;
    if(broj%2==0 && broj!=2) return false;

    int kor = std::sqrt(broj);
    for(int i=3; i<=kor; ++i) {
        if(broj%i==0) return false;
    }

    return true;
}

std::vector<int>ProstiBrojeviUOpsegu(int a, int b)
{
    std::vector<int> myVector;
    int max = std::numeric_limits<int>::max();
    for(int i=a; i<=b; ++i) {
        if(DaLiJeProst(i)) myVector.push_back(i);
        if(i == max) break;
    }

    return myVector;
}



int main ()
{
    int a, b;
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    std::cin >> a >> b;

    std::vector<int>noviVector;

    noviVector = ProstiBrojeviUOpsegu(a,b);

    if(noviVector.size()!=0) {
        std::cout << "Prosti brojevi u rasponu od " << a <<" do " << b << " su: ";
        for(int i=0; i<int(noviVector.size()); ++i) {

            if(i!=noviVector.size()-1) std::cout << noviVector.at(i) << ", ";
            else std::cout << noviVector.at(i) << std::endl;
        }
    } else std::cout << "Nema prostih brojeva u rasponu od " << a << " do " << b << "!";
    return 0;
}