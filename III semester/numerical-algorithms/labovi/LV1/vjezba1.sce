clc
mode(1)

pause 
//Zadatak 1
//a
3*456/23+31.54+2^6
//b
sqrt(2)*log(10)
//c
cos(%pi/3)+sin(%pi/2)*exp(3)
//d
atan(5)+log10(20)

pause
//Zadatak 2
//a
zeros(5,9)
//b
ones(7,2)
//c
eye(5,5)
//d
A=[1, -4*%i, sqrt(2); log(-1), sin(%pi/2), cos(%pi/3);asin(0.5), acos(0.8),exp(0.8)]

pause
//Zadatak 3
//a
A.'
//b
A'
//c
A-A.'
//d
A*A.'
A.'*A
//e
det(A)
sum(A)
sum(A,1)
sum(A,2)

pause
//Zadatak 4
//a
A(2,:)
//b
A(:,3)
//c
A(2,3)
//d
B=A(1:2,2:3)

pause
//Zadatak 5
a=[ones(1,3);3*ones(1,3);2*ones(1,3)]
b=[9:-1:7;6:-1:4;3:-1:1]
//a
c=cos(b)
//b
c=sin(b).*cos(a)
//c
c=b^(1/5)
//d
c=a.^(1/3)

pause
//Zadatak 6
//a
a=1:50
//b
b=49:-1:0
//c
c=0:5:45

pause
//Zadatak 7
//a
x=-%pi:%pi/50:%pi;
y=cos(x);
plot(x,y)

pause
clf
//b
x=linspace(1,7,100);
y=sin(1 ./ x);
plot(x,y,'k')

pause
//c
y= sin(2*x);
plot(x,y,'bo')

pause
clf
//Zadatak 8
x=linspace(-8,8,100);
y=linspace(-8,8,100);
[X,Y]=meshgrid(x,y);
Z=X.^2+Y.^2;
surf(X,Y,Z);

pause
//Zadatak 9
//a
function [zbir,razlika] = Rezultat(x,y)
zbir=x+y;
razlika=x-y;
endfunction
//Primjer
[z,r]=Rezultat(5,3)

pause
//b
function [s] = Suma (A)
s=0;
for i=1:size(A,'r')
    for j=1:size(A,'c')
        s=s+A(i,j);
    end;
end;
endfunction
//Primjer
Suma(A)

pause
//Zadatak 10
//a
function [] = z10a(s)
    x=linspace(-2,2,100);
    y=evstr(s);
    subplot(1,2,1);
    plot(x,y,'b');
    subplot(1,2,2);
    plot(x,y,'k+');
endfunction
z10a('x^2')
pause
clf
//b
function [] = z10b(s)
   X=linspace(-4,4,100);
   Y=linspace(-4,4,100);
   [x,y]=meshgrid(X,Y);
   z=evstr(s)
   surf(x,y,z);
endfunction
z10b('x.^2+y.^2')
