/* TP 2016/2017 (Tutorijal 4, Zadatak 3)

   Autotestovi by Eldar Kurtic, sva pitanja, sugestije i prijave gresaka javite na
   mail ekurtic3@etf.unsa.ba

   NAPOMENA: testovi ce biti konacni TEK pred pocetak tutorijala. Zbog toga pokrenite
   testove za SVE zadatke na tutorijalu, da se ne bi desila situacija da neko uradi
   zadatak ranije i prolazi mu npr. 5/5 testova a naknadno dodano jos 2 testa koja mu
   padaju!

*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cctype>

typedef std::vector<std::string> VektorStringova;

bool ImaLiuVektoru(std::string &s, VektorStringova &w)
{
   auto i = w.size();
   for(i=0; i< w.size(); i++) {
      if(w[i]==s) return false;
   }
   return true;
}

void ZadrziDuplikate(VektorStringova &v)
{
   VektorStringova pomocni;
   auto i = v.size();
   auto j = i;
   for(i =0; i<v.size(); i++) {
      for(j=i+1; j< v.size(); j++) {
         if(v[i]==v[j] && ImaLiuVektoru(v[i], pomocni)) pomocni.push_back(v[i]);
      }
   }
   v = std::move(pomocni);
}


void IzdvojiKrajnjeRijeci(VektorStringova &v, std::string &prvi, std::string &drugi)
{
   if(v.size()==0) return;

   std::string min1(v[0]), max1(v[0]);
   auto i = v.size();

   auto j = min1.size();
   auto k = max1.size();

   for(i=0; i < v.size(); i++) {

      for(j=0; j < min1.size(); j++) {
         while(j < v[i].size() && j < min1.size() && std::toupper(v[i][j]) == std::toupper(min1[j])) j++;
         break;
      }
      if(j == v[i].size() && j < min1.size()) min1 = v[i];
      if(j < v[i].size() &&  std::toupper(v[i][j]) < std::toupper(min1[j])) min1 = v[i];

      for(k=0; k < min1.size(); k++) {
         while(k < v[i].size() && k < min1.size() && std::toupper(v[i][k]) == std::toupper(max1[k])) k++;
         break;
      }
      if(k == v[i].size() && k < max1.size()) max1 = v[i];
      if(k < v[i].size() &&  std::toupper(v[i][k]) > std::toupper(max1[k])) max1 = v[i];
   }

   prvi = min1;
   drugi = max1;
}

int main ()
{
   int broj;
   std::string a, b;
   VektorStringova vektor;
   std::cout << "Koliko zelite unijeti rijeci: ";
   std::cin >> broj;
   std::cin.ignore(10000, '\n');
   std::string pomocni;
   std::cout << "Unesite rijeci: ";
   for(int i=0; i < broj; i++) {
      std::cin >> pomocni;
      vektor.push_back(pomocni);
   }

   IzdvojiKrajnjeRijeci(vektor, a, b);
   ZadrziDuplikate(vektor);
   std::cout << "Prva rijec po abecednom poretku je: " << a << std::endl;
   std::cout << "Posljednja rijec po abecednom poretku je: " << b << std::endl;
   std::cout << "Rijeci koje se ponavljaju su: ";
   for(int i=0; i < vektor.size(); i++) std::cout << vektor[i] << " ";
   return 0;
}