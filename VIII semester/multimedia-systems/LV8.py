# Masovic Haris
# Lab 8 - 1689/17993

import math as mth
import matplotlib.pyplot as plt
import numpy as np


def function(t):
    return np.sin(2 * np.pi * 5 * t) + 6 * np.sin(2 * np.pi * 10 * t) + 2 * np.sin(2 * np.pi * 20 * t)


def odziv_impulsni(fc, M, m):
    return np.sin(2 * mth.pi * fc * (m - M / 2.0)) / (mth.pi * (m - M / 2.0))


fc = 15
M = 1
x = np.arange(-1, 1, 0.01)
m = np.arange(-1, 1, 0.01)

h = odziv_impulsni(fc, M, m)
h2 = np.convolve(function(x), h, 'same')

# f(x)
plt.subplot(6, 1, 1)
plt.plot(x, function(x))

# fft f(x)
h1 = abs(np.fft.fft(x))
plt.subplot(6, 1, 2)
plt.stem(x, h1, use_line_collection = True)
plt.axis([min(x), max(x), min(h1), max(h1)])

# conv h
plt.subplot(6, 1, 3)
plt.plot(m, h2)

# fft conv h
c = abs(np.fft.fft(h2))
plt.subplot(6, 1, 4)
plt.stem(m, c, use_line_collection = True)
plt.axis([min(m), max(m), min(c), max(c)])

# impulsni
plt.subplot(6, 1, 5)
plt.plot(m, h)

# fft impulsni
a = abs(np.fft.fft(h))
plt.subplot(6, 1, 6)
plt.stem(m, a, use_line_collection = True)
plt.axis([min(m), max(m), min(a), max(a)])


plt.show()
