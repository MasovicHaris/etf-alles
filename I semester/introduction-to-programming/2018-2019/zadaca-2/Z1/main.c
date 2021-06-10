// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int main() {
	
		int i,j,n, dobar=0, k=0, l=0;
		
		
		do{
		printf("Unesite broj N: ");
		scanf("%d", &n);
		if(n<=0)
		{
		printf("N nije ispravno!\n");
			continue;
		}
		if(n%4!=1)
		{
			printf("N nije ispravno!\n");
			continue;
		}
		if(n%4==1)
			dobar=1;
		
		if(dobar==1)
		break;
		}while(n>0);
		printf("\n");
		
		for(i=0; i<n; i++)
			{
				k++;
				if(i>2)
				l++;
				
				for(j=0; j<n; j++)
				{
					if((j==(n/2)+1) && (i==(n/2)+1) || (i==2 && j==n-2) || (i==1 && j==0))
					printf(" ");
					
					
					else if(i==n-1)
					{
						printf("*");
					}
					
					else if((i<3 && j%2==1 && j==n-1) || (i%2==0 && i<3))
					{
						printf("*");
					}
					
					
					else if(j<l && i<=(n/2)+1)
					{
						if(j%2==0)
						printf("*");
						else
						printf(" ");
					}
					
					
					else if(j<=n-k && i>=(n/2)+1)
					{
						if(j%2==0)
						printf("*");
						else
						printf(" ");
					}
					
					
					else if((j<=n-1 && j>n-k) && i<=(n/2)-1)
					{
						if(j%2!=0)
						printf(" ");
						else
						printf("*");
					}
					
					
					else if(i>(n/2)-1 && (j<=n-1 && j>=k-1))
					{
						if(j%2!=0)
						printf(" ");
						else
						printf("*");
					}
					
					else if(i%2!=0)
					printf(" ");
					else
					printf("*");
				
					
					
					
				}
				printf("\n");
			}
}
	
		
		
		
	
	
	
	
	
