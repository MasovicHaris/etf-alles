/* 
    TP 16/17 (Tutorijal 10, Zadatak 4)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <iomanip>
const double pi = 4 * atan(1);

class Ugao {
	double radijani;
	void KafeAparat(double &x){
		while(x >= 2*pi) x -= 2*pi;
		while(x < 0) x += 2*pi;
	}
public:
	Ugao(double radijani = 0){ Ugao::radijani = radijani; KafeAparat(Ugao::radijani); }
	Ugao(int stepeni, int minute, int sekunde){
		radijani = (stepeni*3600 + minute*60 + sekunde) * (pi / (180*3600));
		KafeAparat(radijani);
	}
	void Postavi(double x) { radijani = x; }
	void Postavi(int stepeni, int minute, int sekunde){ 
		radijani = (stepeni*3600 + minute*60 + sekunde) * (pi / (180*3600));
		KafeAparat(radijani); 
	}
	double DajRadijane() const { return radijani; }
	void OcitajKlasicneJednacine(int &stepeni, int &minute, int &sekunde){
		int temp = radijani * (180 * 3600)/ pi;
		sekunde = temp % 60;
		temp /= 60; minute = temp % 60;
		temp /= 60; stepeni = temp;
	}
	int DajStepene() const { int a(radijani * (180*3600)/ pi); return a / 3600; }
	int DajMinute() const { int a(radijani * (180*3600)/ pi); a /= 60;  return a % 60; }
	int DajSekunde() const { int a(radijani * (180*3600)/ pi); return a % 60; }
	void Ispisi() const { std::cout << std::fixed << std::setw(6) << std::setprecision(5) << radijani; }
	void IspisiKlasicno() const {
		int stepeni, minute, sekunde;
		int temp = radijani * (180 * 3600)/ pi; 
		sekunde = temp % 60;
		temp /= 60; minute = temp % 60;
		temp /= 60; stepeni = temp;
		std::cout << stepeni << "deg " << minute << "min " << sekunde << "sec"; 
	}
	Ugao &SaberiSa(const Ugao &u){ radijani += u.radijani; KafeAparat(radijani); return *this; }
	Ugao &PomnoziSa(double x){ radijani *= x; KafeAparat(radijani); return *this; }
	
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x); 
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
	return (u1.radijani + u2.radijani);
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){ return u.radijani * x; }

int main ()
{
	int stepenm, minutaa, sekundac;
	Ugao u1, u2(21), u3(2100), u4(-455), u5 = 31, u6=-52;
	u1.OcitajKlasicneJednacine(stepenm, minutaa, sekundac);
	std::cout << stepenm << minutaa << sekundac << std::endl;
	
	u1.Ispisi(); std::cout << std::endl;
	u2.Ispisi(); std::cout << std::endl;
	u3.Ispisi(); std::cout << std::endl;
	u4.Ispisi(); std::cout << std::endl;
	u5.Ispisi(); std::cout << std::endl;
	u6.Ispisi(); std::cout << std::endl;
	u1.IspisiKlasicno(); std::cout << std::endl;
	u2.IspisiKlasicno(); std::cout << std::endl;
	u3.IspisiKlasicno(); std::cout << std::endl;
	u4.IspisiKlasicno(); std::cout << std::endl;
	u5.IspisiKlasicno(); std::cout << std::endl;
	u6.IspisiKlasicno(); std::cout << std::endl;
	
	Ugao u(1), v;          
	std::cout << u.DajRadijane() << std::endl;
	std::cout << u.DajStepene() << " " << u.DajMinute()
	<< " " << u.DajSekunde() << std::endl;
	std::cout << v.DajRadijane() << std::endl;
	std::cout << v.DajStepene() << " " << v.DajMinute()
	<< " " << v.DajSekunde() << std::endl;
	
	u.Postavi(4);
	u.Ispisi(); std::cout << std::endl;
	u.IspisiKlasicno(); std::cout << std::endl;
	v.Postavi(u.DajRadijane());
	v.Ispisi(); std::cout << std::endl;
	v.IspisiKlasicno();
	
	u.Postavi(2122, 527, 28.3062), v.Postavi(1,1,-21);
	u.Ispisi(); std::cout << std::endl;
	u.IspisiKlasicno(); std::cout << std::endl;
	v.Ispisi(); std::cout << std::endl;
	v.IspisiKlasicno();
	
	Ugao f(50, 30, 10);
	u.SaberiSa(f);
	u.IspisiKlasicno(); std::cout << std::endl;
	u.SaberiSa(v);
	u.IspisiKlasicno(); std::cout << std::endl;
	
	u.SaberiSa(f).SaberiSa(v);                    
	u.IspisiKlasicno(); std::cout << std::endl;
	u.SaberiSa(v).SaberiSa(f).Ispisi(); std::cout << std::endl;
	u.PomnoziSa(5);
	u.IspisiKlasicno(); std::cout << std::endl;
	u.PomnoziSa(-5);
	u.IspisiKlasicno(); std::cout << std::endl;
	u.PomnoziSa(-5.5);
	u.IspisiKlasicno(); std::cout << std::endl;
	u.PomnoziSa(-5.5).PomnoziSa(2);
	u.IspisiKlasicno(); std::cout << std::endl;
	
	u=ZbirUglova(u, v);
	u.IspisiKlasicno(); std::cout << std::endl;
	ZbirUglova(u, f).IspisiKlasicno(); std::cout << std::endl;
	u=ZbirUglova(u, 90);
	u.IspisiKlasicno(); std::cout << std::endl;
	
	u = ProduktUglaSaBrojem(u, 5);
	u.IspisiKlasicno(); std::cout << std::endl;
	ProduktUglaSaBrojem(u, -5).IspisiKlasicno(); std::cout << std::endl;
	
	
	return 0;
}