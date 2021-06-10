/*
    TP 16/17 (Tutorijal 12, Zadatak 6)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>

template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
	std::string Pretvoriustring(double x) {
		std::string novi;
		novi = std::to_string(x);
		int lsd=novi.length();
		for(; lsd>0 && novi[lsd-1] == '0'; lsd--);
		novi.resize(lsd);
		if(novi[lsd-1] == '.') novi.resize(lsd-1);
		return novi;
	}
public:
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
	~Matrica() {
		DealocirajMemoriju(elementi, br_redova);
	}
	Matrica &operator =(const Matrica &m);
	Matrica &operator =(Matrica &&m);

	template<typename tip2>
	friend std::ostream &operator << (std::ostream& ispis, Matrica<tip2> m);		// moraju biti friend vazda
	template <typename Tip3>
	friend std::istream &operator >> (std::istream& ispis, Matrica<Tip3> &m);		// mora biti friend vazda

	friend Matrica<TipEl> operator *(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
		if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
		Matrica<TipEl> m3(m1.br_redova, m2.br_kolona);
		try {
			for(int i=0; i < m1.br_redova; i++) {
				for(int j=0; j < m2.br_kolona; j++) {
					TipEl suma(0);
					for(int k=0; k < m2.br_redova; k++) {
						suma += m1.elementi[i][k] * m2.elementi[k][j];
					}
					m3.elementi[i][j] = suma;
				}
			}
		} catch(...) {
			throw std::bad_alloc();
		}
		return m3;
	}
	Matrica<TipEl> operator *=(double x) {
		for(int i=0; i < br_redova; i++) {
			for(int j=0; j < br_redova; j++) {
				elementi[i][j] *= x;
			}
		}
		return *this;
	}

	Matrica<TipEl> operator *=(const Matrica<TipEl> &m2) {
		Matrica<TipEl> m1(*this);
		if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
		Matrica<TipEl> m3(m1.br_redova, m2.br_kolona);
		try {
			for(int i=0; i < m1.br_redova; i++) {
				for(int j=0; j < m2.br_kolona; j++) {
					TipEl suma(0);
					for(int k=0; k < m2.br_redova; k++) {
						suma += m1.elementi[i][k] * m2.elementi[k][j];
					}
					m3.elementi[i][j] = suma;
				}
			}
		} catch(...) {
			throw std::bad_alloc();
		}
		DealocirajMemoriju(elementi, br_redova);
		br_kolona = m2.br_kolona;
		elementi = AlocirajMemoriju(br_redova, br_kolona);
		for(int i=0; i < br_redova; i++) {
			for(int j=0; j < br_kolona; j++) {
				elementi[i][j] = m3[i][j];
			}
		}
		return *this;
	}


	friend Matrica<TipEl> operator -(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
		if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
		Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
		for(int i=0; i < m1.br_redova; i++) {
			for(int j=0; j < m2.br_kolona; j++) {
				m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
			}
		}
		return m3;
	}

	friend Matrica<TipEl> operator +(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
		if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
		Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
		for(int i=0; i < m1.br_redova; i++) {
			for(int j=0; j < m2.br_kolona; j++) {
				m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
			}
		}
		return m3;
	}

	friend Matrica<TipEl> operator *(const Matrica<TipEl> &m1, double a) {
		Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
		for(int i=0; i < m1.br_redova; i++) {
			for(int j=0; j < m1.br_kolona; j++) {
				m3.elementi[i][j] = m1.elementi[i][j] *a;
			}
		}
		return m3;
	}

	friend Matrica<TipEl> operator *(double a, const Matrica<TipEl> &m1) {
		return m1 * a;
	}


	Matrica<TipEl> &operator +=(const Matrica<TipEl> &m) {
		if(br_redova != m.br_redova || br_kolona != m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
		for(int i=0; i < br_redova; i++) {
			for(int j=0; j < br_kolona; j++) {
				elementi[i][j] += m[i][j];
			}
		}
		return *this;
	}
	Matrica<TipEl> &operator -=(const Matrica<TipEl> &m) {
		if(br_redova != m.br_redova || br_kolona != m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
		for(int i=0; i < br_redova; i++) {
			for(int j=0; j < br_kolona; j++) {
				elementi[i][j] -= m[i][j];
			}
		}
		return *this;
	}

	TipEl* operator [](int indeks) const {
		return elementi[indeks];
	}
	TipEl* operator [](int indeks) {
		return elementi[indeks];
	}

	TipEl operator ()(int indeks1, int indeks2) const {
		if(indeks1 <1 || indeks1 > br_redova)  throw std::range_error("Neispravan indeks");
		if(indeks2 <1 || indeks2 > br_kolona) throw std::range_error("Neispravan indeks");
		return elementi[indeks1-1][indeks2-1];
	}
	TipEl &operator ()(int indeks1, int indeks2) {
		if(indeks1 <1 || indeks1 > br_redova)  throw std::range_error("Neispravan indeks");
		if(indeks2 <1 || indeks2 > br_kolona) throw std::range_error("Neispravan indeks");
		return elementi[indeks1-1][indeks2-1];
	}

	operator std::string();

	void Unesi();
	void Ispisi(int sirina_ispisa) const;
	template <typename Tip2>
	friend Matrica<Tip2> ZbirMatrica(const Matrica<Tip2> &m1, const Matrica<Tip2> &m2);
};
template <typename tip>
Matrica<tip>::operator std::string()
{
	std::string novi;
	novi += '{';
	for(int i=0; i < br_redova; i++) {
		novi += '{';
		for(int j = 0; j < br_kolona; j++) {
			novi += Pretvoriustring(elementi[i][j]);
			if(j != br_kolona-1) novi += ',';
		}
		novi += '}';
		if(i != br_redova-1) novi += ',';
	}
	novi += '}';
	return novi;
}


template <typename TipEl>
std::ostream &operator <<(std::ostream &ispis, Matrica<TipEl> m)
{
	int duzina = ispis.width();
	for(int i=0; i < m.br_redova; i++) {
		for(int j=0; j < m.br_kolona; j++) {
			ispis.width(duzina);
			ispis << m.elementi[i][j];
		}
		std::cout << std::endl;
	}
	return ispis;
}

template <typename TipEl>
std::istream &operator >>(std::istream &ispis, Matrica<TipEl> &m)
{
	for(int i=0; i < m.br_redova; i++) {
		for(int j=0; j <m.br_kolona; j++) {
			std::cout << m.ime_matrice << '(' << i+1 << ',' << j+1 << ')' << " = ";
			ispis >> m.elementi[i][j];
		}
	}
	return ispis;
}

template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona)
{
	TipEl **elementi(new TipEl*[br_redova] {});
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime), elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi)
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova), br_kolona(m.br_kolona), ime_matrice(m.ime_matrice), elementi(AlocirajMemoriju(m.br_redova, m.br_kolona))
{
	KopirajElemente(m.elementi);
}

template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice)
{
	m.br_redova = 0;
	m.elementi = nullptr;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m)
{
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor(AlocirajMemoriju(m.br_redova, m.br_kolona));
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;
	} else if(br_redova > m.br_redova)
		for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	br_redova = m.br_redova;
	br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m)
{
	std::swap(br_redova, m.br_redova);
	std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice);
	std::swap(elementi, m.elementi);
	return *this;
}

template <typename TipEl>
void Matrica<TipEl>::Unesi()
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++) {
			std::cout << ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
			std::cin >> elementi[i][j];
		}
}

template <typename TipEl>
void Matrica<TipEl>::Ispisi(int sirina_ispisa) const
{
	for(int i = 0; i < br_redova; i++) {
		for(int j = 0; j < br_kolona; j++)
			std::cout << std::setw(sirina_ispisa) << elementi[i][j];
		std::cout << std::endl;
	}
}

template <typename TipEl>
Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
	return m3;
}

int main()
{

	int m, n;
	std::cout << "Unesi broj redova i kolona za matrice:\n";
	std::cin >> m >> n;
	try {
		Matrica<double> a(m, n, 'A'), b(m, n, 'B');
		std::cout << "Unesi matricu A:\n";
		std::cin >> a;
		std::cout << "Unesi matricu B:\n";
		std::cin >> b;
		std::cout << "Zbir ove dvije matrice je:\n";
		std::cout << std::setw(7) << a + b;
		std::cout << a[0][0] << std::endl;
		std::cout << a(0,0);
		a*=a;
		a*=5;
		a+=a;
		a-=a;
		std::cout << a;
	} catch(std::bad_alloc) {
		std::cout << "Nema dovoljno memorije!\n";
	}
	catch(...){
		std::cout << std::endl << "Nema nema tituleeeee...";
	}
	return 0;
}
