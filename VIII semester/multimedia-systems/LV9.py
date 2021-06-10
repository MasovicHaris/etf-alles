# Masovic Haris
# Lab 9 - 1689/17993

import math as mth
import matplotlib.pyplot as plt
import numpy as np
import random


def funkcija_sa_sumom(t):
    return [3 * np.sin(2 * mth.pi * 5 * x) + random.randint(-200, 300) / 100 for x in t]

def funkcija_sa_sumom_2(t):
    return [3 * np.sin(2 * mth.pi * 5 * x) + 0.3 * np.sin(2 * mth.pi * 80 * x) for x in t]

def odziv_impulsni(fc, M, m):
    return np.sin(2 * mth.pi * fc * (m - M / 2.0)) / (mth.pi * (m - M / 2.0))


fc = 20
M = 1
x = np.arange(-1, 1, 0.001)
m = np.arange(-1, 1, 0.001)
N = 1000

h = odziv_impulsni(fc, M, m)
h2 = np.convolve(funkcija_sa_sumom(x), h, 'same')

fig, axs = plt.subplots(6, 2)

# f(x)
axs[0, 0].plot(x, funkcija_sa_sumom(x))

# fft f(x)
h1 = abs(np.fft.fft(funkcija_sa_sumom(x)))
axs[1, 0].stem(x, h1, use_line_collection = True)
axs[1, 0].set_xlim(0, N)
axs[1, 0].axis([min(x), max(x), min(h1), max(h1)])


# impulsni
axs[2, 0].plot(m, h)

# fft impulsni
a = abs(np.fft.fft(h))
axs[3, 0].stem(m, a, use_line_collection = True)
axs[3, 0].set_xlim(0, N)
axs[3, 0].axis([min(m), max(m), min(a), max(a)])

# conv h
axs[4, 0].plot(m, h2)

# fft conv h
c = abs(np.fft.fft(h2))
axs[5, 0].stem(m, c, use_line_collection = True)
axs[5, 0].set_xlim(0, N)
axs[5, 0].axis([min(m), max(m), min(c), max(c)])


# --------------- funkcija suma 2 ----

h2 = np.convolve(funkcija_sa_sumom_2(x), h, 'same')

# f(x)
axs[0, 1].plot(x, funkcija_sa_sumom_2(x))

# fft f(x)
h1 = abs(np.fft.fft(funkcija_sa_sumom_2(x)))
axs[1, 1].stem(x, h1, use_line_collection = True)
axs[1, 1].set_xlim(0, N)
axs[1, 1].axis([min(x), max(x), min(h1), max(h1)])


# impulsni
axs[2, 1].plot(m, h)

# fft impulsni
a = abs(np.fft.fft(h))
axs[3, 1].stem(m, a, use_line_collection = True)
axs[3, 1].set_xlim(0, N)
axs[3, 1].axis([min(m), max(m), min(a), max(a)])

# conv h
axs[4, 1].plot(m, h2)

# fft conv h
c = abs(np.fft.fft(h2))
axs[5, 1].stem(m, c, use_line_collection = True)
axs[5, 1].set_xlim(0, N)
axs[5, 1].axis([min(m), max(m), min(c), max(c)])


plt.show()
