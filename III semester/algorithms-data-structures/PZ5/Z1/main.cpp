#include <iostream>

int fib2_0(int n, int pretprosli = 0, int prosli = 1){
    if(n<=1) return n;
    if(n==2) return (pretprosli + prosli);
    return fib2_0(n-1, prosli, prosli+pretprosli);
}

int nzd(int x, int y){
    if(y == 0) return x;
    return nzd(y, x%y);
}

int main() {
    std::cout << "Pripremna Zadaca Za Vjezbu 5, Zadatak 1";
    return 0;
}
