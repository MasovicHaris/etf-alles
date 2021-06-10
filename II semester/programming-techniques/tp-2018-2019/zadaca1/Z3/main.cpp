//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
typedef std::vector<std::vector<int>> matrica;

int razmak(matrica mat1)
{

	int brojcifri=0;
	int temp=0;

	for(int i=0; i<mat1.size(); i++)
	{
		for(int j=0; j<mat1.at(i).size(); j++)
		{
			int a=mat1.at(i).at(j);
			brojcifri=0;
			if(a<0) brojcifri++;
			while(a!=0)
			{
				a/=10;
				brojcifri++;
			}
			if(brojcifri>temp) temp=brojcifri;
		}
	}

	return temp;
}



matrica KroneckerovProizvod(matrica mat1, matrica mat2)
{
	
	bool korektna1=true, korektna2=true;

	
	for(int p=0; p<mat1.size(); p++)
	{
		if(mat1.at(p).size()!=mat1.at(0).size() || mat1.at(p).size()==0) 
		{
			korektna1=false;
			break;
		}
	}
	for(int p=0; p<mat2.size(); p++)
	{
		if(mat2.at(p).size()!=mat2.at(0).size() || mat2.at(p).size()==0)
		{
			korektna2=false;
			break;
		}
	}
	
	if(!korektna1 && !korektna2) throw std::domain_error("Parametri nemaju formu matrice");
	if(!korektna1 && korektna2) throw std::domain_error("Prvi parametar nema formu matrice");
	if(korektna1 && !korektna2) throw std::domain_error("Drugi parametar nema formu matrice");

	int duzina=mat1.size()*mat2.size();

	matrica matra(duzina, std::vector<int> (0) );
	
	if(duzina==0) return matra; 
	
	
	int k=0;  //pocetna vrijednost reda prve matrice
	int i=0;  //pocetna vrijednost reda druge matrice
	int brojac=0;
	for(;;) 		//beskonacna petlja
	{
		for(int j=0; j<mat1.at(i).size(); j++)  //kako je i=0 u prvoj iteraciji ovo ce uzimati redom elemente prvog reda matrice br 1.
		{
			for(;;)
			{
				
				for(int l=0; l<mat2.at(k).size(); l++) //kako je k=0 u prvoj iteraciji ovo ce uzimati redom elemente prvog reda matrice br 2.
				{
					
					int elem=mat1.at(i).at(j)*mat2.at(k).at(l);  //one se mnoze i ispisuje se prvi red kronekerove matrice
					matra.at(brojac).push_back(elem);
				}
				
				break;  //beskonacna petlja se breaka 
			}
			
		}
		k++;
		brojac++;// k++ da bi presli u drugi red druge matrice
		if(k==mat2.size())			// ako je k doso do kraja druge matrice, tj ako se svaki element prvog reda matrice 1, pomnozio sa svim elementima
		{							// matrice 2, i++ (da se predje u drugi red matrice 1) i k=0 (k se vrati na nulu da bi se opet svaki element drugog reda matrice 1)
			i++;					// mogao pomnoziti sa svim elementima druge matrice
			k=0;
		}
		if(i==mat1.size()) break;		// te ako i dodje do kraja prve matrice to znaci da je kronekerov proizvod okoncan nadamo se uspjesno hehe :D
	}
	return matra;
}



int main ()
{
	std::cout<<"Unesite dimenzije prve matrice:";
	int red1, kol1;
	std::cin>>red1>>kol1;
	
	std::cin.clear();
	std::cin.ignore(100000,'\n');
	
	std::cout<<std::endl;
	matrica mat1(red1, std::vector<int>(kol1, 0));
	std::cout<<"Unesite elemente prve matrice:";
	int elem;
	
	for(int i=0; i<mat1.size(); i++)
	{
		for(int j=0; j<mat1.at(i).size(); j++)
		{
			std::cin>>elem;
			mat1.at(i).at(j)=elem;
			
		}
	
	}
	
	std::cin.clear();
	std::cin.ignore(100000,'\n');
	
	std::cout<<"\nUnesite dimenzije druge matrice:";
	int red2, kol2;
	std::cin>>red2>>kol2;
	
	std::cin.clear();
	std::cin.ignore(100000,'\n');
	
	matrica mat2(red2, std::vector<int>(kol2));
	std::cout<<"\nUnesite elemente druge matrice:";
	for(int i=0; i<mat2.size(); i++)
	{
		for(int j=0; j<mat2.at(i).size(); j++)
		{
			std::cin>>elem;
			mat2.at(i).at(j)=elem;
		}
	}
	
	std::cin.clear();
	std::cin.ignore(100000,'\n');
	try
	{		std::cout<<"\nNjihov Kroneckerov proizvod glasi:\n";
			auto k=KroneckerovProizvod(mat1, mat2);
			int spejs=razmak(k);
			for(int i=0; i<k.size(); i++)
			{
				for(int j=0; j<k.at(i).size(); j++)
				{
					std::cout<<std::right<<std::setw(spejs+1)<<k.at(i).at(j);
				}
				std::cout<<"\n";
			}
	}
	catch(std::domain_error izuzetak)
	{
		std::cout<<izuzetak.what();
	}
	
    return 0;
}