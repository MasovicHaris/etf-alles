//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 3, Zadatak 1
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <stdexcept>

double fja(double x){return x*x+sin(x);}

double max(double x, double y)
{
    if(x>y) return x;
    else return y;
}

double min(double x, double y)
{
    if(x<y) return x;
    else return y;
}

double dublve(int n, int d, int index, double xi, const std::vector<std::pair<double,double>> &x)
{
    double suma(0);
    index++;        //shiftano po i kako bi mogo izracunat sve prvo za i=1!
    for(int k=max(1,index-d); k<=min(index,n-d); k++)
    {
        double proizvod(1);
        for(int j=k-1; j<k+d; j++)
        {
            if(index-1==j) continue; //j!=i preskace se u sumi!
            proizvod*=(1/(xi-x[j].first));
        }
        proizvod*=pow(-1,k-1);
        suma+=proizvod;
    }
    return suma;
}

std::function<double(double)> BaricentricnaInterpolacija(std::vector<std::pair<double,double>> v, int d)
{
    if(d<0 || d>=v.size()) throw std::domain_error("Nedozvoljen red");
    for(int i=0; i<v.size(); i++)
    {
        for(int j=0; j<v.size(); j++)
        {
        if(i!=j && v[i].first==v[j].first) throw std::domain_error("Neispravni cvorovi");
        }
    }
    
    int n=v.size();
    std::vector<double> omega;
    for(int i=0; i<v.size(); i++)
    {
        omega.push_back(dublve(n,d,i,v[i].first,v));
    }
    
    
    return [v,d,omega,n](double x)
    {
        for(int i=0; i<n; i++)
        {
            if(x==v[i].first) return v[i].second;
        }
        
        int i=0;
        auto f1(double((omega[i]*(v[i].second))/(x-v[i].first)));
        auto f2(omega[i]/(x-v[i].first));
        
        for(i=1; i<n; i++)
        {
            f1=f1+(omega[i]*v[i].second)/(x-v[i].first);
            f2=f2+(omega[i])/(x-v[i].first);
        }
        return f1/f2;
    };
}

std::function<double(double)> BaricentricnaInterpolacija(std::function<double(double)> f, double xmin, double xmax, double dx, int d)
{
    if(xmin>xmax || dx<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double,double>> v;
    for(;;)
    {
        if(xmin>xmax) break;
        v.push_back(std::make_pair(xmin,f(xmin)));
        xmin+=dx;
    }
    return BaricentricnaInterpolacija(v,d);
}


int main ()
{
    try
    {
            for(;;)
            {
                std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
                int n;
                double xmin,xmax,dx;
                std::cin>>n;
                std::vector<std::pair<double,double>> veka;
                if(n==1)
                {
                    std::cout<<"Unesite broj cvorova: ";
                    int c;
                    std::cin>>c;
                    std::cout<<"Unesite cvorove kao parove x y: ";
                    for(int i=0 ; i<c; i++)
                    {
                        double k, l;
                        std::cin>>k;
                        std::cin>>l;
                        veka.push_back(std::make_pair(k,l));
                    }
                    std::cout<<"Unesite red interpolacije: ";
                    int d;
                    std::cin>>d;
                    if(d<0 || d>=veka.size()) throw std::domain_error("Nedozvoljen red");
                   
                    while(1)
                    {
                        double x;
                        std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                        std::cin>>x;
                        if(!std::cin) return 0;
                        std::cout<<"f("<<x<<") = "<<BaricentricnaInterpolacija(veka,d)(x)<<std::endl;
                    }
                }
                else if(n==2)
                {
                    std::cout<<"Unesite krajeve intervala i korak: ";
                    std::cin>>xmin>>xmax>>dx;
                    std::cout<<"Unesite red interpolacije: ";
                    int d;
                    std::cin>>d;
                    if(xmin>xmax || dx<=0) throw std::domain_error("Nekorektni parametri");
                    double xmin2(xmin);
                    for(;;)
                    {
                        if(xmin2>xmax) break;
                        veka.push_back(std::make_pair(xmin2,fja(xmin2)));
                        xmin2+=dx;
                    }
                    
                    while(1)
                    {
                        std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
                        double x; std::cin>>x;
                        if(!std::cin) return 0;
                        std::cout<<"f("<<x<<") = "<<fja(x)<< " ";
                        std::cout<<"fapprox("<<x<<") = "<<BaricentricnaInterpolacija(fja,xmin,xmax,dx,d)(x)<<std::endl;
                    }
                }
            }
    }
    catch(std::domain_error e)
    {
        std::cout<<e.what()<<std::endl;
    }
    
	return 0;
}