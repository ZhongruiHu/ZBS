# D2VHU 

pdf("ZBS-par-pol.pdf", width=12, height=4, family="Times")
par(xpd=TRUE, mfrow=c(1,2), mar=c(4,4.5,1.5,0.5), cex=1.1) # margin: bottom left top right

#pdf("ZBS-par-pol.pdf", width=6, height=8, family="Times")
#par(xpd=TRUE, mfrow=c(2,1), mar=c(4,4.5,1.5,0.5), cex=1.1) # margin: bottom left top right

# fixed degree: use exp1.sh =======================================================================

area_l <- c(100, 120, 140, 160, 180, 200, 220, 240)

# PAR_POL_DEPTH
avg_lat <- c(8.833159, 8.391093, 8.475892, 8.783953, 9.167986, 9.546415, 10.039348, 10.594758)
avg_max_lat <- c(18.44, 17.14, 16.92, 17.29, 18.09, 18.65, 19.42, 20.76)
plot(area_l, avg_lat, type='o', pch=1, ylim=c(7.5,10.7),
	xlab='Area length (m)', ylab='Average latency (slots)', main='(a) Fixed network density')
legend('topleft', legend=c('Depth', 'Depth then slot', 'Slot', 'Slot then depth'), pch=c(1,2,3,4))

# PAR_POL_DEPTH_SLOT
avg_lat <- c(8.150194, 7.785741, 8.060103, 8.316581, 8.707242, 9.146581, 9.693088, 10.041181)
avg_max_lat <- c(16.69, 15.58, 15.84, 16.26, 17.07, 17.67, 18.60, 19.38)
lines(area_l, avg_lat, type='o', pch=2)

# PAR_POL_SLOT
avg_lat <- c(8.103438, 7.671895, 7.677255, 8.205648, 8.472386, 8.872275, 9.292247, 9.842714)
avg_max_lat <- c(15.78, 14.46, 14.56, 15.19, 15.82, 16.68, 17.45, 18.37)
lines(area_l, avg_lat, type='o', pch=3)

# PAR_POL_SLOT_DEPTH
avg_lat <- c(7.928209, 7.553087, 7.623915, 8.002494, 8.377339, 8.829048, 9.296258, 9.753569)
avg_max_lat <- c(15.37, 14.49, 14.43, 15.22, 15.92, 16.53, 17.35, 18.37)
lines(area_l, avg_lat, type='o', pch=4)

# increasing degree: use exp2.sh ==================================================================

num_FFD <- c(300, 400, 500, 600, 700, 800, 900, 1000)
 
# PAR_POL_DEPTH
avg_lat <- c(9.522748, 9.886576, 10.206525, 10.637270, 11.090729, 11.401455, 11.849753, 12.328218)
avg_max_lat <- c(18.45, 19.20, 19.99, 20.64, 21.58, 22.38, 23.37, 24.00)
plot(num_FFD, avg_lat, type='o', pch=1, ylim=c(8.9,12.4),
	xlab='Number of nodes', ylab='Average latency (slots)', main='(b) Fixed simulation area')
legend('topleft', legend=c('Depth', 'Depth then slot', 'Slot', 'Slot then depth'), pch=c(1,2,3,4))

# PAR_POL_DEPTH_SLOT
avg_lat <- c(9.278912, 9.441935, 9.754906, 10.243923, 10.639856, 11.074290, 11.425051, 11.845306)
avg_max_lat <- c(17.58, 18.12, 18.89, 19.67, 20.48, 21.29, 21.98, 22.96)
lines(num_FFD, avg_lat, type='o', pch=2)

# PAR_POL_SLOT
avg_lat <- c(9.215081, 9.325111, 9.664797, 9.981336, 10.303896, 10.769924, 11.089811, 11.381359)
avg_max_lat <- c(17.49, 17.83, 18.10, 18.86, 19.47, 20.38, 21.10, 21.51)
lines(num_FFD, avg_lat, type='o', pch=3)

# PAR_POL_SLOT_DEPTH
avg_lat <- c(8.982480, 9.370987, 9.586215, 9.971699, 10.351797, 10.620194, 10.984016, 11.348175)
avg_max_lat <- c(16.94, 17.63, 17.88, 18.93, 19.27, 19.91, 20.98, 21.41)
lines(num_FFD, avg_lat, type='o', pch=4)

dev.off()

