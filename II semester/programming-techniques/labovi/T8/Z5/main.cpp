//TP 2016/2017: Tutorijal 8, Zadatak 5
#include <iostream>

template <typename TipElemenata>
struct Cvor {
    TipElemenata element;
    Cvor *veza;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni)
{
    Cvor<TipElemenata> *pocetak(nullptr), *prethodni;
    for(;;) {
        TipElemenata broj;
        std::cin >> broj;
        if(broj == zavrsni) break;
        Cvor<TipElemenata> *novi(new Cvor<TipElemenata>); // Kreiranje novog čvora
        novi->element = broj;
        novi->veza = nullptr;
        if(!pocetak) pocetak = novi; // Prvi čvor...
        else prethodni->veza = novi; // Svi osim prvog...
        prethodni = novi;
    }
    return pocetak;
}

template <typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata> *pocetak)
{
    int brojac(0);
    for(auto *p = pocetak; p != nullptr; p = p->veza) brojac++;
    return brojac;
}

template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak)
{
    if(pocetak == nullptr) return TipElemenata();
    TipElemenata brojac(0);
    for(Cvor<TipElemenata> *p = pocetak; p != nullptr; p = p->veza) brojac += p->element;
    return brojac;
}

template <typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag)
{
    if(pocetak == nullptr) return 0;
    int brojac(0);
    for(auto *p = pocetak; p != nullptr; p = p->veza) if(p->element > prag) brojac++;
    return brojac;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak)
{
    if(pocetak == nullptr) return;
    Cvor<TipElemenata> *pomocni;
    while (pocetak != nullptr) {
        pomocni = pocetak;
        pocetak = pocetak->veza;
        delete pomocni;
    }
}

int main()
{
    Cvor<double> *pocetak = nullptr;
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    pocetak = KreirajPovezanuListu<double>(0);
    std::cout << "U slijedu ima " <<  BrojVecihOd(pocetak, SumaElemenata(pocetak)/BrojElemenata(pocetak))  <<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(pocetak);
    return 0;
}