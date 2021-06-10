# Dubinska Analiza Podataka
# Laboratorijska vjezba 1
# Masovic Haris - 1689/17993

# used functions

plotAutoCovariance <- function(ts) {
  acf(ts, type="covariance", 
      main="Koeficjenti autokovarijanse walk vremenske serije",
      xlab="Korak", ylab="Autokovarijansa")
}

plotAutoCorrelation <- function(ts) {
  acf(ts,
      main="Koeficjenti autokorelacije walk vremenske serije",
      xlab="Korak", ylab="Autokorelacija")
}

###### DIO I - simulacija vremenske serije

#### Zadatak 1
# timeplot, funkcija autokovarijanse i autokorelacije
# raznih vremenskih serija

# a) random walk vremenska simulacija
# N = 1000
# Zt = rnorm(0, 4)
# x_t = x_t-1 + Zt

x <- NA
x[1] <- 0

for(i in 2:1001) {
  # mi = 0, sigma^2 = 4
  x[i] <- x[i-1] + rnorm(1, 0, 4) # x_t = x_t-1 + Zt
}

randomWalk <- ts(x)

plot(randomWalk, main="Random walk vremenska serija", ylab="", 
     xlab="dani", 
     col="blue", lwd=2)

plotAutoCovariance(randomWalk)

plotAutoCorrelation(randomWalk)


# b) moving average vremenska serija 
# N = 1000
# Zt = rnorm(0, 4)
# Xt = Zt + 0.6 * Zt-1 + 0.08 * Zt-2

noise <- rnorm(1000, 0, 4)
temp <- NA
temp[1] <- noise[1]
temp[2] <- noise[2]

for (i in 3 : 1000) {
  temp[i] <- noise[i] + 0.6 * noise[i-1] + 0.08 * noise[i-2]
}

moovingAverage <- ts(temp)

plot(moovingAverage, main="Moving average vremenska serija", 
     ylab="", xlab="dani", 
     col="blue", lwd=2)

plotAutoCovariance(moovingAverage)

plotAutoCorrelation(moovingAverage)

# c) auto regresivna vremenska serija 
# N = 1000
# Zt = rnorm(0, 4)
# Xt = Zt + 0.5 * Xt-1 + 0.3 * Xt-2

Z <- rnorm(1000, 0, 4)

x <- NA
x[1] <- Z[1]
x[2] <- Z[2]

for(i in 3 : 1000) {
  x[i] <- Z[i] + 0.5 * x[i-1] + 0.3 * x[i-2]
}

autoRegresive <- ts(x)

plot(autoRegresive, main="Auto regresive vremenska serija", ylab="", 
     xlab="dani", 
     col="blue", lwd=2)

plotAutoCovariance(autoRegresive)

plotAutoCorrelation(autoRegresive)

###### DIO II - yule-walker jednacine

#### Primjer AR(2)

# Simulacija postavljenog AR(2) procesa:
sigma <- 4
phi <- c(1/3 , 1/2)
n <- 10000
set.seed(2021)

# AR(2) cemo simulirati pomocu arima.sim funkcije
## pri cemu postavljamo samo parametre AR modela, bez MA dijela

ar.proces <- arima.sim(n, model=list(ar=phi), sd=sigma)

# Estimacija koeficijenata autokorelacije r1 i r2
## Koristimo acf[2:3], jer je acf[1]=1, tj. koeficijent r0

r <- acf(ar.proces, plot=F)$acf[2:3]

# Kreirat cemo matricu R
## matrica sa elemntima 1, velicine 2x2

R <- matrix(1,2,2)
R[1,2] <- r[1]
R[2,1] <- r[1]

# Kreirat cemo matricu (vektor kolonu) b
## matrica sa prethodno kreiranim elementima r, velicine 2x1

b <- matrix(r,2,1)

# Da bi smo rijesili sistem jednacina koristimo funkciju solbe(R,b)
## Tj. dobili estimaciju parametara phi1 i phi2

phi.hat <- as.matrix(solve(R,b))

# Estimacija varijanse, tj. sigma parametra
c0 <- acf(ar.proces,type='covariance', plot=F)$acf[1]
sigma.hat <- c0 * (1 - sum(phi.hat*r))

# Vizualizacija simuliranog procesa
par(mfrow=c(3,1))
plot(ar.proces, main="Simulirani AR(2)")
acf(ar.proces, main="Funkcija autokorelacije simuliranog AR(2)")
pacf(ar.proces, main="Funkcija parcijalne autokorelacije simuliranog AR(2)")

# printanje aproksimacije
print(phi)
print(phi.hat)
print(sigma)
print(sigma.hat)

#### Zadatak 2
# Simulacija postavljenog AR(3) procesa
# parametri:
sigma <- 4
phi <- c(1/3 , 1/2, 7/100)
n <- 10000

set.seed(2021)

# simulacija procesa
ar.proces <- arima.sim(n, model=list(ar=phi), sd=sigma)

# racunanje r-ova i dobavljanje r1,r2,r3
r <- acf(ar.proces, plot=F)$acf[2:4]

# formiranje matrice i rjesavanje sistema jednacina
# racunanje phi hat
R <- matrix(1, 3, 3)
R[1,2] <- r[1]
R[1,3] <- r[2]
R[2,1] <- r[1]
R[2,3] <- r[1]
R[3,1] <- r[2]
R[3,2] <- r[1]

b <- matrix(r, 3, 1)

phi.hat <- as.matrix(solve(R,b))

# racunanje sigma hat
c0 <- acf(ar.proces, type='covariance', plot=F)$acf[1]

sigma.hat <- c0 * (1 - sum(phi.hat*r))

par(mfrow=c(3,1))
plot(ar.proces, main="Simulirani AR(3)")
acf(ar.proces, main="Funkcija autokorelacije simuliranog AR(3)")
pacf(ar.proces, main="Funkcija parcijalne autokorelacije simuliranog AR(3)")

# printanje aproksimacije za AR(3)
print(phi)
print(phi.hat)
print(sigma)
print(sigma.hat)

#### Zadatak 3

# instaliranje paketa
install.packages("astsa")
library(astsa)

data(rec)
fish = rec

# dobavljanje parametara
mi_x = mean(rec)

# cilj da postane mean ~ 0
ar.proces <- rec - mi_x

# odredjivanje reda auto-regresivnog procesa
# gledajuci grafik -> 2 red
par(mfrow=c(1,1))
pacf(ar.proces, main="Funkcija parcijalne autokorelacije rec dataseta")

r <- acf(ar.proces, plot=F)$acf[2:3]

R <- matrix(1,2,2)
R[1,2] <- r[1]
R[2,1] <- r[1]

b <- matrix(r,2,1)

phi.hat <- as.matrix(solve(R,b))

c0 <- acf(ar.proces, type='covariance', plot=F)$acf[1]

sigma.hat <- c0 * (1 - sum(phi.hat*r))

phi.hat.zero = mi_x * (1 - sum(phi.hat))

# Vizualizacija simuliranog procesa
par(mfrow=c(3,1))
plot(ar.proces, main="Ar.proces ts")
acf(ar.proces, main="Acf ar.proces ts")
pacf(ar.proces, main="Pacf ar.proces ts")

# Estimirani koeficjenti
print(phi.hat.zero)
print(phi.hat)
print(sigma.hat)
