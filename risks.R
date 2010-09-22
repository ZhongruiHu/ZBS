require('colorspace')

# k.array <- seq(1, 5)
# 
# # These are obtained by running p.cpp
# s1 <- c(0.000125, 0.000231, 0.000312, 0.000375, 0.000423)	# n=1000
# s2 <- c(0.000063, 0.000114, 0.000156, 0.000188, 0.000213) # n=2000
# s3 <- c(0.000042, 0.000076, 0.000103, 0.000126, 0.000144) # n=3000
# 
# # These are obtained by running test.nc
# t1 <- c(0.00012299,   0.000219508,  0.00029439,   0.00035213,  0.000396617)
# t2 <- c(0.0000614948, 0.000109754,  0.000147195,  0.000176065, 0.000198308)
# t3 <- c(0.0000409965, 0.0000731694, 0.0000981299, 0.000117377, 0.000132206)

P_Ustar <- function(r) {
	integrand <- function(x) {
		A <- 2*acos(x/(2*r))-2*sqrt(1-(x/(2*r))^2)*(x/(2*r))
		B <- (1-A/pi)^k*(2*x)/(3*r^2)
		B.integrand <- function(x) {
			return(B)
		}
		C <- integrate(B.integrand, lower=r, upper=2*r)$value
		return(r^2*A*B/C)
	}
	return(integrate(integrand, lower=r, upper=2*r)$value)
}

k.array <- c(5, 10, 15, 20, 25)
r1.array <- sqrt(k.array/(1000*pi))
r2.array <- sqrt(k.array/(2000*pi))
r3.array <- sqrt(k.array/(3000*pi))
phi <- c(0.553643, 0.392767, 0.31258, 0.263885, 0.23446)

# This is calculated using R; Mathematica takes a long time to calculate, if at all
# 's' stands for simulation 
# 't' stands for theory
# P_U^*
s1 <- c(0.000423, 0.000561, 0.000612, 0.000626, 0.000628)
s2 <- c(0.000213, 0.000277, 0.000300, 0.000307, 0.000309)
s3 <- c(0.000144,	0.000188, 0.000198, 0.000205, 0.000208)

t1 <- c(0.000396617, 0.000509954, 0.0005527123, 0.00057537,   0.0005899476)
t2 <- c(0.000198308, 0.000254977, 0.0002763562, 0.000287685,  0.0002949738)
t3 <- c(0.000132206, 0.000169985, 0.0001842374, 0.0001918047, 0.0001966492)

# P_H simulation results
h.s1 <- c(0.001041, 0.001944, 0.002765, 0.003554, 0.004322)
h.s2 <- c(0.000524, 0.000970, 0.001388, 0.001775, 0.002154)
h.s3 <- c(0.000349, 0.000647, 0.000921, 0.001186, 0.001438)

# P_U simulation results
u.s1 <- c(0.000426, 0.000566, 0.000612, 0.000632, 0.000642)
u.s2 <- c(0.000217, 0.000278, 0.000300, 0.000303, 0.000311)
u.s3 <- c(0.000143, 0.000187, 0.000201, 0.000207, 0.000208)

P_H <- function(P_Ustar, r, phi) {
	#cat(sprintf("%f, %f, %f\n", r, phi, P_Ustar))
	return( (phi*P_Ustar-sqrt(3)*r*r/4.0)/(phi-1) )
}

P_U <- function(P_Ustar, r) {
	return( 3*pi*r*r*P_Ustar )
}

P_V <- function(r) {
	return( (1+3*sqrt(3)/(4*pi))*pi*r*r )
}

pdf("ZBS-risks.pdf", width=10, height=2.8, family="Times")
par(xpd=TRUE, mfrow=c(1,3), mar=c(3.5,2.5,1,0.5)) # margin: bottom left top right
par(mgp=c(1.5,0.5,0)) # margin line (in mex units) for the axis title, axis labels and axis line
par(cex.axis=1.1) # expansion factor for axis annotations
par(cex.lab=1.1) # expansion factor for axis labels

# plot P_H
plot (k.array, h.s1,                      type='o', pch=1, ylim=c(0.00045, 0.0045), ylab=expression(paste(P[H], "(u,v)")), xlab=expression(italic(k)), sub='(a)')
lines(k.array, P_H(t1, r1.array, phi),    type='o', pch=2)
lines(k.array, 0.17*pi*r1.array*r1.array, type='o', pch=3)
lines(k.array, h.s2,                      type='o', pch=4)
lines(k.array, P_H(t2, r2.array, phi),    type='o', pch=5)
lines(k.array, 0.17*pi*r2.array*r2.array, type='o', pch=6)
lines(k.array, h.s3,                      type='o', pch=8)
lines(k.array, P_H(t3, r3.array, phi),    type='o', pch=16)
lines(k.array, 0.17*pi*r3.array*r3.array, type='o', pch=17)
legend("topleft", c('n=1000 (simulation)', 'n=1000 (analytical)', 'n=1000 (heuristic)',
                    'n=2000 (simulation)', 'n=2000 (analytical)', 'n=2000 (heuristic)',
									  'n=3000 (simulation)', 'n=3000 (analytical)', 'n=3000 (heuristic)'), pch=c(seq(1,6),8,16,17))

# plot P_U (not P_U^*)
plot (k.array, P_U(u.s1, r1.array), type='o', pch=1, ylim=c(0.000001, 0.00005), ylab=expression(paste(P[U], "(u,v)")), xlab=expression(italic(k)), sub='(b)')
lines(k.array, P_U(t1,   r1.array), type='o', pch=2)
lines(k.array, P_U(u.s2, r2.array), type='o', pch=3)
lines(k.array, P_U(t2,   r2.array), type='o', pch=4)
lines(k.array, P_U(u.s3, r3.array), type='o', pch=5)
lines(k.array, P_U(t3,   r3.array), type='o', pch=6)
legend("topleft", c('n=1000 (simulation)', 'n=1000 (analytical)',
                    'n=2000 (simulation)', 'n=2000 (analytical)',
										'n=3000 (simulation)', 'n=3000 (analytical)'), pch=seq(1,6))

# compare P_V, P_H and P_U
k.array <- seq(1,25)
phi <- c(0.862168, 0.75613 , 0.673142, 0.607086, 0.553643,
         0.509726, 0.473108, 0.44216 , 0.41568 , 0.392767,
         0.372737, 0.355069, 0.339355, 0.325277, 0.31258 ,
         0.301063, 0.290558, 0.280932, 0.272072, 0.263885,
         0.256292, 0.249233, 0.242636, 0.236162, 0.23446)
r.array <- sqrt(k.array/(100*pi))
t1 <- c(); for(r in r.array) t1 <- c(t1, P_Ustar(r))
plot (k.array, P_V(r.array),          type='o', pch=1, ylim=c(0,0.35), ylab='Probability', xlab=expression(italic(k)), sub='(c)')
lines(k.array, P_H(t1, r.array, phi), type='o', pch=2)
lines(k.array, P_U(t1, r.array),      type='o', pch=3)
legend("topleft", pch=seq(1,6), c(expression(paste(P[V], "(u,v)")), expression(paste(P[H], "(u,v)")), expression(paste(P[U], "(u,v)"))))

dev.off()
