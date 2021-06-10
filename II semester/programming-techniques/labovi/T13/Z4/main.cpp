/*
    TP 16/17 (Tutorijal 13, Zadatak 4)
	Autotestove pisala Ivona Ivkovic. Sva pitanja, sugestije, prijave gresaka
	slati na mail iivkovic2@etf.unsa.ba

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

class ApstraktniStudent
{
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
			if(ocjena !=5) {
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

class StudentBachelor : public ApstraktniStudent
{
public:
	StudentBachelor(std::string ime, std::string prezime, int index) : ApstraktniStudent(ime, prezime, index) { }
	void IspisiPodatke() const {
		std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << "," << std::endl << "ima prosjek " << DajProsjek()<<"." << std::endl;
	}
	StudentBachelor *DajKopiju() const {
		return new StudentBachelor(*this);
	}
};

class StudentMaster : public ApstraktniStudent
{
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

class Fakultet
{
	std::vector<ApstraktniStudent*> vektor;
	bool Danka(int indeks) {
		for(int i=0; i < vektor.size(); i++) {
			if(vektor[i]->DajBrojIndeksa() == indeks) return false;
		}
		return true;
	}
public:
	Fakultet() { }
	~Fakultet() {
		for(int i=0; i < vektor.size(); i++) {
			delete vektor[i];
			vektor[i] = nullptr;
		}
	}
	Fakultet(const Fakultet &k) : vektor(k.vektor) {
		for(int i=0; i < k.vektor.size(); i++) vektor[i] = k.vektor[i]->DajKopiju();
	}
	Fakultet &operator =(const Fakultet &k) {
		std::vector<ApstraktniStudent*> novi(k.vektor.size());
		try {
			for(int i=0; i < novi.size(); i++) {
				novi[i] = k.vektor[i]->DajKopiju();
			}
		} catch(...) {
			throw;
		}
		for(int i=0; i < vektor.size(); i++) {
			delete vektor[i];
			vektor[i] = nullptr;
		}
		vektor = novi;
		return *this;
	}
	Fakultet(Fakultet &&k) : vektor(k.vektor.size()) {
		for(int i=0; i < vektor.size(); i++) delete vektor[i];
		vektor.resize(k.vektor.size());
		try {
			for(int i=0; i < vektor.size(); i++) {
				vektor[i] = k.vektor[i]->DajKopiju();
			}
		} catch(...) {
			throw;
		}
		for(int i=0; i < k.vektor.size(); i++) {
			delete k.vektor[i];
			k.vektor[i] = nullptr;
		}
		k.vektor.resize(0);
	}
	Fakultet &operator =(Fakultet &&k) {
		for(int i=0; i < vektor.size(); i++) delete vektor[i];
		vektor.resize(k.vektor.size());
		try {
			for(int i=0; i < vektor.size(); i++) {
				vektor[i] = k.vektor[i]->DajKopiju();
			}
		} catch(...) {
			throw;
		}
		for(int i=0; i < k.vektor.size(); i++) {
			delete k.vektor[i];
			k.vektor[i] = nullptr;
		}
		k.vektor.resize(0);
		return *this;
	}
	void UpisiStudenta(std::string ime, std::string prezime, int indeks) {
		if(!Danka(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		ApstraktniStudent *pok = new StudentBachelor(ime, prezime, indeks);
		vektor.push_back(pok);
	}
	void UpisiStudenta(std::string ime, std::string prezime, int indeks, int godina) {
		if(!Danka(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
		ApstraktniStudent *pok = new StudentMaster(ime, prezime, indeks, godina);
		vektor.push_back(pok);
	}
	void ObrisiStudenta(int indeks) {
		if(Danka(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		int poz=0;
		for(int i=0; i < vektor.size(); i++) {
			if(vektor[i]->DajBrojIndeksa() == indeks) {
				delete vektor[i];
				poz = i;
				break;
			}
		}
		vektor.erase(vektor.begin(), vektor.begin() + poz+1);
	}
	const ApstraktniStudent &operator [](int indeks) const {
		bool halo(true);
		for(int i=0; i < vektor.size(); i++) {
			if(vektor[i]->DajBrojIndeksa() == indeks) halo = false;
		}
		if(halo) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		for(int i=0; i < vektor.size(); i++) {
			if(vektor[i]->DajBrojIndeksa() == indeks) return *vektor[i];
		}
		return *vektor[0];
	}
	ApstraktniStudent &operator [](int indeks) {
		if(Danka(indeks)) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
		for(int i=0; i < vektor.size(); i++) {
			if(vektor[i]->DajBrojIndeksa() == indeks) return *vektor[i];
		}
		return *vektor[0];
	}
	void IspisiSveStudente() const {
		auto novi = vektor;
		std::sort(novi.begin(), novi.end(), [](ApstraktniStudent* pok1, ApstraktniStudent *pok2) {
			if(pok1->DajProsjek() == pok2->DajProsjek()) return pok1->DajBrojIndeksa() < pok2->DajBrojIndeksa();
			return pok1->DajProsjek() > pok2->DajProsjek();
		});
		for(int i=0; i < novi.size(); i++) {
			novi[i]->IspisiPodatke();
		}
	}
};

class Student
{
	ApstraktniStudent *p;
public:
	Student() {
		p = nullptr;
	}
	~Student() {
		delete p;
		p = nullptr;
	}
	Student(const Student &student) {
		if(!student.p) p = nullptr;
		else p = student.p->DajKopiju();
	}
	Student(Student &&student) {
		p = student.p;
		student.p = nullptr;
	}
	std::string DajIme() const {
		return p->DajIme();
	}
	std::string DajPrezime() const {
		return p->DajPrezime();
	}
	int DajBrojIndeksa() const {
		return p->DajBrojIndeksa();
	}
	int DajBrojPolozenih() const {
		return p->DajBrojPolozenih();
	}
	double DajProsjek() const {
		return p->DajProsjek();
	}
	void RegistrirajIspit(int ocjena) {
		p->RegistrirajIspit(ocjena);
	}
	void PonistiOcjene() {
		p->PonistiOcjene();
	}
	void IspisiPodatke() {
		p->IspisiPodatke();
	}
	Student &operator =(const Student &student) {
		ApstraktniStudent *p_novi(nullptr);
		if(student.p != nullptr) p_novi = student.p->DajKopiju();
		delete p;
		p = p_novi;
		return *this;
	}
	Student &operator =(Student &&student) {
		std::swap(p, student.p);
		return *this;
	}
	Student(const ApstraktniStudent &student) : p(student.DajKopiju()){ }
};

int main ()
{
	Student s1, s2;
	s1 = StudentBachelor("Dusko", "Dugousko", 1234); // s1 je bachelor
	s2 = StudentMaster("Paja", "Patak", 4312, 2015); // a s2 master
	s1.RegistrirajIspit(6);
	s1.RegistrirajIspit(9);
	s2.RegistrirajIspit(8);
	s1.IspisiPodatke();
	s2.IspisiPodatke();
	s1 = s2; // sad je i s1 master
	s1.IspisiPodatke();

	return 0;
}