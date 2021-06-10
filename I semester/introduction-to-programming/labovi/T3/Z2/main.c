#include <stdio.h>

int main() {
	int i=0, broj, suma=0;
	for(i=0; suma<=100 ;i++)
	{
		scanf("%d", &broj);
		suma+=broj; 
		if(!(suma<=100)) { printf("%d", suma); return 0; }
		
	}
	return 0;
}
