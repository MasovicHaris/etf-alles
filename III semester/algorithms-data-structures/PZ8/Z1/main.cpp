#include <iostream>
#include <stdexcept>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

template <typename TipKljuca, typename TipVrijednosti>
struct Cvor {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    Cvor *lijevi = nullptr;
    Cvor *desni = nullptr;
    Cvor *rod = nullptr;
};

template <typename TipKljuca, typename TipVrijednosti>
class Mapa {
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual TipVrijednosti &operator[] (TipKljuca k) =0;
    virtual TipVrijednosti  operator[] (TipKljuca k) const =0;
    virtual void obrisi() =0;
    virtual void obrisi(const TipKljuca &k) =0;
    virtual int brojElemenata() const=0;
};

template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti> {
    Cvor<TipKljuca, TipVrijednosti> *korijen;
    int brojEl;
    Cvor<TipKljuca, TipVrijednosti>* &pretragaBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* &noviKorjen, Cvor<TipKljuca, TipVrijednosti>* &p) {
        p = noviKorjen;
        while(p != nullptr && k != p->kljuc){
            if(k < p->kljuc){
                p = p->lijevi;
            }
            else  p = p->desni;
        }
        return p;
    }
    Cvor<TipKljuca, TipVrijednosti>* pretragaBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* noviKorjen) const {
        while(noviKorjen != nullptr && k != noviKorjen->kljuc){
            if(k < noviKorjen->kljuc){
                noviKorjen = noviKorjen->lijevi;
            }
            else  noviKorjen = noviKorjen->desni;
        }
        return noviKorjen;
    }

    bool brisiCvorBST(const TipKljuca &k, Cvor<TipKljuca, TipVrijednosti>* &noviKorjen) {
        Cvor<TipKljuca, TipVrijednosti>* p = noviKorjen;
        Cvor<TipKljuca, TipVrijednosti>* roditelj = nullptr;

        while(p != nullptr && k != p->kljuc){
            roditelj = p;
            if(k < p->kljuc) p = p->lijevi;
            else p = p->desni;
        }
        if( p == nullptr) return false;

        Cvor<TipKljuca, TipVrijednosti>* m = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* pm = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* tmp = nullptr;
        if(p->lijevi == nullptr){
            m = p->desni;
        }
        else if (p->desni == nullptr){
            m = p->lijevi;
        }
        else {
            pm = p;
            m = p->lijevi;
            tmp = m->desni;
            while(tmp != nullptr){
                pm = m;
                m = tmp;
                tmp = m->desni;
            }
            if(pm != p ){
                pm->desni = m->lijevi;
                m->lijevi = p->lijevi;
            }
            m->desni = p->desni;
        }
        if(roditelj == nullptr) noviKorjen = m;
        else {
            if(p == roditelj->lijevi) {
                roditelj->lijevi = m;
            }
            else {
                roditelj->desni = m;
            }
        }
        if(m != nullptr) m->rod = roditelj;
        delete p;
        p = nullptr;
        return true;
    }

    void obrisiSve(Cvor<TipKljuca, TipVrijednosti>* &korje) {
        Cvor<TipKljuca, TipVrijednosti>* noviKorjen = korje;
        if(noviKorjen == nullptr) return;
        obrisiSve(korje->lijevi);
        obrisiSve(korje->desni);
        delete noviKorjen;
    }
    void kopirajBST(Cvor<TipKljuca, TipVrijednosti>* &prviKorjen, Cvor<TipKljuca, TipVrijednosti>* drugiKorjen){
        if (drugiKorjen == nullptr) return;

        Cvor<TipKljuca, TipVrijednosti>* p = drugiKorjen;

        prviKorjen = new Cvor<TipKljuca, TipVrijednosti>();
        prviKorjen->kljuc = p->kljuc;
        prviKorjen->vrijednost = p->vrijednost;
        prviKorjen->lijevi = nullptr;
        prviKorjen->desni = nullptr;
        
        kopirajBST(prviKorjen->lijevi, p->lijevi);
        kopirajBST(prviKorjen->desni, p->desni);
        if(prviKorjen->lijevi != nullptr) prviKorjen->lijevi->rod = prviKorjen;
        if(prviKorjen->desni  != nullptr) prviKorjen->desni->rod = prviKorjen;
        brojEl++;
    }
    void umetniBST(Cvor<TipKljuca, TipVrijednosti>* &prviKorjen, Cvor<TipKljuca, TipVrijednosti>* &cvorN){
        Cvor<TipKljuca, TipVrijednosti>* y = nullptr;
        Cvor<TipKljuca, TipVrijednosti>* x = prviKorjen;
        while(x != nullptr){
            y = x;
            if(cvorN->kljuc < x->kljuc)x = x->lijevi;
            else x = x->desni;
        }
        if(y == nullptr) prviKorjen = cvorN;
        else {
            if(cvorN->kljuc < y->kljuc) y->lijevi = cvorN;
            else y->desni = cvorN;
        }
        cvorN->rod = y;
    }
public:
    BinStabloMapa() { korijen=nullptr; brojEl=0; }
    BinStabloMapa(const BinStabloMapa<TipKljuca, TipVrijednosti> &b ) : korijen(nullptr), brojEl(0) {
        kopirajBST(korijen, b.korijen);
    }
    BinStabloMapa<TipKljuca, TipVrijednosti> &operator=(const BinStabloMapa<TipKljuca, TipVrijednosti> &b) {
        if (this==&b) return *this;
        obrisiSve(korijen);
        brojEl = 0;
        korijen=nullptr;
        kopirajBST(korijen, b.korijen);
        return *this;
    }
    ~BinStabloMapa() { obrisiSve(korijen); korijen = nullptr; brojEl = 0; }
    TipVrijednosti &operator[] (TipKljuca k) {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = pretragaBST(k, korijen);
        if(pomoc == nullptr){
            pomoc = new Cvor<TipKljuca, TipVrijednosti>();
            pomoc->kljuc = k;
            pomoc->lijevi = nullptr;
            pomoc->desni = nullptr;
            pomoc->vrijednost = TipVrijednosti();
            umetniBST(korijen, pomoc);
            brojEl++;
        }
        return pomoc->vrijednost;
    }
    TipVrijednosti  operator[] (TipKljuca k) const {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = pretragaBST(k, korijen);
        if (pomoc == nullptr) return TipVrijednosti();
        else return pomoc->vrijednost;
    }
    void obrisi() {
        obrisiSve(korijen);
        korijen = nullptr;
        brojEl = 0;
    }
    void obrisi(const TipKljuca &k) {
        Cvor<TipKljuca, TipVrijednosti> *pomoc = nullptr;
        pretragaBST(k, korijen, pomoc);
        if(pomoc != nullptr) {
            brisiCvorBST(pomoc->kljuc, korijen);
            pomoc = nullptr;
            brojEl--;
        } 
    }
    int brojElemenata() const { return brojEl; }
};

// 2 zadatak - nizMapa

template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca, TipVrijednosti> {
    int brojEl, kapacitet;
    std::pair<TipKljuca, TipVrijednosti> *nizElementa;
public:
    NizMapa() { nizElementa = nullptr; kapacitet = 50; brojEl = 0; }
    NizMapa(NizMapa<TipKljuca, TipVrijednosti> &m){
        if (&m != this) {
            nizElementa = new std::pair<TipKljuca,TipVrijednosti>[m.brojElemenata()];
            brojEl = m.brojEl;
            kapacitet = m.kapacitet;
            for (int i = 0; i < m.brojElemenata(); i++) {
                 nizElementa[i].first = m.nizElementa[i].first;
                 nizElementa[i].second = m.nizElementa[i].second;
            }
        }
    }
    NizMapa(NizMapa<TipKljuca, TipVrijednosti> &&m) {
        if (&m != this) {
            nizElementa = new std::pair<TipKljuca,TipVrijednosti>[m.brojElemenata()];
            brojEl = m.brojEl;
            kapacitet = m.kapacitet;
            for (int i = 0; i < m.brojElemenata(); i++) {
                nizElementa[i].first = m.nizElementa[i].first;
                nizElementa[i].second = m.nizElementa[i].second;
            }
            delete[] m.nizElementa;
            m.nizElementa = nullptr;
        }
    }
    NizMapa &operator= (NizMapa<TipKljuca, TipVrijednosti> &m) {
        if ( &m != this){

            delete[] nizElementa;
            nizElementa = new std::pair<TipKljuca,TipVrijednosti>[m.brojElemenata()];
            brojEl=m.brojEl;
            kapacitet=m.kapacitet;

            for (int i = 0; i < m.brojElemenata(); i++) {
                nizElementa[i].first = m.nizElementa[i].first;
                nizElementa[i].second = m.nizElementa[i].second;
            }
        }
        return *this;
    }
    ~NizMapa() { this->obrisi(); }
    TipVrijednosti operator[] (TipKljuca k) const {
        for (int i=0; i<brojEl; i++) if (nizElementa[i].first == k) return nizElementa[i].second;
        return TipVrijednosti();
    }
    TipVrijednosti &operator[] (TipKljuca k) {
        if (brojEl==0) {
            nizElementa = new std::pair<TipKljuca, TipVrijednosti>[kapacitet];
            nizElementa[0].first = k;
            nizElementa[0].second = TipVrijednosti();
            brojEl++;
            return nizElementa[0].second;

        } else {
            for (int i=0; i<brojEl; i++)  if (nizElementa[i].first == k) return nizElementa[i].second;

            if ( brojEl == kapacitet) {
                kapacitet *= 2;
                std::pair<TipKljuca,TipVrijednosti> *nk = new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
                for (int i=0; i<brojEl; i++) {
                    nk[i].first = nizElementa[i].first;
                    nk[i].second = nizElementa[i].second;
                }
                delete[] nizElementa;
                nizElementa = nk;
                nk = nullptr;
            }
            nizElementa[brojEl].first = k;
            nizElementa[brojEl].second = TipVrijednosti();
            brojEl++;
            return nizElementa[brojEl-1].second;
        }
    }
    void obrisi() {
        delete[] nizElementa;
        nizElementa = nullptr;
        brojEl = 0;
        kapacitet = 50;
    }
    void obrisi(const TipKljuca &k) {
        if (brojEl==0) throw std::domain_error("Nema elemenata u Mapi");

        int poz = -1;
        for (int i=0; i<brojEl; i++) {
            if (nizElementa[i].first == k) {
                poz=i;
                break;
            }
        }
        if(poz == -1) throw std::domain_error("Nema tog elemenata u Mapi");

        while (poz < brojEl-1) {
            nizElementa[poz].first = nizElementa[poz + 1].first;
            nizElementa[poz].second = nizElementa[poz + 1].second;
            poz++;
        }
        brojEl--;
    }
    int brojElemenata() const { return brojEl; }
};


int main() {
    // glavni testni program
    
BinStabloMapa <int, int> m;                 // binarno stablo mapa
NizMapa<int, int> n;                        // nizmapa 

int vel(10000);                              
    
    std::vector<int> vektor;
    for(int i =0; i < vel; i++){
        vektor.push_back(rand()%vel);
    }
    clock_t vrijeme1 = clock();
    
    for (int i(0); i<vel; i++) {
        m[vektor[i]] = i;                 // trpanje podataka u binstablomapu
    }
    
    clock_t vrijeme2 = clock();
    int ukvrijeme1 = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja rng elemenata (prosjecan slucaj) - binstablo: " << ukvrijeme1 << " ms." << std::endl;

    clock_t vrijeme3 = clock();
    
    for (int i(0); i<vel; i++) {
        n[vektor[i]] = i;                 // trpanje podataka u nizmapu
    }
    
    clock_t vrijeme4 = clock();
    int ukvrijeme2 = (vrijeme4 - vrijeme3) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja rng elemenata (prosjecan slucaj) - nizmapa: " << ukvrijeme2 << " ms." << std::endl;


    clock_t vrijeme5 = clock();
    
    for (int i(0); i<vel; i++) {
        m[vektor[i]] = i;                 // pristupanje svim podacima u binstablomapi
    }
    
    clock_t vrijeme6 = clock();
    int ukvrijeme3 = (vrijeme6 - vrijeme5) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja pristupa svim elementima (prosjecan slucaj) - binstablo: " << ukvrijeme3 << " ms." << std::endl;

    clock_t vrijeme7 = clock();
    
    for (int i(0); i<vel; i++) {
        n[vektor[i]] = i;                 // pristupanje svim podacima u nizmpai
    }
    
    clock_t vrijeme8 = clock();
    int ukvrijeme4 = (vrijeme8 - vrijeme7) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja pristupa svim elementima (prosjecan slucaj) - nizmapa: " << ukvrijeme4 << " ms." << std::endl;

    m.obrisi();
    n.obrisi();
    
    // komentar
    // Ovolika razlika u izvršavanju je radi kompleknosti jedne i druge mape, odnosno:
    // - Nizmapa ima kompleksnost O(n).
    // - Binstablo ima kompleknost O(log n).
    // Binstablo će imati manje vrijeme izvršavanja nego nizmapa, što nalaže logika, odnosno za 10k elemenata test gornji potvrđuje ovaj komentar.
    // Razlog je što pristupanje i generisanje zahtjeva O(n) kompleksnost, dok kod binstabla zahtjeva O(log n)
    return 0;
}
