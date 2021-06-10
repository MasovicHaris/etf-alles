# Masovic Haris
# Lab 7 - 1689/17993
import math as m
import numpy as np
import matplotlib.pyplot as plt


def zadanaSinusFunc(x):
    return m.sin(2 * m.pi * 5 * x) + 6 * m.sin(2 * m.pi * 10 * x) + 2 * m.sin(2 * m.pi * 20 * x)


def nadjiFFT(x):
    f = []
    for i in range(0, len(x)):
        f.append(zadanaSinusFunc(x[i]))

    even = []
    odd = []
    X = []
    N = len(x)
    for i in range(0, N):
        X.append(complex(0.0))
        even.append(complex(0.0))
        odd.append(complex(0.0))
        
        for j in range(0, int(N / 2)):
            omega = (m.e ** ((-2j * m.pi * j * i) / (N / 2)))
            even[i] += f[2 * j] * omega
            odd[i] += f[(2 * j) + 1] * omega * (m.e ** (-2j * m.pi * i / N))
        
        X[i] = abs(even[i] + odd[i])
        X[i] /= 100

    return X


x = [i for i in np.arange(0, 1, 0.01)]

f = []
for i in range(0, len(x)):
    f.append(zadanaSinusFunc(x[i]))

fft = nadjiFFT(x)
X = [i for i in np.arange(0, len(fft), 1)]

plt.figure(1)
plt.subplot(211)
plt.plot(x, f)
plt.ylabel('f')
plt.xlabel('t')
plt.axis([0, 1, min(f) - 1, max(f) + 1])

plt.subplot(212)
plt.stem(X[0:80], fft[0:80], use_line_collection = True)
plt.ylabel('|Y(f)|')
plt.xlabel('f (Hz)')
plt.axis([min(X), max(X), min(fft), max(fft) + 0.5])

plt.show()
