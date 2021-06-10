#include <iostream>
#include <stdexcept>

template <typename Tip>
class Lista {
public:
    Lista() {}
    Lista (const Lista<Tip> &l) {}
    virtual ~Lista() {}
    virtual int brojElemenata() const = 0;
    virtual Tip &trenutni() = 0;
    virtual Tip trenutni() const = 0;
    virtual bool prethodni() =0;
    virtual bool sljedeci() =0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const Tip &el) =0;
    virtual void dodajIza(const Tip &el) =0;
    virtual Tip &operator[] (int i) = 0;                                          // dopisati
    virtual Tip operator[] (int i) const = 0;                                     // dopisati
};

template <typename Tip>
class NizLista : public Lista<Tip> {
        int maxkapacitet;
        int brojEl;
        Tip *pocetni = nullptr;
        Tip *trenutnipok = nullptr;
    public:
    NizLista() { brojEl=0; pocetni = nullptr; trenutnipok = nullptr; maxkapacitet = 2; }
    NizLista (const NizLista<Tip> &niz) {
        try{
            Tip *novi = new Tip[niz.maxkapacitet];
            int Trenutni(trenutnipok - pocetni);
            for(int i=0; i < niz.brojEl; i++) novi[i] = niz.pocetni[i];
            delete[] pocetni;
            pocetni = nullptr; trenutnipok = nullptr;
            maxkapacitet = niz.maxkapacitet;
            brojEl=niz.brojEl;
            pocetni = novi; trenutnipok = &novi[Trenutni];
        }catch(...){
            throw std::domain_error("Nema memorije!");
        }
    }
    NizLista (NizLista<Tip> &&niz) {
            maxkapacitet =niz.maxkapacitet; brojEl=niz.brojEl; pocetni=niz.pocetni; trenutnipok = niz.trenutnipok;
            niz.maxkapacitet=0; niz.brojEl=0; niz.pocetni = nullptr; niz.trenutnipok = nullptr;
    }
    ~NizLista() { delete[] pocetni; pocetni=nullptr; trenutnipok = nullptr; brojEl=0; }
    int brojElemenata() const { return brojEl; }
    Tip &trenutni() { if (brojEl == 0) throw std::domain_error("Greska!"); return *trenutnipok; }
    Tip trenutni() const { if (brojEl == 0) throw std::domain_error("Greska!"); return *trenutnipok; }
    bool prethodni() {
        if( brojEl == 0) throw std::domain_error("Greska!");
        if(trenutnipok == pocetni) return false;
        trenutnipok = trenutnipok -1;
        return true;
    }
    bool sljedeci() {
        if(brojEl == 0) throw std::domain_error("Greska!");
        if(trenutnipok == pocetni + brojEl - 1) return false;
        trenutnipok = trenutnipok + 1;
        return true;
    }
    void pocetak(){
        if(brojEl == 0) throw std::domain_error("Greska!");
        trenutnipok = pocetni;
    }
    void kraj(){
        if(brojEl == 0) throw std::domain_error("Greska!");
        trenutnipok = pocetni + brojEl - 1;
    }
    void obrisi(){
        if( brojEl == 0 ) throw std::domain_error("Greska!");
        if( brojEl == 1 ) {
            delete[] pocetni;
            brojEl--;
            pocetni = nullptr; trenutnipok = nullptr;
            return;
        }
         if( trenutnipok == &pocetni[brojEl - 1]) {
            brojEl--;
            trenutnipok--;
            return;
        } 
        
        Tip *plus(trenutnipok);
        Tip *plusjedan(trenutnipok +1);
        while(plusjedan - pocetni < brojEl){
            *plus = *plusjedan;
            plus++; plusjedan++;
        }
        brojEl--; // trenutnipok++;
    }

    void dodajIspred(const Tip &el){

        if(brojEl == 0){
            try {
                pocetni = new Tip[maxkapacitet];
                pocetni[0] = el;
                trenutnipok = pocetni;
                brojEl++;
                return;
            }catch(...){
                throw std::domain_error("Nema memorije!");
            }
        }
        if(brojEl == maxkapacitet){
            try {
                Tip *noviNiz = new Tip[maxkapacitet + 10];
                for (int i = 0; i < brojEl; ++i) noviNiz[i] = pocetni[i];
                int indeksTrenutnog(trenutnipok - pocetni);

                Tip *pomocni1 = &noviNiz[indeksTrenutnog];
                Tip *pomocni2(pomocni1);
                while(pomocni2 - noviNiz < brojEl + 1) pomocni2++;
                while(pomocni2 > pomocni1){
                    *pomocni2 = *(pomocni2-1);
                    pomocni2--;
                }
                noviNiz[indeksTrenutnog] = el;
                brojEl++; maxkapacitet+=10;

                trenutnipok = nullptr;
                delete[] pocetni;
                pocetni = nullptr;

                pocetni = &noviNiz[0];
                trenutnipok = &noviNiz[indeksTrenutnog + 1];
                return;
            }catch(...){
                throw std::domain_error("Nema memorije!");
            }
        }
        int indeksTrenutnog(trenutnipok - pocetni);
        Tip *pomocni1 = &pocetni[indeksTrenutnog];
        Tip *pomocni2(pomocni1);
        while(pomocni2 - pocetni < brojEl) pomocni2++;
        while(pomocni2 > pomocni1){
            *pomocni2 = *(pomocni2-1);
            pomocni2--;
        }
        pocetni[indeksTrenutnog] = el;
        trenutnipok = &pocetni[indeksTrenutnog+1];
        brojEl++;
    }

    void dodajIza(const Tip &el){

        if(brojEl == 0){
            try {
                pocetni = new Tip[maxkapacitet];
                pocetni[0] = el;
                trenutnipok = pocetni;
                brojEl++;
                return;
            }catch(...){
                throw std::domain_error("Nema memorije!");
            }
        }
        if(brojEl == maxkapacitet){
            try {
                Tip *noviNiz = new Tip[maxkapacitet + 10];
                for (int i = 0; i < brojEl; ++i) noviNiz[i] = pocetni[i];
                unsigned int indeksTrenutnog(trenutnipok - pocetni);

                Tip *pomocni1 = &noviNiz[indeksTrenutnog];
                Tip *pomocni2(pomocni1);
                while(pomocni2 - noviNiz < brojEl + 1) pomocni2++;
                while(pomocni2 > pomocni1){
                    *pomocni2 = *(pomocni2-1);
                    pomocni2--;
                }
                noviNiz[indeksTrenutnog+1] = el;
                brojEl++; maxkapacitet+= 10;

                trenutnipok = nullptr;
                delete[] pocetni;
                pocetni = nullptr;

                pocetni = &noviNiz[0];
                trenutnipok = &noviNiz[indeksTrenutnog];
                return;
            }catch(...){
                throw std::domain_error("Nema memorije!");
            }
        }
        unsigned int indeksTrenutnog(trenutnipok - pocetni);

        Tip *pomocni1 = &pocetni[indeksTrenutnog];
        Tip *pomocni2(pomocni1);
        while(pomocni2 - pocetni < brojEl ) pomocni2++;
        while(pomocni2 > pomocni1){
            *pomocni2 = *(pomocni2-1);
            pomocni2--;
        }
        pocetni[indeksTrenutnog+1] = el;
        trenutnipok = &pocetni[indeksTrenutnog];
        brojEl++;
    }

    NizLista<Tip> &operator= (const NizLista<Tip> &niz){
        try{
            Tip *novi = new Tip[niz.maxkapacitet];
            int Trenutni(trenutnipok - pocetni);
            for(int i=0; i < niz.brojEl; i++) novi[i] = niz.pocetni[i];
            delete[] pocetni;
            pocetni = nullptr; trenutnipok = nullptr;
            maxkapacitet = niz.maxkapacitet;
            brojEl=niz.brojEl;
            pocetni = novi; trenutnipok = &novi[Trenutni];
        }catch(...){
            throw std::domain_error("Nema memorije!");
        }
        return *this;
    }
    NizLista<Tip> &operator= (NizLista<Tip> &&niz){
        maxkapacitet =niz.maxkapacitet;
        brojEl=niz.brojEl;
        pocetni=niz.pocetni;
        trenutnipok=niz.trenutnipok;
        niz.maxkapacitet=0;
        niz.brojEl=0;
        niz.pocetni=nullptr;
        niz.maxkapacitet=nullptr;
        return *this;
    }
    Tip &operator[] (int i){
    if (i<0 || i>=brojEl){
        throw std::domain_error("Greska!");
    }
    return *(pocetni+i);
    }

    Tip operator[] (int i) const {
    if (i<0 || i>=brojEl){
        throw std::domain_error("Greska!");
    }
    return *(pocetni+i);
    }
    
};


template <typename Tip>
struct Cvor {
    Tip info;
    Cvor *sljedeci = nullptr;
};

template <typename Tip>
class JednostrukaLista : public Lista<Tip> {
    Cvor<Tip> *pocetni = nullptr;
    Cvor<Tip> *trenutnipok = nullptr;
    int brElemenata;
public:
    JednostrukaLista() { pocetni = nullptr; trenutnipok = nullptr; brElemenata=0; }
    JednostrukaLista (const JednostrukaLista<Tip> &l) {
        try{
            pocetni = new Cvor<Tip>();                  // deklaracija prvog
            pocetni->info = l.pocetni->info;
            pocetni->sljedeci = nullptr;
            if(l.pocetni == l.trenutnipok) pocetni = trenutnipok;
            auto pok1(pocetni->sljedeci);
            auto pok2(l.pocetni->sljedeci);

            do {
                pok1 = new Cvor<Tip>;
                pok1->info = pok2->info;
                if(pok2 == l.trenutnipok) trenutnipok = pok1;
                pok1 = pok1->sljedeci;
                pok2 = pok2->sljedeci;
            }while(pok2->sljedeci != nullptr);

            pok1->sljedeci = nullptr;
            brElemenata = l.brElemenata;
        }catch(...){
            throw std::domain_error("Nejma memorije!");
        }
    }
    JednostrukaLista (const JednostrukaLista<Tip> &&l){
        pocetni = l.pocetni;
        trenutnipok = l.trenutnipok;
        brElemenata = l.brElemenata;
    }
    ~JednostrukaLista() {
        Cvor<Tip> *trenutnii = pocetni;
        Cvor<Tip> *novi;
        while (trenutnii != NULL) {
            novi = trenutnii -> sljedeci;
            delete trenutnii;
            trenutnii = novi;
        }
        pocetni = nullptr;
    }
    JednostrukaLista<Tip> &operator= (const JednostrukaLista<Tip> &l) {
        try{
            pocetni = new Cvor<Tip>();                  // deklaracija prvog
            pocetni->info = l.pocetni->info;
            pocetni->sljedeci = nullptr;
            if(l.pocetni == l.trenutnipok) pocetni = trenutnipok;
            auto pok1(pocetni->sljedeci);
            auto pok2(l.pocetni->sljedeci);

            do {
                pok1 = new Cvor<Tip>;
                pok1->info = pok2->info;
                if(pok2 == l.trenutnipok) trenutnipok = pok1;
                pok1 = pok1->sljedeci;
                pok2 = pok2->sljedeci;
            }while(pok2->sljedeci != nullptr);

            pok1->sljedeci = nullptr;
            brElemenata = l.brElemenata;
        }catch(...){
            throw std::domain_error("Nejma memorije!");
        }
    }
    JednostrukaLista<Tip> &operator= (JednostrukaLista<Tip> &&l){
        pocetni = l.pocetni;
        trenutnipok = l.trenutnipok;
        brElemenata = l.brElemenata;
        l.pocetni = nullptr; l.trenutnipok = nullptr; l.brElemenata = 0;
    }
    int brojElemenata() { return brElemenata; }
    int brojElemenata() const { return brElemenata; }
    Tip &trenutni () {
        if (trenutnipok == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        return trenutnipok->info;
    }
    Tip trenutni() const {
        if (trenutnipok == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        return trenutnipok->info;
    }
    bool prethodni() {
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        if(trenutnipok == pocetni) return false;

        auto p(pocetni);
        while(p->sljedeci != trenutnipok) p = p->sljedeci;
        trenutnipok = p;
        p = nullptr;
        return true;
    }
    bool sljedeci() {
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        if(trenutnipok->sljedeci == nullptr) return false;
        trenutnipok = trenutnipok->sljedeci;
        return true;
    }
    void obrisi() {
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        if(pocetni->sljedeci == nullptr){                                                    // prvi slucaj
            delete pocetni;
            pocetni = nullptr; trenutnipok = nullptr; brElemenata = 0;
            return;
        }
        if(trenutnipok->sljedeci == nullptr){                                                // zadnji slucaj
            auto p(pocetni);
            while(p->sljedeci != trenutnipok) p = p->sljedeci;
            delete trenutnipok;
            trenutnipok = nullptr;
            trenutnipok = p; trenutnipok->sljedeci = nullptr;
            p = nullptr;
            brElemenata--;
            return;
        }

        auto p(pocetni);
        while(p->sljedeci != nullptr && p->sljedeci != trenutnipok) p = p->sljedeci;                                   // opci slucaj
        p->sljedeci = trenutnipok->sljedeci;
        trenutnipok->sljedeci = nullptr;
        delete trenutnipok; trenutnipok = nullptr;

        trenutnipok = p->sljedeci;
    }
    
    void dodajIspred(const Tip &el) {
        try {
            if (brElemenata == 0) {
                pocetni = new Cvor<Tip>();
                pocetni->sljedeci = nullptr;
                pocetni->info = el;
                trenutnipok = pocetni;
                brElemenata++;
                return;
            }

            if(brElemenata == 1 || pocetni == trenutnipok){
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = pocetni;
                pokazivac->info = el;
                pocetni = pokazivac;
                brElemenata++;
                return;
            }
            
            
            auto p(pocetni);
            while (p->sljedeci != nullptr && p->sljedeci != trenutnipok) p = p->sljedeci;

            Cvor<Tip> *pokazivac = new Cvor<Tip>();
            pokazivac->sljedeci = trenutnipok;
            pokazivac->info = el;
            p->sljedeci = pokazivac;
            brElemenata++;
        }catch(...){
            throw std::domain_error("Nejma memorije!");
        }
    }
    void dodajIza(const Tip &el) {
        try {
            if (brElemenata == 0) {
                pocetni = new Cvor<Tip>();
                pocetni->sljedeci = nullptr;
                pocetni->info = el;
                trenutnipok = pocetni;
                brElemenata++;
                return;
            }

            if(brElemenata == 1){
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = nullptr;
                pokazivac->info = el;
                pocetni->sljedeci = pokazivac;
                brElemenata++;
                return;
            }
            
            auto p(trenutnipok->sljedeci);
            if(p == nullptr){                                                   // zadnji element
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = nullptr;
                pokazivac->info = el;
                p = pokazivac;
                brElemenata++;
                return;
            }

            Cvor<Tip>  *pokazivac = new Cvor<Tip>();
            pokazivac->sljedeci = trenutnipok->sljedeci;
            pokazivac->info = el;
            p = pokazivac;
            brElemenata++;
        }catch(...){
            throw std::domain_error("Nejma memorije!");
        }
    }
    
    Tip &operator[] (int i){
        int brojac = 0;
        auto pok(pocetni);
        while (brojac != i) {
            pok=pok->sljedeci;
            brojac++;
        }
        return pok->info;
    }
    Tip operator[] (int i) const {
        int brojac = 0;
        auto pok(pocetni);
        while (brojac != i) {
            pok=pok->sljedeci;
            brojac++;
        }
        return pok->info;
    }
    void pocetak() {
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        trenutnipok = pocetni;
    }
    void kraj(){
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        auto p(trenutnipok);
        while(p->sljedeci != nullptr) p = p->sljedeci;
        trenutnipok = p;
    }

};




int main() {
  NizLista<int> n;
for (int i(1); i<=5; i++) {
	n.dodajIza(i);
	n.sljedeci();
}
for (int i(0); i<n.brojElemenata(); i++)
	std::cout << n[i] << " ";
	
	std::cout << std::endl;
    std::cout << n.trenutni();
    std::cout << std::endl;
n.pocetak();
n.sljedeci();
n.sljedeci();
    std::cout << n.trenutni();
    std::cout << std::endl;
n.obrisi();
for (int i(0); i<n.brojElemenata(); i++)
	std::cout << n[i] << " ";
	std::cout << std::endl;
std::cout << n.trenutni();
    return 0;
}