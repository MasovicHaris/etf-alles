//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
 struct Matrica 
     {
     int br_redova, br_kolona;
     TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
     };
     
template <typename TipElemenata>
 void UnistiMatricu(Matrica<TipElemenata> &mat) 
 {
 if(!mat.elementi) return;
 for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
 delete[] mat.elementi;
 mat.elementi = nullptr;
 }
 
template <typename TipElemenata>
 Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona) 
 {
     Matrica<TipElemenata> mat;
     mat.br_redova = br_redova; mat.br_kolona = br_kolona;
     mat.elementi = new TipElemenata*[br_redova]{};
         try 
         {
             for(int i = 0; i < br_redova; i++)
             mat.elementi[i] = new TipElemenata[br_kolona];
         }
         catch(...) 
         {
             UnistiMatricu(mat);
             throw;
         }
        return mat;
 }
 
template <typename TipElemenata>
 void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat) 
 {
    for(int i = 0; i < mat.br_redova; i++)
    {
         for(int j = 0; j < mat.br_kolona; j++) 
         {
             std::cout << ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
             std::cin >> mat.elementi[i][j];
         }
    }
 }
 
template <typename TipElemenata>
 void IspisiMatricu(Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false) 
 {
         for(int i = 0; i < mat.br_redova; i++) 
         {
             for(int j = 0; j < mat.br_kolona; j++)
             std::cout << std::setw(sirina_ispisa) <<std::setprecision(preciznost)<< mat.elementi[i][j];
             std::cout << std::endl;
         }
     if(treba_brisati)
     {
         UnistiMatricu(mat);
     }
 }
 
template <typename TipElemenata>
 Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2) 
 {
     if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
     throw std::domain_error("Matrice nemaju jednake dimenzije!");
     auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
     for(int i = 0; i < m1.br_redova; i++)
     for(int j = 0; j < m1.br_kolona; j++)
     m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
     return m3;
 }
 
template<typename TipElemenata>
 Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
 {
     
     if(m2.br_redova!=m1.br_kolona) throw std::domain_error("Matrice nisu saglasne za mnozenje");
     
     auto matra=StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona);
     
     for(int i=0 ; i<m1.br_redova; i++)
     {
         for(int j=0; j<m2.br_kolona; j++)
         {
             TipElemenata suma(0);
             for(int k=0; k<m2.br_redova; k++)
             {
                 suma+=m1.elementi[i][k]*m2.elementi[k][j];
             }
             matra.elementi[i][j]=suma;
         }
     }
     return matra;
 }
 
 template<typename TipElemenata>
    Matrica<TipElemenata> PomnoziSaSkalarom(const Matrica<TipElemenata> &mat, double p)
    {
       auto m=StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
        for(int i=0 ; i<mat.br_redova; i++)
        {
            for(int j=0 ; j<mat.br_kolona; j++)
            {
                m.elementi[i][j]=mat.elementi[i][j]*p;
            }
        }
        return m;
    }
    
template<typename TipElemenata>
void Saberi(Matrica<TipElemenata> &m1, Matrica<TipElemenata> &m2)
{
 for(int i=0; i<m1.br_redova; i++)
  for(int j=0; j<m1.br_kolona; j++)
    m1.elementi[i][j]+=m2.elementi[i][j];
}

template<typename TipElemenata>
 void proizv(Matrica<TipElemenata> &em1, Matrica<TipElemenata> &em2)
 {
   auto em3(StvoriMatricu<TipElemenata>(em1.br_redova, em1.br_kolona));
    for(int i=0; i<em1.br_redova; i++)
    {
       for(int j=0; j<em1.br_kolona; j++)
       {
         TipElemenata suma(0);
          for(int k=0; k<em1.br_redova; k++)
          {
           suma+=em1.elementi[i][k]*em2.elementi[k][j];
          }
          em3.elementi[i][j]=suma;
       }
    }
    for(int i=0; i<em1.br_redova; i++) for(int j=0; j<em2.br_kolona; j++) em1.elementi[i][j]=em3.elementi[i][j];
    UnistiMatricu(em3);
 }
    
template<typename TipElemenata>
 Matrica<TipElemenata> MatricniPolinom(Matrica<TipElemenata> mat, std::vector<double> veka)
 {
     if(mat.br_kolona!=mat.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
     int m=mat.br_redova;
     int n=mat.br_kolona;
        Matrica<TipElemenata> matra(StvoriMatricu<TipElemenata>(m, n));

        for(int i=0; i<matra.br_redova; i++)
        {
            for(int j=0; j<matra.br_kolona; j++)
            {
                if(i==j) matra.elementi[i][j]=1;
                else 
                {
                matra.elementi[i][j]=0;
                }
            }
        }  //matra je jedinicna matrica
      
       if(veka.size()==0)
       {
        auto bez=PomnoziSaSkalarom(matra,0);
        for(int i=0; i<m; i++) for(int j=0; j<m; j++) matra.elementi[i][j]=bez.elementi[i][j];
        UnistiMatricu(bez);
        return matra;
       }
       
       //PomnoziSaSkalarom(matra, veka.at(0));   //pomnozimo je sa prvim skalarom u vektoru
       Matrica<TipElemenata> kopija(StvoriMatricu<TipElemenata>(m,n));
       for(int i=0; i<m; i++) for(int j=0; j<n; j++) kopija.elementi[i][j]=mat.elementi[i][j];    //kopija poslane matrice, mora se napravit zbog mnozenja sa pocetnom matricom
       auto es=PomnoziSaSkalarom(matra,veka.at(0));
       for(int i=0; i<m; i++) for(int j=0; j<n; j++) matra.elementi[i][j]=es.elementi[i][j];
       
       UnistiMatricu(es);
       
       for(int i=1; i<veka.size(); i++)
       {
        if(veka.at(i)!=0)
        {
         auto skal=PomnoziSaSkalarom(kopija,veka.at(i));
         //PomnoziSaSkalarom(kopija, veka.at(i));
         Saberi(matra,skal);
         //PomnoziSaSkalarom(kopija,1./veka.at(i));
         UnistiMatricu(skal);
        }
        auto prd=ProduktMatrica(kopija,mat);
        for(int k=0; k<m; k++)
        {
          for(int l=0; l<m; l++)
          {
           kopija.elementi[k][l]=prd.elementi[k][l];
          }
        }
        UnistiMatricu(prd);
       }
       
       UnistiMatricu(kopija);
       return matra;

 }

int main() {
 Matrica<double> a, z;// AUTOMATSKA INICIJALIZACIJA!!!
 int m, r;
 double x;
 std::cout << "Unesite dimenziju kvadratne matrice: ";
 std::cin >>m;
 std::vector<double> v;
 try {
 a = StvoriMatricu<double>(m, m);
 std::cout<<"Unesite elemente matrice A:\n";
 UnesiMatricu('A', a);
 std::cout<<"Unesite red polinoma: ";   
 std::cin>>r;
 std::cout<<"Unesite koeficijente polinoma: ";
     for(int i=0; i<r+1; i++)
     {
         std::cin>>x;
         v.push_back(x);
     }
 z=MatricniPolinom<double>(a,v);
 IspisiMatricu<double>(z, 10, 6, false);
 }
 catch(std::bad_alloc) {
 std::cout << "Nema dovoljno memorije!\n";
 }
 UnistiMatricu(a); UnistiMatricu(z);
 return 0;
}
