// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int periodican(const char *string)
{
	int duzina=0;
	const char *p1=string;
	const char *p2=string;
	int bul=1;
	
		while(*p1!=0)
		{
			if(*p1==*p2 && p1!=p2)
			{
				duzina=p1-p2;
				while(*p1!=0)
				{
					if(bul==0) break;
					if(*p1!=*p2)
					{
						bul=0;
						break;
					}
					p1++;
					p2++;
				}
				if(bul==0)
				{
					p2=string;
					p1=p2+duzina;
					bul=1;
				}
				else if(bul==1) return duzina;
			}
			p1++;
		}
		return 0;
}

int main() {
	char string[10] = "abacaba";
	int period=periodican(string);
	printf("%d", period);
	return 0;
}
