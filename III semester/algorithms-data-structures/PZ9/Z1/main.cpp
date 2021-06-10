#include <iostream>
#include <stdexcept>
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
class Mapa
{
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
class HashMapa : public Mapa<TipKljuca, TipVrijednosti> {
    unsigned int brojEl, kapacitet;
    std::pair<TipKljuca, TipVrijednosti> *nizElementa;
    unsigned int (*f)(TipKljuca, unsigned int) = 0;

public:
    HashMapa() {
        nizElementa = nullptr;
        kapacitet = 50;
        brojEl = 0;
    }
    HashMapa(HashMapa<TipKljuca, TipVrijednosti> &m)  {
        kapacitet = m.kapacitet;
        brojEl = m.brojEl;
        f = m.f;

        nizElementa = new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for (int i = 0; i < m.kapacitet; i++) {
            nizElementa[i] = m.nizElementa[i];
        }
    }
    HashMapa(HashMapa<TipKljuca, TipVrijednosti> &&m) {
        brojEl = m.brojEl;
        kapacitet = m.kapacitet;
        nizElementa = m.nizElementa;
        f = m.f;
    }
    HashMapa &operator= (const HashMapa<TipKljuca, TipVrijednosti> &m) {
        if ( &m != this) {

            delete[] nizElementa;
            nizElementa = new std::pair<TipKljuca,TipVrijednosti>[m.kapacitet];
            brojEl=m.brojEl;
            kapacitet=m.kapacitet;

            for (int i = 0; i < m.kapacitet; i++) {
                nizElementa[i].first = m.nizElementa[i].first;
                nizElementa[i].second = m.nizElementa[i].second;
            }
            f = m.f;
        }
        return *this;
    }
    HashMapa &operator= (HashMapa<TipKljuca, TipVrijednosti> &&m) {
        if(this == &m) return *this;
        delete []nizElementa;
        kapacitet = m.kapacitet;
        brojEl = m.brojEl;
        f = m.f;
        nizElementa = new std::pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0; i < kapacitet; i++) nizElementa[i] = m.nizElementa[i];
        return *this;

    }
    ~HashMapa() {
        this->obrisi();
    }
    TipVrijednosti operator[] (TipKljuca k) const {
        unsigned int adresa = f(k, kapacitet);
        if (nizElementa[adresa].first == k) return nizElementa[adresa].second;

        for(int i = adresa+1; i < kapacitet; i++) {
            if(nizElementa[i].first == k) return nizElementa[i].second;
        }
        for(int i = 0; i < adresa; i++) {
                if(nizElementa[i].first == k) return nizElementa[i].second;
        }
        return TipVrijednosti();
    }
    TipVrijednosti &operator[] (TipKljuca k) {
        if(f == 0) throw "Nema heš funkcije. Molimo dođite nam opet!";
        unsigned int adresa = f(k, kapacitet);
        if (brojEl==0) {
            nizElementa = new std::pair<TipKljuca, TipVrijednosti>[kapacitet];
            nizElementa[adresa].first = k;
            nizElementa[adresa].second = TipVrijednosti();
            brojEl++;
            for(int i=0; i < kapacitet; i++) if(i != adresa) nizElementa[i].first = TipKljuca();
            return nizElementa[adresa].second;

        } else {
            if (nizElementa[adresa].first == k) return nizElementa[adresa].second;

            for(int i = adresa+1; i < kapacitet; i++) {
                if(nizElementa[i].first == k) return nizElementa[i].second;
            }
            for(int i = 0; i < adresa; i++) {
                if(nizElementa[i].first == k) return nizElementa[i].second;
            }

            for(int i = adresa+1; i < kapacitet; i++) {
                if(nizElementa[i].first == TipKljuca()) {
                    nizElementa[i].first = k;
                    nizElementa[i].second = TipVrijednosti();
                    brojEl++;
                    return nizElementa[i].second;
                }
            }
            for(int i = 0; i < adresa; i++) {
                if(nizElementa[i].first == TipKljuca()) {
                    nizElementa[i].first = k;
                    nizElementa[i].second = TipVrijednosti();
                    brojEl++;
                    return nizElementa[i].second;
                }
            }


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
            for(int i= brojEl+1; i < kapacitet; i++) nizElementa[i].first = TipKljuca();
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
        unsigned int adresa = f(k, kapacitet);
        int poz = -1;
        if(nizElementa[adresa].first == k) poz = adresa;

        if(poz == -1) {
            for (int i = adresa+1; i < kapacitet; i++) {
                if (nizElementa[i].first == k) {
                    poz = i;
                    break;
                }
            }
        }

        if(poz == -1) {
            for (int i = 0; i < adresa; i++) {
                if (nizElementa[i].first == k) {
                    poz = i;
                    break;
                }
            }
        }


        if(poz == -1) throw std::domain_error("Nema tog elemenata u Mapi");

        nizElementa[poz].first = TipKljuca();
        nizElementa[poz].second = TipVrijednosti();
        /*
        while (poz < kapacitet-1) {
            nizElementa[poz].first = nizElementa[poz + 1].first;
            nizElementa[poz].second = nizElementa[poz + 1].second;
            poz++;
        }   */
        brojEl--;
    }
    int brojElemenata() const {
        return brojEl;
    }
    void definisiHashFunkciju (unsigned int (*fun)(TipKljuca, unsigned int)) {
        if (fun==nullptr)throw std::domain_error("Not defined");
        f=fun;
    }
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

unsigned int mojhash2(int ulaz, unsigned int max) {
	unsigned int suma=23; 
	suma = suma*31 + ulaz;
	return suma % max;
}

int main()
{
    // glavni testni program
    
BinStabloMapa <int, int> m;                 // binarno stablo mapa
NizMapa<int, int> n;                        // nizmapa 
HashMapa<int, int> h;
h.definisiHashFunkciju(mojhash2);
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

    clock_t vrijemeH1 = clock();
    
    for (int i(0); i<vel; i++) {
        h[vektor[i]] = i;                 // trpanje podataka u hashmapa
    }
    
    clock_t vrijemeH2 = clock();
    int ukvrijeme23 = (vrijemeH2 - vrijemeH1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja dodavanja rng elemenata (prosjecan slucaj) /mojhash2/ - hashmapa: " << ukvrijeme23 << " ms." << std::endl;


    std::cout << std::endl;



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

    clock_t vrijeme71 = clock();
    
    for (int i(0); i<vel; i++) {
        h[vektor[i]] = i;                 // pristupanje svim podacima u hashmapi
    }
    
    clock_t vrijeme81 = clock();
    int ukvrijeme41 = (vrijeme81 - vrijeme71) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja pristupa svim elementima (prosjecan slucaj) /mojhash2/ - hashmapa: " << ukvrijeme41 << " ms." << std::endl;

      std::cout << std::endl;


    clock_t vrijeme7123 = clock();
    for(int i=0; i< 1000;i++) m[i] = i;
    for(int i=0; i< 1000;i++) m.obrisi(i);
    
    clock_t vrijeme8123 = clock();
    int ukvrijeme4123 = (vrijeme8123 - vrijeme7123) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja brisanje 1k elementa po 1 - binstablo: " << ukvrijeme4123 << " ms." << std::endl;


    clock_t vrijeme7124 = clock();
    for(int i=0; i< 1000;i++) n[i] = i;
    for(int i=0; i< 1000;i++) n.obrisi(i);
    
    clock_t vrijeme8124 = clock();
    int ukvrijeme4124 = (vrijeme8124 - vrijeme7124) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja brisanje 1k elementa po 1 - nizmapa: " << ukvrijeme4124 << " ms." << std::endl;




    clock_t vrijeme712 = clock();
    for(int i=0; i< 1000;i++) h[i] = i;
    for(int i=0; i< 1000;i++) h.obrisi(i);
    
    clock_t vrijeme812 = clock();
    int ukvrijeme412 = (vrijeme812 - vrijeme712) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja brisanje 1k elementa po 1 /mojhash2/ - hashmapa: " << ukvrijeme412 << " ms." << std::endl;



    
    // kada gledamo dodavanje rng elemenata, tj. prosjecan slucaj kod hashmape, imamo vece vrijeme izvrsavanja
    // sto moze biti posljedica velikih kolizija u odnosu na binstablo i nizmapu
    
    // kada gledamo pristupanje elementima, vidim da pristupanje je manje nego za binarno stablo sto je logicno, ali vjerovatno je hash funkcija
    // losa samim tim vjerovatno imamo vise kolizija
    // u protivnom zahtjeva samo vrijeme koje je potrebno za racunanje heša
    
    // kada gledamo brisanje elemenata 1po1 od nekih 1k elemenata
    // vidimo da je tu hashmapa brza od nizmape, jer moze efikasno naci hash elementa sacuvan ali isto moze bit O(n) kompleksnosti
    // odnosno najbrze brisanje ce biti kod binstabla, pa hashmapa, pa tek nizmapa
    
    return 0;
}
