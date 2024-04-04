#Script to evaluate uniform distribuition of the data

#NtHash2 ---------

#Test K-S
dataNt <- read.csv("nthashvalue.csv")
ks_resultNt <- ks.test(dataNt, "punif", min(dataNt), max(dataNt))
print(ks_resultNt)

#Plot
#Scientific notation conversion
dataNt <- as.numeric(as.character(dataNt$X8683982964936228251)) 
hist(dataNt, freq = FALSE, main = "Distribuzione dei dati NTHash", 
     xlab = "Valori", ylab = "Densità",col="green")

min_val <- min(dataNt)
max_val <- max(dataNt)
curve(dunif(x, min_val, max_val), add = TRUE,
      col = "blue", lwd = 2, n = 1001, from = min_val, to = max_val)

#---------------------------
#MurmurHash3 ---DA FARE
dataMur <- read.csv("murmurDis.csv")
colnames(dataMur)[colnames(dataMur) == "X4afea45b67ee70587872c1c18cd07946"] <- "Values"

ks_resultM <- ks.test(dataMur, "punif", min(dataMur), max(dataMur))
print(ks_resultM)


hist(dataMur, freq = FALSE, main = "Distribuzione dei dati NTHash", 
     xlab = "Valori", ylab = "Densità",col="green")

min_val <- min(dataNt)
max_val <- max(dataNt)
curve(dunif(x, min_val, max_val), add = TRUE,
      col = "blue", lwd = 2, n = 1001, from = min_val, to = max_val)



#------------------------
#CityHash
dataCity <- read.csv("cityDis.csv")
ks_resultCity <- ks.test(dataCity, "punif", min(dataCity), max(dataCity))
print(ks_resultCity)

