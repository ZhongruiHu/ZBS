pdf("ZBS-reassoc.pdf", width=12, height=5, family="Times")
par(xpd=TRUE, mfrow=c(1,2), mar=c(0,2.5,1,0)) # margin: bottom left top right

########################################################
area_l <- c(100, 120, 140, 160, 180, 200, 220, 240)

#### D1HVU ####
count <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

prob <- c(0.6772, 0.2312, 0.0717, 0.0154, 0.0034, 0.0007, 0.0005, 0.0000, 0.0000, 0.0000, 0.0000, # 100
					0.6225, 0.2471, 0.0972, 0.0242, 0.0075, 0.0013, 0.0001, 0.0001, 0.0000, 0.0000, 0.0000, # 120
					0.5736, 0.2597, 0.1161, 0.0376, 0.0095, 0.0029, 0.0003, 0.0001, 0.0000, 0.0000, 0.0000, # 140
					0.5338, 0.2628, 0.1335, 0.0488, 0.0153, 0.0042, 0.0012, 0.0002, 0.0000, 0.0000, 0.0000, # 160
					0.5246, 0.2784, 0.1313, 0.0460, 0.0142, 0.0039, 0.0010, 0.0004, 0.0001, 0.0000, 0.0000, # 180
					0.4791, 0.2823, 0.1530, 0.0606, 0.0186, 0.0051, 0.0011, 0.0001, 0.0000, 0.0000, 0.0000, # 200
					0.4670, 0.2833, 0.1540, 0.0645, 0.0224, 0.0067, 0.0016, 0.0005, 0.0000, 0.0001, 0.0000, # 220
					0.4506, 0.2819, 0.1637, 0.0693, 0.0249, 0.0073, 0.0019, 0.0004, 0.0001, 0.0000, 0.0000) # 240

dim(prob) <- c(length(count), length(area_l))
persp(count, area_l, prob,			
			xlab = "Re-association count", ylab = "Area length (m)", zlab = "Fraction of nodes",
			main="(a) Fixed network density", zlim=c(0,0.7),
			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
      ltheta = 120, shade = 0.75, ticktype = "detailed"
)

#### D1HU ####
# count <- c(0, 1, 2, 3, 4)
# 
# prob <- c(0.8669, 0.1221, 0.0106, 0.0004, 0.0000,	# 100
# 					0.8561, 0.1280, 0.0147, 0.0012, 0.0000,	# 120
# 					0.8803, 0.1088, 0.0097, 0.0010, 0.0001,	# 140
# 					0.8978, 0.0944, 0.0073, 0.0004, 0.0000,	# 160
# 					0.9243, 0.0714, 0.0042, 0.0001, 0.0000,	# 180
# 					0.9492, 0.0489, 0.0018, 0.0001, 0.0000,	# 200
# 					0.9614, 0.0363, 0.0022, 0.0001, 0.0001,	# 220
# 					0.9788, 0.0206, 0.0006, 0.0000, 0.0000)	# 240
# 
# dim(prob) <- c(length(count), length(area_length))
# persp(count, area_length, prob,			
# 			xlab = "Reassociation count", ylab = "Area length (m)", zlab = "Probability",
# 			sub="D1HU (fixed network density)", zlim=c(0,1),
# 			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
#       ltheta = 120, shade = 0.75, ticktype = "detailed"
# )

#####################################################
num_FFD <- c(300, 400, 500, 600, 700, 800, 900, 1000)

#### D1VHU ####
count <- c(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13)

prob <- c(0.6937,  0.2280,  0.0627,  0.0131,  0.0024,  0.0002,	0.0000,  0.0000, 0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000,	# 300 
					0.5743,  0.2715,  0.1107,  0.0329,  0.0081,  0.0021,  0.0004,  0.0001, 0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000, # 400 
					0.4854,  0.2898,  0.1449,  0.0570,  0.0170,  0.0045,  0.0010,  0.0003, 0.0001,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000, # 500 
					0.4439,  0.2857,  0.1609,  0.0706,  0.0272,  0.0086,  0.0021,  0.0008, 0.0002,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000, # 600 
					0.4174,  0.2829,  0.1717,  0.0821,  0.0313,  0.0104,  0.0033,  0.0006, 0.0001,  0.0001,  0.0000,  0.0000,  0.0000,  0.0000, # 700 
					0.3829,  0.2743,  0.1822,  0.0951,  0.0410,  0.0157,  0.0058,  0.0020, 0.0006,  0.0003,  0.0001,  0.0000,  0.0000,  0.0000, # 800 
					0.3790,  0.2645,  0.1842,  0.0997,  0.0460,  0.0173,  0.0063,  0.0022, 0.0006,  0.0002,  0.0000,  0.0000,  0.0000,  0.0000, # 900 
					0.3466,  0.2622,  0.1897,  0.1097,  0.0554,  0.0233,  0.0088,  0.0030, 0.0008,  0.0003,  0.0001,  0.0000,  0.0000,  0.0000) # 1000

dim(prob) <- c(length(count), length(num_FFD))
persp(count, num_FFD, prob,
			xlab = "Re-association count", ylab = "Number of nodes", zlab = "Fraction of nodes", 
			main="(b) Fixed simulation area", zlim=c(0,0.7),
			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
      ltheta = 120, shade = 0.75, ticktype = "detailed"
)

#### D1HU ####
# count <- c(0, 1, 2, 3, 4, 5, 6)
# 
# prob <- c(0.9006, 0.0915, 0.0075, 0.0004, 0.0000, 0.0000, 0.0000,	# 300 
# 					0.8646, 0.1225, 0.0121, 0.0008, 0.0000, 0.0000, 0.0000,	# 400 
# 					0.8166, 0.1609, 0.0203, 0.0020, 0.0002, 0.0000, 0.0000,	# 500 
# 					0.7914, 0.1790, 0.0265, 0.0028, 0.0003, 0.0000, 0.0000,	# 600 
# 					0.7589, 0.1998, 0.0353, 0.0053, 0.0005, 0.0001, 0.0000,	# 700 
# 					0.7380, 0.2114, 0.0430, 0.0062, 0.0012, 0.0002, 0.0001,	# 800 
# 					0.7119, 0.2237, 0.0521, 0.0100, 0.0020, 0.0003, 0.0000,	# 900 
# 					0.6890, 0.2392, 0.0580, 0.0111, 0.0022, 0.0004, 0.0001)	# 1000
# 
# dim(prob) <- c(length(count), length(num_FFD))
# persp(count, area_length, prob,
# 			xlab = "Reassociation count", ylab = "Number of nodes", zlab = "Probability",
# 			sub="D1HU (varying network density)", zlim=c(0,1),
# 			theta = 22.5, phi = 22.5, expand = 0.6, col = "lightblue",
#       ltheta = 120, shade = 0.75, ticktype = "detailed"
# )

dev.off()
