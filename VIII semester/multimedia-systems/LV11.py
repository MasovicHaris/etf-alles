# Masovic Haris
# Lab 11 - 1689/17993

import numpy as np
import math as m
import matplotlib.image as pltimg
import matplotlib.pyplot as plt

# prva slika, u istom direktoriju slika

slika = pltimg.imread('LV11.png')

# definisanje broja tacaka po x i po y

broj_pixela_x = 32
broj_pixela_y = 32

# r filter proizvoljan

r_vrijednost = 0.05


def dajAlfuPQ(p_or_q, dots):
    return (1 / m.sqrt(dots) if p_or_q == 0 else m.sqrt(2 / dots))


def dajBPQ(A, p, q):
    s = 0
    for m in range(0, broj_pixela_x - 1):
        for n in range(0, broj_pixela_y - 1):
            s = s + A[m][n] * np.cos(np.pi * (2 * m + 1) * p / (2
                    * broj_pixela_x)) * np.cos(np.pi * (2 * n + 1) * q
                    / (2 * broj_pixela_y))

    return s * dajAlfuPQ(p, broj_pixela_x) * dajAlfuPQ(q, broj_pixela_y)


def dajAMN(
    B,
    m,
    n,
    a,
    b,
    ):
    s = 0
    for p in range(0, a + 1):
        for q in range(0, b + 1):
            s = s + dajAlfuPQ(p, broj_pixela_x) * dajAlfuPQ(q,
                    broj_pixela_y) * B[p][q] * np.cos(np.pi * (2 * m
                    + 1) * p / (2 * broj_pixela_x)) * np.cos(np.pi * (2
                    * n + 1) * q / (2 * broj_pixela_y))

    return s


def dajDijagonalaAMN(B, m, n):
    s = 0
    for p in range(0, broj_pixela_x - 1):
        for q in range(0, broj_pixela_y - 1):
            if p == q:
                s = s + dajAlfuPQ(p, broj_pixela_x) * dajAlfuPQ(q,
                        broj_pixela_y) * B[p][q] * np.cos(np.pi * (2
                        * m + 1) * p / (2 * broj_pixela_x)) \
                    * np.cos(np.pi * (2 * n + 1) * q / (2
                             * broj_pixela_y))

    return s


def dajDCT(slikica, g, end):
    dct = [[0 for x in range(g - 1)] for y in range(end - 1)]

    for p in range(0, g - 1):
        for q in range(0, end - 1):
            delta = dajBPQ(slikica, p, q)
            dct[p][q] = delta

    return dct


#######################################################  1 Zadatak ################################################################

f1_dct = dajDCT(slika, broj_pixela_x, broj_pixela_y)
f1_idct1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f1_idct2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f1_idct3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f1_idct4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f1_idct5 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f1_idct6 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f1_idct7 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

for x in range(0, broj_pixela_x - 1):
    for y in range(0, broj_pixela_y - 1):
        f1_idct1[x][y] = dajAMN(f1_dct, x, y, broj_pixela_x - 2, broj_pixela_y - 2)
        f1_idct2[x][y] = dajAMN(f1_dct, x, y, 0, broj_pixela_y - 2)
        f1_idct3[x][y] = dajAMN(f1_dct, x, y, broj_pixela_x - 2, 0)
        f1_idct4[x][y] = dajDijagonalaAMN(f1_dct, x, y)
        f1_idct5[x][y] = dajAMN(f1_dct, x, y, 3, 3)
        f1_idct6[x][y] = dajAMN(f1_dct, x, y, 8, 8)
        f1_idct7[x][y] = dajAMN(f1_dct, x, y, 16, 16)


# original

plt.figure(1)
plt.subplot(3, 3, 1)
plt.imshow(slika, cmap='gray')

# dct originala

plt.subplot(3, 3, 2)
plt.imshow(f1_dct, cmap='gray')

# inverzna dct

plt.subplot(3, 3, 3)
plt.imshow(f1_idct1, cmap='gray')

# inverzna samo prvi red

plt.subplot(3, 3, 4)
plt.imshow(f1_idct2, cmap='gray')

# inverzna samo prva kolona

plt.subplot(3, 3, 5)
plt.imshow(f1_idct3, cmap='gray')

# inverzna samo dijagonala

plt.subplot(3, 3, 6)
plt.imshow(f1_idct4, cmap='gray')

# prve 8 bazne

plt.subplot(3, 3, 7)
plt.imshow(f1_idct5, cmap='gray')

# prve 16 bazne

plt.subplot(3, 3, 8)
plt.imshow(f1_idct6, cmap='gray')

# prve 3 bazne

plt.subplot(3, 3, 9)
plt.imshow(f1_idct7, cmap='gray')

plt.show()

#######################################################  2 Zadatak ################################################################

prva_cetvrtina = slika[0:16, 0:16]
druga_cetvrtina = slika[0:16, 16:32]
treca_cetvrtina = slika[16:32, 0:16]
cetvrta_cetvrtina = slika[16:32, 16:32]

gornji_dio = np.concatenate((prva_cetvrtina, druga_cetvrtina), axis=1)
donji_dio = np.concatenate((treca_cetvrtina, cetvrta_cetvrtina), axis=1)
citava_slika = np.concatenate((gornji_dio, donji_dio), axis=0)

broj_pixela_x = 16
broj_pixela_y = 16

f2_dct1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_dct2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_dct3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_dct4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_dct1 = dajDCT(prva_cetvrtina, broj_pixela_x, broj_pixela_y)
f2_dct2 = dajDCT(druga_cetvrtina, broj_pixela_x, broj_pixela_y)
f2_dct3 = dajDCT(treca_cetvrtina, broj_pixela_x, broj_pixela_y)
f2_dct4 = dajDCT(cetvrta_cetvrtina, broj_pixela_x, broj_pixela_y)

gornji_dio = np.concatenate((f2_dct1, f2_dct2), axis=1)
donji_dio = np.concatenate((f2_dct3, f2_dct4), axis=1)
f2_dct = np.concatenate((gornji_dio, donji_dio), axis=0)

f2_idct1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct1_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct1_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct1_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct1_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_idct2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct2_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct2_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct2_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct2_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_idct3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct3_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct3_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct3_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct3_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_idct4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct4_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct4_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct4_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct4_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_idct5 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct5_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct5_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct5_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct5_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_idct6 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct6_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct6_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct6_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct6_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

f2_idct7 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct7_1 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct7_2 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct7_3 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))
f2_idct7_4 = np.zeros((broj_pixela_x - 1, broj_pixela_y - 1))

for x in range(0, broj_pixela_x - 1):
    for y in range(0, broj_pixela_y - 1):

        f2_idct1_1[x][y] = dajAMN(f2_dct1, x, y, broj_pixela_x - 2, broj_pixela_y - 2)
        f2_idct1_2[x][y] = dajAMN(f2_dct2, x, y, broj_pixela_x - 2, broj_pixela_y - 2)
        f2_idct1_3[x][y] = dajAMN(f2_dct3, x, y, broj_pixela_x - 2, broj_pixela_y - 2)
        f2_idct1_4[x][y] = dajAMN(f2_dct4, x, y, broj_pixela_x - 2, broj_pixela_y - 2)

        f2_idct2_1[x][y] = dajAMN(f2_dct1, x, y, 0, broj_pixela_y - 2)
        f2_idct2_2[x][y] = dajAMN(f2_dct2, x, y, 0, broj_pixela_y - 2)
        f2_idct2_3[x][y] = dajAMN(f2_dct3, x, y, 0, broj_pixela_y - 2)
        f2_idct2_4[x][y] = dajAMN(f2_dct4, x, y, 0, broj_pixela_y - 2)

        f2_idct3_1[x][y] = dajAMN(f2_dct1, x, y, broj_pixela_x - 2, 0)
        f2_idct3_2[x][y] = dajAMN(f2_dct2, x, y, broj_pixela_x - 2, 0)
        f2_idct3_3[x][y] = dajAMN(f2_dct3, x, y, broj_pixela_x - 2, 0)
        f2_idct3_4[x][y] = dajAMN(f2_dct4, x, y, broj_pixela_x - 2, 0)

        f2_idct4_1[x][y] = dajDijagonalaAMN(f2_dct1, x, y)
        f2_idct4_2[x][y] = dajDijagonalaAMN(f2_dct2, x, y)
        f2_idct4_3[x][y] = dajDijagonalaAMN(f2_dct3, x, y)
        f2_idct4_4[x][y] = dajDijagonalaAMN(f2_dct4, x, y)

        f2_idct5_1[x][y] = dajAMN(f2_dct1, x, y, 3, 3)
        f2_idct5_2[x][y] = dajAMN(f2_dct2, x, y, 3, 3)
        f2_idct5_3[x][y] = dajAMN(f2_dct3, x, y, 3, 3)
        f2_idct5_4[x][y] = dajAMN(f2_dct4, x, y, 3, 3)

        f2_idct6_1[x][y] = dajAMN(f2_dct1, x, y, 5, 5)
        f2_idct6_2[x][y] = dajAMN(f2_dct2, x, y, 5, 5)
        f2_idct6_3[x][y] = dajAMN(f2_dct3, x, y, 5, 5)
        f2_idct6_4[x][y] = dajAMN(f2_dct4, x, y, 5, 5)

        f2_idct7_1[x][y] = dajAMN(f2_dct1, x, y, 8, 8)
        f2_idct7_2[x][y] = dajAMN(f2_dct2, x, y, 8, 8)
        f2_idct7_3[x][y] = dajAMN(f2_dct3, x, y, 8, 8)
        f2_idct7_4[x][y] = dajAMN(f2_dct4, x, y, 8, 8)

gornji_dio = np.concatenate((f2_idct1_1, f2_idct1_2), axis=1)
donji_dio = np.concatenate((f2_idct1_3, f2_idct1_4), axis=1)
f2_idct1 = np.concatenate((gornji_dio, donji_dio), axis=0)
gornji_dio = np.concatenate((f2_idct2_1, f2_idct2_2), axis=1)
donji_dio = np.concatenate((f2_idct2_3, f2_idct2_4), axis=1)
f2_idct2 = np.concatenate((gornji_dio, donji_dio), axis=0)
gornji_dio = np.concatenate((f2_idct3_1, f2_idct3_2), axis=1)
donji_dio = np.concatenate((f2_idct3_3, f2_idct3_4), axis=1)
f2_idct3 = np.concatenate((gornji_dio, donji_dio), axis=0)
gornji_dio = np.concatenate((f2_idct4_1, f2_idct4_2), axis=1)
donji_dio = np.concatenate((f2_idct4_3, f2_idct4_4), axis=1)
f2_idct4 = np.concatenate((gornji_dio, donji_dio), axis=0)
gornji_dio = np.concatenate((f2_idct5_1, f2_idct5_2), axis=1)
donji_dio = np.concatenate((f2_idct5_3, f2_idct5_4), axis=1)
f2_idct5 = np.concatenate((gornji_dio, donji_dio), axis=0)
gornji_dio = np.concatenate((f2_idct6_1, f2_idct6_2), axis=1)
donji_dio = np.concatenate((f2_idct6_3, f2_idct6_4), axis=1)
f2_idct6 = np.concatenate((gornji_dio, donji_dio), axis=0)
gornji_dio = np.concatenate((f2_idct7_1, f2_idct7_2), axis=1)
donji_dio = np.concatenate((f2_idct7_3, f2_idct7_4), axis=1)
f2_idct7 = np.concatenate((gornji_dio, donji_dio), axis=0)

plt.figure(2)
plt.subplot(3, 3, 1)
plt.imshow(citava_slika, cmap='gray')
plt.subplot(3, 3, 2)
plt.imshow(f2_dct, cmap='gray')

# inverzna dct

plt.subplot(3, 3, 3)
plt.imshow(f2_idct1, cmap='gray')

# inverzna samo prvi red

plt.subplot(3, 3, 4)
plt.imshow(f2_idct2, cmap='gray')

# inverzna samo prva kolona

plt.subplot(3, 3, 5)
plt.imshow(f2_idct3, cmap='gray')

# inverzna samo dijagonala

plt.subplot(3, 3, 6)
plt.imshow(f2_idct4, cmap='gray')

# prve 3 bazne

plt.subplot(3, 3, 7)
plt.imshow(f2_idct5, cmap='gray')

# prvih 5 baznih

plt.subplot(3, 3, 8)
plt.imshow(f2_idct6, cmap='gray')

# prvih 8 baznih

plt.subplot(3, 3, 9)
plt.imshow(f2_idct7, cmap='gray')

plt.show()