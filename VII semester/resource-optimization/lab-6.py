# -*- coding: utf-8 -*-
import random
import numpy
import numbers

c1 = 15
c2 = 5

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
        return self.Fitness
    def SetFitness(self, value):
        if not isinstance(value, numbers.Number):
            raise Exception('Nije dabl')
        self.Fitness = value
        return self.Fitness
    def Evaluiraj(self): pass

def y(Hromozom):
    return 147

class MojaIndividua(ApstraktnaIndividua):
    def Evaluiraj(self):
        c1 * y(self.Hromozom) + c2
    
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
        print(rnd)
        print(c1, c2)
        for i in range(rnd, p1.DuzinaHromozoma):
            c1[i] = p2.GetHromozom()[i]
        for i in range(rnd, p1.DuzinaHromozoma):
            c2[i] = p1.GetHromozom()[i]
        i1 = MojaIndividua(self.DuzinaHromozoma)
        i2 = MojaIndividua(self.DuzinaHromozoma)
        print(c1, c2)
        i1.SetHromozom(c1)
        i2.SetHromozom(c2)
        return (i1, i2)
    
    def OpUkrstanjaDvijeTacke(self, p1, p2):
        rnd1 = random.randint(1, p1.DuzinaHromozoma-3)
        rnd2 = random.randint(rnd1 + 1, p1.DuzinaHromozoma)
        c1, c2 = p1.GetHromozom(), p2.GetHromozom()
        for i in range(rnd1, rnd2):
            c1[i] = p2.GetHromozom()[i]
        for i in range(rnd1, rnd2):
            c2[i] = p1.GetHromozom()[i]
        i1 = MojaIndividua(self.DuzinaHromozoma)
        i2 = MojaIndividua(self.DuzinaHromozoma)
        i1.SetHromozom(c1)
        i2.SetHromozom(c2)
        return (i1, i2)
        
    def OpBinMutacija(self, c1):
        rnd = random.randint(0, c1.DuzinaHromozoma-1)
        p = random.uniform(0, 1)
        if p < self.VjerovatnocaMutacije:
            c1h = c1.GetHromozom()
            c1h[rnd] = 1 - c1h[rnd]
            c1.SetHromozom(c1h)
        return c1

 # Vjerovatnoca mutiranja je inace PUNO manja, ali ovdje cisto
2 # da vidimo da li "mutira" kako treba
p = Populacija (20, 0.99, 0.99, 10, 1, 5) # DuzinaHromozoma = 10
# Posljednji parametar mozemo izostaviti jer ima
# podrazumijevanu vrijednost 16
r1 = random.randint (1, p.GetVelicinaPopulacije() - 1)
r2 = random.randint (1, p.GetVelicinaPopulacije() - 1)
p1 = p.GetPopulacija()[r1] # dva random roditelja...
p2 = p.GetPopulacija()[r2]
print("P1", p1.GetHromozom())
print("P2", p2.GetHromozom())
(c1, c2) = p.OpUkrstanjaTacka(p1, p2)
print("C1", c1.GetHromozom())
print("C2", c2.GetHromozom())
c3 = p.OpBinMutacija(c1)
print("C3", c3.GetHromozom(), "C1 nakon mutiranja")
for i in p.GetPopulacija():
    print(i.GetHromozom())

