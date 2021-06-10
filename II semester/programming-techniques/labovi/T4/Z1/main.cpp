/* TP 2016/2017 (Tutorijal 4, Zadatak 1)

   Autotestovi by Eldar Kurtic, sva pitanja, sugestije i prijave gresaka javite na 
   mail ekurtic3@etf.unsa.ba
   
   NAPOMENA: testovi ce biti konacni TEK pred pocetak tutorijala. Zbog toga pokrenite
   testove za SVE zadatke na tutorijalu, da se ne bi desila situacija da neko uradi
   zadatak ranije i prolazi mu npr. 5/5 testova a naknadno dodano jos 2 testa koja mu
   padaju!
   
*/
#include <iostream>
#include <limits>
#include <cmath>

int Cifre(long long int n, int &c_min, int &c_max){
   
   auto pomocna(n);
   int brojac=0;
   int min(9), max(0);
   
   if(pomocna==0) {
      c_min=0; c_max=0;
      return brojac+1;
   }
   
   while(pomocna!=0){
      int zadnja = std::fabs(pomocna % 10);
      if(zadnja < min) min = zadnja;
      if(zadnja > max) max = zadnja;
      brojac++;
      pomocna/=10;
   }
   c_min = min;
   c_max = max;
   return brojac;
}


int main ()
{
   int a, b;
   long long broj;
   std::cout << "Unesite broj: "; 
   std::cin >> broj;
   
   int cifre = Cifre(broj, a, b);
   std::cout << "Broj " << broj << " ima " << cifre << " cifara, najveca je " << b  << " a najmanja " << a << ".";
	return 0;
}