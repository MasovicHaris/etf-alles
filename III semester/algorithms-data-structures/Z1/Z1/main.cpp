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
class Iterator;

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

    friend class Iterator<Tip>;
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

template<typename Tip>
class Iterator {
    const DvostrukaLista<Tip> *listatrenutna;
    Cvor<Tip> *cvor;
public:
    Iterator(const DvostrukaLista<Tip> &lista) : listatrenutna(&lista), cvor(lista.trenutnipok){}
    Iterator(const Lista<Tip> &lista){
        listatrenutna = (const DvostrukaLista<Tip>*) &lista;
        cvor = listatrenutna->pocetni;
    }
    int brojElemenata() {return listatrenutna->brojElemenata(); }
    bool sljedeci() {
        if (listatrenutna->brojElemenata() == 0) return false;                   // bit ce false i za nullptr
        cvor = cvor->sljedeci;
        return true;
    }
    bool prethodni() {
        if (listatrenutna->brojElemenata() == 0) return false;
        cvor = cvor->prethodni;
        return true;
    }
    void kraj() { cvor = listatrenutna->krajni; }
    void pocetak() { cvor = listatrenutna->pocetni; }
    Tip &trenutni(){
        if (listatrenutna->brojElemenata() == 0) throw std::domain_error("Kuda?");
        return cvor->info;
    }
};

template<typename Tip>
Tip dajMaksimum(const Lista<Tip> &nova) {
    Iterator<Tip> iteratorNovi(nova);
    iteratorNovi.pocetak();
    Tip max = iteratorNovi.trenutni();
    for (int i=0; i<iteratorNovi.brojElemenata(); i++) {
        if(iteratorNovi.trenutni() > max) max = iteratorNovi.trenutni();
        iteratorNovi.sljedeci();
    }
    return max;
}


template <typename Tip>
void f_1(Lista<Tip> &l){
    std::cout << "Broj elemenata: " << l.brojElemenata() << std::endl;
    l.dodajIza(3);
    std::cout << "Novi broj elemenata nakon dodavanja 1 elementa: " << l.brojElemenata();

    std::cout << std::endl;
}
// trenutni
template <typename Tip>
void f_2(Lista<Tip> &l){

    std::cout << "Citava lista: " << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;

    std::cout << "Trenutni: " << l.trenutni() << std::endl;
    l.sljedeci();
    std::cout << "Novi trenutni: " << l.trenutni();
    l.prethodni();
    std::cout << std::endl << "Stari trenutni: " << l.trenutni();
    std::cout << std::endl;
}
// prethodni
template <typename Tip>
void f_3(Lista<Tip> &l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Trenutni: " << l.trenutni() << std::endl;
    l.prethodni();
    std::cout << "Novi trenutni: " << l.trenutni();
    l.sljedeci();
    std::cout << std::endl << "Stari trenutni: " << l.trenutni();

    std::cout << std::endl;
}
// sljedeci
template <typename Tip>
void f_4(Lista<Tip> &l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Trenutni: " << l.trenutni() << std::endl;
    l.sljedeci();
    std::cout << "Novi trenutni: " << l.trenutni() << std::endl;
    l.prethodni();
    std::cout << "Stari trenutni: " << l.trenutni();
    std::cout << std::endl;
}
// pocetak
template <typename Tip>
void f_5(Lista<Tip> &l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Trenutni: " << l.trenutni() << std::endl;
    l.pocetak();
    l.dodajIspred(1337);
    std::cout << "Pocetak nakon dodavanja na pocetak: " << std::endl;
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// kraj
template <typename Tip>
void f_6(Lista<Tip> &l){
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Trenutni: " << l.trenutni() << std::endl;
    l.kraj();
    l.dodajIza(1337);
    std::cout << "Kraj nakon dodavanja na kraj: " << std::endl;
    for(int i=0; i < l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// obrisi
template <typename Tip>
void f_7(Lista<Tip> &l){
    std::cout << "Broj elemenata prije brisanja: " << l.brojElemenata() << std::endl;
    l.obrisi();
    std::cout << "Broj elemenata nakon brisanja trenutnog elementa: " << l.brojElemenata();

    std::cout << std::endl;
}
// dodajispred
template <typename Tip>
void f_8(Lista<Tip> &l){
    std::cout << "Prije dodavanja: ";
    for(int i=0; i<l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    l.pocetak();
    for(int i=1; i<=3; i++) l.dodajIspred(1);
    std::cout << "Poslije dodavanja: ";
    for(int i=0; i<l.brojElemenata(); ++i) std::cout << l[i] << " ";

    std::cout << std::endl;
}
// dodajiza
template <typename Tip>
void f_9(Lista<Tip> &l){
    std::cout << "Prije dodavanja: ";
    for(int i=0; i<l.brojElemenata(); ++i) std::cout << l[i] << " ";
    std::cout << std::endl;
    l.pocetak();
    for(int i=1; i<=3; i++) l.dodajIza(2);
    std::cout << "Poslije dodavanja: ";
    for(int i=0; i<l.brojElemenata(); ++i) std::cout << l[i] << " ";

    std::cout << std::endl;
}

int main() {
    
    std::cout << "Testiramo Dvostruka:" << std::endl << std::endl;

    DvostrukaLista<int> lista;
    for (int i(1); i<=5; i++) lista.dodajIspred(i);

    f_1(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_2(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_3(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_4(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_5(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_6(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_7(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_8(lista);
    std::cout << "--------------------------------------" << std::endl;
    f_9(lista);     
    return 0;
}