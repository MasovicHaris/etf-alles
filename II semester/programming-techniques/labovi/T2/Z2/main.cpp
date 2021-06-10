//TP 2016/2017: Tutorijal 2, Zadatak 2
#include <iostream>
#include <vector>

bool TestPerioda(const std::vector <double> v, int p)
{
    bool a(true);
    if(p>=v.size()) return false; // zašto bi p bio veći od veličine niza ili jednak - nema logike
    if(v.size()==1) return false; // niz od 1 elementa nije periodičan logično
    for(int i=0; i<int(v.size()); ++i) {
        if(i+p < v.size() && v[i]!=v[i+p]) {
            a = false;
        }
    }

    return a;
}

int OdrediOsnovniPeriod(const std::vector <double> v)
{
    int p=0;
    for(int i=1; i<int(v.size()); ++i) {

        bool a = true;
        if(v[0]==v[i]) {

            for(int j=1; j < int((v.size()-i)); ++j) {

                if(v[j]!=v[i+j]) {
                    a = false;
                    break;
                }
            }
            if(a) {
                p= i;
                break;
            }
        }
    }

    if(TestPerioda(v,p)) return p;
    return 0;
}


int main ()
{

    std::vector<double> vekta;
    double broj;
    std::cout << "Unesite slijed brojeva (0 za kraj): ";

    for(;;) {
        std::cin >> broj;
        if(broj==0) break;
        vekta.push_back(broj);
    }

    int rez = OdrediOsnovniPeriod(vekta);
    if(rez!=0) {
        std::cout << "Slijed je periodican sa osnovnim periodom " << rez << ".";
    } else std::cout << "Slijed nije periodican!";
    return 0;
}