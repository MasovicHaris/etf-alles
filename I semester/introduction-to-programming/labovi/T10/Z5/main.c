#include <stdio.h>

int duzina(char* s) {
int duz=0;
while (*s != '\0') {
duz++;
s++;
}
return duz;
}




char* whitespace(char* text){
	
	char *onako = text;
   int brojac=0;
   
   while(*text!='\0') {
   	
   	if(*text=='\n'|| *text=='\t') *text=' ';
   	
   	text++;
   }
   
   text=onako;
   
   while(*text!='\0')
   {
      if(*text==' ' && *(text+1)==' '){
         char *kraj_rijeci = text+1;
         char *pom = text+1;
         
      while (*kraj_rijeci != '\0' && *kraj_rijeci==' ') kraj_rijeci++; 
         
         
      while(*pom!='\0')
      {
      *pom = *kraj_rijeci;
      if (*kraj_rijeci=='\0'){ 
         
         *pom='\0'; 
         break; 
         
      }
      pom++;
      kraj_rijeci++;
      }
      
      }
      text++;
   }
   
   text= onako;
   
   while(*text==' ') { onako++; text++; } // dobacuje do pocetka stringa 
   
   while(*text!='\0') text++; // ide do kraja 
   
   --text;
   
   if(*onako=='\0') return onako;
   
   while(*text==' '){
      text--;
   }
   *(text+1)='\0';
   return onako;
}

int main() {
	return 0;
}
