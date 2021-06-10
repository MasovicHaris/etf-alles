clc
mode(1)
pause
//Zadatak 1 
//Definisanje seta podataka
xdata=linspace(0,2*%pi,10);
ydata=sin(xdata);
x=linspace(0,2*%pi,100);
pause
//Interpolacija funkcije not a knot
[yp, yp1, yp2]=interp(x,xdata,ydata,splin(xdata,ydata));
subplot(1,2,1)
plot(x,yp1,'k');
plot(x,yp2,'r');
pause
//Interpolacija funkcije natural
[yp, yp1, yp2]=interp(x,xdata,ydata,splin(xdata,ydata,'natural'));
subplot(1,2,2)
plot(x,yp1,'k');
plot(x,yp2,'r');

pause
//Zadatak 2
//Definisanje polinoma
P=poly([5,1,2,1],"x","c")
y=poly(0,'y');
Q=1/y^2+1
pause
//Prvi izvod
pd1=derivat(P)
pd2=derivat(Q)
pause
//Drugi izvod
dd1=derivat(pd1)
dd2=derivat(pd2)

pause 
//Zadatak 3
//Definisanje funkcije
function y=F(x)
  y = sum(x.^3);
endfunction
x = [1; 2; 3];
pause
//Računanje  Jakobijana i Hesijana
[J, H] = numderivative(F, x, [], [], "blockmat")

pause
//Zadatak 4
//Definisanje funkcije i vrijednosti parametara
function f=fun(x, a, b, c)
  f=(x+a)^c+b;
endfunction
a=3; b=4; c=2;x=1;
pause
//Računanje gradijenta
g=numderivative(list(fun,a,b,c),x)
//Tačna vrijednost
exact=c*(x+a)^(c-1)

pause
//Zadatak 5
//Definisanje parametara
x0=0;x1=0:0.5:%pi;
pause
//Računanje integrala
X=integrate('sin(x)','x',x0,x1)

pause
//Zadatak 6
//Definisanje funkcije
function y=myfun(x)
y=x*sin(30*x)/sqrt(1-((x/(2*%pi))^2));
endfunction
exact=-2.5432596188;
pause
//Računanje integrala i greške
I=intg(0,2*%pi,myfun)
abs(exact-I)

pause
//Zadatak 7
//Definisanje funkcije
function y=g(z)
  y = z^(3 + %pi * %i);
endfunction
pause
//Računanje vrijednosti integrala
intc(1+%i, 4-%i,g)

pause
//Zadatak 8
//Definisanje t
t=0:0.1:%pi;
pause
//Računanje integrala
inttrap(t,cos(t))

pause
//Zadatak 9
//Računanje integrala
intsplin(t,cos(t))
