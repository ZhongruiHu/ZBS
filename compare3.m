% Generates figure ZBS-prob3
% Raw data is from exp7.R

clear;
clf;
hold all;

r200 = [0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21];
r250 = [0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21];
r300 = [0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20];
r350 = [0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20];
r400 = [0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19];
r450 = [0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19];
r500 = [0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18];
r550 = [0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18];
r600 = [0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17];
r650 = [0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17];
r700 = [0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16];

% R means Raw
P_H200R = [0.003311, 0.004278, 0.005322, 0.006521, 0.007681, 0.008931, 0.010199, 0.011472, 0.012981, 0.014601, 0.016352, 0.018101, 0.020062, 0.021775, 0.023782];
P_H250R = [0.003269, 0.004179, 0.005234, 0.006290, 0.007478, 0.008633, 0.009944, 0.011190, 0.012595, 0.014199, 0.015893, 0.017588, 0.019426, 0.021141, 0.023118];
P_H300R = [0.002448, 0.003220, 0.004160, 0.005105, 0.006184, 0.007299, 0.008525, 0.009746, 0.010947, 0.012340, 0.013805, 0.015434, 0.017179, 0.019075, 0.020760];
P_H350R = [0.002396, 0.003175, 0.004096, 0.005058, 0.006043, 0.007124, 0.008260, 0.009550, 0.010838, 0.012234, 0.013622, 0.015234, 0.016820, 0.018612, 0.020356];
P_H400R = [0.001710, 0.002391, 0.003129, 0.004034, 0.004972, 0.005968, 0.006980, 0.008158, 0.009375, 0.010610, 0.012033, 0.013467, 0.014972, 0.016622, 0.018353];
P_H450R = [0.001707, 0.002382, 0.003106, 0.003996, 0.004903, 0.005870, 0.006884, 0.008022, 0.009232, 0.010477, 0.011848, 0.013294, 0.014833, 0.016454, 0.018197];
P_H500R = [0.001088, 0.001684, 0.002320, 0.003077, 0.003916, 0.004856, 0.005786, 0.006790, 0.007921, 0.009125, 0.010361, 0.011708, 0.013174, 0.014658, 0.016265];
P_H550R = [0.001084, 0.001673, 0.002311, 0.003040, 0.003890, 0.004809, 0.005720, 0.006707, 0.007818, 0.008991, 0.010243, 0.011590, 0.012999, 0.014547, 0.016121];
P_H600R = [0.000631, 0.001076, 0.001655, 0.002296, 0.002998, 0.003828, 0.004710, 0.005657, 0.006632, 0.007740, 0.008885, 0.010128, 0.011477, 0.012860, 0.014399];
P_H650R = [0.000643, 0.001055, 0.001650, 0.002291, 0.002986, 0.003785, 0.004664, 0.005581, 0.006578, 0.007646, 0.008796, 0.010066, 0.011403, 0.012801, 0.014292];
P_H700R = [0.000290, 0.000619, 0.001078, 0.001632, 0.002260, 0.002961, 0.003772, 0.004606, 0.005544, 0.006533, 0.007582, 0.008723, 0.009953, 0.011286, 0.012697];

P_U200R = [0.001547, 0.001912, 0.002234, 0.002450, 0.002666, 0.002750, 0.002903, 0.002946, 0.003055, 0.003069, 0.003042, 0.003108, 0.003230, 0.003228, 0.003258];
P_U250R = [0.001454, 0.001721, 0.001974, 0.002048, 0.002172, 0.002183, 0.002277, 0.002317, 0.002383, 0.002471, 0.002461, 0.002534, 0.002557, 0.002564, 0.002558];
P_U300R = [0.001155, 0.001373, 0.001564, 0.001747, 0.001838, 0.001911, 0.001917, 0.002004, 0.001985, 0.001981, 0.002013, 0.002021, 0.002085, 0.002148, 0.002152];
P_U350R = [0.001076, 0.001300, 0.001426, 0.001565, 0.001657, 0.001661, 0.001668, 0.001716, 0.001749, 0.001785, 0.001785, 0.001781, 0.001817, 0.001848, 0.001810];
P_U400R = [0.000795, 0.001036, 0.001204, 0.001348, 0.001477, 0.001489, 0.001494, 0.001491, 0.001499, 0.001508, 0.001542, 0.001586, 0.001598, 0.001619, 0.001623];
P_U450R = [0.000756, 0.000973, 0.001163, 0.001253, 0.001349, 0.001384, 0.001361, 0.001314, 0.001355, 0.001382, 0.001422, 0.001447, 0.001445, 0.001434, 0.001487];
P_U500R = [0.000548, 0.000746, 0.000902, 0.001030, 0.001144, 0.001255, 0.001276, 0.001210, 0.001226, 0.001236, 0.001228, 0.001249, 0.001275, 0.001264, 0.001236];
P_U550R = [0.000539, 0.000705, 0.000879, 0.000986, 0.001069, 0.001147, 0.001147, 0.001105, 0.001115, 0.001107, 0.001140, 0.001128, 0.001145, 0.001169, 0.001179];
P_U600R = [0.000335, 0.000518, 0.000702, 0.000830, 0.000911, 0.000970, 0.001043, 0.001010, 0.001030, 0.001025, 0.001032, 0.001027, 0.001029, 0.001057, 0.001051];
P_U650R = [0.000329, 0.000508, 0.000669, 0.000791, 0.000883, 0.000935, 0.000964, 0.000969, 0.000936, 0.000947, 0.000964, 0.000961, 0.000945, 0.000960, 0.000971];
P_U700R = [0.000160, 0.000325, 0.000504, 0.000644, 0.000739, 0.000802, 0.000873, 0.000882, 0.000889, 0.000898, 0.000894, 0.000905, 0.000876, 0.000888, 0.000911];

n_array = [200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700];

% R means Raw
P_H008R = [0.004278, 0.004179, 0.004160, 0.004096, 0.004034, 0.003996, 0.003916, 0.003890, 0.003828, 0.003785, 0.003772];
P_H012R = [0.008931, 0.008633, 0.008525, 0.008260, 0.008158, 0.008022, 0.007921, 0.007818, 0.007740, 0.007646, 0.007582];
P_H016R = [0.014601, 0.014199, 0.013805, 0.013622, 0.013467, 0.013294, 0.013174, 0.012999, 0.012860, 0.012801, 0.012697];

P_U008R = [0.001912, 0.001721, 0.001564, 0.001426, 0.001348, 0.001253, 0.001144, 0.001069, 0.000970, 0.000935, 0.000873];
P_U012R = [0.002750, 0.002183, 0.001917, 0.001668, 0.001491, 0.001314, 0.001226, 0.001115, 0.001025, 0.000947, 0.000894];
P_U016R = [0.003069, 0.002471, 0.002013, 0.001785, 0.001586, 0.001447, 0.001275, 0.001145, 0.001057, 0.000960, 0.000911];

phi = [		% k=1:25 analytical; k=26:56 experimental {{{
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
0.23446 ,	% 25
0.229073,	% 26
0.224124,	% 27
0.219228,	% 28
0.214491,	% 29
0.209858,	% 30
0.206411,	% 31
0.202695,	% 32
0.198517,	% 33
0.194765,	% 34
0.191870,	% 35
0.187840,	% 36
0.184256,	% 37
0.180952,	% 38
0.178613,	% 39
0.175323,	% 40
0.172776,	% 41
0.169925,	% 42
0.167319,	% 43
0.164788,	% 44
0.162461,	% 45
0.160314,	% 46
0.157947,	% 47
0.155790,	% 48
0.153770,	% 49
0.151721,	% 50
0.150070,	% 51
0.148275,	% 52
0.147293,	% 53
0.145117,	% 54
0.142951,	% 55
0.141381,	% 56
0.139896,	% 57
0.137973,	% 58
0.136286,	% 59
0.134698];	% 60}}}

sigma = [	% From a.xls for k=1:60 {{{
1.148359, 
1.242248,
1.324327,
1.398556,
1.425776,
1.478505,
1.505301,
1.530002,
1.558995,
1.589913,
1.601284,
1.616834,
1.628119,
1.644447,
1.676979,
1.684638,
1.68096 ,
1.692744,
1.706022,
1.714721,
1.717019,
1.728896,
1.726633,
1.738283,
1.748649,
1.754724,
1.759417,
1.760129,
1.769109,
1.770747,
1.777578,
1.779811,
1.781214,
1.788005,
1.792862,
1.793909,
1.795261,
1.798126,
1.801044,
1.805415,
1.801571,
1.811608,
1.811077,
1.819349,
1.819215,
1.82056 ,
1.816817,
1.825232,
1.823967,
1.828635,
1.827867,
1.83332 ,
1.832967,
1.838618,
1.839045,
1.843508,
1.843903,
1.843647,
1.84808 ,
1.848892];	% }}}

sigma = smooth(1:1:size(sigma,1), sigma);	% default filter is good enough

% constants
gamma = 0.17;
a1 = -0.000124; a2 = 0.1304; b = 1.5356; c = 0.1745;

% flags
plotPH = true;

% sanity check
for i = 1:size(n_array, 2)
	p = pi*0.08*0.08; k = round(p*n_array(i));
	fprintf('(n=%f, r=0.08) %f vs %f\n', n_array(i), sqrt(3)*p/4/pi, P_U008R(i)*phi(k)+P_H008R(i)*(1-phi(k)));
	p = pi*0.12*0.12; k = round(p*n_array(i));
	fprintf('(n=%f, r=0.12) %f vs %f\n', n_array(i), sqrt(3)*p/4/pi, P_U012R(i)*phi(k)+P_H012R(i)*(1-phi(k)));
	p = pi*0.16*0.16; k = round(p*n_array(i));
	fprintf('(n=%f, r=0.16) %f vs %f\n', n_array(i), sqrt(3)*p/4/pi, P_U016R(i)*phi(k)+P_H016R(i)*(1-phi(k)));
end

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% n = 200, 400, 600
% Suffix L stands for linear fit
% No suffix stands for effective radius method
% Suffix F stands for exponential fit
n = 200;
P_H200L = zeros(1, size(r200, 2));
P_U200L = zeros(1, size(r200, 2));
for i = 1:size(r200, 2)
	p = pi*r200(i)*r200(i);
	P_H200L(i) = gamma*p;
	k = round(p*n);
	P_U200L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;
	% sanity check:
	%fprintf('(r=%f) %f vs %f\n', r200(i), sqrt(3)*p/4/pi, P_U200L(i)*phi(k)+P_H200L(i)*(1-phi(k)));
end
P_H200 = zeros(1, size(r200, 2));
P_U200 = zeros(1, size(r200, 2));
for i = 1:size(r200, 2)
	p = pi*r200(i)*r200(i);
	k = round(p*n);
	sigmasq = sigma(k)*sigma(k);
	P_U200(i) = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	P_U200(i) = P_U200(i)*p/(4*pi*(4-sigmasq));	
	P_H200(i) = (phi(k)*P_U200(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end
P_H200F = zeros(1, size(r200, 2));
P_U200F = zeros(1, size(r200, 2));
for i = 1:size(r200, 2)
	lambda = (a1*n+a2)/(r200(i)^3) + b*n + c;
	tmp = (3*sqrt(3)-4*pi)*r200(i)*r200(i)*lambda;
	P_U200F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	p = pi*r200(i)*r200(i);
	k = round(p*n);
	P_H200F(i) = (phi(k)*P_U200F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end

n = 400;
P_H400L = zeros(1, size(r400, 2));
P_U400L = zeros(1, size(r400, 2));
for i = 1:size(r400, 2)
	p = pi*r400(i)*r400(i);
	P_H400L(i) = gamma*p;
	k = round(p*n);
	P_U400L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;
end
P_H400 = zeros(1, size(r400, 2));
P_U400 = zeros(1, size(r400, 2));
for i = 1:size(r400, 2)
	p = pi*r400(i)*r400(i);
	k = round(p*n);
	sigmasq = sigma(k)*sigma(k);
	P_U400(i) = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	P_U400(i) = P_U400(i)*p/(4*pi*(4-sigmasq));	
	P_H400(i) = (phi(k)*P_U400(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end
P_H400F = zeros(1, size(r400, 2));
P_U400F = zeros(1, size(r400, 2));
for i = 1:size(r400, 2)
	lambda = (a1*n+a2)/(r400(i)^3) + b*n + c;
	tmp = (3*sqrt(3)-4*pi)*r400(i)*r400(i)*lambda;
	P_U400F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	p = pi*r400(i)*r400(i);
	k = round(p*n);
	P_H400F(i) = (phi(k)*P_U400F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end

n = 600;
P_H600L = zeros(1, size(r600, 2));
P_U600L = zeros(1, size(r600, 2));
for i = 1:size(r600, 2)
	p = pi*r600(i)*r600(i);
	P_H600L(i) = gamma*p;
	k = round(p*n);
	P_U600L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;	
end
P_H600 = zeros(1, size(r600, 2));
P_U600 = zeros(1, size(r600, 2));
for i = 1:size(r600, 2)
	p = pi*r600(i)*r600(i);
	k = round(p*n);
	sigmasq = sigma(k)*sigma(k);
	P_U600(i) = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	P_U600(i) = P_U600(i)*p/(4*pi*(4-sigmasq));
	P_H600(i) = (phi(k)*P_U600(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end
P_H600F = zeros(1, size(r600, 2));
P_U600F = zeros(1, size(r600, 2));
for i = 1:size(r600, 2)
	lambda = (a1*n+a2)/(r600(i)^3) + b*n + c;
	tmp = (3*sqrt(3)-4*pi)*r600(i)*r600(i)*lambda;
	P_U600F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	p = pi*r600(i)*r600(i);
	k = round(p*n);	
	P_H600F(i) = (phi(k)*P_U600F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end

subplot(2,3,1);
if plotPH
	plot(r200, P_H200L, 'ko-', ...
		 r200, P_H200R, 'kx--', ...
		 r400, P_H400L, 'b+-', ...
		 r400, P_H400R, 'b*--', ...
		 r600, P_H600L, 'rs-', ...
		 r600, P_H600R, 'rd--');
	title(sprintf('(a) First heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_H200R, P_H200L), rmse(P_H400R, P_H400L), rmse(P_H600R, P_H600L)));
	ylabel('P_H(u,v)');
	legend('n=200 (estimated)', 'n=200 (simulated)', ...
		   'n=400 (estimated)', 'n=400 (simulated)', ...
		   'n=600 (estimated)', 'n=600 (simulated)', 'Location', 'NorthWest');	
else
	plot(r200, P_U200L, 'ko-', ...
		 r200, P_U200R, 'kx--', ...
		 r400, P_U400L, 'b+-', ...
		 r400, P_U400R, 'b*--', ...
		 r600, P_U600L, 'rs-', ...
		 r600, P_U600R, 'rd--');
	title(sprintf('(a) First heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_U200R, P_U200L), rmse(P_U400R, P_U400L), rmse(P_U600R, P_U600L)));
	ylabel('P_U(u,v)');
	legend('n=200 (estimated)', 'n=200 (simulated)', ...
		   'n=400 (estimated)', 'n=400 (simulated)', ...
		   'n=600 (estimated)', 'n=600 (simulated)', 'Location', 'SouthWest');
end
xlabel('Radio range (r)');
pos = get(gca, 'Position');
pos(3) = 0.25; pos(4) = 0.3;
set(gca, 'Position', pos);

subplot(2,3,2);
if plotPH
	plot(r200, P_H200,  'ko-', ...
		 r200, P_H200R, 'kx--', ...
		 r400, P_H400,  'b+-', ...
		 r400, P_H400R, 'b*--', ...
		 r600, P_H600,  'rs-', ...
		 r600, P_H600R, 'rd--');
	title(sprintf('(b) Second heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_H200R, P_H200), rmse(P_H400R, P_H400), rmse(P_H600R, P_H600)));
	ylabel('P_H(u,v)');
else
	plot(r200, P_U200,  'ko-', ...
		 r200, P_U200R, 'kx--', ...
		 r400, P_U400,  'b+-', ...
		 r400, P_U400R, 'b*--', ...
		 r600, P_U600,  'rs-', ...
		 r600, P_U600R, 'rd--');
	title(sprintf('(b) Second heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_U200R, P_U200), rmse(P_U400R, P_U400), rmse(P_U600R, P_U600)));
	ylabel('P_U(u,v)');
	ylim([0 4e-3]);
end
xlabel('Radio range (r)');
legend('n=200 (est.)', 'n=200 (sim.)', ...
	   'n=400 (est.)', 'n=400 (sim.)', ...
	   'n=600 (est.)', 'n=600 (sim.)', 'Location', 'NorthWest');
pos = get(gca, 'Position');
pos(3) = 0.25; pos(4) = 0.3;
set(gca, 'Position', pos);

subplot(2,3,3);
if plotPH
	plot(r200, P_H200F, 'ko-', ...
		 r200, P_H200R, 'kx--', ...
		 r400, P_H400F, 'b+-', ...
		 r400, P_H400R, 'b*--', ...
		 r600, P_H600F, 'rs-', ...
		 r600, P_H600R, 'rd--');
	title(sprintf('(c) Third heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_H200R, P_H200F), rmse(P_H400R, P_H400F), rmse(P_H600R, P_H600F)));
	ylabel('P_H(u,v)');
else
	plot(r200, P_U200F, 'ko-', ...
		 r200, P_U200R, 'kx--', ...
		 r400, P_U400F, 'b+-', ...
		 r400, P_U400R, 'b*--', ...
		 r600, P_U600F, 'rs-', ...
		 r600, P_U600R, 'rd--');
	title(sprintf('(c) Third heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_U200R, P_U200F), rmse(P_U400R, P_U400F), rmse(P_U600R, P_U600F)));
	ylabel('P_U(u,v)');
	ylim([0 4e-3]);
end
xlabel('Radio range (r)');
legend('n=200 (est.)', 'n=200 (sim.)', ...
	   'n=400 (est.)', 'n=400 (sim.)', ...
	   'n=600 (est.)', 'n=600 (sim.)', 'Location', 'NorthWest');
pos = get(gca, 'Position');
pos(3) = 0.25; pos(4) = 0.3;
set(gca, 'Position', pos);

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% r = 0.08, 0.12, 0.16
r = 0.08;
P_H008L = zeros(1, size(n_array, 2));
P_U008L = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	p = pi*r*r;
	P_H008L(i) = gamma*p;
	k = round(p*n_array(i));
	P_U008L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;
	% sanity check:
	%fprintf('(n=%f) %f vs %f\n', n_array(i), sqrt(3)*p/4/pi, P_U008L(i)*phi(k)+P_H008L(i)*(1-phi(k)));
end
P_H008 = zeros(1, size(n_array, 2));
P_U008 = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	p = pi*r*r;
	k = round(p*n_array(i));
	sigmasq = sigma(k)*sigma(k);
	P_U008(i) = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	P_U008(i) = P_U008(i)*p/(4*pi*(4-sigmasq));
	P_H008(i) = (phi(k)*P_U008(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end
P_H008F = zeros(1, size(n_array, 2));
P_U008F = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	lambda = (a1*n_array(i)+a2)/(r^3) + b*n_array(i) + c;
	tmp = (3*sqrt(3)-4*pi)*r*r*lambda;
	P_U008F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	p = pi*r*r;
	k = round(p*n);
	P_H008F(i) = (phi(k)*P_U008F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
	% sanity check:
	%fprintf('(n=%f, r=%f) %f vs %f\n', n_array(i), r, sqrt(3)*p/4/pi, P_U008F(i)*phi(k)+P_H008F(i)*(1-phi(k)));	
end

r = 0.12;
P_H012L = zeros(1, size(n_array, 2));
P_U012L = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	p = pi*r*r;
	P_H012L(i) = gamma*p;
	k = round(p*n_array(i));
	P_U012L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;	
end
P_H012 = zeros(1, size(n_array, 2));
P_U012 = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	p = pi*r*r;
	k = round(p*n_array(i));
	sigmasq = sigma(k)*sigma(k);
	P_U012(i) = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	P_U012(i) = P_U012(i)*p/(4*pi*(4-sigmasq));
	P_H012(i) = (phi(k)*P_U012(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end
P_H012F = zeros(1, size(n_array, 2));
P_U012F = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	lambda = (a1*n_array(i)+a2)/(r^3) + b*n_array(i) + c;
	tmp = (3*sqrt(3)-4*pi)*r*r*lambda;
	P_U012F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	p = pi*r*r;
	k = round(p*n);	
	P_H012F(i) = (phi(k)*P_U012F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
	% sanity check:
	%fprintf('(n=%f, r=%f) %f vs %f\n', n_array(i), r, sqrt(3)*p/4/pi, P_U012F(i)*phi(k)+P_H012F(i)*(1-phi(k)));	
end

r = 0.16;
P_H016L = zeros(1, size(n_array, 2));
P_U016L = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	p = pi*r*r;
	P_H016L(i) = gamma*p;
	k = round(p*n_array(i));
	P_U016L(i) = (gamma + (sqrt(3)/4/pi - gamma)/phi(k))*p;	
end
P_H016 = zeros(1, size(n_array, 2));
P_U016 = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	p = pi*r*r;
	k = round(p*n_array(i));
	sigmasq = sigma(k)*sigma(k);
	P_U016(i) = 8*(1-sigmasq)*acos(sigma(k)/2) + sigma(k)*(2+sigmasq)*sqrt(4-sigmasq);
	P_U016(i) = P_U016(i)*p/(4*pi*(4-sigmasq));
	P_H016(i) = (phi(k)*P_U016(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
end
P_H016F = zeros(1, size(n_array, 2));
P_U016F = zeros(1, size(n_array, 2));
for i = 1:size(n_array, 2)
	lambda = (a1*n_array(i)+a2)/(r^3) + b*n_array(i) + c;
	tmp = (3*sqrt(3)-4*pi)*r*r*lambda;
	P_U016F(i) = (1+(1/6)*exp(tmp/6)*(-6+tmp))/lambda;
	p = pi*r*r;
	k = round(p*n);	
	P_H016F(i) = (phi(k)*P_U016F(i) - sqrt(3)/4/pi*p)/(phi(k)-1);
	% sanity check:
	%fprintf('(n=%f, r=%f) %f vs %f\n', n_array(i), r, sqrt(3)*p/4/pi, P_U016F(i)*phi(k)+P_H016F(i)*(1-phi(k)));
end

subplot(2,3,4);
if plotPH
	plot(n_array, P_H008L, 'ko-', ...
		 n_array, P_H008R, 'kx--', ...
		 n_array, P_H012L, 'b+-', ...
		 n_array, P_H012R, 'b*--', ...
		 n_array, P_H016L, 'rs-', ...
		 n_array, P_H016R, 'rd--');
	title(sprintf('(a) First heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_H008R, P_H008L), rmse(P_H012R, P_H012L), rmse(P_H016R, P_H016L)));
	ylabel('P_H(u,v)');
else
	plot(n_array, P_U008L, 'ko-', ...
		 n_array, P_U008R, 'kx--', ...
		 n_array, P_U012L, 'b+-', ...
		 n_array, P_U012R, 'b*--', ...
		 n_array, P_U016L, 'rs-', ...
		 n_array, P_U016R, 'rd--');
	title(sprintf('(a) First heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_U008R, P_U008L), rmse(P_U012R, P_U012L), rmse(P_U016R, P_U016L)));
	ylabel('P_U(u,v)');
end
xlabel('Total number of nodes (n)');
legend('r=0.08 (estimated)', 'r=0.08 (simulated)', ...
	   'r=0.12 (estimated)', 'r=0.12 (simulated)', ...
	   'r=0.16 (estimated)', 'r=0.16 (simulated)', 'Location', 'SouthWest');
pos = get(gca, 'Position');
pos(3) = 0.25;  pos(4) = 0.3; pos(2) = 0.2;
set(gca, 'Position', pos);

subplot(2,3,5);
if plotPH
	plot(n_array, P_H008,  'ko-', ...
		 n_array, P_H008R, 'kx--', ...
		 n_array, P_H012,  'b+-', ...
		 n_array, P_H012R, 'b*--', ...
		 n_array, P_H016,  'rs-', ...
		 n_array, P_H016R, 'rd--');
	title(sprintf('(b) Second heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_H008R, P_H008), rmse(P_H012R, P_H012), rmse(P_H016R, P_H016)));
	ylabel('P_H(u,v)');
else
	plot(n_array, P_U008,  'ko-', ...
		 n_array, P_U008R, 'kx--', ...
		 n_array, P_U012,  'b+-', ...
		 n_array, P_U012R, 'b*--', ...
		 n_array, P_U016,  'rs-', ...
		 n_array, P_U016R, 'rd--');
	title(sprintf('(b) Second heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_U008R, P_U008), rmse(P_U012R, P_U012), rmse(P_U016R, P_U016)));
	ylabel('P_U(u,v)');
end
xlabel('Total number of nodes (n)');
legend('r=0.08 (estimated)', 'r=0.08 (simulated)', ...
	   'r=0.12 (estimated)', 'r=0.12 (simulated)', ...
	   'r=0.16 (estimated)', 'r=0.16 (simulated)', 'Location', 'NorthEast');
pos = get(gca, 'Position');
pos(3) = 0.25;  pos(4) = 0.3; pos(2) = 0.2;
set(gca, 'Position', pos);

subplot(2,3,6);
if plotPH
	plot(n_array, P_H008F, 'ko-', ...
		 n_array, P_H008R, 'kx--', ...
		 n_array, P_H012F, 'b+-', ...
		 n_array, P_H012R, 'b*--', ...
		 n_array, P_H016F, 'rs-', ...
		 n_array, P_H016R, 'rd--');
	title(sprintf('(c) Third heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_H008R, P_H008F), rmse(P_H012R, P_H012F), rmse(P_H016R, P_H016F)));
	ylabel('P_H(u,v)');
else
	plot(n_array, P_U008F, 'ko-', ...
		 n_array, P_U008R, 'kx--', ...
		 n_array, P_U012F, 'b+-', ...
		 n_array, P_U012R, 'b*--', ...
		 n_array, P_U016F, 'rs-', ...
		 n_array, P_U016R, 'rd--');
	title(sprintf('(c) Third heuristic (RMSE: %f, %f, %f)', ...
		rmse(P_U008R, P_U008F), rmse(P_U012R, P_U012F), rmse(P_U016R, P_U016F)));
	ylabel('P_U(u,v)');
end
xlabel('Total number of nodes (n)');
legend('r=0.08 (estimated)', 'r=0.08 (simulated)', ...
	   'r=0.12 (estimated)', 'r=0.12 (simulated)', ...
	   'r=0.16 (estimated)', 'r=0.16 (simulated)', 'Location', 'NorthEast');
pos = get(gca, 'Position');
pos(3) = 0.25;  pos(4) = 0.3; pos(2) = 0.2;
set(gca, 'Position', pos);

% vim:foldmethod=marker:
