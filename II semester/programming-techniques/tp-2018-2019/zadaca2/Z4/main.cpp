//solved by @who.so (hhamzic1@etf.unsa.ba)
#include <stdexcept>
#include <iostream>
#include <new>

long long int rezultat(long long int j, long long int i)
{
    
    
    if(j==0 && i==0)
    {
        return 1;
    }
    
    if((j==0 && i!=0) || (j>i))
    {
        return 0;
    }
    
    return rezultat(j-1,i-1)+j*rezultat(j,i-1);
}

long long int **StirlingoviBrojeviV1(long long int x)
{
    if(x<0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int **pok=nullptr;
    try{
             pok=new long long int*[x+1]{};
             try{
                 for(long long int i=0; i<x+1; i++)
                    {
                        pok[i]=new long long int[i+1];
                    }
                }
                 catch(std::bad_alloc)
                 {
                    for(int i=0; i<x+1; i++)
                     {
                         delete[] pok[i];
                     }
                     throw;
                 }
      }
      catch(...)
      {
          delete[] pok;
          pok=nullptr;
          throw std::range_error("Parametar prevelik za raspolozivu memoriju");
      }
    
    for(long long int i=0; i<x+1; i++)
    {
        for(long long int j=0; j<i+1; j++)
        {
            pok[i][j]=rezultat(j, i);
    
        }
    }
    return pok;
}

long long int **StirlingoviBrojeviV2(int x)
{
    if(x<0) throw std::domain_error("Parametar ne smije biti negativan");
    long long int **pok=nullptr;
    auto brelemenata=((x+1)*(x+2))/2;
    try
    {
            pok=new long long int*[x+1]{};
            try
            {
            pok[0]=new long long int[brelemenata];
            }
            catch(std::bad_alloc)
            {
                delete[] pok[0];
                pok=nullptr;
                throw;
            }
            for(long long int i=1; i<x+1; i++)
            {
                pok[i]=pok[i-1]+i;
            }
    }
    catch(...)
    {
        delete[] pok;
        pok=nullptr;
        throw std::range_error("Parametar prevelik za raspolozivu memoriju");
    }
    
    for(long long int i=0; i<x+1; i++)
    {
        for(long long int j=0; j<i+1; j++)
        {
            pok[i][j]=rezultat(j,i);
        
        }
        
    }
    
    return pok;
}

int main ()
{
	std::cout<<"Unesite dimenzije grbave matrice: ";
	int n;
	std::cin>>n;
    try
    {
    	auto a=StirlingoviBrojeviV1(n);
    	for(long long int i=0; i<n+1; i++)
    	{
    	    for(long long int j=0; j<i+1; j++)
    	    {
    	        std::cout<<a[i][j]<<" ";
    	    }
    	    std::cout<<"\n";
    	}
    	
    	for(long long int i=0; i<n+1; i++)
    	{
    	    delete[] a[i];
    	}
    	delete[] a;
    	a=nullptr;
    }
    catch(std::domain_error a)
    {
        std::cout<<a.what();
    }
    catch(std::range_error e)
    {
        std::cout<<e.what();
    }
	std::cout<<std::endl;
	
	try
	{
    	auto b=StirlingoviBrojeviV2(n);
    	for(long long int i=0; i<n+1; i++)
    	{
    	    for(long long int j=0; j<i+1; j++)
    	    {
    	        std::cout<<b[i][j]<<" ";
    	    }
    	    std::cout<<"\n";
    	}
    	
    	delete[] b[0];
    	delete[] b;
    	b=nullptr;
	}
	catch(std::domain_error a)
	{
	    std::cout<<a.what();
	}
	catch(std::range_error e)
	{
	    std::cout<<e.what();
	}
	return 0;
}