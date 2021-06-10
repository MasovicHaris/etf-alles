/*
    TP 16/17 (Tutorijal 13, Zadatak 2)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>

class ApstraktniStudent {
	std::string ime, prezime;
	int index, bpi;
	double prosjek;
public:
	virtual ~ApstraktniStudent() { }
	ApstraktniStudent(std::string ime, std::string prezime, int index) : ime(ime), prezime(prezime), index(index), bpi(0), prosjek(5) {}
	std::string DajIme() const {
		return ime;
	}
	std::string DajPrezime() const {
		return prezime;
	}
	int DajBrojIndeksa() const {
		return index;
	}
	int DajBrojPolozenih() const {
		return bpi;
	}
	double DajProsjek() const {
		return prosjek;
	}
	void RegistrirajIspit(int ocjena) {
		if(ocjena>=5 && ocjena <=10) {
			if(ocjena !=5){
			double suma = prosjek*bpi;
			bpi++;
			suma += ocjena;
			prosjek =  suma/bpi;
			}
		} else throw std::domain_error("Neispravna ocjena");
	}
	void PonistiOcjene() {
		bpi = 0;
		prosjek = 5;
	}
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent *DajKopiju() const = 0;
};

class StudentBachelor : public ApstraktniStudent {
public:
	StudentBachelor(std::string ime, std::string prezime, int index) : ApstraktniStudent(ime, prezime, index) { }
	void IspisiPodatke() const {
		std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << "," << std::endl << "ima prosjek " << DajProsjek()<<"." << std::endl;
	}
	StudentBachelor *DajKopiju() const {
		return new StudentBachelor(*this);
	}
};

class StudentMaster : public ApstraktniStudent {
	int zavrsio;
public:
	StudentMaster(std::string ime, std::string prezime, int index, int god) : ApstraktniStudent(ime, prezime, index), zavrsio(god) { }
	StudentMaster *DajKopiju() const {
		return new StudentMaster(*this);
	}
	void IspisiPodatke() const {
		std::cout << "Student master studija " << DajIme() << " "  << DajPrezime()<<", sa brojem indeksa " << DajBrojIndeksa()<<"," << std::endl << "zavrsio bachelor studij godine " <<
		          zavrsio << ",ima prosjek " << DajProsjek() << "." << std::endl;
	}
};

int main ()
{
	StudentMaster s2("A", "BA", 42312, 201523);
	s2.RegistrirajIspit(7);
	s2.RegistrirajIspit(6);
	s2.RegistrirajIspit(5);
	s2.RegistrirajIspit(10);
	s2.RegistrirajIspit(7);
	std::cout << s2.DajIme() << " " << s2.DajPrezime() << " " << s2.DajBrojIndeksa() << " " << s2.DajBrojPolozenih() << " " << s2.DajProsjek() << std::endl;
	s2.IspisiPodatke();
	s2.PonistiOcjene();
	std::cout << s2.DajIme() << " " << s2.DajPrezime() << " " << s2.DajBrojIndeksa() << " " << s2.DajBrojPolozenih() << " " << s2.DajProsjek() << std::endl;
	s2.IspisiPodatke();
	StudentBachelor s1("Primjer", "Primjeric", 17745);
	for (int i = 0; i < 5; i++) s1.RegistrirajIspit(10);
	s1.IspisiPodatke();
	for (int i = 0; i < 5; i++) s2.RegistrirajIspit(10);
	s2.PonistiOcjene();
	s2.IspisiPodatke();
	return 0;
}