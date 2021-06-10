/*
    TP 16/17 (Tutorijal 12, Zadatak 3)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};
std::string pok[]{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};

Dani &operator ++(Dani &d)
{
	return d = Dani((int(d) + 1) % 7);
}
Dani operator ++(Dani &d, int)
{
	Dani pomocni(d);
	++d;
	return pomocni;
}
Dani operator +(Dani d, int n)
{
	return Dani((int(d) + n) % 7);
}

std::ostream& operator << (std::ostream& ispis, Dani d)
{
	ispis << pok[d];
	return ispis;
}

int main ()
{
	for(Dani d = Ponedjeljak; d <= Nedjelja; d++){ std::cout << d << std::endl; if(d == Nedjelja) break; }
	return 0;
}