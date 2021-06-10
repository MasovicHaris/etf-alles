# Dubinska Analiza Podataka
# Laboratorijska vjezba 2
# Masovic Haris - 1689/17993

setwd("/Users/harismasovic/Desktop/dap")

#### Zadatak 1

library(astsa)

birth.data <- read.csv("daily-total-female-births-in-cal.csv") 

number_of_births <- 
  birth.data$Daily.total.female.births.in.California..1959

birth.data$Date <- strptime(birth.data$Date,format="%Y-%m-%d")

birth.data$Date <- as.Date(birth.data$Date, "%m/%d/%Y")

plot(number_of_births ~ birth.data$Date, type = "l",
     main='Dnevni broj rodjenja djevojcica u Kalirorniji, 1959.',
     ylab = 'Broj rodjenja', xlab='Datum')

Box.test(number_of_births, lag = log(length(number_of_births)))
# Autokorelaciju provjeravamo od koraka k = 1 do k = log(len(x))
# p-value = 2.088e-06 < 0.05 -> postoji autokorelacija 

number_of_births.diff <- diff(number_of_births)

plot(number_of_births.diff ~ birth.data$Date[1:364], type = "l",
     main='Differenced series',
     ylab = '', xlab='Date')

Box.test(number_of_births.diff, lag =
           log(length(number_of_births.diff)))

acf(number_of_births.diff,
    main='Autokorelacija diferencirane serije', 50)

pacf(number_of_births.diff,
     main='Parcijalna autokorelacija diferencirane serije', 50)

# kreiranje modela
# p = {0, 7}, d = 1, q = {1, 2}
model1 <- arima(number_of_births, order=c(0,1,1))
SSE1 <- sum(model1$residuals^2)
model1.test <- Box.test(model1$residuals, lag =
                        log(length(model1$residuals)))

model2 <- arima(number_of_births, order=c(0,1,2))
SSE2 <- sum(model1$residuals^2)
model2.test <- Box.test(model1$residuals, lag =
                        log(length(model1$residuals)))

model3 <- arima(number_of_births, order=c(7,1,1))
SSE3 <- sum(model1$residuals^2)
model3.test <- Box.test(model1$residuals, lag =
                        log(length(model1$residuals)))

model4 <- arima(number_of_births, order=c(7,1,2))
SSE4 <- sum(model1$residuals^2)
model4.test <- Box.test(model1$residuals, lag =
                        log(length(model1$residuals)))


# rezultati
rezultati <- data.frame(row.names=c('AIC', 'SSE', 'p-value'),
                      c(model1$aic, SSE1, model1.test$p.value),
                      c(model2$aic, SSE2, model2.test$p.value),
                      c(model3$aic, SSE3, model3.test$p.value),
                      c(model4$aic, SSE4, model4.test$p.value))

colnames(rezultati) <- 
  c('Arima(0,1,1)', 'Arima(0,1,2)', 'Arima(7,1,1)', 'Arima(7,1,2)')

format(rezultati, scientific=FALSE)
# p-values testnog modela tj. reziduali ne smiju imati korelaciju
# odnosno mora biti p-value > 0.05

# sarima
sarima(number_of_births, 0,1,2,0,0,0)

#### Zadatak 2

data(BJsales)

sales = BJsales

plot(sales, type = "l", main='BJSales')

Box.test(sales, lag = log(length(sales))) 
# p-value = 2.2e-16 < 0.05 -> ima autokorelacije

sales.diff <- diff(sales)

plot(sales.diff, type = "l", main='Differenced sales')

sales.diff.diff <- diff(sales.diff)

plot(sales.diff.diff, type = "l", main='Double Differenced sales')

Box.test(sales.diff.diff, lag =
           log(length(sales.diff.diff)))
# p-value = 1.304e-06 < 0.05 -> ima autokorelacije

# acf i pacf
acf(sales.diff.diff,
    main='Autokorelacija diferencirane serije sales', 50)

pacf(sales.diff.diff,
     main='Parcijalna autokorelacija diferencirane serije sales', 50)

# kreiranje modela
# p = {0, 3}, d = 2, q = {1, 2}
model1 <- arima(sales, order=c(0,2,1))
SSE1 <- sum(model1$residuals^2)
model1.test <- Box.test(model1$residuals, lag =
                          log(length(model1$residuals)))

model2 <- arima(sales, order=c(0,2,2))
SSE2 <- sum(model1$residuals^2)
model2.test <- Box.test(model1$residuals, lag =
                          log(length(model1$residuals)))

model3 <- arima(sales, order=c(3,2,1))
SSE3 <- sum(model1$residuals^2)
model3.test <- Box.test(model1$residuals, lag =
                          log(length(model1$residuals)))

model4 <- arima(sales, order=c(3,2,2))
SSE4 <- sum(model1$residuals^2)
model4.test <- Box.test(model1$residuals, lag =
                          log(length(model1$residuals)))


# rezultati
rezultati <- data.frame(row.names=c('AIC', 'SSE', 'p-value'),
                        c(model1$aic, SSE1, model1.test$p.value),
                        c(model2$aic, SSE2, model2.test$p.value),
                        c(model3$aic, SSE3, model3.test$p.value),
                        c(model4$aic, SSE4, model4.test$p.value))

colnames(rezultati) <- 
  c('Arima(0,2,1)', 'Arima(0,2,2)', 'Arima(3,2,1)', 'Arima(3,2,2)')

format(rezultati, scientific=FALSE)
# gledajuci AIC i SSE vrijednosti najbolji (0,2,1)
# svi reziduali > 0.05 -> nema korelacije

sarima(sales, 0,2,1,0,0,0)
# ma koeficijent = -0.7480, sigma^2 = 1.866

#### Zadatak 3

data(jj)

plot(jj, main="Johnson&Johnson zarada po kvartalima",
     ylab="Zarada", xlab="Godine")

jj.log.diff <- diff(log(jj))

plot(jj.log.diff, main="Log-return Johnson&Johnson",
     ylab="Zarada", xlab="Godine")

# acf i pacf
acf(jj.log.diff,
    main='Autokorelacija log-return serije', 50)

pacf(jj.log.diff,
     main='Parcijalna autokorelacija log-return serije', 50)

# sezonalno diff
jj.log.diff.diff.S <- diff(jj.log.diff, 4)

Box.test(jj.log.diff.diff.S,
          lag = log(length(jj.log.diff.diff.S)))

# acf i pacf nakon sezonalnosti
acf(jj.log.diff.diff.S,
    main='Autokorelacija log-return-diff.S serije', 20)

pacf(jj.log.diff.diff.S,
     main='Parcijalna autokorelacija log-return-diff.S serije',
     20)

# q = {0, 1}, Q = {0, 1}, d = 1
# p = {0, 1}, P = {0, 1}, D = 1

d <- 1; D <- 1; S <- 4;

for(p in 0:1){
  for(q in 0:1){
    for(P in 0:1){
      for(Q in 0:1){
        # stedljivost
        if(p+d+q+P+D+Q<=6){
          # samo se mora log uraditi
          # arima model uradi sve ostalo
          # nakon pretpostavke parametara
          model<-arima(x = log(jj), order = c((p),d,(q)),
                       seasonal = list(order=c((P),D,(Q)),
                                       period=S))
          
          pval <- Box.test(model$residuals,
                         lag = log(length(model$residuals)))
          
          sse <- sum(model$residuals^2)
          
          cat(p,d,q,P,D,Q,S,
              'AIC=', model$aic, ' SSE=',sse,' p-VALUE=',
              pval$p.value, '\n')
        }
      }
    }
  }
}

# sarima model nakon log
sarima(log(jj), 0 , 1, 1, 1, 1, 0, 4)
# ma1 = -0.6796, sezonal ar1 = -0.3220

# predikcija
library(forecast)

model <- arima(x=log(jj), order = c(0,1,1), seasonal =
               list(order=c(1,1,0), period=4))

plot(forecast(model))

#### Zadatak 4

monthly.milk <- read.csv("monthly-milk-production-pounds.csv")

milk.ts <- ts(monthly.milk$Monthly.milk.production..pounds.per.cow., 
              frequency=12, 
              start=c(1962,1))

# plottanje milk ts
plot(milk.ts, 
     type="l",
     main="Monthly milk production pounds")

milk.ts.log.diff <- diff(log(milk.ts))

plot(milk.ts.log.diff, main="Diff monthly link production")

# acf i pacf
acf(milk.ts.log.diff,
    main='Autokorelacija log-return serije', 50)

pacf(milk.ts.log.diff,
     main='Parcijalna autokorelacija log-return serije', 50)

# sezonalno diff -> 12
milk.ts.log.diff.diff.S <- diff(milk.ts.log.diff, 12)

Box.test(milk.ts.log.diff.diff.S,
         lag = log(length(milk.ts.log.diff.diff.S)))

acf(milk.ts.log.diff.diff.S,
    main='Autokorelacija log-return serije', 20)

pacf(milk.ts.log.diff.diff.S,
     main='Parcijalna autokorelacija log-return serije', 20)

# q = {0, 2}, Q = {0, 1}, d = 1
# p = {0, 1}, P = {0, 1}, D = 1

d <- 1; D <- 1; S <- 12;

for(p in 0:1){
  for(q in c(0, 2)){
    for(P in 0:1){
      for(Q in 0:1){
        # stedljivost
        if(p+d+q+P+D+Q<=6){
          # samo se mora log uraditi
          # arima model uradi sve ostalo
          # nakon pretpostavke parametara
          model<-arima(x = log(milk.ts), 
                       order = c((p),d,(q)),
                       seasonal = list(order=c((P),D,(Q)),
                                       period=S))
          
          pval <- Box.test(model$residuals,
                           lag = log(length(model$residuals)))
          
          sse <- sum(model$residuals^2)
          
          cat(p,d,q,P,D,Q,S,
              'AIC=', model$aic, ' SSE=',sse,' p-VALUE=',
              pval$p.value, '\n')
        }
      }
    }
  }
}

# najbolji:
# 1 1 2 0 1 1 12 AIC= -964.5449  SSE= 0.0165117  p-VALUE= 0.5309375 

sarima(log(milk.ts), 1, 1, 2, 0, 1, 1, 12)
# ar1 = -0.9022, ma1 = 0.8038, ma2 = -0.1961,
# sma1 = -0.5877, sigma^2 = 0.0001031

model <- arima(x=log(milk.ts), 
               order = c(1,1,2), 
               seasonal = list(order=c(0,1,1), 
                               period=12))

plot(forecast(model))
