library(ISLR)
library(dplyr)
library(MASS)
library(caret)

## Zadatak 1

data("Smarket")
data <- Smarket

# ispis varijabli
names(data)
# dimenzija seta
dim(data)

# deskriptivna statistika
summary(data)

# korelacije
cor(select(data, -Direction))

# podjela seta, test set 2015 godina, trening set sve ostalo
training <- data[data$Year != '2005', ]
train_ind <- sample(seq_len(nrow(training)))
test <- data[data$Year == '2005', ]

# LDA na na osnovu Lag1 i Lag2
lda.model <- lda(Direction ~ Lag1 + Lag2, data = data, subset = train_ind)

# predikcija
lda.pred <- predict(lda.model, test)
# lda.pred$class

# konfuzion matrix
confusionMatrix(lda.pred$class, test$Direction)

## Zadatak 2

# QDA na na osnovu Lag1 i Lag2
qda.model <- qda(Direction ~ Lag1 + Lag2, data = data, subset = train_ind)

# predikcija
qda.pred <- predict(qda.model, test)
# lda.pred$class

# konfuzion matrix
confusionMatrix(qda.pred$class, test$Direction)

## Zadatak 3

# LDA na na osnovu svih varijalbi
lda.model <- lda(Direction ~ ., data = data, subset = train_ind)

# predikcija
lda.pred <- predict(lda.model, test)
# lda.pred$class

# konfuzion matrix
confusionMatrix(lda.pred$class, test$Direction)

# QDA na na osnovu svih varijabli
qda.model <- qda(Direction ~ ., data = data, subset = train_ind)

# predikcija
qda.pred <- predict(qda.model, test)
# lda.pred$class

# konfuzion matrix
confusionMatrix(qda.pred$class, test$Direction)
