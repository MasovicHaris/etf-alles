#include <iostream>
#include <string>
#include <stdexcept>

/* TP 2016/2017: Tutorijal 3, Zadatak 8

   Autotestove pisao Haris Hasic. Sva pitanja
   sugestije i prijave gresaka mozete slati na
   mail: hhasic2@etf.unsa.ba

*/

std::string IzdvojiRijec(std::string s, int n)
{
   if(n<=0) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci! ");
   int brojRijeci=0;
   std::string pomocni;
   int i(0);
   bool DesiloSe(true);
   while(i<s.length()) {
      if(s[i]!=' ') {
         brojRijeci++;
         if(brojRijeci == n) {
            DesiloSe = false;
            while(s[i]!=' ' && i<s.length()) {
               pomocni.push_back(s[i]);
               ++i;
            } 
            break;

         } else while(s[i]!=' ' && i<s.length()) i++;
      }

      if(i == s.length()) --i;
      i++;
   }
   if(DesiloSe) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci! ");
   return pomocni;
}
int main ()
{
   try {

      int n;
      std::cout << "Unesite redni broj rijeci: ";
      std::cin >> n;
      std::cin.ignore(10000, '\n');

      std::cout << "Unesite recenicu: ";
      std::string s;
      std::getline(std::cin, s);
      std::cout << "Rijec na poziciji " << n << " je " << IzdvojiRijec(s, n);

   } catch(std::range_error izuzetak) {
      std::cout << izuzetak.what() << std::endl;
   }
   return 0;
}