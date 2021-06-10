// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int main() {
	char p1, p2, p3;
	int t1, t2, t3, a1=0, e1=0, u1=0, a2=0, e2=0, u2=0, a3=0, e3=0, u3=0, sarajevo=0, mostar=0, bihac=0;
	
	printf("Unesite prognozu za Sarajevo: \n");
	printf("Temperatura: ");
	scanf("%d", &t1);
	printf("Padavine (D/N): ");
	scanf(" %c", &p1);
	while( p1!='D' && p1!='d' && p1!='n' && p1!='N')
	{
	    printf("Pogresan unos.\n");
	    printf("Padavine (D/N): ");
	    scanf(" %c", &p1);
	}
	
	printf("Unesite prognozu za Mostar: \n");
	printf("Temperatura: ");
	scanf("%d", &t2);
	printf("Padavine (D/N): ");
	scanf(" %c", &p2);
	while( p2!='D' && p2!='d' && p2!='n' && p2!='N')
	{
	    printf("Pogresan unos.\n");
	    printf("Padavine (D/N): ");
	    scanf(" %c", &p2);
	}
	
	printf("Unesite prognozu za Bihac: \n");
	printf("Temperatura: ");
	scanf("%d", &t3);
	printf("Padavine (D/N): ");
	scanf(" %c", &p3);
	while( p3!='D' && p3!='d' && p3!='n' && p3!='N')
	{
	    printf("Pogresan unos.\n");
	    printf("Padavine (D/N): ");
	    scanf(" %c", &p3);
	}
	
	if(t1<=30 && t1>=-5)
	e1=1;
	if((p1=='n' || p1=='N')&&(t1<=5 || t1>20))
	u1=1;
	if(((p1=='D' || p1=='d')&&t1<=0) || (p1=='N' || p1=='n'))
	a1=1;
	if(a1==1 && u1==1 && e1==1)
	sarajevo=1;
	else if((u1==1 && a1==1)||(u1==1 && e1==1)||(a1==1 && e1==1))
	sarajevo=2;
	else
	sarajevo=0;
	
	
	if((p2=='n' || p2=='N')&&(t2<=5 || t2>20 ))
	u2=1;
	if(t2<=30 && t2>=-5)
	e2=1;
	if(((p2=='D' || p2=='d')&&t2<=0) || (p2=='N' || p2=='n'))
	a2=1;
	if(a2==1 && u2==1 && e2==1)
	mostar=1;
	else if((a2==1 && e2==1)||(a2==1 && u2==1)||(e2==1 && u2==1))
	mostar=2;
	else 
	mostar=0;
	
	
	if((p3=='n' || p3=='N')&&(t3<=5 || t3>20))
	u3=1;
	if(t3<=30 && t3>=-5)
	e3=1;
	if(((p3=='d' || p3=='D')&&t3<=0) || (p3=='N' || p3=='n'))
	a3=1;
	if(a3==1 && e3==1 && u3==1)
	bihac=1;
	else if((a3==1 && e3==1)||(a3==1 && u3==1)||(e3==1 && u3==1))
	bihac=2;
	else
	bihac=0;
	
	if(sarajevo==1)
	printf("Drugarice idu u Sarajevo.\n");
	else if(mostar==1 && (sarajevo==2 || sarajevo==0))
	printf("Drugarice idu u Mostar.\n");
	else if(bihac==1 && (sarajevo==0 || sarajevo==2)&&(mostar==0 || mostar==2))
	printf("Drugarice idu u Bihac.\n");
	else if(e1==1 && u1==1 && sarajevo==2 && mostar!=1 && bihac!=1)
	printf("Elma i Una mogu u Sarajevo.");
	else if(a1==1 && u1==1 && sarajevo==2 && mostar!=1 && bihac!=1)
	printf("Anja i Una mogu u Sarajevo.");
	else if(a1==1 && e1==1 && sarajevo==2 && mostar!=1 && bihac!=1)
	printf("Anja i Elma mogu u Sarajevo.");
	else if(a2==1 && u2==1 && mostar==2 && sarajevo!=1 && sarajevo!=2 && bihac!=1)
	printf("Anja i Una mogu u Mostar.");
	else if(a2==1 && e2==1 && mostar==2 && sarajevo!=1 && sarajevo!=2 && bihac!=1)
	printf("Anja i Elma mogu u Mostar.");
	else if(e2==1 && u2==1 && mostar==2 && sarajevo!=1 && sarajevo!=2 && bihac!=1)
	printf("Elma i Una mogu u Mostar.");
	else if(a3==1 && u3==1 && bihac==2 && sarajevo!=1 && sarajevo!=2 && mostar!=1 && mostar!=2)
	printf("Anja i Una mogu u Bihac.");
	else if(a3==1 && e3==1 && bihac==2 && sarajevo!=1 && sarajevo!=2 && mostar!=1 && mostar!=2)
	printf("Anja i Elma mogu u Bihac.");
	else if(e3==1 && u3==1 && bihac==2 && sarajevo!=1 && sarajevo!=2 && mostar!=1 && mostar!=2)
	printf("Elma i Una mogu u Bihac.");
	else if(sarajevo==0 && mostar==0 && bihac==0)
	printf("Ne odgovara niti jedan grad.");
	
	
	return 0;
	
}
