//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <limits>

bool aktivan=true;
enum class Smjer {Nalijevo, Nadesno};
enum class Pravci {Jug, Zapad, Sjever, Istok};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nadesno, Nalijevo, Idi, Kraj};

void AktivirajRobota();
void DeaktivirajRobota();
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu);
void Idi(int &x, int &y, Pravci orijentacija, int korak);
void IspisiPoziciju(int x, int y, Pravci orijentacija);
void PrijaviGresku(KodoviGresaka kod_greske);
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija);

void AktivirajRobota()
{
    if(aktivan==false) aktivan=true;
}
void DeaktivirajRobota()
{
    aktivan=false;
}

void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu)
{
    if(aktivan)
    {
        if(na_koju_stranu==Smjer::Nalijevo)
        {
            if(orijentacija==Pravci::Sjever) orijentacija=Pravci::Zapad;
            else if(orijentacija==Pravci::Zapad) orijentacija=Pravci::Jug;
            else if(orijentacija==Pravci::Jug) orijentacija=Pravci::Istok;
            else if(orijentacija==Pravci::Istok) orijentacija=Pravci::Sjever;
        }
        else if(na_koju_stranu==Smjer::Nadesno)
        {
            if(orijentacija==Pravci::Sjever) orijentacija=Pravci::Istok;
            else if(orijentacija==Pravci::Istok) orijentacija=Pravci::Jug;
            else if(orijentacija==Pravci::Jug) orijentacija=Pravci::Zapad;
            else if(orijentacija==Pravci::Zapad) orijentacija=Pravci::Sjever;
        }
        
    }
}

void Idi(int &x, int &y, Pravci orijentacija, int korak)
{
    if(aktivan)
    {
        if(korak>0)
        {
            if(orijentacija==Pravci::Istok) x=x+korak;
            else if(orijentacija==Pravci::Zapad) x=x-korak;
            else if(orijentacija==Pravci::Sjever) y=y+korak;
            else if(orijentacija==Pravci::Jug) y=y-korak;
        }
        else if(korak<0)
        {
            if(orijentacija==Pravci::Istok) x=x+korak;
            else if(orijentacija==Pravci::Zapad) x=x-korak;
            else if(orijentacija==Pravci::Jug) y=y-korak;
            else if(orijentacija==Pravci::Sjever) y=y+korak;
        }
    }
}

void IspisiPoziciju(int x, int y, Pravci orijentacija)
{
    if(aktivan)
    {
        if(orijentacija==Pravci::Sjever) std::cout<<"Robot je trenutno aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever."<<std::endl;
        else if(orijentacija==Pravci::Istok) std::cout<<"Robot je trenutno aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na istok."<<std::endl;
        else if(orijentacija==Pravci::Jug) std::cout<<"Robot je trenutno aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jug."<<std::endl;
        else if(orijentacija==Pravci::Zapad) std::cout<<"Robot je trenutno aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na zapad."<<std::endl;
    }
    else if(!aktivan)
    {
        if(orijentacija==Pravci::Sjever) std::cout<<"Robot je trenutno neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na sjever."<<std::endl;
        else if(orijentacija==Pravci::Istok) std::cout<<"Robot je trenutno neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na istok."<<std::endl;
        else if(orijentacija==Pravci::Zapad) std::cout<<"Robot je trenutno neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na zapad."<<std::endl;
        else if(orijentacija==Pravci::Jug) std::cout<<"Robot je trenutno neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na jug."<<std::endl;
        
    }
}

void PrijaviGresku(KodoviGresaka kod_greske)
{
    if(kod_greske==KodoviGresaka::PogresnaKomanda) std::cout<<"Nerazumljiva komanda!"<<std::endl;
    else if(kod_greske==KodoviGresaka::NedostajeParametar) std::cout<<"Komanda trazi parametar koji nije naveden!"<<std::endl;
    else if(kod_greske==KodoviGresaka::NeispravanParametar) std::cout<<"Parametar komande nije ispravan!"<<std::endl;
    else if(kod_greske==KodoviGresaka::SuvisanParametar) std::cout<<"Zadan je suvisan parametar nakon komande!"<<std::endl;
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija)
{
    if(komanda==Komande::Aktiviraj) AktivirajRobota();
    else if(komanda==Komande::Deaktiviraj) DeaktivirajRobota();
    else if(komanda==Komande::Nalijevo) Rotiraj(orijentacija, Smjer::Nalijevo);
    else if(komanda==Komande::Nadesno) Rotiraj(orijentacija, Smjer::Nadesno);
    else if(komanda==Komande::Idi) Idi(x,y,orijentacija,parametar);
    
}

bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske)
{
    char slovo;
    std::cout<<"\nUnesi komandu: ";
   // std::cin.ignore(10000,'\n');
    std::cin>>slovo;
    if(slovo=='D')
    {
        char a=getchar();
        if(a!=' ' && a!='\n') 
        {
            kod_greske=KodoviGresaka::SuvisanParametar;
            return false;
        }
        while(a!='\n')
        {
            if(a!=' ' && a!='\n')
            {
                kod_greske=KodoviGresaka::SuvisanParametar;
                return false;
            }
            a=getchar();
        }
        komanda=Komande::Nadesno;
        return true;
    }
    
    if(slovo=='L')
    {
        char a=getchar();
        if(a!=' ' && a!='\n')
        {
            kod_greske=KodoviGresaka::SuvisanParametar;
            return false;
        }
        while(a!='\n')
        {
            if(a!=' ' && a!='\n')
            {
                kod_greske=KodoviGresaka::SuvisanParametar;
                return false;
            }
            a=getchar();
        }
        komanda=Komande::Nalijevo;
        return true;
    }
    
    if(slovo=='K')
    {
      
        char a=getchar();
        if(a!=' ' && a!='\n')
        {
            kod_greske=KodoviGresaka::SuvisanParametar;
            return false;
        }
        while(a!='\n')
        {

            if(a!=' ' && a!='\n')
            {
                kod_greske=KodoviGresaka::SuvisanParametar;
                return false;
            }
            a=getchar();
        }
    
        komanda=Komande::Kraj;
        parametar=0;
        return true;
    }
    
    if(slovo=='A')
    {
      
        char a=getchar();
        if(a=='+' && a!='\n')
        {
            a=getchar();
            while(a!='\n')
            {
              if(a!=' ' && a!='\n')
              {
                  kod_greske=KodoviGresaka::SuvisanParametar;
                  return false;
              }
                a=getchar();
            }
            komanda=Komande::Aktiviraj;
            parametar=0;
            return true;
        }
        else if(a=='-' && a!='\n')
        {
            a=getchar();
            while(a!='\n')
            {
                if(a!=' ' && a!='\n')
                {
                    kod_greske=KodoviGresaka::SuvisanParametar;
                    return false;
                }
                a=getchar();
            }
            komanda=Komande::Deaktiviraj;
            return true;
        }
        else if(a=='\n')
        {
            kod_greske=KodoviGresaka::NedostajeParametar;
            return false;
        }
    }
    
    if(slovo=='I')
    {
        char a=getchar();
        bool nedobro=false;
        bool broj=true;
        bool negativan=false;
        int tk=10;
        int cifra=0;
        int brojac=0;
        while(a!='\n')
        {
            if(a=='-' && brojac==0) negativan=true;
            else if(a=='-' && brojac!=0) broj=false; 
            if(a!=' ') nedobro=true;
            if(!(a>='0' && a<='9') && a!=' ' && a!='-') broj=false;
            if(a>='0' && a<='9')
            {
                cifra=cifra*tk + (a-'0');
                brojac++;
            }
            a=getchar();
        }
    
        if(negativan) parametar=(-1)*cifra;
        else if(!negativan) parametar=cifra;
        if(nedobro==false)
        {
            kod_greske=KodoviGresaka::NedostajeParametar;
            return false;
        }
        if(broj==false)
        {
            kod_greske=KodoviGresaka::NeispravanParametar;
            return false;
        }

            komanda=Komande::Idi;
            return true;

    }
    else
   {    std::cin.ignore(10000,'\n');
       kod_greske=KodoviGresaka::PogresnaKomanda;
         return false;
   }
    
}


int main ()
{
    int x,y;
    x=y=0;
    Pravci orijentacija=Pravci::Sjever;
    IspisiPoziciju(x,y,orijentacija);
    Komande komanda;
    KodoviGresaka greska;
    int parametar;
    
    while(true)
    {
        if(UnosKomande(komanda,parametar,greska))
        {
            if(komanda==Komande::Aktiviraj)
            {
                AktivirajRobota();
                IspisiPoziciju(x,y,orijentacija);
            }
            else if(komanda==Komande::Deaktiviraj)
            {
                DeaktivirajRobota();
                IspisiPoziciju(x,y,orijentacija);
            }
            else if(komanda==Komande::Nadesno)
            {
                Rotiraj(orijentacija,Smjer::Nadesno);
                IspisiPoziciju(x,y,orijentacija);
            }
            else if(komanda==Komande::Nalijevo)
            {
                Rotiraj(orijentacija, Smjer::Nalijevo);
                IspisiPoziciju(x,y,orijentacija);
            }
            else if(komanda==Komande::Idi)
            {
                Idi(x,y,orijentacija,parametar);
                IspisiPoziciju(x,y,orijentacija);
            }
            else if(komanda==Komande::Kraj)
            {
                std::cout<<"Dovidjenja!";
                return 0;
            }
        }
        else
        {
            PrijaviGresku(greska);
        }
    }
    
	return 0;
}