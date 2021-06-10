/*
    TP 16/17 (Tutorijal 9, Zadatak 1)

	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d
{
	double x, y, z;
public:
	void Postavi(double x, double y, double z) {
		Vektor3d::x = x; Vektor3d::y = y; Vektor3d::z = z;
	}
	void PostaviX(double x){ Vektor3d::x = x; }
	void PostaviY(double y){ Vektor3d::y = y; }
	void PostaviZ(double z){ Vektor3d::z = z; }
	void Ocitaj(double &x, double &y, double &z) const {
		x = Vektor3d::x; y = Vektor3d::y; z = Vektor3d::z;
	}
	void Ispisi() const {
		std::cout << "{" << x << "," << y << "," << z << "}";
	}
	double DajX() const { return x; }
	double DajY() const { return y; }
	double DajZ() const { return z; }
	double DajDuzinu() const { return std::sqrt(x * x + y * y + z * z); }
	Vektor3d &PomnoziSaSkalarom(double s) { x *= s; y *= s; z *= s; return *this; }
	Vektor3d &SaberiSa(const Vektor3d &v) { x += v.x; y += v.y; z += v.z; return *this; }
	friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2){
	Vektor3d novi;
	novi.x = v1.x + v2.x; novi.y = v1.y + v2.y; novi.z = v1.z + v2.z;
	return novi;
} 


int main ()
{
	// testiranje svega
	std::cout << "Pravimo vektor v i stavljamo koordinate sve na 1337: " << std::endl;
	Vektor3d v;
	v.Postavi(1337, 1337, 1337);
	v.Ispisi();
	
	std::cout << std::endl << "Kreiramo ponovo novi vektor a i stavljamo koordinate na 123 posebno: " << std::endl;
	Vektor3d a;
	a.PostaviX(123);
	a.PostaviY(123);
	a.PostaviZ(123);
	a.Ispisi();
	
	std::cout << std::endl << "Saberimo ova 2 vektora i imamo: " << std::endl;
	v.SaberiSa(a);
	std::cout << "Koordinate v-a: " << std::endl;
	std::cout << "X: " << v.DajX() << " ";
	std::cout << "Y: " << v.DajY() << " ";
	std::cout << "Z: " << v.DajZ() << std::endl;
	std::cout << "Duzina: " << v.DajDuzinu() << std::endl;
	
	std::cout << "Mnozimo vektor a sa 123: " << std::endl;
	a.PomnoziSaSkalarom(123);
	a.Ispisi();
	
	std::cout << std::endl << "Saberimo ova dva vektora, pri tome kreiramo neki novi vektor : " << std::endl;
	Vektor3d h;
	h = ZbirVektora(v, a);
	h.Ispisi();	
	return 0;
}