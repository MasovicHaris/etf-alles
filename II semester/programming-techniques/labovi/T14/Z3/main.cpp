/* 
    TP 16/17 (Tutorijal 11, Zadatak 4)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <new>
#include <stdexcept>
class Tim
{
	char ime_tima[20];
	int odigrane, pobjede, nerijesene, porazi, dati, primljeni, bodovi;
	public:
	Tim(const char ime[]):odigrane(0),pobjede(0),nerijesene(0),porazi(0),dati(0),primljeni(0),bodovi(0)
	{
		if(strlen(ime) >= 20) throw std::range_error("Predugacko ime tima");
		strcpy(ime_tima, ime);
	}
	void ObradiUtakmicu(int broj_datih, int broj_primljenih)
	{
		if(broj_primljenih < 0 || broj_datih < 0) throw std::range_error("Neispravan broj golova");
		if(broj_datih > broj_primljenih) { pobjede++; bodovi+=3; }
		else if(broj_datih == broj_primljenih) { nerijesene++; bodovi++; }
		else porazi++;
		odigrane++;
		dati += broj_datih;
		primljeni += broj_primljenih;
	}
	const char *DajImeTima() { return ime_tima; }
	int DajBrojPoena() const { return bodovi; }
	int DajGolRazliku() const { return dati-primljeni; }
	void IspisiPodatke() const
	{
		std::cout<<std::left<<std::setw(20)<< ime_tima;
		std::cout<<std::right<<std::setw(4)<<odigrane<<std::setw(4)<<pobjede<<std::setw(4)<<nerijesene<<std::setw(4)<<porazi<<std::setw(4)<<
		dati<<std::setw(4)<<primljeni<<std::setw(4)<<bodovi<<"\n";
	}
};

class Liga
{
	int broj_timova;
    int max_broj_timova;
	Tim** timovi;
	public:
	explicit Liga(int velicina_lige):max_broj_timova(velicina_lige)
	{
		broj_timova = 0;
		timovi = new Tim*[velicina_lige];
		for(int i=0; i<velicina_lige; i++) timovi[i]=nullptr;
	}
	explicit Liga(std::initializer_list<Tim> lista_timova):max_broj_timova(lista_timova.size()),broj_timova(lista_timova.size())
	{
		timovi = new Tim*[max_broj_timova];
		for(int i=0; i<max_broj_timova; i++) timovi[i] = nullptr;
		try
		{
			auto it = lista_timova.begin();
			for(int i=0; i<max_broj_timova; i++)
			{
				timovi[i] = new Tim(*it++);
			}
		}
		catch(...)
		{
			for(int i=0;i<max_broj_timova;i++) delete timovi[i];
			delete[] timovi;
		}
	}
	~Liga()
	{
		for(int i=0; i<broj_timova; i++) delete timovi[i];
		delete[] timovi;
	}
	Liga(const Liga &l):max_broj_timova(l.max_broj_timova),broj_timova(l.broj_timova)
	{
		timovi=nullptr;
		timovi = new Tim*[max_broj_timova];
		for(int i=0;i<max_broj_timova;i++) timovi[i] = nullptr;
		try
		{
			for(int i=0;i<broj_timova;i++)
			{
				timovi[i] = new Tim(*(l.timovi[i]));
			}
		}
		catch(...)
		{
			for(int i=0;i<broj_timova;i++) delete timovi[i];
			delete[] timovi;
		}
	}
	Liga(Liga &&l):broj_timova(l.broj_timova),max_broj_timova(l.max_broj_timova)
	{
		timovi = l.timovi;
		l.timovi = nullptr;
		l.broj_timova = 0;
	}
	Liga& operator=(const Liga &l)
	{
		if(max_broj_timova != l.max_broj_timova)
			throw std::logic_error("Nesaglasni kapaciteti liga");
		try
		{
			for(int i=0; i<broj_timova; i++) { delete timovi[i]; timovi[i]=nullptr; }
			for(int i=0;i<l.broj_timova;i++)
			{
				timovi[i] = new Tim(*(l.timovi[i]));
			}
			broj_timova = l.broj_timova;
		}
		catch(...)
		{
			for(int i=0;i<l.broj_timova;i++) delete timovi[i];
		}
		return *this;
	}
	Liga& operator=(Liga &&l)
	{
		if(max_broj_timova != l.max_broj_timova)
			throw std::logic_error("Nesaglasni kapaciteti liga");
		for(int i=0; i<broj_timova; i++)
			delete timovi[i];
		delete timovi;
		timovi = l.timovi;
		broj_timova = l.broj_timova;
		l.broj_timova = 0;
		l.timovi = nullptr;
		return *this;
	}
	void DodajNoviTim(const char ime_tima[])
	{
		Tim t(ime_tima);
		if(broj_timova == max_broj_timova) 
			throw std::range_error("Liga popunjena");
		for(int i=0;i<broj_timova;i++)
			if(strcmp(timovi[i]->DajImeTima(), ime_tima) == 0)
				throw std::logic_error("Tim vec postoji");
		timovi[broj_timova++] = new Tim(t); 
	}
	void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2)
	{
		int i1=-1,i2=-1;
		for(int i=0;i<broj_timova;i++)
		{
			if(strcmp((*timovi[i]).DajImeTima(), tim1) == 0) i1 = i;
			if(strcmp((*timovi[i]).DajImeTima(), tim2) == 0) i2 = i;
		}
		if(i1==-1 || i2==-1) 
			throw std::logic_error("Tim nije nadjen");
		if(rezultat_1<0 || rezultat_2<0)
			throw std::range_error("Neispravan broj golova");
		timovi[i1]->ObradiUtakmicu(rezultat_1, rezultat_2);
		timovi[i2]->ObradiUtakmicu(rezultat_2, rezultat_1);
	}
	void IspisiTabelu()
	{
		std::sort(timovi,timovi+broj_timova,[](Tim* t1, Tim* t2){
		return t1->DajBrojPoena() > t2->DajBrojPoena() 
		|| (t1->DajBrojPoena() == t2->DajBrojPoena() && t1->DajGolRazliku() > t2->DajGolRazliku())||
		(t1->DajBrojPoena() == t2->DajBrojPoena() && t1->DajGolRazliku() == t2->DajGolRazliku() && strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0);	
		});
		for(int i=0;i<broj_timova; i++) timovi[i]->IspisiPodatke();
	}
	void ObrisiSve()
	{
		for(int i=0;i<broj_timova;i++) delete timovi[i];
		broj_timova = 0;
	}
	void SacuvajStanje(std::string dat)
	{
		std::ofstream izlaz(dat, std::ios::binary);
		if(!izlaz) throw std::logic_error("Problemi pri upisu u datoteku");
		izlaz.write(reinterpret_cast<char*>(&max_broj_timova), sizeof(max_broj_timova));
		izlaz.write(reinterpret_cast<char*>(&broj_timova), sizeof(broj_timova));
		for(int i=0;i<broj_timova;i++) izlaz.write(reinterpret_cast<char*>(timovi[i]),sizeof(Tim));
		if(!izlaz) throw std::logic_error("Problemi pri upisu u datoteku");
	}
	void AzurirajIzDatoteke(std::string dat)
	{
		std::ifstream ulaz(dat);
		if(!ulaz) throw std::logic_error("Datoteka ne postoji");
		std::string s1,s2;
		for(;;)
		{
			std::getline(ulaz,s1);
			std::getline(ulaz,s2);
			int r1,r2;
			char x;
			ulaz>>r1>>x>>r2;
			if(!ulaz.eof()) ulaz.get();
			if(s1.size()>20 || s2.size()>20 || (!ulaz&&!ulaz.eof()) || x!=':') 
		 		throw std::logic_error("Problemi pri citanju datoteke");
		 	try
		 	{
		 		RegistrirajUtakmicu(s1.c_str(),s2.c_str(),r1,r2);
		 	}
		 	catch(...)
		 	{
		 		throw std::logic_error("Problemi pri citanju datoteke");
		 	}
		 	if(ulaz.eof()) break;
		}
	}
	Liga(std::string dat)
	{
		std::ifstream ulaz(dat, std::ios::binary);
		if(!ulaz) throw std::logic_error("Datoteka ne postoji");
		ulaz.read(reinterpret_cast<char*>(&max_broj_timova), sizeof(max_broj_timova));
		ulaz.read(reinterpret_cast<char*>(&broj_timova), sizeof(broj_timova));
		if(!ulaz) throw std::logic_error("Problemi pri citanju datoteke");
		if(max_broj_timova < broj_timova) throw std::logic_error("Datoteka sadrzi fatalne greske");
		timovi = new Tim*[broj_timova];
		for(int i=0;i<broj_timova;i++)
		{
			try
			{
				timovi[i] = new Tim("FK Igman Konjic");
				ulaz.read(reinterpret_cast<char*>(timovi[i]), sizeof(Tim));
			}
			catch(...)
			{
				for(int j=0;j<i;j++) delete timovi[j];
				delete[] timovi;
				throw std::bad_alloc();
			}
			if(!ulaz) throw std::logic_error("Problemi pri citanju datoteke");
		}
	}
};

int main ()
{
try{	
Liga l2("LIGA.DAT");
  
l2.DodajNoviTim("NK Siroki Brijeg");
l2.DodajNoviTim("NK Vitez");

l2.RegistrirajUtakmicu("NK Siroki Brijeg", "NK Vitez",1,1);

std::cout << "Djelimicna Liga za Ispadanje: " << std::endl;
l2.IspisiTabelu();

std::cout << std::endl << "Kopija Lige za Prvaka: " << std::endl;
l2.IspisiTabelu();
l2.SacuvajStanje("LIGA.DAT");
}
catch(std::logic_error e)
{
	std::cout << e.what();
}
	return 0;
}