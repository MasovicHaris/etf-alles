# LV3 - Masovic Haris
# 1689/17993

def nadjiUnikatne(string):
    znakovi = []
    nadjen = False
    znakovi.append(string[0])

    for i in range(1, len(string)):
        for j in range(0, len(znakovi)):
            if znakovi[j] == string[i]:
                nadjen = True
                break
        if not nadjen:
            znakovi.append(string[i])
        nadjen = False

    return znakovi


def izracunajPonavljanja(string, znakovi):
    ponavljanja = []

    for i in range(0, len(znakovi)):
        ponavljanja.append(0)

    for j in range(0, len(znakovi)):
        for i in range(0, len(string)):
            if string[i] == znakovi[j]:
                ponavljanja[j] = ponavljanja[j] + 1

    return ponavljanja


def sortiraj(znakovi, ponavljanja):
    indeksi = []

    for i in range(0, len(znakovi)):
        indeksi.append(i)

    for i in range(0, len(ponavljanja)):
        for j in range(i + 1, len(ponavljanja)):
            if ponavljanja[j] > ponavljanja[i]:
                ponavljanja[i], ponavljanja[j] = ponavljanja[j], ponavljanja[i]
                indeksi[i], indeksi[j] = indeksi[j], indeksi[i]

    temp = []
    for i in range(0, len(znakovi)):
        temp.append(znakovi[i])

    for i in range(0, len(indeksi)):
        znakovi[i] = temp[indeksi[i]]

    return [znakovi, ponavljanja]


def podjela(ponavljanja):
    prethodnaRazlika = 100000000000

    for i in range(1, len(ponavljanja)):
        lijevaSuma = sum(ponavljanja[1:i])
        desnaSuma = sum(ponavljanja[(i + 1):len(ponavljanja)])
        razlika = abs(lijevaSuma - desnaSuma)

        if razlika > prethodnaRazlika:
            return i - 1

        prethodnaRazlika = razlika


def Huffman(ponavljanja, lista):
    if len(lista) == 1:
        return lista

    lista1 = lista[len(lista) - 1]
    lista.pop()
    najmanjePonavljanje = ponavljanja[len(ponavljanja) - 1]
    ponavljanja.pop()
    ponavljanja[len(ponavljanja) - 1] += najmanjePonavljanje

    for i in range(0, len(lista[len(lista) - 1])):
        lista[len(lista) - 1][i][1] += "1"

    for i in range(0, len(lista1)):
        lista1[i][1] += "0"
        lista[len(lista) - 1].append(lista1[i])

    for i in range(0, len(ponavljanja)):
        for j in range(i + 1, len(ponavljanja)):
            if ponavljanja[i] < ponavljanja[j]:
                ponavljanja[i], ponavljanja[j] = ponavljanja[j], ponavljanja[i]
                lista[i], lista[j] = lista[j], lista[i]

    return Huffman(ponavljanja, lista)


# primjeri za slacka:

string = "AAAAABBBCCDE"
print(" ")
print('za string: ', string)
znakovi = nadjiUnikatne(string)

ponavljanja = izracunajPonavljanja(string, znakovi)
listaSvega = []
[z, p] = sortiraj(znakovi, ponavljanja)
for i in range(0, len(z)):
    listaSvega.append([[z[i], ""]])
lista = Huffman(p, listaSvega)
for i in range(0, len(lista[0])):
    print("Znak: {}, Kod: {}".format(lista[0][i][0], lista[0][i][1]))

print("")
noviString = ""
for j in range(0, len(string)):
    for i in range(0, len(lista[0])):
        if string[j] == lista[0][i][0]:
            noviString += lista[0][i][1]
            break

print('Kodirano: ', noviString)

duzinaN = len(string) * 8
duzinaK = len(noviString)

print("Stepen kompresije: ", format(float(duzinaN) / duzinaK))

# -----------------------------------------------------

string = "AAABBBCCDE"
print(" ")
print('za string: ', string)
znakovi = nadjiUnikatne(string)

ponavljanja = izracunajPonavljanja(string, znakovi)
listaSvega = []
[z, p] = sortiraj(znakovi, ponavljanja)
for i in range(0, len(z)):
    listaSvega.append([[z[i], ""]])
lista = Huffman(p, listaSvega)
for i in range(0, len(lista[0])):
    print("Znak: {}, Kod: {}".format(lista[0][i][0], lista[0][i][1]))

print("")
noviString = ""
for j in range(0, len(string)):
    for i in range(0, len(lista[0])):
        if string[j] == lista[0][i][0]:
            noviString += lista[0][i][1]
            break

print('Kodirano: ', noviString)

duzinaN = len(string) * 8
duzinaK = len(noviString)

print("Stepen kompresije: ", format(float(duzinaN) / duzinaK))

# -----------------------------------------------------

string = "EEEEAAAANNTTMMIIHHSSFFF0000000OUXPRL"
print(" ")
print('za string: ', string)
znakovi = nadjiUnikatne(string)

ponavljanja = izracunajPonavljanja(string, znakovi)
listaSvega = []
[z, p] = sortiraj(znakovi, ponavljanja)
for i in range(0, len(z)):
    listaSvega.append([[z[i], ""]])
lista = Huffman(p, listaSvega)
for i in range(0, len(lista[0])):
    print("Znak: {}, Kod: {}".format(lista[0][i][0], lista[0][i][1]))

print("")
noviString = ""
for j in range(0, len(string)):
    for i in range(0, len(lista[0])):
        if string[j] == lista[0][i][0]:
            noviString += lista[0][i][1]
            break

print('Kodirano: ', noviString)

duzinaN = len(string) * 8
duzinaK = len(noviString)

print("Stepen kompresije: ", format(float(duzinaN) / duzinaK))