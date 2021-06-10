#include <stdio.h>
/* 6.  Napisati program koji sa tastature učitava prirodan broj, te ispituje da li je broj prost. Ako se unese broj koji nije prirodan (n<=0),
program treba ispisati poruku „Broj nije prirodan“ i završava. 
Ako je broj prost treba ispisati poruku „Uneseni broj je prost“, u suprotnom poruku „Uneseni broj je slozen“. Ako je unesen broj n=1 
program treba ispisati poruku: „Broj 1 nije ni prost ni slozen“.
Napomena: Pod prostim brojem podrazumijevamo prirodan broj koji se ne može napisati kao umnožak dvaju prirodnih brojeva manjih od tog broja. 
Broj 1 nije niti prost niti složen. 

Primjeri ulaza i izlaza:

Unesite broj: -5
Broj nije prirodan.

Unesite broj: 1
Broj nije ni prost ni slozen.

Unesite broj: 121
Broj je slozen.

Unesite broj: 13
Broj je prost. */
 
int main() {
      int i, c = 0; int signed n;
      printf("Unesite broj: ");
      scanf("%d", &n);
      if(n<=0) { printf("Broj nije prirodan."); return 0; }
      if(n==1) { printf("Broj nije ni prost ni slozen."); return 0; }
      for (i=1; i<=n; i++) {
          if (n%i==0) c++;
      }
      if (c==2) printf("Broj je prost.");
      else printf("Broj je slozen.");
      return 0;    
      
}  