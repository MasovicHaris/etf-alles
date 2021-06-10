//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 4, Zadatak 1
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
typedef std::pair<double,double> Tacka;

class Trougao
{
    Tacka t1, t2, t3;
    bool kolinearne(Tacka t1, Tacka t2, Tacka t3)
    {
        if((t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second))==0) return true;
        return false;
    }
    static double jednavamo(const Tacka &t1, const Tacka &t2, const Tacka &t3)
    {
        return (t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second));
    }
    void rota(Tacka &rot, const Tacka &t, double ugao)
    {
        rot=Tacka(t.first+(rot.first-t.first)*std::cos(ugao)-(rot.second-t.second)*std::sin(ugao), t.second+(rot.first-t.first)*std::sin(ugao)+(rot.second-t.second)*std::cos(ugao));
    }
    public:
    Trougao(const Tacka &tj1, const Tacka &tj2, const Tacka &tj3);
    void Postavi(const Tacka &tj1, const Tacka &tj2, const Tacka &tj3);
    void Postavi(int indeks, const Tacka &t);
    static int Orijentacija(const Tacka &tj1, const Tacka &tj2, const Tacka &tj3);
    Tacka DajTjeme(int indeks) const{if(indeks==1){ return t1;} else if(indeks==2) {return t2;} else if(indeks==3) {return t3;} else throw std::range_error("Nekorektan indeks");}
    double DajStranicu(int indeks) const;
    double DajUgao(int indeks) const;
    Tacka DajCentar() const;
    double DajObim() const {return DajStranicu(1)+DajStranicu(2)+DajStranicu(3);}
    double DajPovrsinu() const;
    bool DaLiJePozitivnoOrijentiran() const;
    bool DaLiJeUnutra(const Tacka &t) const;
    void Ispisi() const {std::cout<<"(("<<t1.first<<","<<t1.second<<"),("<<t2.first<<","<<t2.second<<"),("<<t3.first<<","<<t3.second<<"))";}
    void Transliraj(double delta_x, double delta_y);
    void Centriraj(const Tacka &t);
    void Rotiraj(const Tacka &t, double ugao);
    void Skaliraj(const Tacka &t, double faktor);
    void Rotiraj(double ugao);
    void Skaliraj(double faktor);
    friend bool DaLiSuIdenticni(const Trougao &t1, const Trougao &t2);
    friend bool DaLiSuPodudarni(const Trougao &t1, const Trougao &t2);
    friend bool DaLiSuSlicni(const Trougao &t1, const Trougao &t2);
    
};

Trougao::Trougao(const Tacka &tj1, const Tacka &tj2, const Tacka &tj3)
{
    if(kolinearne(tj1,tj2,tj3)) throw std::domain_error("Nekorektne pozicije tjemena");
    t1=tj1; t2=tj2; t3=tj3;
}

void Trougao::Postavi(const Tacka &tj1, const Tacka &tj2, const Tacka &tj3)
{
    if(kolinearne(tj1,tj2,tj3)) throw std::domain_error("Nekorektne pozicije tjemena");
    t1=tj1; t2=tj2; t3=tj3;
}

void Trougao::Postavi(int indeks, const Tacka &t)
{
    if(indeks==1) (*this).Postavi(t,t2,t3);
    else if(indeks==2) (*this).Postavi(t1,t,t3);
    else if(indeks==3) (*this).Postavi(t1,t2,t);
    else throw std::range_error("Nekorektan indeks");
}

int Trougao::Orijentacija(const Tacka &tj1, const Tacka &tj2, const Tacka &tj3)
{
    if((tj1.first*(tj2.second-tj3.second)-tj2.first*(tj1.second-tj3.second)+tj3.first*(tj1.second-tj2.second))==0) return 0;
    else if((tj1.first*(tj2.second-tj3.second)-tj2.first*(tj1.second-tj3.second)+tj3.first*(tj1.second-tj2.second))>0) return 1;
    else return -1;
}

double Trougao::DajStranicu(int indeks) const
{
    if(indeks==1) return std::sqrt(std::pow(t2.first-t3.first,2) + std::pow(t2.second-t3.second,2));
    else if(indeks==2) return std::sqrt(std::pow(t1.first-t3.first,2)+std::pow(t1.second-t3.second,2));
    else if(indeks==3) return std::sqrt(std::pow(t2.first-t1.first,2)+std::pow(t2.second-t1.second,2));
    else throw std::range_error("Nekorektan indeks");
}

double Trougao::DajUgao(int indeks) const
{
    if(indeks==1) return acos((pow(DajStranicu(2),2)+pow(DajStranicu(3),2)-pow(DajStranicu(1),2))/(2*DajStranicu(2)*DajStranicu(3))); //alfa
    else if(indeks==2) return acos((pow(DajStranicu(1),2)+pow(DajStranicu(3),2)-pow(DajStranicu(2),2))/(2*DajStranicu(1)*DajStranicu(3))); //beta
    else if(indeks==3) return acos((pow(DajStranicu(1),2)+pow(DajStranicu(2),2)-pow(DajStranicu(3),2))/(2*DajStranicu(1)*DajStranicu(2))); //gama
    else throw std::range_error("Nekorektan indeks");
}

Tacka Trougao::DajCentar() const
{
    return std::make_pair((t1.first+t2.first+t3.first)/3., (t1.second+t2.second+t3.second)/3.);
}

double Trougao::DajPovrsinu() const
{
    return 0.5*fabs(t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second));
}

bool Trougao::DaLiJePozitivnoOrijentiran() const
{
    if(Orijentacija(t1,t2,t3)==1) return true;
    return false;
}

bool Trougao::DaLiJeUnutra(const Tacka &t) const
{
    if(Orijentacija(t1,t2,t3)==1 && Orijentacija(t1,t2,t)==1 && Orijentacija(t2,t3,t)==1 && Orijentacija(t3,t1,t)==1) return true;
    if(Orijentacija(t1,t2,t3)==-1 && Orijentacija(t1,t2,t)==-1 && Orijentacija(t2,t3,t)==-1 && Orijentacija(t3,t1,t)==-1) return true;
    return false;
}

void Trougao::Transliraj(double delta_x, double delta_y)
{
    t1.first+=delta_x; t1.second+=delta_y;
    t2.first+=delta_x; t2.second+=delta_y;
    t3.first+=delta_x; t3.second+=delta_y;
}

void Trougao::Centriraj(const Tacka &t)
{
    Tacka c=DajCentar();
    double delta_x=t.first-c.first;
    double delta_y=t.second-c.second;
    Transliraj(delta_x, delta_y);
}

void Trougao::Rotiraj(const Tacka &t, double ugao)
{
   rota(t1,t,ugao);
   rota(t2,t,ugao);
   rota(t3,t,ugao);
}

void Trougao::Skaliraj(const Tacka &t, double faktor)
{
    if(faktor==0) throw std::domain_error("Nekorektan faktor skaliranja");
    t1.first=t.first+faktor*(t1.first-t.first);
    t1.second=t.second+faktor*(t1.second-t.second);
    t2.first=t.first+faktor*(t2.first-t.first);
    t2.second=t.second+faktor*(t2.second-t.second);
    t3.first=t.first+faktor*(t3.first-t.first);
    t3.second=t.second+faktor*(t3.second-t.second);
}

void Trougao::Rotiraj(double ugao)
{
    Tacka c=DajCentar();
    Rotiraj(c,ugao);
}

void Trougao::Skaliraj(double faktor)
{
    Tacka c=DajCentar();
    Skaliraj(c,faktor);
}

bool DaLiSuIdenticni(const Trougao &t1, const Trougao &t2)
{
    Tacka niz1[3];
    Tacka niz2[3];
    niz1[0]=t1.DajTjeme(1); niz1[1]=t1.DajTjeme(2); niz1[2]=t1.DajTjeme(3);
    niz2[0]=t2.DajTjeme(1); niz2[1]=t2.DajTjeme(2); niz2[2]=t2.DajTjeme(3);
    int brojac(0);
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(niz1[i]==niz2[j]) {brojac++; break;}
        }
    }
    if(brojac==3) return true;
    return false;
}

bool DaLiSuPodudarni(const Trougao &trg1, const Trougao &trg2)
{
    
    std::vector<std::pair<Tacka,double>> vekaprvog{{trg1.t1, trg1.DajStranicu(1)}, {trg1.t2, trg1.DajStranicu(2)}, {trg1.t3, trg1.DajStranicu(3)}};
    std::vector<std::pair<Tacka,double>> vekadrugog{{trg2.t1, trg2.DajStranicu(1)}, {trg2.t2, trg2.DajStranicu(2)}, {trg2.t3, trg2.DajStranicu(3)}};
    
    std::sort(vekaprvog.begin(), vekaprvog.end(), [](std::pair<Tacka, double> a, std::pair<Tacka,double> b){
        return a.second>b.second;
    });
    std::sort(vekadrugog.begin(), vekadrugog.end(), [](std::pair<Tacka,double> a, std::pair<Tacka,double> b){
        return a.second>b.second;
    });
    
    std::vector<double> StranicePrvog{trg1.DajStranicu(1), trg1.DajStranicu(2), trg1.DajStranicu(3)};
    std::vector<double> StraniceDrugog{trg2.DajStranicu(1), trg2.DajStranicu(2), trg2.DajStranicu(3)};
    std::sort(StranicePrvog.begin(), StranicePrvog.end());
    std::sort(StraniceDrugog.begin(), StraniceDrugog.end());
    
    bool bul1=false;
    bool bul2(Trougao::jednavamo(vekaprvog[0].first, vekaprvog[1].first, vekaprvog[2].first)>0);
    bool bul3(Trougao::jednavamo(vekadrugog[0].first, vekadrugog[1].first, vekadrugog[2].first)>0);
    bool dobar=true;
    for(int i=0; i<StranicePrvog.size(); i++)
    {
        if(std::fabs(StranicePrvog[i]-StraniceDrugog[i])>1e-25) {dobar=false; break;}
    }
    if(dobar) bul1=true;
    else if(!dobar) bul1=false;
    if(bul1 && ((bul2 && bul3) || (!bul2 && !bul3))) return true;
    return false;
}

bool DaLiSuSlicni(const Trougao &trg1, const Trougao &trg2)
{
    std::vector<double> StranicePrvog{trg1.DajStranicu(1), trg1.DajStranicu(2), trg1.DajStranicu(3)};
    std::vector<double> StraniceDrugog{trg2.DajStranicu(1), trg2.DajStranicu(2), trg2.DajStranicu(3)};
    std::sort(StranicePrvog.begin(), StranicePrvog.end());
    std::sort(StraniceDrugog.begin(), StraniceDrugog.end());
    double k(StranicePrvog[0]/StraniceDrugog[0]);
    Trougao p1(trg1), p2(trg2);
    if(k>1) p2.Skaliraj(k);
    else if(k<1) p1.Skaliraj((1.0/k));
    if(DaLiSuPodudarni(p1,p2)) return true;
    return false;
}


int main ()
{
    std::cout<<"Koliko zelite kreirati trouglova: ";
    int n;
    std::cin>>n;
    std::vector<std::shared_ptr<Trougao>> veka;
    int brojac(0);
    Tacka tac1, tac2, tac3, tel1;
    while(brojac<n)
    {
        std::cout<<"Unesite podatke za "<<brojac+1<<". trougao (x1 y1 x2 y2 x3 y3): ";
        for(int i=0; i<3; i++)
        {
            double x;
            std::cin>>x;
            double y;
            std::cin>>y;
            if(i==0) tac1=std::make_pair(x,y);
            if(i==1) tac2=std::make_pair(x,y);
            if(i==2) tac3=std::make_pair(x,y);
        }
        try{
        veka.push_back(std::make_shared<Trougao>(tac1,tac2,tac3));
        }catch(std::domain_error e) {std::cout<<e.what()<<", ponovite unos!"<<std::endl; brojac--;}
        brojac++;
    }
    std::cout<<"Unesite vektor translacije (dx dy): ";
    double dx, dy;
    std::cin>>dx>>dy;
    std::cout<<"Unesite ugao rotacije: ";
    double ugao;
    std::cin>>ugao;
    std::cout<<"Unesite faktor skaliranja: ";
    double fakt;
    std::cin>>fakt;
    
    //transformacija
    std::transform(veka.begin(), veka.end(), veka.begin(), [&](std::shared_ptr<Trougao> v){
        v->Transliraj(dx,dy);
        v->Rotiraj(ugao);
        v->Skaliraj(v->DajTjeme(1),fakt);
        return v;
    });

    std::sort(veka.begin(), veka.end(), [](std::shared_ptr<Trougao>t1, std::shared_ptr<Trougao> t2){
        return t1->DajPovrsinu()<t2->DajPovrsinu();
    });
    
    std::cout<<"Trouglovi nakon obavljenih transformacija: "<<std::endl;
    std::for_each(veka.begin(), veka.end(), [](std::shared_ptr<Trougao> v){
        v->Ispisi(); std::cout<<std::endl;
    });
    std::cout<<"Trougao sa najmanjim obimom: ";
    (*std::min_element(veka.begin(), veka.end(), [](std::shared_ptr<Trougao>t1, std::shared_ptr<Trougao>t2){
        return t1->DajObim() < t2->DajObim();
    }))->Ispisi();
    
    std::cout<<std::endl;
    
    bool identicni(true);
    if(veka.empty()) std::cout<<"Nema identicnih trouglova!"<<std::endl;
    else
    {
        for(int i=0; i<veka.size(); i++)
        {
            for(int j=i+1; j<veka.size(); j++)
            {
                
                if(DaLiSuIdenticni(*veka[i], *veka[j]))
                {
                    if(identicni)
                    {
                        std::cout<<"Parovi identicnih trouglova: "<<std::endl;
                        identicni=false;
                    }
                    veka[i]->Ispisi(); std::cout<<" i "; veka[j]->Ispisi(); std::cout<<std::endl;
                }
            }
        }
        if(identicni) std::cout<<"Nema identicnih trouglova!"<<std::endl;
    }
    
    identicni=true;
    
    if(veka.empty()) std::cout<<"Nema podudarnih trouglova!"<<std::endl;
    else
    {
        for(int i=0; i<veka.size(); i++)
        {
            for(int j=i+1; j<veka.size(); j++)
            {
            
                if(DaLiSuPodudarni(*veka[i], *veka[j]))
                {
                    if(identicni)
                    {
                        std::cout<<"Parovi podudarnih trouglova: "<<std::endl;
                        identicni=false;
                    }
                    veka[i]->Ispisi(); std::cout<<" i "; veka[j]->Ispisi(); std::cout<<std::endl;
                }
            }
        }
        if(identicni) std::cout<<"Nema podudarnih trouglova!"<<std::endl;
    }
    
    identicni=true;
    
    if(veka.empty()) std::cout<<"Nema slicnih trouglova!"<<std::endl;
    else
    {
        for(int i=0; i<veka.size(); i++)
        {
            for(int j=i+1; j<veka.size(); j++)
            {
                
                if(DaLiSuSlicni(*veka[i],*veka[j]))
                {
                    if(identicni)
                    {
                        std::cout<<"Parovi slicnih trouglova: "<<std::endl;
                        identicni=false;
                    }
                    veka[i]->Ispisi(); std::cout<<" i "; veka[j]->Ispisi(); std::cout<<std::endl;
                }
            }
        }
        if(identicni) std::cout<<"Nema slicnih trouglova!"<<std::endl;
    }
    
    
    return 0;
}