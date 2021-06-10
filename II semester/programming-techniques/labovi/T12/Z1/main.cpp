/*
    TP 16/17 (Tutorijal 12, Zadatak 1)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <stdexcept>

class Sat
{
	int h, m, s;
	static const int d = 86400;
	static void SekundeuP(int Sekunde, int &hour, int &min, int &sec) {
		hour = Sekunde / 3600;
		min = (Sekunde % 3600) / 60;
		sec = Sekunde % 60;
	}
public:
	Sat() {
		h = m = s = 0;
	}
	Sat(int sati, int minute, int sekunde) {	// 1
		PostaviNormalizirano(sati, minute, sekunde);
	}
	static bool DaLiJeIspravno(int sati, int minute, int sekunde) {	// 1
		if(sati<0 || sati>23) return false;
		if(minute<0 || minute>59) return false;
		if(sekunde<0 || sekunde>59) return false;
		return true;
	}
	void Postavi(int sati, int minute, int sekunde) {	// 1
		if(!DaLiJeIspravno(sati, minute, sekunde)) throw std::domain_error("Neispravno vrijeme");
		h = sati;
		m = minute;
		s = sekunde;
	}
	void PostaviNormalizirano(int sati, int minute, int sekunde) {	// 1
		int sati2(sati), minute2(minute), sekunde2(sekunde);
		int temp = sati2 * 3600 + minute2 * 60 + sekunde2;
		if(temp >= d) temp = temp % d;
		if(temp < 0) temp = d + temp % d; // negativno vrijeme
		SekundeuP(temp, h, m, s);
	}
	Sat &operator ++() {
		int temp = h * 3600 + m * 60 + s;
		temp++;
		SekundeuP(temp, h, m, s);
		return *this;
	}
	Sat operator ++(int) {
		Sat novi(*this);
		++(*this);
		return novi;
	}
	Sat &operator --() {
		int temp = h * 3600 + m * 60 + s;
		temp--;
		SekundeuP(temp, h, m, s);
		return *this;
	}
	Sat operator --(int) {
		Sat novi(*this);
		--(*this);
		return novi;
	}


	Sat &operator +=(int pomak) {	// 1
		int temp = h * 3600 + m * 60 + s;
		temp += pomak;
		if(temp >= d) temp = temp % d;
		if(temp < 0) temp = d + temp % d; // negativno vrijeme
		SekundeuP(temp, h, m, s);
		return *this;
	}

	Sat &operator -=(int pomak) {
		return *this += -pomak;

	}
	friend std::ostream& operator << (std::ostream &ispisi, const Sat &s) {
		ispisi.width(2);
		ispisi.fill('0');
		ispisi << s.DajSate() << ":";
		ispisi.width(2);
		ispisi.fill('0');
		ispisi << s.DajMinute() << ":";
		ispisi.width(2);
		ispisi.fill('0');
		return ispisi << s.DajSekunde();
	}
	friend int operator -(const Sat &v1, const Sat &v2) {
		return int(v1.h * 3600 + v1.m * 60 + v1.s) - (v2.h * 3600 + v2.m * 60 + v2.s);
	}
	Sat operator +(int pomak);
	Sat operator -(int pomak);
	Sat operator +=(int pomak) const;
	Sat operator -=(int pomak) const;

	int DajSate() const {
		return h;    // 1
	}
	int DajMinute() const {
		return m;    // 1
	}
	int DajSekunde() const {
		return s;    // 1
	}
};

Sat Sat::operator +(int pomak)
{
	Sat novi(*this);
	novi += pomak;
	return novi;
}
Sat Sat::operator +=(int pomak) const
{
	Sat novi(*this);
	novi += pomak;
	return novi;
}

Sat Sat::operator -(int pomak)
{
	Sat novi(*this);
	novi -= pomak;
	return novi;
}

Sat Sat::operator -=(int pomak) const
{
	Sat novi(*this);
	novi -= pomak;
	return novi;
}


int main ()
{
    Sat vrijeme;
    vrijeme.Postavi(1,30,45);
    vrijeme++;
    ++vrijeme;
    vrijeme--;
    --vrijeme;
    vrijeme+=50;
    vrijeme -= -50;
    vrijeme = vrijeme - 10;
    vrijeme = vrijeme + 10;
    
    int sati(vrijeme.DajSate()),minute(vrijeme.DajMinute()),sekunde(vrijeme.DajSekunde());
    std::cout<<vrijeme;
    std::cout<<std::endl<<sati<<" "<<minute<<" "<<sekunde<<" "<<vrijeme.DaLiJeIspravno(50,45,3423);
    return 0;
}