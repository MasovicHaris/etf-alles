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


template <typename TipOznake>
class UsmjereniGraf
{
public:
    UsmjereniGraf()= default;
    virtual int dajBrojCvorova()= 0;
    virtual ~UsmjereniGraf() {}
    virtual void postaviBrojCvorova(int broj) = 0;
    virtual void dodajGranu(int polazni, int dolazni, double tezina = 0) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, double tezina = 0) = 0 ;
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

template <typename TipOznake>
class Cvor
{
    TipOznake oznaka;
    UsmjereniGraf<TipOznake> *pokGraf;
    int redniBroj;
public:
    Cvor (int rbroj, UsmjereniGraf<TipOznake> &g) {
        pokGraf = &g;
        redniBroj = rbroj;
    }
    TipOznake dajOznaku() {
        return oznaka;
    }
    void postaviOznaku(TipOznake novaOznaka) {
        oznaka = novaOznaka;
    }
    int dajRedniBroj() {
        return redniBroj;
    }
};

template <typename TipOznake>
class Grana
{
    int polazniCvor;
    int dolazniCvor;
    double tezina;
    TipOznake oznaka;
    UsmjereniGraf<TipOznake> *pokGraf;
public:
    Grana( int a, int b, UsmjereniGraf<TipOznake> &g, double t=0) {
        polazniCvor = a;
        dolazniCvor = b;
        tezina = t;
        pokGraf = &g;
    }

    Grana(const Grana<TipOznake> &g) {
        polazniCvor = g.polazniCvor;
        dolazniCvor = g.dolazniCvor;
        tezina = g.tezina;
        pokGraf = g.pokGraf;
        oznaka = g.oznaka;
    }
    
    double dajTezinu() {
        return tezina;
    }
    void postaviTezinu(double t=0) {
        pokGraf->dajGranu(polazniCvor, dolazniCvor).tezina=t;
        tezina=t;
    }
    TipOznake dajOznaku() {
        return oznaka;
    }
    void postaviOznaku(TipOznake o) {
        pokGraf->dajGranu(polazniCvor,dolazniCvor).oznaka = o;
        oznaka=o;
    }
    bool operator == (Grana<TipOznake> g) {
        if (g.polazniCvor == polazniCvor &&  g.dolazniCvor == dolazniCvor) return true;
        return false;
    }
    Cvor<TipOznake> dajPolazniCvor() {
        return pokGraf->dajCvor(polazniCvor);
    }
    Cvor<TipOznake> dajDolazniCvor() {
        return pokGraf->dajCvor(dolazniCvor);
    }
};

template <typename TipOznake>
class GranaIterator
{
    int dolazniCvor, polazniCvor, pozicijaMatrica;
    std::vector<Grana<TipOznake>> grane;
    std::vector<std::vector<bool>> matricaVrijednosti;
public:
    Grana<TipOznake> operator*() const {
        int brojac=0;
        int red = -1, kolona = -1;
        bool jestelPonijeliBajedere = false;
        for (int i=0; i< matricaVrijednosti.size(); i++) {
            for (int j=0; j< matricaVrijednosti[0].size(); j++) {
                if (matricaVrijednosti[i][j] && brojac <= pozicijaMatrica) {
                    brojac++;
                    red = i;
                    kolona = j;
                } else if (brojac > pozicijaMatrica) {
                    jestelPonijeliBajedere = true;
                    break;
                }
            }
            if (jestelPonijeliBajedere) break;
        }


        for (int i=0; i< grane.size(); i++) {
            if (grane[i].dajPolazniCvor().dajRedniBroj() == red && grane[i].dajDolazniCvor().dajRedniBroj() == kolona) return grane[i];
        }
        throw std::domain_error("Nema grane, aj ćao");
    }
    Grana<TipOznake> operator*() {
        int brojac=0;
        int red = -1, kolona = -1;
        bool jestelPonijeliBajedere = false;
        for (int i=0; i< matricaVrijednosti.size(); i++) {
            for (int j=0; j< matricaVrijednosti[0].size(); j++) {
                if (matricaVrijednosti[i][j] && brojac <= pozicijaMatrica) {
                    brojac++;
                    red = i;
                    kolona = j;
                } else if (brojac > pozicijaMatrica) {
                    jestelPonijeliBajedere = true;
                    break;
                }
            }
            if (jestelPonijeliBajedere) break;
        }


        for (int i=0; i< grane.size(); i++) {
            if (grane[i].dajPolazniCvor().dajRedniBroj() == red && grane[i].dajDolazniCvor().dajRedniBroj() == kolona) return grane[i];
        }
        throw std::domain_error("Nema grane, aj ćao");
    }

    GranaIterator(const GranaIterator<TipOznake> &g) {
        dolazniCvor = g.dolazniCvor;
        polazniCvor = g.polazniCvor;
        pozicijaMatrica = g.pozicijaMatrica;
        grane = g.grane;
    }

    GranaIterator<TipOznake> &operator = (const GranaIterator<TipOznake> &g) {
        dolazniCvor = g.dolazniCvor;
        polazniCvor = g.polazniCvor;
        pozicijaMatrica = g.pozicijaMatrica;
        grane = g.grane;
    }

    bool operator ==(const GranaIterator &iter) const {
        int brojac=0;
        int red = -1, kolona = -1;
        bool jestelPonijeliBajedere = false;
        for (int i=0; i< matricaVrijednosti.size(); i++) {
            for (int j=0; j< matricaVrijednosti[0].size(); j++) {
                if (matricaVrijednosti[i][j] && brojac <= pozicijaMatrica) {
                    brojac++;
                    red = i;
                    kolona = j;
                } else if (brojac > pozicijaMatrica) {
                    jestelPonijeliBajedere = true;
                    break;
                }
            }
            if (jestelPonijeliBajedere) break;
        }
        if (matricaVrijednosti[red][kolona] == iter.matricaVrijednosti[red][kolona]) return true;
        return false;
    }
    bool operator !=(const GranaIterator &iter) const {
        int brojac=0;
        int red = -1, kolona = -1;
        bool jestelPonijeliBajedere = false;
        for (int i=0; i< matricaVrijednosti.size(); i++) {
            for (int j=0; j< matricaVrijednosti[0].size(); j++) {
                if (matricaVrijednosti[i][j] && brojac <= pozicijaMatrica) {
                    brojac++;
                    red = i;
                    kolona = j;
                } else if (brojac > pozicijaMatrica) {
                    jestelPonijeliBajedere = true;
                    break;
                }
            }
            if (jestelPonijeliBajedere) break;
        }
        if (matricaVrijednosti[red][kolona] != iter.matricaVrijednosti[red][kolona]) return false;
        if (pozicijaMatrica==grane.size()) return false;
        return true;
    }


    GranaIterator &operator++() {
        int brojac=0;
        int red = -1, kolona = -1;
        bool jestelPonijeliBajedere = false;
        for (int i=0; i< matricaVrijednosti.size(); i++) {
            for (int j=0; j< matricaVrijednosti[0].size(); j++) {
                if (matricaVrijednosti[i][j] && brojac <= pozicijaMatrica) {
                    brojac++;
                    red = i;
                    kolona = j;
                } else if (brojac > pozicijaMatrica) {
                    jestelPonijeliBajedere = true;
                    break;
                }
            }
            if (jestelPonijeliBajedere) break;
        }
        if(red == matricaVrijednosti.size()-1 && kolona == matricaVrijednosti[0].size()-1) throw std::domain_error("Greska!");
        pozicijaMatrica++;
        return *this;
    }
    GranaIterator operator++(int a) {
        int brojac=0;
        int red = -1, kolona = -1;
        bool jestelPonijeliBajedere = false;
        for (int i=0; i< matricaVrijednosti.size(); i++) {
            for (int j=0; j< matricaVrijednosti[0].size(); j++) {
                if (matricaVrijednosti[i][j] && brojac <= pozicijaMatrica) {
                    brojac++;
                    red = i;
                    kolona = j;
                } else if (brojac > pozicijaMatrica) {
                    jestelPonijeliBajedere = true;
                    break;
                }
            }
            if (jestelPonijeliBajedere) break;
        }
        if(red + a >= matricaVrijednosti.size()-1 || kolona + a >= matricaVrijednosti[0].size()-1) throw std::domain_error("Greska!");
        pozicijaMatrica += a;
        return *this;
    }
    GranaIterator(std::vector<std::vector<bool>> m, std::vector<Grana<TipOznake>> gr, int polaz, int dolaz, int poz) {
        grane = gr;
        polazniCvor = polaz;
        dolazniCvor = dolaz;
        pozicijaMatrica = poz;
        matricaVrijednosti = m;
    }
};

template <typename TipOznake>
class MatricaGraf : public UsmjereniGraf<TipOznake>
{
    std::vector<std::vector<bool>> matricaVrijednosti;
    std::vector<Cvor<TipOznake>> cvorovi;
    std::vector<Grana<TipOznake>> grane;
public:
    MatricaGraf(int broj) {
        if (broj<=0) throw std::domain_error("Error");
        matricaVrijednosti.resize(broj);
        for (int i=0; i<broj; i++) matricaVrijednosti[i].resize(broj);
        for (int i=0; i<broj; i++) {
            for (int j=0; j<broj; j++) matricaVrijednosti[i][j] = false;
            cvorovi.push_back(Cvor<TipOznake> (i, *this));                                              // dovoljno sam i-te
        }
    }
    ~MatricaGraf() {}
    MatricaGraf(const MatricaGraf<TipOznake> &m) {
        matricaVrijednosti = m.matricaVrijednosti;
        cvorovi = m.cvorovi;
        grane = m.grane;
    }
    MatricaGraf<TipOznake> &operator =(const MatricaGraf<TipOznake> &m) {
        if(matricaVrijednosti != this->matricaVrijednosti) {
            matricaVrijednosti = m.matricaVrijednosti;
            cvorovi=m.cvorovi;
            grane=m.grane;
        }
        return *this;
    }
    int dajBrojCvorova() {
        return cvorovi.size();
    }
    void postaviBrojCvorova(int broj) {
        if (broj < matricaVrijednosti.size()) throw std::domain_error("Error");

        int prijasnja(matricaVrijednosti.size());
        for (int i = prijasnja; i < broj; i++) cvorovi.push_back(Cvor<TipOznake>(i, *this));
        if(prijasnja < broj) {
        matricaVrijednosti.resize(broj);
        for (int i=0; i<broj; i++) matricaVrijednosti[i].resize(broj);

        for (int i=0; i<broj; i++) {
            for (int j=0; j<broj; j++) {
                if (i >= prijasnja || j>= prijasnja) matricaVrijednosti[i][j] = false;
            }
        }
        }
    }
    void dodajGranu(int polazni, int dolazni, double tezina=0) {
        if (polazni >= cvorovi.size() || dolazni >= cvorovi.size() || polazni<0 || dolazni<0) throw std::domain_error("Cvor izvan opsega");

        if (matricaVrijednosti[polazni][dolazni] == false) {
            matricaVrijednosti[polazni][dolazni] = true;
            grane.push_back(Grana<TipOznake>(polazni, dolazni, *this, tezina));
        } else {
            throw std::domain_error("Grana vec postoji");
        }
    }
    void obrisiGranu(int polazni, int dolazni) {
        matricaVrijednosti[polazni][dolazni] = false;
        for (int i=0; i<grane.size(); i++) {
            if (grane[i]==Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                grane.erase(grane.begin()+i);
                return;
            }
        }
    }
    void postaviTezinuGrane(int polazni, int dolazni, double tezina=0) {
        if (matricaVrijednosti[polazni][dolazni]==true) {
            for (int i=0; i<grane.size(); i++) {
                if (grane[i]==Grana<TipOznake>(polazni, dolazni, *this, tezina)) {
                    grane[i].postaviTezinu(tezina);
                    return;
                }
            }
        } else {
            throw std::domain_error("Grana nije nadjena");
        }
    }
    float dajTezinuGrane(int polazni, int dolazni) {
        if (matricaVrijednosti[polazni][dolazni]==true) {
            for (int i=0; i<grane.size(); i++) {
                if (grane[i]==Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                    return grane[i].dajTezinu();
                }
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }
    bool postojiGrana(int polazni, int dolazni) {
        return matricaVrijednosti[polazni][dolazni];
    }

    void postaviOznakuCvora(int broj, TipOznake oznaka) {
        if (broj>=cvorovi.size() || broj<0) throw std::domain_error("Cvor ne postoji");
        cvorovi[broj].postaviOznaku(oznaka);
    }
    TipOznake dajOznakuCvora(int broj) {
        if (broj>=cvorovi.size() || broj<0) throw std::domain_error("Cvor ne postoji");
        return cvorovi[broj].dajOznaku();
    }
    void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) {
        for (int i=0; i<grane.size(); i++) {
            if (grane[i]==Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                grane[i].postaviOznaku(oznaka);
                return;
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }
    TipOznake dajOznakuGrane(int polazni, int dolazni) {
        for (int i=0; i<grane.size(); i++) {
            if (grane[i]==Grana<TipOznake>(polazni, dolazni, *this, 0)) {
                return grane[i].dajOznaku();
            }
        }
        throw std::domain_error("Grana nije nadjena");
    }
    Cvor<TipOznake> &dajCvor(int broj) {
        return cvorovi[broj];
    }
    Grana<TipOznake> &dajGranu(int polazni, int dolazni) {
        for (int i=0; i<grane.size(); i++) {
            if (grane[i]==Grana<TipOznake>(polazni, dolazni, *this, 0)) return grane[i];
        }
        throw std::domain_error("Nije nadjena");
    }
    GranaIterator<TipOznake> dajGranePocetak() {
        return GranaIterator<TipOznake>(matricaVrijednosti, grane, grane[0].dajPolazniCvor().dajRedniBroj(), grane[0].dajDolazniCvor().dajRedniBroj(),0);
    }
    GranaIterator<TipOznake> dajGraneKraj() {
        return GranaIterator<TipOznake>(matricaVrijednosti, grane, grane[grane.size()-1].dajPolazniCvor().dajRedniBroj(), grane[grane.size()-1].dajDolazniCvor().dajRedniBroj(), grane.size()-1);
    }
};

// nigdje u postavci ne pise da treba dfs i bfs..
template <typename TipOznake>
void dfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake> > &dfs_obilazak, Cvor<TipOznake> cvor) {
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
void bfs(UsmjereniGraf<TipOznake> *graf, vector<Cvor<TipOznake> > &bfs_obilazak, Cvor<TipOznake> pocetni_cvor) {
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
    UsmjereniGraf<std::string> *g = new MatricaGraf<std::string>(4);
  g->dodajGranu(0, 1, 2.5);
  g->dodajGranu(1, 2, 1.2);
  g->dodajGranu(1, 3, 0.1);
  g->dodajGranu(3, 3, -4.0);
  g->postaviOznakuGrane(3, 3, "aa");
  Grana<std::string> grana = g->dajGranu(0,1);
  grana.postaviOznaku("bb");
  grana.postaviTezinu(3.5);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (g->postojiGrana(i,j)) {
        cout << "(" << i << "," << j << ") -> '" << g->dajOznakuGrane(i, j) << "','" << g->dajGranu(i, j).dajOznaku();
        cout << "'," << g->dajTezinuGrane(i, j) << "; ";
      }
delete g;
    return 0;
}