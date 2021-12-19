# -*- coding: utf-8 -*-
import numpy
import math
import matplotlib.pyplot as plot

def NewtonRaphson(f, df, ddf, x0, N, eps):
    brojIteracija = 0
    dx = math.inf
    while brojIteracija < N and dx >= eps:
        fx1 = f(x0)
        x0 = x0 - df(x0) / ddf(x0)
        dx = abs(fx1 - f(x0))
        brojIteracija += 1
    return (x0, f(x0))

f1 = lambda x: 3*x*x - 1
df1 = lambda x: 6*x
ddf1 = lambda x: 6

f2 = lambda x: -(16*x*x - 24*x + 5) * (math.e ** (-x))
df2 = lambda x: (16*x*x - 56*x + 29) * (math.e ** (-x))
ddf2 = lambda x: -(16*x*x - 88*x + 85) * (math.e ** (-x))

f3 = lambda x: math.sin(x) + math.sin(10/3*x)
df3 = lambda x: math.cos(x) + 10*math.cos(10/3*x)/3
ddf3 = lambda x: -math.sin(x) - 100*math.sin(10/3*x)/9

f4 = lambda x: math.e ** (-x)
df4 = lambda x: - (math.e ** (-x))
ddf4 = lambda x: math.e ** (-x)

x = input()
print(x)
ITER = 5
eps = 0
if x == "1":
    x = numpy.arange(-5, 5, 0.01)
    y = list(map(f1, x))
    plot.figure()
    plot.plot(x,y,'black')
    M1 = NewtonRaphson(f1, df1, ddf1, 1, ITER, eps)
    M2 = NewtonRaphson(f1, df1, ddf1, 10, ITER, eps)
    plot.plot([M1[0], M2[0]], [M1[1], M2[1]], 'go')
    plot.plot([0], [-1], 'r^')
    plot.grid(True)
    plot.xlabel('x')
    plot.ylabel('3x^2-1')
    plot.show()
elif x == "2":
    x = numpy.arange(-1, 5, 0.01)
    y = list(map(f2, x))
    plot.figure()
    plot.plot(x,y,'black')
    M1 = NewtonRaphson(f2, df2, ddf2, 0.5, ITER, eps)
    M2 = NewtonRaphson(f2, df2, ddf2, 3.5, ITER, eps)
    plot.plot([M1[0], M2[0]], [M1[1], M2[1]], 'go')
    plot.plot([0.632, 2.868], [2.008, -3.85], 'r^')
    plot.grid(True)
    plot.xlabel('x')
    plot.ylabel('-(16*x*x - 24*x + 5) * (math.e ** (-x))')
    plot.show()
elif x == "3":
    x = numpy.arange(-2, 8.5, 0.01)
    y = list(map(f3, x))
    plot.figure()
    plot.plot(x,y,'black')
    M1 = NewtonRaphson(f3, df3, ddf3, 3, ITER, eps)
    M2 = NewtonRaphson(f3, df3, ddf3, 6, ITER, eps)
    M3 = NewtonRaphson(f3, df3, ddf3, 7, ITER, eps)
    plot.plot([M1[0], M2[0], M3[0]], [M1[1], M2[1], M3[1]], 'go')
    plot.plot([-1.398, -0.549, 0.549, 1.398, 2.296, 3.387, 4.197, 5.146, 6.217, 7, 8],[0.014, -1.488, 1.488, -0.014, 1.728, -1.2, 0.119, -1.9, 0.888, -0.317, 1.989],'r^')
    plot.grid(True)
    plot.xlabel('x')
    plot.ylabel('sin(x) + sin(10*x/3')
    plot.show()
elif x == "4":
    x = numpy.arange(-5, 15, 0.01)
    y = list(map(f4, x))
    plot.figure()
    plot.plot(x,y,'black')
    M1 = NewtonRaphson(f4, df4, ddf4, 1, ITER, eps)
    M2 = NewtonRaphson(f4, df4, ddf4, 10, ITER, eps)
    plot.plot([M1[0], M2[0]], [M1[1], M2[1]], 'go')
    plot.plot([], [], 'r^')
    plot.grid(True)
    plot.xlabel('x')
    plot.ylabel('e^(-x)')
    plot.title('e^(-x)')
    plot.show()

