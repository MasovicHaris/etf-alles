/*
    TP 16/17 (Tutorijal 12, Zadatak 2)
	Autotestove napisao Kerim Hodzic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: khodzic2@etf.unsa.ba.

	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <set>

template <typename tip>
std::set<tip> &operator *=(std::set<tip> &skup1, std::set<tip> skup2)
{
	std::set<tip> novi;

	typename std::set<tip>::iterator it1(skup1.begin()), it2(skup1.end());
	while(it1 != it2) {
		if(skup2.find(*it1) != skup2.end()) {
			novi.insert(*it1);
		}
		it1++;
	}
	skup1 = novi;
	return skup1;

}

template <typename tip>
std::set<tip> &operator +=(std::set<tip> &skup1, std::set<tip> skup2)
{
	std::set<tip> novi;

	typename std::set<tip>::iterator it1(skup1.begin()), it2(skup1.end());
	typename std::set<tip>::iterator it21(skup2.begin()), it22(skup2.end());

	while(it1 != it2) {
		novi.insert(*it1);
		it1++;
	}
	while(it21 != it22) {
		novi.insert(*it21);
		it21++;
	}
	skup1 = novi;
	return skup1;
}
template <typename tip>
std::ostream &operator <<(std::ostream &ispis, std::set<tip> s)
{
	ispis << '{';
	auto i2(s.begin());
	if(s.size()==0) {
		return ispis << '}';
	}
	for(auto i=0; i < s.size()-1; i++) ispis << *i2++ << ",";
	ispis << *i2 << '}';
	return ispis;
}

template <typename tip>
std::set<tip> operator +(std::set<tip> skup1, std::set<tip> skup2)
{
	std::set<tip> novi(skup1 += skup2);
	return novi;
}

template <typename tip>
std::set<tip> operator *(std::set<tip> &skup1, std::set<tip> skup2)
{
	std::set<tip> novi(skup1 *= skup2);
	return novi;
}

template <typename tip1, typename tip2>
std::set<std::pair<tip1, tip2>> operator %(std::set<tip1> skup1, std::set<tip2> skup2)
{
	std::set<std::pair<tip1, tip2>> novi;

	typename std::set<tip1>::iterator it1(skup1.begin()), it2(skup1.end());
	typename std::set<tip2>::iterator it21(skup2.begin()), it22(skup2.end());

	while(it1 != it2) {
		while(it21 != it22) {
			novi.insert({*it1, *it21});
			it21++;
		}
		it21 = skup2.begin();
		it1++;
	}

	return novi;
}

template <typename tip1, typename tip2>
std::ostream &operator <<(std::ostream &ispis, std::set<std::pair<tip1, tip2>> s)
{
	ispis << '{';
	auto i2(s.begin());
	if(s.size()==0) {
		return ispis << '}';
	}
	for(auto i=0; i < s.size()-1; i++) {
		ispis << '(' << i2->first << "," << i2->second << ')' << ',';
		i2++;
	}
	ispis << '(' << i2->first << "," << i2->second << ')' << '}';
	return ispis;
}

int main ()
{
	std::set<int> s1 {3, 5, 1, 2, 8}, s2 {7, 2, 8, 4};
	std::cout << s1 + s2 << std::endl; // Ispis {1,2,3,4,5,7,8}
	std::cout << s1 * s2 << std::endl; // Ispis {2,8}

	std::set<char> s3 {'A', 'B'};
	std::set<char> s4 {1, 2, 3};
	std::cout << s1 % s2 << std::endl; // Ispis {(A,1),(A,2),(A,3),(B,1),(B,2),(B,3)}
	return 0;
}