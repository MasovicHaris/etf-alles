# -*- coding: utf-8 -*-
import random
import numpy
import numbers
import math


RANG_SP = 1.47

C1 = 15
C2 = 5

class ApstraktnaIndividua:
    def __init__(self, duzinaHromozoma):
        if duzinaHromozoma <= 0:
            raise Exception('Mora bit veće od nule')
        self.DuzinaHromozoma = duzinaHromozoma
        self.Hromozom = numpy.random.choice([0, 1], self.DuzinaHromozoma)
    def GetDuzinaHromozoma(self):
        return self.DuzinaHromozoma
    def SetDuzinaHromozoma(self, value):
        if value <= 0 or value != int(value):
            raise Exception('Ne mere tako')
        self.DuzinaHromozoma = value
        self.Hromozom = numpy.random.choice([0, 1], self.DuzinaHromozoma)
        return self.DuzinaHromozoma
    def GetHromozom(self):
        return self.Hromozom
    def SetHromozom(self, value):
        self.Hromozom = value
        self.DuzinaHromozoma = len(value)
        return self.Hromozom
    def GetFitness(self):
        return self.Evaluiraj()
    def SetFitness(self, value):
        if not isinstance(value, numbers.Number):
            raise Exception('Nije dabl')
        self.Fitness = value
        return self.Fitness
    def Evaluiraj(self): pass

def y(Hromozom):
    return 147

def pretvoriUBroj(h):
    h = h.tolist()
    h.reverse()
    d = len(h)
    st = 1
    x1 = 0
    for i in range(d - 3, d - 1):
        if h[i] == 1:
            x1 += st
        st *= 2
    st = 0.5
    for i in range(-(d-4), -d//2 + 1):
        i = -i
        if h[i] == 1:
            x1 += st
        st *= 0.5
    if h[d - 1] == 1:
        x1 = -x1
    
    st = 1
    x2 = 0
    for i in range((d - 2)//2 - 2, (d-2)//2):
        if h[i] == 1:
            x2 += st
        st *= 2
    st = 0.5
    for i in range(-((d - 2)//2 - 3), 1):
        i = -i
        if h[i] == 1:
            x2 += st
        st *= 0.5
    if h[d//2-1] == 1:
        x2 = -x2
    return (x1, x2)
    
def rastrigin(x1, x2):
    return 80 - (x1**2 - 10*math.cos(2*math.pi*x1)) - (x2**2 - 10*math.cos(2*math.pi*x2))

class MojaIndividua(ApstraktnaIndividua):
    def Evaluiraj(self):
        (x1, x2) = pretvoriUBroj(self.Hromozom)
        return rastrigin(x1, x2)
        
    
class Populacija:
    def __init__(self, VelicinaPopulacije, VjerovatnocaUkrstanja, VjerovatnocaMutacije, MaxGeneracija, VelicinaElite, DuzinaHromozoma = 16):
        if VelicinaPopulacije < 0:
            raise Exception('Velicina populacije treba biti pozitivna')
        if not 0 < VjerovatnocaUkrstanja < 1:
            raise Exception('Vjerovatnoca ukrstanja treba biti između 0 i 1')
        if not 0 < VjerovatnocaMutacije < 1:
            raise Exception('Vjerovatnoca mutacije treba biti između 0 i 1')
        if MaxGeneracija < 0:
            raise Exception('MaxGeneracija treba biti pozitivna')
        if VelicinaElite < 0:
            raise Exception('Velicina elite treba biti pozitivna')  
        if DuzinaHromozoma < 0:
            raise Exception('Duzina hromozoma treba biti pozitivna')     
        self.VelicinaPopulacije = VelicinaPopulacije
        self.VjerovatnocaUkrstanja = VjerovatnocaUkrstanja 
        self.VjerovatnocaMutacije = VjerovatnocaMutacije
        self.MaxGeneracija = MaxGeneracija
        self.VelicinaElite = VelicinaElite
        self.DuzinaHromozoma = DuzinaHromozoma
        self.Populacija = []
        for i in range(0, VelicinaPopulacije):
            self.Populacija.append(MojaIndividua(DuzinaHromozoma))
    def GetVelicinaPopulacije(self):
        return self.VelicinaPopulacije
    def SetVelicinaPopulacije(self, VelicinaPopulacije):
        if VelicinaPopulacije < 0:
            raise Exception('Velicina populacije treba biti pozitivna')
        self.VelicinaPopulacije = VelicinaPopulacije
        return self.VelicinaPopulacije
    def GetVjerovatnocaUkrstanja(self):
        return self.VjerovatnocaUkrstanja
    def SetVjerovatnocaUkrstanja(self, VjerovatnocaUkrstanja):
        if not 0 < VjerovatnocaUkrstanja < 1:
            raise Exception('Vjerovatnoca ukrstanja treba biti između 0 i 1')
        self.VjerovatnocaUkrstanja = VjerovatnocaUkrstanja
        return self.VjerovatnocaUkrstanja
    def GetVjerovatnocaMutacije(self):
        return self.VjerovatnocaMutacije
    def SetVjerovatnocaMutacije(self, VjerovatnocaMutacije):
        if not 0 < VjerovatnocaMutacije < 1:
            raise Exception('Vjerovatnoca mutacije treba biti između 0 i 1')
        self.VjerovatnocaMutacije = VjerovatnocaMutacije
        return self.VjerovatnocaMutacije
    def GetMaxGeneracija(self):
        return self.MaxGeneracija
    def SetMaxGeneracija(self, MaxGeneracija):
        if MaxGeneracija < 0:
            raise Exception('MaxGeneracija treba biti pozitivna')
        self.MaxGeneracija = MaxGeneracija
        return self.MaxGeneracija
    def GetVelicinaElite(self):
        return self.VelicinaElite
    def SetVelicinaElite(self, VelicinaElite):
        if VelicinaElite < 0:
            raise Exception('Velicine elite treba biti pozitivna')
        self.VelicinaElite = VelicinaElite
        return self.VelicinaElite
    def GetDuzinaHromozoma(self):
        return self.DuzinaHromozoma
    def SetDuzinaHromozoma(self, value):
        if value <= 0 or value != int(value):
            raise Exception('Ne mere tako')
        self.DuzinaHromozoma = value
        self.Hromozom = numpy.random.choice([0, 1], self.DuzinaHromozoma)
        return self.DuzinaHromozoma
    def GetPopulacija(self):
        return self.Populacija
    def SetPopulacija(self, Populacija):
        self.Populacija = Populacija
        return self.Populacija
    def OpUkrstanjaTacka(self, p1, p2):
        rnd = random.randint(1, p1.DuzinaHromozoma)
        c1, c2 = numpy.copy(p1.GetHromozom()), numpy.copy(p2.GetHromozom())
        for i in range(rnd, p1.DuzinaHromozoma):
            c1[i] = p2.GetHromozom()[i]
        for i in range(rnd, p1.DuzinaHromozoma):
            c2[i] = p1.GetHromozom()[i]
        if random.uniform(0, 1) < self.VjerovatnocaUkrstanja:
            i1 = MojaIndividua(self.DuzinaHromozoma)
            i2 = MojaIndividua(self.DuzinaHromozoma)
            i1.SetHromozom(c1)
            i2.SetHromozom(c2)
            return (i1, i2)
        else:
            return False
    
    def OpUkrstanjaDvijeTacke(self, p1, p2):
        rnd1 = random.randint(1, p1.DuzinaHromozoma-3)
        rnd2 = random.randint(rnd1 + 1, p1.DuzinaHromozoma)
        c1, c2 = p1.GetHromozom(), p2.GetHromozom()
        for i in range(rnd1, rnd2):
            c1[i] = p2.GetHromozom()[i]
        for i in range(rnd1, rnd2):
            c2[i] = p1.GetHromozom()[i]
        if random.uniform(0, 1) < self.VjerovatnocaUkrstanja:
            i1 = MojaIndividua(self.DuzinaHromozoma)
            i2 = MojaIndividua(self.DuzinaHromozoma)
            i1.SetHromozom(c1)
            i2.SetHromozom(c2)
            return (i1, i2)
        else:
            return False
        
    def OpBinMutacija(self, c1):
        rnd = random.randint(0, c1.DuzinaHromozoma-1)
        p = random.uniform(0, 1)
        if p < self.VjerovatnocaMutacije:
            c1h = c1.GetHromozom()
            c1h[rnd] = 1 - c1h[rnd]
            c1.SetHromozom(c1h)
        return c1
    
    def SelekcijaRTocak(self):
        suma = 0
        for h in self.Populacija:
            suma += h.GetFitness()
        rnd = random.uniform(0, 1)
        s = 0
        for h in self.Populacija:
            s += h.GetFitness() / suma
            if s >= rnd:
                return h
    
    def SelekcijaRang(self):
        self.Populacija = sorted(self.Populacija, key = lambda h1: h1.GetFitness())
        suma = 0
        for i in range(0, len(self.Populacija)):
            suma += (2 - RANG_SP) + 2 * (RANG_SP - 1) * i / (len(self.Populacija) - 1)
        rnd = random.uniform(0, 1)
        s = 0
        for i in range(0, len(self.Populacija)):
            s += ((2 - RANG_SP) + 2 * (RANG_SP - 1) * i / (len(self.Populacija) - 1)) / suma
            if s >= rnd:
                return self.Populacija[i]
    
    def NovaGeneracija(self):
        p = self.Populacija
        novaP = []
        elita = self.VelicinaElite
        while len(novaP) + elita < len(p):
            h1 = self.SelekcijaRang()
            h2 = self.SelekcijaRang()
            if h1 == h2:
                continue
            h = self.OpUkrstanjaTacka(h1, h2)
            if not h:
                continue
            h1 = self.OpBinMutacija(h[0])
            h2 = self.OpBinMutacija(h[1])
            novaP.append(h1)
            novaP.append(h2)
        p = sorted(p, key = lambda h1: h1.GetFitness())
        print(pretvoriUBroj(p[-1].Hromozom), p[-1].GetFitness())
        for i in range(len(p) - elita, len(p)):
            novaP.append(p[i])
        self.Populacija = novaP
        # for h in novaP:
            # print(pretvoriUBroj(h.Hromozom), h.GetFitness())
        print('...')
        
        
    def GenerisiGeneracije(self):
        for i in range(0, self.MaxGeneracija):
            self.NovaGeneracija()
        
    

p = Populacija(18, 0.99, 0.05, 10, 2, 14)
p.GenerisiGeneracije()
