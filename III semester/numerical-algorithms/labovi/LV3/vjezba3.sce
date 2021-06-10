
mode(1)
clc
clf
pause
//Zadatak 1 
// a)Sin(x)
x1=linspace(0,2*%pi,100);
y1=sin(x1);
subplot(1,2,1)
plot(x1,y1);

pause
//b) Rungeova funkcija
x2=linspace(-1,1,100);
y2=1 ./ (1+25*x2.^2);
subplot(1,2,2)
plot(x2,y2);

pause
//Zadatak 2
clf
//Definisanje tačaka za interpolaciju
xdata1=linspace(0,2*%pi,10);
ydata1=sin(xdata1);
//Potrebno izvršiti zaokruživanje ydata1(10)
ydata1(10)=round(ydata1(10));
xdata2=linspace(-1,1,10);
ydata2=1 ./ (1+25*xdata2.^2);
xx1=linspace(0,2*%pi,50);
xx2=linspace(-1,1,50);


pause
//a) Linearna interpolacija
//Sin(x)
yy1=interp1(xdata1,ydata1,xx1,"linear");
subplot(2,2,1)
plot(x1,y1,'r');
plot(xx1,yy1,'b');
plot(xdata1,ydata1,'g*');
legend(["Sin(x)";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//Rungeova funkcija
yy2=interp1(xdata2,ydata2,xx2,"linear");
subplot(2,2,2)
plot(x2,y2,'r');
plot(xx2,yy2,'b');
plot(xdata2,ydata2,'g*');
legend(["Runge funkcija";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//b) Spline interpolacija
//Sin(x)
yy1=interp1(xdata1,ydata1,xx1,"spline");
subplot(2,2,3)
plot(x1,y1,'r');
plot(xx1,yy1,'b');
plot(xdata1,ydata1,'g*');
legend(["Sin(x)";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//Rungeova funkcija
yy2=interp1(xdata2,ydata2,xx2,"spline");
subplot(2,2,4)
plot(x2,y2,'r');
plot(xx2,yy2,'b');
plot(xdata2,ydata2,'g*');
legend(["Runge funkcija";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//Zadatak 3
//Sin(x)
clf
//not-a-knot
d=splin(xdata1,ydata1,"not_a_knot");
[yy1]=interp(xx1,xdata1,ydata1,d);
subplot(2,2,1)
plot(x1,y1,'r');
plot(xx1,yy1,'b');
plot(xdata1,ydata1,'g*');
legend(["Sin(x)";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//clamped
d=splin(xdata1,ydata1,"clamped",[1,1]);
[yy1]=interp(xx1,xdata1,ydata1,d);
subplot(2,2,2)
plot(x1,y1,'r');
plot(xx1,yy1,'b');
plot(xdata1,ydata1,'g*');
legend(["Sin(x)";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//natural
d=splin(xdata1,ydata1,"natural");
[yy1]=interp(xx1,xdata1,ydata1,d);
subplot(2,2,3)
plot(x1,y1,'r');
plot(xx1,yy1,'b');
plot(xdata1,ydata1,'g*');
legend(["Sin(x)";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//periodic
d=splin(xdata1,ydata1,"periodic");
[yy1]=interp(xx1,xdata1,ydata1,d);
subplot(2,2,4)
plot(x1,y1,'r');
plot(xx1,yy1,'b');
plot(xdata1,ydata1,'g*');
legend(["Sin(x)";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//Runge
clf
//not-a-knot
d=splin(xdata2,ydata2,"not_a_knot");
[yy2]=interp(xx2,xdata2,ydata2,d);
subplot(2,2,1)
plot(x2,y2,'r');
plot(xx2,yy2,'b');
plot(xdata2,ydata2,'g*');
legend(["RungeFun";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//clamped
d=splin(xdata2,ydata2,"clamped",[25/338,-25/338]);
[yy2]=interp(xx2,xdata2,ydata2,d);
subplot(2,2,2)
plot(x2,y2,'r');
plot(xx2,yy2,'b');
plot(xdata2,ydata2,'g*');
legend(["RungeFun";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//natural
d=splin(xdata2,ydata2,"natural");
[yy2]=interp(xx2,xdata2,ydata2,d);
subplot(2,2,3)
plot(x2,y2,'r');
plot(xx2,yy2,'b');
plot(xdata2,ydata2,'g*');
legend(["RungeFun";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//periodic
d=splin(xdata2,ydata2,"periodic");
[yy2]=interp(xx2,xdata2,ydata2,d);
subplot(2,2,4)
plot(x2,y2,'r');
plot(xx2,yy2,'b');
plot(xdata2,ydata2,'g*');
legend(["RungeFun";"Vrijednosti interpolacije";"Podaci za interpolaciju"]);

pause
//Zadatak 4
//Sin(x)
clf
//not-a-knot
xdata1=xdata1';
ydata1=ydata1';
xx1=linspace(-%pi,3*%pi,100)';
d=splin(xdata1,ydata1);
yy1a=interp(xx1,xdata1,ydata1,d,"C0");
yy1b=interp(xx1,xdata1,ydata1,d,"by_nan");
yy1c=interp(xx1,xdata1,ydata1,d,"by_zero");
yy1d=interp(xx1,xdata1,ydata1,d,"natural");
yy1e=interp(xx1,xdata1,ydata1,d,"linear");
yy1f=interp(xx1,xdata1,ydata1,d,"periodic");
subplot(2,2,1)
title("Sin(x)");
plot2d(xx1,[yy1a yy1b yy1c]);
legend(["C0";"by_nan";"by_zero"]);
subplot(2,2,2)
plot2d(xx1,[yy1d yy1e yy1f]);
title("Sin(x)");
legend(["natural";"linear";"periodic"]);

pause
//Runge(x)
//not-a-knot
xdata2=xdata2';
ydata2=ydata2';
xx2=linspace(-2,2,100)';
d=splin(xdata2,ydata2);
yy2a=interp(xx2,xdata2,ydata2,d,"C0");
yy2b=interp(xx2,xdata2,ydata2,d,"by_nan");
yy2c=interp(xx2,xdata2,ydata2,d,"by_zero");
yy2d=interp(xx2,xdata2,ydata2,d,"natural");
yy2e=interp(xx2,xdata2,ydata2,d,"linear");
yy2f=interp(xx2,xdata2,ydata2,d,"periodic");
subplot(2,2,3)
title("RungeFun");
plot2d(xx2,[yy2a yy2b yy2c]);
legend(["C0";"by_nan";"by_zero"]);
subplot(2,2,4)
plot2d(xx2,[yy2d yy2e yy2f]);
title("RungeFun");
legend(["natural";"linear";"periodic"]);

