# reading data from the .csv file
data <- read.csv("bench3h.csv")

# Extracting data and converting from micro seconds to seconds
ntHash2 <- data$ntHash2/1000000

#plotting data beggining with NTHash
valori_ascisse <- c(1, 2, 4, 6, 8)
etichette_ascisse <- c("500k", "1M", "2M", "4M", "8M")

plot(valori_ascisse, ntHash2, xlab = "Numero di sequenze", ylab = "Tempo di esecuzione in secondi", 
     ylim=c(0,700), pch = 16, col = "blue", xaxt = "n")
lines(valori_ascisse, ntHash2, type = "l", col = "blue")

axis(1, at = valori_ascisse, labels = etichette_ascisse)

#-----MurmurHash
murmurH <- data$Murmur3/1000000
points(valori_ascisse,murmurH,pch=16,col="red")
lines(valori_ascisse, murmurH, type = "l", col= "red")

#-----CityHash
cityH <- data$CityHash128/1000000
points(valori_ascisse, cityH, pch=16, col="green")
lines(valori_ascisse, cityH, typer = "l", col= "green")

legend("topleft", legend = c("ntHash2", "MurmurHash", "CityHash"),
       col = c("blue", "red", "green"), pch = 16, lty = 1)

title(main = "Grafico dei Tempi di Esecuzione con 3 Hash", col.main = "black", font.main = 1)
