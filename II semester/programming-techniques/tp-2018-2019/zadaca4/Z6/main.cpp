//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 4, Zadatak 5
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>
#include <memory>


class Student
{
  int broj_indexa;  
  std::string godina_studija;
  std::string ime;
  std::string adresa;
  std::string br_tel;
  std::string bez_razmaka_string(std::string s);
  std::string jel_dobar_br(std::string s);
  static int poziv;
  public:
    Student(int br_indexa, std::string g_studija, std::string ime_prezime, std::string adr, std::string broj_telefona);
    int DajIndeks() const {return broj_indexa;}
    std::string DajGodinuStudija() const{return godina_studija;}
    std::string DajImePrezime() const{return ime;}
    std::string DajAdresu() const{return adresa;}
    std::string DajTelefon() const{return br_tel;}
    void Ispisi() const;
    
};

std::string Student::bez_razmaka_string(std::string s)
{
  bool prvi=true;
  if(s.size()==0) return s;
  std::string uredjen;
  std::string razmak;
  razmak.push_back(' ');
  for(int i=0; i<s.length(); i++)
  {
    int brojac=0;
    if(s[i]!=' ')
    {
      for(int j=i;; j++)
      {
        if(s[j]==' ' || j==s.length()) break;
        brojac++;
      }
      std::string pom=s.substr(i,brojac);
      if(poziv==1 || poziv==2)
      {
        if(prvi) {uredjen+=pom; prvi=false;}
        else{uredjen+=razmak+pom;}
      }
      else{uredjen+=pom;}
      i+=pom.length()-1;
      
    }
  }
  poziv++;
  return uredjen;
}

std::string Student::jel_dobar_br(std::string s)
{
  std::string kosa;
  std::string crtica;
  kosa.push_back('/');
  crtica.push_back('-');
  int i=0;
  for(i=0; i<s.length(); i++)
  {
    if(s[i]=='/') break;
  }
  std::string pom1=s.substr(0, i);
  auto bez_razmaka_pom1=bez_razmaka_string(pom1); //3 poziv
  for(int j=0; j<bez_razmaka_pom1.length(); j++)
  {
    if(!(bez_razmaka_pom1[j]>='0' && bez_razmaka_pom1[j]<='9')) {pom1.resize(0); return pom1;} //catcg dole
  }
  bez_razmaka_pom1+=kosa;
  i++;
  if(i>=s.length()){pom1.resize(0); return pom1;}
  int k;
  for(k=i; k<s.length(); k++)
  {
    if(s[k]=='-') break;
  }
  std::string pom2=s.substr(i, k-i);
  auto bez_razmaka_pom2=bez_razmaka_string(pom2); //4ti poziv
  for(int j=0; j<bez_razmaka_pom2.length(); j++)
  {
    if(!(bez_razmaka_pom2[j]>='0' && bez_razmaka_pom2[j]<='9')) {pom2.resize(0); return pom2;} //catch dole
  }
  bez_razmaka_pom1+=bez_razmaka_pom2+crtica;
  k++;
  if(k>=s.length()){pom1.resize(0); return pom1;}
  std::string pom3=s.substr(k, s.length()-k);
  auto bez_razmaka_pom3=bez_razmaka_string(pom3); //5ti poziv
  for(int j=0; j<bez_razmaka_pom3.length(); j++)
  {
    if(!(bez_razmaka_pom3[j]>='0' && bez_razmaka_pom3[j]<='9')) {pom2.resize(0); return pom2;} //catch dole
  }
  bez_razmaka_pom1+=bez_razmaka_pom3;
  return bez_razmaka_pom1;
}
int Student::poziv=0;
Student::Student(int br_indexa, std::string god_studija, std::string ime_prezime, std::string adr, std::string broj_telefona)
{
    int pomocni=br_indexa;
    int brojac(0);
    while(pomocni!=0){ pomocni/=10; brojac++; }
    if(brojac!=5) throw std::domain_error("Neispravni parametri");
    auto g_studija=bez_razmaka_string(god_studija); //nulti poziv
    if(g_studija=="1" || g_studija=="2" || g_studija=="3") g_studija+="/B";
    if(!(g_studija=="1" || g_studija=="2" || g_studija=="3" || g_studija=="1/B" || g_studija=="2/B" || g_studija=="3/B" || g_studija=="1/M" || g_studija=="2/M" || g_studija=="1/D" || g_studija=="2/D" || g_studija=="3/D"))
        throw std::domain_error("Neispravni parametri");
    
    auto pomocni_ime=bez_razmaka_string(ime_prezime); // 1 poziv
    auto pomocni_adresa=bez_razmaka_string(adr);      // 2 poziv
    auto pomocni_broj=jel_dobar_br(broj_telefona);
    if(pomocni_ime.size()==0 || pomocni_adresa.size()==0 || pomocni_broj.size()==0) throw std::domain_error("Neispravni parametri");
    Student::poziv=0;
    broj_indexa=br_indexa;
    godina_studija=g_studija;
    ime=pomocni_ime;
    adresa=pomocni_adresa;
    br_tel=pomocni_broj;
}

void Student::Ispisi() const
{
  std::cout<<"Broj indeksa: "<<DajIndeks()<<std::endl;
  std::cout<<"Godina studija: "<<DajGodinuStudija()<<std::endl;
  std::cout<<"Ime i prezime: "<<DajImePrezime()<<std::endl;
  std::cout<<"Adresa: "<<DajAdresu()<<std::endl;
  std::cout<<"Telefon: "<<DajTelefon()<<std::endl;
}


class Laptop
{
  int ev_broj;
  std::string naziv;
  std::string karakteristike;
  Student *kod_koga_je;
  public:
  friend class Administracija;
    Laptop(int evid_br, std::string ime_laptopa, std::string kark_laptopa)
    {
      if(evid_br<0) throw std::domain_error("Neispravni parametri");
      ev_broj=evid_br;
      naziv=ime_laptopa;
      karakteristike=kark_laptopa;
      kod_koga_je=nullptr;
    }
    int DajEvidencijskiBroj() const{return ev_broj;}
    std::string DajNaziv() const{return naziv;}
    std::string DajKarakteristike() const{return karakteristike;}
    void Zaduzi(Student &ucenik)
    {
      if(kod_koga_je!=nullptr) throw std::domain_error("Laptop vec zaduzen");
      kod_koga_je=&ucenik;
    }
    void Razduzi()
    {
      if(kod_koga_je==nullptr) return;
      kod_koga_je=nullptr;
    }
    bool DaLiJeZaduzen() const
    {
      if(kod_koga_je==nullptr) return false;
      return true;
    }
    Student &DajKodKogaJe() const
    {
      if(kod_koga_je==nullptr) throw std::domain_error("Laptop nije zaduzen");
      return *kod_koga_je;
    }
    Student *DajPokKodKogaJe() const {return kod_koga_je;}
    void Ispisi() const 
    {
      std::cout<<"Evidencijski broj: "<<DajEvidencijskiBroj()<<std::endl;
      std::cout<<"Naziv: "<<DajNaziv()<<std::endl;
      std::cout<<"Karakteristike: "<<DajKarakteristike()<<std::endl;
    }
};

class Administracija
{
  std::map<int, std::shared_ptr<Student>> mapa_studenata;
  std::map<int, std::shared_ptr<Laptop>> mapa_laptopa;
  public:
  Administracija(){}
  Administracija(const Administracija &admin)
  {
    for(auto ita=admin.mapa_studenata.begin(); ita!=admin.mapa_studenata.end(); ita++)
    {
      mapa_studenata[ita->first] = std::make_shared<Student>(*ita->second);
    }
    for(auto it=admin.mapa_laptopa.begin(); it!=admin.mapa_laptopa.end(); it++)
    {
      mapa_laptopa[it->first] = std::make_shared<Laptop>(*it->second);
    }
  }
  Administracija(Administracija &&admin)
  {
    std::swap(mapa_studenata, admin.mapa_studenata); 
    std::swap(mapa_laptopa, admin.mapa_laptopa);
  }
  Administracija &operator =(const Administracija &admin)
  {
    for(auto it=admin.mapa_studenata.begin(); it!=admin.mapa_studenata.end(); it++)
    {
      mapa_studenata[it->first] = std::make_shared<Student>(*it->second);
    }
    for(auto it=admin.mapa_laptopa.begin(); it!=admin.mapa_laptopa.end(); it++)
    {
      mapa_laptopa[it->first] = std::make_shared<Laptop>(*it->second);
    }
    return *this;
  }
  Administracija &operator =(Administracija &&admin)
  {
    std::swap(mapa_studenata, admin.mapa_studenata);
    std::swap(mapa_laptopa, admin.mapa_laptopa);
    return *this;
  }
  ~Administracija()
  {
    for(auto it=mapa_studenata.begin(); it!=mapa_studenata.end(); it++)
    {
      it->second=nullptr;
    }
    for(auto it=mapa_laptopa.begin(); it!=mapa_laptopa.end(); it++)
    {
      it->second=nullptr;
    }
  }
  void RegistrirajNovogStudenta(int br_indexa, std::string g_studija, std::string ime_prezime, std::string adr, std::string broj_telefona)
  {
    try
    {
    Student pomocni(br_indexa, g_studija, ime_prezime, adr, broj_telefona);
    auto s=mapa_studenata.find(pomocni.DajIndeks());
    if(s!=mapa_studenata.end()) throw std::domain_error("Student s tim indeksom vec postoji");
    mapa_studenata[pomocni.DajIndeks()] = std::make_shared<Student>(pomocni);
    }catch(std::domain_error) {throw;}
  }
  void RegistrirajNoviLaptop(int e_broj, std::string nejm, std::string kerek)
  {
    try
    {
       // Laptop pomocni(e_broj);
        auto l=mapa_laptopa.find(e_broj);
        if(l!=mapa_laptopa.end()) throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
        mapa_laptopa[e_broj] = std::make_shared<Laptop>(e_broj, nejm, kerek);
    }catch(std::domain_error){throw std::domain_error("Neispravni parametri");}
  }
  Student &NadjiStudenta(int indeks)
  {
    auto it=mapa_studenata.find(indeks);
    if(it==mapa_studenata.end()) throw std::domain_error("Student nije nadjen");
    return *it->second;
  }
  Student NadjiStudenta(int indeks) const
  {
    auto it=mapa_studenata.find(indeks);
    if(it==mapa_studenata.end()) throw std::domain_error("Student nije nadjen");
    return *it->second;
  }
  Laptop &NadjiLaptop(int evbroj)
  {
    auto it=mapa_laptopa.find(evbroj);
    if(it==mapa_laptopa.end()) throw std::domain_error("Laptop nije nadjen");
    return *it->second;
  }
  Laptop NadjiLaptop(int evbroj) const
  {
    auto it=mapa_laptopa.find(evbroj);
    if(it==mapa_laptopa.end()) throw std::domain_error("Laptop nije nadjen");
    return *it->second;
  }
  void IzlistajStudente()
  {
    int brojac(0);
    for(auto it=mapa_studenata.begin(); it!=mapa_studenata.end(); it++)
    {
      if(brojac!=0 && brojac%2==0) std::cout<<std::endl;
      (*it->second).Ispisi();
      brojac++;
    }
  }
  void IzlistajLaptope()
  {
    int brojac(0);
    for(auto it=mapa_laptopa.begin(); it!=mapa_laptopa.end(); it++)
    {
      if(brojac!=0 && brojac%2==0) std::cout<<std::endl;
      (*it->second).Ispisi();
      std::cout<<std::endl;
      auto bul=(*it->second).DaLiJeZaduzen();
      if(bul)
      {
        auto l=(*it->second).DajKodKogaJe();
        std::cout<<"Zaduzio(la): "<<l.DajImePrezime()<<" ("<<l.DajIndeks()<<")"<<std::endl;
      }
    }
  }
  void ZaduziLaptop(int indeks, int ebroj)
  {
    auto s=mapa_studenata.find(indeks);
    if(s==mapa_studenata.end()) throw std::domain_error("Student nije nadjen");
    auto l=mapa_laptopa.find(ebroj);
    if(l==mapa_laptopa.end()) throw std::domain_error("Laptop nije nadjen");
    auto bul=(*l->second).DaLiJeZaduzen();
    if(bul) throw std::domain_error("Laptop vec zaduzen");
    Student* nekipok=nullptr;
    for(auto it=mapa_studenata.begin(); it!=mapa_studenata.end(); it++)
    {
      auto nekibroj=(*it->second).DajIndeks();
      if(nekibroj==indeks){nekipok=&(*it->second); break;}
    }
    for(auto it=mapa_laptopa.begin(); it!=mapa_laptopa.end(); it++)
    {
      auto nekipok2=(*it->second).DajPokKodKogaJe();
      if(nekipok2==nekipok) throw std::domain_error("Student je vec zaduzio laptop");
    }
    (*l->second).Zaduzi((*s->second));
  }
  int NadjiSlobodniLaptop()
  {
    for(auto it=mapa_laptopa.begin(); it!=mapa_laptopa.end(); it++)
    {
      if(!(*it->second).DaLiJeZaduzen()) return (*it->second).DajEvidencijskiBroj();
    }
    throw std::domain_error("Nema slobodnih laptopa");
  }
  void RazduziLaptop(int evbroj)
  {
    auto l=mapa_laptopa.find(evbroj);
    if(l==mapa_laptopa.end()) throw std::domain_error("Laptop nije nadjen");
    auto bul=(*l->second).DaLiJeZaduzen();
    if(!bul) throw std::domain_error("Laptop nije zaduzen");
    (*l->second).Razduzi();
  }
  void PrikaziZaduzenja()
  {
    bool nisuzaduzeni=true;
    if(mapa_laptopa.size()==0) throw std::domain_error("Nema zaduzenja");
    for(auto it=mapa_laptopa.begin(); it!=mapa_laptopa.end(); it++)
    {
      bool zaduz=(*it->second).DaLiJeZaduzen();
      if(zaduz)
      {
        nisuzaduzeni=false;
        auto pok=(*it->second).DajPokKodKogaJe();
        std::cout<<"Student "<<(*pok).DajImePrezime()<<" ("<<(*pok).DajIndeks()<<") zaduzio/la laptop broj "<<it->first<<std::endl;
      }
    }
    if(nisuzaduzeni) throw std::domain_error("Nema zaduzenja");
  }
};

int main ()
{
	Student proba(18305, "3  ", "  Huso  Hamzic   Car", "Pjesivac  Kulaa BB", " 06003/ 450234- 619");
	proba.Ispisi();
	return 0;
}









