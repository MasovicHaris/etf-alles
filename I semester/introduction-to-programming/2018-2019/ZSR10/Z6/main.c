// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int duzina(const char* p)
{
	int brojac=0;
	while(*p!=0) {
		brojac++;
		p++;
	}
	return brojac;
}

int jel_ta_rijec(char *p1, const char *p2, int cs)
{
	int duz=duzina(p2);
	int i=0; 
	if(cs==0) {
		while(i<duz) {
			if(!(*p1==*p2 || *p1-32==*p2 || *p1+32==*p2)) return 0;
			p1++;
			p2++;
			i++;
		}
	} else if(cs==1) {
		while(i<duz) {
			if(*p1!=*p2) return 0;
			p1++;
			p2++;
			i++;
		}
	}
	return 1;
}
void izbaci_rijec(char* s1, char* s2)
{
	while(*s2!='\0') {
		*s1++=*s2++;
	}
	*s1='\0';
}

void ubaci_rijec(char* s1, const char* s2)
{	
	int duzina_prosiri=duzina(s2);
	char* kraj=s1;
	while(*kraj!=0) kraj++;
	while(kraj>=s1) {
		*(kraj+duzina_prosiri)=*kraj;
		kraj--;
	}
	while(*s2!=0) {
		*s1++=*s2++;
	}
}

char* zamijeni_tekst(char* str, const char *sta, const char *sa_cim, int cs)
{
	char* p=str;
	int duz_sta=duzina(sta);
	while(*p!=0) {
		if(cs==0) {
			if(*p==*sta || *p+32==*sta || *p-32==*sta) {
				if(jel_ta_rijec(p,sta,cs)) {
					izbaci_rijec(p, p+duz_sta);
					//p--;
					ubaci_rijec(p, sa_cim);
				}
			}
		} else if(cs==1) {
			if(*p==sta[0]) {
				if(jel_ta_rijec(p,sta,cs)) {
					izbaci_rijec(p, p+duz_sta);
					//p--;
					ubaci_rijec(p, sa_cim);
				}
			}
		}
		p++;
	}
	p=str;
	return p;
}

int main()
{
	char tekst[100] = "  Zeko   pije   CAJ.  Pije caj mali zeko!";
	char*pok=tekst;
	while(*pok!='C') pok++;
	zamijeni_tekst (tekst, "caj", "mlijeko", 0); //cs = 0
	printf ("'%s'", tekst);
	return 0;
}
