import random as r
import numpy as np
import math
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d


numOfParticles = 100


def PSO(f, opseg, brojIteracija, eps, P):
    x = []
    v = []
    for i in range(0, numOfParticles):
        x.append([r.uniform(*opseg), r.uniform(*opseg)])
        v.append([r.uniform(*opseg), r.uniform(*opseg)])
    bests = x
    best = x[0]
    for c in x:
        if f(c) < f(best):
            best = c
    for iteracija in range(0, brojIteracija):
        for i in range(0, numOfParticles):
            r1 = r.uniform(0, 1)
            r2 = r.uniform(0, 1)
            v0 = P[0] * v[i][0] + P[1]*r1 * (bests[i][0] - x[i][0]) + P[2]*r2 * (best[0] - x[i][0])
            v1 = P[0] * v[i][1] + P[1]*r1 * (bests[i][1] - x[i][1]) + P[2]*r2 * (best[1] - x[i][1])
            v[i] = (v0, v1)
            x[i] = (max(opseg[0], min(opseg[1], x[i][0] + v0)), max(opseg[0], min(opseg[1], x[i][1] + v1)))
            if f(x[i]) < f(bests[i]):
                bests[i] = x[i]
            if f(x[i]) < f(best):
                best = x[i]
    print(best) 
    return best        
        
def f(x):
    return (x[0] - 10)**2 + (x[1] - 10)**2
PSO(f, [-50, 50], 10, 0.0001, [0.7, 1.47, 1.47])
        
        
IT = 150
a = 1.1
eps = 0.0001
P = [0.7, 1.47, 1.47]

def f(X):
    return (X[0]-3)**2 + (X[1]+1)**2
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
fig = plt.figure()
ax = fig.add_subplot(2,2,1,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = PSO(f, [-5, 5], IT, eps, P)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = (x_1-3)^2 + (x_2+1)^2$')

def f(X):
    return -(1+np.cos(12*np.sqrt(X[0]**2 + X[1]**2)))/ (0.5*(X[0]**2 + X[1]**2) + 2)
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,2,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = PSO(f, [-5, 5], IT, eps, P)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
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
xTS = PSO(f, [-5, 5], IT, eps, P)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = 20 + (x_1^2 - 10cos(2\pi x_1) + (x_2^2 - 10cos(2\pi x_2)$')

def f(x):
    return -abs(np.sin(x[0]) * np.cos(x[1]) * np.exp(abs(1 - np.sqrt(x[0]**2 + x[1]**2)/math.pi)))
x1 = np.linspace(-10, 10, 100)
x2 = np.linspace(-10, 10, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,4,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = PSO(f, [-10, 10], IT, eps, P)
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = -|\sin(x_1)|\cos(x_2)e^{|1 - \sqrt{x_1^2+x_2^2}/\pi|}$')

plt.show()

        
        
        
        
        
        
        