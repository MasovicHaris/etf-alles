/* TP 2016/2017 (Tutorijal 4, Zadatak 2)

   Autotestovi by Eldar Kurtic, sva pitanja, sugestije i prijave gresaka javite na 
   mail ekurtic3@etf.unsa.ba
   
   NAPOMENA: testovi ce biti konacni TEK pred pocetak tutorijala. Zbog toga pokrenite
   testove za SVE zadatke na tutorijalu, da se ne bi desila situacija da neko uradi
   zadatak ranije i prolazi mu npr. 5/5 testova a naknadno dodano jos 2 testa koja mu
   padaju!
   
*/ 
#include <iostream>
#include <string>

void IzvrniString(std::string &s){
   auto i = s.size();
   for(i=0; i < s.size()/2; i++){
      char a = s[i];
      s[i] = s[s.size()-i-1];
      s[s.size()-i-1] = a;
   }
}

int main ()
{
   std::string s;
   std::cout << "Unesi string: ";
   std::getline(std::cin, s);
   
   IzvrniString(s);
   std::cout << "Izvrnuti string je: " << s;
	return 0;
}