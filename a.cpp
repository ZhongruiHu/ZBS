// Calculates the coverage of a circlea and its 1-hop neighbours 

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "gvc.h"

using namespace std;

#define NUM_SAMPLES		20000
#define NUM_RUNS		100

#define EUC_DIST(xi,yi,xj,yj)	sqrt(((xi)-(xj))*((xi)-(xj)) + ((yi)-(yj))*((yi)-(yj)))

bool fdebug = false;
bool fpolar_rnd_dist = false;
int min_n, max_n;		// number of circles
double *x, *y;			// coordinates
double r = 0.1;			// radio range
vector<double> vec_p;
vector<double> vec_p2;
vector<double> vec_d_plus_r;

template <typename T> void get_stat(T const& v, double &avg, double &stddev)
{ //{{{
	typename T::const_iterator iter;

	avg = stddev = 0;
	for (iter = v.begin(); iter != v.end(); iter++) {
		avg += (*iter);
		stddev += (*iter)*(*iter);
	}
	avg /= v.size();
	stddev = sqrt(stddev/v.size() - avg*avg);
} //}}}

GVC_t *gv_start(char *outfile)
{ //{{{
	GVC_t *gvc = gvContext();
	char *args[5];
	args[0] = (char *)"";
	args[1] = (char *)"-Tps2";
	args[2] = (char *)"-Kneato";
	args[3] = new char[3+strlen(outfile)];
	sprintf(args[3], "-o%s", outfile);
	args[4] = NULL;
	gvParseArgs(gvc, sizeof(args)/sizeof(char *)-1, args);
	//delete[] args[3];	// not necessary
	return gvc;
} //}}}

Agnode_t *gv_create_node(Agraph_t *g, int i)
{ //{{{
	Agnode_t *u;
	char buf[32];

	// label
	sprintf(buf, "%d", i);
	u = agnode(g, buf);

	// position ("!" is for fixing position)
	sprintf(buf, "%f,%f!", x[i]*8, y[i]*8);
	agsafeset(u, (char *)"pos", buf, (char *)"");

	// size		
	agsafeset(u, (char *)"fontname", (char *)"Courier", (char *)"");
	agsafeset(u, (char *)"fontsize", (char *)"8", (char *)"");
	agsafeset(u, (char *)"shape", (char *)"ellipse", (char *)"");
	sprintf(buf, "%f", 2*r*8);
	agsafeset(u, (char *)"width", buf, (char *)"");
	agsafeset(u, (char *)"height", buf, (char *)"");

	if (i == 0)
		agsafeset(u, (char *)"color", (char *)"red", (char *)"");

	return u;
} //}}}

void gv_run(GVC_t *gvc, Agraph_t *g)
{ //{{{
	agsafeset(g, (char *)"margin", (char *)"0,0", (char *)"");
	gvLayoutJobs(gvc, g);
	gvRenderJobs(gvc, g);
	gvFreeLayout(gvc, g);
} //}}}

void gv_end(GVC_t *gvc, Agraph_t *g)
{ //{{{
	agclose(g);
	gvFreeContext(gvc);
} //}}}

void one_run(int run, int n)
{ //{{{
	double p;		// p/NUM_SAMPLES gives the union area of the circles, i.e., coverage
	int i, j;		// counters

	// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
	// These circles are randomly distributed
	// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
	// make the circles
	x[0] = 0.5;
	y[0] = 0.5;
	for (i = 1; i < n; i++) {
		// random neighbors of node 0
		double d;
		if (fpolar_rnd_dist) {
			// This is random in polar coordinates:
			d = (double)rand()/RAND_MAX*(r-0.00000001);
			double theta = (double)rand()/RAND_MAX*(2*M_PI);
			x[i] = 0.5+d*cos(theta);
			y[i] = 0.5+d*sin(theta);
		} else {
			// This is random is X-Y coordinates:
			do {
				x[i] = 0.5-r+(double)rand()/RAND_MAX*(2*r);
				y[i] = 0.5-r+(double)rand()/RAND_MAX*(2*r);
				d = EUC_DIST(x[i], y[i], x[0], y[0]);			
			} while (d >= r);
		}
		vec_d_plus_r.push_back(d+r);
	}

	// random sample to get coverage
	p = 0;
	for (i = 0; i < NUM_SAMPLES; i++) {
		double sx = (double)rand()/RAND_MAX;	// x-coord of sampling point
		double sy = (double)rand()/RAND_MAX;	// y-coord of sampling point
		//printf("(sx, sy) = (%f, %f)\t", sx, sy);

		bool covered = false;
		for (j = 0; j < n; j++) {
			if (EUC_DIST(x[j], y[j], sx, sy) < r) {
				covered = true;
				break;
			}
		}
		if (covered) {
			p++;
		}
	}

	// store result: since total sim area is 1, 
	// p/NUM_SAMPLES gives the covered area
	vec_p.push_back(p/NUM_SAMPLES);
	
	/* Result is not useful
	// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
	// These circles are uniformly distributed
	// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~		
	// make the circles	
	x[0] = 0.5;
	y[0] = 0.5;
	for (i = 1; i < n; i++) {
		double theta = 2*M_PI*i/(n-1);
		x[i] = 0.5+0.5*r*cos(theta);
		y[i] = 0.5+0.5*r*sin(theta);
	}

	// random sample to get coverage
	p = 0;
	for (i = 0; i < NUM_SAMPLES; i++) {
		double sx = (double)rand()/RAND_MAX;	// x-coord of sampling point
		double sy = (double)rand()/RAND_MAX;	// y-coord of sampling point
		//printf("(sx, sy) = (%f, %f)\t", sx, sy);

		bool covered = false;
		for (j = 0; j < n; j++) {
			if (EUC_DIST(x[j], y[j], sx, sy) < r) {
				covered = true;
				break;
			}
		}
		if (covered) {
			p++;
		}
	}

	// store result: since total sim area is 1, 
	// p/NUM_SAMPLES gives the covered area
	vec_p2.push_back(p/NUM_SAMPLES);
	*/

	// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
	// vizualization
	// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
	if (fdebug || 
		(!fdebug && run == NUM_RUNS - 1 && n == max_n)) {
		char buf[256];
		sprintf(buf, "out/a-%02d-%02d.ps", n, run);
		GVC_t *gvc = gv_start(buf);
		Agraph_t *g = agopen((char *)"g", AGRAPH);

		// create nodes
		Agnode_t **gn = new Agnode_t*[n];
		for (i = 0; i < n; i++) {
			gn[i] = gv_create_node(g, i);
		}

		// draw a 2r-circle
		Agnode_t *twor = agnode(g, "");
		agsafeset(twor, "pos", "4,4!", "");
		agsafeset(twor, "shape", "ellipse", "");
		sprintf(buf, "%f", 4*r*8);
		agsafeset(twor, "width", buf, "");
		agsafeset(twor, "height", buf, "");
		agsafeset(twor, "color", "blue", "");

		gv_run(gvc, g);
		gv_end(gvc, g);
		delete[] gn;
	}
} //}}}

int main(int argc, char **argv)
{ //{{{
	int n;			// number of circles
	int run;		// counter
	double coverage, coverage2, avg_d_plus_r, stddev;

	// parse command line
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <min_num_nodes> <max_num_nodes>\n", argv[0]);
		exit(1);
	}
	if (!(min_n = atoi(argv[1])) || min_n < 1) {
		fprintf(stderr, "Error: Invalid min number of nodes.\n");
		exit(1);
	}
	if (!(max_n = atoi(argv[2]))) {
		fprintf(stderr, "Error: Invalid max number of nodes.\n");
		exit(1);
	}
	
	// parse environment variable

	if (getenv("DEBUG")) {
		printf("DEBUG set\n");
		fdebug = true;
	} else {
		printf("DEBUG not set\n");
	}
	if (getenv("POLAR_RND_DIST")) {
		printf("POLAR_RND_DIST set\n");
		fpolar_rnd_dist = true;
	} else {
		printf("POLAR_RND_DIST not set\n");
	}
	
	// debug
	//printf("M_PI*r*r = %f\n", M_PI*r*r);
	//printf("4*M_PI*r*r = %f\n", 4*M_PI*r*r);
	//printf("Union area of two circles = %f\n", 1+sqrt(27.)/4/M_PI);

	srand(8544012);

	// for each value of n
	for (n = min_n; n <= max_n; n++) {
		x = new double[n];
		y = new double[n];

		vec_p.clear();
		vec_p2.clear();
		vec_d_plus_r.clear();

		// make a number of runs for each value of n
		for (run = 0; run < NUM_RUNS; run++) {
			one_run(run, n);
		}

		// display result
		get_stat(vec_p, coverage, stddev);
		//get_stat(vec_p2, coverage2, stddev);			// ignored
		//get_stat(vec_d_plus_r, avg_d_plus_r, stddev);	// ignored
		printf("n = %3d: sim = %f ¡À%f, yen = %f\n",
			n, coverage/M_PI/r/r, stddev, 4*(1-pow(.75, n)));

		delete[] x;
		delete[] y;
	}
} //}}}

// vim:foldmethod=marker:
