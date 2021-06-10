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
class NizLista : public Lista<Tip> {                                             // mrsko mi dodavati Tip** :p
    int maxkapacitet;                                                       
    int brojEl;
    Tip *pocetni = nullptr;
    Tip *trenutnipok = nullptr;
    static int prva, druga, treca, cetvrta, peta, sesta, sedma, osma, deveta;
public:
    NizLista() { brojEl=0; pocetni = nullptr; trenutnipok = nullptr; maxkapacitet = 50; }
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
    int brojElemenata() const { return brojEl; prva++; }
    Tip &trenutni() { if (brojEl == 0) throw std::domain_error("Greska!"); return *trenutnipok; druga++; }
    Tip trenutni() const { if (brojEl == 0) throw std::domain_error("Greska!"); return *trenutnipok; druga++; }
    bool prethodni() {
        treca++;
        if( brojEl == 0) throw std::domain_error("Greska!");
        if(trenutnipok == pocetni) return false;
        trenutnipok = trenutnipok -1;
        return true;
    }
    bool sljedeci() {
        cetvrta++;
        if(brojEl == 0) throw std::domain_error("Greska!");
        if(trenutnipok == pocetni + brojEl - 1) return false;
        trenutnipok = trenutnipok + 1;
        return true;
    }
    void pocetak(){
        peta++;
        if(brojEl == 0) throw std::domain_error("Greska!");
        trenutnipok = pocetni;
    }
    void kraj(){
        sesta++;
        if(brojEl == 0) throw std::domain_error("Greska!");
        trenutnipok = pocetni + brojEl - 1;
    }
    void obrisi(){
        sedma++;
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
        osma++;
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
        deveta++;
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
template< typename Tip>
int NizLista<Tip>::prva = 0;
template< typename Tip>
int NizLista<Tip>::druga = 0;
template< typename Tip>
int NizLista<Tip>::treca = 0;
template< typename Tip>
int NizLista<Tip>::cetvrta = 0;
template< typename Tip>
int NizLista<Tip>::peta = 0;
template< typename Tip>
int NizLista<Tip>::sesta = 0;
template< typename Tip>
int NizLista<Tip>::sedma = 0;
template< typename Tip>
int NizLista<Tip>::osma = 0;
template< typename Tip>
int NizLista<Tip>::deveta = 0;

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
    static int prva, druga, treca, cetvrta, peta, sesta, sedma, osma, deveta;
public:
    JednostrukaLista() { pocetni = nullptr; trenutnipok = nullptr; brElemenata=0; }
    JednostrukaLista (const JednostrukaLista<Tip> &l) {
        try{
            Cvor<Tip> *novi = l.pocetni;
            pocetni = new Cvor<Tip>();                                          // novi cvor
            if(l.pocetni == l.trenutnipok) trenutnipok = pocetni;               // ako je treutni jedank pocetnom
            Cvor<Tip> *novcat = pocetni;
            novcat->sljedeci = nullptr;
            novcat->info = novi->info;

            while(novi->sljedeci != nullptr){

                novcat->sljedeci = new Cvor<Tip>();
                novcat->sljedeci->info = novi->sljedeci->info;
                if(novi->sljedeci == l.trenutnipok) trenutnipok = novcat->sljedeci;

                novi = novi->sljedeci;
                novcat = novcat->sljedeci;
            }
            novcat->sljedeci = nullptr;
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
            Cvor<Tip> *novi = l.pocetni;
            pocetni = new Cvor<Tip>();                                          // novi cvor
            if(l.pocetni == l.trenutnipok) trenutnipok = pocetni;               // ako je treutni jedank pocetnom
            Cvor<Tip> *novcat = pocetni;
            novcat->sljedeci = nullptr;
            novcat->info = novi->info;

            while(novi->sljedeci != nullptr){

                novcat->sljedeci = new Cvor<Tip>();
                novcat->sljedeci->info = novi->sljedeci->info;
                if(novi->sljedeci == l.trenutnipok) trenutnipok = novcat->sljedeci;

                novi = novi->sljedeci;
                novcat = novcat->sljedeci;
            }
            novcat->sljedeci = nullptr;
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

        auto p(pocetni);
        while(p->sljedeci != trenutnipok) p = p->sljedeci;
        trenutnipok = p;
        p = nullptr;
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
            pocetni = nullptr; trenutnipok = 0; brElemenata = 0;
            return;
        }
        if(trenutnipok->sljedeci == nullptr && trenutnipok != pocetni){                                                // zadnji slucaj
            auto p(pocetni);
            while(p->sljedeci != trenutnipok) p = p->sljedeci;
            delete trenutnipok;
            trenutnipok = nullptr;
            trenutnipok = p; trenutnipok->sljedeci = nullptr;
            p = nullptr;
            brElemenata--;
            return;
        }

        if(trenutnipok == pocetni){
            Cvor<Tip> *nov = pocetni;
            pocetni = pocetni->sljedeci;
            delete nov; nov = nullptr;
            brElemenata--;
            trenutnipok = pocetni;
            return;
        }


        auto p(pocetni);
        while(p->sljedeci != nullptr && p->sljedeci != trenutnipok) p = p->sljedeci;                                   // opci slucaj
        p->sljedeci = trenutnipok->sljedeci;
        trenutnipok->sljedeci = nullptr;
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
        deveta++;
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

            if(trenutnipok->sljedeci == nullptr){                                                   // zadnji element
                Cvor<Tip> *pokazivac = new Cvor<Tip>();
                pokazivac->sljedeci = nullptr;
                pokazivac->info = el;
                trenutnipok->sljedeci = pokazivac;
                brElemenata++;
                return;
            }

            Cvor<Tip>  *pokazivac = new Cvor<Tip>();
            pokazivac->sljedeci = trenutnipok->sljedeci;
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
        auto p(trenutnipok);
        while(p->sljedeci != nullptr) p = p->sljedeci;
        trenutnipok = p;
    }

};
template< typename Tip>
int JednostrukaLista<Tip>::prva = 0;
template< typename Tip>
int JednostrukaLista<Tip>::druga = 0;
template< typename Tip>
int JednostrukaLista<Tip>::treca = 0;
template< typename Tip>
int JednostrukaLista<Tip>::cetvrta = 0;
template< typename Tip>
int JednostrukaLista<Tip>::peta = 0;
template< typename Tip>
int JednostrukaLista<Tip>::sesta = 0;
template< typename Tip>
int JednostrukaLista<Tip>::sedma = 0;
template< typename Tip>
int JednostrukaLista<Tip>::osma = 0;
template< typename Tip>
int JednostrukaLista<Tip>::deveta = 0;

// TEST METODE

// broj elemenata
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
    
    std::cout << "Testiramo JEDNOSTRUKALISTA:" << std::endl << std::endl;
    
    JednostrukaLista<int> lista;
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
    
    std::cout << std::endl;
    std::cout << "Testiramo NIZLISTA:" << std::endl << std::endl;
    
    NizLista<int> lista2;
    for (int i(1); i<=5; i++) lista2.dodajIspred(i);
    f_1(lista2); 
    std::cout << "--------------------------------------" << std::endl;
    f_2(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_3(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_4(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_5(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_6(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_7(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_8(lista2);
    std::cout << "--------------------------------------" << std::endl;
    f_9(lista2);
    return 0;
}