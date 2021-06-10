// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Tacka
	{
		int x,y;
	};
struct Trougao 
	{
		struct Tacka A,B,C;
	};
int izbaci_pravougle(struct Trougao trouglovi[], int n)
{
	int p,q,r;
	int i=0;
	int j=0;
	for(i=0; i<n; i++)
	{
		p=(trouglovi[i].A.x - trouglovi[i].B.x)*(trouglovi[i].A.x-trouglovi[i].B.x) + (trouglovi[i].A.y - trouglovi[i].B.y)*(trouglovi[i].A.y-trouglovi[i].B.y);             
		q=(trouglovi[i].A.x-trouglovi[i].C.x)*(trouglovi[i].A.x-trouglovi[i].C.x) + (trouglovi[i].A.y - trouglovi[i].C.y)*(trouglovi[i].A.y-trouglovi[i].C.y);
		r=(trouglovi[i].C.x-trouglovi[i].B.x)*(trouglovi[i].C.x-trouglovi[i].B.x) + (trouglovi[i].C.y - trouglovi[i].B.y)*(trouglovi[i].C.y-trouglovi[i].B.y);
		
		if(p>q && p>r && p-q-r==0)
		{
			for(j=i; j<n-1; j++)
			{
				trouglovi[j]=trouglovi[j+1];
			}
			n--;
			i--;
		}
		else if(r>q && r>p && r-q-p==0)
		{
			for(j=i; j<n-1; j++)
			{
				trouglovi[j]=trouglovi[j+1];
			}
			n--;
			i--;
		}
		else if(q>p && q>r && q-p-r==0)
		{
			for(j=i; j<n-1; j++)
			{
				trouglovi[j]=trouglovi[j+1];
			}
			n--;
			i--;
		}
			
	}
	return n;
}
	
	
	
	

int main() {

}
