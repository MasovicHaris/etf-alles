/* 
    TP 16/17 (Tutorijal 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

class Krug {
	double poluprecnik;
	const double pi = 4 * atan(1);
public:
	explicit Krug(double x){ if(x <= 0 ) throw std::domain_error("Neispravan poluprecnik"); poluprecnik = x; }
	void Postavi(double x){ if(x <= 0 ) throw std::domain_error("Neispravan poluprecnik"); poluprecnik = x; }
	double DajPoluprecnik() const { return poluprecnik; }
	double DajObim() const { return 2*poluprecnik*pi; }
	double DajPovrsinu() const { return poluprecnik*poluprecnik*pi; }
	void Skaliraj(double x){ if(x <=0) throw std::domain_error("Neispravan faktor skaliranja"); poluprecnik*=x; }
	void Ispisi() const;
	
};

void Krug::Ispisi() const {
	std::cout << "R=" << DajPoluprecnik() << std::fixed << std::setprecision(5) << " O=" << DajObim() << " P=" << DajPovrsinu();
}

class Valjak {
	double visina;
	Krug baza;
public:
	explicit Valjak(double poluprecnik, double vis) : baza(poluprecnik) {
		if(vis < 0) throw std::domain_error("Neispravna visina");
		visina = vis;
	}
	void Postavi(double pp, double vis) { 
		if(pp < 0) throw std::domain_error("Neispravan poluprecnik");
		if(vis < 0) throw std::domain_error("Neispravna visina");
		baza.Postavi(pp);
		visina = vis; 
	}
	Krug DajBazu() const { return baza; }
	double DajPoluprecnikBaze() const { return baza.DajPoluprecnik(); }
	double DajVisinu() const { return visina; }
	double DajPovrsinu() const { return (2*baza.DajPovrsinu()+visina*baza.DajObim()); }
	double DajZapreminu() const { return (baza.DajPovrsinu()*visina); }
	void Skaliraj(double x){ if(x <=0) throw std::domain_error("Neispravan faktor skaliranja"); baza.Skaliraj(x); }
	void Ispisi() const;
};

void Valjak::Ispisi() const {
	std::cout << "R=" << DajPoluprecnikBaze() << std::setprecision(5) << std::fixed << " H=" << DajVisinu() << " P=" << DajPovrsinu() << " V=" << DajZapreminu();
}

int main ()
{
	std::cout << "Testiranje konstruktora: "; 
	std::cout << std::boolalpha                                     
    << std::is_default_constructible<Krug>::value << " "          
    << std::is_default_constructible<Valjak>::value << " "         
    << std::is_convertible<int, Krug>::value << std::endl; 
    
    Krug k1(4);
	std::cout<<std::fixed<<std::setprecision(5)<<k1.DajPoluprecnik() << " "
	<<std::fixed<<std::setprecision(5)<< k1.DajObim() << " "
	<<std::fixed<<std::setprecision(5)<< k1.DajPovrsinu()<< std::endl;

	Krug k2(std::sqrt(15));

	std::cout <<std::fixed<<std::setprecision(5)<<k2.DajPoluprecnik() << " " 
	<<std::fixed<<std::setprecision(5)<<k2.DajObim() << " "
	<<std::fixed<<std::setprecision(5)<<k2.DajPovrsinu()<< std::endl;
    
    Valjak v(2, 2);
  	std::cout <<std::fixed<<std::setprecision(3) <<v.DajPoluprecnikBaze() << " " 
	<<std::fixed<<std::setprecision(3) << v.DajVisinu() << " "
	<<std::fixed<<std::setprecision(3) << v.DajPovrsinu() << " "
	<<std::fixed<<std::setprecision(3) << v.DajZapreminu() << std::endl;
	
	Valjak h(std::sqrt(2), std::sqrt(3));

	std::cout << std::fixed<<std::setprecision(3)<<h.DajBazu().DajPoluprecnik() << std::endl;
	std::cout << std::fixed<<std::setprecision(3)<<h.DajPoluprecnikBaze() << std::endl;
	
	Krug k10(10);
	k1.Ispisi(); std::cout << std::endl;
	Valjak v6(10, 92);
	v6.Ispisi(); std::cout << std::endl;
	v6.DajBazu().Ispisi(); std::cout << std::endl;
	Valjak v10(k10.DajPoluprecnik(),8);
	v10.DajBazu().Ispisi(); std::cout << std::endl;
	
	std::cout << "Testiramo spešl inspektore: ";
	Krug kx(5);
	Valjak vx(1,9);
	const Krug ky(kx);                          
	const Valjak vy(vx);
	kx.Ispisi(); std::cout << std::endl;
	vy.Ispisi(); std::cout << std::endl;
	
	
	Krug kha(5);
	kha.Postavi(100);
	Valjak ve(5,5);
	ve.Postavi(10,10);
	std::cout<<kha.DajPoluprecnik()<<std::endl;
	std::cout<<ve.DajBazu().DajPoluprecnik();
	
	Krug k(5);
	k.Skaliraj(10);
	Valjak v11(5,5);
	v11.Skaliraj(10);
	std::cout<<k.DajPoluprecnik()<<std::endl;
	std::cout<<v11.DajBazu().DajPoluprecnik()<<std::endl;
	return 0;
}