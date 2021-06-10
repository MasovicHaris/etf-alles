/* 
    TP 16/17 (Tutorijal 10, Zadatak 1)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>

class StedniRacun {
	double pare;
public:	
	StedniRacun(double z = 0){ if(z < 0) throw std::logic_error("Nedozvoljeno pocetno stanje"); pare = z; }
	void Ulozi(double z);
	void Podigni(double z){
		if(z > pare) throw std::logic_error("Transakcija odbijena");
		pare -= z;
	}
	double DajStanje() const { return pare; }
	void ObracunajKamatu(double x){
		if(x < 0) throw std::logic_error("Nedozvoljena kamatna stopa");
		double z;
		z = pare + pare*(x/100);
		pare = z;
	}
};

void StedniRacun::Ulozi(double z){
	double x = pare + z;
	if(x < 0) throw std::logic_error("Transakcija odbijena");
	pare = x;
}

int main ()
{
	StedniRacun s1=5000,s2(150),s3=0; 
	std::cout << s1.DajStanje()<<" "<<s2.DajStanje()<<" "<<s3.DajStanje() << std::endl;
	s1.Ulozi(220);
	std::cout << s1.DajStanje()<<std::endl;
	s1.Ulozi(500);
	std::cout << s1.DajStanje()<<std::endl;
	s1.Ulozi(-102);
	std::cout << s1.DajStanje()<<std::endl;
	s1.Podigni(100);
	std::cout << s1.DajStanje()<<std::endl;
	s1.Podigni(-20);
	std::cout << s1.DajStanje()<<std::endl;
	s1.Podigni(-20);
	std::cout << s1.DajStanje()<<std::endl;
	s1.ObracunajKamatu(5);
	std::cout << s1.DajStanje()<<std::endl;
	std::cout << "TEstiramo konstruktore: "; 
	std::cout << std::boolalpha << std::is_default_constructible<StedniRacun>::value << " "          
    << std::is_default_constructible<StedniRacun>::value << " "         
    << std::is_convertible<double, StedniRacun>::value << std::endl;  
	return 0;
}