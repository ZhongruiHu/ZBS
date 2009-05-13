% Generates figure ZBS-prob

r = [
0.06,
0.07,
0.08,
0.09,
0.10,
0.11,
0.12,
0.13,
0.14,
0.15,
0.16];

p = 0;
for i = 1:size(r, 1)
	p(i) = pi*r(i)*r(i);
end

phi = [
0.862168,
0.75613 ,
0.673142,
0.607086,
0.553643,
0.509726,
0.473108,
0.44216 ,
0.41568 ,
0.392767,
0.372737,
0.355069,
0.339355,
0.325277,
0.31258 ,
0.301063,
0.290558,
0.280932,
0.272072,
0.263885,
0.256292,
0.249233,
0.242636,
0.236162,
0.23446];

n = 300;
gamma = 0.17;

P_V = 0;
P_H = 0;
P_U = 0;
for i = 1:size(r, 1)	
	P_V(i) = (1+3*sqrt(3)/(4*pi))*p(i);
	P_H(i) = gamma*p(i);
	k = ceil(p(i)*n);
	P_U(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i);
end

clf;
hold all;
semilogy(p, P_V, '-x');
semilogy(p, P_H, '-+');
semilogy(p, P_U, '-<');
xlim([0.01, 0.085]);
xlabel('Link probability (p)');
ylabel('Risk probabilities');
legend('P_V(u,v)', 'P_H(u,v,)', 'P_U(u,v)');
