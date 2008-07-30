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

gamma = 0.1689;
calced = 0;
for i = 1:size(r, 1)
	k = ceil(p(i)*n);
	calced(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i);
	%calced(i) = phi(k)*(gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i) + gamma*p(i)*(1-phi(k));
end

gamma = 0.17;
calced2 = 0;
for i = 1:size(r, 1)
	k = ceil(p(i)*n);
	calced2(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i);
	%calced2(i) = phi(k)*(gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i) + gamma*p(i)*(1-phi(k));
end

gamma = 0.1720; % this is already curving too much
calced3 = 0;
for i = 1:size(r, 1)
	k = ceil(p(i)*n);
	calced3(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i);
	%calced3(i) = phi(k)*(gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p(i) + gamma*p(i)*(1-phi(k));
end

%pu:
simued = [
0.000940,
0.001254,
0.001508,
0.001613,
0.001715,
0.001796,
0.001800,
0.0017058,
0.0017547,
0.0020863,
0.0019087];

%diff = 0;
%for i = 1:size(r, 1)
%	diff(i) = (calced(i) - simued(i))/simued(i);
%end

% Pr[W|X]
%simued = [
%0.001556,
%0.002113,
%0.002763,
%0.003513,
%0.004346,
%0.005258,
%0.006255,
%0.007335,
%0.008490,
%0.009732,
%0.011077];

yen = 0;
for i = 1:size(r, 1)
	k = ceil(p(i)*n);
	numer = sqrt(27)/4/pi*p(i)*p(i)*(1 - sqrt(3)/4/pi)^k;
	denom = 1 - 4*p(i)*(1 - 0.75^k);
	yen(i) = numer/denom
end

clf;
hold all;
plot(p, calced);
plot(p, calced2);
plot(p, calced3);
plot(p, simued);
plot(p, yen);
legend('gamma = 0.1689', 'gamma = 0.17', 'gamma = 0.1720', 'Simulation', 'yen');

%plot(p, diff);
%ylim([0, 0.1]);
