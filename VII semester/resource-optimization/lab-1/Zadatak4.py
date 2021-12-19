import math
class Funkcija:
    def __init__(self, function, interval, step):
        self.function = function
        self.interval = interval
        self.step = step
        self.values = [] 
        x0 = interval[0]
        while x0 <= interval[1]:
            self.values.append(function(x0))
            x0 += step
    
    def f(self, x):
        lo = math.floor((x - self.interval[0]) / self.step) * self.step + self.interval[0]
        hi = lo + self.step
        return (x - lo) * (self.function(hi) - self.function(lo)) / (hi - lo) + self.function(lo)
        
    def df(self, x):
        x0 = self.interval[0]
        i = 0
        while x0 <= x:
            x0 += self.step
            i += 1
        return (self.values[i] - self.values[i - 1]) / self.step
        hi = x0
        lo = x0 - self.step
        lo = math.floor((x - self.interval[0]) / self.step) * self.step + self.interval[0]
        hi = lo + self.step
        return (self.function(hi) - self.function(lo)) / self.step
        

def ff(x):
    return x ** 2

F = Funkcija(ff, [0, 10], 2)
print(F.df(1))
        
    