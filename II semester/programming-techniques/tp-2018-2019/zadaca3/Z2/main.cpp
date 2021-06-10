//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 3, Zadatak 2
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

bool rijec(char x)
{
    if((x>='a' && x<='z') || (x>='A' && x<='Z') || (x>='0' && x<='9')) return true;
    return false;
}

std::map<std::string, std::set<int>> KreirajIndeksPojmova(std::string s)
{
    
    std::map<std::string, std::set<int>> mapa;
    
    for(int i=0; i<s.length(); i++)
    {
        int brojac=0;
        if(rijec(s[i]))
        {
            for(int j=i ;; j++)
            {
                if(!rijec(s[j])) break;
                brojac++;
            }
            
            std::string novi=s.substr(i, brojac);
            std::transform(novi.begin(), novi.end(), novi.begin(), ::tolower);
            if(novi.size()==0) continue;
            auto p=mapa.find(novi);
            if(p==mapa.end())
            {
                mapa[novi].insert(i);
            }
            else
            {
                p->second.insert(i);
            }
            i+=novi.length()-1;
        }
        
    }
    return mapa;
}

std::set<int> PretraziIndeksPojmova(std::string s, std::map<std::string, std::set<int>> mapa)
{
    for(auto it=mapa.begin(); it!=mapa.end(); it++)
    {
        std::string novi1=s;
        std::transform(novi1.begin(), novi1.end(), novi1.begin(), ::tolower);
        std::string novi2=it->first;
        std::transform(novi2.begin(), novi2.end(), novi2.begin(), ::tolower);
        if(novi1==novi2) return mapa[it->first];
    }
    throw std::logic_error("Pojam nije nadjen");
}

void IspisiIndeksPojmova(std::map<std::string, std::set<int>> mapa)
{
    for(auto it=mapa.begin(); it!=mapa.end(); it++)
    {
        std::cout<<it->first<<": ";
        int brojac=0;
        for(auto x : mapa[it->first])
        {
            if(brojac==(mapa[it->first]).size()-1) std::cout<<x;
            else std::cout<<x<<",";
            brojac++;
        }
        std::cout<<std::endl;
    }
}

int main ()
{
    std::cout<<"Unesite tekst: ";
    std::string recenica;
    std::getline(std::cin, recenica);
    
    auto m=KreirajIndeksPojmova(recenica);
    IspisiIndeksPojmova(m);
    
    while(1)
    {
        std::cout<<"Unesite rijec: ";
        std::string s;
        std::getline(std::cin, s);
        if(s==".") break;
        try
        {
            for(auto x : PretraziIndeksPojmova(s,m)) std::cout<<x<<" ";
        }
        catch(std::logic_error)
        {
            std::cout<<"Unesena rijec nije nadjena!";
        }
        std::cout<<std::endl;
    }
	return 0;
}