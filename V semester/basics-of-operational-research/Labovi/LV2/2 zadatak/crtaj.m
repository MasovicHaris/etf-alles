
% crta funkciju koja se proslijedi stringom kao funkcija
% sasvim normalno napisati funkciju kao npr 'x+y'

function crtaj(funkcija)

X = linspace(-5, 5, 100);
Y = X;
[x,y] = meshgrid(X,Y);

z = eval(funkcija);

figure
mesh(x,y,z)
axis([-10 10 -10 10 -0.5 1])
grid on 
title(strcat('Grafik funkcije: ',funkcija));
xlabel('x');
ylabel('y');
zlabel('z');

end