k.array <- seq(1, 5)

# These are obtained by running p.cpp
s1 <- c(0.000125, 0.000231, 0.000312, 0.000375, 0.000423)	# n=1000
s2 <- c(0.000063, 0.000114, 0.000156, 0.000188, 0.000213) # n=2000
s3 <- c(0.000042, 0.000076, 0.000103, 0.000126, 0.000144) # n=3000

# These are obtained by running test.nc
t1 <- c(0.00012299,   0.000219508,  0.00029439,   0.00035213,  0.000396617)
t2 <- c(0.0000614948, 0.000109754,  0.000147195,  0.000176065, 0.000198308)
t3 <- c(0.0000409965, 0.0000731694, 0.0000981299, 0.000117377, 0.000132206)

pdf("ZBS-P_U^star.pdf", width=5, height=3.5, family="Times")
par(xpd=TRUE, mfrow=c(1,1), mar=c(2.5,2.5,0.5,0.5)) # margin: bottom left top right
par(mgp=c(1.5,0.5,0)) # margin line (in mex units) for the axis title, axis labels and axis line
par(cex.axis=1.1) # expansion factor for axis annotations
par(cex.lab=1.1) # expansion factor for axis labels
#dev.new()

plot (k.array, s1, type='o', pch=1, ylim=c(0.00004,0.000450), ylab=expression(paste(P[U]^"*", "(u,v)")), xlab='Average degree (k)')
lines(k.array, t1, type='o', pch=2)
lines(k.array, s2, type='o', pch=3)
lines(k.array, t2, type='o', pch=4)
lines(k.array, s3, type='o', pch=5)
lines(k.array, t3, type='o', pch=6)
legend("topleft", c('n=1000 (simulation)', 'n=1000 (Theorem 2)', 'n=2000 (simulation)', 'n=2000 (Theorem 2)', 'n=3000 (simulation)', 'n=3000 (Theorem 2)'), 
	pch=seq(1,6))

dev.off()
