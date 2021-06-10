#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <stdexcept>
// zadatak 4 i zadatak 5

bool Permutacija (std::string s1, std::string s2) {
    if (s1.length()!=s2.length()) return false;
    int niz1[256]={0}, niz2[256]={0};
    for (int i=0; i<s1.length(); i++) {
        niz1[s1[i]-'\0']++;
        niz2[s2[i]-'\0']++;
    }
    for (int i=0; i<256; i++) if (niz1[i]!=niz2[i]) return false;
    return true;
} 

bool prost(int n) {
    int d = int(sqrt(n));
    for (int i(2); i<=d; i++) if (n%i==0) return false;
    return true;
}

void ispisiProste(int n){
    for(int i=0; i < n; ++i) if(prost(i)) std::cout << i << " ";
}  

int main() {

    int n, p(-1), q(-1);

    clock_t vrijeme1 = clock();
    
    std::cout << Permutacija("halo", "aloh") << " ";
    ispisiProste(n);
    
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    std::cout << "p: " << p << " q: " << q;
     return 0;
}