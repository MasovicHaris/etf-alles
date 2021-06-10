/*
    TP 16/17 (Tutorijal 9, Zadatak 2)

	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <cmath>

class Vektor3d
{
	double koordinate[3];
public:
	void Postavi(double x, double y, double z) {
	 koordinate[0] = x; koordinate[1] = y; koordinate[2] = z;
	}
	void PostaviX(double x){ koordinate[0] = x; }
	void PostaviY(double y){ koordinate[1] = y; }
	void PostaviZ(double z){ koordinate[2] = z; }
	void Ocitaj(double &x, double &y, double &z) const {
		x = DajX(); y = DajY(); z = DajZ();
	}
	void Ispisi() const {
		std::cout << "{" << DajX() << "," << DajY() << "," << DajZ() << "}";
	}
	double DajX() const { return koordinate[0]; }
	double DajY() const { return koordinate[1]; }
	double DajZ() const { return koordinate[2]; }
	double DajDuzinu() const { return std::sqrt(koordinate[0]*koordinate[0] + koordinate[1]*koordinate[1]  + koordinate[2]*koordinate[2] ); }
	Vektor3d &PomnoziSaSkalarom(double s) { koordinate[0] *= s; koordinate[1] *= s; koordinate[2] *= s; return *this; }
	Vektor3d &SaberiSa(const Vektor3d &v) { koordinate[0] += v.koordinate[0]; koordinate[1] += v.koordinate[1]; koordinate[2] += v.koordinate[2]; return *this; }
	friend Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2);
};

Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2){
	Vektor3d novi;
	novi.koordinate[0] = v1.koordinate[0] + v2.koordinate[0]; novi.koordinate[1] = v1.koordinate[1] + v2.koordinate[1]; novi.koordinate[2] = v1.koordinate[2] + v2.koordinate[2];
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
	
	std::cout << std::endl << "Saberimo ova dva vektora, pri tome kreiramo neki novi vektor h: " << std::endl;
	Vektor3d h;
	h = ZbirVektora(v, a);
	h.Ispisi();
	return 0;
}