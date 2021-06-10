clc
mode(1)
pause
//Zadatak 1 
//Definisanje P1 i P2
P1=poly(1:2:5,"x","c")
P2=poly(1:3:10,"x","r")
pause
//Nule P1 i P2
kp1=roots(P1)
kp2=roots(P2)
pause
//Koeficijenti P1 i P2
kop1=coeff(P1)
kop2=coeff(P2)

pause
//Zadatak 2
pause
//a)Sabiranje
Z=P1+P2
pause
//b)Oduzimanje
R=P1-P2
pause
//c)Množenje
P=P1*P2
pause
//d)Dijeljenje
D=P1/P2

pause
//Zadatak 3
P3=poly(1:3,"y","c")
pause
//a) Broj 5
horner(P3,5)
pause
//b) Vektor[1:5]
horner(P3,1:5)
pause
//c) Kompleksan broj 5+2i
horner(P3,5+2*%i)
pause
//d) Izraz 1/x
x=poly(0,'x');
horner(P3,1/x)

pause
//Zadatak 4
//Obična chepol
var='z';
F=chepol(4,var)
pause
//Rekurzivna
T0=1;
T1=poly(0,var);
T2=2*poly(0,var)*T1-T0
T3=2*poly(0,var)*T2-T1
T4=2*poly(0,var)*T3-T2
