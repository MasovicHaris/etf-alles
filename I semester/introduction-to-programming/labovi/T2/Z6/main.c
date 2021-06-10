#include <stdio.h>

int main() {
	float a, b, c, d, max, min;
            printf("Unesite brojeve a,b,c,d: ");
            scanf("%f %f %f %f", &a, &b, &c, &d);
				
			
            if(c<b && d<a){ printf("Skupovi se ne sijeku."); return 0; }
            if((c<b)|| (d<a)) {
            if(a>c) min=a; else min=c;
            if(d<b) max=d; else max=b;
            printf("Rezultantni interval je [%g,%g].", min, max);
            }
            else printf("Skupovi se ne sijeku."); 

	return 0;
}
