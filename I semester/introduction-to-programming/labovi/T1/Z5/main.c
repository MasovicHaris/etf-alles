#include <stdio.h>
#define cVT 0.3
#define cMT 0.2
int main() {
    float VT, MT, uPotrosnja;
	printf("Unesi veliku i malu tarifu: ");
	scanf("%f %f", &VT, &MT);
	uPotrosnja=VT+MT;
	printf("Ukupna potrosnja je: %.2f KWh\n", uPotrosnja);
	printf("Cijena racuna je: %.2f KM\n", (VT*cVT)+(MT*cMT));
	
	
	float postotakVT, postotakMT;
	postotakMT = (MT*100)/uPotrosnja;
	postotakVT = (VT*100)/uPotrosnja;
	printf("Velika tarifa: %.2f%% i Mala tarifa: %.2f%%", postotakVT, postotakMT);
	
}
