clc
clear all
close all 
%%input circle radius and coordinate 
r=2;
c_x=7;
c_y=7;
%%position of the outer rectangle
p_x=c_x-r;
p_y=c_y-r;
pos=[p_x,p_y,r^2,r^2] 
%%random number generation within the sqaure
N=1000;
a=p_x;
b=p_x+(2*r);
x = a + (b-a).*rand(N,1);
y = a + (b-a).*rand(N,1);
radii = sqrt((x-c_x).^2+(y-c_y).^2);
i = radii <= r;
hits = sum(i);
misses = N-hits;
plot(x(i),y(i),'.g');
hold;
plot(x(~i),y(~i),'.r');
actual_a=22/7*r^2;
ttl = sprintf('Estimate Actual Area of circle: %1.3f, Area of the circle: %1.3f',actual_a,hits/N*(2*r)^2);
title(ttl);
axis equal
