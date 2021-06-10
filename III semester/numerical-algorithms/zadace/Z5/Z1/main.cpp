//NA 2017/2018: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <limits>
#include <functional>
#include <vector>
#include <complex>
#include <stdexcept>
#include <utility>
#include <algorithm>


enum RegulaFalsiMode {Unmodified, Illinois, Slavic, IllinoisSlavic};
const double PI = 4*std::atan(1);
const double eps = std::numeric_limits<double>::epsilon();
const double inf = std::numeric_limits<double>::infinity();

template<typename Tip>
bool BracketRoot(Tip fun, double x0, double &a, double &b, double hinit=1e-5, double hmax=1e10, double lambda = 1.4)
{
    if(hinit<=0 || hmax<=0 || lambda<=0) throw std::domain_error("Invalid parameters");
    double tempA=x0, f1=fun(tempA), h=hinit;
    while(std::abs(h)<hmax)
    {
        double tempB=tempA+h;
        double f2=fun(tempB);
        if(f1*f2<=0)
        {
            if(tempA>tempB) std::swap(tempA, tempB);
            a=tempA;
            b=tempB;
            return true;
        }
        
        h=h*lambda;
        tempA=tempB;
        f1=f2;
    }
    
    h=hinit;
    tempA=x0;
    f1=fun(tempA);
    while(std::abs(h)<hmax)
    {
        double tempB=tempA-h;
        double f2=fun(tempB);
        if(f1*f2<=0)
        {
            if(tempA>tempB) std::swap(tempA, tempB);
            a=tempA;
            b=tempB;
            return true;
        }
        h=h*lambda;
        tempB=tempA;
        f2=f1;
    }
    return false;
}



template<typename Tip>
double RegulaFalsiSolve(Tip fun, double a, double b, RegulaFalsiMode mode=Slavic, double epsilon=1e-10, int maxiter=100)
{
    if(fun(a)*fun(b)>0) throw std::range_error("Root must be bracketed");
    if(epsilon<=0 || maxiter<=0) throw std::domain_error("Invalid parameters");
    std::function<double(double)> phi;
    double f1,f2,c,cStaro;
    int i;
    switch(mode)
    {
        case Illinois:
        {
            f1=fun(a); f2=fun(b); c=a; cStaro=b;
            i=0;
            while(std::abs(c-cStaro)>epsilon)
            {
                if(i==maxiter) throw std::logic_error("Given accuracy has not achieved");
                cStaro=c;
                c=(a*f2-b*f1)/(f2-f1);
                double f3=fun(c);
                if(std::abs(f3)<epsilon) return c;
                if(f1*f3<0) {b=a; f2=f1;}
                else f2/=2;
                a=c;
                f1=f3;
                i++;
            }
            return c;
            break;
        }
        
        case Unmodified:
        {
            f1=fun(a), f2=fun(b),c=a, cStaro=b;
            i=0;
            while(std::abs(c-cStaro)>epsilon)
            {
                if(i==maxiter) throw std::logic_error("Given accuracy has not achieved");
                cStaro=c;
                c=(a*f2-b*f1)/(f2-f1);
                double f3=fun(c);
                if(std::abs(f3)<epsilon) return c;
                if(f1*f3<0)
                {
                    b=a; f2 = f1;
                }
                a=c;
                f1=f3;
                i++;
            }
            return c;
            break;
        }
        
        case IllinoisSlavic:
        {
            phi=[](double x){return x/(1+std::abs(x));};
            f1=phi(fun(a));
            f2=phi(fun(b));
            c=a; cStaro=b;
            i = 0;
            while(std::abs(c-cStaro)>epsilon)
            {
                if(i==maxiter) throw std::logic_error("Given accuracy has not achieved");
                cStaro=c;
                c=(a*f2-b*f1)/(f2-f1);
                double f3=phi(fun(c));
                if(std::abs(f3)<epsilon) return c;
                if(f1*f3<0)
                {
                    b=a;
                    f2=f1;
                }
                else f2=f2/2;
                a=c;
                f1=f3;
                i++;
            }
            return c;
            break;
        }
        
        case Slavic:
        {
            phi=[](double x){return x/(1+std::abs(x));};
            f1=phi(fun(a));
            f2=phi(fun(b));
            c=a; cStaro=b;
            i = 0;
            
            while(std::abs(c-cStaro)>epsilon)
            {
                if(i==maxiter) throw std::logic_error("Given accuracy has not achieved");
                cStaro=c;
                c=(a*f2-b*f1)/(f2-f1);
                double f3=phi(fun(c));
                if(std::abs(f3)<epsilon) return c;
                if(f1*f3<0)
                {
                    b=c;
                    f2=f3;
                }
                else
                {
                    a=c;
                    f1=f3;
                }
                i++;
            }
        }
        
        default:
            throw std::domain_error("Invalid Regula Falsi mode");
            break;
    }
}

template<typename Tip>
double RiddersSolve(Tip f, double a, double b, double epsilon = 1e-10, int maxiter=100)
{
    if(f(a)*f(b)>0) throw std::range_error("Root must be bracketed");
    if(epsilon<=0 || maxiter <= 0) throw std::domain_error("Invalid parameters");
    double f1=f(a), f2=f(b);
    int i = 0;
    while(std::abs(b-a)>=epsilon)
    {  if(i==maxiter) throw std::logic_error("Given accuracy has not achieved");
        double c=(a+b)/2, f3=f(c);
        if(std::abs(f3)<eps) return c;
        int sign;
        if((f1-f2)>0) sign=1;
        else if((f1-f2)<0) sign = -1;
        else sign = 0;
        double d = c+(f3*(c-a)*sign)/std::sqrt(f3*f3 - f1*f2);
        double f4=f(d);
        if(std::abs(f4) < eps) return d;
        if(f3*f4<=0)
        {
            a=c;
            b=d;
            f1=f3;
            f2=f4;
        }
        else if(f1*f4<=0)
        {
            b=d;
            f2=f4;
        }
        else
        {
            a=d;
            f1=f4;
        }
        i++;
    }
    return (a+b)/2;
}


template<typename Tip1, typename Tip2>
double NewtonRaphsonSolve(Tip1 f, Tip2 fprim, double x0, double epsilon=1e-10, double damping=0, int maxiter=100)
{
    if(epsilon<=0 || maxiter<=0 || damping<0 || damping>=1) throw std::domain_error("Invalid parameters");
    double deltax=inf;
    double x=x0;
    int i=0;
    while(std::abs(deltax)>epsilon)
    {
        if(std::abs(fprim(x))<epsilon || i==maxiter) throw std::logic_error("Convergence has not achieved");
        double v = f(x);
        if(std::abs(v)<epsilon) return x;
        deltax = v/fprim(x);
        x=x-deltax;
        i++;
    }
    return x;
}

std::complex<double> operator+(std::complex<double> c1, std::complex<double> c2)
{
    return {c1.real()+c2.real(), c1.imag()+c2.imag()};
}

std::complex<double> operator-(std::complex<double> c1, std::complex<double> c2)
{
    return {c1.real()-c2.real(), c1.imag()-c2.imag()};
}

std::complex<double> operator*(std::complex<double> c1, std::complex<double> c2)
{
    return {c1.real()*c2.real() - c1.imag()*c2.imag(), c1.real()*c2.imag()+c1.imag()*c2.real()};
}

std::complex<double> dajKonjugovanoKompleksni(std::complex<double> c)
{
    return {c.real(), (-1)*c.imag()};
}

std::complex<double> operator/(std::complex<double> c1, std::complex<double> c2)
{
    std::complex<double> br = c1*dajKonjugovanoKompleksni(c2), naz = c2*dajKonjugovanoKompleksni(c2);
    return {br.real()/naz.real(), br.imag()/naz.real()};
}

std::complex<double> operator*(double c1, std::complex<double> c2)
{
    std::complex<double> t(c1,0);
    return t*c2;
}

std::complex<double> operator*(std::complex<double> c1, double c2)
{
    return c2*c1;
}

bool operator ==(std::complex<double> c1, std::complex<double> c2)
{
    return (std::abs(c1.real()-c2.real())<eps && std::abs(c1.imag()-c2.imag())<eps);
}

bool operator !=(std::complex<double> c1, std::complex<double> c2)
{
    return !(c1==c2);
}

std::pair<std::complex<double>,bool> Laguerre(std::vector<double> p, int n, std::complex<double> x, double epsilon, int maxiter)
{
    std::complex<double> dx = inf;
    int k=1;
    while(std::abs(dx) > epsilon && k<maxiter)
    {
        std::complex<double> f=p[n];
        std::complex<double> d=0;
        std::complex<double> s=0;
        for(int i = n-1; i>=0; i--)
        {
            s=s*x+2*d;
            d=d*x + f;
            f=f*x + p[i];
        }
        
        if(f==0) return {x,true};
        std::complex<double> r = std::sqrt((n-1)*((n-1)*d*d-n*f*s));
        if(std::abs(d+r)>std::abs(d-r)) dx=n*f/(d+r);
        else dx=n*f/(d-r);
        x=x-dx;
        k++;
    }
    
    if(std::abs(dx)<=epsilon) return {x,true};
    return {x,false};
}

std::pair<std::complex<double>, bool> Laguerre (std::vector<std::complex<double>> p, int n, std::complex<double> x, double epsilon, int maxiter)
{
    std::complex<double> dx=inf;
    int k=1;
    while(std::abs(dx)>epsilon && k<maxiter)
    {
        std::complex<double> f=p[n];
        std::complex<double> d=0;
        std::complex<double> s=0;
        for(int i = n-1; i>=0; i--)
        {
            s=s*x+2*d;
            d=d*x + f;
            f=f*x + p[i];
        }
        
        if(f==0) return {x,true};
        std::complex<double> r = std::sqrt((n-1)*((n-1)*d*d-n*f*s));
        if(std::abs(d+r)>std::abs(d-r)) dx=n*f/(d+r);
        else dx = n*f/(d-r);
        x=x-dx;
        k++;
    }
    if(std::abs(dx)<=epsilon) return {x,true};
    return {x,false};
}

std::vector<std::complex<double>> PolyRoots (std::vector<double> coefficients, double epsilon=1e-10, int maxiters=100, int maxtrials=10)
{
    if(epsilon<=0 || maxiters<=0 || maxtrials<=0) throw std::domain_error("Invalid parameters");
    int n = coefficients.size()-1, i=n, it=0;
    std::vector<std::complex<double>> p(n+1);
    while(i>=1)
    {
        if(it==maxiters) throw std::logic_error("Convergence has not achieved");
        int t=1;
        bool c = false;
        std::complex<double> x;
        while(!c && (t<maxtrials))
        {
            x={1,1};
            std::pair<std::complex<double>, bool> paric = Laguerre(coefficients, i, x, epsilon, maxiters);
            c=paric.second;
            x=paric.first;
            t++;
        }
        if(!c) throw std::logic_error("Convergence has not achieved");
        if(std::abs(x.imag())<=epsilon)
        {
            x=x.real();
            p[i]=x;
            double v = coefficients[i];
            for(int j = i-1; j>=0; j--)
            {
                double w = coefficients[j];
                coefficients[j]=v;
                v=w+x.real()*v;
            }
            i--;
        }
        
        else
        {
            p[i]=x;
            p[i-1]=dajKonjugovanoKompleksni(x);
            double alpha = 2*x.real();
            double beta = std::abs(x);
            beta=beta*beta;
            double u = coefficients[i], v=coefficients[i-1]+alpha*u;
            for(int j=i-2; j>=0; j--)
            {
                double w=coefficients[j];
                coefficients[j]=u;
                u=v;
                v=w+alpha*v - beta*coefficients[j];
            }
            i=i-2;
        }
        it++;
    }
    
    p.erase(p.begin());
    std::sort(p.begin(), p.end(), [](std::complex<double> x1, std::complex<double> x2){
        if(std::abs(x1.real()-x2.real())>eps) return x1.real()<x2.real();
        return x1.imag()<x2.imag();
    });
    
    return p;
}

std::vector<std::complex<double>> PolyRoots(std::vector<std::complex<double>> coefficients, double epsilon=1e-10, int maxiters=100, int maxtrials=10)
{
    if(epsilon<=0 || maxtrials<=0 || maxiters<=0) throw std::domain_error("Invalid parameters");
    int n = coefficients.size()-1, i=n, it=0;
    std::vector<std::complex<double>> p;
    while(i>=1)
    {
        if(it==maxiters) throw std::logic_error("Convergence has not achieved");
        int t=1;
        bool c = false;
        std::complex<double> x;
        while(!c && (t<maxtrials))
        {
            x={0,0};
            std::pair<std::complex<double>, bool> paric = Laguerre(coefficients, i, x, epsilon, maxiters);
            c=paric.second;
            x=paric.first;
            t++;
        }
        
        if(!c) throw std::logic_error("Convergence has not achieved");
        if(std::abs(x.imag())<=epsilon) x = x.real();
        p.push_back(x);
        std::complex<double> v = coefficients[i];
        for(int j=i-1; j>=0; j--)
        {
            std::complex<double> w= coefficients[j];
            coefficients[j]=v;
            v=w+x*v;
        }
        i--;
        it++;
    }
    
    std::sort(p.begin(), p.end(), [](std::complex<double> x1, std::complex<double> x2){
        if(std::abs(x1.real()-x2.real())>eps) return x1.real()<x2.real();
        return x1.imag()<x2.imag();
    });
    
    return p;
}

int main ()
{
// Test 24: Newton Raphson
auto fn = [](double x) { return std::atan(x-1); };
auto fnprim = [](double x) { return 1./(1+(x-1)*(x-1)); };
try{
   NewtonRaphsonSolve(fn, fnprim, 3, 1e-10, 0, 1000);
}
catch(std::logic_error e) {
    std::cout << "'" << e.what() << "'";
}
}