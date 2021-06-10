//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <vector>
#include <cmath>
#include <iostream>
#include <stdexcept>
bool jelprost(int n)
{
    bool prost=true;
    for(unsigned int i=2; i*i<=n; i++)
    {
        if(n%i==0)
        {
            prost=false;
            break;
        }
    }
    return prost;
}


void RastavaBroja(int n, int &p, int &q)
{
    if(n<=0) throw std::domain_error("Broj koji se rastavlja mora biti prirodan");
    int c=n;
    int k=1;
    int qkvadrat=1;
    int ponavljanje=0;
    
    auto prostje=jelprost(n);
    
    if(prostje)
    {
        p=n;
        q=1;
        return;
    }
    
    std::vector<int> pbrojevi;
    pbrojevi.push_back(2);
    int i=2;
    for(;;)
    {
        if(c%i!=0) break;
        ponavljanje++;
        c/=i;
    }
     
     if(ponavljanje!=0 && ponavljanje%2!=0)
     {
         k*=i;
         ponavljanje--;
     }
     
     if(ponavljanje!=0 && ponavljanje%2==0)
     {
         qkvadrat=std::pow(i,ponavljanje);
     }
     
     if(c==1)
     {
         p=k;
         q=std::sqrt(qkvadrat);
         return;
     }
     
    for(int i=3; i<=n; i+=2)
    {
        bool prost=true;
        
        for(int j=0; j<pbrojevi.size() && pbrojevi.at(j)*pbrojevi.at(j)<=i; j++)
        {
            if(i%pbrojevi.at(j)==0)
            {
                prost=false;
                break;
            }
        }
        
        if(prost)
        {
            pbrojevi.push_back(i);
            ponavljanje=0;
            
            while(c!=1)
            {
                if(c%i!=0) break;
                
                    ponavljanje++;
                    c/=i;
                
            }
            
            if(ponavljanje!=0 && ponavljanje%2!=0)
            {
                k*=i;
                ponavljanje--;
            }
            
            if(ponavljanje!=0 && ponavljanje%2==0)
            {
                qkvadrat*=std::pow(i,ponavljanje);
            }
            if(c==1) break;
            
            if(jelprost(c))
            {
                p=k*c;
                q=std::sqrt(qkvadrat);
                return;
            }
        }
    }

    p=k;
    q=std::sqrt(qkvadrat);
}


int main ()
{
    int a=1, b=1;
    int n;
    std::cout<<"Unesite prirodan broj ";
    std::cin>>n;
    try
    {
	RastavaBroja(n, a, b);
	std::cout<<"\n"<<a<<" "<<b;
    }
    catch(std::domain_error e)
    {
        std::cout<<"\nIzuzetak: "<<e.what()<<"!";
    }

	return 0;
}