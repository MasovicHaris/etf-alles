#include <stdio.h>

char *tritacke(char *s)
{
	int duzinaslova=0;
	char *reset = s;
	
	while(*s!='\0')
	{
		while(*s==' ') s++;
		
		if(*s>='A' && *s<='Z' || *s>='a' && *s<='z'){
			
			char *pocetak = s;
			char *kraj = s;
			
			while(*kraj!=' ' && *kraj!='\0') kraj++;
			
			/* */
			
			char *duzina = pocetak;
			while(*duzina!=' ' && *duzina!='\0'){
				
				duzinaslova++;
				
				duzina++;
			}
			
			/* */
			
			if(duzinaslova>=10)
			{
				
				pocetak=pocetak+3;
				*pocetak='.';
				pocetak++;

				while(*pocetak!='\0')
				{
					*pocetak=*kraj;
					
					if(*kraj=='\0'){
						
					*pocetak='\0';
					break;
					}
					
					kraj++;
					pocetak++;
				}
				
			}
			
			
			
			
			
		} 
		
		
		if(*s=='\0') s--;
		
		duzinaslova=0;
		s++;
	}
	
	
	
	return reset;
}


int main() {
	
	return 0;
}
