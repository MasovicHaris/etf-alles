install.packages("factoextra")
install.packages("cluster")
install.packages("NbClust")
install.packages("ISLR")

library("factoextra")
library("cluster")
library("NbClust")
library("ISLR")

set.seed(2)
x<-matrirnorm(50*2),ncol=2)
x[1:25 ,1]<-x[1:25,1]+3
x[1:25 ,2]<-x[1:25,2]-4

km.out<-kmeans(x,2,nstart=20)
km.out3<-kmeans(x, 3, nstart=20)

plot(x,col=(km.out3$cluster +1), main="K-Means Rezultati za K=3", xlab ="", ylab="", pch=20, cex=2)


## 1 - a

ds = data("USArrests")
#dataSkalirana = scale(ds) # radi ovdje šta hoš
View(ds)
ds = USArrests
set.seed(123)
km.res1 = kmeans(USArrests, 2, nstart=30)
fviz_nbclust(ds, kmeans, method="wss", k.max=20)
fviz_nbclust(ds, kmeans, method="silhouette", k.max=20)
fviz_nbclust(ds, kmeans, method="gap_stat", k.max=20)

km.out <- kmeans(ds, 2, nstart=20)
km.out$cluster
plot(x,col=(km.out$cluster+1), main="K-Means Rezultati...", xlab="", ylab="", pch=20, cex=2)

## 1 - b

NbClust(ds, distance = "euclidean", min.nc = 2, max.nc = 20,method = "kmeans", index = "all")

# 2 - broj clustera
dsModel = eclust(ds, FUNcluster="kmeans", k=2, hc_metric="euclidean")
silhouette(dsModel$cluster, dist(ds))
fviz_silhouette(dsModel)

# priprema
dsCollege = data("College")
View(dsCollege)
College$is_elite <- ifelse(College$Top10perc >= 50, 1, 0)
View(College)
College$accept_rate <- (College$Accept / College$Apps)

College$is_elite = as.factor(College$is_elite)
College$Private = as.factor(College$Private)

set.seed(123)
dist_gower <- daisy(College, metric="gower")
gower_mat <- as.matridist_gower)
dist_gower

College[which(gower_mat == min(gower_mat[gower_mat != 0]), arr.ind = TRUE)[1,],]
pam <- pam(dist.gower, diss = TRUE, k = 3)
College[pam$medoids, ]