library(tidyverse)
library(scales)
library(ggthemes)
library(kableExtra)
library(plotly)
library(purrr)
library(readr)
library(scales)
library(clustertend)
library(stringr)
library("factoextra")
library("cluster")
library("NbClust")
library(flexclust)


# mozda fali koji library

options(scipen = 999)

setwd("C:\\Users\\Amir\\Desktop\\MU\\DZ3\\Code") # promijeniti path i izcitati podatke !!
fifa_data <- read.csv(file = 'data.csv', encoding = "UTF-8")

# trebamo definisati sve pozicije u igrici radi formiranja
# finalnih grupa koje ce biti ukljucene u clustering
positions <- unique(fifa_data$Position)

gk <- "GK"
defs <- positions[str_detect(positions, "B$")]
mids <- positions[str_detect(positions, "M$")]
f1 <- positions[str_detect(positions, "F$")]
f2 <- positions[str_detect(positions, "S$")]
f3 <- positions[str_detect(positions, "T$")]
f4 <- positions[str_detect(positions, "W$")]
fwds <- c(as.character(f1), as.character(f2), as.character(f3), as.character(f4))


# position grup ce predsavljati ili golman ili odbrana ili mid ili napad
fifa_data <- fifa_data %>% 
  mutate(PositionGroup = ifelse(Position %in% gk, "GK", ifelse(Position %in% defs, "DEF", ifelse(Position %in% mids, "MID", ifelse(Position %in% fwds, "FWD", "Unknown")))))

# definisati cemo grupnu klasu po pitanju broja godina, koju mozemo iskoristiti
# za definisanje boljeg clustera tj. kao parametar za prikaz slicnih igraca

fifa_data <- fifa_data %>%
  mutate(AgeGroup = ifelse(Age <= 20, "20 and under", ifelse(Age > 20 & Age <=25, "21 to 25", ifelse(Age > 25 & Age <= 30, "25 to 30", ifelse(Age > 30 & Age <= 35, "31 to 35", "Over 35"))))) %>%
  mutate(AttackingRating = (Finishing + LongShots + Penalties + ShotPower + Positioning) /5)

fifa_data <- fifa_data %>%
  mutate(ValueMultiplier = ifelse(str_detect(Value, "K"), 1000, ifelse(str_detect(Value, "M"), 1000000, 1))) %>%
  mutate(ValueNumeric_pounds = as.numeric(str_extract(Value, "[[:digit:]]+\\.*[[:digit:]]*")) * ValueMultiplier)

fifa_data <- fifa_data %>%
  mutate(WageMultiplier = ifelse(str_detect(Wage, "K"), 1000, ifelse(str_detect(Wage, "M"), 1000000, 1))) %>%
  mutate(WageNumeric_pounds = as.numeric(str_extract(Wage, "[[:digit:]]+\\.*[[:digit:]]*")) * WageMultiplier)

# pregled uniformnosti rating playera iz igrice

fifa_data %>%
  ggplot(aes(x= Overall)) +
  geom_histogram(color = "white", fill = "blue") +
  ggtitle("Raspored uniformnosti overall rating-a za playere") +
  theme_fivethirtyeight()

# uniformna raspodjela rating-a za playere, shodno tome nije potrebno 
# cilj tj. ideja trenutnog clusteringa jeste da na osnovu grupisanih podjela generise clustere koji daju slicne igrace u svakom clusteru
# po svojim karakteristikama
# tj. pocetni problem je da nekom manageru u igrici, omoguci da izabere igrace koje su mu potrebni sa strane pozicije ratinga, cijene etc


# ako pozicija je unkown ili ako je to golman
# uvest cemo RoomToGrow potencijal - overlal

data_cluster <- fifa_data %>%
  filter(PositionGroup != "Unknown") %>%
  filter(PositionGroup != "GK") %>%
  mutate(RoomToGrow = Potential - Overall) %>%
  select_if(is.numeric) %>%
  select(-ID, -Jersey.Number, -starts_with("Value"), - starts_with("Wage"), -starts_with("GK"), -Overall)

# hopkins, ocekivano <0.5
# hopkins(data_cluster, 50)


## ---------------------------- implementacija algoritama ----------------------------
## ---------------------------- K-means - Masovic Haris   ---------------------------- 

# prvo treba skalirati podatke
scaled_data <- scale(data_cluster)

set.seed(109)
# koristiti wss tj. total within sum of squares error
wss <- 0
# definisat cemo 30 clustera
for (j in 1:30) {
  km.out <- kmeans(scaled_data, centers = j, nstart = 20) # ovdje cemo koristiti custom kmeans funkciju
  wss[j] <- km.out$tot.withinss
}

wss_df <- data.frame(num_cluster = 1:30, wgss = wss)

# trebamo naci optimalno k
ggplot(data = wss_df, aes(x=num_cluster, y= wgss)) + 
  geom_line(color = "lightgrey", size = 2) + 
  geom_point(color = "blue", size = 4) +
  theme_fivethirtyeight() +
  labs(title = "Prikaz wss clustera za dataset, elbow metoda")

# definisemo k
k <- 8

# k-means model
wisc.km <- kmeans(scale(data_cluster), centers = k, nstart = 20)

# treba dodati za svakog igraca u kojem clusteru spada
cluster_data <- fifa_data %>%
  filter(PositionGroup != "Unknown") %>%
  filter(PositionGroup != "GK") %>%
  mutate(Cluster = wisc.km$cluster)

# izaberimo kljucne varijable
cluster_analysis <- cluster_data %>%
  select(ID, Name, Club, Age, PositionGroup, Overall, Cluster, ValueNumeric_pounds)

# prikaz clustera
table(cluster_analysis$Cluster, cluster_analysis$PositionGroup)

# novi cluster grupiran po clusteru i desc overall
cluster_arranged <- cluster_analysis %>%
  mutate(Cluster = as.character(Cluster)) %>%
  arrange(desc(Overall)) %>% 
  group_by(Cluster)

# prikaz igraca, crtanje top 20 ljudi u svakom clusteru
# tj. vrstama po poziciji i dodatni filter da li odabrani player ima manje od 28g

p  <- cluster_analysis %>%
  mutate(Cluster = paste("Cluster: ", Cluster, sep = "")) %>%
  arrange(desc(Overall)) %>% 
  group_by(Cluster) %>%
  slice(1:20) %>%
  mutate(Under28 = ifelse(Age < 28, "Yes", "No")) %>%
  ggplot(aes(x= Overall, y= ValueNumeric_pounds)) +
  geom_point(position = "jitter", shape = 21, color = "black", size = 2, aes(text = paste(Name, PositionGroup), fill = Under28)) +
  scale_fill_manual(values = c("blue", "red")) +
  scale_y_continuous(labels = dollar_format(prefix = "â¬")) +
  ggtitle("Najbolji playeri u svom clusteru") +
  facet_wrap(~ factor(Cluster), scales = "free", ncol = 2) +
  theme_fivethirtyeight() +
  theme(legend.position = "none", strip.text = element_text(face = "bold", size = 12))

# plot output
ggplotly(p, height = 700, width = 900)

# vraca slicne igrace u odnosu na onog koji se proslijedi
vratiSlicne <- function(playerId, kolikoIgracaSlicnih, eps) {

  cluster_filter <- cluster_analysis[cluster_analysis$ID == playerId,]$Cluster
  player_value <- cluster_analysis[cluster_analysis$ID == playerId,]$ValueNumeric_pounds
  player_group <- cluster_analysis[cluster_analysis$ID == playerId,]$PositionGroup
  
  cluster_analysis %>%
    filter(Cluster == cluster_filter, ValueNumeric_pounds >= (player_value * (1 - eps)) & ValueNumeric_pounds <= (player_value * (1 + eps)),
           PositionGroup == player_group, ID != playerId) %>%
    head(kolikoIgracaSlicnih)
}

# eksterni i interni kriteriji validacije

# interna validacija - sillhoute
dsModel = eclust(scaled_data, FUNcluster="kmeans", k=8, hc_metric="euclidean")
silhouette(dsModel$cluster, dist(scaled_data))
fviz_silhouette(dsModel)

# externa validacija - rand index
tabela <- table(cluster_analysis$Cluster, cluster_analysis$PositionGroup)

tabela2 <- matrix(1:16, nrow = 8, ncol = 2)
for (j in 1:8) {
  if(which.max(tabela[j,]) == 1) tabela2[j,] <- c('FWD', 'MID')
  if(which.min(tabela[j,]) == 2) tabela2[j,] <- c('DEF', 'MID')
  if(which.min(tabela[j,]) == 3) tabela2[j,] <- c('FWD', 'DEF')
}

cluster_analysis <- cluster_analysis %>% 
  mutate(positionResult = ifelse(PositionGroup %in% tabela2[Cluster,], Cluster, 0))


randIndex(cluster_analysis$Cluster, cluster_analysis$positionResult)


## ---------------------------- DBSEARCH - Muminovic Amir   ---------------------------- 

nadjiSusjede <- function(D, P, eps) {
  # Pronadji sve tacke iz D koje su udaljeni do eps od tacke p
  susjedi = matrix(nrow = nrow(D), ncol = ncol(D));
  counter = 0
  for (i in c(1:nrow(D))) {
    currentPoint = D[i,]
    if (dist(rbind(currentPoint,P)) < eps){
      counter = counter + 1
      susjedi[counter,] = currentPoint
    }
  }
  
  return(susjedi[1:counter,])
}

povecajCluster <- function(D, labele, P, susjedi, C, eps, MinPts) {
  
  labele[P] = C

  i = 1
  while ( i <= nrow(susjedi)){
    sljedecaTacka = susjedi[i,]
    if (labele[i] == -1) {
      labele[i] = C
    }
    else if (labele[i] == 0) {
      labele[i] = C
      
      sljedeceSusjedstvo = nadjiSusjede(D, sljedecaTacka, eps)
      
      if (length(sljedeceSusjedstvo) >= MinPts) {
        susjedi = rbind(susjedi, sljedeceSusjedstvo)
      }
    }
    i = i + 1
  }
}


dbsearch <- function(D, eps, MinPts) {
  labele = replicate(nrow(D), 0)
  
  clusterID = 0
  
  for (i in c(1:nrow(D))){
    print(i)
    if (labele[i] == 0) {
      #Nadji susjede moje
      susjedi = nadjiSusjede(D, D[i,], eps)
      
      if (length(susjedi) < MinPts) {
        labele[i] = -1
      }
      else {
        clusterID = clusterID + 1
        povecajCluster(D, labele, i, susjedi, clusterID, eps, MinPts)
      }
    }
  }
  
  return(labele)
}

# Poziv fje
scaled_data <- scale(data_cluster)

library(dbscan)
kNNdistplot(scaled_data, k = length(scaled_data)+1)

res.Cluster <- dbsearch(section, 160, 150)

#Reuse

cluster_data <- fifa_data %>%
  filter(PositionGroup != "Unknown") %>%
  filter(PositionGroup != "GK") %>%
  mutate(Cluster = res$cluster)

# izaberimo kljucne varijable
cluster_analysis <- cluster_data %>%
  select(ID, Name, Club, Age, PositionGroup, Overall, Cluster, ValueNumeric_pounds)

# prikaz clustera
table(cluster_analysis$Cluster, cluster_analysis$PositionGroup)

# novi cluster grupiran po clusteru i desc overall
cluster_arranged <- cluster_analysis %>%
  mutate(Cluster = as.character(Cluster)) %>%
  arrange(desc(Overall)) %>% 
  group_by(Cluster)

# prikaz igraca, crtanje top 20 ljudi u svakom clusteru
# tj. vrstama po poziciji i dodatni filter da li odabrani player ima manje od 28g

p  <- cluster_analysis %>%
  mutate(Cluster = paste("Cluster: ", Cluster, sep = "")) %>%
  arrange(desc(Overall)) %>% 
  group_by(Cluster) %>%
  slice(1:20) %>%
  mutate(Under28 = ifelse(Age < 28, "Yes", "No")) %>%
  ggplot(aes(x= Overall, y= ValueNumeric_pounds)) +
  geom_point(position = "jitter", shape = 21, color = "black", size = 2, aes(text = paste(Name, PositionGroup), fill = Under28)) +
  scale_fill_manual(values = c("blue", "red")) +
  scale_y_continuous(labels = dollar_format(prefix = "â¬")) +
  ggtitle("Najbolji playeri u svom clusteru") +
  facet_wrap(~ factor(Cluster), scales = "free", ncol = 2) +
  theme_fivethirtyeight() +
  theme(legend.position = "none", strip.text = element_text(face = "bold", size = 12))

# plot output
ggplotly(p, height = 700, width = 900)

# vraca slicne igrace u odnosu na onog koji se proslijedi
vratiSlicne <- function(playerId, kolikoIgracaSlicnih, eps) {
  
  cluster_filter <- cluster_analysis[cluster_analysis$ID == playerId,]$Cluster
  player_value <- cluster_analysis[cluster_analysis$ID == playerId,]$ValueNumeric_pounds
  player_group <- cluster_analysis[cluster_analysis$ID == playerId,]$PositionGroup
  
  cluster_analysis %>%
    filter(Cluster == cluster_filter, ValueNumeric_pounds >= (player_value * (1 - eps)) & ValueNumeric_pounds <= (player_value * (1 + eps)),
           PositionGroup == player_group, ID != playerId) %>%
    head(kolikoIgracaSlicnih)
}

# eksterni i interni kriteriji validacije

# interna validacija - sillhoute
silhouette(res$cluster, dist(data_cluster))

# externa validacija - rand index
tabela <- table(cluster_analysis$Cluster, cluster_analysis$PositionGroup)

tabela2 <- matrix(1:16, nrow = 8, ncol = 2)
for (j in 1:8) {
  if(which.max(tabela[j,]) == 1) tabela2[j,] <- c('FWD', 'MID')
  if(which.min(tabela[j,]) == 2) tabela2[j,] <- c('DEF', 'MID')
  if(which.min(tabela[j,]) == 3) tabela2[j,] <- c('FWD', 'DEF')
}

cluster_analysis <- cluster_analysis %>% 
  mutate(positionResult = ifelse(PositionGroup %in% tabela2[Cluster,], Cluster, 0))


randIndex(cluster_analysis$Cluster, cluster_analysis$positionResult)
