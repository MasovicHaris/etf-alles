//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <iostream>
#include <vector>
#include <iomanip>
#include <complex>
#include <stdexcept>
#include <limits>

typedef std::vector<std::vector<int>> matrica;

std::complex<int> sahat(int n)   // funkcija koja omogucuje notaciju u clockwise smjeru
{
	switch(n) {
	case 1:
		return std::complex<int>(-1, 0);
		break;
	case 2:
		return std::complex<int>(-1, 1);
		break;
	case 3:
		return std::complex<int>(0, 1);
		break;
	case 4:
		return std::complex<int>(1, 1);
		break;
	case 5:
		return std::complex<int>(1, 0);
		break;
	case 6:
		return std::complex<int>(1, -1);
		break;
	case 7:
		return std::complex<int>(0, -1);
		break;
	case 8:
		return std::complex<int>(-1, -1);
		break;
	}

	return std::complex<int>(0,0);
}

bool velement(matrica mat, int red, int kol)   //funkcija koja provjerava da li je taj element u matrici
{

	if(red>=0 && red<mat.size() && kol>=0 && kol<mat.at(red).size()) {
		return true;
	} else {
		return false;
	}
}



std::complex<double> VrhMatrice(matrica mat, int red, int kol)
{
	if(mat.size()==0) throw std::domain_error("Nekorektna matrica");

	for(int h=1; h<mat.size(); h++) {
		if(mat.at(h).size()!=mat.at(0).size() || mat.at(h).size()==0) throw std::domain_error("Nekorektna matrica");
	}

	if(!velement(mat, red, kol)) throw std::range_error("Nekorektna pocetna pozicija");


	bool vrh=true;
	int kvotai=0, kvotaj=0, temp=0;

	std::vector<int> poziv{1, 2, 3, 4, 5, 6, 7, 8};  //pomocu ovog vektora koji pozivamo dobijamo redom koordinate u clockwise notaciji

	int i=0, j=0;
	for(;;) { //besk petlja
		i=red;

		for(;;) { //besk petlja
			j=kol;
			for(int k=0; k<poziv.size(); k++) { // provjeravamo da li je odmah taj element ujedno i vrh matrice sa ovim blokom koda
				auto offset=sahat(poziv.at(k));

				if(velement(mat, i+offset.real(), j+offset.imag())) {
					if(mat.at(i).at(j)>= mat.at(i+offset.real()).at(j+offset.imag())) {
						vrh=true;
					} else {
						vrh=false;
						break;
					}
				}
			}

			if(vrh) { // ako jest vrati njegove koordinate
				return std::complex<double>(red, kol);
			} else if(vrh==false) { //ako nije trazimo najveci broj oko njega

				for(int l=i;;) { //besk petlja
					for(int g=j;;) { //besk petlja

						for(int q=0; q<poziv.size(); q++) { //stavljamo prvi broj koji je pored izabranog broja i koji je u matrici kao temp za potencijalni vrh
							auto prvitemp=sahat(poziv.at(q));
							int	c=l+prvitemp.real();
							int	d=g+prvitemp.imag();
							if(velement(mat, c, d)) {
								temp=mat.at(c).at(d);
								kvotai=c;
								kvotaj=d;
								break;   //nasao se prvi temp maximum u clockwise smjeru i breakamo;
							}

						}

						for(int k=0; k<poziv.size(); k++) { //upoređujemo sa ostalim njegovim susjedima da li ima neki veci broj ako da onda on postaje max
							auto maximum=sahat(poziv.at(k));
							int a=l+maximum.real();
							int b=g+maximum.imag();
							if(velement(mat, a, b)) {
								int max=mat.at(a).at(b);
								if(max>temp) {
									temp=max;
									kvotai=a;		//imamo kvote maximuma
									kvotaj=b;
								}
							}

						}

						break; //brejkaju se sve petlje osim vanjske beskonacne

					}
					break;
				}

			}
			break;

		}
		red=kvotai;   //red postane kvota maximuma koji se nalazi oko naseg broja, također i kolona te se sve ponovo gleda da li je taj broj vrh matrice
		kol=kvotaj;		//ako nije onda trazimo najveci broj do njega i tako u krug
	}

	return std::complex<double>(0, 0);  //samo zbog warninga, f-ja nikad nece vratiti ovu vrijednost

}

int main ()
{
	std::cout<<"Unesite broj redova i kolona matrice:";
	int red, kol;
	std::cin>>red;
	std::cin>>kol;
	std::cin.clear();
	std::cin.ignore(1000000,'\n');
	std::cout<<std::endl;
	std::cout<<"Unesite elemente matrice:";

	matrica matra(red, std::vector<int>(kol));
	int elem;
	for(int i=0; i<matra.size(); i++) {
		for(int j=0; j<matra.at(i).size(); j++) {
			std::cin>>elem;
			matra.at(i).at(j)=elem;
		}

	}
	std::cout<<std::endl;
	std::cin.clear();
	std::cin.ignore(100000,'\n');
	std::cout<<"Unesite poziciju odakle zapocinje pretraga:";
	std::cin>>red>>kol;
	std::cout<<std::endl;
	try {
		auto pozicija=VrhMatrice(matra, red, kol);

		std::cout<<"Nadjen je vrh matrice na poziciji "<<pozicija.real()<<" "<<pozicija.imag()<<std::endl;
		std::cout<<"Njegova vrijednost je "<<matra.at(pozicija.real()).at(pozicija.imag());
	} catch(std::domain_error izuzetak) {
		std::cout<<izuzetak.what();
	} catch(std::range_error izuzetak2) {
		std::cout<<"Greska: "<<izuzetak2.what();
	}
	return 0;
}
