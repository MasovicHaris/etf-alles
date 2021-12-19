import numpy
import random
import math

class TabuTSP:
    
    def __init__(self, graf, duzinaTabuListe = 1, brojIteracija = 2):
        self.graf = graf
        self.brojCvorova = len(graf)
        self.rjesenje = self.greedyTSP()
        self.tabuLista = []
        self.duzinaTabuListe = duzinaTabuListe
        self.brojIteracija = brojIteracija
    
    def getFitness(self, rjesenje):
        fitness = 0
        for i in range(0, len(rjesenje)):
            fitness += self.graf[rjesenje[i]][rjesenje[(i + 1) % self.brojCvorova]]
        return fitness
    
    def randomRjesenje(self):
        return list(numpy.random.permutation(range(0, self.brojCvorova)))
                        
    def greedyTSP(self):
        rjesenje = [0]
        while len(rjesenje) < self.brojCvorova:
            mini = (rjesenje[-1] + 1) % self.brojCvorova
            miniGrana = math.inf
            for i in range(0, self.brojCvorova):
                if i not in rjesenje and (miniGrana == math.inf or self.graf[rjesenje[-1]][i] <= miniGrana):
                    mini = i
                    miniGrana = self.graf[rjesenje[-1]][mini] 
            rjesenje.append(mini)
        return rjesenje
        
    def step(self):
        najboljeRjesenje = self.rjesenje
        najboljiFitness = math.inf
        for i in range(0, self.brojCvorova):
            for j in range(i + 1, self.brojCvorova):
                rjesenje = self.rjesenje.copy()
                rjesenje[i], rjesenje[j] = rjesenje[j], rjesenje[i]
                if self.getFitness(rjesenje) < najboljiFitness and rjesenje not in self.tabuLista:
                    najboljeRjesenje = rjesenje
                    najboljiFitness = self.getFitness(rjesenje)
        self.rjesenje = najboljeRjesenje
        self.tabuLista.append(najboljeRjesenje)
        if len(self.tabuLista) > self.duzinaTabuListe:
            self.tabuLista.pop(0)
    
    def run(self):
        najboljeRjesenje = self.rjesenje
        najboljiFitness = self.getFitness(najboljeRjesenje)
        print(self.rjesenje)
        for i in range(0, self.brojIteracija):
            self.step()
            if self.getFitness(self.rjesenje) < najboljiFitness:
                najboljiFitness = self.getFitness(self.rjesenje)
                najboljeRjesenje = self.rjesenje
            print(self.rjesenje, self.getFitness(self.rjesenje), self.getFitness(najboljeRjesenje))
            print(self.tabuLista)
        return najboljeRjesenje

t = TabuTSP([[0,2,2,2,7,5,2],
      [2,0,4,7,9,1,3],
      [2,4,0,3,6,6,5],
      [2,7,3,0,4,9,6],
      [7,9,6,4,0,4,9],
      [5,1,6,9,4,0,2],
      [2,3,5,6,9,2,0]])
      

      
t.run()

t2 = TabuTSP([[0,3,3,8,6],
      [3,0,7,2,8],
      [3,7,0,5,2],
      [8,2,5,0,1],
      [6,8,2,1,0]])

t2.run()



