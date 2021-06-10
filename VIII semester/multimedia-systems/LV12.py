import numpy
import math
from matplotlib import pyplot

img0 = pyplot.imread('./data/Teddy/frame10.png')
img1 = pyplot.imread('./data/Teddy/frame11.png')

M, N = img0.shape
print(img0.shape)
W = 25

def lucas_kanade(img0, img1, W):
    It = img1 - img0
    Ix, Iy = numpy.gradient(img0)
    pyplot.imshow(img0, cmap = 'gray')
    quiv = []
    for i in range(0, M - W // 2, W):
        for j in range(0, N - W // 2, W):
            sX = i + W // 2
            sY = j + W // 2
            A = ([[0., 0.], [0., 0.]])
            b = ([[0.], [0.]])
            for m in range(i, min(M, i + W)):
                for n in range(j, min(N, j + W)):
                    A[0][0] += Ix[m][n] ** 2
                    A[0][1] += Ix[m][n] * Iy[m][n]
                    A[1][0] += Iy[m][n] * Ix[m][n]
                    A[1][1] += Iy[m][n] ** 2
                    b[0][0] += -Ix[m][n] * It[m][n]
                    b[1][0] += -Iy[m][n] * It[m][n]
            V = numpy.linalg.inv(A).dot(b)
            quiv.append([sY, sX, V[1][0], -V[0][0]])
    quiv = numpy.array(quiv)
    print(quiv[:, 0])
    pyplot.quiver(quiv[:, 0], quiv[:, 1], quiv[:, 2], quiv[:, 3], color=(1, 0, 0))
    pyplot.show()


lucas_kanade(img0, img1, W)