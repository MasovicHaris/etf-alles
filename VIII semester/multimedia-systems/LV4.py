# Masovic Haris
# Lab 4 - 1689/17993
from math import log2


def lzw(dictionary, rijec):
    prijeRijec = ""
    kod = ""
    for i in range(0, len(rijec)):
        trenutno = rijec[i]
        spojeno = prijeRijec + trenutno
        if spojeno in dictionary:
            prijeRijec = spojeno
            continue
        duzina = len(dictionary)
        dictionary[spojeno] = duzina
        kod = kod + str(dictionary[prijeRijec]) + ","
        prijeRijec = trenutno

    kod = kod + str(dictionary[prijeRijec])
    return kod


def dekodiraj(string, dictionary):
    niz = [int(x) for x in string.split(',')]
    string = ""
    for i in range(0, len(niz)):
        for k, v in dictionary.items():
            if v == niz[i]:
                string = string + k
    return string


dictionary = {"#": 0, "A": 1, "B": 2, "C": 3, "D": 4, "E": 5, "F": 6, "G": 7, "H": 8, "I": 9, "J": 10, "K": 11, "L": 12,
              "M": 13, "N": 14, "O": 15, "P": 16, "Q": 17, "R": 18, "S": 19, "T": 20, "U": 21, "V": 22, "W": 23,
              "X": 24, "Y": 25, "Z": 26}

print('Rijecnik: ')
for k, v in dictionary.items():
    print('Simbol {}, Binarna vrijednost {}, Decimalna vrijednost {}'.format(k, int(bin(v)[2:]), v))

print('')
print('Za string BABAABBACABABB: ')
string = "BABAABBACABABB"
kodnovi = lzw(dictionary, string)
print('Rezultat kompresije: ', kodnovi)
kompresovano = kodnovi.split(',')
rez = dekodiraj(kodnovi, dictionary)
print('Konvertovano nazad: ', rez)

duzinaN = len(string) * 8
duzinaK = len(kompresovano) * (int(log2(len(dictionary))) + 1)

print("Stepen kompresije: ", format(duzinaN / duzinaK))
