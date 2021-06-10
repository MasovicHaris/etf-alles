// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <string.h>
int da_li_je_validna(const char* pok)
{
	if(*pok!=65 && *pok!=69 && *pok!=74 && *pok!=75 && *pok!=79 && *pok!=84) return 0;
	int i=0;
	pok++;
	for(i=0; i<2; i++)
	{
		if(!(*pok>='0' && *pok<='9')) return 0;
		pok++;
	}
	if(*pok!='-') return 0;
	pok++;
	if(*pok!=65 && *pok!=69 && *pok!=74 && *pok!=75 && *pok!=79 && *pok!=84) return 0;
	pok++;
	if(*pok!='-') return 0;
	pok++;
	for(i=0; i<3; i++)
	{
		if(!(*pok>='0' && *pok<='9')) return 0;
		if(*pok=='\0') break;
		pok++;
	}
	return 1;
}

int generisi_tablice(const char* prethodna, char* nova)
{
	int reverse=0;
	if(!da_li_je_validna(prethodna)) return -1;
	char slovo1= prethodna[0];
	char slovo2= prethodna[4];
	
	
	int brojevi=(prethodna[1]-'0')*10000 + (prethodna[2]-'0')*1000 + (prethodna[6]-'0')*100 + (prethodna[7]-'0')*10 + (prethodna[8]-'0');
	brojevi++;
	char brs[0]=prethodna[1]; brs[1]=prethodna[2]; brs[2]=prethodna[6]; brs[3]=prethodna[7]; brs[4]=prethodna[8];
	if(brojevi>99999)
	{
		brojevi=0;
		if(slovo2=='A') slovo2='E';
		else if(slovo2=='E') slovo2='J';
		else if(slovo2=='J') slovo2='K';
		else if(slovo2=='K') slovo2='M';
		else if(slovo2=='M') slovo2='O';
		else if(slovo2=='O') slovo2='T';
		else if(slovo2=='T') 
		{
			slovo2='A';
			if(slovo1=='A') slovo1='E';
			else if(slovo1=='E') slovo1='J';
			else if(slovo1=='J') slovo1='K';
			else if(slovo1=='K') slovo1='M';
			else if(slovo1=='M') slovo1='O';
			else if(slovo1=='O') slovo1='T';
			else if(slovo1=='T') { strcat(nova,"A00-A-000"); return 1; }
		}
	}
	else if(brojevi<=99999)
	{
		nova[0]=slovo1; 
		nova[1]=(reverse%10)+48; 
		if(reverse!=0) reverse=reverse/10;
		nova[2]=(reverse%10)+48; 
		if(reverse!=0) reverse=reverse/10;
		nova[3]='-';
		nova[4]=slovo2;
		nova[5]='-';
		nova[6]=(reverse%10)+48; 
		if(reverse!=0) reverse=reverse/10;
		nova[7]=(reverse%10)+48; 
		if(reverse!=0) reverse=reverse/10;
		nova[8]=(reverse%10)+48; 
		nova[9]='\0';
		
		if(nova[9]=='9') 
		{
			nova[9]=='0';
			nova[8]++;
			if(nova[8]=='9') 
		{
			nova[9]=='0';
			nova[8]++;
			
		
		return 1;
	}
	 return 1;
}

int main() {
	char tablica[15] = "A00-A-009";
char nova[15], t2[15], t3[15];
printf("%d ", generisi_tablice(tablica, nova));
printf("%s\n", nova);
printf("%d ", generisi_tablice(nova, t2));
printf("%s\n", t2);
printf("%d ", generisi_tablice(t2, t3));
printf("%s\n", t3);

}
