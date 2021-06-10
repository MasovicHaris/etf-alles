// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int main() {
			
			int n, i, j, iks, b=0;
			int array[100];
			int arraydva[100]={0};
			
			printf("Unesite N: ");
			scanf("%d", &n);
			
			for(i=0; i<n; i++)
			{
				scanf("%d", &array[i]);
			}
			i=0;
			while(i<1337)
			{
				b=1;
				for(j=0; j<n; j++)
				{
				arraydva[j]=array[j]^i;
				}
				
				for(j=0; j<n-1; j++)
				{
					if(arraydva[j]>arraydva[j+1])
					{ 
						b=0;
						iks=-1;
						break;
					}
				}
				
				if(b==1)
				{
					iks=i;
					break;
				}
				
				i++;
			
				
				
			}
			printf("X=%d", iks );
		
}
