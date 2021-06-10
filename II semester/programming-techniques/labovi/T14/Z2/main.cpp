/* 
    TP 16/17 (Tutorijal 14, Zadatak 2)
	Autotestovi by Enil Pajic.
	NOTE: ukoliko smatrate da je greska u autotestu, radite po postavci, bice uvazeno
	NOTE: vrsit ce se provjera na prepisivanje tutorijala (i kaznjavati sa oduzimanjem poena od ukupno osvojenih)
	NOTE: ovaj tutorijal se salje kao zadaca na Zamger
*/
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
class Predmet
{
	double gustina;
  public:
	Predmet(double gustina):gustina(gustina){}
	virtual double DajZapreminu() const = 0;
	double DajTezinu() const { return gustina*DajZapreminu(); }
	virtual ~Predmet(){}
};
class Lopta : public Predmet
{
	double r;
  public:
  	Lopta(double gustina, double r):Predmet(gustina),r(r){}
  	double DajZapreminu() const override { return 4*acos(-1)/3*r*r*r; }
};
class Cigla : public Predmet
{
	double a,b,c;
  public:
    Cigla(double gustina, double a, double b, double c):Predmet(gustina),a(a),b(b),c(c){}
    double DajZapreminu() const override { return a*b*c; }
};
void Obrisi(Predmet** p, int N)
{
	for(int i=0;i<N;i++) delete p[i];
	delete p;
}
int main ()
{
	std::string ime_datoteke;
	std::cout << "Unesite ime datoteke: ";
	std::getline(std::cin, ime_datoteke);
	std::ifstream ulaz(ime_datoteke);
	if(!ulaz) std::cout << "Trazena datoteka ne postoji\n";
	else
	{
		int N = 0;
		bool ok1 = false;
		std::string s;
		Predmet** niz_pok;
		try
		{
			ulaz >> N;
			ulaz.ignore(1000,'\n');
			niz_pok = new Predmet*[N];
			ok1 = true;
			for(int i=0;i<N;i++) niz_pok[i] = nullptr;
			for(int i=0;i<N;i++)
			{
				std::getline(ulaz, s);
				std::istringstream iss(s);
				if(s.size() == 0 || (s[0]!='L'&&s[0]!='C'))
				{
					std::cout << "Neispravan format datoteke";
					return 0;
				}
				char znak;
				iss >> znak;
				double g,a,b,c,r;
				if(znak == 'L')
				{
					iss >> g >> r;
					if(!iss || g<=0 || r<=0 || !iss.eof())
					{
						std::cout << "Neispravan format datoteke";
						return 0;
					}
					niz_pok[i] = new Lopta(g, r);
				}
				else 
				{
					iss >> g >> a >> b >> c;
					if(!iss || g <= 0 || a <= 0 || b <= 0 || c <= 0 || !iss.eof())
					{
						std::cout << "Neispravan format datoteke";
						return 0;
					}
					niz_pok[i] = new Cigla(g,a,b,c);
				}
			}
			std::sort(niz_pok, niz_pok+N,[](Predmet* p1, Predmet* p2){
				return p1->DajTezinu() > p2->DajTezinu();	
			});
			for(int i=0;i<N;i++)
			{
				std::cout << niz_pok[i]->DajTezinu() << std::endl;
			}
			for(int i=0;i<N;i++)
			{
				delete niz_pok[i];
			}
			delete[] niz_pok;
		}
		catch(...)
		{
			if(ok1) {
			for(int i=0;i<N;i++) delete niz_pok[i]; 
				delete niz_pok;
			}
			std::cout << "NEMA MEMORIJE!!!";
		}
	} 
	return 0;
}