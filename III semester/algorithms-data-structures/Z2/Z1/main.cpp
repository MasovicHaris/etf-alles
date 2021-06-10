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
    virtual Tip &operator[] (int i) = 0;
    virtual Tip operator[] (int i) const = 0;
};

template <typename Tip>
struct Cvor {
    Tip info;
    Cvor *sljedeci = nullptr;
    Cvor *prethodni = nullptr;
};

template <typename Tip>
class DvostrukaLista : public Lista<Tip> {
    Cvor<Tip> *pocetni = nullptr;
    Cvor<Tip> *trenutnipok = nullptr;
    Cvor<Tip> *krajni = nullptr;
    int brElemenata;
    static int prva, druga, treca, cetvrta, peta, sesta, sedma, osma, deveta;
public:
    DvostrukaLista() { pocetni = nullptr; trenutnipok = nullptr; krajni = nullptr; brElemenata=0; }
    DvostrukaLista(const DvostrukaLista<Tip> &l) {
        if(&l!=this) {
            try{
                Cvor<Tip> *novi = l.pocetni;
                pocetni = new Cvor<Tip>();                                          // novi cvor
                if(l.pocetni == l.trenutnipok) trenutnipok = pocetni;               // ako je treutni jedank pocetnom
                Cvor<Tip> *novcat = pocetni;
                novcat->sljedeci = nullptr;
                novcat->prethodni = nullptr;
                novcat->info = novi->info;

                while(novi->sljedeci != nullptr){

                    novcat->sljedeci = new Cvor<Tip>();
                    novcat->sljedeci->prethodni = novcat;
                    novcat->sljedeci->info = novi->sljedeci->info;
                    if(novi->sljedeci == l.trenutnipok) {
                        trenutnipok = novcat->sljedeci;
                        trenutnipok->prethodni = novcat;
                    }

                    novi = novi->sljedeci;
                    novcat = novcat->sljedeci;
                }
                novcat->sljedeci = nullptr;
                krajni = novcat;
                brElemenata = l.brElemenata;
            }catch(...){
                throw std::domain_error("Nejma memorije!");
            }
        }
    }
    DvostrukaLista (const DvostrukaLista<Tip> &&l){
        pocetni = l.pocetni;
        trenutnipok = l.trenutnipok;
        brElemenata = l.brElemenata;
        krajni = l.krajni;
    }
    ~DvostrukaLista() {
        Cvor<Tip> *trenutnii = pocetni;
        Cvor<Tip> *novi;
        while (trenutnii != NULL) {
            novi = trenutnii -> sljedeci;
            delete trenutnii;
            trenutnii = novi;
        }
        pocetni = nullptr;
    }
    DvostrukaLista<Tip> &operator= (const DvostrukaLista<Tip> &l) {
        if(&l!=this) {
            if(brElemenata != 0 ){
            for(int i=0; i < brElemenata; i++) obrisi();
            brElemenata = 0;
            }
            try{
                Cvor<Tip> *novi = l.pocetni;
                pocetni = new Cvor<Tip>();                                          // novi cvor
                if(l.pocetni == l.trenutnipok) trenutnipok = pocetni;               // ako je treutni jedank pocetnom
                Cvor<Tip> *novcat = pocetni;
                novcat->sljedeci = nullptr;
                novcat->prethodni = nullptr;
                novcat->info = novi->info;

                while(novi->sljedeci != nullptr){

                    novcat->sljedeci = new Cvor<Tip>();
                    novcat->sljedeci->prethodni = novcat;
                    novcat->sljedeci->info = novi->sljedeci->info;
                    if(novi->sljedeci == l.trenutnipok) {
                        trenutnipok = novcat->sljedeci;
                        trenutnipok->prethodni = novcat;
                    }

                    novi = novi->sljedeci;
                    novcat = novcat->sljedeci;
                }
                novcat->sljedeci = nullptr;
                krajni = novcat;
                brElemenata = l.brElemenata;
            }catch(...){
                throw std::domain_error("Nejma memorije!");
            }
        }
        return *this;
    }
    DvostrukaLista<Tip> &operator= (DvostrukaLista<Tip> &&l){
        pocetni = l.pocetni;
        trenutnipok = l.trenutnipok;
        brElemenata = l.brElemenata;
        krajni = l.krajni;
        l.pocetni = nullptr; l.trenutnipok = nullptr; l.brElemenata = 0; l.krajni = nullptr;
    }
    int brojElemenata() const { return brElemenata; prva++; }
    Tip &trenutni () {
        druga++;
        if (trenutnipok == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        return trenutnipok->info;
    }
    Tip trenutni() const {
        druga++;
        if (trenutnipok == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        return trenutnipok->info;
    }
    bool prethodni() {
        treca++;
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        if(trenutnipok == pocetni) return false;
        trenutnipok = trenutnipok->prethodni;
        return true;
    }
    bool sljedeci() {
        cetvrta++;
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        if(trenutnipok->sljedeci == nullptr) return false;
        trenutnipok = trenutnipok->sljedeci;
        return true;
    }
    void obrisi() {
        sedma++;
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");

        if(pocetni->sljedeci == nullptr){                                                    // prvi slucaj
            delete pocetni;
            pocetni = nullptr; trenutnipok = 0; brElemenata = 0; krajni = nullptr;
            return;
        }
        if(trenutnipok->sljedeci == nullptr && trenutnipok != pocetni){                                                // zadnji slucaj
            auto p(trenutnipok->prethodni);
            delete trenutnipok;
            trenutnipok = nullptr;
            trenutnipok = p; trenutnipok->sljedeci = nullptr;
            p = nullptr;
            brElemenata--;
            krajni = trenutnipok;
            return;
        }

        if(trenutnipok == pocetni){
            Cvor<Tip> *nov = pocetni;
            pocetni = pocetni->sljedeci;
            delete nov; nov = nullptr;
            brElemenata--;
            trenutnipok = pocetni;
            krajni = trenutnipok;
            return;
        }


        auto p(trenutnipok->prethodni);         // opci slucaj
        p->sljedeci = trenutnipok->sljedeci;
        trenutnipok->sljedeci->prethodni = p;
        trenutnipok->sljedeci = nullptr;
        trenutnipok->prethodni = nullptr;
        delete trenutnipok; trenutnipok = nullptr;
        brElemenata--;
        trenutnipok = p->sljedeci;
    }
    void dodajIspred(const Tip &el) {
        osma++;
        try {
            if (brElemenata == 0) {
                pocetni = new Cvor<Tip>();
                pocetni->sljedeci = nullptr;
                pocetni->prethodni = nullptr;
                pocetni->info = el;
                trenutnipok = pocetni;
                brElemenata++;
                return;
            }

            if(brElemenata == 1 || pocetni == trenutnipok){
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = pocetni;
                pokazivac->prethodni = nullptr;
                pokazivac->info = el;
                trenutnipok->prethodni = pokazivac;
                pocetni = pokazivac;
                brElemenata++;
                return;
            }


            auto p(trenutnipok->prethodni);
            Cvor<Tip> *pokazivac = new Cvor<Tip>();
            pokazivac->sljedeci = trenutnipok;
            trenutnipok->prethodni = pokazivac;
            pokazivac->info = el;
            p->sljedeci = pokazivac;
            pokazivac->prethodni = p;
            brElemenata++;
        }catch(...){
            throw std::domain_error("Nejma memorije!");
        }
    }
    void dodajIza(const Tip &el) {
        deveta++;
        try {
            if (brElemenata == 0) {
                pocetni = new Cvor<Tip>();
                pocetni->sljedeci = nullptr;
                pocetni->prethodni = nullptr;
                pocetni->info = el;
                trenutnipok = pocetni;
                brElemenata++;
                krajni = pocetni;
                return;
            }

            if(brElemenata == 1){
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = nullptr;
                pokazivac->info = el;
                pocetni->sljedeci = pokazivac;
                pokazivac->prethodni = pocetni;
                krajni = pokazivac;
                brElemenata++;
                return;
            }

            if(trenutnipok->sljedeci == nullptr){                                                   // zadnji element
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = nullptr;
                pokazivac->info = el;
                trenutnipok->sljedeci = pokazivac;
                pokazivac->prethodni = trenutnipok;
                krajni = pokazivac;
                brElemenata++;
                return;
            }

            Cvor<Tip>  *pokazivac = new Cvor<Tip>();
            pokazivac->sljedeci = trenutnipok->sljedeci;
            trenutnipok->sljedeci->prethodni = pokazivac;
            pokazivac->prethodni = trenutnipok;
            pokazivac->info = el;
            trenutnipok->sljedeci = pokazivac;
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
        peta++;
        if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        trenutnipok = pocetni;
    }
    void kraj(){
        sesta++;
       if(pocetni == nullptr) throw std::domain_error("Jesi li mala pravila greske do sada?");
        trenutnipok = krajni;
    }
    Tip dajInfo(){
        return trenutnipok->info;
    }
};
template< typename Tip>
int DvostrukaLista<Tip>::prva = 0;
template< typename Tip>
int DvostrukaLista<Tip>::druga = 0;
template< typename Tip>
int DvostrukaLista<Tip>::treca = 0;
template< typename Tip>
int DvostrukaLista<Tip>::cetvrta = 0;
template< typename Tip>
int DvostrukaLista<Tip>::peta = 0;
template< typename Tip>
int DvostrukaLista<Tip>::sesta = 0;
template< typename Tip>
int DvostrukaLista<Tip>::sedma = 0;
template< typename Tip>
int DvostrukaLista<Tip>::osma = 0;
template< typename Tip>
int DvostrukaLista<Tip>::deveta = 0;

template <typename Tip>
class DvostraniRed {
    DvostrukaLista<Tip> lista;
    int brojac;
public:
    DvostraniRed() {  }
    DvostraniRed(DvostraniRed<Tip> &dr){ if(&dr!=this) lista = dr.lista; }
    DvostraniRed<Tip> &operator= (DvostraniRed<Tip> &dr){  if(&dr!=this) lista = dr.lista; return *this; }
    ~DvostraniRed(){ }
    int brojElemenata() const { return lista.brojElemenata(); }
    Tip vrh() {
        if (lista.brojElemenata() != 0) {
            lista.kraj();
            return lista.dajInfo();
        } else {
            throw std::domain_error("Dvostrani red je prazan!");
        }
    } 
    Tip celo() {
        if (lista.brojElemenata() != 0) {
            lista.pocetak();
            return lista.dajInfo();
        } else { 
            throw std::domain_error("Dvostrani red je prazan!");
        }
    }
    void brisi(){
        lista.kraj();
        int brEL(brojElemenata());
        for(int i=0; i < brEL; i++) lista.obrisi();
    }
    Tip skiniSaCela(){
        lista.pocetak();
        Tip a = lista.dajInfo();
        lista.obrisi();
        return a;
    }
    Tip skiniSaVrha(){
        lista.kraj();
        Tip a = lista.dajInfo();
        lista.obrisi();
        return a;
    }
    void staviNaCelo(const Tip &el){
        brojac=0;
        if(brojElemenata() == 0) brojac++;
        if(!brojac) lista.pocetak();
        lista.dodajIspred(el);
    }
    void staviNaVrh(const Tip &el){
        brojac = 0;
        if(brojElemenata() == 0) brojac++;
        if(!brojac) lista.kraj();
        lista.dodajIza(el);
    }
    Tip &operator[] (int i) {
     return lista[i];
    }
    Tip operator[] (int i) const {
     return lista[i];
    }
};


// brojelemenata
template <typename Tip>
void f_1(DvostraniRed<Tip> &l){
    std::cout << "Broj elemenata: " << l.brojElemenata() << std::endl;
    l.staviNaVrh(3);
    std::cout << "Novi broj elemenata nakon dodavanja 1 elementa: " << l.brojElemenata();

    std::cout << std::endl;
}
// vrh
template <typename Tip>
void f_2(DvostraniRed<Tip> &l){

    std::cout << "Citava lista: " << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Element na vrhu: " << l.vrh();
}
// celo
template <typename Tip>
void f_3(DvostraniRed<Tip>&l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Element na celu: " << l.celo();

    std::cout << std::endl;
}
// brisi
template <typename Tip>
void f_4(DvostraniRed<Tip> &l){
    std::cout << "Elementi u redu: ";
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    l.brisi();
    std::cout << "Elementi u redu: ";
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// skiniSaCela
template <typename Tip>
void f_5(DvostraniRed<Tip> &l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon skidanja sa cela: ";
    l.skiniSaCela();
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// skiniSaVrha
template <typename Tip>
void f_6(DvostraniRed<Tip> &l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon skidanja sa vrha: ";
    l.skiniSaVrha();
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// staviNaCelo
template <typename Tip>
void f_7(DvostraniRed<Tip> &l){
    std::cout << "Broj elemenata prije dodavanja na celo: " << l.brojElemenata() << std::endl;
    l.staviNaCelo(1);
    std::cout << "Broj elemenata nakon dodavanja na celo pomocu staviNACelo: " << l.brojElemenata();

    std::cout << std::endl;
}
// staviNaVrh
template <typename Tip>
void f_8(DvostraniRed<Tip> &l){
    std::cout << "Broj elemenata prije dodavanja na vrh: " << l.brojElemenata() << std::endl;
    l.staviNaVrh(1);
    std::cout << "Broj elemenata nakon dodavanja na vrh pomocu staviNAVrh: " << l.brojElemenata();

    std::cout << std::endl;
}


int main() {
    std::cout << "Testiramo DvostrukiRed:" << std::endl << std::endl;

    DvostraniRed<int> lista;
    for (int i(1); i<=5; i++) lista.staviNaVrh(i);

    f_1(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_2(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_3(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_5(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_6(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_7(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_8(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_4(lista);
    return 0;
}