/* TP 2016/2017 (Tutorijal 4, Zadatak 4)

   Autotestovi by Eldar Kurtic, sva pitanja, sugestije i prijave gresaka javite na 
   mail ekurtic3@etf.unsa.ba
   
   NAPOMENA: testovi ce biti konacni TEK pred pocetak tutorijala. Zbog toga pokrenite
   testove za SVE zadatke na tutorijalu, da se ne bi desila situacija da neko uradi
   zadatak ranije i prolazi mu npr. 5/5 testova a naknadno dodano jos 2 testa koja mu
   padaju!
   
*/
#include <iostream>
#include <string>

template <typename tip>
void UnosBroja(std::string prvi, std::string drugi, tip &broj){
   for(;;){
      std::cout << prvi;
      
      while(!(std::cin >> broj)){
         std::cin.clear();
         std::cin.ignore(10000, '\n');
         std::cout << drugi << std::endl;
         std::cout << prvi;
      }
      if(std::cin.peek()!='\n' || broj - tip(broj)!=0){
         std::cin.clear();
         std::cin.ignore(10000,'\n');
         std::cout << drugi << std::endl;
      }
      else break;
   } 
}



int main ()
{
   double x; 
   bool flag=true;
   UnosBroja("Unesite bazu: \n", "Neispravan unos, pokusajte ponovo...", x);
   int n;
   std::cout << std::endl;
   UnosBroja("Unesite cjelobrojni eksponent: \n","Neispravan unos, pokusajte ponovo...", n);
   
   std::cout << std::endl;
   
   std::cout << x << " na " << n << " iznosi ";
   double suma(x);
   if(n<0) { flag=false; n*=-1; }
   for(int i=0; i< n-1; i++) suma *= x;
   if(!flag) std::cout << 1/suma;
   else std::cout << suma;
	return 0;
}