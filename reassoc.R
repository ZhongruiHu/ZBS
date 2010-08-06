pdf("ZBS-reassoc.pdf", width=12, height=10, family="Times")
par(xpd=TRUE, mfrow=c(2,2), mar=c(5,2,0,0)) # margin: bottom left top right

########################################################
area_length <- c(100, 120, 140, 160, 180, 200, 220, 240)

#### D1HVU ####
count <- c(0, 1, 2, 3, 4, 5)

prob <- c(0.8582, 0.1275, 0.0133, 0.0009, 0.0001, 0.0000,	# 100
					0.8360, 0.1412, 0.0206, 0.0022, 0.0001, 0.0000,	# 120
					0.8170, 0.1587, 0.0226, 0.0014, 0.0002, 0.0001,	# 140
					0.8221, 0.1541, 0.0207, 0.0028, 0.0002, 0.0000,	# 160
					0.8496, 0.1320, 0.0169, 0.0015, 0.0001, 0.0000,	# 180
					0.8659, 0.1223, 0.0111, 0.0006, 0.0000, 0.0000,	# 200
					0.8933, 0.0971, 0.0090, 0.0006, 0.0000, 0.0000,	# 220
					0.9135, 0.0801, 0.0060, 0.0004, 0.0000, 0.0000)	# 240

dim(prob) <- c(length(count), length(area_length))
persp(count, area_length, prob,			
			xlab = "Reassociation count", ylab = "Area length (l)", zlab = "Probability",
			sub="D1VHU (fixed network density)", zlim=c(0,1),
			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
      ltheta = 120, shade = 0.75, ticktype = "detailed"
)

#### D1HU ####
count <- c(0, 1, 2, 3, 4)

prob <- c(0.8669, 0.1221, 0.0106, 0.0004, 0.0000,	# 100
					0.8561, 0.1280, 0.0147, 0.0012, 0.0000,	# 120
					0.8803, 0.1088, 0.0097, 0.0010, 0.0001,	# 140
					0.8978, 0.0944, 0.0073, 0.0004, 0.0000,	# 160
					0.9243, 0.0714, 0.0042, 0.0001, 0.0000,	# 180
					0.9492, 0.0489, 0.0018, 0.0001, 0.0000,	# 200
					0.9614, 0.0363, 0.0022, 0.0001, 0.0001,	# 220
					0.9788, 0.0206, 0.0006, 0.0000, 0.0000)	# 240

dim(prob) <- c(length(count), length(area_length))
persp(count, area_length, prob,			
			xlab = "Reassociation count", ylab = "Area length (l)", zlab = "Probability",
			sub="D1HU (fixed network density)", zlim=c(0,1),
			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
      ltheta = 120, shade = 0.75, ticktype = "detailed"
)

#####################################################
num_FFD <- c(300, 400, 500, 600, 700, 800, 900, 1000)

#### D1VHU ####
count <- c(0, 1, 2, 3, 4, 5, 6)

prob <- c(0.9052, 0.0868, 0.0075, 0.0005, 0.0000, 0.0000, 0.0000,	# 300
					0.8492, 0.1316, 0.0175, 0.0017, 0.0001, 0.0000, 0.0000,	# 400
					0.8105, 0.1623, 0.0242, 0.0026, 0.0004, 0.0000, 0.0000,	# 500
					0.7753, 0.1862, 0.0337, 0.0043, 0.0004, 0.0000, 0.0000,	# 600
					0.7550, 0.1982, 0.0405, 0.0057, 0.0006, 0.0001, 0.0000,	# 700
					0.7283, 0.2140, 0.0494, 0.0071, 0.0011, 0.0002, 0.0000,	# 800
					0.7087, 0.2243, 0.0549, 0.0104, 0.0014, 0.0002, 0.0000,	# 900
					0.6852, 0.2331, 0.0655, 0.0137, 0.0020, 0.0004, 0.0001)	# 1000

dim(prob) <- c(length(count), length(num_FFD))
persp(count, area_length, prob,
			xlab = "Reassociation count", ylab = "Number of nodes (n)", zlab = "Probability", 
			sub="D1VHU (varying network density)", zlim=c(0,1),
			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
      ltheta = 120, shade = 0.75, ticktype = "detailed"
)

#### D1HU ####
count <- c(0, 1, 2, 3, 4, 5, 6)

prob <- c(0.9006, 0.0915, 0.0075, 0.0004, 0.0000, 0.0000, 0.0000,	# 300 
					0.8646, 0.1225, 0.0121, 0.0008, 0.0000, 0.0000, 0.0000,	# 400 
					0.8166, 0.1609, 0.0203, 0.0020, 0.0002, 0.0000, 0.0000,	# 500 
					0.7914, 0.1790, 0.0265, 0.0028, 0.0003, 0.0000, 0.0000,	# 600 
					0.7589, 0.1998, 0.0353, 0.0053, 0.0005, 0.0001, 0.0000,	# 700 
					0.7380, 0.2114, 0.0430, 0.0062, 0.0012, 0.0002, 0.0001,	# 800 
					0.7119, 0.2237, 0.0521, 0.0100, 0.0020, 0.0003, 0.0000,	# 900 
					0.6890, 0.2392, 0.0580, 0.0111, 0.0022, 0.0004, 0.0001)	# 1000

dim(prob) <- c(length(count), length(num_FFD))
persp(count, area_length, prob,
			xlab = "Reassociation count", ylab = "Number of nodes (n)", zlab = "Probability",
			sub="D1HU (varying network density)", zlim=c(0,1),
			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
      ltheta = 120, shade = 0.75, ticktype = "detailed"
)

dev.off()
