// zadatak by @who.so (hhamzic1@etf.unsa.ba)
#include <stdio.h>

int main()
{
	
	int x1, y1, xp, yp, n, m, odb1=0, odb2=0, px=0, py=0;
	
	printf("Unesite brojeve x1 y1 xp i yp: ");
	scanf("%d %d %d %d", &x1, &y1, &xp, &yp);
	printf("Unesite n i m: ");
	scanf("%d %d", &n, &m);
	
	if(y1==yp || x1==xp)
	printf("0 1");
	else{
	
	long double koef=(double)(yp-y1)/(double)(xp-x1);
	if(xp<x1)
	px=1;
	if(yp<y1)
	py=1;
	
	int kraj=0;
	
	while(kraj!=1)
{
	 long long int cx, cy, rezx, rezy;
	 
	 if(odb1==0)
	 rezx=x1;
	 else
	 if(odb1==-1)
	 rezx=-x1;
	 else{
	 	if(odb1%2){
	 		rezx=(odb1+1)*n-x1;
	 	}
	 	else{
	 		rezx=odb1*n+x1;
	 	}
	 }
	 if(odb2==0)
	 rezy=y1;
	 else if(odb2==-1)
	 rezy=-y1;
	 
	 else{
	 	if(odb2%2){
	 		rezy=(odb2+1)*m-y1;
	 	}
	 	else{
	 		rezy=odb2*m+y1;
	 	}
	 }
	 
	long double dstrana=(double)(rezx-x1)*koef;
	long double lstrana=(double)(rezy-y1);
	long double r=lstrana-dstrana;
	 
	 if(r<0)
	 {
	 	r=-r;
	 	
	 }
	 
	 if((odb1!=0 || odb2!=0)&&r<0.0000000001){
	 	if(odb1<0)
	 	odb1=-odb1;
	 	if(odb2<0)
	 	odb2=-odb2;
	 	printf("0 %d", odb2+odb1);
	 	kraj=1;
	 	break;
	 }
	 else{
	 	cx=n*(odb1+1-px);
	 	cy=m*(odb2+1-py);
	 	
	 	if((double)cy>((double)(cx-x1)*koef+y1))
	 	{
	 		if(!py)
	 			if(px==1)
	 		odb1--;
	 		if(px==0)
	 		odb1++;
	 		else 
	 		odb2--;
	 	}
	 	else if((double)cy<((double)(cx-x1)*koef+(double)(y1)))
	 	{
	 		if(!py)
	 		odb2++;
	 		else
	 		{
	 		if(px==1)
	 		odb1--;
	 		if(px==0)
	 		odb1++;
	 		}
	
	 	}
	 	else
	 	{
	 		if(odb1<0)
	 		odb1=-odb1;
	 		if(odb2<0)
	 		odb2=-odb2;
	 		printf("-1 %d", odb2+odb1);
	 		kraj=1; 
	 		break;
	 	}
	 	
	 }
}
}
}