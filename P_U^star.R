#k <- 12
#n <- 1000

if(!exists("k"))
	stop("Must specify k")

if(!exists("n"))
	stop("Must specify n")

cat(sprintf("k=%d, n=%d\n", k, n))

r <- sqrt(k/(n*pi))

integrand <- function(x) {
	A <- 2*acos(x/(2*r))-2*sqrt(1-(x/(2*r))^2)*(x/(2*r))
	B <- (1-A/pi)^k*(2*x)/(3*r^2)
	B.integrand <- function(x) {
		return(B)
	}
	C <- integrate(B.integrand, lower=r, upper=2*r)$value
	return(r^2*A*B/C)
}

print(integrate(integrand, lower=r, upper=2*r)$value)

