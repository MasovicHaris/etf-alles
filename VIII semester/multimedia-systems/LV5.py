import matplotlib.pyplot as plt
import math as m
import numpy as np

def firstFunction():
    N = 80
    x = [i for i in np.arange(0, 10, 0.01)]
    f = np.ones(len(x)) * 0.5
    omega = 1.0

    i = 1
    while i < N:
        a = 2.0 / (m.pi * i)
        for j in range(0, len(x)):
            f[j] += a * m.cos(i * omega * x[j])
        i = i + 4

    i = 3
    while i < N:
        a = -2.0 / (m.pi * i)
        for j in range(0, len(x)):
            f[j] += a * m.cos(i * omega * x[j])
        i += 4

    plt.plot(x, f)
    plt.ylabel('y osa')
    plt.xlabel('x osa')
    plt.axis([min(x), max(x), min(f), max(f)])
    plt.grid(True)
    plt.show()


def secondFunction():
    N = 80
    x = [i for i in np.arange(0, 10, 0.01)]
    f = np.ones(len(x)) * 0.75
    omega = 1.0
    for i in range(1, N):
        a = m.sin(i * m.pi / 2) / (i * m.pi)
        b = (m.cos(i * m.pi) + m.cos(i * m.pi / 2) - 2) / (i * m.pi)
        for j in range(0, len(x)):
            f[j] += a * m.cos(i * omega * x[j]) + b * m.sin(i * omega * x[j])

    plt.plot(x, f)
    plt.ylabel('y osa')
    plt.xlabel('x osa')
    plt.axis([min(x), max(x), min(f), max(f)])
    plt.grid(True)
    plt.show()

def thirdFunction():
    N = 80 
    x = [i for i in np.arange(0, 10, 0.01)]
    f = [2/m.pi]*1000 
    omega = 1.0
    for k in range(0, 1000):
        i = 2
        while i<N:
            a = -(4 / (m.pi * (i*i - 1)))
            f[k] = f[k] + a*m.cos(i*omega*x[k])
            i=i+2
        f[k] = f[k]+m.sin(omega*x[k]) 

    plt.plot(x, f)
    plt.ylabel('y osa')
    plt.xlabel('x osa')
    plt.axis([min(x), max(x), min(f), max(f)])
    plt.grid(True)
    plt.show()


firstFunction()
secondFunction()
thirdFunction()