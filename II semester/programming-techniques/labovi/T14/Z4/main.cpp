/* 
    TP 16/17 (Tutorijal 14, Zadatak 4)
	Autotestovi by Enil Pajic.
	NOTE: ukoliko smatrate da je greska u autotestu, radite po postavci, bice uvazeno
	NOTE: vrsit ce se provjera na prepisivanje tutorijala (i kaznjavati sa oduzimanjem poena od ukupno osvojenih)
	NOTE: ovaj tutorijal se salje kao zadaca na Zamger
*/
#include <iostream>
#include <fstream>
#include <stdexcept>

void IzvrniDatoteku(const char ime_datoteke[]){
	std::fstream datoteka(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
	if(!datoteka) throw std::logic_error("Datoteka ne postoji");
	datoteka.seekg(0, std::ios::end);
	int duzina(datoteka.tellg());
	int broj_el(duzina/sizeof(double));
	for(int i=0; i < (broj_el+1)/2; i++){
		datoteka.seekp(0);
		double broj1, broj2;
		datoteka.seekg(int(i * sizeof(double)));
		datoteka.read(reinterpret_cast<char*>(&broj1), sizeof broj1);
		datoteka.seekg(-int((i+1) * sizeof(double)), std::ios::end);
		datoteka.read(reinterpret_cast<char*>(&broj2), sizeof broj2);
		datoteka.seekp(int(i * sizeof(double)));
		datoteka.write(reinterpret_cast<char*>(&broj2), sizeof broj2);
		datoteka.seekp(-int((i + 1) * sizeof(double)), std::ios::end);
		datoteka.write(reinterpret_cast<char*>(&broj1), sizeof broj1);
		datoteka.seekg(0);
	}
	if(!datoteka) throw std::logic_error("Problemi pri citanju datoteke");
}

int main ()
{
	double niz[] = {1, 2, 0.5, 0.2, 6.23};
	double novi[5]{};
	std::ofstream f ("dat.bin", std::ios::binary);
	f.write((char *)niz, sizeof niz);
	f.close();
	IzvrniDatoteku("dat.bin");
	std::ifstream ff ("dat.bin", std::ios::binary);
	ff.read((char *)novi, sizeof novi);
	for (int i = 0; i < 5; ++i) std::cout << novi[i] << ", ";
	ff.close();
	return 0;
}