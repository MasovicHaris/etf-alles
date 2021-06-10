clc
mode(1)
pause
//Zadatak 1
//a)
//Plotanje i definisanje funkcija
deff('res=funct_1(x)','res=cos(x)-x');
x0 = 0;
x = linspace(-2,2,51);
y=cos(x);
plot(x,y,'r-');
plot(x,x,'b-');
pause
//Poziv fsolve
xsol =fsolve(x0,funct_1)

pause
//b)
//Plotanje i definisanje funkcija
deff('res=funct_2(x)',['res(1)=x(2)-(x(1).^2+1)';'res(2)=x(1)-(2*x(2)-x(2).^2)/3']);
clf;
x = linspace(-3,3,101);
y = x.^2+1;
plot(x,y,'r-');
y = linspace(-3,5,51);
x=(2*y-y.^2)/3;
plot(x,y,'b-');
x0 = [1;0];
x1 = [-3;8];
pause
//Poziv fsolve
xsol1 =fsolve(x0,funct_2)
xsol2 =fsolve(x1,funct_2)

pause
//Zadatak 2
//Plotanje funkcije
x = linspace(-1.5,1.5); y = linspace(-1,3);
[X,Y] = meshgrid(x,y);
Z= (1-X).^2 + 100*(Y-X.^2).^2;
clf
surf(X,Y,Z,'facecol','red','edgecol','blu');
pause
//Definisanje funkcije
function y=banana(x)
  y = 100*(x(2)-x(1)^2)^2 + (1-x(1))^2;
endfunction
pause
//Potraga minimuma
[x, fval, exitflag, output] = fminsearch ( banana , [-1.2 1] )

pause 
//Zadatak 3
//Definisanje funkcije i početnih uvjeta
function [dpdt] = opruga(t, p)
m = 10;
k = 100;
dpdt = zeros(2, 1);
dpdt(1) = p(2);
dpdt(2) = -k*p(1)/m
endfunction
clf
t0=0;
y0=[0;1];
pause
//Obično rješavanje
t=linspace(0,10,100);
y = ode(y0,t0,t,opruga);
subplot(1,2,1)
plot(t',y(1,:)');
title('Pozicija vs Vrijeme');
subplot(1,2,2)
title('Brzina vs Vrijeme');
plot(t',y(2,:)');


pause
//Zadatak 4
//Definisanje sekvenci
x = [ 1 3 5 4 2 ];
a = [ 1 5 4 2];
b = [ 4 1 3 ];
a1 = [ a 0 0 0 0 ];
b1 = [ b 0 0 0 0 0 ];
pause
//a) Računanje FFT i IFFT
y = fft(x)
ifft(y)
fft(y, 1) 
pause
//b) Diskretna konvolucija direktno i indirektno
ap = poly(a, 'x', 'c')
bp = poly(b, 'x', 'c');
ap * bp
pause
a1f = fft(a1)
b1f = fft(b1)
c1f = a1f .* b1f
ifft(c1f)
pause
//c) Diskretna konvolucija-predefinisane funkcije
conv(a, b)
convol(a, b)



