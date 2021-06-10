#include <stdio.h>
#include <math.h>

int main() {
	printf("Tutorijal 1, Zadatak \n");
	int x1, y1, z1;
	int x2, y2, z2;
	float rastojanje=0;
	printf("Unesi prvu tacku: ");
	scanf("%d %d %d", &x1, &y1, &z1);
	printf("Unesi drugu tacku: ");
	scanf("%d %d %d", &x2, &y2, &z2);
	
	rastojanje = sqrt(pow(x2-x1,2) + pow(y2-y1, 2) + pow(z2-z1,2));
	printf("%.2f", rastojanje);
	
	
	
	
	return 0;
}
