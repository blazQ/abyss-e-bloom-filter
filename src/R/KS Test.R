#Script to evaluate uniform distribuition of the data
options(scipen = 999)

#NtHash2 ---------

#Reading and adjusting data
dataNt <- read.csv("nthashDis.csv")
colnames(dataNt)[1] <- "Values"
dataNt$Values <- as.numeric(as.character(dataNt$Values))

# Kolmogorov-Smirnov test on the data
ks_resultNt <- ks.test(dataNt$Values, "punif", min(dataNt$Values), max(dataNt$Values))
print(ks_resultNt)

#Plot

hist(dataNt$Values, freq = FALSE, main = "Distribuzione dei dati NTHash", 
     xlab = "Valori", ylab = "Densità",col="green")

min_val <- min(dataNt$Values)
max_val <- max(dataNt$Values)
curve(dunif(x, min_val, max_val), add = TRUE,
      col = "blue", lwd = 2, n = 1001, from = min_val, to = max_val)

#---------------------------
#MURMURHASH3 TEST

#Reading and adjusting data
dataMur <- read.csv("murmurDis.csv")
colnames(dataMur)[1] <- "Values"
dataMur$Values <- as.numeric(as.character(dataMur$Values))

# Kolmogorov-Smirnov test on the data
ks_resultM <- ks.test(dataMur$Values, "punif", min(dataMur$Values), max(dataMur$Values))
print(ks_resultM)

#Plot
hist(dataMur$Values, freq = FALSE, main = "Distribuzione dei dati di MurmurHash", 
     xlab = "Valori", ylab = "Densità", col = "green")

min_val <- min(dataMur$Values)
max_val <- max(dataMur$Values)

curve(dunif(x, min_val, max_val), add = TRUE,
      col = "blue", lwd = 2, n = 1001, from = min_val, to = max_val)



#------------------------
#CITYHASH TEST

#Reading and adjusting data
dataCity <- read.csv("cityDis.csv")
colnames(dataCity)[1] <- "Values"
dataCity$Values <- as.numeric(as.character(dataCity$Values))

# Kolmogorov-Smirnov test on the data
ks_resultCity <- ks.test(dataCity$Values, "punif", min(dataCity$Values), max(dataCity$Values))
print(ks_resultCity)

#Plot
hist(dataCity$Values, freq = FALSE, main = "Distribuzione dei dati di CityHash", 
     xlab = "Valori", ylab = "Densità", col = "green")

min_val <- min(dataCity$Values)
max_val <- max(dataCity$Values)

curve(dunif(x, min_val, max_val), add = TRUE,
      col = "blue", lwd = 2, n = 1001, from = min_val, to = max_val)







