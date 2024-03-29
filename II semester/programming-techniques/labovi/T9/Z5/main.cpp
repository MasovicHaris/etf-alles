/* 
    TP 16/17 (Tutorijal 9, Zadatak 5)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <iomanip>
#include <stdexcept>

class Sat{
	int sekundice;
	static const int d = 86400;
	static void SekundeuP(int Sekunde, int &hour, int &min, int &sec) {
		hour = Sekunde / 3600;
		min = (Sekunde % 3600) / 60;
		sec = Sekunde % 60;
	}
public:
	static bool DaLiJeIspravno(int sati, int minute, int sekunde){	// 1
		if(sati<0 || sati>23) return false;
		if(minute<0 || minute>59) return false;
		if(sekunde<0 || sekunde>59) return false;
		return true;
	}
	void Postavi(int sati, int minute, int sekunde){	// 1
		if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno vrijeme");
		int temp = sati * 3600 + minute * 60 + sekunde;
		sekundice = temp;
	}
	void PostaviNormalizirano(int sati, int minute, int sekunde){	// 1
		int sati2(sati), minute2(minute), sekunde2(sekunde);
		int temp = sati2 * 3600 + minute2 * 60 + sekunde2;
		if(temp >= d) temp = temp % d;	
		if(temp < 0) temp = d + temp % d; // negativno vrijeme
		sekundice = temp;
	}
	
	Sat &PomjeriZa(int pomak){	// 1
		int h, m, s;
		SekundeuP(sekundice, h, m, s);
		int temp = h * 3600 + m * 60 + s;
		temp += pomak;
		if(temp >= d) temp = temp % d;	
		if(temp < 0) temp = d + temp % d; // negativno vrijeme
		sekundice = temp;
		return *this;
	}
	Sat &Sljedeci() { PomjeriZa(1); return *this; }	// 1
	Sat &Prethodni() { PomjeriZa(-1);  return *this; }	// 1
	void Ispisi() const	{	// 1
		int h, m, s;
		SekundeuP(sekundice, h, m, s);
		std::cout << std::setw(2) << std::setfill('0') << h << ":";
		std::cout << std::setw(2) << std::setfill('0') << m << ":";
		std::cout << std::setw(2) << std::setfill('0') << s;
	}
	int DajSate() const { int h, m, s; SekundeuP(sekundice, h, m, s); return h; } 		// 1
	int DajMinute() const { int h, m, s; SekundeuP(sekundice, h, m, s); return m; }		// 1
	int DajSekunde() const { int h, m, s; SekundeuP(sekundice, h, m, s); return s; }		// 1
	friend int BrojSekundiIzmedju(const Sat &v1, const Sat &v2);
	static int Razmak(const Sat &v1, const Sat &v2){
		int h1, m1, s1;
		int h2, m2, s2;
		SekundeuP(v1.sekundice+0, h1, m1, s1);
		SekundeuP(v2.sekundice+0, h2, m2, s2);
		return (h1 * 3600 + m1 * 60 + s1) - (h2 * 3600 + m2 * 60 + s2);
	}
};


int BrojSekundiIzmedju(const Sat &v1, const Sat &v2){
	return v1.sekundice - v2.sekundice;
}

int main ()
{
	Sat v;
	v.Postavi(10,10,10);
	std::cout << "Halo momak jel ispravno: " << v.DaLiJeIspravno(10,10,10) << std::endl;
	try {
		v.Postavi(24,10,10);
		std::cout << "Sati: " << v.DajSate() << std::endl;
		std::cout << "Minute: " << v.DajMinute() << std::endl;
		std::cout << "Sekunde: " << v.DajSekunde() << std::endl;
		}catch(...){
		std::cout << "Selo gori a baba se češlja!" << std::endl;
	}
	Sat h;
	std::cout << "Postavljamo h na 00:00:-01 " << std::endl;
	h.PostaviNormalizirano(0,0,-1); h.Ispisi();
	
	std::cout << "Pomjeramo za 1sec " << std::endl;
	v.Sljedeci(); v.Ispisi();
	std::cout << "Pomjeramo za 1sec nazad " << std::endl;
	v.Prethodni(); v.Ispisi();
	std::cout << "Pomjeramo za 10sec " << std::endl;
	v.PomjeriZa(10); v.Ispisi();
	
	Sat v1, v2;
	static Sat v3, v4;
	std::cout << "Broj sekundi izmedju v1 i v2 sa BrojSekundiIzmedju: "<< std::endl;
	v1.Postavi(10,10,15);
	v2.Postavi(5,5,5);
	std::cout << BrojSekundiIzmedju(v1,v2) << std::endl;
	
	v3.Postavi(10,10,15);
	v4.Postavi(5,5,5);
	std::cout << "Broj sekundi izmedju v3 i v4 sa Razmak: "<< std::endl;
	std::cout << Sat::Razmak(v3,v4);
	return 0;
}