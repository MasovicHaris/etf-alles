#include <stdio.h>

void zamijeni(int *p1, int *p2) {
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
int main() {
	int br1=5, br2=3;
	
	printf("Prije zamjene: %d %d\n", br1, br2);
	zamijeni(&br1, &br2);
	printf("Poslije zamjene: %d %d\n", br1, br2);
	return 0;
}