#include <stdio.h>

int main() {
	int d1=0, d2=0;
            printf("Unesite stranice pravougaonika a,b: ");
            scanf("%d,%d", &d1, &d2);
            
    int i=0, j=0;
    		
    		for(i=0;i<d2;i++)
    		{
    			for(j=0;j<d1;j++)
    			{
    				if( (i==0 && j==0) || (i==0 && j==(d1-1)) || (j==0 && i==(d2-1)) || (j==(d1-1) && i==(d2-1)) ) printf("+");
    				else if(i==0 || i==(d2-1)) printf("-");
    				else if(j==0 || j==(d1-1)) printf("|");
    			 	else printf(" ");
    			}
    			printf("\n");
    		}
	return 0;
}
