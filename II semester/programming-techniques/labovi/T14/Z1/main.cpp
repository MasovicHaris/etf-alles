/* 
    TP 16/17 (Tutorijal 14, Zadatak 1)
	Autotestovi by Enil Pajic.
	NOTE: ukoliko smatrate da je greska u autotestu, radite po postavci, bice uvazeno
	NOTE: vrsit ce se provjera na prepisivanje tutorijala (i kaznjavati sa oduzimanjem poena od ukupno osvojenih)
	NOTE: ovaj tutorijal se salje kao zadaca na Zamger
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
class Datum{
	int d,m,g;
	public:
	Datum(int d,int m,int g):d(d),m(m),g(g)
	{
		int niz[]={31,28,31,30,31,30,31,31,30,31,30,31};
		if(g%4 == 0 && !(g%100==0 && g%400!=0)) niz[1]++;
		if(g < 0 || m < 1 || m > 12 || d < 1 || d > niz[m-1])
			throw std::string("NE VALJA");
	}
	int DajD(){return d;}
	int DajM(){return m;}
	int DajG(){return g;}
};
struct Student
{
	std::string ime;
	int indeks;
	Datum dat;
	std::vector<int> ocjene;
	public:
	Student(std::string ime, int indeks, Datum dat, std::vector<int> ocjene):
	ime(ime),indeks(indeks),dat(dat),ocjene(ocjene)
	{
		if(indeks < 0) throw std::string("NE VALJA");
		for(auto e: ocjene) if(e < 5 || e > 10) throw std::string("NE VALJA");
	}
	double DajProsjek()
	{
		double suma = 0;
		int br = 0;
		for(auto e: ocjene) if(e != 5) {suma += e; br++;}
		if(br == 0) return 5;
		return suma / br;
	}
	int DajIndeks() { return indeks; }
	friend std::ostream& operator<<(std::ostream& out, Student st);
};
std::ostream& operator<<(std::ostream& out, Student st)
{
	out << std::left << std::setw(30) << st.ime;
	out << std::left << std::setw(10) << st.indeks;
	std::string s=std::to_string(st.dat.DajD())+"/"+std::to_string(st.dat.DajM())+"/"+std::to_string(st.dat.DajG());
	out << std::left << std::setw(20) << s;
	out << std::left << std::setw(10) << std::setprecision(2) << std::fixed << st.DajProsjek();
	return out;
}
int main ()
{
    std::ifstream ulaz("STUDENTI.TXT");
    if(!ulaz)
    {
    	std::cout << "Datoteka STUDENTI.TXT ne postoji!\n";
    }
    else
    {
    	std::vector<Student> v;
    	std::string ime;
    	int indeks,d,m,g,ocjena;
    	char z1, z2;
    	std::vector<int> ocjene;
    	bool neispravan_format = false;
    	for(;;)
    	{
  			std::getline(ulaz, ime);
  			if(ulaz.eof()) break;
  			ulaz >> indeks;
  			if(!ulaz) { neispravan_format = true; break; }
 			ulaz >> d >> z1 >> m >> z2 >> g;
 			if(!ulaz || z1 != z2 || z1 != '/') { neispravan_format = true; break; }
 			for(;;)
    		{
    			ulaz >> ocjena;
    			z1 = ulaz.get();
    			if(!ulaz)
    			{
    				if(ulaz.eof())
    				{
    					ocjene.push_back(ocjena);
    					break;
    				}
    				else
    				{
    					neispravan_format = true;
    					break;
    				}
    			}
    			else
    			{
    				if(z1 == '\n') { ocjene.push_back(ocjena); break; }
    				else if(z1 == ',') { ocjene.push_back(ocjena); }
    				else { neispravan_format = true; break; }
    			}
    		}
    		if(ulaz.bad())
    		{
    			std::cout << "Problemi pri citanju datoteke STUDENTI.TXT";
    			return 0;
    		}
    		else if(neispravan_format)
    		{
    			std::cout << "Neispravan format datoteke STUDENTI.TXT\n";
    			return 0;
    		}
    		else
    		{
    			try
    			{
    				v.push_back(Student(ime, indeks, {d,m,g}, ocjene));
    			}
    			catch(...)
    			{
    				std::cout << "Neispravan format datoteke STUDENTI.TXT\n";
    				return 0;
    			}
    			if(ulaz.eof()) break;
    		}
    		ocjene.clear();
    	}
    	std::sort(v.begin(),v.end(),[](Student s1, Student s2){
    		return s1.DajProsjek() - s2.DajProsjek() > 1e-9 || (fabs(s1.DajProsjek()-s2.DajProsjek()) < 1e-9 && s1.DajIndeks() < s2.DajIndeks());	
    	});
    	std::ofstream out("IZVJESTAJ.TXT");
    	out << std::setw(30) << std::left << "Student";
    	out << std::setw(10) << std::left << "Indeks";
    	out << std::setw(20) << std::left << "Datum rodjenja";
    	out << std::setw(10) << std::left << "Prosjek";
    	out << std::endl;
    	out << std::setw(30) << std::left << "-------";
    	out << std::setw(10) << std::left << "------";
    	out << std::setw(20) << std::left << "--------------";
    	out << std::setw(30) << std::left << "-------";
    	out << std::endl;
    	for(auto& e: v)
    	{
    		out << e;
    		out << std::endl;
    	}
    }
	return 0;
}
