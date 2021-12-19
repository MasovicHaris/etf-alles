import math

def LS(f, x0, delta_x, N, eps):
    i = 0
    prevF = math.inf
    while i < N and abs(prevF - f(x0)) > eps:
        prevF = f(x0)
        novoX = (x0[0] + delta_x, x0[1])
        for dx0 in [x0[0] - delta_x, x0[0], x0[0] + delta_x]:
            for dx1 in [x0[1] - delta_x, x0[1], x0[1] + delta_x]:
                if f(novoX) > f((dx0, dx1)):
                    novoX = (dx0, dx1)
        i += 1
        x0 = novoX
    print(i, f(x0))
    return x0

print(LS(lambda x: x[0]*x[0] + x[1]*x[1], (0.5, 0.5), 0.1, 1000, 0))
print(LS(lambda x: x[0]*x[0] + x[1]*x[1], (15, 10), 0.1, 1000, 0.2))
print(LS(lambda x: (x[0] + x[1])**2, (15, 10), 0.1, 1000, 0.2))  
print(LS(lambda x: x[0]*x[0] + x[1]*x[1] + 4*math.e**(-x[0]*x[0]-x[1]*x[1]), (0.5, 0.5), 0.1, 1000, 0))
print(LS(lambda x: x[0]*x[0] + (x[1]-1)**4 + 5, (5, 5), 0.2, 1000, 0))
print(LS(lambda x: x[0]*x[0] + x[1]*x[1] + 4*math.e**(-x[0]*x[0]-x[1]*x[1]), (0.5, 0.5), 0.2, 500, 0))
print(LS(lambda x: x[0]*x[0] + x[1]*x[1] + x[0]*x[1], (0.5, 0.5), 0.01, 1000, 0.01))
