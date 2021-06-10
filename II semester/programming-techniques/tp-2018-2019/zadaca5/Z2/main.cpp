//solved by @who.so (hhamzic1@etf.unsa.ba)
//TP 2018/2019: Zadaća 5, Zadatak 2
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iomanip>
class Berza
{
    std::vector<int> veka;
    int minimum;
    int maximum;
    public:
        Berza(int min, int max) 
        {
            if(min<0 || max<0) throw std::range_error("Ilegalne granice cijene");
            minimum=min;
            maximum=max;
        }
        explicit Berza(double max): minimum(0)
        {
            if(max<0) throw std::range_error("Ilegalne granice cijene");
            maximum=max;
        }
        void RegistrirajCijenu(int cijena)
        {
            if(cijena<minimum || cijena>maximum) throw std::range_error("Ilegalna cijena");
            veka.push_back(cijena);
        }
        int DajBrojRegistriranihCijena() const
        {
            return int(veka.size());
        }
        void BrisiSve() 
        {
            veka.resize(0);
        }
        int DajMinimalnuCijenu() const
        {
            if(veka.size()==0) throw std::range_error("Nema registriranih cijena");
            return *std::min_element(veka.begin(), veka.end());
        }
        int DajMaksimalnuCijenu() const
        {
            if(veka.size()==0) throw std::range_error("Nema registriranih cijena");
            return *std::max_element(veka.begin(), veka.end());
        }
        bool operator !()
        {
            if(veka.size()==0) return true;
            return false;
        }
        int DajBrojCijenaVecihOd(int n)
        {
            if(veka.size()==0) throw std::range_error("Nema registriranih cijena");
            return std::count_if(veka.begin(), veka.end(), std::bind(std::greater<int>(), std::placeholders::_1,n));
        }
        void Ispisi() const
        {
            
            std::vector<double>novi_vektor;
            std::copy(veka.begin(), veka.end(), std::back_inserter(novi_vektor));
            std::transform(novi_vektor.begin(),novi_vektor.end(), novi_vektor.begin(), std::bind(std::multiplies<double>(), 1./100, std::placeholders::_1));
            std::sort(novi_vektor.begin(), novi_vektor.end(), std::greater<double>());
            std::copy(novi_vektor.begin(), novi_vektor.end(), std::ostream_iterator<double>(std::cout<<std::setprecision(2)<<std::fixed, "\n"));
        }
        int operator [](int i)
        {
            if(i>veka.size() || i<1) throw std::range_error("Neispravan indeks");
            return veka[i-1];
        }
        Berza &operator ++()
        {
            std::transform(veka.begin(), veka.end(), veka.begin(), std::bind(std::plus<int>(), 100, std::placeholders::_1));
            auto it=std::find_if(veka.begin(), veka.end(), std::bind(std::greater<int>(), std::placeholders::_1, maximum));
            if(it==veka.end()) return *this;
            throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        }
        Berza operator ++(int)
        {
            Berza novi(*this);
            try{
            ++(*this);
            }catch(std::range_error e){throw;}
            return novi;
        }
        Berza &operator --()
        {
            std::transform(veka.begin(), veka.end(), veka.begin(), std::bind(std::plus<int>(),-100, std::placeholders::_1));
            auto it=std::find_if(veka.begin(), veka.end(), std::bind(std::less<int>(), std::placeholders::_1, minimum));
            if(it==veka.end()) return *this;
            throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        }
        Berza operator--(int)
        {
            Berza novi(*this);
            try
            {
            --(*this);
            }
            catch(std::range_error e){throw;}
            return novi;
        }

        Berza operator -()
        {
            Berza novi(*this);
            std::transform(novi.veka.begin(), novi.veka.end(), novi.veka.begin(), std::bind(std::minus<int>(), minimum+maximum, std::placeholders::_1));
            return novi;
        }
        Berza operator +(const int i)
        {
            Berza novi(*this);
            std::transform(novi.veka.begin(), novi.veka.end(), novi.veka.begin(), std::bind(std::plus<int>(), i, std::placeholders::_1));
            auto it=std::find_if(novi.veka.begin(), novi.veka.end(), std::bind(std::greater<int>(), std::placeholders::_1, maximum));
            if(it!=novi.veka.end()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
            return novi;
        }
        friend Berza operator +(const int i, const Berza &b);
        Berza operator -(int i)
        {
            Berza novi(*this);
            std::transform(novi.veka.begin(), novi.veka.end(), novi.veka.begin(), std::bind(std::plus<int>(), -i, std::placeholders::_1));
            auto it=std::find_if(novi.veka.begin(), novi.veka.end(), std::bind(std::less<int>(), std::placeholders::_1, minimum));
            if(it!=novi.veka.end()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
            return novi;
        }
        friend Berza operator -(int i, Berza &b);
        friend Berza operator -(Berza &berzica1, Berza &berzica2);
        Berza &operator +=(const int i)
        {
            auto k=(*this)+i;
            *this=k;
            return *this;
        }
        Berza &operator -=(int i)
        {
            auto k=(*this)-i;
            *this=k;
            return *this;
        }
        friend void operator -=(Berza &berzica1, Berza &berzica2);
        bool operator ==(Berza &berzica2)
        {
            return this->veka==berzica2.veka;
        }
        bool operator !=(Berza &berzica2)
        {
            return !(*this==berzica2);
        }
    
};
Berza operator +(const int i, Berza &b)
{
    return b+i;
}
Berza operator -(int i, Berza &b)
{
    Berza novi(b);
    std::transform(novi.veka.begin(), novi.veka.end(), novi.veka.begin(), std::bind(std::minus<int>(),i, std::placeholders::_1));
    auto it=std::find_if(novi.veka.begin(), novi.veka.end(), std::bind(std::less<int>(), std::placeholders::_1, novi.minimum));
    if(it!=novi.veka.end()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    auto ti=std::find_if(novi.veka.begin(), novi.veka.end(), std::bind(std::greater<int>(), std::placeholders::_1, novi.maximum));
    if(ti!=novi.veka.end()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return novi;
    
}
Berza operator -(Berza &berzica1, Berza &berzica2)
{
    if(berzica1.veka.size()!=berzica2.veka.size() || berzica1.minimum!=berzica2.minimum || berzica1.maximum!=berzica2.maximum) throw std::domain_error("Nesaglasni operandi");
    Berza novi(berzica1);
    std::transform(novi.veka.begin(), novi.veka.end(), berzica2.veka.begin(), novi.veka.begin(), std::minus<int>());
    auto it=std::find_if(novi.veka.begin(), novi.veka.end(), std::bind(std::less<int>(), std::placeholders::_1, novi.minimum));
    if(it!=novi.veka.end()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    auto ti=std::find_if(novi.veka.begin(), novi.veka.end(), std::bind(std::greater<int>(), std::placeholders::_1, novi.maximum));
    if(ti!=novi.veka.end()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return novi;
}
void operator -=(Berza &berzica1, Berza &berzica2)
{
    berzica1=berzica1-berzica2;
}


int main ()
{
	Berza viki(323);
	Berza vile(323);
	viki.RegistrirajCijenu(198);
	viki.RegistrirajCijenu(198);
	viki.RegistrirajCijenu(198);
	vile.RegistrirajCijenu(198);
	vile.RegistrirajCijenu(198);
	vile.RegistrirajCijenu(192);
    if(viki!=vile) std::cout<<"isti nisu";
    else return 0;
	
}