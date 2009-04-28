# Calculates the coverage of a circle and its 1-hop neighbours
# The answers are in the number of circles

#r <- as.symbol("r")
r <- 1 			# doesn't matter what this is, JUST because we know r will cancel out

num_ngb <- 1	# number of neighbors
repeat {
	integrand <- function(x) {
		x*(1-2*(r*r*acos(x/(2*r))-r*(x/2)*sqrt(1-(x/(2*r))^2))/(pi*r*r))^num_ngb
	}
	res <- integrate(integrand, lower=r, upper=2*r)$value
	res <- 4 - 2*pi*res/(pi*r*r)

	cat("num_ngb=", num_ngb, ": ", res, "\n")

	num_ngb <- num_ngb + 1
	if(num_ngb > 100) break
}
