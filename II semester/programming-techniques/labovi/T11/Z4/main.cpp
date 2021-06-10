/* 
    TP 16/17 (Tutorijal 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <algorithm>
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
	int broj_timova;
	const int max_br_timova;
	Tim **timovi;
	void AlocirajTimove(int x){
		timovi = nullptr;
		try {
			timovi = new Tim *[x];
		}catch(...){
			OslobodiTimove();
			throw;
		}
	}
	void OslobodiTimove(){
		if(timovi == nullptr) return;
		for(int i=0; i < broj_timova; i++) delete timovi[i];
		delete[] timovi;
		timovi = nullptr;
	}
	bool ImalLevata(const char *IME) const {
		for(int i=0; i < broj_timova; i++) if(strcmp(IME, timovi[i]->DajImeTima()) == 0) return true;
		return false;
	}
	int DajIdeks(const char *IME) const {
		for(int i=0; i < broj_timova; i++) if(strcmp(IME, timovi[i]->DajImeTima()) == 0) return i;
		return -1;
	}
	static bool Kriterij(Tim *tim1, Tim *tim2){
		if(tim1->DajBrojPoena() == tim2->DajBrojPoena()){
			if(tim1->DajGolRazliku() == tim2->DajGolRazliku()){
				if(strcmp(tim1->DajImeTima(), tim2->DajImeTima())<0) return true;
			}else return (tim1->DajGolRazliku() > tim2->DajGolRazliku());
		}
		return (tim1->DajBrojPoena() > tim2->DajBrojPoena());
	}
public:
	explicit Liga(int velicina_lige) : broj_timova(0), max_br_timova(velicina_lige), timovi(nullptr){
		AlocirajTimove(max_br_timova);
	}
	explicit Liga(std::initializer_list<Tim> lista_timova) : broj_timova(lista_timova.size()), max_br_timova(lista_timova.size()), timovi(nullptr) {
		
		try {
			AlocirajTimove(max_br_timova);
			int i(0);
			for(auto j = lista_timova.begin(); j != lista_timova.end(); j++) timovi[i++] = new Tim(*j);
		}catch(...){
			OslobodiTimove();
			throw;
		}
	}
	~Liga(){
		for(int i=0; i < broj_timova; i++) delete timovi[i];
		delete [] timovi;
	}
	Liga(const Liga &l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova), timovi(nullptr){
		try{
		AlocirajTimove(max_br_timova);
		for(int i=0; i < broj_timova; i++) this->timovi[i] = new Tim(*l.timovi[i]);
		}catch(...){
			OslobodiTimove();
			throw; 
		}
	}
	Liga(Liga &&l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova), timovi(nullptr){
		timovi = l.timovi;
		l.timovi = nullptr;
	}
	Liga &operator =(const Liga &l){
		if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		if(&l == this) return *this; // samododjela 
		
		Tim **novi = nullptr;
		try{
			novi = new Tim*[l.broj_timova];
			for(int i=0; i < l.broj_timova; i++) novi[i] = nullptr;
			for(int i=0; i < l.broj_timova; i++) novi[i] = new Tim(*l.timovi[i]);
			
			for(int i=0; i < broj_timova; i++) delete timovi[i];
			delete []timovi; timovi = nullptr;
			timovi = novi; novi = nullptr;
			broj_timova = l.broj_timova;
		}catch(...){
			for(int i=0; i < l.broj_timova; i++) delete novi[i];
			delete []novi; novi = nullptr;
			throw;
		}
		return *this;
	}
	Liga &operator =(Liga &&l){
		if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		if(&l == this) return *this; // samododjela 
		timovi = l.timovi;
		broj_timova = l.broj_timova;
		l.timovi = nullptr;
		return *this;
	}
	void DodajNoviTim(const char ime_tima[]){
		if(broj_timova == max_br_timova) throw std::range_error("Liga popunjena");
		if(ImalLevata(ime_tima)) throw std::logic_error("Tim vec postoji");
		try {
			timovi[broj_timova++] = new Tim(ime_tima);
		}catch(...){
			broj_timova--;
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
	std::sort(timovi, timovi + broj_timova, Kriterij);
	for(int i=0; i < broj_timova; i++) timovi[i]->IspisiPodatke();
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