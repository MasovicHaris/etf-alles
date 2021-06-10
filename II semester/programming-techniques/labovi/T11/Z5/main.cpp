/* 
    TP 16/17 (Tutorijal 11, Zadatak 5)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream> 
#include <iomanip>  
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <memory>
// OSTAO MAIN 
class Tim {
	char ime_tima[21];
	int broj_odigranih;
	int broj_pobjeda;
	int broj_nerijesenih;
	int broj_poraza;
	int broj_datih;
	int broj_primljenih;
	int broj_poena;
public:
	Tim(const char ime[]) : broj_odigranih(0), broj_pobjeda(0), broj_nerijesenih(0),
		broj_poraza(0), broj_datih(0), broj_primljenih(0), broj_poena(0){
			if(std::strlen(ime) > 19) throw std::range_error("Predugacko ime tima");
			std::strcpy(ime_tima, ime);
		}
	void ObradiUtakmicu(int broj_datih, int broj_primljenih){
		if(broj_datih < 0 || broj_primljenih < 0) throw std::range_error("Neispravan broj golova");
		broj_odigranih++;
		Tim::broj_datih +=broj_datih;
		Tim::broj_primljenih +=broj_primljenih;
		if(broj_datih > broj_primljenih){
			broj_pobjeda++;
			broj_poena += 3;
		}else if(broj_datih == broj_primljenih){
			broj_nerijesenih++;
			broj_poena += 1;
		}
		else broj_poraza++;
	}
	const char *DajImeTima() const { return ime_tima; }
	int DajBrojPoena() const { return broj_poena; }
	int DajGolRazliku() const { return (broj_datih - broj_primljenih); }
	void IspisiPodatke() const;
};

void Tim::IspisiPodatke() const {
	std::cout << std::setw(20) << std::left << ime_tima
	<< std::setw(4) << std::right << broj_odigranih
	<< std::setw(4) << std::right << broj_pobjeda
	<< std::setw(4) << std::right << broj_nerijesenih
	<< std::setw(4) << std::right << broj_poraza
	<< std::setw(4) << std::right << broj_datih
	<< std::setw(4) << std::right << broj_primljenih
	<< std::setw(4) << std::right << broj_poena << std::endl;
}

class Liga {
	std::vector<std::shared_ptr<Tim>> timovi;
	void AlocirajTimove(int x){
		try {
			timovi.resize(x);
		}catch(...){
			throw;
		}
	}
	bool ImalLevata(const char *IME) const {
		for(int i=0; i < timovi.size(); i++) if(strcmp(IME, timovi[i]->DajImeTima()) == 0) return true;
		return false;
	}
	int DajIdeks(const char *IME) const {
		for(int i=0; i < timovi.size(); i++) if(strcmp(IME, timovi[i]->DajImeTima()) == 0) return i;
		return -1;
	}
	static bool Kriterij(std::shared_ptr<Tim> tim1, std::shared_ptr<Tim> tim2){
		if(tim1->DajBrojPoena() == tim2->DajBrojPoena()){
			if(tim1->DajGolRazliku() == tim2->DajGolRazliku()){
				if(strcmp(tim1->DajImeTima(), tim2->DajImeTima())<0) return true;
			}else return (tim1->DajGolRazliku() > tim2->DajGolRazliku());
		}
		return (tim1->DajBrojPoena() > tim2->DajBrojPoena());
	}
public:
	explicit Liga() { }
	explicit Liga(std::initializer_list<Tim> lista_timova) {
		
		try {
			AlocirajTimove(lista_timova.size());
			int i(0);
			for(auto j = lista_timova.begin(); j != lista_timova.end(); j++) timovi[i++] = std::make_shared<Tim>(*j);
		}catch(...){
			throw;
		}
	}
	Liga(const Liga &l){
		try{
		AlocirajTimove(l.timovi.size());
		for(int i=0; i < timovi.size(); i++) this->timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
		}catch(...){
			throw; 
		}
	}
	Liga(Liga &&l){
		timovi = l.timovi;
		l.timovi.resize(0);
	}
	Liga &operator =(const Liga &l){
		if(&l == this) return *this; // samododjela
		try{
			timovi.resize(l.timovi.size());
			for(int i=0; i < l.timovi.size(); i++) this->timovi[i] = std::make_shared<Tim>(*l.timovi[i]);
		}catch(...){
			throw;
		}
		return *this;
	}
	Liga &operator =(Liga &&l){
		if(&l == this) return *this; // samododjela 
		timovi = l.timovi;
		l.timovi.resize(0);
		return *this;
	}
	void DodajNoviTim(const char ime_tima[]){
		if(ImalLevata(ime_tima)) throw std::logic_error("Tim vec postoji");
		try {
			timovi.emplace_back(std::make_shared<Tim>(ime_tima));
		}catch(...){
			throw;
		}
	}
	void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2){
 		if(!ImalLevata(tim1) || !ImalLevata(tim2)) throw std::logic_error("Tim nije nadjen");
 		try {
 			timovi[DajIdeks(tim1)]->ObradiUtakmicu(rezultat_1, rezultat_2);
 			timovi[DajIdeks(tim2)]->ObradiUtakmicu(rezultat_2, rezultat_1);
 		}catch(...){
 			throw std::range_error("Neispravan broj golova");
 		}
 	}
	void IspisiTabelu();
};

void Liga::IspisiTabelu() {
	std::sort(timovi.begin(), timovi.end(), Kriterij);
	for(int i=0; i < timovi.size(); i++) timovi[i]->IspisiPodatke();
}

int main ()
{
	try {
	Liga l{"Zeljeznicar", "Sarajevo", "Celik", "Zrinjski", "Borac", "Jedinstvo"};
	l.IspisiTabelu(); std::cout << std::endl;
	
	while(1){
		char timp[100]{}, timp2[100]{};
		std::cout << "Unesite ime prvog tima (ENTER za kraj): ";
			std::cin.getline(timp, 100);
			if(timp[0] == '\0') break;
			std::cout << "Unesite ime drugog tima: ";
			std::cin.getline(timp2, 100);
			std::cout << "Unesite broj postignutih golova za oba tima: ";
			
			int golovi1(0), golovi2(0);
			std::cin >> golovi1 >> golovi2;
			try {
				l.RegistrirajUtakmicu(timp, timp2, golovi1, golovi2);
			}
			catch(std::logic_error exec){
				std::cout << exec.what() << std::endl;
			}
			catch(std::range_error exec){
				std::cout << exec.what() << std::endl;
			}
			std::cin.ignore(10000, '\n');
			std::cout << std::endl;	l.IspisiTabelu(); std::cout << std::endl;
	}
	
	}
	catch(std::logic_error exec){
		std::cout << exec.what() << std::endl;
	}
	catch(std::range_error exec){
		std::cout << exec.what() << std::endl;
	}
	return 0;
}