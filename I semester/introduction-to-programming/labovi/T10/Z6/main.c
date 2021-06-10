#include <stdio.h>

char *ukloni_komentare(char *s){
	
	char *reset = s;
	/* */
 	while(*s!='\0')
	{
		if(*s=='/' && *(s+1)=='*')
		{
			char *s2=s+2;
			char *pom=s;
			while((*s2!='*' || *(s2+1)!='/') && *s2!='\0' && *(s2+1)!='\0') s2++;
			if(*s2=='\0' || *(s2+1)=='\0') break;
			s2=s2+2;
			
			while(*pom!='\0')
      		{
      			*pom = *s2;
      			if (*s2=='\0'){ 
         
         		*pom='\0'; 
        		 break; 
         
      			}
      	 	pom++;
    		s2++;
    	    }
			
			
			
		}
		if(*s=='/' && *(s+1)=='/')
		{
			char *s2=s+2;
			char *pom=s;
			while(*s2!='\n' && *(s2+1)!='\n' && *s2!='\0' && *(s2+1)!='\0') s2++;
			s2++;
			
			while(*pom!='\0')
      		{
      			*pom = *s2;
      			if (*s2=='\0'){ 
         
         		*pom='\0'; 
        		 break;  
         
      			}
      	 	pom++;
    		s2++;
    	    }
			
			
			
		} 
		
		
		
		
		
		s++;
	}
	
	
	return reset;
}



int main() {
	return 0;
}
