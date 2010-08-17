pdf("ZBS-vs.pdf", width=14, height=8, family="Times")
par(xpd=NA, mfrow=c(2,3), mar=c(6,4,1.5,0.5), cex=1.1) # margin: bottom left top right

num_FFD <- c(300, 400, 500, 600, 700, 800, 900, 1000)
legend <- c("DSA", "D2VHU")

# # # # # # # # Average latency # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# # # # # # # # flat # # # # # # # #
# DSA
avg_lat <- c(9.430780, 11.485220, 13.166376, 14.812940, 16.062326, 17.000750, 18.177999, 19.364155)
plot(num_FFD, avg_lat, type='o', pch=1, ylim=c(2,20),
	xlab='Number of nodes', ylab='Average latency (slots)', main='(a) "Flat" tree')

# D2VHU
avg_lat <- c(2.537583, 2.796554, 3.038903, 3.165081, 3.425238, 3.457808, 3.604372, 3.769868)
lines(num_FFD, avg_lat, type='o', pch=2)

# # # # # # # # normal # # # # # # # #
# DSA
avg_lat <- c(13.268541, 15.270854, 16.723609, 18.522221, 19.616419, 20.371414, 21.445719, 22.346408)
plot(num_FFD, avg_lat, type='o', pch=1, ylim=c(2,23),
	xlab='Number of nodes', ylab='Average latency (slots)', main='(b) Normal tree')

# D2VHU
avg_lat <- c(4.381564, 4.805202, 5.052102, 5.292424, 5.407700, 5.618335, 5.788207, 5.953091)
lines(num_FFD, avg_lat, type='o', pch=2)

legend(400, -7.5, legend=c('DSA', 'D2VHU'), pch=c(1,2), ncol=2)

# # # # # # # # tall # # # # # # # #
# DSA
avg_lat <- c(15.099361, 16.792427, 18.574422, 20.065302, 21.408511, 21.947956, 23.361496, 24.076928)
plot(num_FFD, avg_lat, type='o', pch=1, ylim=c(2,25),
	xlab='Number of nodes', ylab='Average latency (slots)', main='(c) "Tall" tree')

# D2VHU
avg_lat <- c(6.117536, 6.491474, 6.998628, 7.170593, 7.388546, 7.625382, 7.842445, 7.872848)
lines(num_FFD, avg_lat, type='o', pch=2)

# # # # # # # # Number of associated devices # # # # # # # # # # # # # # # # # # # # # # # # #
par(mar=c(4,4,1.5,0.5))

# # # # # # # # flat # # # # # # # #
# DSA
num_assoc <- c(52.940000, 77.170000, 101.890000, 124.730000, 148.830000, 171.860000, 194.850000, 216.740000)
num_assoc <- num_assoc / num_FFD
plot(num_FFD, num_assoc, type='o', pch=1, ylim=c(0.1,0.25),
	xlab='Number of nodes', ylab='Fraction of associated nodes', main='(d) "Flat" tree')

# D2VHU
num_assoc <- c(41.85, 60.10, 78.53, 95.85, 114.42, 129.50, 147.05, 162.39)
num_assoc <- num_assoc / num_FFD
lines(num_FFD, num_assoc, type='o', pch=2)

# # # # # # # # normal # # # # # # # #
# DSA
num_assoc <- c(118.05, 172.92, 228.50, 280.39, 335.66, 394.32, 448.40, 501.68)
num_assoc <- num_assoc / num_FFD
plot(num_FFD, num_assoc, type='o', pch=1, ylim=c(0.25,0.5),
	xlab='Number of nodes', ylab='Fraction of associated nodes', main='(e) Normal tree')

# D2VHU
num_assoc <- c(89.01, 132.02, 171.08, 210.47, 250.61, 298.31, 329.02, 364.89)
num_assoc <- num_assoc / num_FFD
lines(num_FFD, num_assoc, type='o', pch=2)

# # # # # # # # tall # # # # # # # #
# DSA
num_assoc <- c(186.47, 282.87, 373.82, 466.11, 560.25, 652.40, 737.71, 823.07)
num_assoc <- num_assoc / num_FFD
plot(num_FFD, num_assoc, type='o', pch=1, ylim=c(0.4,0.85),
	xlab='Number of nodes', ylab='Fraction of associated nodes', main='(f) "Tall" tree')

# D2VHU
num_assoc <- c(137.93, 212.24, 281.32, 337.34, 401.40, 472.12, 523.23, 593.78)
num_assoc <- num_assoc / num_FFD
lines(num_FFD, num_assoc, type='o', pch=2)

dev.off()
