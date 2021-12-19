import numpy as np
import math
import random

def f(x):
    return (x[0]-3)**2 + (x[1]+1)**2

class ES:
    def __init__(self, MaxIter, a, sigma0, f):
        self.MaxIter = MaxIter
        self.f = f
        self.a = a
        self.sigma = 0.4
        self.sigma0 = sigma0
        self.P_S = 0
        self.x = [2, 2]
        self.eps = 0.0001
        self.brojUspjesnih = 0
        self.brojIter = 0
    
    def mutate(self):
        x = [min(max(self.x[0] + self.sigma0[0][0] * random.gauss(0, self.sigma), -10), 10), min(max(self.x[1] + self.sigma0[1][1] * random.gauss(0, self.sigma), -10), 10)]                
        print(x, end = ' ')
        if abs(x[0]) >= 10 or abs(x[1]) >= 10:
            x = [random.uniform(-10,10), random.uniform(-10, 10)]
        return x
    def step(self):
        xn = self.mutate()
        if self.f(xn) <= self.f(self.x):
            self.x = xn
            self.brojUspjesnih += 1
        if self.P_S > 1/5:
            self.sigma0[0][0] *= self.a
        elif self.P_S < 1/5:
            self.sigma0[1][1] /= self.a
        self.brojIter += 1
        self.P_S = self.brojUspjesnih / self.brojIter
    
    def run(self):
        for i in range(0, self.MaxIter):
            self.step()
        print('')
        return self.x    

# print((ES(100, 1.47, [[1, 0], [0, 1]], f).run()))




import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

IT = 15
a = 1.1
S = [[0.5, 0], [0, 0.5]]
def f(X):
    return (X[0]-3)**2 + (X[1]+1)**2
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
fig = plt.figure()
ax = fig.add_subplot(2,2,1,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = ES(IT, a, S, f).run()
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = (x_1-3)^2 + (x_2+1)^2$')
print((ES(IT, a, S, f).run()))

def f(X):
    return -(1+np.cos(12*np.sqrt(X[0]**2 + X[1]**2)))/ (0.5*(X[0]**2 + X[1]**2) + 2)
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,2,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = ES(IT, a, S, f).run()
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = (1-x_1)^2+100(x_2-x_1^2)^2$')
print((ES(IT, a, S, f).run()))

def f(x):
    return 20 + (x[0]**2 - 10*np.cos(2*math.pi*x[0])) + (x[1]**2 - 10*np.cos(2*math.pi*x[1]))
x1 = np.linspace(-5, 5, 100)
x2 = np.linspace(-5, 5, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,3,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = ES(IT, a, S, f).run()
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = 20 + (x_1^2 - 10cos(2\pi x_1) + (x_2^2 - 10cos(2\pi x_2)$')
print((ES(IT, a, [[0.5, 0], [0, 0.5]], f).run()))

def f(x):
    return -abs(np.sin(x[0]) * np.cos(x[1]) * np.exp(abs(1 - np.sqrt(x[0]**2 + x[1]**2)/math.pi)))
x1 = np.linspace(-11, 11, 100)
x2 = np.linspace(-11, 11, 100)
X1, X2 = np.meshgrid(x1, x2)
Y = f([X1, X2])
ax = fig.add_subplot(2,2,4,projection='3d')
ax.contour(X1, X2, Y, 50, cmap='binary')
xTS = ES(IT, a, S, f).run()
ax.scatter(xTS[0], xTS[1], f(xTS), color='blue', marker='o')
# ax.scatter(xILS[0], xILS[1], f(xILS), color='green', marker='x')
ax.set_xlabel('$x_1$')
ax.set_ylabel('$x_2$')
ax.set_zlabel('$f(x_1,x_2)$');
ax.set_title('$f(x_1,x_2) = -|\sin(x_1)|\cos(x_2)e^{|1 - \sqrt{x_1^2+x_2^2}/\pi|}$')
print((ES(IT, a, S, f).run()))

plt.show()
