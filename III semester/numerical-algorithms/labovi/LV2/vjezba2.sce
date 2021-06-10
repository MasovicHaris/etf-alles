clc
mode(1)

pause
//Zadatak 1
A=[2,1,3;2,6,8;6,8,18]
B=[1;3;5]

pause
//Varijanta 1
X=A\B

pause
//Varijanta 2
X=(A.'*A)\(A.'*B)

pause
//Varijanta 3
X=pinv(A)*B

pause
//Zadatak 2
A=[2,1;-3,1;-1,1]
B=[-1;-1;2]
X=A\B
pause
//Greska 
err=abs(A*X-B)

pause
//Zadatak 3
//a)
A=[2,4,6,8;3,5,7,9]
B=[10*ones(2,4)]

pause
A/B

pause
//b)
A=[1 2 3; 4 5 6; 7 8 9]
B=[7 5 6; 2 0 8; 5 7 1]

pause
A/B

pause
//Zadatak 4
C=testmatrix('magi',3)
D=inv(testmatrix('hilb',3))

pause
//Determinanta
det(C)
det(D)

pause
//Rang
rank(C)
rank(D)

pause
//Faktor uslovljenosti
cond(C)
cond(D)

pause
//Zadatak 5
A=[1 -2 -2 -3; 3 -9 0 -9; -1 2 4 7; -3 -6 26 2]
B=[ 2 -1 0; -1 2 -1; 0 -1 2]

pause
//LU faktorizacija
[L, U]=lu(A)

pause
//Faktorizacija Choleskog
R=chol(B)

pause
//provjera
A
L*U

//provjera
B
R*R'

pause
//Zadatak 6
M=[3 4 18 34 0 2 31
1 -3 -7 -6 2 4 26
2 1 7 16 3 -1 27
5 11 43 74 2 0 56
3 -3 -3 6 -1 14 55
-2 0 -4 -12 1 5 6
1 -6 -16 -18 4 4 33]

pause
//RREF
rref(M)

pause
//Zadatak 7
P=[1,1,1;1,2,3;1,3,6]

pause
//QR faktorizacija
[Q,R]=qr(P)

pause
//Provjera
P
Q*R

pause
//Zadatak 8
A=[1,0,1;-1,-2,0;0,1,-1]

pause
//a) Predefinisana funkcija
X=spec(A)

pause
//b) QR algoritam
AA=A;
[Q,R]= qr(AA); AA=R*Q
pause
[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

[Q,R]= qr(AA); AA=R*Q

pause
//Provjera sopstvenih vrijednosti
X
AA

pause
//c)SVD
[U,S,V]=svd(A)

pause
//Singularne vrijednosti 
S

pause
//Provjera SVD dekompozicije
A
U*S*V.'
