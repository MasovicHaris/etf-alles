#include <stdio.h>
#include <stdlib.h>

struct Vrijeme {
		int sati;
		int minute;
		int sekunde;
	};
	
struct Vrijeme unos_vremena(){
	struct Vrijeme v;
	
	scanf("%d %d %d", &v.sati, &v.minute, &v.sekunde);
	return v;
	
}

int proteklo( struct Vrijeme v1, struct Vrijeme v2){
	
	int a=0, b=0;
	
	a += v1.sati * 3600;
	a += v1.minute * 60;
	a += v1.sekunde;
	
	b += v2.sati * 3600;
	b += v2.minute * 60;
	b += v2.sekunde;
	
	return abs(a-b);
	
	
}

	
int main() {
	struct Vrijeme v1;
	struct Vrijeme v2;
	printf("Unesite prvo vrijeme (h m s): ");
	v1 = unos_vremena();
	printf("\nUnesite drugo vrijeme (h m s): ");
	v2 = unos_vremena();
	
	printf("\nIzmedju dva vremena je proteklo %d sekundi.", proteklo(v1,v2));
	return 0;
}
