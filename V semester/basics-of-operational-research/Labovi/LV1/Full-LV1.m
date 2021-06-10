% Amir Muminovic - 17744
% Haris Masovic - 17993

% Prvi
3 * (456/23) + 31.54 + 2^6  %a
sqrt(2) * log(10)           %b
sin(pi/7) * exp(0.3) * (2 + 0.9i) %c
(5+3i)/(1.2+4.5i) %d

%Drugi
a = (atan(5) + exp(5.6))/3 
b = (sin(pi/3))^(1/15)
c = (log(15)+1) / 23
d = sin(pi/2) + cos (pi)

(a+b) * c %a
acos(a) * asin(b/11) %b
(a-b)^4/d %c
nthroot(c,a) + (b*i)/(3+2i) %d

%Treci
A = [ 1 -4*i sqrt(2)
    log(-1) sin(pi/2) cos(pi/3)
    asin(0.5) acos(0.8) exp(0.8)
    ]

A.' %a
A + A.' %b
A * A.' %c
A.' * A %d
det(A) %e
pinv(A) %f

%Cetvrti
zeros(8,9) %a
ones(7,5) %b
eye(5) %c
magic(5) %d

%Peti
%a
magicna = magic(5)
sum(magicna, 1)
sum(magicna, 2)
trace(magicna)
trace(magicna.')

%b
magicna = (magic(4) * 100) / 34
sum(magicna, 1)
sum(magicna, 2)
trace(magicna)
trace(magicna.')


%Sesti
a = [ 1 2 3
      4 5 6
      7 8 9
    ]

b = [ 1 1 1
      2 2 2 
      3 3 3
    ]

c = sin(a) %a
c = sin(a) .* cos(b) %b

a = [ 1 8 27
      1 8 27
      1 8 64
    ]

c = a^(1/3) %c
c = a.^(1/3) %d

%Sedmi
v = [0:99];
v = [0:0.01:0.99]
v = ([1:2:39])'

%Osmi
a = [ones(4)*7 zeros(4); 3*ones(4,8)]
b = magic(8) * a
c = b(1:2:end,:)
d = b(:,1:2:end)
e = b(1:2:end, 1:2:end)

%%Fje za crtanje

%Prvi
%a
x = linspace(-pi, pi, 101);
y = sin(x);
figure
plot(x,y)
grid on
title('y = sin(x)')
xlabel('x')
ylabel('y')

%b
x = linspace(-pi, pi, 101);
y = cos(x);
figure
plot(x,y)
grid on
title('y = cos(x)')
xlabel('x')
ylabel('y')

%c
x = linspace(-3, 3, 1001);
y = sin(1./x);
figure
plot(x,y, 'k-')
grid on
title('y = sin(1/x)')
xlabel('x')
ylabel('y')

%d
x1 = linspace(-3, 3, 1001);
y1 = sin(1./x1);

x2 = linspace(-3, 3, 101);
y2 = sin(1./x2);

figure
plot(x1,y1, 'k-')
hold on
plot(x2,y2, 'bo')
grid on
title('y = sin(1/x)')
xlabel('x')
ylabel('y')

%e
x1 = linspace(-pi, pi, 101);
y1 = sin(x1);
x2 = linspace(-pi, pi, 101);
y2 = cos(x2);

figure
plot(x1,y1, 'yp')
hold on
plot(x,y, 'c+')
grid on
title('y = sin(x) i y = cos(x)')
xlabel('x')
ylabel('y')
legend('sin(x)', 'cos(x)')

% Drugi - plotting

x = -8:0.5:8;
y = x;
[X,Y] = meshgrid(x,y);

Z=sin(sqrt(X.^2+Y.^2))./sqrt(X.^2+Y.^2);

figure

subplot(2,2,1)
mesh(X,Y,Z)
axis([-10 10 -10 10 -0.5 1])
grid on 
xlabel('x')
ylabel('y')
zlabel('z')
title('mesh funkcija')


subplot(2,2,2)
surf(X,Y,Z)
axis([-10 10 -10 10 -0.5 1])
grid on
xlabel('x')
ylabel('y')
zlabel('z')
title('surf funkcija')

subplot(2,2,3)
contour3(X,Y,Z, 50)
axis([-10 10 -10 10 -0.5 1])
grid on 
xlabel('x')
ylabel('y')
zlabel('z')
title('contour3 funkcija')

subplot(2,2,4)
contour(X,Y,Z, 50)
axis([-10 10 -10 10])
grid on
xlabel('x')
ylabel('y')
zlabel('z')
title('contour funkcija')



