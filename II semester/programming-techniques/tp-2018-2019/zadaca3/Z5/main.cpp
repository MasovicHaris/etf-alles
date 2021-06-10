//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stdexcept>

struct Dijete
{
    std::string ime;
    Dijete *sljedeci;
};

int brslova(std::string s)
{
    int brojac=0;
    for(int i=0; i<s.size(); i++)
    {
        if((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i]>='0' && s[i]<='9')) brojac++;
    }
    return brojac;
}

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> v, int n)
{
    
    if(n<1 || n>v.size()) throw std::logic_error("Razvrstavanje nemoguce");
    
    std::vector<std::set<std::string>> imena;
    imena.resize(n);
    
    Dijete *pocetno(nullptr), *prethodno;
    
    for(int i=0; i<v.size(); i++)
    {
        Dijete *novi(new Dijete);
        novi->ime=v[i];
        novi->sljedeci=nullptr;
        if(!pocetno) pocetno=novi;
        else prethodno->sljedeci=novi;
        prethodno=novi;
    }
    
    Dijete *prvo=pocetno->sljedeci;
    
    int velicina=brslova(pocetno->ime);
    
    imena[0].insert(pocetno->ime);
    delete pocetno;
    prethodno->sljedeci=prvo;
    
    std::vector<int> vel_timova;
    vel_timova.resize(n);
    
    for(int i=0; i<n; i++)
    {
        if(i<v.size()%n)
        {
            vel_timova[i]=v.size()/n+1;
            if((double(v.size()/n)-v.size()/n)>0.5) vel_timova[i]++;
        }
        else
        {
            vel_timova[i]=v.size()/n;
            if((double(v.size()/n)-v.size()/n)>0.5) vel_timova[i]++;
        }
    }
    
    int index=0;
    velicina--;
    auto poslije=prvo->sljedeci;
    
    for(int i=0; i<v.size()-1; i++)
    {
        for(int j=0; j<velicina-1; j++)
        {
            prvo=poslije;
            poslije=prvo->sljedeci;
        }
        if(imena[index].size()>=vel_timova[index]) index++;
        velicina=brslova(poslije->ime);
        imena[index].insert(poslije->ime);
        prvo->sljedeci=poslije->sljedeci;
        poslije->sljedeci=nullptr;
        delete poslije;
        if(i!=v.size()-2) poslije=prvo->sljedeci;
        
    }
    
    return imena;
    
    
}






int main ()
{
    std::cout<<"Unesite broj djece: ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite imena djece: ";
    std::cin.ignore(10000,'\n');
    std::vector<std::string> veka;
    std::string pomocni;
    for(int i=0; i<n; i++)
    {
        std::getline(std::cin, pomocni);
        veka.push_back(pomocni);
    }
    
    std::cout<<"\nUnesite broj timova: ";
    int m;
    std::cin>>m;
    try
    {
        auto skup=Razvrstavanje(veka, m);
            for(int i=0; i<skup.size(); i++)
            {
                std::cout<<"Tim "<<i+1<<": ";
                int brojac=0; 
                for(auto x : skup[i])
                {
                    if(brojac!=skup[i].size()-1) std::cout<<x<<", ";
                    else std::cout<<x;
                    brojac++;
                }
                std::cout<<std::endl;
            }
    	return 0;
    }
    catch(std::logic_error a)
    {
        std::cout<<"Izuzetak: "<<a.what();
    }
    
}