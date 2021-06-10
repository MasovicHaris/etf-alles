//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <string>
#include <iostream>
#include <algorithm>
#include <deque>
#include <type_traits>
template<typename itertip>
bool ZaSve(itertip p1, itertip p2, bool (*f)(typename std::remove_reference<decltype(*p1)>::type))
{
	if(std::find_if_not(p1, p2, f)!=p2) return false;
	return true;
}

template<typename itertip>
bool MakarJedan(itertip p1, itertip p2, bool (*g)(typename std::remove_reference<decltype(*p1)>::type))
{
	if(std::find_if(p1, p2, g)!=p2) return true;
	return false;
}

template<typename itertip>
auto Akumuliraj(itertip p1, itertip p2, auto (*h)(typename std::remove_reference<decltype(*p1)>::type, typename std::remove_reference<decltype(*p1)>::type)->typename std::remove_reference<decltype(*p1)>::type, typename std::remove_reference<decltype(*p1)>::type a) ->typename std::remove_reference<decltype(*p1)>::type
{
	if(p1==p2) return a;
	
	while(p1<p2)
	{
		a=h(a,*p1);
		p1++;
	}
	return a;
}

int main ()
{
	std::cout<<"Unesite string: ";
	std::string recenica;
	std::getline (std::cin, recenica);
	
	auto a=ZaSve(recenica.begin(), recenica.end(), [](char p)->bool{
	if((p>='a' && p<='z') || (p>='A' && p<='Z') || (p>='0' && p<='9')) return true;
	return false;
	});
	
	if(a) std::cout<<"Uneseni string sadrzi samo slova i cifre";
	else if(!a) std::cout<<"Uneseni string sadrzi i druge znakove osim slova i cifara";
	
	int niz[10];
	std::cout<<"\nUnesite niz od 10 brojeva: ";
	std::for_each(std::begin(niz), std::end(niz), [](int &x){std::cin>>x;});
	
	auto b=MakarJedan(std::begin(niz), std::end(niz), [](int x)->bool{
		
		if(x==0) return true;
		int suma=0;
		int n=std::abs(x);
		int y=x;
		
		while(n!=0)
		{
			suma+=std::abs(n%10);
			n/=10;
		}
	
		if(std::abs(y%suma)==0) return true;
		
		return false;

	});
	
	if(b) std::cout<<"U nizu ima brojeva djeljivih sa sumom svojih cifara";
	else if(!b) std::cout<<"U nizu nema brojeva djeljivih sa sumom svojih cifara";
	
	std::cout<<"\nUnesite dek od 10 elemenata: ";

	std::deque<double> dek(10);
	std::for_each(dek.begin(), dek.end(), [](double &x){std::cin>>x;});
	
	auto c=Akumuliraj(dek.begin(), dek.end(), [](double x, double y)->double{return x+y;}, 0.0);
	std::cout<<"\nSuma deka: "<<c;
	
	auto d=Akumuliraj(dek.begin(), dek.end(), [](double x, double y)->double{return x*y;}, 1.0);
	std::cout<<"\nProdukt deka: "<<d;
	
	auto f=Akumuliraj(dek.begin(), dek.end(), [](double x, double y)->double{if(x>=y) return x; else return y;}, dek[0]);
	std::cout<<"\nNajveci elemenat deka: "<<f;
	
	auto k=Akumuliraj(dek.begin(), dek.end(), [](double x, double y)->double{if(x>=y) return y; else return x;}, dek[0]);
	std::cout<<"\nNajmanji elemenat deka: "<<k;
	
	return 0;
}