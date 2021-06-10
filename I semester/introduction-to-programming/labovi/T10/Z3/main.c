#include <stdio.h>
char * rot13( char * str ) 
    {
  		char *reset = str;
       while(*str!='\0')
       {

            if( *str >= 'a' && *str < 'n') *str += 13;       
            else if( *str >= 'n' && *str <= 'z') *str -= 13;
            
            if( *str >= 'A' && *str < 'N') *str += 13;       
            else if( *str >= 'N' && *str <= 'Z') *str -= 13;
            str++;
        }
        return reset;
    }
int main() {
	return 0;
}
