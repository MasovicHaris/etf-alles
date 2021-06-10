/*
    TP 16/17 (Tutorijal 12, Zadatak 4)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>

class Kompleksni {
	double re, im;
public:
	Kompleksni(double re = 0, double im = 0) : re(re), im(im) {}
	friend Kompleksni operator +(const Kompleksni &a) {
		return a;
	}
	friend Kompleksni operator -(const Kompleksni &a) {
		return {-a.re, -a.im};
	}
	friend Kompleksni operator +(const Kompleksni &a, const Kompleksni &b) {
		return {a.re + b.re, a.im + b.im};
	}
	friend Kompleksni operator -(const Kompleksni &a, const Kompleksni &b) {
		return Kompleksni(a.re - b.re, a.im - b.im);
	}
	friend Kompleksni operator *(const Kompleksni &a, const Kompleksni &b) {
		return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
	}
	friend Kompleksni operator /(const Kompleksni &a, const Kompleksni &b) {
		double pomocna(b.re * b.re + b.im * b.im);
		return {(a.re * b.re + a.im * b.im) / pomocna,
		        (a.im * b.re - a.re * b.im) / pomocna
		       };
	}
	friend bool operator ==(const Kompleksni &a, const Kompleksni &b) {
		return a.re == b.re && a.im == b.im;
	}
	friend bool operator !=(const Kompleksni &a, const Kompleksni &b) {
		return !(a == b);
	}
	friend Kompleksni &operator +=(Kompleksni &a, const Kompleksni &b) {
		a.re += b.re;
		a.im += b.im;
		return a;
	}
	friend Kompleksni &operator -=(Kompleksni &a, const Kompleksni &b) {
		a.re -= b.re;
		a.im -= b.im;
		return a;
	}
	friend Kompleksni &operator *=(Kompleksni &a, const Kompleksni &b) {
		double pomocna(a.re * b.im + a.im * b.re);
		a.re = a.re * b.re - a.im * b.im;
		a.im = pomocna;
		return a;
	}
	friend Kompleksni &operator /=(Kompleksni &a, const Kompleksni &b) {
		double pom1(a.im * b.re - a.re * b.im), pom2(b.re * b.re + b.im * b.im);
		a.re = (a.re * b.re + a.im * b.im) / pom2;
		a.im = pom1 / pom2;
		return a;
	}
	friend std::ostream &operator <<(std::ostream &tok, const Kompleksni &a) {
		double realni(a.re), imaginarni(a.im);
		if(realni == 0 && imaginarni == 0) tok << "0";
		else if(imaginarni ==0) tok << realni;
		else if(realni == 0){
			if(imaginarni == 1) tok << "i";
			else if(imaginarni == -1) tok << "-i";
			else tok << imaginarni << "i"; }
		else { 
			if(imaginarni > 0){
				if(imaginarni == 1) tok << realni << "+i";
				else tok << realni << "+" << imaginarni << "i"; }
			else {
				if(imaginarni == -1) tok << realni << "-i";
				else tok << realni << imaginarni << "i"; }
		}
		return tok;
	}
	friend std::istream &operator >>(std::istream &tok, Kompleksni &a);
	friend double real(const Kompleksni &a) {
		return a.re;
	}
	friend double imag(const Kompleksni &a) {
		return a.im;
	}
	friend double abs(const Kompleksni &a) {
		return std::sqrt(a.re * a.re + a.im * a.im);
	}
	friend double arg(const Kompleksni &a) {
		return std::atan2(a.im, a.re);
	}
	friend Kompleksni conj(const Kompleksni &a) {
		return {a.re, -a.im};
	}
	friend Kompleksni sqrt(const Kompleksni &a) {
		double rho(std::sqrt(abs(a))), phi(arg(a) / 2);
		return {rho * cos(phi), rho * sin(phi)};
	}
};

int main ()
{
	return 0;
}