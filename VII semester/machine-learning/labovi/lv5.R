library(ISLR)
library(class, lib.loc = "C:/Program Files/R/R-3.6.1/library")
library(caret)
library("dplyr")
library(C50)
library(tree)
library(ROCR)

data("Caravan")
data <- Caravan

## zadatak 1

# upoznavanje sa setom, rek'o sam joj cao cao zdravo

?Caravan

summary(data)

str(data)

# provjera izbalansiranosti

prop.table(table(data$Purchase))*100 # zakljucujemo da ima 94.03% No i 5.97% Yes

# scaling the data
ind <- sapply(data, is.numeric)
data[ind] <- lapply(data[ind], scale)

# podjela 1k instanci i ostalo data

test <- data[1:1000,,drop = TRUE]
train <- data[1001:nrow(data),, drop = TRUE]

# provjera izbalansiranosti
  
prop.table(table(test$Purchase))*100 # zakljucujemo da ima 94.1% No i 5.9% Yes, tj. relativno su isti znaci nije promijenjeno
  
## zadatak 2

pr <- knn(select_if(train, is.numeric), select_if(test, is.numeric), train$Purchase, k=1)
confusionMatrix(table(pr,test$Purchase))

pr <- knn(select_if(train, is.numeric), select_if(test, is.numeric), train$Purchase, k=3)
confusionMatrix(table(pr,test$Purchase))

pr <- knn(select_if(train, is.numeric), select_if(test, is.numeric), train$Purchase, k=5)
confusionMatrix(table(pr,test$Purchase)) # poboljsavaju se rezultati povecanjem k

## zadatak 3

# lda
lda.model <- lda(Purchase ~ ., data = train)
lda.pred <- predict(lda.model, test)
confusionMatrix(lda.pred$class, test$Purchase)

# c50
tree.c50 <- C5.0.formula(Purchase ~ ., data)
tree.pred <- predict(tree.c50, test)
confusionMatrix(tree.pred, test$Purchase)

# tree
tree.normal <- tree(Purchase~., data)
tree.predNormal <- predict(tree.normal, test)
yesValue <- as.data.frame(tree.predNormal)
compare <- as.factor(ifelse(yesValue$Yes > 0.2 , "Yes", "No"))
confusionMatrix(compare, test$Purchase)

## zadatak 4 rocr kriva

# knn
perf<-prediction(predictions=as.numeric(pr), labels=test$Purchase)
plot(performance(perf, measure = "tpr", x.measure = "fpr"))

# lda
perf<-prediction(predictions=as.numeric(lda.pred$class), labels=test$Purchase)
plot(performance(perf, measure = "tpr", x.measure = "fpr"))

# c50
perf<-prediction(predictions=as.numeric(tree.pred), labels=test$Purchase)
plot(performance(perf, measure = "tpr", x.measure = "fpr"))

# tree
perf<-prediction(predictions=as.numeric(compare), labels=test$Purchase)
plot(performance(perf, measure = "tpr", x.measure = "fpr"))

