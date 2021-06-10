#include <stdio.h>
/*
Prepravite prethodni program na sljedeći način: dozvoljeno je unositi brojeve između 0 i 100.
Ukoliko se unese broj van ovog opsega, ponavlja se unos. Nakon što korisnik unese broj -1, 
treba za svaki broj napisati koliko puta se ponavlja. Brojeve koji se ne javljaju nijednom na ulazu ne treba ispisivati. 

Primjer ulaza i izlaza:
	Unesite brojeve:
	15
	22
	151
	Brojevi moraju biti izmedju 0 i 100!
	15
	35
	22
	35
	15
	7
	-1
Broj 7 se javlja 1 puta.
	Broj 15 se javlja 3 puta.
	Broj 22 se javlja 2 puta.
	Broj 35 se javlja 2 puta. 
	*/
	
int main() {
    int n=0, p=0, i, brojacba=1;
    int niz[200], brojac[200] = {0};
    printf("Unesite brojeve:\n"); 
    LOOP:
	while(n!=-1){
	    scanf("%d", &n);
	    if((n<0 || n>100) && n!=-1){ printf("Brojevi moraju biti izmedju 0 i 100!\n"); goto LOOP; }
		
		if(brojacba==100) return 0;
	    niz[p]=n;
	   	
	   	p++;
	    
	}
	int j;
	
/*	for(i=0;i<p-1;i++)
	{
		printf("%d ", niz[i]);
	}
	printf("\n");  */
	
	
	for(i=0;i<p-1;i++){
		for(j=i+1;j<p-1;j++){
			if(niz[j] > niz[i])
			{	
				int x;
				x=niz[i];
				niz[i]=niz[j];
				niz[j]=x;
			}
			
		}
	}
	
	/*for(i=0;i<p-1;i++)
	{
		printf("%d ", niz[i]);
	} 
	

	printf("\n"); */
	
	for(i=p-1;i>0;i--)
	{	
		for(j=i-1;j>=0;j--)
		{
			if(niz[j]==niz[i]) brojac[i]++;
		}

	//	printf("Broj %d se javlja %d puta.\n", niz[i], brojac[i]+1);
	}
	for(i=p-2;i>=0;i--)
	{
		if(niz[i+1]!=niz[i]) printf("Broj %d se javlja %d puta.\n", niz[i], brojac[i]+1);
	}
	
	
	return 0;
}
