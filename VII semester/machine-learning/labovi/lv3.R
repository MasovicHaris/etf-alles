library(tree)
library(C50)
library(caret)

# LV3 - Masovic Haris 
# get the dataset
setwd('C:/Users/User/Desktop/Data')

data <- read.csv("credit.csv", header=T)

# zadatak 1
# upoznavanje sa datasetom - rek'o sam joj cao cao zdravo

smp_size <- floor(0.70 * nrow(data)) # getting the 70% of the dataset
train_ind <- sample(seq_len(nrow(data)), size = smp_size)

train <- data[train_ind, ] # train contains 70%
test <- data[-train_ind, ] # our test set contains 30%

# plotting the tree with tree library
tree.credit1 <- tree(class~., data, subset = train_ind)
# plot(tree.credit1)
# text(tree.credit1, cex = .7)

# plotting the tree with c50 library
tree.credit2 <- C5.0.formula(class~., data, subset = train_ind)
# plot(tree.credit2)

# predicting the outcome
class.test <- data$class[-train_ind]
tree.pred1 <- predict(tree.credit1, test, type = "class")
tree.pred2 <- predict(tree.credit2, test, type = "class")

# creating the confusion matrixes
# k1 <- table(tree.pred1, class.test)
k2 <- table(tree.pred2, class.test)

# print them out
k2

# getting the values
TP1 <- k2[1,1]
FP1 <- k2[2,1]
FN1 <- k2[1,2]
TN1 <- k2[2,2]


# tacnost, stepen greske, osjetljivost, specificnost, preciznost, kappa statistika [nije mi se dalo]
# sve je isto

accuracy2 <- (TP1+TN1)/(FP1+FN1+TN1+TP1)
accuracy2
precision2 <- TP1/(TP1+FN1)
precision2

# zadatak 2

provjera2 <- confusionMatrix(k2)
provjera2

# zadatak 3
kPuta <- function(k) {
  rez <- c(0,0)
  setwd('C:/Users/User/Desktop/Data')
  data <- read.csv("credit.csv", header=T)
  
  for(i in 1:k){
    smp_size <- floor(0.70 * nrow(data)) # getting the 70% of the dataset
    train_ind <- sample(seq_len(nrow(data)), size = smp_size)
    
    train <- data[train_ind, ] # train contains 70%
    test <- data[-train_ind, ] # our test set contains 30%
    
    # plotting the tree with c50 library
    tree.credit2 <- C5.0.formula(class~., data, subset = train_ind)
    # plot(tree.credit2)
    
    # predicting the outcome
    class.test <- data$class[-train_ind]
    tree.pred2 <- predict(tree.credit2, test, type = "class")
    
    # creating the confusion matrixes
    k2 <- table(tree.pred2, class.test)
    
    # getting the values
    TP1 <- k2[1,1]
    FP1 <- k2[2,1]
    FN1 <- k2[1,2]
    TN1 <- k2[2,2]
    
    
    # tacnost i preciznost
    accuracy2 <- (TP1+TN1)/(FP1+FN1+TN1+TP1)
    rez[1] = rez[1] + accuracy2
    precision2 <- TP1/(TP1+FN1)
    rez[2] = rez[2] + precision2
  }
  return(c(rez[1]/k, rez[2]/k))
}
