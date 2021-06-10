//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 3, Zadatak 4
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stdexcept>

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
    
    std::list<std::string> imena;
    for(int i=0; i<v.size(); i++) imena.push_back(v[i]);
    
    std::vector<std::set<std::string>> razvrstani;
    razvrstani.resize(n);
    
    auto it=imena.begin();
    razvrstani[0].insert(*it);
    int br_vel=brslova(*it);
    it=imena.erase(it);
    
    std::vector<int> vel_timova;
    vel_timova.resize(n);
    
    for(int i=0; i<n; i++)
    {
        if(i<v.size()%n)
        {
            vel_timova[i]=v.size()/n+1;
            if((double(v.size()/n)-v.size()/n)>=0.5) vel_timova[i]++;   //raspodjela u timove
        }
        else
        {                                                               //vektor ljude po broju timova
            vel_timova[i]=int(v.size()/n);
            if((double(v.size()/n)-v.size()/n)>=0.5) vel_timova[i]++;   //raspodjela u timove
        }
    }
    
    int index_tima=0;
    
    while(imena.size()!=0)
    {
        br_vel--;
        if(it==imena.end()) it=imena.begin();
        for(int i=0; i<br_vel; i++)
        {
            it++;
            if(it==imena.end()) it=imena.begin();
        }
        if(razvrstani[index_tima].size()>=vel_timova[index_tima]) index_tima++;
        razvrstani[index_tima].insert(*it);
        br_vel=brslova(*it);
        it=imena.erase(it);
    }
    
    return razvrstani;
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