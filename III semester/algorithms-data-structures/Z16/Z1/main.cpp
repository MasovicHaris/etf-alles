#include <iostream>
#include <stdexcept>

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

template <typename TipKljuca, typename TipVrijednosti>
void funkcija1(NizMapa<TipKljuca, TipVrijednosti> &m){
    std::cout << "Testna funkcija 1 (Pretraga nepostojecih elemenata)" << std::endl;
    std::cout << std::endl;
    std::cout << "Pretraga BH klubova: FK Zeljeznicar i FK Sarajevo" << std::endl;
    m["FK Zeljeznicar"] = "Sampion";
    m["FK Sarajevo"] = "Nije sampion";
    std::cout << "FK Zeljeznicar" << " - " << m["FK Zeljeznicar"] << std::endl;
    std::cout << "FK Sarajevo" << " - " << m["FK Sarajevo"] << std::endl;
    std::cout << std::endl;
}

template <typename TipKljuca, typename TipVrijednosti>
void funkcija2(NizMapa<TipKljuca, TipVrijednosti> &m){
    std::cout << "Testna funkcija 2 (Brisanje broja 1337 iz niz mape)" << std::endl;
    std::cout << std::endl;
    try{
        m.obrisi(1337);
    }
    catch(...){
        std::cout << "IZUZETAK: " << "Broj 1337 se ne nalazi u mapi!" << std::endl;
    }
    std::cout << std::endl;
}

template <typename TipKljuca, typename TipVrijednosti>
void funkcija3(NizMapa<TipKljuca, TipVrijednosti> m){
    std::cout << "Testna funkcija 3 (Brisanje čitave niz mape)" << std::endl;
    std::cout << std::endl;
    try{
        std::cout << "Broj elemenata prije brisanja: " << m.brojElemenata() << std::endl;
        m.obrisi();
        std::cout << "Broj elemenata nakon brisanja: " << m.brojElemenata() << std::endl;
    }
    catch(...){
        std::cout << "Nema elemenata kolega" << std::endl;
    }
    std::cout << std::endl << "Čitava liga obrisana (tugi plaki - mora sa i kolega)" << std::endl;
    std::cout << std::endl;
}

template <typename TipKljuca, typename TipVrijednosti>
void funkcija4(NizMapa<TipKljuca, TipVrijednosti> m){
    std::cout << "Testna funkcija 4 (mapa koja sadrzi double brojeve i 2 * te iste brojeve)" << std::endl;
    std::cout << std::endl;
    try{
        m.obrisi();
        m[2.1] = 4.2;
        std::cout << "2.1"<< " - " << m[2.1] << std::endl;
        m.obrisi(3.0);
    }
    catch(...){
        std::cout << "IZUZETAK: " << "Nema tog kljuca!" << std::endl;
    }
    std::cout << std::endl;
}

template <typename TipKljuca, typename TipVrijednosti>
void funkcija5(NizMapa<TipKljuca, TipVrijednosti> &m){
    std::cout << "Testna funkcija 5 (Ispis nadjenog elementa i broj elemenata)" << std::endl;
    m["Dodji da ostarimooo"] = 3.14;
    std::cout << "Dodji da ostarimooo " << m["Dodji da ostarimooo"] << " ~ Broj elemenata (mora biti 1): " << m.brojElemenata() << std::endl; // 1 
    m.obrisi("Dodji da ostarimooo");
    std::cout << "Mora biti 0: " << m.brojElemenata(); // 2
    m["Ciganka sam"] = 2.78;
    std::cout << std::endl << " " << m["Dodji da ostarimooo"] << std::endl;                  // nema sta da se ispise, vraca default tj. 0 u ovom slucaju
    std::cout << "Ciganka sam " << m["Ciganka sam"] << std::endl;
     
    std::cout << std::endl;
}

int main(){
    NizMapa<std::string,std::string> m;
    NizMapa<int, int> m2;
    NizMapa<int, double> m3;
    NizMapa<double, double> m4;
    NizMapa<std::string,double> m5;
    funkcija1(m);
    std::cout << "--------------------------------------------" << std::endl;
    funkcija2(m2);
    std::cout << "--------------------------------------------" << std::endl;
    m3[123] = 3.555;
    funkcija3(m3);
    std::cout << "--------------------------------------------" << std::endl;
    funkcija4(m4);
    std::cout << "--------------------------------------------" << std::endl;
    funkcija5(m5);
    std::cout << "--------------------------------------------" << std::endl;
    return 0;
}
