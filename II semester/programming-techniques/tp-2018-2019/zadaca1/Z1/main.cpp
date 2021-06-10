//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <iostream>
#include <vector>
#include <cmath>
std::vector<int> PalindromskaOtpornost(std::vector<int> v)
{
	int brojac=0;
	std::vector<int> palindrom;
	for(int i=0; i<v.size(); i++)
	{
		int c=abs(v.at(i));
		int broj=c;
		int suma;
		brojac=0;
		do
		{
			suma=0;
			while(c>0)
				{
					suma=suma*10 + c%10;
					c/=10;
				}
				if(suma==broj)
				{
					palindrom.push_back(brojac);
					break;
				}
				else
				{
					c=broj+suma;
					broj=c;
					brojac++;
				}
				
		}while(1);
		
	}
	return palindrom;
}


int main ()
{
	
	std::cout<<"Koliko zelite unijeti elemenata: "; //Unos elemenata u vektor
	int n;
	int elem;
	std::cin>>n;
	std::vector<int> veka(n);
	std::cout<<"Unesite elemente: ";
	for(int i=0; i<n; i++)
	{
		std::cin>>elem;
		veka.at(i)=elem;
	}
	
	std::cin.clear();
	std::cin.ignore(100000,'\n');
	
	
	auto p=PalindromskaOtpornost(veka);
	
	for(int i=0; i<p.size(); i++)
	{
		std::cout<<"Palindromska otpornost broja "<<veka.at(i)<<" iznosi "<<p.at(i)<<"\n";
	}

}