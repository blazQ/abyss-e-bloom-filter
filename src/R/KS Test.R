#Script per valutare la distribuzione dei dati

#NtHash2 ---------

#Test K-S
dataNt <- read.csv("nthashvalue.csv")
ks_resultNt <- ks.test(dataNt, "punif", min(dataNt), max(dataNt))
print(ks_resultNt)

#Plot
dataNt <- as.numeric(as.character(dataNt$X8683982964936228251)) #conversione da notazione scientifica
hist(dataNt, freq = FALSE, main = "Distribuzione dei dati", 
     xlab = "Valori", ylab = "Densità",col="green")

min_val <- min(dataNt)
max_val <- max(dataNt)
curve(dunif(x, min_val, max_val), add = TRUE,
      col = "blue", lwd = 2, n = 1001, from = min_val, to = max_val)

#---------------------------
#MurmurHash3
dataMur <- read.csv("murmur.csv")
ks_resultM <- ks.test(dataMur, "punif", min(dataMur), max(dataMur))
print(ks_resultM)


#------------------------
#CityHash
dataCity <- read.csv("city.csv")
ks_resultCity <- ks.test(dataCity, "punif", min(dataCity), max(dataCity))
print(ks_resultCity)

