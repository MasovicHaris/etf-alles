import numpy as np
import random as random
import math

def okolina(x0, delta_x, opseg):
    okolo = []
    for dx0 in [x0[0] - delta_x, x0[0], x0[0] + delta_x]:
        for dx1 in [x0[1] - delta_x, x0[1], x0[1] + delta_x]:
            if  (dx0 != x0[0] or dx1 != x0[1]) and dx0 >= opseg[0] and dx0 <= opseg[1] and dx1 >= opseg[0] and dx1 <= opseg[1]:
                okolo.append((dx0, dx1))
    return okolo
            


def SA(f, opseg, x0, delta_x, N, eps, T0):
    M = 1000
    alfa = 0.96
    najboljeX = x0
    x = x0
    v = f(x)
    tk = T0
    for iter in range(0, N):
        for m in range(0, M):
            okolo = okolina(x, delta_x, opseg)
            xp = random.choice(okolo)
            vp = f(xp)
            pa = math.e ** (-abs(vp - v)/tk)
            r = random.uniform(0, 1)
            if r < pa or vp <= v:
                x = xp
                v = vp
            if f(najboljeX) >= f(xp):
                najboljeX = xp
        tk *= alfa
    return najboljeX
    

import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
T = 0.1
brojIt = 100

def f(X):
    return (X[0]-3)**2 + (X[1]+1)**2
x1 = np.linspace(-6, 6, 100)
x2 = np.linspace(-6, 6, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
fig = plt.figure()
ax = fig.add_subplot(2,2,1,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = SA(f, [-5, 5], (-5, 5), 0.1, brojIt, 0, T)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = (x_1-3)^2 + (x_2+1)^2$')

def f(x):
    return 20 + (x[0]**2 - 10*np.cos(2*math.pi*x[0])) + (x[1]**2 - 10*np.cos(2*math.pi*x[1]))
x1 = np.linspace(-6, 6, 100)
x2 = np.linspace(-6, 6, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,2,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = SA(f, [-5.12, 5.12], (-5.12, 5.12), 0.1, brojIt, 0, T)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = 20 + (x_1^2 - 10cos(2\pi x_1) + (x_2^2 - 10cos(2\pi x_2)$')

def f(X):
    return -(1+np.cos(12*np.sqrt(X[0]**2 + X[1]**2)))/ (0.5*(X[0]**2 + X[1]**2) + 2)
x1 = np.linspace(-6, 6, 100)
x2 = np.linspace(-6, 6, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,3,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = SA(f, [-5.12, 5.12], (-5.12, 5.12), 0.1, brojIt, 0, T)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = -({1+\cos{(12\sqrt{x_1^2+x_2^2})}})/({0.5(x_1^2+x_2^2)+2})$')


def f(x):
    return -abs(np.sin(x[0]) * np.cos(x[1]) * np.exp(abs(1 - np.sqrt(x[0]**2 + x[1]**2)/math.pi)))
x1 = np.linspace(-10, 10, 100)
x2 = np.linspace(-10, 10, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,4,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = SA(f,[-10, 10], (0, 0), 0.1, brojIt, 0, T)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = -|\sin(x_1)|\cos(x_2)e^{|1 - \sqrt{x_1^2+x_2^2}/\pi|}$')

plt.show() 