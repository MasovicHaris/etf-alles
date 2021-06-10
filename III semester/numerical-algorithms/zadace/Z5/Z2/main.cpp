//NA 2017/2018: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <complex>
#include <algorithm>
#include <stdexcept>
#include <limits>

const double epsilon = std::numeric_limits<double>::epsilon();

template<typename Tip>
double FindMinimum(Tip f, double x0, double eps =1e-8, double hinit = 1e-5, double hmax=1e10, double lambda = 1.4)
{
    if(eps<=0 || hinit<=0 || hmax<=0 || lambda<=0) throw std::domain_error("Invalid parameters");
    double h = hinit, a=x0-h, b=x0+h, c=x0;
    bool found =false;
    while(std::abs(h)<hmax)
    {
        if(f(c+h)<f(c))
        {
            b=c+h;
            a=c-h;
        }
        else if(f(c-h)<f(c))
        {
            b=c-h;
            a=b-h;
        }
        else
        {
            a=c-h;
            b=c+h;
            found=true;
            break;
        }
        c=b;
        h=h*lambda;
    }
    
    if(!found) throw std::logic_error("Minimum has not found");
    double k = (std::sqrt(5)+1)/2;
    double d;
    if(std::abs(c-a)<std::abs(b-c)) d=b-(b-c)/k;
    else
    {
        d=c;
        c=a+(c-a)/k;
    }
    double u = f(c);
    double v = f(d);
    while(std::abs(b-a)>eps)
    {
        if(u<v)
        {
            b=d;
            d=c;
            c=a+(c-a)/k;
            v=u;
            u=f(c);
        }
        else
        {
            a=c;
            c=d;
            d=b-(b-d)/k;
            u=v;
            v=f(d);
        }
    }
    return (a+b)/2;
}


int main ()
{
	return 0;
}