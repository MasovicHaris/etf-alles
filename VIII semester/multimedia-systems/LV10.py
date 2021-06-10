# Masovic Haris
# Lab 10 - 1689/17993

import numpy as np
import math as m
import matplotlib.image as pltimg
import matplotlib.pyplot as plt

# prva slika, u istom direktoriju slika
slika = pltimg.imread('lena1.png')
plt.subplot(3, 1, 1)
plt.imshow(slika, cmap='gray')

# definisanje broja tacaka po x i po y
broj_pixela_x = 30
broj_pixela_y = 30

# r filter proizvoljan
r_vrijednost = 0.05

def dajAlfuPQ(p_or_q, dots):
    return 1 / m.sqrt(dots) if p_or_q == 0 else m.sqrt(2 / dots)

def dajBPQ(A, p, q):
    s = 0
    for m in range(0, broj_pixela_x - 1):
        for n in range(0, broj_pixela_y - 1):
            s = s + A[m][n] * np.cos(np.pi * (2 * m + 1) * p / (2 * broj_pixela_x)) \
                * np.cos(np.pi * (2 * n + 1) * q / (2 * broj_pixela_y))
                
    return s * dajAlfuPQ(p, broj_pixela_x) * dajAlfuPQ(q, broj_pixela_y)

def dajAMN(B, m, n):
    s = 0
    for p in range(0, broj_pixela_x - 1):
        for q in range(0, broj_pixela_y - 1):
            s = s + dajAlfuPQ(p, broj_pixela_x) * dajAlfuPQ(q, broj_pixela_y) * B[p][q] \
                * np.cos(np.pi * (2 * m + 1) * p / (2 * broj_pixela_x)) \
                * np.cos(np.pi * (2 * n + 1) * q / (2 * broj_pixela_y))

    return s

dct = []

for i in range(0, broj_pixela_x - 1):
    dct.append([])
    for j in range(0, broj_pixela_y - 1):
        dct[i].append(0)

for p in range(0, broj_pixela_x - 1):
    for q in range(0, broj_pixela_y - 1):
        b = dajBPQ(slika, p, q)

        if m.fabs(b) >= r_vrijednost:
            dct[p][q] = b

# dct slika
plt.subplot(3, 1, 2)
plt.imshow(dct, cmap='gray')

inverzna = []

for i in range(0, broj_pixela_x - 1):
    inverzna.append([])
    
    for j in range(0, broj_pixela_y - 1):
        inverzna[i].append(0)

for i in range(0, broj_pixela_x - 1):
    for n in range(0, broj_pixela_y - 1):
        inverzna[i][n] = dajAMN(dct, i, n)

# inverzna dct
plt.subplot(3, 1, 3)
plt.imshow(inverzna, cmap='gray')
plt.show()