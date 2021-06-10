# zadaca 2 - zadatak 3
# konverzija u numericke
# must_convert<-sapply(attrition.full,is.factor)
# M2<-sapply(attrition.full[,must_convert],unclass)    
# attrition.lm<-cbind(attrition.full[,!must_convert],M2) 

attrition.testing = attrition.full

# korak 1 evaluacija modela
reg.fit<-lm(MonthlyIncome~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=attrition.testing)
plot(predict(reg.fit),residuals(reg.fit))
lines(smooth.spline(predict(reg.fit),residuals(reg.fit)),col="red")

sumari = summary(reg.fit)

sumari$adj.r.squared 
sumari$r.squared
MAE(predict(reg.fit), attrition.full$MonthlyIncome)


# korak 2 korelacija rezidualnih vrijednosti

## Q-Q plot
plot(density(reg.fit$residuals), main="Residuals", xlab="Value")
plot(reg.fit, which=2)

## shapiro test
shapiro.test(reg.fit$residuals)

## durbin watston test
dwtest(MonthlyIncome~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=attrition.testing)


# korak 3 - nekonstantna variansa rezidualnih vrijednosti
plot(reg.fit$residuals, attrition.testing$MonthlyIncome, main="Residuals vs Values", xlab="Residuals ", ylab="Values ", pch=19)


# korak 4 uklanjanje outlinera izlazne varijable, everything above 1.3 gotta go, poboljsa model
vectorToClear = as.numeric(names(rstudent(reg.fit)[rstudent(reg.fit)>1]))
attrition.clear = attrition.testing[-vectorToClear,]


reg.fit<-lm(MonthlyIncome~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany,data=attrition.clear)
plot(predict(reg.fit),residuals(reg.fit))
lines(smooth.spline(predict(reg.fit),residuals(reg.fit)),col="red")


sumari = summary(reg.fit)

sumari$adj.r.squared 
sumari$r.squared
MAE(predict(reg.fit), attrition.clear$MonthlyIncome)

# korak 5 epodobne vrijednosti ulaznih varijabli (eng. high leverage points)

hatvalues(reg.fit)[hatvalues(reg.fit)>10*(ncol(attrition.clear[,-10])+1)/nrow(attrition.clear)]

# korak 6 ko-linearnost ulaznih varijabli
vif(reg.fit)

## preostali dio zadatka 2

# lmStepAIC
train.control <- trainControl(method = "cv", number = 10)
step.model <- train(MonthlyIncome~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data = attrition.clear, trControl = train.control, method = "lmStepAIC", trace = FALSE)
step.model$results
step.model$finalModel
summary(step.model$finalModel)

# leapBackward
train.control <- trainControl(method = "cv", number = 10)
step.model <- train(MonthlyIncome~NumCompaniesWorked+DistanceFromHome+Department+BusinessTravel+WorkLifeBalance+TrainingTimesLastYear+TotalWorkingYears+JobSatisfaction+MaritalStatus+JobLevel+HourlyRate+JobInvolvement+EnvironmentSatisfaction+EducationField+OverTime+PercentSalaryHike+StockOptionLevel+YearsWithCurrManager+YearsInCurrentRole+YearsAtCompany, data = attrition.clear, method = "leapBackward", tuneGrid = data.frame(nvmax = 7), trControl = train.control, trace = FALSE)
step.model$results
step.model$finalModel
summary(step.model$finalModel)