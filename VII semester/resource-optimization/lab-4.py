import math
import numpy as np
import random

def xinlist(lista, x):
    for y in lista:
        if ((x[0]-y[0])**2 + (x[1]-y[1])**2) < 1e-6:
            return True
        

def TS(f, x0, delta_x, N, eps, L, opseg):
    tabooList = []
    i = 0
    prevF = math.inf
    minx0 = x0
    miny0 = f(x0)
    while i < N and abs(prevF - f(x0)) >= eps:
        prevF = f(x0)
        novoX = (0, 0)
        novoF = math.inf
        for dx0 in [x0[0] - delta_x, x0[0], x0[0] + delta_x]:
            for dx1 in [x0[1] - delta_x, x0[1], x0[1] + delta_x]:
                if dx0 >= opseg[0] and dx0 <= opseg[1] and dx1 >= opseg[0] and dx1 <= opseg[1] and (dx0, dx1) != x0 and (dx0, dx1) not in tabooList and novoF > f((dx0, dx1)):
                    novoX = (dx0, dx1)
                    novoF = f((dx0, dx1))
                    if novoF < miny0:
                        miny0 = novoF
                        minx0 = (dx0, dx1)
        if novoF < math.inf:
            x0 = novoX
            tabooList.append(x0)
            if len(tabooList) > L:
                tabooList.pop(0)
        i += 1
        x0 = novoX
    return minx0

   
def LS(f, x0, delta_x, N, eps):
    i = 0
    prevF = math.inf
    while i < N and abs(prevF - f(x0)) > eps:
        prevF = f(x0)
        novoX = (x0[0] + delta_x, x0[1])
        for dx0 in [x0[0] - delta_x, x0[0], x0[0] + delta_x]:
            for dx1 in [x0[1] - delta_x, x0[1], x0[1] + delta_x]:
                if f(novoX) > f((dx0, dx1)):
                    novoX = (dx0, dx1)
        i += 1
        x0 = novoX
    return x0
def ILS(f, x0, delta_x, N, eps, M):
    omega = []
    def AzuriranjeMemorije(x):
        omega.append(x)
        return omega
    def Perturbacija():
        a, b = -1, 1
        x = (random.uniform(a, b), random.uniform(a, b))
        while x in omega:
            x = (random.uniform(a, b), random.uniform(a, b))
        return x
    xz = LS(f, x0, delta_x, N, eps)
    AzuriranjeMemorije(xz)
    for iter in range(1, M):
        x = Perturbacija()
        xz = LS(f, x, delta_x, N, eps)
        AzuriranjeMemorije(xz)
        AzuriranjeMemorije(x)
    xmin = omega[0]
    for x in omega:
        if f(x) < f(xmin):
            xmin = x
    return xmin

DTL = 10000

import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

def f(X):
    return (X[0]-3)**2 + (X[1]+1)**2
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
fig = plt.figure()
ax = fig.add_subplot(2,2,1,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = TS(f, (1, 1), 0.1, 5000, 0, DTL, [-5, 5])
xILS = ILS(f, (1, 1), 0.1, 1000, 0, 5)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = (x_1-3)^2 + (x_2+1)^2$')

def f(X):
    return (1-X[0])**2 + 100*(X[1] - X[0]**2)**2
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,2,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = TS(f, (1, 1), 0.1, 5000, 0, DTL, [-5, 5])
xILS = ILS(f, (1, 1), 0.1, 1000, 0, 5)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = (1-x_1)^2+100(x_2-x_1^2)^2$')

def f(x):
    return 20 + (x[0]**2 - 10*np.cos(2*math.pi*x[0])) + (x[1]**2 - 10*np.cos(2*math.pi*x[1]))
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,3,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = TS(f, (3, 3), 0.1, 1000, 0, 100, [-6, 6])
xILS = ILS(f, (5, 5), 0.1, 1000, 0, 5)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = 20 + (x_1^2 - 10cos(2\pi x_1) + (x_2^2 - 10cos(2\pi x_2)$')

def f(x):
    return -abs(np.sin(x[0]) * np.cos(x[1]) * np.exp(abs(1 - np.sqrt(x[0]**2 + x[1]**2)/math.pi)))
x1 = np.linspace(-11, 11, 100)
x2 = np.linspace(-11, 11, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,4,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = TS(f, (0, 0), 0.1, 30000, 0, 1000, [-11, 11])
xILS = ILS(f, (1, 1), 0.1, 1000, 0, 5)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = -|\sin(x_1)|\cos(x_2)e^{|1 - \sqrt{x_1^2+x_2^2}/\pi|}$')

plt.show()