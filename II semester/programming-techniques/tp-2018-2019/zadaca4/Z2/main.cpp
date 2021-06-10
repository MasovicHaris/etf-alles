//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 4, Zadatak 2
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>

bool KorektanDatum(int dan, int mjesec, int godina)
{
    if(mjesec>12 || mjesec<1) return false;
    if(godina<0) return false;
    if(mjesec==1 || mjesec==3 || mjesec==5 || mjesec==7 || mjesec==8 || mjesec==10 || mjesec==12)
    {
        if(dan>31 || dan<1) return false;
    }
    if(mjesec==4 || mjesec==6 || mjesec==9 || mjesec==11)
    {
        if(dan>30 || dan<1) return false;
    }
    if(mjesec==2)
    {
        if((godina%4==0 && godina%100!=0) || godina%400==0)
        {
            if(dan>29 || dan<1) return false;
            else
            {
                if(dan>28 || dan<1) return false;
            }
        }
    }
    return true;
}

void KorektanJMBG(long long int broj)
{
    int niz[13], i(12), brojac(0);
    while(broj!=0)
    {
        niz[i]=broj%10;
        broj/=10;
        brojac++;
        i--;
    }
    if(brojac==13)
    {
        if(KorektanDatum(niz[0]*10+niz[1], niz[2]*10+niz[3], 1000+niz[4]*100+niz[5]*10+niz[6])==false)
            throw std::logic_error("JMBG nije validan");
    }
    if(brojac==12)
    {
        if(KorektanDatum(niz[0], niz[1]*10+niz[2], 1000+niz[3]*100+niz[4]*10+niz[5])==false)
            throw std::logic_error("JMBG nije validan");
    }
    if(brojac!=12 && brojac!=13) throw std::logic_error("JMBG nije validan");
}
class GradjaninBiH
{
    std::string ime;
    long long int JMBG;
    GradjaninBiH *pok;
    static GradjaninBiH *zadnji;
    int muski=0, zenski=500;
    int dan;
    int mjesec;
    int godina;
    int sifra;
    bool spol;
    public:
        enum Pol{Musko,Zensko};
        GradjaninBiH(std::string ime_i_prezime, long long int jmbg);
        GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja, int mjesec_rodjenja, int godina_rodjenja, int sifra_regije, Pol pol);
        GradjaninBiH(const GradjaninBiH &g) = delete;
        GradjaninBiH(GradjaninBiH &&g) = delete;
        GradjaninBiH &operator =(const GradjaninBiH &g) = delete;
        GradjaninBiH &operator =(GradjaninBiH &&g) = delete;
        std::string DajImeIPrezime() const {return ime;}
        long long int DajJMBG() const{return JMBG;}
        int DajMjesecRodjenja() const {return mjesec;}
        int DajDanRodjenja() const {return dan;}
        int DajGodinuRodjenja() const {return godina;}
        int DajSifruRegije() const {return sifra;}
        Pol DajPol() const {if(spol) return Musko; else return Zensko;}
        void PromijeniImeIPrezime(std::string novo_ime){ime=novo_ime;}
        ~GradjaninBiH()
        {
            auto p(zadnji);
            if(p==this)
            {
                zadnji=this->pok;
            }
            else
            {
                while(p->pok!=this) p=p->pok;
                p->pok=this->pok;
            }
        }
        
};
GradjaninBiH* GradjaninBiH::zadnji=nullptr;

GradjaninBiH::GradjaninBiH(std::string ime_i_prezime, long long int jmbg)
{
    try
    {
        KorektanJMBG(jmbg);
    }catch(std::logic_error){throw;}
    
    pok=zadnji;
    zadnji=this;        //samo služi za provjeru
    auto p=pok;         //ima li ljudi sa istim JMBG-om u listi
    while(p!=nullptr)
    {
        if(jmbg==p->JMBG) throw std::logic_error("Vec postoji gradjanin sa istim JMBG");
        p=p->pok;
    }
    JMBG=jmbg;
    ime=ime_i_prezime;
    auto broj(jmbg);
    int niz[13], i(12);
    niz[0]=0;
    while(broj!=0)
    {
        niz[i]=broj%10;
        broj/=10;
        i--;
    }
    dan=niz[0]*10+niz[1];
    mjesec=niz[2]*10+niz[3];
    godina=niz[4]*100+niz[5]*10+niz[6];
    if(godina<100) godina+=2000;
    else godina+=1000;
    sifra=niz[7]*10+niz[8];
    if(niz[9]<5) spol=true;
    else spol=false;
}

GradjaninBiH::GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja, int mjesec_rodjenja, int godina_rodjenja, int sifra_regije, Pol pol)
{
    if(KorektanDatum(dan_rodjenja, mjesec_rodjenja, godina_rodjenja)==false) throw std::logic_error("Neispravni podaci");
    if(sifra_regije<0 || sifra_regije>99) throw std::logic_error("Neispravni podaci");
    pok=zadnji;
    zadnji=this;
    auto p=pok;
    int g=godina_rodjenja%1000;
    while(p!=nullptr)
    {
        if(dan_rodjenja==p->dan && mjesec_rodjenja==p->mjesec && godina_rodjenja==p->godina)
        {
            if(p->spol==true && pol==Musko) muski++;
            if(p->spol==false && pol==Zensko) zenski++;
        }
        p=p->pok;
    }
    
    long long int j=0;
    if(pol==Musko)
    {
        j=muski*10+pow(100,2)*sifra_regije+pow(1000,2)*g+pow(1000,3)*(long long int)mjesec_rodjenja+pow(1000,3)*100*dan_rodjenja;
    }
    if(pol==Zensko)
    {
        j=zenski*10+pow(100,2)*sifra_regije+pow(1000,2)*g+pow(1000,3)*(long long int)mjesec_rodjenja+pow(1000,3)*100*dan_rodjenja;
    }
    p=pok;
    while(p!=nullptr)
    {
        if(j==p->JMBG) throw std::logic_error("Vec postoji gradjanin sa istim JMBG");
        p=p->pok;
    }
    int s=0;
    if(pol==Musko) s=muski;
    else s=zenski;
    int c13=(11-(7*((dan_rodjenja/10)+(g%10))+6*(dan_rodjenja%10+(sifra_regije/10))+5*((mjesec_rodjenja/10)+sifra_regije%10)+4*(mjesec_rodjenja%10+(s/100))+3*((g/100)+(s%100)/10)+2*((g%100)/10+(s%10)))%11);
    if(c13==11) c13=0;
    if(c13==10) throw std::logic_error("JMBG nije validan");
    j+=c13;
    JMBG=j;
    ime=ime_i_prezime;
    dan=dan_rodjenja;
    mjesec=mjesec_rodjenja;
    godina=godina_rodjenja;
    sifra=sifra_regije;
    if(pol==Musko) spol=true;
    else spol=false;
}
int main ()
{
    GradjaninBiH *g[1000];
    for(int i=0; i<1000; i++) g[i]=nullptr;
    int n, z, br=0;
    
    std::cout<<"Koliko gradjana zelite unijeti po JMBG?"<<std::endl;
    std::cin>>n;
    for(int i=0; i<n; i++)
    {
        std::string ime;
        long long int jmbg;
        std::cin.ignore(10000,'\n');
        std::cout<<"Unesite ime i prezime (u istom redu): "<<std::endl,
        std::getline(std::cin, ime);
        std::cout<<"Unesite JMBG: "<<std::endl;
        std::cin>>jmbg;
        try
        {
            g[br]=new GradjaninBiH(ime, jmbg);
            std::cout<<"Unijeli ste gradjanina "<<g[br]->DajImeIPrezime()<<" rodjenog "<<g[br]->DajDanRodjenja()<<"."<<g[br]->DajMjesecRodjenja()<<"."<<g[br]->DajGodinuRodjenja()<<" u regiji "<<g[br]->DajSifruRegije();
            if(g[br]->DajPol()==GradjaninBiH::Musko) std::cout<<", musko."<<std::endl;
            else std::cout<<", zensko."<<std::endl;
        }catch(std::logic_error a)
        {
            std::cout<<a.what()<<std::endl;
            i--;
        }
        br++;
    }
    
    std::cout<<"Koliko gradjana zelite unijeti po datumu rodjenja, regiji i polu?"<<std::endl;
    std::cin>>z;
    for(int i=0; i<z; i++)
    {
        std::string ime;
        int dan, mjesec, godina;
        int sifra;
        GradjaninBiH::Pol pol;
        std::cin.ignore(10000,'\n');
        std::cout<<"Unesite ime i prezime (u istom redu): "<<std::endl;
        std::getline(std::cin, ime);
        std::cout<<"Unesite datum rodjenja (format dd/mm/gggg): "<<std::endl;
        char znak;
        std::cin>>dan>>znak>>mjesec>>znak>>godina;
        std::cout<<"Unesite sifru regije: "<<std::endl;
        std::cin>>sifra;
        std::cout<<"Unesite M za musko, Z za zensko: "<<std::endl;
        char a;
        std::cin>>a;
        if(a=='M') pol=GradjaninBiH::Musko;
        if(a=='Z') pol=GradjaninBiH::Zensko;
        try
        {
            g[br]=new GradjaninBiH(ime,dan,mjesec,godina,sifra,pol);
            std::cout<<"Unijeli ste gradjanina "<<g[br]->DajImeIPrezime()<<" JMBG: "<<g[br]->DajJMBG()<<"."<<std::endl;
        }
        catch(std::logic_error era)
        {
            std::cout<<era.what()<<std::endl;
            i--;
        }
        br++;
    }
    for(int i=0; i<=br; i++) delete g[i];
	return 0;
}