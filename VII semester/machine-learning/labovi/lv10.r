install.packages(c("arules", "arulesViz"))
library(arules)
library(arulesViz)
data(Groceries)
data(Adult)

# Zadatak 1
itemsets <- apriori(Groceries, parameter = list(minlen=1, maxlen=1, support=0.15, target="frequent itemsets"))
inspect(sort(itemsets, by="support"))
# Svi proizvodi imaju minumalno 0.15 support

# Zadatak 2
# a
itemsets2 <- apriori(Groceries, parameter = list(minlen=2, maxlen=2, support=0.03, target="frequent itemsets"))
inspect(sort(itemsets2, by="support"))
# 19 item setova zadrzi dva proizvoda i minimalni support iznosi 0.03
# b 
plot(itemsets2, method="graph", control=list(type="items"))
# Plot predstavlja veze izmedu pojedinih proizvoda, s kojim se artiklom koji artikal najcesce pojavljuje

# Zadatak 3
# a
itemsets3 <- eclat(Adult, parameter = list(supp = 0.7, minlen = 3))
inspect(sort(itemsets3, by="support"))
# Napravljena su 4 item seta
# b
plot(itemsets3, method="graph", control=list(type="items"))
