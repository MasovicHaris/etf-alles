//NA 2017/2018: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <vector>
#include <complex>
#include <utility>


template<typename Tip>
double korak(Tip f, double x, double y, double h)
{
    double koefOne=f(x,y);
    double koefTwo=f(x+h/2, y+h*koefOne/2);
    double koefThree=f(x+h/2, y+h*koefTwo/2);
    double koefFour=f(x+h, y+h*koefThree);
    return y+h*(koefOne+2*koefTwo+2*koefThree+koefFour)/6;
}

template<typename Tip>
std::vector<std::pair<double,double>> RK4Integrator(Tip f, double x0, double y0, double xmax, double h, double eps=1e-8, bool adaptive = false)
{
    if(h>0 && xmax<x0 || (h<=0 && xmax>x0)) return {{x0,y0}};
    std::vector<std::pair<double,double>> k;
    if(!adaptive)
    {
        double x=x0, y=y0;
        if(h>0)
        {
            while(x<=xmax+eps)
            {
                k.push_back({x,y});
                double l1=f(x,y);
                double l2=f(x+h/2, y+h*l1/2);
                double l3=f(x+h/2, y+h*l2/2);
                double l4=f(x+h, y+h*l3);
                y=y+h*(l1+2*l2+2*l3+l4)/6;
                x=x+h;
            }
        }
        else
        {
            while(x>=xmax-eps)
            {
                k.push_back({x,y});
                double l1=f(x,y);
                double l2=f(x+h/2, y+h*l1/2);
                double l3=f(x+h/2, y+h*l2/2);
                double l4=f(x+h, y+h*l3);
                y=y+h*(l1+2*l2+2*l3+l4)/6;
                x=x+h;
            }
        }
    }
    else
    {
        if(h>0)
        {
            double x=x0, y=y0;
            k.push_back({x,y});
            while(x<=xmax+eps)
            {
                double u = korak(f,x,y,h/2);
                double v = korak(f, x+h/2, u, h/2);
                double w = korak(f,x,y,h);
                double dlt = std::abs(w-v)/h;
                if(dlt<=eps)
                {
                    x+=h;
                    y=v;
                    k.push_back({x,y});
                }
                h*=std::min(5.,0.9*std::pow(eps/dlt,1/4.));
                
            }
            if(std::abs(k[k.size()-1].first-xmax)>std::numeric_limits<double>::epsilon())
            {
                k.erase(k.begin());
                h=xmax-k[k.size()-1].first;
                double u = korak(f,x,y,h/2);
                double v = korak(f, x+h/2, u, h/2);
                double w = korak(f,x,y,h);
                k[k.size()-1]={xmax,v};
            }
        }
        else
        {
            double x=x0, y=y0;
            k.push_back({x,y});
            while(x>=xmax-eps)
            {
                double u = korak(f,x,y,h/2);
                double v = korak(f, x+h/2, u, h/2);
                double w = korak(f,x,y,h);
                double dlt = std::abs(w-v)/((-1)*h);
                if(dlt<=eps)
                {
                    x=x+h;
                    y=v;
                    k.push_back({x,y});
                }
                h*=std::min(5.,0.9*std::pow(eps/dlt, 1/4.));
            }
            if(std::abs(k[k.size()-1].first-xmax)>std::numeric_limits<double>::epsilon())
            {
                 k.erase(k.begin());
                h=xmax-k[k.size()-1].first;
                double u = korak(f,x,y,h/2);
                double v = korak(f, x+h/2, u, h/2);
                double w = korak(f,x,y,h);
                k[k.size()-1]={xmax,v};
            }
        }
    }
    return k;
}
int main ()
{
	return 0;
}