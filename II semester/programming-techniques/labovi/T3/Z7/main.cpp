#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

/* TP 2016/2017: Tutorijal 3, Zadatak 7

   Autotestove pisao Haris Hasic. Sva pitanja
   sugestije i prijave gresaka mozete slati na
   mail: hhasic2@etf.unsa.ba

*/

typedef std::vector<std::vector<int>> Matrica;

Matrica KreirajMatricu(int br_redova, int br_kolona)
{
   return Matrica(br_redova, std::vector<int>(br_kolona));
}

int NajvecaSirina(Matrica m)
{

   int Maxduzina=0;
   for(int i=0; i<m.size(); i++) {
      for(int j=0; j<m[i].size(); j++) {
         int x = m[i][j];
         int duzina=0;
         if(x<0) {
            duzina++;
            x*=-1;
         }
         while(x!=0) {
            duzina++;
            x/=10;
         }
         if(duzina > Maxduzina) Maxduzina = duzina;
      }
   }

   return Maxduzina;  
}  

void IspisiMatricu(Matrica m, int duzina)
{
   for(int i=0; i <m.size(); i++) {
      for(int j=0; j< m[i].size(); j++)
         std::cout << std::setw(duzina+1) << m[i][j];

      std::cout << std::endl;
   }
}

Matrica PascalovTrougao(int n)
{
   if(n < 0) throw std::domain_error("Broj redova ne smije biti negativan");
   if(n == 0) { Matrica m; return m; }
   Matrica m(KreirajMatricu(n, 0));
   for(int i=0; i<m.size(); i++) {
      m[i].resize((unsigned int)(i+1));
      for(int j=0; j< m[i].size(); j++) {
         if(j==0 || i==j) m[i][j]=1;
         else m[i][j] = m[i-1][j-1] + m[i-1][j];
      }
   }
   return m;
}

int main (){
   
   try {
      int n;
      std::cout << "Unesite broj redova: ";
      std::cin >> n;
      Matrica k;
      k = PascalovTrougao(n);
      int duzina = NajvecaSirina(k);
      std::cout << std::endl;
      IspisiMatricu(k, duzina);
   } catch(std::domain_error izuzetak) {
      std::cout << izuzetak.what() << std::endl;
   } 

   return 0;
}