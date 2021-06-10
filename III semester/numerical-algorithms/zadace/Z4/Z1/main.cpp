//NA 2017/2018: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector> 
#include <exception>
class ChebyshevApproximation{
    private:
    std::vector<double> c;
    int m;
    double min, max;
    ChebyshevApproximation(std::vector<double> koef, double xmin, double xmax): c(koef), m(koef.size() - 1), min(xmin), max(xmax) {}
    public:
    template<typename FunType>
    ChebyshevApproximation(FunType f, double xmin, double xmax, int n){
        if(n < 1 || xmin >= xmax) throw std::domain_error("Bad parameters");
        std::vector<double> w(n+2);
        std::vector<double> v(n+1);
        c.resize(n+1);
        m = n;
        min = xmin;
        max = xmax;
        const double pi = 4 * atan(1);
        for(int i = 0; i <= n; i++){
            w[i] = pi * (2 * i + 1) / (2 * n + 2);
            v[i] = f((xmin + xmax + (xmax - xmin) * std::cos(w[i])) / 2);
        }
        double s;
        for(int k = 0; k <= n; k++){
            s = 0;
            for(int i = 0; i <= n; i++)
             s += v[i] * std::cos(k * w[i]);
            c[k] = 2 * s / (n + 1); 
        }
    }
    void set_m(int m){
        if(m > c.size() - 1 || m <= 1) throw std::domain_error("Bad order");
        this->m = m;
    }
    void trunc(double eps){
        if(eps < 0) throw std::domain_error("Bad tolerance");
        for(int i = m; i >= 0; i--){
            if(std::fabs(c[i]) > eps){
                m = i;
                return;
            }
        }
        throw std::domain_error("Bad tolerance");
    }
    double operator()(double x) const{
        if(x < min || x > max) throw std::domain_error("Bad argument");
        double t = (2 * x - min - max) / (max - min);
        double p = 1;
        double q = t;
        double s = c[0] / 2 + c[1] * t;
        double r;
        for(int k = 2; k <= m; k++){
            r = 2 * t * q - p;
            s += c[k] * r;
            p = q;
            q = r;
        }
        return s;
    }
    double derivative(double x) const{
        if(x < min || x > max) throw std::domain_error("Bad argument");
        double t = (2 * x - min - max) / (max - min);
        double p = 1;
        double q = 4 * t;
        double s = c[1] + 4 * c[2] * t;
        double r;
        for(int k = 3; k <= m; k++){
            r = k * (2 * t * q / (k - 1) - p / (k - 2));
            s += c[k] * r;
            p = q;
            q = r;
        }
        return 2 * s / (max - min);
    }
    ChebyshevApproximation derivative() const{
    double mi = 4. / (max-min);
    std::vector<double> temp(c.size());
    temp[m-1] = mi * m * c[m];
    temp[m-2] = mi * (m-1) * c[m-1];
    for(int k = m-3;k >= 0; k--)
        temp[k] = temp[k+2] + mi * (k+1) * c[k+1];
    return ChebyshevApproximation(temp,min,max);
    }
    ChebyshevApproximation antiderivative() const{
        double mi = ( max - min) / 4;
        std::vector<double> vek(m + 2,0);
        for(int i = 1; i <= m - 1; i++)
         vek[i] = mi / i * (c[i - 1] - c[i + 1]);
        vek[m] = mi / m * c[m-1];
        vek[m+1] = mi / (m + 1) * c[m];
        return ChebyshevApproximation(vek,min,max);
    }
    double integrate(double a, double b) const{
        if(a < min || a > max || b < min || b > max) throw std::domain_error("Bad interval");
        ChebyshevApproximation F(this->antiderivative());
        return F(b) - F(a);
    }
    double integrate() const{
        double s = 0;
        for(int k = 1; k <= (m - 1) / 2 + 1; k++)
         s += 2 * c[2 * k] / (1 - 4 * k * k);
        s *= (max - min) / 2;
        s += c[0] * (max - min) / 2;
        return s;
    }
    
};
/* Nisam stigao temeljitije istestirat program, stvarno nemam dovoljno vremena */
int main ()
{
ChebyshevApproximation c([](double x){return x * x + 2 * x + 1;},0,10,2); 
std::cout << c.integrate(1,2) << " " << c.integrate() << std::endl;
std::cout << c(3) << " " << c(7) << std::endl;
std::cout << c.derivative(4) << " " << c.derivative(2) << std::endl;
try{
    c.integrate(-1,2);
}
catch(std::domain_error d){
    std::cout << "Dobar!" << std::endl;
}
try{
    c.antiderivative()(18);
}
catch(std::domain_error d){
    std::cout << "Dobar!" << std::endl;
}
ChebyshevApproximation ln([](double x){return std::log(x);},1,10,2); 
ChebyshevApproximation lnizvod([](double x){return 1 / x;},1,10,2); 
std::cout << ln.derivative().integrate(5,7) << " " << lnizvod.integrate(5,7) << std::endl;


	return 0;
}