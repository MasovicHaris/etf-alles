#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <stdexcept>

// pripremni zadatak

bool prost(int n) {
    int d = int(sqrt(n));
    for (int i(2); i<=d; i++) if (n%i==0) return false;
    return true;
}
 

void Goldbach(int n, int &p, int &q) {
    if(n<2 || (n%2)!= 0) throw std::domain_error("Tebe sam ljubio i grliooo");
    for(int i=2; i < (n+1)/2; ++i) {
        if (prost(i) && prost(n - i)) {
            int a(i), b(n - i);
            if (n == (a + b)) {
                p = a;
                q = b;
                return;
            }
        }
    }
    if(p == (-1) && q ==(-1)) throw std::domain_error("Bojanaaa");
}

int main() {

    int n, p(-1), q(-1);
    std::cout << "Unesite n: ";
    std::cin >> n;
    clock_t vrijeme1 = clock();
    try {
        Goldbach(n, p, q);
    }catch(std::domain_error &ex){
        std::cout << ex.what() << " ";
        return 0;
    }
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    std::cout << "p: " << p << " q: " << q;
    return 0;
}