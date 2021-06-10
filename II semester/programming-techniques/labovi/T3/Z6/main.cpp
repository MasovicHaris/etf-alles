#include <iostream>
#include <iomanip>
#include <vector>

/* TP 2016/2017: Tutorijal 3, Zadatak 6

   Autotestove pisao Haris Hasic. Sva pitanja
   sugestije i prijave gresaka mozete slati na
   mail: hhasic2@etf.unsa.ba

*/
typedef std::vector<std::vector<int>> Matrica;

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
   for(int i=0; i< m.size(); i++) {
      for(int j=0; j<m[i].size(); j++)
         std::cout << std::setw(duzina+1) << m[i][j];
      std::cout << std::endl;
   }
}

Matrica KreirajMatricu(int br_redova, int br_kolona)
{
   return Matrica(br_redova, std::vector<int>(br_kolona));
}

Matrica KroneckerovProizvod(const std::vector <int> v1, const std::vector <int> v2)
{
   auto m(KreirajMatricu(int(v1.size()), int(v2.size())));
   for(int i=0; i<v1.size(); i++) {
      for(int j=0; j<v2.size(); j++) {
         m[i][j]= v1[i]*v2[j];
      }
   }
   return m;
}


int main ()
{   
   int n1, n2;
   int p;
   std::vector <int> v1;
   std::vector <int> v2;
   std::cout << "Unesite broj elemenata prvog vektora: ";
   std::cin >> n1;
   std::cout << "Unesite elemente prvog vektora: ";
   for(int i=0; i<n1; i++) {
      std::cin >> p;
      v1.push_back(p);
   }
   std::cout << "Unesite broj elemenata drugog vektora: ";
   std::cin >> n2;
   std::cout << "Unesite elemente drugog vektora: ";
   for(int i=0; i<n2; ++i) {
      std::cin >> p;
      v2.push_back(p);
   }

   std::cout << std::endl;
   Matrica k;
   k = KroneckerovProizvod(v1, v2);
   int duzina = NajvecaSirina(k);
   IspisiMatricu(k, duzina);  
   
   

   

   return 0;
}