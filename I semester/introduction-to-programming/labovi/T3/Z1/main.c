#include <stdio.h>

int main() {
	int broj, suma=0;
	while(suma<=100) {
		scanf("%d", &broj);
		suma+=broj;
	}
	printf("%d", suma);
	return 0;
}
