library(ggplot2)
library(plyr)
library(dplyr)
library(GGally)
library(rpart)
library(rpart.plot)
library(randomForest)
library(caret)
library(corrplot)
library(RColorBrewer)

# Preprocessing
# Loading training & test sets 
attrition.train <- read.csv(file="attrition_train.csv", stringsAsFactors = FALSE, header = TRUE)
attrition.test <- read.csv(file="attrition_test.csv", stringsAsFactors = FALSE, header = TRUE)

# Checking the structure
str(attrition.train)

# Creating a new data set with both the test and the train sets
attrition.full <- bind_rows(attrition.train,attrition.test)
LT=dim(attrition.train)[1] 

# How many distinct, unique values are there - length(unique(x))
apply(attrition.full, 2, function(x) length(unique(x)))
#Irrelevant variables: StandardHours, Over18

#Empty values: Department-93/1470, EducationField-86, JobRole-89, PercentSalaryHike-99, TrainingTimesLastYear-103
summary(is.na(attrition.full))

#JobLevel: One->1, Five->5
attrition.full$JobLevel <- revalue(attrition.full$JobLevel, c("One"=1,"Five"=5)) 
#StockOptionLevel: zero change into 0
attrition.full$StockOptionLevel <- revalue(attrition.full$StockOptionLevel, c("Zero"=0)) 
#EnvironmentSatisfaction: Medium -> 2
attrition.full$EnvironmentSatisfaction <- revalue(attrition.full$EnvironmentSatisfaction, c("Medium"=2)) 
#Education: Master->4; Doctor->5
attrition.full$Education <- revalue(attrition.full$Education, c("Master"=4,"Doctor"=5)) 
#JobInvolvement: High->3
attrition.full$JobInvolvement <- revalue(attrition.full$JobInvolvement, c("High"=3)) 
#JobSatisfaction: Very High->4
attrition.full$JobSatisfaction <- revalue(attrition.full$JobSatisfaction, c("Very High"=4)) 
#RelationshipSatisfaction: Low->1, High->3
attrition.full$RelationshipSatisfaction <- revalue(attrition.full$RelationshipSatisfaction, c("Low"=1,"High"=3)) 
#Attrition Yes->1, No->0

# Getting back the data for oversampling test
train_im <- attrition.full[1:LT,]
attrition.train <- attrition.full[1:LT,]
test_im<-attrition.full[(LT+1):1470,]
attrition.test <- attrition.full[(LT+1):1470,]

#Check if there is oversampling?
ggplot(data=attrition.full,aes(x=Attrition))+geom_bar( fill="steelblue")
ggplot(data=test_im,aes(x=Attrition))+geom_bar( fill="steelblue")

#There is oversampling & during the ML implementation we should care xD
# numPositive <-length(which(newthyroid1$Class=="positive"))
# numNegative <-length(which(newthyroid1$Class=="negative"))
# nInstances <-  numNegative-numPositive
#Factors
cols<-c("JobLevel","JobRole","StockOptionLevel","EnvironmentSatisfaction","Education","JobInvolvement","JobSatisfaction","RelationshipSatisfaction","PerformanceRating","WorkLifeBalance","OverTime","MaritalStatus","Gender","Department","BusinessTravel","Attrition")
for (i in cols){
  attrition.full[ ,i] <- as.factor(attrition.full[ ,i])
}

#Normalisation - doesn't change models much, so it can be avoided
normalize <- function(x) {
  return ((x - min(x)) / (max(x) - min(x)))
}

attrition.full$DailyRate<-normalize(attrition.full$DailyRate)
attrition.full$MonthlyRate<-normalize(attrition.full$MonthlyRate)
attrition.full$MonthlyIncome<-normalize(attrition.full$MonthlyIncome)

#Check if the empty variables are relevant
#Department VS Attrition
ggplot(data = attrition.train[!is.na(attrition.train$Department),],aes(x=Department,fill=Attrition))+geom_bar()

#EducationField VS Attrition
ggplot(data = attrition.train[!is.na(attrition.train$EducationField),],aes(x=EducationField,fill=Attrition))+geom_bar()

#Department VS EducationField
ggplot(data = attrition.train[!is.na(attrition.train$Department),],aes(x=Department,fill=EducationField))+geom_bar()
#Not correlated as I expected

#Education VS EducationField
ggplot(data = attrition.train[!is.na(attrition.train$Education),],aes(x=Education,fill=EducationField))+geom_bar()
#Not correlated

#JobRole VS EducationField
ggplot(data = attrition.train[!is.na(attrition.train$EducationField),],aes(x=EducationField,fill=JobRole))+geom_bar()
#Not so correlated

#Department VS JobRole
ggplot(data = attrition.train[!is.na(attrition.train$Department),],aes(x=Department,fill=JobRole))+geom_bar()
#Correlated, but have to check which one to take

#JobRole VS Education
ggplot(data = attrition.train[!is.na(attrition.train$Education),],aes(x=Education,fill=JobRole))+geom_bar()
#Not correlated

# Education VS BusinessTravel
ggplot(data = attrition.train[!is.na(attrition.train$Education),],aes(x=Education,fill=BusinessTravel))+geom_bar()
# Not correlated

#EducationField VS BusinessTravel
ggplot(data = attrition.train[!is.na(attrition.train$EducationField),],aes(x=EducationField,fill=BusinessTravel))+geom_bar()
#Not correlated

#EducationField VS Gender
ggplot(data = attrition.train[!is.na(attrition.train$Gender),],aes(x=Gender,fill=EducationField))+geom_bar()
#Not correlated

#JobRole VS Gender
ggplot(data = attrition.train[!is.na(attrition.train$Gender),],aes(x=Gender,fill=JobRole))+geom_bar()
#Not correlated

#EducationField VS MonthlyIncome
ggplot(data = attrition.train,aes(x=MonthlyIncome,fill=EducationField))+geom_histogram()+theme_minimal()
#Not correlated

#JobRole VS MonthlyIncome
ggplot(data = attrition.train,aes(x=MonthlyIncome,fill=JobRole))+geom_histogram(bins=30)+theme_minimal()
#Correlated -> Therefore, I won't consider JobRole, but will MonthlyIncome. For check if I should use Department:
#Department VS MonthlyIncome
ggplot(data = attrition.train,aes(x=MonthlyIncome,fill=Department))+geom_histogram(bins=30)+theme_minimal()
#Not correlated -> Department should be filled

#Department
ggplot(data=attrition.train,aes(x=Department))+geom_bar( fill="steelblue")
#Fill empty fields with the most frequent "Research & Development"
attrition.full$Department[is.na(attrition.full$Department)==TRUE] <- "Research & Development"

#EducationField
ggplot(data=attrition.train,aes(x=EducationField))+geom_bar( fill="steelblue")
#Filling EducationField - most frequent
attrition.full$EducationField[is.na(attrition.full$EducationField)==TRUE] <- as.factor("LifeScience")
attrition.full[ ,"EducationField"] <- as.factor(attrition.full[ ,"EducationField"])

#PercentSalaryHike
ggplot(data=attrition.train,aes(x=PercentSalaryHike))+geom_bar( fill="steelblue")
ggplot(data = attrition.full[!is.na(attrition.full$PercentSalaryHike),],aes(x=PercentSalaryHike,fill=Attrition))+geom_bar(position="fill")+ylab("Frequency")
#It seem that employees with the larger PercentSalaryHike will leave company. Why? On the other hand, for less than 10% of people with the largest PercentSalaryHike Attrition=Yes 
#People for whom Attrition=Yes is largest:
filter(attrition.train, PercentSalaryHike == 24)
#All of them have: PerformanceRating=Outstanding & BirthDate in March XD & mostly Department=Research & Development 
#People for whom Attrition=Yes is smalest:
filter(attrition.train, PercentSalaryHike == 25)
#All of them have: PerformanceRating=Outstanding & BirthDate in March XD & mostly Department=Research & Development 

#PercentSalaryHike is relevant, & therefore I will fill it using  regression model
boxplot(attrition.train$PercentSalaryHike)
boxplot.stats(attrition.full$PercentSalaryHike)
upper.whisker <- boxplot.stats(attrition.full$PercentSalaryHike)$stats[5]
outlier.filter <- attrition.full$PercentSalaryHike < upper.whisker
PercentSalaryHike.equation = "PercentSalaryHike ~ PerformanceRating + Department + BirthDate+Gender+WorkLifeBalance+JobInvolvement"
PercentSalaryHike.model <- lm(
  formula = PercentSalaryHike.equation, 
  data = attrition.full[outlier.filter,]
)
PercentSalaryHike.row <- attrition.full[
  is.na(attrition.full$PercentSalaryHike), 
  c("PerformanceRating", "Department", "BirthDate","Gender","WorkLifeBalance","JobInvolvement")
  ]
PercentSalaryHike.predictions <- predict(PercentSalaryHike.model, newdata=PercentSalaryHike.row)
attrition.full[is.na(attrition.full$PercentSalaryHike), "PercentSalaryHike"] <- PercentSalaryHike.predictions

#TrainingTimesLastYear
ggplot(data = attrition.train[!is.na(attrition.train$TrainingTimesLastYear),],aes(x=TrainingTimesLastYear,fill=Attrition))+geom_bar()

ggplot(data=attrition.train,aes(x=TrainingTimesLastYear))+geom_bar( fill="steelblue")
#Filling TrainingTimesLastYear - most frequent
attrition.full$TrainingTimesLastYear[is.na(attrition.full$TrainingTimesLastYear)==TRUE] <- 2
#attrition.full[ ,TrainingTimesLastYear] <- as.factor(attrition.full[ ,TrainingTimesLastYear])

#Converting BirthDate into numeric
library(lubridate)
attrition.full$BirthDate <- ymd(attrition.full$BirthDate)

attrition.full<-select(attrition.full,-c(StandardHours,Over18,JobRole,EmployeeCount,EmployeeNumber,X))

#Convert into factors
#cols<-c("JobLevel","JobRole","StockOptionLevel","EnvironmentSatisfaction","Education","JobInvolvement","JobSatisfaction","RelationshipSatisfaction","PerformanceRating","WorkLifeBalance","OverTime","MaritalStatus","Gender","Department","BusinessTravel","Attrition")
#for (j in cols){
# attrition.full[ ,j] <- as.factor(attrition.full[ ,j])


# Other Correlations
attrition.full2<-select(attrition.full,c(YearsWithCurrManager,YearsSinceLastPromotion,YearsInCurrentRole,YearsAtCompany,Attrition))
df<-data.frame(attrition.full2)
attrition.full3<-select(attrition.full,c(StockOptionLevel,RelationshipSatisfaction,PerformanceRating,PercentSalaryHike,OverTime,Attrition))
df2<-data.frame(attrition.full3)
attrition.full4<-select(attrition.full,c(JobLevel,JobInvolvement,HourlyRate,Gender,EnvironmentSatisfaction,EducationField,Education,Attrition))
df3<-data.frame(attrition.full4)
attrition.full5<-select(attrition.full,c(WorkLifeBalance,TrainingTimesLastYear,TotalWorkingYears,JobSatisfaction,MonthlyIncome,MaritalStatus,Attrition))
df4<-data.frame(attrition.full5)
attrition.full6<-select(attrition.full,c(NumCompaniesWorked,MonthlyRate,DistanceFromHome,Department,DailyRate,BusinessTravel,BirthDate,Attrition))
df5<-data.frame(attrition.full6)

# For every generated df, do correlation plot (change df into df, df2, df3, df4 then df5.)
# A low value for chi-square means there is a high correlation between your two sets of data.
library(tidyverse)
library(lsr)
library(purrr)
# function to get chi square p value and Cramers V
f = function(x,y) {
  tbl = df5 %>% select(x,y) %>% table()
  chisq_pval = round(chisq.test(tbl)$p.value, 4)
  cramV = round(cramersV(tbl), 4) 
  data.frame(x, y, chisq_pval, cramV) }

# create unique combinations of column names
# sorting will help getting a better plot (upper triangular)
df_comb = data.frame(t(combn(sort(names(df5)), 2)), stringsAsFactors = F)

# apply function to each variable combination
df_res = map2_df(df_comb$X1, df_comb$X2, f)

# plot results
df_res %>%
  ggplot(aes(x,y,fill=chisq_pval))+
  geom_tile()+
  geom_text(aes(x,y,label=cramV))+
  scale_fill_gradient(low="red", high="yellow")+
  theme_classic()

#df: everything except YearsSinceLastPromotion - other variables are fine for Attrition ML
#Plot YearsSinceLastPromotion  VS Attrition
ggplot(data = attrition.full[!is.na(attrition.full$YearsSinceLastPromotion),],aes(x=YearsSinceLastPromotion,fill=Attrition))+geom_bar(position="fill")

#df2: there are correlations between variables:
#PerformanceRating & PercentSalaryHike:
ggplot(data = attrition.full[!is.na(attrition.full$PercentSalaryHike),],aes(x=PercentSalaryHike,fill=PerformanceRating))+geom_histogram()
#PerformanceRating should be ignored during the ML model building
#Attrition & OverTime:
ggplot(data = attrition.full[!is.na(attrition.full$OverTime),],aes(x=OverTime,fill=Attrition))+geom_bar(position="fill")
#Good variables for ML model building: OverTime,PercentSalaryHike & StockOptionLevel

#df3: Good variables: JobLevel, HourlyRate, JobInvolment, EnvironmentSatisfction,EducationField
ggplot(data = attrition.full[!is.na(attrition.full$JobLevel),],aes(x=JobLevel,fill=Attrition))+geom_bar(position="fill")
ggplot(data = attrition.full[!is.na(attrition.full$HourlyRate),],aes(x=HourlyRate,fill=Attrition))+geom_histogram()

#df4: Good variables: WorkLifeBalance,TrainingTimesLastYear,TotalWorkingYears,JobSatisfaction,MaritalStatus
#TotalWorkingYears & MonthlyIncome correlated
ggplot(data=attrition.full, aes(x=TotalWorkingYears, y=MonthlyIncome)) +geom_point(aes(color=attrition.full$Attrition))

#df5: Good var: NumCompaniesWorked,DistanceFromHome,Department,BusinessTravel
#2 variables correlated with BirthDate
#MonthlyRate VS Attrition
ggplot(data = attrition.full[!is.na(attrition.full$MonthlyRate),],aes(x=MonthlyRate,fill=Attrition))+geom_histogram()

#Conclusion: Variables for ML: correlated with Attrition but not so with other variables
#NumCompaniesWorked,DistanceFromHome,Department,BusinessTravel,WorkLifeBalance,TrainingTimesLastYear,TotalWorkingYears,JobSatisfaction,MaritalStatus,JobLevel, HourlyRate, JobInvolment, EnvironmentSatisfction,EducationField,OverTime,PercentSalaryHike,StockOptionLevel,YearsWithCurrManager,YearsInCurrentRole,YearsAtCompany
#holdout method1: data=80% training & 20% test set
train_im <- attrition.full[1:LT, c("Attrition","NumCompaniesWorked","DistanceFromHome","Department","BusinessTravel","WorkLifeBalance","TrainingTimesLastYear","TotalWorkingYears","JobSatisfaction","MaritalStatus","JobLevel","HourlyRate","JobInvolvement","EnvironmentSatisfaction","EducationField","OverTime","PercentSalaryHike","StockOptionLevel","YearsWithCurrManager","YearsInCurrentRole","YearsAtCompany")]
test_im<-attrition.full[(LT+1):1470,c("Attrition","NumCompaniesWorked","DistanceFromHome","Department","BusinessTravel","WorkLifeBalance","TrainingTimesLastYear","TotalWorkingYears","JobSatisfaction","MaritalStatus","JobLevel","HourlyRate","JobInvolvement","EnvironmentSatisfaction","EducationField","OverTime","PercentSalaryHike","StockOptionLevel","YearsWithCurrManager","YearsInCurrentRole","YearsAtCompany")]



## holdout masha

smp_size <- floor(0.70 * nrow(train_im)) # getting the 70% of the dataset
train_ind <- sample(seq_len(nrow(train_im)), size = smp_size)

train <- train_im[train_ind, ] # train contains 70%
test <- train_im[-train_ind, ] # our test set contains 30%


model_dt_k<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train, method = "C5.0")
pred.train.dt <- predict(model_dt,test,type = "class")

confusionMatrix(table(test$Attrition,pred.train.dt))

# randomforest

model_rf_y <-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train)

pred.train.rf <- predict(model_rf_y,test)

confusionMatrix(table(test$Attrition,pred.train.rf))
                

# gbm

## cv

#c50
train_control <- trainControl(method="cv", number=10)
model_dt_k<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train, method = "C5.0", trControl=train_control)

pred.train.dt <- predict(model_dt_k,test,type = "raw")

confusionMatrix(table(test$Attrition,pred.train.dt))

#randomforest
train_control <- trainControl(method="cv", number=100)
# fix the parameters of the algorithm
grid <- expand.grid(.fL=c(0), .usekernel=c(FALSE))
# train the model
model_rf_k<-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train,trControl=train_control,tuneGrid=grid)

pred.train.dt <- predict(model_rf_k,test,type = "class")

confusionMatrix(table(test$Attrition,pred.train.dt))



## bootstrappin

# c50
train_control <- trainControl(method="boot", number=10)
model_dt_b <- train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train_im, method = "C5.0", trControl=train_control)

pred.train.dt <- predict(model_dt_b,train_im,type = "raw")

confusionMatrix(table(train_im$Attrition,pred.train.dt))

# randomForest

train_control <- trainControl(method="boot", number=100)
# train the model
model_rf_ha<-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im,trControl=train_control)

pred.train.dt <- predict(model_rf_ha,train_im,type = "class")

confusionMatrix(table(train_im$Attrition,pred.train.dt))







t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))












#ML
#decision tree model

model_dt_k<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train, method = "C5.0")
pred.train.dt <- predict(model_dt,test_im,type = "class")

confusionMatrix(table(test_im$Attrition,pred.train.dt))

mean(pred.train.dt==test_im$Attrition)

t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))


#precision_dt<- t_dt[1,1]/(sum(t_dt[1,]))
#recall_dt<- t_dt[1,1]/(sum(t_dt[,1]))
#precision_dt
#recall_dt
#accuracy_dt<-(t_dt[1,1]+t_dt[2,2])/(sum(t_dt[1,])+sum(t_dt[,1]))
#accuracy_dt

#F1_dt<- 2*precision_dt*recall_dt/(precision_dt+recall_dt)
#F1_dt


#Plotting prediction
predicted.data.dt <- data.frame(pred.train.dt,test_im$Attrition)
predicted.data.dt$rank <- 1:nrow(predicted.data.dt)
p1 <- ggplot(data=predicted.data.dt, aes(x=rank, y=pred.train.dt)) + geom_point(aes(color=test_im$Attrition), alpha=1, shape=4, stroke=2)
p1 + ggtitle("Predicted probabilty of the employees attrition") +
  xlab("Number of people") + ylab("Predicted probabilty of attrition")+labs(color="Test Attrition")

#holdout method2
library(mlbench)

set.seed(1)
print(in_train <- createDataPartition(attrition.full$Attrition, p = 2/5, list = FALSE))
training <- attrition.full[ in_train,]
testing  <- attrition.full[-in_train,]

model_dt_ho<-rpart(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=training,method = "class")

rpart.plot(model_dt_ho)
pred.train.dt_ho <- predict(model_dt_ho,testing,type = "class")


#Task2
confusionMatrix(table(testing$Attrition,pred.train.dt_ho))
#Plotting prediction
predicted.data.dt <- data.frame(pred.train.dt_ho,testing$Attrition)
predicted.data.dt$rank <- 1:nrow(predicted.data.dt)
p1 <- ggplot(data=predicted.data.dt, aes(x=rank, y=pred.train.dt_ho)) + geom_point(aes(color=testing$Attrition), alpha=1, shape=4, stroke=2)
p1 + ggtitle("Predicted probabilty of the employees attrition") +
  xlab("Number of people") + ylab("Predicted probabilty of attrition")+labs(color="Test Attrition")

#bootstrap
# define training control
train_control <- trainControl(method="boot", number=100)
# train the model
model_dt_b<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=attrition.full, method = "rpart", trControl=train_control)


plot(model_dt_b)
stat(model_dt_b)
rpart.plot(model_dt_b)
pred.train.dt_b <- predict(model_dt_b,test_im,type = "class")
confusionMatrix(table(test_im$Attrition,pred.train.dt_b))

#masha
train_control <- trainControl(method="boot", number=100)
train_control
model_dt<- tree(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im, control = train_control)

pred.train.dt <- predict(model_dt,test_im,type = "class")

t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))



#k-fold Cross Validation
train_control <- trainControl(method="cv", number=10)
model_dt_k<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im, method = "C5.0",trControl=train_control)
pred.train.dt <- predict(model_dt_k,test_im,type = "raw")

t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))

# k fold c5.0

train_control <- trainControl(method="cv", number=10)
model_dt_k<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train_im, method = "C5.0", trControl=train_control)

pred.train.dt <- predict(model_dt_k,test_im,type = "raw")

confusionMatrix(table(test_im$Attrition,pred.train.dt))


# boostrappin
train_control <- trainControl(method="boot", number=10)
model_dt_x<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train_im, method = "C5.0", trControl=train_control)

pred.train.dt <- predict(model_dt_x,test_im,type = "raw")

confusionMatrix(table(test_im$Attrition,pred.train.dt))


#masha
model_dt<- tree(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im)

pred.train.dt <- predict(model_dt,test_im,type = "class")

t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))

# summarize results
print(model_dt_k)


############################
#Random Forest

#holdout method1: data=80% training & 20% test set
train_im <- attrition.full[1:LT, c("Attrition","NumCompaniesWorked","DistanceFromHome","Department","BusinessTravel","WorkLifeBalance","TrainingTimesLastYear","TotalWorkingYears","JobSatisfaction","MaritalStatus","JobLevel","HourlyRate","JobInvolvement","EnvironmentSatisfaction","EducationField","OverTime","PercentSalaryHike","StockOptionLevel","YearsWithCurrManager","YearsInCurrentRole","YearsAtCompany")]
test_im<-attrition.full[(LT+1):1470,c("Attrition","NumCompaniesWorked","DistanceFromHome","Department","BusinessTravel","WorkLifeBalance","TrainingTimesLastYear","TotalWorkingYears","JobSatisfaction","MaritalStatus","JobLevel","HourlyRate","JobInvolvement","EnvironmentSatisfaction","EducationField","OverTime","PercentSalaryHike","StockOptionLevel","YearsWithCurrManager","YearsInCurrentRole","YearsAtCompany")]

model_rf<-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im)
# Let's look at the error
plot(model_rf)
importance(model_rf)
pred.train.rf <- predict(model_rf,test_im)
mean(pred.train.rf==test_im$Attrition)

t1<-table(pred.train.rf,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.rf))

#Plotting prediction
predicted.data.rf <- data.frame(pred.train.rf,test_im$Attrition)
predicted.data.rf$rank <- 1:nrow(predicted.data.rf)
p1 <- ggplot(data=predicted.data.rf, aes(x=rank, y=pred.train.rf)) + geom_point(aes(color=test_im$Attrition), alpha=1, shape=4, stroke=2)
p1 + ggtitle("Predicted probabilty of the employees attrition") +
  xlab("Number of people") + ylab("Predicted probabilty of attrition")+labs(color="Test Attrition")


#holdout method2
library(mlbench)

set.seed(1)
in_train <- createDataPartition(attrition.full$Attrition, p = 2/5, list = FALSE)
training <- attrition.full[ in_train,]
testing  <- attrition.full[-in_train,]

model_rf<-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=training)
# Let's look at the error
plot(model_rf)
importance(model_rf)
pred.train.rf <- predict(model_rf,testing)
mean(pred.train.rf==testing$Attrition)

t1<-table(pred.train.rf,testing$Attrition)

#Task2
confusionMatrix(table(testing$Attrition,pred.train.rf))

#Plotting prediction
predicted.data.rf <- data.frame(pred.train.rf,testing$Attrition)
predicted.data.rf$rank <- 1:nrow(predicted.data.rf)
p1 <- ggplot(data=predicted.data.rf, aes(x=rank, y=pred.train.rf)) + geom_point(aes(color=testing$Attrition), alpha=1, shape=4, stroke=2)
p1 + ggtitle("Predicted probabilty of the employees attrition") +
  xlab("Number of people") + ylab("Predicted probabilty of attrition")+labs(color="Test Attrition")

#bootstrap
# define training control
train_control <- trainControl(method="boot", number=100)
# train the model
model_rf_b<-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im,trControl=train_control)

pred.train.dt <- predict(model_rf_b,test_im,type = "class")

t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))

plot(model_rf_b)
stat(model_rf_b)
#pred.train.rf_b <- predict(model_rf_b,testing)
#confusionMatrix(table(testing$Attrition,pred.train.rf_b))

#k-fold Cross Validation
train_control <- trainControl(method="cv", number=10)
# fix the parameters of the algorithm
grid <- expand.grid(.fL=c(0), .usekernel=c(FALSE))
# train the model
model_rf_k<-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im,trControl=train_control,tuneGrid=grid)
pred.train.dt <- predict(model_rf_k,test_im,type = "class")

t_dt<-table(pred.train.dt,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.dt))

# summarize results
plot(model_rf_k)

print(model_rf_k)



model_dt_k<-train(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data=train_im, method = "C5.0")

pred.train.dt <- predict(model_dt_k,test_im,type = "class")

confusionMatrix(table(test_im$Attrition,pred.train.dt))


model_rf_y <-randomForest(Attrition~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=train_im)

pred.train.rf <- predict(model_rf_y,test_im)

confusionMatrix(table(test_im$Attrition,pred.train.rf))

# Let's look at the error
plot(model_rf)
importance(model_rf)
pred.train.rf <- predict(model_rf,test_im)
mean(pred.train.rf==test_im$Attrition)

t1<-table(pred.train.rf,test_im$Attrition)
confusionMatrix(table(test_im$Attrition,pred.train.rf))


