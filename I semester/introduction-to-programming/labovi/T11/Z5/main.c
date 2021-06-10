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

struct Vrijeme proteklo( struct Vrijeme v1, struct Vrijeme v2){
	
	struct Vrijeme v3;
	
	if(v1.minute<v2.minute && v1.minute!=0){ v1.sati--; v1.minute+=60; }
	if(v1.sekunde<v2.sekunde && v1.sekunde!=0){ v1.minute--; v1.sekunde+=60; }
	
	v3.sati = abs(v1.sati-v2.sati);
	v3.minute = abs(v1.minute-v2.minute);
	v3.sekunde = abs(v1.sekunde-v2.sekunde);
	
	return v3;
	
}

	
int main() {
	struct Vrijeme v1;
	struct Vrijeme v2;
	printf("Unesite prvo vrijeme (h m s): ");
	v1 = unos_vremena();
	printf("\nUnesite drugo vrijeme (h m s): ");
	v2 = unos_vremena();
	
	struct Vrijeme v3;
	v3 = proteklo(v1,v2);
	printf("\nIzmedju dva vremena je proteklo %d sati, %d minuta i %d sekundi.", v3.sati, v3.minute, v3.sekunde);
	return 0;
}
