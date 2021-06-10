//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 5, Zadatak 1
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <list>


template <typename TipEl, template <typename...> class Kontejner = std::vector>
 class Tok 
 {
 Kontejner<TipEl> kolekcija;
 public:
 template <typename TipEl2, template <typename...> class Kontejner2>
 friend class Tok; // Stvara prijateljstvo između različitih vrsta tokova
 template <typename IterTip>
 Tok(IterTip pocetak, const IterTip iza_kraja)
 {
     for(auto it=pocetak; it!=iza_kraja; it++)
     {
        kolekcija.insert(std::end(kolekcija),*it);
     }
 }
 template <typename IterabilniKontejner>
 Tok(const IterabilniKontejner &kontejner)
 {
     for(auto it1=std::begin(kontejner); it1!=std::end(kontejner); it1++)
     {
         kolekcija.insert(std::end(kolekcija),*it1);
     }
 }
 Tok(std::initializer_list<TipEl> lista)
 {
     for(auto it=std::begin(lista); it!=std::end(lista); it++)
     {
         kolekcija.insert(std::end(kolekcija),*it);
     }
 }
 static Tok<TipEl, Kontejner> Opseg(TipEl poc, TipEl kraj, TipEl korak = 1)
 {
     Tok helpme{};
     auto itka=poc;
     while(itka<=kraj)
     {
         helpme.kolekcija.insert(std::begin(helpme.kolekcija), itka);
         itka=itka+korak;
     }
     return helpme;
 }
 unsigned int Velicina() const
 {
     unsigned int brojac=0;
     for(auto it=std::begin(kolekcija); it!=std::end(kolekcija); it++)
     {
         brojac++;
     }
     return brojac;
 }
 bool Prazan() const
 {
     int brojac=0;
     auto itka=std::begin(kolekcija);
     while(itka!=std::end(kolekcija))
     {
         brojac++;
         itka++;
     }
     if(brojac==0) return true;
     return false;
 }
 Tok<TipEl, Kontejner> Limitiraj(unsigned int n) const
 {
    int brojac=1;
    Tok pomocni{};
    auto it=std::begin(kolekcija);
    while(it!=std::end(kolekcija)) 
    {
        if(brojac>n) break;
        pomocni.kolekcija.insert(std::end(pomocni.kolekcija),*it);
        brojac++;
        it++;
    }
    return pomocni;
 }
 Tok<TipEl, Kontejner> Preskoci(unsigned int n) const
 {
     int k=int(Velicina());
     int brojac=1;
     Tok pomocni{};
     if(n>k) return Tok{};
     auto itka=std::begin((*this).kolekcija);
     while(itka!=std::end((*this).kolekcija))
     {
         if(brojac<=n) {brojac++; itka++; continue;}
         pomocni.kolekcija.insert(std::end(pomocni.kolekcija),*itka);
         itka++;
     }
     return pomocni;
 }
 Tok<TipEl, Kontejner> Obrnut() const
 {
     Tok pomocni=*this;
     std::reverse(std::begin(pomocni.kolekcija), std::end(pomocni.kolekcija));
     return pomocni;
 }
 Tok<TipEl, Kontejner> Akcija(std::function<void(void)> akcija) const
 {
     auto kop=*this;
     akcija();
     return kop;
 }
 void ZaSvaki(std::function<void(TipEl)> akcija) const
 {
        auto p=std::begin(kolekcija);
     while(p!=std::end(kolekcija)) 
     {
         akcija(*p);
         p++;
     }
 }
 Tok<TipEl, Kontejner> Filtriraj(std::function<bool(TipEl)> predikat) const
 {
     Tok f{};
     auto ti=std::begin(kolekcija);
     while(ti!=std::end(kolekcija)) 
     {
         if(predikat(*ti)) f.kolekcija.insert(std::end(f.kolekcija),*ti);
         ti++;
     }
     return f;
 }
 TipEl PronadjiPrvi() const
 {
     if(!Velicina()) throw std::logic_error("Tok je prazan");
     return *std::begin(kolekcija);
 }
 TipEl PronadjiPosljednji() const
 {
     if(!Velicina()) throw std::logic_error("Tok je prazan");
     return *(std::end(kolekcija)-1);
 }
 bool ZadovoljavaBaremJedan(std::function<bool(TipEl)> kriterij) const
 {
     auto it=std::begin(kolekcija);
     while(it!=std::end(kolekcija)) 
     {
         if(kriterij(*it)) return true;
         it++;
     }
     return false;
 }
 bool ZadovoljavaNijedan(std::function<bool(TipEl)> kriterij) const
 {
     for(auto it=std::begin(kolekcija); it!=std::end(kolekcija); it++)
     {
         if(kriterij(*it)) return false;
     }
     return true;
 }
 bool ZadovoljavajuSvi(std::function<bool(TipEl)> kriterij) const
 {
     for(auto it=std::begin(kolekcija); it!=std::end(kolekcija); it++)
     {
         if(!kriterij(*it)) return false;
     }
     return true;
 }
 TipEl Akumuliraj(TipEl inicijalna,std::function<TipEl(TipEl, TipEl)> akumulator) const
 {
     auto itka=std::begin(kolekcija);
     auto usisivac=akumulator(inicijalna, *itka);
     itka++;
     while(itka!=std::end(kolekcija)){ usisivac=akumulator(usisivac, *itka); itka++;}
     return usisivac;
 }
 TipEl Akumuliraj(std::function<TipEl(TipEl, TipEl)> akumulator) const
 {
     if(!Velicina()) throw std::logic_error("Tok je prazan");
     TipEl usisivac=akumulator(*std::begin(kolekcija), *(1+std::begin(kolekcija)));
     for(auto itka=std::begin(kolekcija)+1+1; itka!=std::end(kolekcija); itka++) usisivac=akumulator(usisivac, *itka);
     return usisivac;
 }
 Tok<TipEl, Kontejner> Sortirano(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x < y; }) const
 {
     Tok sorted=*this;
     std::sort(std::begin(sorted.kolekcija), std::end(sorted.kolekcija), komparator);
     return sorted;
 }
 Tok<TipEl, Kontejner> Unikatno(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x == y; }) const
 {
     Tok jedinstvo{};
     for(auto itka1=std::begin(kolekcija); itka1!=std::end(kolekcija); itka1++)
     {
         bool dobar=true;
         for(auto itka2=itka1; itka2!=std::end(kolekcija); itka2++)
         {
             if(itka1==itka2) continue;
             if(komparator(*itka1,*itka2)) dobar=false;
         }
         if(std::find(std::begin(jedinstvo.kolekcija), std::end(jedinstvo.kolekcija), *itka1)!=std::end(jedinstvo.kolekcija)) continue;
         if(dobar) jedinstvo.kolekcija.insert(std::end(jedinstvo.kolekcija), *itka1);
     }
     return jedinstvo;
 }
 Tok<TipEl, Kontejner> Proviri(std::function<void(TipEl)> akcija) const
 {
     Tok cu_koje=*this;
     for(auto itka=std::begin(cu_koje.kolekcija); itka!=std::end(cu_koje.kolekcija); itka++) akcija(*itka);
     return *this;
 }
 TipEl Minimalan(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x < y; }) const
 {
     if((*this).Velicina()==0) throw std::logic_error("Tok je prazan");
        return *std::min_element(std::begin(kolekcija), std::end(kolekcija), komparator);
 }
 TipEl Maksimalan(std::function<bool(TipEl, TipEl)> komparator = [](TipEl x, TipEl y) { return x > y; }) const
 {
     if((*this).Velicina==0) throw std::logic_error("Tok je prazan");
     return *std::max_element(std::begin(kolekcija), std::end(kolekcija), komparator);
 }
 template <typename Kont2>
 Kont2 Sakupi(std::function<void(Kont2 &, TipEl)> kombinator) const
 {
     Kont2 geter{};
     auto itka=std::begin(kolekcija); 
     while(itka!=std::end(kolekcija)){ kombinator(geter, *itka); itka++;}
     return geter;
 }
 template <typename TipEl2>
 Tok<TipEl2, Kontejner> Mapiraj(std::function<TipEl2(TipEl)> maper) const
 {
     Kontejner<TipEl2> conta;
     auto itka=std::begin(kolekcija);
     while(itka!=std::end(kolekcija))
     {
         conta.insert(std::end(conta), maper(*itka));
         itka++;
     }
     Tok<TipEl2,Kontejner> meped(std::begin(conta), std::end(conta));
     return meped;
 }
 template <typename TipEl2>
 Tok<TipEl2, Kontejner> MapirajPoravnato(std::function<Tok<TipEl2, Kontejner>(TipEl)> maper) const
 {
     Kontejner<TipEl2> conta;
     auto itka=std::begin(kolekcija); 
     while(itka!=std::end(kolekcija))
     {
         auto k=maper(*itka);
         for(auto it=std::begin(k.kolekcija); it!=std::end(k.kolekcija); it++)
         {
             conta.insert(std::end(conta),*it);
         }
         itka++;
     }
     Tok<TipEl2,Kontejner> evenlimeped(std::begin(conta), std::end(conta));
     return evenlimeped;
 }
};

int main ()
{
Tok<char> tok = Tok<char>::Opseg('A', 'Z');
    //ispisi svako drugo slovo engl. alfabeta
    int i = 0;
    tok
            .Filtriraj([&i](const char &) { return i++ % 2 == 0; })
            .ZaSvaki([](const char &c) { std::cout << c; });
    std::cout << std::endl;
    //drugi nacin za istu stvar, zadavanjem treceg parametra u ::Opseg
    Tok<char>::Opseg('A', 'Z', 2).ZaSvaki([](const char &c) { std::cout << c; });
}