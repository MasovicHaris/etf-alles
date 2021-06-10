// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#define epsilon 0.0001
int main() {
		
		double mat[101][101]={0};
		int m, n, i, j, dobar=0, f, l;
		double prosjek, clanovi, sumareda, preda, sumakolone, pkolone, t;
		printf("Unesite vrijednosti M i N: ");
		do
		{
			scanf("%d %d", &m, &n);
			if((m<1 || m>100) || (n<1 || n>100))
			{
				dobar=0;
				printf("Vrijednosti su van opsega!");
				printf("\nUnesite vrijednosti M i N: ");
			}
			else 
			{
			break;
			}
			
		}while(dobar==0);
		
			clanovi=m*n;
		
		printf("Unesite clanove matrice: \n");
		
		for(i=0; i<m; i++)
			{
				for(j=0; j<n; j++)
				{
					scanf("%lf", &mat[i][j]);
				}
			
			}
			
			double suma=0;
			for(i=0; i<m; i++)
			{
				
				for(j=0; j<n; j++)
				{
					suma=suma+mat[i][j];
				}
			}
			
			prosjek=suma/clanovi;
			
			
			//redovi
				for(i=0; i<m; i++)
					{
						sumareda=0;
						for(j=0; j<n; j++)
						{
							sumareda=sumareda+mat[i][j];
						}
							preda=sumareda/n;
						if(preda>prosjek+epsilon)
						{
							for(f=i; f<m; f++)
							for(j=0; j<n; j++)
							{
								t=mat[f][j];
								mat[f][j]=mat[f+1][j];
								mat[f+1][j]=t;
							}
							
							m--;
							i--;
						}
						
					
						
					}
					
					//kolone
				for(j=0; j<n; j++)
				{
					sumakolone=0;
					for(i=0; i<m; i++)
					{
					
						sumakolone=sumakolone+mat[i][j];
					}

						pkolone=sumakolone/m;
							
							if(pkolone>prosjek+epsilon)
							{
								for(l=j; l<n; l++)
								for(i=0; i<m; i++)
								{
									t=mat[i][l];
									mat[i][l]=mat[i][l+1];
									mat[i][l+1]=t;
								}
								j--;
								n--;
							}
						
					}
				
					
					
					
					printf("Nakon izbacivanja matrica glasi:\n");
					
					for(i=0; i<m; i++)
					{
						for(j=0; j<n; j++)
						{
							
							printf("%6.1f", mat[i][j]);
							
						}
						printf("\n");
					}
					
			
			return 0;
}
