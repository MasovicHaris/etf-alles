//NA 2017/2018: Zadaća 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <utility>
#include <vector> 
template <typename FunType>
std::pair<double, bool> RombergIntegration(FunType f, double a, double b, double eps=1e-8, int nmax = 1000000, int nmin = 50){
 if(nmax < 0 || nmin < 0 || nmin > nmax || eps < 0) throw std::domain_error("Bad parameter");
 int n = 2;
 double h = (b - a) / n;
 double s = (f(a) + f(b)) / 2;
 double Iold = s;
 double p;
 std::vector<double> ig;
 for(int i = 1; n <= nmax; i++){
     for(int j = 1; j <= n / 2; j++)
      s += f(a + (2 * j - 1) * h);
     ig.emplace_back(h * s);
     p = 4;
     for(int k = ig.size() - 2; k >= 0; k--){
         ig[k] = (p * ig[k+1] - ig[k]) / (p - 1);
         p *= 4;
     }
     if(n >= nmin && std::fabs(ig[0] - Iold) <= eps) return {ig[0],true};
  Iold = ig[0];
 h /= 2;
 n *= 2;
}
return {Iold, false};
}


template <typename FunType>
std::pair<double, bool> TanhSinhIntegration(FunType f, double a,double b,double eps = 1e-8, int nmax = 1000000, int nmin = 20, double range = 3.5){
    if(nmin < 0 || nmax < 0 || nmax < nmin || range < 0 || eps < 0) throw std::domain_error("Bad parameter");
    const double pi = 4 * atan(1);
    int sign = 1;
    if(a > b){
        sign = -1;
        std::swap(a,b);
    }
    auto fp = [&](double t){
        double t1 = std::cosh(pi * std::sinh(t)/2);
        double t2 = (a + b) / 2 + (b - a) / 2 * std::tanh(pi * std::sinh(t) / 2);
        double d  = std::cosh(t) * f(t2) /(t1 * t1);
        if(!std::isfinite(d)) return 0.;
        return (b - a) * pi / 4 * d;
};
double n = 2;
double h = (2 * range) / n;
double s = (fp(-range) + fp(range)) / 2;
double Iold = s;
while(n < nmax){
    for(int i = 1; i <= n / 2; i++)
     s += fp(-range + (2 * i - 1) * h);
    double I = h * s;
    if(n > nmin && std::fabs(I - Iold) <= eps) return {sign * I, true};
    Iold = I;
    n *= 2;
    h /= 2;
}
return {sign * Iold, false};
}
std::pair<double, bool> operator+(std::pair<double,bool> p1, std::pair<double, bool> p2){
    return {p1.first + p2.first, p1.second && p2.second};
}
template <typename FunTip>
std::pair<double, bool> AdaptiveAux(FunTip f, double a, double b, double eps, double f1, double f2, double f3, int maxdepth){
    if(!std::isfinite(f1)) f1 = 0;
    if(!std::isfinite(f2)) f2 = 0;
    if(!std::isfinite(f3)) f3 = 0;
    double c = (a + b) / 2;
    double I1 = (b - a) * (f1 + 4 * f3 + f2) / 6;
    double f4 = f((a + c) / 2);
    double f5 = f((c + b) / 2);
    if(!std::isfinite(f4)) f4 = 0;
    if(!std::isfinite(f5)) f5 = 0;
    double I2 = (b - a) * (f1 + 4 * f4 + 2 * f3 + 4 * f5 + f2) / 12;
    if(std::fabs(I1 - I2) <= eps) return {I2, true};
    if(maxdepth <= 0) return {I2, false};
    return AdaptiveAux(f,a,c,eps,f1,f3,f4,maxdepth - 1) + AdaptiveAux(f,c,b,eps,f3,f2,f5,maxdepth-1);
}

template <typename FunType>
std::pair<double,bool> AdaptiveIntegration(FunType f, double a, double b, double eps = 1e-10, int maxdepth = 30, int nmin = 1){
if(maxdepth < 0 || nmin < 0 || eps < 0) throw std::domain_error("Bad parameter");
std::pair<double,bool> s = {0, true};
double h = (b - a) / nmin;
for(int i = 1; i <= nmin; i++){
    auto temp = AdaptiveAux(f, a, a + h, eps, f(a), f(a + h), f(a + h/2), maxdepth);
    s.first += temp.first,
    s.second = s.second && temp.second;
    a += h;
}
return s;
}
int main ()
{
    // romberg
    auto f = [](double x) {
        if(x == 0) return 0.;
        return 1. / sqrt(x);
    };
    auto a = RombergIntegration(f, 0, 1);
    std::cout << a.first << " " << a.second << std::endl;
    a = RombergIntegration(f, 0, 1, 1e-8, 1000000);
    std::cout << a.first << " " << a.second << std::endl;
    
    // tanhsinh
    a = TanhSinhIntegration(f, 0 , 1);
      std::cout << a.first << " " << a.second << std::endl;
    a = TanhSinhIntegration(f, 0, 1, 1e-8, 1000000);
    std::cout << a.first << " " << a.second << std::endl;
    
    // adaptive
    a = AdaptiveIntegration(f,0,1);
         std::cout << a.first << " " << a.second << std::endl;
    a = AdaptiveIntegration(f, 0, 1, 1e-8, 1000000);
    std::cout << a.first << " " << a.second << std::endl;
    
    

	return 0;
}