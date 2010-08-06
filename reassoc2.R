pdf("ZBS-reassoc2.pdf", width=12, height=4, family="Times")
par(xpd=TRUE, mfrow=c(1,2), mar=c(4,4,0,0.5)) # margin: bottom left top right

########################################################
area_length <- c(100, 120, 140, 160, 180, 200, 220, 240)

avg   <-c(0.157200, 0.189097, 0.209082, 0.235234, 0.232840, 0.257775, 0.268946, 0.266181)
stddev<-c(0.407048, 0.456290, 0.471168, 0.517484, 0.505325, 0.532895, 0.546554, 0.543345)

plot(area_length, avg, type="o", pch=1, ylim=c(0.14,0.27),
	ylab="Avg number of reassociation counts per node",	xlab="Area length (l) (fixed network density)")

avg   <-c(0.144500, 0.160972, 0.185561, 0.204844, 0.218827, 0.222875, 0.240785, 0.251406)
stddev<-c(0.383692, 0.414232, 0.440669, 0.472849, 0.485993, 0.488264, 0.512849, 0.523350)

lines(area_length, avg, type="o", pch=2)

legend("bottomright", legend=c("D1VHU", "D1HU"), pch=c(1,2))

#####################################################
num_FFD <- c(300, 400, 500, 600, 700, 800, 900, 1000)

avg   <-c(0.103300, 0.171950, 0.219900, 0.268383, 0.299057, 0.339375, 0.372211, 0.415710)
stddev<-c(0.332810, 0.434377, 0.489637, 0.543557, 0.577897, 0.618809, 0.653931, 0.700982)

plot(num_FFD, avg, type="o", pch=1,
	ylab="Avg number of reassociation counts per node",	xlab="Number of nodes (n) (varying network density)")

avg	  <-c(0.107667, 0.149250, 0.208420, 0.241767, 0.289100, 0.321838, 0.367678, 0.399930)
stddev<-c(0.336761, 0.395379, 0.469788, 0.507591, 0.563059, 0.600173, 0.654592, 0.678562)

lines(num_FFD, avg, type="o", pch=2)

legend("bottomright", legend=c("D1VHU", "D1HU"), pch=c(1,2))

dev.off()
