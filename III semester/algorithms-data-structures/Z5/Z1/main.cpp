#include <iostream>
#include <vector>
#include <stdexcept>
#include <queue>

using namespace std;
template <typename TipOznake>
class Grana;
template <typename TipOznake>
class Cvor;
template <typename TipOznake>
class GranaIterator;
template <typename TipKljuca, typename TipVrijednosti>
struct CvorN {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    CvorN *next = nullptr;
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
class  HashMapaLan : public Mapa<TipKljuca, TipVrijednosti>
{
    unsigned int brojEl, kapacitet;
    CvorN<TipKljuca,TipVrijednosti>** nizElementa;
    unsigned int (*f)(TipKljuca, unsigned int) = 0;

public:
    HashMapaLan() {
        nizElementa = nullptr;
        kapacitet = 50;
        brojEl = 0;
    }
    HashMapaLan( HashMapaLan<TipKljuca, TipVrijednosti> &m)  {
        kapacitet = m.kapacitet;
        brojEl = m.brojEl;
        f = m.f;

        nizElementa = new CvorN<TipKljuca,TipVrijednosti>*[kapacitet];
        for(int i = 0; i < kapacitet; i++) nizElementa[i] = nullptr;

        for (int i = 0; i < m.kapacitet; i++) {
            if(m.nizElementa[i] != nullptr) {
                nizElementa[i] = new CvorN<TipKljuca,TipVrijednosti>();
                nizElementa[i]->kljuc = m.nizElementa[i]->kljuc;
                nizElementa[i]->vrijednost = m.nizElementa[i]->vrijednost;
                auto r = nizElementa[i];
                auto p = m.nizElementa[i];
                while(p->next != nullptr) {
                    r->next = new CvorN<TipKljuca,TipVrijednosti>();
                    p = p->next;
                    r->next->kljuc = p->kljuc;
                    r->next->vrijednost = p->vrijednost;
                }
            }
        }
    }
    HashMapaLan( HashMapaLan<TipKljuca, TipVrijednosti> &&m) {
        brojEl = m.brojEl;
        kapacitet = m.kapacitet;
        nizElementa = m.nizElementa;
        f = m.f;
    }
    HashMapaLan &operator= (const  HashMapaLan<TipKljuca, TipVrijednosti> &m) {
        if ( &m != this) {

            for(int i = 0; i < kapacitet; i++) {
                if (nizElementa[i] != nullptr) {
                    while(nizElementa[i] != nullptr) {
                        auto trenutni = nizElementa[i];
                        nizElementa[i] = nizElementa[i]->next;
                        delete trenutni;
                    }
                    nizElementa[i] = nullptr;
                }
            }
            delete [] nizElementa;

            kapacitet = m.kapacitet;
            brojEl = m.brojEl;
            f = m.f;

            nizElementa = new CvorN<TipKljuca,TipVrijednosti>*[kapacitet];
            for(int i = 0; i < kapacitet; i++) nizElementa[i] = nullptr;

            for (int i = 0; i < m.kapacitet; i++) {
                if(m.nizElementa[i] != nullptr) {
                    nizElementa[i] = new CvorN<TipKljuca,TipVrijednosti>();
                    nizElementa[i]->kljuc = m.nizElementa[i]->kljuc;
                    nizElementa[i]->vrijednost = m.nizElementa[i]->vrijednost;
                    auto r = nizElementa[i];
                    auto p = m.nizElementa[i];
                    while(p->next != nullptr) {
                        r->next = new CvorN<TipKljuca,TipVrijednosti>();
                        p = p->next;
                        r->next->kljuc = p->kljuc;
                        r->next->vrijednost = p->vrijednost;
                    }
                }
            }
        }
        return *this;
    }
    HashMapaLan &operator= ( HashMapaLan<TipKljuca, TipVrijednosti> &&m) {
        if(this == &m) return *this;
        for(int i = 0; i < kapacitet; i++) {
            if (nizElementa[i] != nullptr) {
                while(nizElementa[i]->next != nullptr) {
                    auto trenutni = nizElementa[i];
                    nizElementa[i] = nizElementa[i]->next;
                    delete trenutni;
                }
                delete nizElementa[i];
            }
        }
        delete [] nizElementa;
        nizElementa = m.nizElementa;
        brojEl=m.brojEl;
        kapacitet=m.kapacitet;
        f = m.f;
        return *this;
    }
    ~HashMapaLan() {
        this->obrisi();
    }
    TipVrijednosti operator[] (TipKljuca k) const {
        if(f == 0) throw "Nema heš funkcije. Molimo dođite nam opet!";
        unsigned int adresa = f(k, kapacitet);
        if (nizElementa[adresa] != nullptr) {
            auto p = nizElementa[adresa];
            while(p != nullptr) {
                if(p->kljuc == k) return p->vrijednost;
                p = p->next;
            }
        }
        return TipVrijednosti();
    }
    TipVrijednosti &operator[] (TipKljuca k) {
        if(f == 0) throw "Nema heš funkcije. Molimo dođite nam opet!";
        unsigned int adresa = f(k, kapacitet);
        if (brojEl==0) {
            nizElementa = new CvorN<TipKljuca,TipVrijednosti>*[kapacitet];
            nizElementa[adresa] = new CvorN<TipKljuca,TipVrijednosti>();
            nizElementa[adresa]->kljuc = k;
            nizElementa[adresa]->vrijednost = TipVrijednosti();
            brojEl++;

            for(int i=0; i < kapacitet; i++) if(i != adresa) nizElementa[i] = nullptr;
            return nizElementa[adresa]->vrijednost;

        } else {
            if (nizElementa[adresa] != nullptr ) {
                auto p = nizElementa[adresa];
                while(p!= nullptr) {
                    if(p->kljuc == k) return p->vrijednost;
                    p = p->next;
                }
            }


            if(nizElementa[adresa] == nullptr) {
                nizElementa[adresa] = new CvorN<TipKljuca,TipVrijednosti>();
                nizElementa[adresa]->kljuc = k;
                nizElementa[adresa]->vrijednost = TipVrijednosti();
                brojEl++;
                return nizElementa[adresa]->vrijednost;
            } else {
                if(k < nizElementa[adresa]->kljuc) {
                    auto pomocni = nizElementa[adresa];
                    nizElementa[adresa] = new CvorN<TipKljuca,TipVrijednosti>();
                    nizElementa[adresa]->kljuc = k;
                    nizElementa[adresa]->vrijednost = TipVrijednosti();
                    nizElementa[adresa]->next = pomocni;
                    brojEl++;
                    return nizElementa[adresa]->vrijednost;
                }

                auto prije = nizElementa[adresa];
                auto p = nizElementa[adresa];
                while(p->next != nullptr && p->kljuc < k) {
                    prije = p;
                    p = p->next;
                }
                if(p->next == nullptr) {
                    p->next = new CvorN<TipKljuca,TipVrijednosti>();
                    p->next->kljuc = k;
                    p->next->vrijednost = TipVrijednosti();
                    brojEl++;
                    return p->next->vrijednost;
                } else {
                    auto p1 = new CvorN<TipKljuca,TipVrijednosti>();
                    p1->kljuc = k;
                    p1->vrijednost = TipVrijednosti();
                    prije->next = p1;
                    p1->next = nizElementa[adresa];
                    brojEl++;
                    return p1->vrijednost;
                }
            }
        }
    }
    void obrisi() {
        if(brojEl == 0 ) return;
        for(int i = 0; i < kapacitet; i++) {
            if (nizElementa[i] != nullptr) {
                while(nizElementa[i] != nullptr) {
                    auto trenutni = nizElementa[i];
                    nizElementa[i] = nizElementa[i]->next;
                    delete trenutni;
                }
                nizElementa[i] = nullptr;
            }
        }
        delete [] nizElementa;
        nizElementa = nullptr;
        brojEl = 0;
        kapacitet = 50;
    }
    void obrisi(const TipKljuca &k) {
        if (brojEl==0) throw std::domain_error("Nema elemenata u Mapi");
        unsigned int adresa = f(k, kapacitet);
        bool ima = false;
        if(nizElementa[adresa] != nullptr) {
            if(nizElementa[adresa]->kljuc == k ) {
                ima = true;
                nizElementa[adresa]->vrijednost = TipVrijednosti();
                brojEl--;
                return;
            }
            auto pok = nizElementa[adresa];
            while(pok != nullptr) {
                if(pok->next != nullptr) {
                    auto p = pok->next;
                    if(p->kljuc == k ) {
                        ima = true;
                        p->vrijednost = TipVrijednosti();
                        break;
                    }
                }
                pok = pok->next;
            }
            brojEl--;
        }
        if(!ima) throw std::domain_error("Nema tog elemenata u Mapi");
    }
    int brojElemenata() const {
        return brojEl;
    }
    void definisiHashFunkciju (unsigned int (*fun)(TipKljuca, unsigned int)) {
        if (fun==nullptr)throw std::domain_error("Not defined");
        f=fun;
    }
};


template <typename TipOznake>
class UsmjereniGraf
{
public:
    UsmjereniGraf()= default;
    virtual int dajBrojCvorova()= 0;
    virtual ~UsmjereniGraf() {}
    virtual void postaviBrojCvorova(int broj) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina = 0) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina = 0) = 0 ;
    virtual float dajTezinuGrane(int polazni, int dolazni) = 0;
    virtual bool postojiGrana(int polazni, int dolazni) = 0;
    virtual void postaviOznakuCvora(int broj, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuCvora(int broj) = 0;
    virtual void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuGrane(int polazni, int dolazni) = 0;
    virtual Cvor<TipOznake> &dajCvor(int broj) = 0;
    virtual Grana<TipOznake> &dajGranu(int polazni, int dolazni) = 0;
    virtual GranaIterator<TipOznake> dajGranePocetak() = 0;
    virtual GranaIterator<TipOznake> dajGraneKraj() = 0;
};

template<typename TipOznake>
class Cvor
{
    TipOznake oznaka;
    UsmjereniGraf<TipOznake> *graf;
    int redniBroj;
public:
    Cvor(int rbroj, UsmjereniGraf<TipOznake> &g) {
        graf = &g;
        redniBroj = rbroj;
    }

    TipOznake dajOznaku() const {
        return oznaka;
    }

    void postaviOznaku(TipOznake o) {
        oznaka = o;
    }

    int dajRedniBroj() const {
        return redniBroj;
    }
};


template <typename TipOznake>
class Grana
{
    int p;
    int d;
    float tezina;
    TipOznake oznaka;
    UsmjereniGraf<TipOznake> *graf;
public:
    Grana( int a, int b, UsmjereniGraf<TipOznake> &g, float t=0) {
        p=a;
        d=b;
        tezina=t;
        graf=&g;
    }

    Grana(const Grana<TipOznake> &g) {
        p=g.p;
        d=g.d;
        tezina=g.tezina;
        graf=g.graf;
        oznaka=g.oznaka;
    }

    float dajTezinu() {
        return tezina;
    }
    void postaviTezinu(float t=0) {
        graf->dajGranu(p,d).tezina=t;
        tezina=t;
    }
    TipOznake dajOznaku() {
        return oznaka;
    }
    void postaviOznaku(TipOznake o) {
        graf->dajGranu(p,d).oznaka = o;
        oznaka=o;
    }
    bool operator == (Grana<TipOznake> g) {
        if (g.p==p && g.d==d) return true;
        return false;
    }
    bool operator != (Grana<TipOznake> g) {
        if (g.p==p && g.d==d) return false;
        return true;
    }
    Cvor<TipOznake> dajPolazniCvor() {
        return graf->dajCvor(p);
    }
    Cvor<TipOznake> dajDolazniCvor() {
        return graf->dajCvor(d);
    }
};

template<typename TipOznake>
class GranaIterator
{
    int dolazni, polazni, pozicija;
    std::vector<Grana<TipOznake>> grane;
    UsmjereniGraf<TipOznake> *graf = nullptr;
public:
    GranaIterator(UsmjereniGraf<TipOznake> &g, std::vector<Grana<TipOznake>> gr, int p, int d, int poz) {
        grane = gr;
        polazni = p;
        dolazni = d;
        pozicija = poz;
        graf = &g;
    }

    Grana<TipOznake> operator*() {
        int brojac = 0;
        for (int i = 0; i < graf->dajBrojCvorova(); i++) {
            for (int j = 0; j < graf->dajBrojCvorova(); j++) {
                
                
                if (graf->postojiGrana(i, j) && brojac < pozicija) {
                    brojac++;
                } else if (brojac >= pozicija && graf->postojiGrana(i, j)) {
                    return graf->dajGranu(i, j);
                }
                
            }
        }
        throw std::domain_error("Nema grane");
    }

    GranaIterator(const GranaIterator<TipOznake> &g) {
        dolazni = g.dolazni;
        polazni = g.polazni;
        pozicija = g.pozicija;
        grane = g.grane;
    }

    GranaIterator<TipOznake> &operator=(const GranaIterator<TipOznake> &g) {
        dolazni = g.dolazni;
        polazni = g.polazni;
        pozicija = g.pozicija;
        grane = g.grane;
    }

    bool operator==(const GranaIterator &iter) const {
        if (polazni == iter.polazni && dolazni == iter.dolazni) return true;
        return false;
    }

    bool operator!=(const GranaIterator &iter) const {
        if (polazni == iter.polazni && dolazni == iter.dolazni) return false;
        return true;
    }

    GranaIterator &operator++() {
        pozicija++;
        return *this;
    }

    GranaIterator operator++(int) {
        pozicija++;
        return *this;
    }
};

template<typename TipOznake>
class ListaGraf : public UsmjereniGraf<TipOznake>
{
    std::vector<std::vector<int>> lista;
    std::vector<Cvor<TipOznake>> cvorovi;
    std::vector<Grana<TipOznake>> grane;
public:
    ListaGraf(int broj) {
        if (broj <= 0) throw std::domain_error("Error");
        for (int i = 0; i < broj; i++) {
            cvorovi.push_back(Cvor<TipOznake>(i, *this));
            lista.push_back(std::vector<int>());
        }
    }

    ~ListaGraf() {}

    ListaGraf(const ListaGraf<TipOznake> &m) {
        lista = m.lista;
        cvorovi = m.cvorovi;
        grane = m.grane;
    }

    ListaGraf<TipOznake> &operator=(const ListaGraf<TipOznake> &m) {
        if (&m != this) {
            lista = m.lista;
            cvorovi = m.cvorovi;
            grane = m.grane;
        }
        return *this;
    }

    int dajBrojCvorova() {
        return cvorovi.size();
    }

    void postaviBrojCvorova(int broj) {
        if (broj < lista.size()) throw std::domain_error("Error");
        int stara(lista.size());
        for (int i = stara; i < broj; i++) {
            cvorovi.push_back(Cvor<TipOznake>(i, *this));
            lista.push_back(std::vector<int>());
        }
    }

    void dodajGranu(int polazni, int dolazni, float tezina = 0) {
        if (polazni >= cvorovi.size() || dolazni >= cvorovi.size() || polazni < 0 || dolazni < 0) throw std::domain_error("Cvor izvan opsega");

        for (int j = 0; j < lista[polazni].size(); j++) {
            if (lista[polazni][j] == dolazni) {
                throw std::domain_error("Grana vec postoji");
            }
        }
        lista[polazni].push_back(dolazni);
        grane.push_back(Grana<TipOznake>(polazni, dolazni, *this, tezina));
    }

    void obrisiGranu(int polazni, int dolazni) {
        for (int j = 0; j < lista[polazni].size(); j++) {
            if (lista[polazni][j] == dolazni) {
                lista[polazni].erase(lista[polazni].begin() + j);
                break;
            }
        }
        for (int i = 0; i < grane.size(); i++) {
            if (grane[i] == Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                grane.erase(grane.begin() + i);
                return;
            }
        }
    }

    void postaviTezinuGrane(int polazni, int dolazni, float tezina = 0) {
        for (int i = 0; i < grane.size(); i++) {
            if (grane[i] == Grana<TipOznake>(polazni, dolazni, *this, tezina)) {
                grane[i].postaviTezinu(tezina);
                return;
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }

    float dajTezinuGrane(int polazni, int dolazni) {
        for (int i = 0; i < grane.size(); i++) {
            if (grane[i] == Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                return grane[i].dajTezinu();
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }

    bool postojiGrana(int polazni, int dolazni) {
        for (int j = 0; j < lista[polazni].size(); j++) {
            if (lista[polazni][j] == dolazni) {
                return true;
            }
        }
        return false;
    }

    void postaviOznakuCvora(int broj, TipOznake oznaka) {
        if (broj >= cvorovi.size() || broj < 0) {
            throw std::domain_error("Cvor ne postoji");
        }
        cvorovi[broj].postaviOznaku(oznaka);
    }

    TipOznake dajOznakuCvora(int broj) {
        if (broj >= cvorovi.size() || broj < 0) {
            throw std::domain_error("Cvor ne postoji");
        }
        return cvorovi[broj].dajOznaku();
    }

    void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) {
        for (int i = 0; i < grane.size(); i++) {
            if (grane[i] == Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                grane[i].postaviOznaku(oznaka);
                return;
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }

    TipOznake dajOznakuGrane(int polazni, int dolazni) {
        for (int i = 0; i < grane.size(); i++) {
            if (grane[i] == Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                return grane[i].dajOznaku();
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }

    Cvor<TipOznake> &dajCvor(int broj) {
        return cvorovi[broj];
    }

    Grana<TipOznake> &dajGranu(int polazni, int dolazni) {
        for (int i = 0; i < grane.size(); i++) {
            if (grane[i] == Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                return grane[i];
            }
        }
        throw std::domain_error("Nije nadjena");
    }

    GranaIterator<TipOznake> dajGranePocetak() {
        return GranaIterator<TipOznake>(*this, grane, grane[0].dajPolazniCvor().dajRedniBroj(),
                                        grane[0].dajDolazniCvor().dajRedniBroj(), 0);
    }

    GranaIterator<TipOznake> dajGraneKraj() {
        return GranaIterator<TipOznake>(*this, grane, grane[grane.size() - 1].dajPolazniCvor().dajRedniBroj(),
                                        grane[grane.size() - 1].dajDolazniCvor().dajRedniBroj(), grane.size() - 1);
    }
};

// nigdje u postavci ne pise da treba dfs i bfs..
template <typename TipOznake>
void dfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake> > &dfs_obilazak, Cvor<TipOznake> cvor)
{
    bool pamti = false;
    for (int i=0; i<dfs_obilazak.size(); i++) {
        if (dfs_obilazak[i].dajRedniBroj() == cvor.dajRedniBroj()) {
            pamti =true;
            break;
        }
    }
    if (!pamti) dfs_obilazak.push_back(cvor);
    for( int i=0; i<graf->dajBrojCvorova(); i++) {
        if (graf->postojiGrana(cvor.dajRedniBroj(), i) && !pamti) {
            dfs(graf, dfs_obilazak, graf->dajCvor(i));
        }
    }
}

template <typename TipOznake>
void bfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake> > &bfs_obilazak, Cvor<TipOznake> pocetni_cvor)
{
    std::queue<Cvor<TipOznake>> red;
    red.push(pocetni_cvor);
    bfs_obilazak.push_back(pocetni_cvor);

    while (!red.empty() && bfs_obilazak.size()!=graf->dajBrojCvorova()) {
        Cvor<TipOznake> cvor=red.front();
        red.pop();
        bool pamti =false;
        vector<Cvor<TipOznake>> izlazeci;
        // gledamo sve cvorove koje izlaze
        for (int i=0; i<graf->dajBrojCvorova(); i++) {
            if (graf->postojiGrana(cvor.dajRedniBroj(), i)) {
                izlazeci.push_back(graf->dajCvor(i));
                red.push(graf->dajCvor(i));
            }
        }

        for (int i=0; i< izlazeci.size(); i++) {
            pamti =false;
            for (int j=0; j<bfs_obilazak.size(); j++) {
                if (izlazeci[i].dajRedniBroj() == bfs_obilazak[j].dajRedniBroj()) pamti = true;
            }
            if (!pamti) bfs_obilazak.push_back(izlazeci[i]);
        }

    }
}

int main()
{
    UsmjereniGraf<bool> *g = new ListaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 0, 1.2);
    g->dodajGranu(1, 2, 0.1);
    g->dodajGranu(0, 0, 3.14);
    for (GranaIterator<bool> iter = g->dajGranePocetak();
         iter != g->dajGraneKraj(); ++iter)
      cout << "(" << (*iter).dajPolazniCvor().dajRedniBroj() << ","
           << (*iter).dajDolazniCvor().dajRedniBroj() << ") -> "
           << (*iter).dajTezinu() << "; ";
  delete g;
    return 0;
}
