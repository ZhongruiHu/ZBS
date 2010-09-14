pdf("ZBS-variants.pdf", width=12, height=8, family="Times")
par(xpd=NA, mfrow=c(2,2), mar=c(6,4,1.5,0.5), cex=1.1) # margin: bottom left top right

area_l <- c(100, 120, 140, 160, 180, 200, 220, 240)
num_FFD <- c(300, 400, 500, 600, 700, 800, 900, 1000)
legend <- c("DVHU", "DHU", "DU", "CVHU", "CHU", "CU", "C")
pch <- c(seq(1,5),15,16)

# # # # # # # # # # # # # # # # # Fixed density # # # # # # # # # # # # # # # # #
# # Average maximum latency # #

# D1VHU
#avg_max_lat <- c(19.09, 18.11, 17.88, 18.62, 18.61, 19.90, 20.14, 20.97)

# D1HU
#avg_max_lat <- c(21.01, 23.63, 25.76, 27.92, 29.14, 31.98, 33.73, 35.57)
#lines(area_l, avg_max_lat, type='o', pch=pch[2])

# D2VHU
avg_max_lat <- c(18.38, 16.89, 17.08, 17.21, 17.92, 18.84, 19.42, 20.47)
plot(area_l, avg_max_lat, type='o', pch=pch[1], ylim=c(18,138),
	xlab='Area length (m)', ylab='Average maximum latency (slots)', main='(a) Fixed network density')
legend(180, -35, legend=legend, pch=pch, ncol=length(legend), bty='o')

# D2HU
avg_max_lat <- c(20.85, 22.40, 24.23, 26.01, 27.12, 29.52, 30.66, 32.29)
lines(area_l, avg_max_lat, type='o', pch=pch[2])

# D2U
avg_max_lat <- c(40.73, 45.12, 48.63, 50.55, 53.21, 56.06, 58.57, 61.31) 
lines(area_l, avg_max_lat, type='o', pch=pch[3])

# CVHU
avg_max_lat <- c(18.28, 16.84, 16.84, 17.27, 17.98, 18.94, 19.60, 20.35)
lines(area_l, avg_max_lat, type='o', pch=pch[4])

# CHU
avg_max_lat <- c(20.74, 22.47, 24.21, 25.94, 27.43, 29.36, 30.77, 32.55)
lines(area_l, avg_max_lat, type='o', pch=pch[5])

# CU
avg_max_lat <- c(41.35, 44.96, 47.98, 50.68, 52.86, 56.17, 58.77, 62.43)
lines(area_l, avg_max_lat, type='o', pch=pch[6])

# C
avg_max_lat <- c(102.15, 135.46, 142.60, 137.22, 137.26, 137.65, 137.84, 136.73)
lines(area_l, avg_max_lat, type='o', pch=pch[7])

# # Average latency # #

# D1VHU
#avg_lat <- c(8.633156, 8.140718, 8.143710, 8.445711, 8.639501, 9.054342, 9.395622, 9.812672)

# D1HU
#avg_lat <- c(9.365611, 10.300120, 11.109248, 11.884447, 12.428119, 13.516939, 14.165949, 14.903600)
#lines(area_l, avg_lat, type='o', pch=pch[2])

# D2VHU
avg_lat <- c(8.838037, 8.336745, 8.485482, 8.735454, 9.138091, 9.605691, 10.063384, 10.579800)
plot(area_l, avg_lat, type='o', pch=pch[1], ylim=c(8,75),
	xlab='Area length (m)', ylab='Average latency (slots)', main='(b) Fixed network density')

# D2HU
avg_lat <- c(9.939890, 10.640719, 11.404108, 12.308732, 13.055188, 13.918293, 14.756973, 15.639346)
lines(area_l, avg_lat, type='o', pch=pch[2])

# D2U
avg_lat <- c(19.878539, 21.917822, 23.438281, 24.595909, 26.022779, 27.156799, 28.620674, 30.176503)
lines(area_l, avg_lat, type='o', pch=pch[3])

# CVHU
avg_lat <- c(8.919318, 8.411400, 8.518859, 8.791262, 9.151941, 9.641454, 10.186824, 10.584161)
lines(area_l, avg_lat, type='o', pch=pch[4])

# CHU
avg_lat <- c(9.843791, 10.667241, 11.524022, 12.301896, 13.104550, 14.002915, 14.680621, 15.589984)
lines(area_l, avg_lat, type='o', pch=pch[5])

# CU
avg_lat <- c(19.945279, 21.901543, 23.417573, 24.632448, 25.730835, 27.287988, 28.673944, 30.504444)
lines(area_l, avg_lat, type='o', pch=pch[6])

# C
avg_lat <- c(51.575000, 65.114137, 68.197776, 68.838323, 70.928022, 73.804502, 74.698971, 74.511222)
lines(area_l, avg_lat, type='o', pch=pch[7])

# # # # # # # # # # # # # # # # # # Fixed area # # # # # # # # # # # # # # # # #
par(mar=c(4,4,1.5,0.5)) # margin: bottom left top right

# # Average maximum latency # #

# D1VHU
#avg_max_lat <- c(18.04, 18.41, 19.95, 20.68, 21.69, 23.36, 24.39, 25.61)

# D1HU
#avg_max_lat <- c(25.74, 28.83, 32.14, 35.28, 38.65, 41.20, 44.65, 47.00)
#lines(num_FFD, avg_max_lat, type='o', pch=pch[2])

# D2VHU
avg_max_lat <- c(18.45, 19.20, 19.99, 20.64, 21.58, 22.38, 23.37, 24.00)
plot(num_FFD, avg_max_lat, type='o', pch=pch[1], ylim=c(18,141),
	xlab='Number of nodes', ylab='Average maximum latency (slots)', main='(c) Fixed simulation area')

# D2HU
avg_max_lat <- c(25.88, 28.61, 30.54, 32.60, 34.85, 36.93, 39.34, 41.46)
lines(num_FFD, avg_max_lat, type='o', pch=pch[2])

# D2U
avg_max_lat <- c(41.83, 48.23, 53.94, 59.81, 65.83, 73.10, 78.42, 84.83)
lines(num_FFD, avg_max_lat, type='o', pch=pch[3])

# CVHU
avg_max_lat <- c(18.69, 19.18, 20.11, 20.92, 21.75, 22.33, 23.27, 24.13)
lines(num_FFD, avg_max_lat, type='o', pch=pch[4])

# CHU
avg_max_lat <- c(26.33, 28.60, 30.45, 33.00, 34.72, 37.38, 39.54, 41.43)
lines(num_FFD, avg_max_lat, type='o', pch=pch[5])

# CU
avg_max_lat <- c(41.98, 47.87, 54.54, 61.21, 66.52, 72.73, 78.94, 85.39)
lines(num_FFD, avg_max_lat, type='o', pch=pch[6])

# C
avg_max_lat <- c(128.00, 129.72, 130.58, 136.56, 136.44, 140.62, 139.56, 137.27)
lines(num_FFD, avg_max_lat, type='o', pch=pch[7])

# # Average latency # #

# D1VHU
#avg_lat <- c(8.911326, 9.018336, 9.465811, 9.736929, 10.147071, 10.750860, 11.067770, 11.527987)

# D1HU
#avg_lat <- c(12.145766, 12.890715, 13.874480, 14.887266, 16.099299, 17.264806, 18.288610, 19.209590)
#lines(num_FFD, avg_lat, type='o', pch=pch[2])

# D2VHU
avg_lat <- c(9.522748, 9.886576, 10.206525, 10.637270, 11.090729, 11.401455, 11.849753, 12.328218)
plot(num_FFD, avg_lat, type='o', pch=pch[1], ylim=c(8.5,75),
	xlab='Number of nodes', ylab='Average latency (slots)', main='(d) Fixed simulation area')

# D2HU
avg_lat <- c(12.766289, 13.639792, 14.520882, 15.514725, 16.700901, 17.644869, 18.718732, 19.663173)
lines(num_FFD, avg_lat, type='o', pch=pch[2])

# D2U
avg_lat <- c(21.209673, 23.746466, 26.708998, 29.437496, 32.494077, 35.789249, 38.411602, 41.863744)
lines(num_FFD, avg_lat, type='o', pch=pch[3])

# CVHU
avg_lat <- c(9.691743, 9.884853, 10.286174, 10.633576, 11.136235, 11.487778, 11.897385, 12.300913)
lines(num_FFD, avg_lat, type='o', pch=pch[4])

# CHU
avg_lat <- c(12.970214, 13.934990, 14.714850, 15.890067, 16.590730, 17.798586, 18.634638, 19.673634)
lines(num_FFD, avg_lat, type='o', pch=pch[5])

# CU
avg_lat <- c(21.068575, 23.701878, 26.658477, 30.097262, 32.577425, 35.778511, 38.385506, 41.531341)
lines(num_FFD, avg_lat, type='o', pch=pch[6])

# C
avg_lat <- c(75.044535, 75.914949, 75.333225, 76.202849, 74.931317, 74.261421, 73.977030, 72.968245)
lines(num_FFD, avg_lat, type='o', pch=pch[7])

dev.off()
