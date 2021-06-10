#include <iostream>
#include <stdexcept>
#include <deque>

template <typename Tip>
class Red {
    std::deque<Tip> jednostruka;
public:
    Red(){ jednostruka = std::deque<Tip>(0); }
    Red(const Red<Tip> &r) : jednostruka(r.jednostruka){}
    Red(Red<Tip> &&r) : jednostruka(r.jednostruka){}
    Red<Tip> &operator= (const Red<Tip> &r) { jednostruka = r.jednostruka; return *this; }
    Red<Tip> operator= (Red<Tip> &&r) { jednostruka =r.jednostruka; return *this;}
    void brisi() { jednostruka = std::deque<Tip>(0); }
    void stavi(const Tip& el) { jednostruka.push_back(el); }
    Tip skini(){
        if (jednostruka.size() == 0) throw std::domain_error("Red je prazan!");
        Tip temp(jednostruka[0]);
        jednostruka.erase(jednostruka.begin());
        return temp;
    }
    int brojElemenata() { return jednostruka.size(); }
    Tip &celo() { if(jednostruka.size() == 0 ) throw std::domain_error("Greska"); return jednostruka[0]; }
    Tip celo() const { if(jednostruka.size() == 0) throw std::domain_error("Greska"); return jednostruka[0]; }
    Tip operator [](int i){  return jednostruka[i]; }
};
    
// brisi
template <typename Tip>
void f_1(Red<Tip> &l){
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi reda: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon brisanja: " << std::endl;
    l.brisi();
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
}
// stavi
template <typename Tip>
void f_2(Red<Tip> &l){
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi reda: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon dodavanja 1 elementa pomocu stavi(): " << std::endl;
    l.stavi(1337);
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
}
// skini
template <typename Tip>
void f_3(Red<Tip> &l){
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi reda: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon skidanja 1 elementa tj. nakon skini(): " << std::endl;
    l.skini();
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
}
// celo
template <typename Tip>
void f_4(Red<Tip> &l){
    l.stavi(1); l.stavi(2);
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi reda: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon promjena cela tj. 1 elementa: " << std::endl;
    l.celo() = 1337;
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    
    std::cout << std::endl << "Element na celu: " << l.celo();
    std::cout << std::endl;
}
// brojelemenata
template <typename Tip>
void f_5(Red<Tip> &l){
    std::cout << "Broj elemenata u redu: " << l.brojElemenata() << std::endl;
    std::cout << "Elementi reda: ";
    for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl;
    std::cout << "Red nakon dodavanja 1 elementa: " << std::endl;
    l.stavi(1338);
    std::cout << "Elementi Reda: "; for(int i=0; i < l.brojElemenata(); i++) std::cout << l[i] << " ";
    std::cout << std::endl << "Broj elemenata u redu nakon dodavanja na kraj reda: " << l.brojElemenata() << std::endl;
} 



int main() {
    Red<int> s;
    for (int i(1); i<=5; i++) s.stavi(i);
    f_1(s);
    std::cout << "------------------------------------" << std::endl;
    f_2(s);
    std::cout << "------------------------------------" << std::endl;
    f_3(s);
    std::cout << "------------------------------------" << std::endl;
    f_4(s);
    std::cout << "------------------------------------" << std::endl;
    f_5(s);
    std::cout << "------------------------------------" << std::endl;
    return 0;
}
