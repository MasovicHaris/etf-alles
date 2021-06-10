//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <new>
#include <string>
#include <iostream>
#include <algorithm>

bool KriterijSortiranja(std::string x, std::string y)
{
	if(x.size()==y.size())
	{
		for(int i=0; i<x.size(); i++)
		{
			x.at(i)=std::toupper(x.at(i));
		}
		for(int i=0; i<y.size(); i++)
		{
			y.at(i)=std::toupper(y.at(i));
		}
		
		return y>x;
	}
	
	return y.size()>x.size();
}
void SortirajPoDuzini(std::string *q, int n)
{
    std::sort(q, q+n, KriterijSortiranja);
}

bool PretraziBinarno(std::string *q, int n, std::string rijec)
{
	if(std::binary_search(q, q+n, rijec, KriterijSortiranja))	return true;
	return false;
}

int main ()
{
    std::cout<<"Unesite broj rijeci: ";
    int n;
    std::cin>>n;
    
	std::string *p=nullptr;
	
	p=new std::string[n];
	
	std::string ime;
	std::cout<<"Unesite rijeci: ";
	for(int i=0; i<n; i++)
	{
	    std::cin>>ime;
	    p[i]=ime;
	}
	
	SortirajPoDuzini(p,n);
	std::cout<<"Sortirane rijeci: ";
	
	for(int i=0; i<n; i++)
	{
	    std::cout<<p[i]<<" ";
	}
	
	std::cout<<"\nUnesite rijec za pretragu: ";
	std::cin>>ime;
	
	auto bulean=PretraziBinarno(p,n,ime);
	if(bulean) 
	{
		std::cout<<"Rijec '"<<ime<<"' se nalazi u nizu.";
		delete[] p;
		return 0;
	}
	else
	{
		std::cout<<"Rijec '"<<ime<<"' se ne nalazi u nizu.";
	    delete[] p;
	    return 0;
	}
}