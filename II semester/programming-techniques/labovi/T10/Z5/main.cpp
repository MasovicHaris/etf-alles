/* 
    TP 16/17 (Tutorijal 10, Zadatak 5)
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
	int step, min, s;
	void KafeAparat(double &x){
		while(x >= 2*pi) x -= 2*pi;
		while(x < 0) x += 2*pi;
	}
	void Kontra(double &radijan, int stepen, int minuta, int sekunda){
		radijan = (stepen*3600 + minuta*60 + sekunda) * (pi / (180*3600));
	}
	void Kontra2(double radijan, int &stepen, int &minuta, int &sekunda){
		int temp = radijan * (180 * 3600)/ pi;
		sekunda = temp % 60;
		temp /= 60; minuta = temp % 60;
		temp /= 60; stepen = temp;
	}
public:
	Ugao(double radijani = 0){ KafeAparat(radijani); Kontra2(radijani, step, min, s); }		// 1
	Ugao(int stepeni, int minute, int sekunde){		
		double radijani; Kontra(radijani, stepeni, minute, sekunde);
		KafeAparat(radijani);
		Kontra2(radijani, step, min, s);
	}
	void Postavi(double x) { Kontra2(x, step, min, s);  }	// 1
	void Postavi(int stepeni, int minute, int sekunde){ 	// 1
		double radijani;
		Kontra(radijani, stepeni, minute, sekunde);
		KafeAparat(radijani); 
		Kontra2(radijani, step, min, s);
	}
	double DajRadijane() const { 	// 1
		return ((step*3600 + min*60 + s) * (pi / (180*3600)));
	}
	void OcitajKlasicneJednacine(int &stepeni, int &minute, int &sekunde){		// 1
		step = stepeni; min = minute; s = sekunde;
	}
	int DajStepene() const { return step; }
	int DajMinute() const { return min; }
	int DajSekunde() const { return s; }
	void Ispisi() const { 
			double radijani; 
			radijani = (step*3600 + min*60 + s) * (pi / (180*3600));
			std::cout << std::fixed << std::setw(6) << std::setprecision(5) << radijani; 
		
	}
	void IspisiKlasicno() const {
		std::cout << step << "deg " << min << "min " << s << "sec"; 
	}
	Ugao &SaberiSa(const Ugao &u){ 
		step += u.step; min += u.min; s += u.s;
		double radijani;
		Kontra(radijani, step, min, s);
		KafeAparat(radijani);
		Kontra2(radijani, step, min, s);
		return *this; 
	}
	Ugao &PomnoziSa(double x){ 
		double radijani;
		Kontra(radijani, step, min, s);
		radijani *= x; 
		KafeAparat(radijani);
		Kontra2(radijani, step, min, s);
		return *this;
	}
	
	friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
	friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x); 
};

Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
	return {u1.step+u2.step, u1.min+u2.min, u1.s+u2.s};
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){ 
	Ugao z(0);
	double radijani;
	radijani = (u.step*3600 + u.min*60 + u.s) * (pi / (180*3600));
	radijani *= x;
	int temp = radijani * (180 * 3600)/ pi;
	int stepen, minuta, sekunda;
	
	sekunda = temp % 60;
	temp /= 60; minuta = temp % 60;
	temp /= 60; stepen = temp;
	z.Postavi(stepen, minuta, sekunda);
	return z;
}

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