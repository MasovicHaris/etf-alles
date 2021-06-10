#include <iostream>
#include <vector>

/* TP 2016/2017: Tutorijal 3, Zadatak 1

   Autotestove pisao Haris Hasic. Sva pitanja
   sugestije i prijave gresaka mozete slati na
   mail: hhasic2@etf.unsa.ba

*/

std::vector <int> IzdvojiElemente(const std::vector <int> v, bool Vrijednost)
{

   std::vector <int> Novi;
   for(int x : v) {
      bool manji = false;
      if(x<0) {
         manji = true;
         x*=-1;
      }
      int suma=0;
      int pamti = x;
      while (pamti!=0) {
         int zadnjaCifra = pamti % 10;
         suma += zadnjaCifra;
         pamti /=10;
      }
      if(manji) x*=-1;
      if(suma%2==0 && Vrijednost) Novi.push_back(x); // parna suma
      if(suma%2!=0 && !Vrijednost) Novi.push_back(x); // neparna suma
   }
   return Novi;
}

int main ()
{
   int n;
   std::cout << "Koliko zelite unijeti elemenata: ";
   std::cin >> n;

   if(n<=0) {
      std::cout << "Broj elemenata mora biti veci od 0!";
      return 0;
   }

   int element;
   std::vector <int> a;
   std::vector <int> b;
   std::vector <int> c;
   std::cout << "Unesite elemente: ";

   for(int i=0; i<n; ++i) {
      std::cin >> element;
      a.push_back(element);
   }

   b = IzdvojiElemente(a, true);
   c = IzdvojiElemente(a, false);

   for(int x : b) std::cout << x << " ";
   std::cout << std::endl;
   for(int x : c) std::cout << x << " ";

   return 0;
}