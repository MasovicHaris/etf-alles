/* TP 2016/2017 (Tutorijal 4, Zadatak 5)

   Autotestovi by Eldar Kurtic, sva pitanja, sugestije i prijave gresaka javite na 
   mail ekurtic3@etf.unsa.ba
   
   NAPOMENA: testovi ce biti konacni TEK pred pocetak tutorijala. Zbog toga pokrenite
   testove za SVE zadatke na tutorijalu, da se ne bi desila situacija da neko uradi
   zadatak ranije i prolazi mu npr. 5/5 testova a naknadno dodano jos 2 testa koja mu
   padaju!
   
*/
#include <iostream>
#include <vector>

template <typename tip>
std::vector<tip> Presjek (const std::vector<tip> &v1, const std::vector <tip> &v2){
   
   std::vector<tip> pomocni;
   auto i = v1.size();
   auto j = v2.size();
   for(i=0; i < v1.size(); i++){
      
      for(j=0; j < v2.size(); j++){
         
         if(v1[i]==v2[j]){
            int br=0;
            for(tip x : pomocni) if(x == v1[i]) br++; // imal ga?
            if(br == 0) pomocni.push_back(v1[i]);
         }
      }
   }
   return pomocni;
}
int main ()
{
   int broj;
   std::vector <double> d1, d2, d3;
   std::vector <std::string> s1, s2, s3;
   double element;
   
   // realni
   std::cout << "Test za realne brojeve..." << std::endl;
   std::cout << "Unesite broj elemenata prvog vektora: ";
   std::cin >> broj;
   std::cout << "Unesite elemente prvog vektora: ";
   for(int i=0; i<broj; i++){
      std::cin >> element;
      d1.push_back(element);
   }
   std::cout << "Unesite broj elemenata drugog vektora: ";
   std::cin >> broj;
   std::cout << "Unesite elemente drugog vektora: ";
   for(int i=0; i<broj; i++){
      std::cin >> element;
      d2.push_back(element);
   }
   d3 = Presjek(d1, d2);
   std::cout << "Zajednicki elementi su: ";
   for(auto element : d3) std::cout << element << " ";
   
   std::cout << std::endl;
   std::string elementx;
   // string
   std::cout << std::endl << "Test za stringove..." << std::endl;
   std::cout << "Unesite broj elemenata prvog vektora: ";
   std::cin >> broj;
   std::cin.ignore(10000, '\n');
   std::cout << "Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";   
   for(unsigned int i=0; i< broj; i++)
   { std::getline(std::cin, elementx); s1.push_back(elementx); }
   
   std::cout << "Unesite broj elemenata drugog vektora: ";
   std::cin >> broj;
   std::cin.ignore(10000, '\n');
   std::cout << "Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
   for(unsigned int i=0; i< broj; i++)
   { std::getline(std::cin, elementx); s2.push_back(elementx); }
   
   s3 = Presjek(s1, s2);
   std::cout << "Zajednicki elementi su: " << std::endl;
   for(auto elementx : s3) std::cout << elementx << std::endl;
	return 0;
}