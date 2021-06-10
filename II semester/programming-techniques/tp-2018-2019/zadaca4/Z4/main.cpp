//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <new>
#include <tuple>
#include <string>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <memory>

bool KorektanDatum(int dan, int mjesec, int godina)
{
    int broj_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
    if((godina%4==0 && godina%100!=0) || godina%400==0) broj_dana[1]++;
    if(dan<1 || mjesec<1 || godina<1 || dan>broj_dana[mjesec-1] || mjesec>12)
        return false;
    else return true;
}
bool KorektnoVrijeme(int sati, int min)
{
    if(sati<0 || min<0 || sati>23 || min>59) return false;
    return true;
}



class Datum
{
    int d;
    int m;
    int g;
    public: 
        friend class Pregled;
        friend class Pregledi;
        Datum(int dan, int mjesec, int godina);
        void Postavi(int dan, int mjesec, int godina);
        std::tuple<int,int,int> Ocitaj() const;
        void Ispisi() const {std::cout<<d<<"/"<<m<<"/"<<g;}
        
};


class Vrijeme
{
    int hrs;
    int mins;
    public:
        friend class Pregled;
        friend class Pregledi;
        Vrijeme(int sati, int minute);
        void Postavi(int sati, int minute);
        std::pair<int,int> Ocitaj() const;
        void Ispisi() const;
};


class Pregled
{   
    private:
    std::string ime;
    std::tuple<int,int,int> dat;
    std::pair<int,int> vrj;
    Datum d_pregleda;
    Vrijeme v_pregleda;
    int dajdaneumjesecu(int mjesec, int godina)
    {
        int br_dana[12]{31,28,31,30,31,30,31,31,30,31,30,31};
        if((godina%4==0 && godina%100!=0) || godina%400==0) br_dana[1]++;
        return br_dana[mjesec-1];
    }
    public:
        friend class Pregledi;
        Pregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda);
        Pregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda, int godina_pregleda, int sati_pregleda, int minute_pregleda);
        void PromijeniPacijenta(const std::string &ime_pacijenta);
        void PromijeniDatum(const Datum &novi_datum);
        void PromijeniVrijeme(const Vrijeme &novo_vrijeme);
        void PomjeriDanUnaprijed();
        void PomjeriDanUnazad();
        std::string DajImePacijenta() const{return ime;}
        Datum DajDatumPregleda() const{return d_pregleda;}
        Vrijeme DajVrijemePregleda() const{return v_pregleda;}
        static bool DolaziPrije(const Pregled &p1, const Pregled &p2);
        void Ispisi() const;
};


class Pregledi
{
  int pronadjiga(const std::string &p, int br) 
  {
      int index=-1;
      for(int i=0; i<br; i++)
      {
          if(p==pregledi[i]->DajImePacijenta())
          {
              index=i; 
              break;
          }
      }
      return index;
  }
  std::vector<std::shared_ptr<Pregled>> pregledi;
  public:
    explicit Pregledi(): pregledi(0){}
    Pregledi(std::initializer_list<Pregled> spisak_pregleda): pregledi(spisak_pregleda.size())
    {
        int i=0;
        for(auto p(spisak_pregleda.begin()); p!=spisak_pregleda.end(); p++)
        {
            pregledi[i]=std::make_shared<Pregled>(*p);
            i++;
        }
    }
    ~Pregledi()
    {
        IsprazniKolekciju();
    }
    Pregledi(const Pregledi &p): pregledi(p.pregledi.size())
    {
        for(int i=0; i<p.pregledi.size(); i++)
        {
            pregledi[i]=std::make_shared<Pregled>(*p.pregledi[i]);
        }
        
    }
    Pregledi(Pregledi &&p)=default;
    Pregledi &operator =(const Pregledi &p)
    {
        pregledi.resize(p.pregledi.size());
        for(int i=0; i<p.pregledi.size(); i++)
            pregledi[i]=std::make_shared<Pregled>(*p.pregledi[i]);
        return *this;
    }
    Pregledi &operator =(Pregledi &&p)= default;
    void RegistrirajPregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda)
    {
        try
        {
            std::shared_ptr<Pregled>p(std::make_shared<Pregled>(ime_pacijenta, datum_pregleda, vrijeme_pregleda));
            pregledi.push_back(p);
            
        }catch(std::bad_alloc){throw;}
    }
    void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda, int godina_pregleda, int sati_pregleda, int minute_pregleda)
    {
        try
        {
            std::shared_ptr<Pregled> p(std::make_shared<Pregled>(ime_pacijenta, dan_pregleda, mjesec_pregleda, godina_pregleda, sati_pregleda, minute_pregleda));
            pregledi.push_back(p);
        }catch(std::bad_alloc){throw;}
    }
    void RegistrirajPregled(std::shared_ptr<Pregled> p)
    {
        pregledi.push_back(p);
    }
    int DajBrojPregleda() const{return pregledi.size();}
    int DajBrojPregledaNaDatum(const Datum &datum) const
    {
        return std::count_if(pregledi.begin(), pregledi.end(), [datum](std::shared_ptr<Pregled> p)
        {
            if(p->d_pregleda.d==datum.d && p->d_pregleda.m==datum.m && p->d_pregleda.g==datum.g) return true;
            else return false;
        });
    }
    Pregled &DajNajranijiPregled()
    {
        if(pregledi.size()==0) throw std::domain_error("Nema registriranih pregleda");
        return **std::min_element(pregledi.begin(), pregledi.end(), [](std::shared_ptr<Pregled> p1, std::shared_ptr<Pregled> p2){
            return Pregled::DolaziPrije(*p1,*p2);
        });
    }
    Pregled DajNajranijiPregled() const
    {
        if(pregledi.size()==0) throw std::domain_error("Nema registriranih pregleda");
        return **std::min_element(pregledi.begin(), pregledi.end(), [](std::shared_ptr<Pregled> p1, std::shared_ptr<Pregled> p2){
            return Pregled::DolaziPrije(*p1,*p2);
        });
    }
    void IsprazniKolekciju()
    {
        pregledi.resize(0);
    }
    void ObrisiNajranijiPregled()
    {
        if(pregledi.size()==0) throw std::range_error("Prazna kolekcija");
        auto it=*std::min_element(pregledi.begin(), pregledi.end(), [](std::shared_ptr<Pregled> p1, std::shared_ptr<Pregled> p2){return Pregled::DolaziPrije(*p1,*p2);});
        for(int i=0; i<pregledi.size(); i++)
        {
            if(pregledi[i]==it)
            {
                for(int j=i; j<pregledi.size()-1; j++)
                {
                    pregledi[j]=pregledi[j+1];
                }
                pregledi.resize(pregledi.size()-1);
                break;
            }
        }
    }
    void ObrisiPregledePacijenta(const std::string &ime_pacijenta)
    {
        for(int i=0; i<pregledi.size(); i++)
        {
            auto index=Pregledi::pronadjiga(ime_pacijenta, pregledi.size());
            if(i==index)
            {
                auto it=pregledi[index];
                for(int j=i; j<pregledi.size()-1; j++)
                {
                    pregledi[j]=pregledi[j+1];
                }
                pregledi.resize(pregledi.size()-1);
                i=-1;
            }
        }
    }
    void IspisiPregledeNaDatum(const Datum &datum) const
    {
        std::vector<std::shared_ptr<Pregled>> v(pregledi);
            
        std::sort(v.begin(), v.end(), [](std::shared_ptr<const Pregled> p1,std::shared_ptr<const Pregled> p2)
        {
           return Pregled::DolaziPrije(*p1,*p2); 
        });
        
        for(int i=0; i<v.size(); i++)
        {
            if(v[i]->d_pregleda.d==datum.d && v[i]->d_pregleda.m==datum.m && v[i]->d_pregleda.g==datum.g)
            {
                v[i]->Ispisi();
            }
        }
    }
    void IspisiSvePreglede() const
    {
        std::vector<std::shared_ptr<Pregled>> v(pregledi);
        std::sort(v.begin(), v.end(), [](std::shared_ptr<const Pregled> p1,std::shared_ptr<const Pregled> p2)
        {
           return Pregled::DolaziPrije(*p1,*p2); 
        });
        
        for(int i(0); i<v.size(); i++)
            v[i]->Ispisi();
    }
};


Datum::Datum(int dan, int mjesec, int godina)
{
    if(KorektanDatum(dan,mjesec,godina)==false) throw std::domain_error("Neispravan datum");
    else{ d=dan; m=mjesec; g=godina; }
}
void Datum::Postavi(int dan, int mjesec, int godina)
{
    if(KorektanDatum(dan,mjesec,godina)==false) throw std::domain_error("Neispravan datum");
    else{ d=dan; m=mjesec; g=godina; }
}
std::tuple<int,int,int> Datum::Ocitaj() const
{
    return std::make_tuple(this->d, this->m, this->g);
}




Vrijeme::Vrijeme(int sati, int minute)
{
    if(KorektnoVrijeme(sati, minute)==false) throw std::domain_error("Neispravno vrijeme");
    else{ hrs=sati; mins=minute; }
}
void Vrijeme::Postavi(int sati, int minute)
{
    if(KorektnoVrijeme(sati,minute)==false) throw std::domain_error("Neispravno vrijeme");
    else{ hrs=sati; mins=minute; }
}
std::pair<int,int> Vrijeme::Ocitaj() const
{
    return std::make_pair(this->hrs, this->mins);
}
void Vrijeme::Ispisi() const
{
    if(this->hrs<10 && this->mins<10) std::cout<<"0"<<hrs<<":"<<"0"<<mins<<"\n"; else if(this->hrs<10 && this->mins>9) std::cout<<"0"<<hrs<<":"<<mins<<"\n"; else if(this->hrs>9 && this->mins<10) std::cout<<hrs<<":"<<"0"<<mins<<"\n";  else if(this->hrs>9 && this->mins>9) std::cout<<hrs<<":"<<mins<<"\n";
}




Pregled::Pregled(const std::string &ime_pacijenta, const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda): dat(datum_pregleda.Ocitaj()), vrj(vrijeme_pregleda.Ocitaj()), d_pregleda(std::get<0>(dat), std::get<1>(dat), std::get<2>(dat)), v_pregleda(vrj.first,vrj.second)
{
    ime=ime_pacijenta;
}
Pregled::Pregled(const std::string &ime_pacijenta, int dan_pregleda, int mjesec_pregleda, int godina_pregleda, int sati_pregleda, int minute_pregleda): d_pregleda(dan_pregleda,mjesec_pregleda,godina_pregleda), v_pregleda(sati_pregleda, minute_pregleda)                    
{
    ime=ime_pacijenta;
}
void Pregled::PromijeniPacijenta(const std::string &ime_pacijenta)
{
    this->ime=ime_pacijenta;
}
void Pregled::PromijeniDatum(const Datum &novi_datum)
{
    this->d_pregleda=novi_datum;
}
void Pregled::PromijeniVrijeme(const Vrijeme &novo_vrijeme)
{
    this->v_pregleda=novo_vrijeme;
}
void Pregled::PomjeriDanUnaprijed()
{
    auto datumi=this->d_pregleda.Ocitaj();
    int dan=std::get<0>(datumi); int mjesec=std::get<1>(datumi); int godina=std::get<2>(datumi);
    int dana_u_mj=dajdaneumjesecu(mjesec, godina);
    if(dan+1>dana_u_mj && mjesec!=12) {dan=1; mjesec++;}
    else if(dan+1>dana_u_mj && mjesec==12) {dan=1; mjesec=1; godina++;}
    else dan++;
    this->d_pregleda.Postavi(dan,mjesec,godina);
}
void Pregled::PomjeriDanUnazad()
{
    auto datumi=this->d_pregleda.Ocitaj();
    int dan=std::get<0>(datumi); int mjesec=std::get<1>(datumi); int godina=std::get<2>(datumi);
    if(dan==1 && mjesec!=1) {dan=dajdaneumjesecu(mjesec-1,godina); mjesec--;}
    else if(dan==1 && mjesec==1){dan=31; mjesec=12; godina--;}
    else dan--;
    this->d_pregleda.Postavi(dan,mjesec,godina);
}
bool Pregled::DolaziPrije(const Pregled &p1, const Pregled &p2)
{
    auto datumi1=p1.d_pregleda.Ocitaj();
    auto datumi2=p2.d_pregleda.Ocitaj();
    int dan1=std::get<0>(datumi1); int mjesec1=std::get<1>(datumi1); int godina1=std::get<2>(datumi1);
    int dan2=std::get<0>(datumi2); int mjesec2=std::get<1>(datumi2); int godina2=std::get<2>(datumi2);
    if(godina1<godina2) return true;
    if(mjesec1<mjesec2 && godina1==godina2) return true;
    if(dan1<dan2 && mjesec1==mjesec2 && godina1==godina2) return true;
    if(p1.v_pregleda.hrs<p2.v_pregleda.hrs && dan1==dan2 && mjesec1==mjesec2 && godina1==godina2) return true;
    if(p1.v_pregleda.mins<p2.v_pregleda.mins && p1.v_pregleda.hrs==p2.v_pregleda.hrs && dan1==dan2 && mjesec1==mjesec2 && godina1==godina2) return true;
    return false;
}
void Pregled::Ispisi() const
{
    std::cout<<std::setw(30)<<std::left<<ime;
    d_pregleda.Ispisi();
    std::cout<<" ";
    v_pregleda.Ispisi();
}


int main ()
{
   
    Pregledi proba;
    for(;;)
    {
        std::cout<<"Unesite ime novog pacijenta ili 'kraj' za zavrsetak unosa: ";
        std::string pomocni;
        std::getline(std::cin, pomocni);
        if(pomocni=="kraj") break;
        std::cout<<"Unesite dan mjesec i godinu pregleda: ";
        int dej, mant, jr;
        std::cin>>dej>>mant>>jr;
        try
        {
            Datum vezenema(dej,mant,jr);
        }
        catch(std::domain_error e){std::cout<<e.what()<<std::endl;}
        std::cout<<"Unesite sate i minute pregleda: ";
        int klok, min;
        std::cin>>klok>>min;
        try
        {
            Vrijeme sklj(klok,min);
        }catch(std::domain_error v){std::cout<<v.what()<<std::endl;}
        try{
        proba.RegistrirajPregled(pomocni, dej, mant, jr, klok, min);
        }catch(std::range_error e){std::cout<<e.what()<<std::endl;}
        catch(std::domain_error a){std::cout<<a.what()<<std::endl;}
        std::cin.ignore(10000,'\n');
    }
    
    std::cout<<"Trenutno su registrovani sljedeci pregledi"<<std::endl;
    proba.IspisiSvePreglede();
    
  while(1)
  {
        std::cout<<"\nOdaberite jednu od sljedecih opcija\n";
        std::cout<<"1 - Broj pregleda na datum\n";
        std::cout<<"2 - Najraniji pregled\n";
        std::cout<<"3 - Obrisi pregled pacijenta\n";
        std::cout<<"4 - Obrisi najraniji pregled\n";
        std::cout<<"5 - Ispisi sve pregleda na datum\n";
        std::cout<<"6 - Ispisi sve preglede\n";
        std::cout<<"7 - Kraj programa\n";

        
        int x;
        std::cin>>x;
        Datum dejt(1,1,1);
        bool izlaz=false;
        try
        {
            switch(x)
            {
                case 1: {std::cout<<"\nUnesite dan mjesec i godinu : "; 
                    int dej, mant, jr; 
                    std::cin>>dej>>mant>>jr; 
                    Datum pom(dej,mant,jr); 
                    std::cout<<"Broj pregleda na datum "<<dej<<" "<<mant<<" "<<jr<<" je: "<<proba.DajBrojPregledaNaDatum(pom)<<"\n";
                    break;}
                case 2: 
                {
                    std::cout<<"Najraniji pregled je:\n";
                    proba.DajNajranijiPregled().Ispisi(); break;
                }
                case 3: 
                {
                    std::cin.ignore(10000,'\n');
                    int raz=proba.DajBrojPregleda();
                    std::cout<<"Unesite ime pacijenta: ";                           
                    std::string nejm; 
                    std::getline(std::cin, nejm);
                    proba.ObrisiPregledePacijenta(nejm);
                    std::cout<<"Uspjesno obrisano "<<raz-proba.DajBrojPregleda()<<" pregleda\n";
                    break;
                }
                case 4: {proba.ObrisiNajranijiPregled(); std::cout<<"Najraniji pregled uspjesno obrisan\n"; break;}
                case 5: 
                {
                    std::cout<<"Unesite dan mjesec i godinu : ";
                    int dej, mant, jr;
                    std::cin>>dej>>mant>>jr;
                    dejt.Postavi(dej,mant,jr);
                    std::cout<<"Pregledi na datum "<<dej<<" "<<mant<<" "<<jr<<" su:\n";
                    proba.IspisiPregledeNaDatum(dejt);
                    break;
                }
                case 6: {proba.IspisiSvePreglede(); break;}
                case 7: {izlaz=true; break;}
                default: continue;
            }
                if(izlaz) break;
        }
        catch(std::range_error e){std::cout<<e.what()<<std::endl; return 0;}
        catch(std::domain_error k){std::cout<<k.what()<<std::endl; return 0;}
    }

	return 0;
}