#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

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
class NizLista : public Lista<Tip> {                                             
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
    ~NizLista() { if(pocetni != nullptr) { delete[] pocetni; pocetni=nullptr; trenutnipok = nullptr; brojEl=0; } }
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
                maxkapacitet = 50;
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
    void BrisiSve(){
        if(pocetni != nullptr) {
            
        delete[] pocetni;
        pocetni = nullptr;
        trenutnipok = nullptr;
        maxkapacitet = 0; brojEl = 0;
        }
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
class Stek {
    NizLista<Tip> lista;
    int brojac=0;
public:
    Stek() { }
    Stek<Tip> &operator= (const Stek<Tip> &stek) { lista = stek.lista; }
    Stek<Tip> operator= (Stek<Tip> &&stek) { lista = stek.lista; }
    Stek (const Stek<Tip> &stek){  lista = stek.lista;}
    Stek (Stek<Tip> &&stek){  lista = stek.lista; }
    void brisi() { lista.BrisiSve(); }
    void stavi (const Tip &el){
        if(lista.brojElemenata() == 0) brojac = 0;
        if(brojac != 0){ lista.kraj(); brojac++;}
        lista.dodajIza(el);
        lista.kraj();
    }
    Tip skini(){
        if(lista.brojElemenata() == 0) throw std::domain_error("Greska!");
        lista.kraj();
        Tip a(lista.trenutni());
        lista.obrisi();
        return a;
    }
    Tip &vrh() { 
        if(lista.brojElemenata() == 0) throw std::domain_error("Greska!"); 
        lista.kraj();
        return lista.trenutni();
    }
    int brojElemenata() { return lista.brojElemenata(); }
    Tip operator [](int i){
        return lista[i];
    }
};

// brisi
template <typename Tip>
void f_1(Stek<Tip> &l){
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi steka: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Stek nakon brisanja: " << std::endl;
    l.brisi();
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// stavi
template <typename Tip>
void f_2(Stek<Tip> &l){
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi steka: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Stek nakon dodavanja 1 elementa: " << std::endl;
    l.stavi(1337);
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// skini
template <typename Tip>
void f_3(Stek<Tip> &l){
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi steka: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Stek nakon skidanja 1 elementa: " << std::endl;
    l.skini();
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// vrh
template <typename Tip>
void f_4(Stek<Tip> &l){
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi steka: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Stek nakon stavljanja 1 elementa: " << std::endl;
    l.stavi(1337);
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    
    std::cout << std::endl << "Element na vrhu: " << l.vrh();
    std::cout << std::endl;
}
// brojelemenata
template <typename Tip>
void f_5(Stek<Tip> &l){
    std::cout << "Broj elemenata u steku: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi steka: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Stek nakon dodavanja 1 elementa: " << std::endl;
    l.stavi(1338);
    std::cout << "Broj elemenata u steku nakon dodavanja 1 elementa: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
} 



int main() {
    Stek<int> s;
    for (int i(1); i<=5; i++) s.stavi(i);
    
    f_1(s);
    std::cout << "------------------------------------" << std::endl;
    f_2(s);
    std::cout << "------------------------------------" << std::endl;
    f_3(s);
    std::cout << "------------------------------------" << std::endl;
    f_4(s);
    std::cout << "------------------------------------" << std::endl;
    f_5(s);
    std::cout << "------------------------------------" << std::endl;
    return 0;
}
