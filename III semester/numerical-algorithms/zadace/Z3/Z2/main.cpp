//NA 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
template <typename FunType>
std::pair<double, bool> Limit(FunType f, double x0, double h = 0, double eps = 1e-8, double nmax = 20){
    if(eps <= 0 || nmax < 3 || nmax > 30) throw std::domain_error("Invalid parameters");
    if(std::fabs(h) < eps) h = 0.001 * std::max(1.,x0);
    std::pair<double, bool> x;
    double yold = std::numeric_limits<double>::infinity();
    std::vector<double> y(nmax);
    double p;
    for(int i = 0; i < nmax; i++){
     y[i] = f(x0 + h);
     p = 2;
     for(int k = i - 1; k >= 0; k--){
         y[k] = (p * y[k + 1] - y[k]) / (p - 1);
         p = p * 2;
     }
     if(std::fabs(y[0] - yold) < eps){
         x.first = y[0];
         x.second = true;
         return x;
     }
     yold = y[0];
     h = h / 2;
    }
    x.first = y[0];
    x.second = false;
    return x;
}
/* Nisam vidio da su vec testirani neki limesi tipa sinx / x u AT-ovima jer ih nisam otvarao, pa sam ih ostavio u mainu svakako */
int main (){
// limes 1 / x, x - > 0
auto p = Limit([](double x){return 1 / x;},0); 
std::cout << p.first << " " << p.second << std::endl;
// limes sin(x) / x; x -> 0
p = Limit([](double x){return sin(x) / x;},0);
std::cout << p.first << " " << p.second << std::endl;
// limes ln(1 + x) / x, x - > 0
p = Limit([](double x){return log(1 + x) / x;},0);
std::cout << p.first << " " << p.second << std::endl;
// limes (3x^3 - 3 )/(x^3 + 1), x -> inf
p = Limit([](double x){return (3 * x * x * x - 3) / (x * x * x + 1);},2);
std::cout << p.first << " " << p.second << std::endl;
	return 0;
}
