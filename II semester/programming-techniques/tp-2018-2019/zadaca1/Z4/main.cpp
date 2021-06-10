//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <iostream>
#include <vector>
#include <cctype>

bool spejs(char p)
{
	if((p>='A' && p<='Z') || (p>='a' && p<='z') || (p>='0' && p<='9')) return false;
	else {
		return true;
	}
}

bool jelpalindrom(std::string rijec)
{

	bool palindrom=true;
	if(rijec.length()<2) return false;

	for(int i=0; i<rijec.length(); i++) {
		if(std::tolower(rijec.at(i))==std::tolower(rijec.at(rijec.length()-1-i))) {
			palindrom=true;

		} else {
			palindrom=false;
			break;
		}
	}


	return palindrom;

}

std::vector<std::string> NadjiSimetricneRijeci(std::string recenica)
{
	std::vector<std::string> kontenjer(1);

	bool jednarijec=true;
	bool kraj=false;
	int redbroj=0;

	for(int i=0; i<recenica.length(); i++) {
		if(spejs(recenica.at(i))) continue;

		else {
			while(!spejs(recenica.at(i))) {
				if(i==recenica.length()) break;
				jednarijec=true;
				if(jednarijec) {
					kontenjer.at(redbroj).push_back(recenica.at(i));
				}

				i++;
				if(i==recenica.length()) {
					kraj=true;
					break;
				}
			}
			if(kraj) break;
			else if(spejs(recenica.at(i))) {
				jednarijec=false;
				redbroj++;
				kontenjer.resize(redbroj+1);

			}
		}
	}

	for(int i=0; i<kontenjer.size(); i++) {
		if(!jelpalindrom(kontenjer.at(i))) {
			for(int j=i; j<kontenjer.size()-1; j++) {
				kontenjer.at(j)=kontenjer.at(j+1);
			}
			kontenjer.resize(kontenjer.size()-1);
			i--;
		}

	}

	return kontenjer;

}

int main ()
{

	std::cout<<"Unesite recenicu:";
	std::string rec;

	std::getline(std::cin, rec);

	std::cout<<std::endl;

	auto rijeci=NadjiSimetricneRijeci(rec);

	if(rijeci.size()==0) {
		std::cout<<"Recenica ne sadrzi simetricne rijeci!";
		return 0;
	}
	std::cout<<"Simetricne rijeci unutar recenice su:\n";

	for(int i=0; i<rijeci.size(); i++) {

		std::cout<<rijeci.at(i)<<std::endl;
	}

	return 0;
}
