% Generates figure ZBS-prob4

clear;
clf;
hold all;

n_array = [1000, 2000, 3000];
k = 5:5:50;

% raw
H1R = [0.001041, 0.001944, 0.002765, 0.003554, 0.004322, 0.005068, 0.005809, 0.006543, 0.007292, 0.008019];
H2R = [0.000524, 0.000970, 0.001388, 0.001775, 0.002154, 0.002533, 0.002909, 0.003274, 0.003638, 0.004004];
H3R = [0.000349, 0.000647, 0.000921, 0.001186, 0.001438, 0.001688, 0.001936, 0.002183, 0.002424, 0.002669];

U1R = [0.000426, 0.000566, 0.000612, 0.000632, 0.000642, 0.000644, 0.000642, 0.000642, 0.000650, 0.000654];
U2R = [0.000217, 0.000278, 0.000300, 0.000303, 0.000311, 0.000316, 0.000319, 0.000319, 0.000320, 0.000321];
U3R = [0.000143, 0.000187, 0.000201, 0.000207, 0.000208, 0.000210, 0.000211, 0.000211, 0.000212, 0.000213];

% constants
phi = [		% k=1:25 analytical; k=26:60 experimental {{{
0.862168
0.75613 
0.673142
0.607086
0.553643
0.509726
0.473108
0.44216 
0.41568 
0.392767
0.372737
0.355069
0.339355
0.325277
0.31258 
0.301063
0.290558
0.280932
0.272072
0.263885
0.256292
0.249233
0.242636
0.236162
0.23446 	% 25
0.229073	% 26
0.224124	% 27
0.219228	% 28
0.214491	% 29
0.209858	% 30
0.206411	% 31
0.202695	% 32
0.198517	% 33
0.194765	% 34
0.191870	% 35
0.187840	% 36
0.184256	% 37
0.180952	% 38
0.178613	% 39
0.175323	% 40
0.172776	% 41
0.169925	% 42
0.167319	% 43
0.164788	% 44
0.162461	% 45
0.160314	% 46
0.157947	% 47
0.155790	% 48
0.153770	% 49
0.151721	% 50
0.150070	% 51
0.148275	% 52
0.147293	% 53
0.145117	% 54
0.142951	% 55
0.141381	% 56
0.139896	% 57
0.137973	% 58
0.136286	% 59
0.134698];	% 60}}}

sigma = [	% From a.xls for k=1:60 {{{
1.148359 
1.242248
1.324327
1.398556
1.425776
1.478505
1.505301
1.530002
1.558995
1.589913
1.601284
1.616834
1.628119
1.644447
1.676979
1.684638
1.68096 
1.692744
1.706022
1.714721
1.717019
1.728896
1.726633
1.738283
1.748649
1.754724
1.759417
1.760129
1.769109
1.770747
1.777578
1.779811
1.781214
1.788005
1.792862
1.793909
1.795261
1.798126
1.801044
1.805415
1.801571
1.811608
1.811077
1.819349
1.819215
1.82056 
1.816817
1.825232
1.823967
1.828635
1.827867
1.83332 
1.832967
1.838618
1.839045
1.843508
1.843903
1.843647
1.84808 
1.848892];	% }}}

sigma = smooth(1:1:size(sigma,1), sigma);	% default filter is good enough

% first heuristic
gamma = 0.17;

% third heuristic performs badly for n = 2000, 3000
a1 = -0.000124; a2 = 0.1304; b = 1.5356; c = 0.1745;

% init variabls
r1  = zeros(1, 10);
r2  = zeros(1, 10);
r3  = zeros(1, 10);

H1L = zeros(1, 10);
U1L = zeros(1, 10);
H2L = zeros(1, 10);
U2L = zeros(1, 10);
H3L = zeros(1, 10);
U3L = zeros(1, 10);

H1  = zeros(1, 10);
U1  = zeros(1, 10);
H2  = zeros(1, 10);
U2  = zeros(1, 10);
H3  = zeros(1, 10);
U3  = zeros(1, 10);

H1F = zeros(1, 10);
U1F = zeros(1, 10);
H2F = zeros(1, 10);
U2F = zeros(1, 10);
H3F = zeros(1, 10);
U3F = zeros(1, 10);

n = 1000;
for i=1:10
	k = 5*i;
	r = sqrt(k/(n*pi));
	p = k/n;

	r1(i) = r;

	H1L(i) = gamma*p;
	U1L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;

	sigmasq = sigma(k)*sigma(k);
	U1(i)  = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	U1(i)  = U1(i)*p/(4*pi*(4-sigmasq));
	H1(i)  = (phi(k)*U1(i) - sqrt(3)/4/pi*p)/(phi(k)-1);

	lambda = (a1*n+a2)/(r^3) + b*n + c;
	tmp = (3*sqrt(3)-4*pi)*r*r*lambda;
	U1F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	H1F(i) = (phi(k)*U1F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end

n = 2000;
for i=1:10
	k = 5*i;
	r = sqrt(k/(n*pi));
	p = k/n;

	r2(i) = r;

	H2L(i) = gamma*p;
	U2L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;

	sigmasq = sigma(k)*sigma(k);
	U2(i)  = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	U2(i)  = U2(i)*p/(4*pi*(4-sigmasq));
	H2(i)  = (phi(k)*U2(i) - sqrt(3)/4/pi*p)/(phi(k)-1);

	lambda = (a1*n+a2)/(r^3) + b*n + c;
	tmp = (3*sqrt(3)-4*pi)*r*r*lambda;
	U2F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	H2F(i) = (phi(k)*U2F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);	
end

n = 3000;
for i=1:10
	k = 5*i;
	r = sqrt(k/(n*pi));
	p = k/n;

	r3(i) = r;

	H3L(i) = gamma*p;
	U3L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;

	sigmasq = sigma(k)*sigma(k);
	U3(i)  = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	U3(i)  = U3(i)*p/(4*pi*(4-sigmasq));
	H3(i)  = (phi(k)*U3(i) - sqrt(3)/4/pi*p)/(phi(k)-1);

	lambda = (a1*n+a2)/(r^3) + b*n + c;
	tmp = (3*sqrt(3)-4*pi)*r*r*lambda;
	U3F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	H3F(i) = (phi(k)*U3F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);	
end

subplot(2,2,1);
plot(r1, H1L, 'ko-', ...
	 r1, H1R, 'kx--', ...
	 r2, H2L, 'b+-', ...
	 r2, H2R, 'b*--', ...
	 r3, H3L, 'rs-', ...
	 r3, H3R, 'rd--');
title(sprintf('(a) Old heuristic (RMSE: %f, %f, %f)', ...
	rmse(H1L, H1R), rmse(H2L, H2R), rmse(H3L, H3R)));
ylabel('P_H(u,v)');	 
legend('n=1k (est.)', 'n=1k (sim.)', ...
	   'n=2k (est.)', 'n=2k (sim.)', ...
	   'n=3k (est.)', 'n=3k (sim.)', 'Location', 'SouthEast');
pos = get(gca, 'Position');
pos(3) = 0.375; pos(4) = 0.3;
set(gca, 'Position', pos);

subplot(2,2,2);
plot(r1, H1,  'ko-', ...
	 r1, H1R, 'kx--', ...
	 r2, H2,  'b+-', ...
	 r2, H2R, 'b*--', ...
	 r3, H3,  'rs-', ...
	 r3, H3R, 'rd--');
title(sprintf('(b) New heuristic (RMSE: %f, %f, %f)', ...
	rmse(H1, H1R), rmse(H2, H2R), rmse(H3, H3R)));
ylabel('P_H(u,v)');
legend('n=1k (est.)', 'n=1k (sim.)', ...
	   'n=2k (est.)', 'n=2k (sim.)', ...
	   'n=3k (est.)', 'n=3k (sim.)', 'Location', 'SouthEast');
pos = get(gca, 'Position');
pos(3) = 0.375; pos(4) = 0.3;
set(gca, 'Position', pos);

% subplot(2,3,3);
% plot(r1, H1F, 'ko-', ...
% 	 r1, H1R, 'kx--', ...
% 	 r2, H2F, 'b+-', ...
% 	 r2, H2R, 'b*--', ...
% 	 r3, H3F, 'rs-', ...
% 	 r3, H3R, 'rd--');
% title(sprintf('(c) Third heuristic (RMSE: %f, %f, %f)', ...
% 	rmse(H1F, H1R), rmse(H2F, H2R), rmse(H3F, H3R)));
% ylabel('P_H(u,v)');
% legend('n=1k (est.)', 'n=1k (sim.)', ...
% 	   'n=2k (est.)', 'n=2k (sim.)', ...
% 	   'n=3k (est.)', 'n=3k (sim.)', 'Location', 'SouthEast');

subplot(2,2,3);
plot(r1, U1L, 'ko-', ...
	 r1, U1R, 'kx--', ...
	 r2, U2L, 'b+-', ...
	 r2, U2R, 'b*--', ...
	 r3, U3L, 'rs-', ...
	 r3, U3R, 'rd--');
title(sprintf('(c) Old heuristic (RMSE: %f, %f, %f)', ...
	rmse(U1L, U1R), rmse(U2L, U2R), rmse(U3L, U3R)));
ylabel('P_U(u,v)');	 
legend('n=1k (est.)', 'n=1k (sim.)', ...
	   'n=2k (est.)', 'n=2k (sim.)', ...
	   'n=3k (est.)', 'n=3k (sim.)', 'Location', 'SouthWest');
pos = get(gca, 'Position');
pos(3) = 0.375; pos(4) = 0.3; pos(2) = 0.2;
set(gca, 'Position', pos);

subplot(2,2,4);
plot(r1, U1,  'ko-', ...
	 r1, U1R, 'kx--', ...
	 r2, U2,  'b+-', ...
	 r2, U2R, 'b*--', ...
	 r3, U3,  'rs-', ...
	 r3, U3R, 'rd--');
title(sprintf('(d) New heuristic (RMSE: %f, %f, %f)', ...
	rmse(U1, U1R), rmse(U2, U2R), rmse(U3, U3R)));
ylabel('P_U(u,v)');
legend('n=1k (est.)', 'n=1k (sim.)', ...
	   'n=2k (est.)', 'n=2k (sim.)', ...
	   'n=3k (est.)', 'n=3k (sim.)', 'Location', 'SouthEast');
pos = get(gca, 'Position');
pos(3) = 0.375; pos(4) = 0.3; pos(2) = 0.2;
set(gca, 'Position', pos);

% subplot(2,3,6);
% plot(r1, U1F, 'ko-', ...
% 	 r1, U1R, 'kx--', ...
% 	 r2, U2F, 'b+-', ...
% 	 r2, U2R, 'b*--', ...
% 	 r3, U3F, 'rs-', ...
% 	 r3, U3R, 'rd--');
% title(sprintf('(f) Third heuristic (RMSE: %f, %f, %f)', ...
% 	rmse(U1F, U1R), rmse(U2F, U2R), rmse(U3F, U3R)));
% ylabel('P_U(u,v)');
% legend('n=1k (est.)', 'n=1k (sim.)', ...
% 	   'n=2k (est.)', 'n=2k (sim.)', ...
% 	   'n=3k (est.)', 'n=3k (sim.)', 'Location', 'SouthEast');

set(gcf, 'PaperSize', [50 20]);

% vim:foldmethod=marker: