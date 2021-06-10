/*
    TP 16/17 (Tutorijal 13, Zadatak 1)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>
const double pi = 4 * atan(1);

class Lik {
public:
	virtual void IspisiSpecificnosti() const = 0;
	virtual double DajObim() const = 0;
	virtual double DajPovrsinu() const = 0;
	virtual ~Lik() { }
	virtual void Ispisi() const { }
};

class Krug : public Lik {
	double poluprecnik;
public:
	Krug(double x) {
		if(x <= 0) throw std::domain_error("Neispravni parametri");
		poluprecnik = x;
	}
	void IspisiSpecificnosti() const {
		std::cout << "Krug poluprecnika " << poluprecnik << std::endl;
	}
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << "Obim: "  << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
	double DajObim() const {
		return 2 * poluprecnik * pi;
	}
	double DajPovrsinu() const {
		return poluprecnik * poluprecnik * pi;
	}
};

class Pravougaonik : public Lik {
	double a, b;
public:
	Pravougaonik(double x, double y) {
		if(x <= 0 || y <= 0) throw std::domain_error("Neispravni parametri");
		a = x;
		b = y;
	}
	void IspisiSpecificnosti() const {
		std::cout << "Pravougaonik sa stranicama duzine " << a << " i " << b << std::endl;
	}
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << "Obim: "  << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
	double DajObim() const {
		return 2*(a+b);
	}
	double DajPovrsinu() const {
		return a*b;
	}
};

class Trougao : public Lik {
	double x, y, z;
public:
	Trougao(double a, double b, double c) {
		bool hehe(a>0 && b>0 && c>0 && ((a+b)>c && (a+c)>b && (c+b)>a));
		if(!hehe) throw std::domain_error("Neispravni parametri");
		 x = a;
		 y = b;
		 z = c;
	}
	void IspisiSpecificnosti() const {
		std::cout << "Trougao sa stranicama duzine " << x << ", " << y << " i " << z << std::endl;
	}
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout << "Obim: "  << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
	double DajObim() const {
		return x + y + z;
	}
	double DajPovrsinu() const {
		double s(DajObim() / 2);
		return std::sqrt(s * (s - x) * (s - y) * (s - z)) ;
	}

};

int main ()
{
	int n;
	std::cout << "Koliko zelite likova: ";
	std::cin >> n;
	std::vector<std::shared_ptr<Lik>> vektorpokazivaca(n);
	for(int i=0; i < n; ){
		try {
		std::cin.ignore(10000, '\n');
		std::cout << "Lik " << i+1 <<": ";
		char q;
		q = std::cin.get();
		double x,y,z,broj;
		switch(q){
			case 'K': 
			std::cin >> broj;
			if(!std::cin || std::cin.peek()!='\n'){ std::cout << "Pogresni podaci, ponovite unos!" << std::endl;  continue; }
			vektorpokazivaca[i] = std::make_shared<Krug>(Krug(broj)); i++;
			break;
			
			case 'P':
			char e;
			std::cin >> x >> e >> y;
			if(!std::cin || std::cin.peek()!='\n'){ std::cout << "Pogresni podaci, ponovite unos!" << std::endl;;  continue; }
			vektorpokazivaca[i] = std::make_shared<Pravougaonik>(Pravougaonik(x, y)); i++;
			break;
			
			case 'T':
			char r ;
			std::cin >> x >> r >> y >> r >> z;
			if(!std::cin || std::cin.peek()!='\n'){ std::cout << "Pogresni podaci, ponovite unos!" << std::endl;  continue; }
			vektorpokazivaca[i] = std::make_shared<Trougao>(Trougao(x,y,z)); i++;
			break;
			default:
			std::cout << "Pogresni podaci, ponovite unos!" << std::endl;  continue;
			break;
		}
		}catch(std::domain_error exec){
			std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
		}
	}
	std::cout << std::endl;
	for(auto x : vektorpokazivaca) x->Ispisi();
	return 0;
}