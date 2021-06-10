//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <vector>
#include <deque>
#include <iostream>
#include <type_traits>
template<typename tip1>
auto duplikati(tip1 p1, tip1 p2) -> std::vector<typename std::remove_reference<decltype(*p1)>::type>
{

    std::vector<typename std::remove_reference<decltype(*p1)>::type> veka;
    for(; p1<p2; p1++)
    {
        veka.push_back(*p1);
    }
    
       for(int i=0; i<int(veka.size()); i++)
       {
           for(int j=i+1; j<int(veka.size()); j++)
           {
               if(veka.at(i)==veka.at(j))
               {
                   for(int k=j; k<int(veka.size()-1); k++)
                   {
                       veka.at(k)=veka.at(k+1);
                   }
                   veka.resize(veka.size()-1);
               }
           }
       }
       
       return veka;

}

template<typename tip1, typename tip2, typename tip3>
tip3 SimetricnaRazlikaBlokova(tip1 p1, tip1 p2, tip2 p3, tip2 p4, tip3 p5)
{
    
    auto skup1=duplikati(p1, p2);
    auto skup2=duplikati(p3, p4);
    std::vector<decltype(skup1.at(0)+skup2.at(0))> veka;
    for(int i=0; i<skup1.size(); i++)
    {
        bool dobar=true;
        for(int j=0; j<skup2.size(); j++)
        {
            if(skup1.at(i)==skup2.at(j))
            {
                dobar=false;
                break;
            }
        }
        if(dobar)
        {
            veka.push_back(skup1.at(i));
        }
        
    }
    
    for(int i=0; i<skup2.size(); i++)
    { 
        bool dobar=true;
        for(int j=0; j<skup1.size(); j++)
        {
            if(skup2.at(i)==skup1.at(j))
            {
                dobar=false;
                break;
            }
        }
        if(dobar)
        {
            veka.push_back(skup2.at(i));
        }
    }
    
    for(int i=0; i<veka.size(); i++)
    {
        *p5=veka.at(i);
        p5++;
    }
    
    return p5;
    
}

int main ()
{
    int niz[100];
    int n;
    std::cout<<"Unesite broj elemenata niza ";
    std::cin>>n;
    std::cout<<"\nUnesite elemente niza ";
    int broj=0;
    for(int i=0; i<n; i++)
    {
        std::cin>>broj;
        niz[i]=broj;
    }
    
    std::deque<int> dek;
    int elemdek;
    std::cout<<"\nUnesite broj elemenata deka ";
    std::cin>>elemdek;
    std::cout<<"\nUnesite elemente deka ";
    
    for(int i=0; i<elemdek; i++)
    {
        std::cin>>broj;
        dek.push_back(broj);
    }

  
    auto a=niz[0]+dek[0];
    std::vector<decltype(0+niz[0]+dek[0])> vec(200,a);
    std::vector<decltype(0+niz[0]+dek[0])>::iterator p5=vec.begin();
    auto k=SimetricnaRazlikaBlokova(niz, niz+n,dek.begin(), dek.end(), p5);
   
    vec.resize(k-vec.begin());
    if(vec.size()==0)
    {
        std::cout<<"\nBlokovi nemaju simetricnu razliku";
        return 0;
    }
    std::cout<<"\nSimetricna razlika blokova je: ";
    for(int i=0; i<int(vec.size()); i++)
    {
        std::cout<<vec.at(i)<<" ";
    }
    return 0;
}