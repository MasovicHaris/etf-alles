/* 
    TP 16/17 (Tutorijal 11, Zadatak 2)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>

class StedniRacun {
	double pare;
	static int zivi;
	static int mrtvi;
public:	
	StedniRacun(double z = 0){ if(z < 0) throw std::logic_error("Nedozvoljeno pocetno stanje"); pare = z; zivi++; mrtvi++; }
	void Ulozi(double z);
	void Podigni(double z){
		if(z > pare) throw std::logic_error("Transakcija odbijena");
		pare -= z;
	}
	StedniRacun(const StedniRacun &s){ pare = s.pare; zivi++; mrtvi++; }
	double DajStanje() const { return pare; }
	void ObracunajKamatu(double x){
		if(x < 0) throw std::logic_error("Nedozvoljena kamatna stopa");
		double z;
		z = pare + pare*(x/100);
		pare = z;
	}
	~StedniRacun(){ mrtvi--; }
	static int DajBrojKreiranih()  { return zivi; }
	static int DajBrojAktivnih()  { return mrtvi; }
};

void StedniRacun::Ulozi(double z){
	double x = pare + z;
	if(x < 0) throw std::logic_error("Transakcija odbijena");
	pare = x;
}

int StedniRacun::zivi = 0;
int StedniRacun::mrtvi = 0;

int main ()
{
	try {
	StedniRacun s1, s2(100);
	{ 
		StedniRacun s3(50);
	} // Nakon } s3 više ne postoji...
	std::cout << StedniRacun::DajBrojKreiranih() << " " << StedniRacun::DajBrojAktivnih(); 	// 3 2
	}catch(...){
		std::cout << "Meho hakeru?";
	}
	return 0;
}