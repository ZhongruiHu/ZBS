#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "gvc.h"

using namespace std;

#define NUM_SAMPLES		10000
#define NUM_RUNS		100

#define EUC_DIST(xi,yi,xj,yj)	sqrt(((xi)-(xj))*((xi)-(xj)) + ((yi)-(yj))*((yi)-(yj)))

int n, min_n, max_n;	// number of circles
double *x, *y;			// coordinates
double r = 0.1;			// radio range
double p = 0;			// p/NUM_SAMPLES gives the union area of the circles
vector<double> vec_p;

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
	args[0] = "";
	args[1] = "-Tps2";
	args[2] = "-Kneato";
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
	sprintf_s(buf, "%d", i);
	u = agnode(g, buf);

	// position ("!" is for fixing position)
	sprintf_s(buf, "%f,%f!", x[i]*8, y[i]*8);
	agsafeset(u, "pos", buf, "");

	// size		
	agsafeset(u, "fontname", "Courier", "");
	agsafeset(u, "fontsize", "8", "");
	agsafeset(u, "shape", "ellipse", "");
	sprintf_s(buf, "%f", 2*r*8);
	agsafeset(u, "width", buf, "");
	agsafeset(u, "height", buf, "");

	if (i == 0)
		agsafeset(u, "color", "red", "");

	return u;
} //}}}

void gv_run(GVC_t *gvc, Agraph_t *g)
{ //{{{
	agsafeset(g, "margin", "0,0", "");
	gvLayoutJobs(gvc, g);
	gvRenderJobs(gvc, g);
	gvFreeLayout(gvc, g);
} //}}}

void gv_end(GVC_t *gvc, Agraph_t *g)
{ //{{{
	agclose(g);
	gvFreeContext(gvc);
} //}}}

int main(int argc, char **argv)
{
	int i, j, run;		// counters

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <min_num_nodes> <max_num_nodes>\n", argv[0]);
		exit(1);
	}
	if (!(min_n = atoi(argv[1]))) {
		fprintf(stderr, "Error: Invalid min number of nodes.\n");
		exit(1);		
	}
	if (!(max_n = atoi(argv[2]))) {
		fprintf(stderr, "Error: Invalid max number of nodes.\n");
		exit(1);		
	}
	
	//printf("M_PI*r*r = %f\n", M_PI*r*r);
	//printf("4*M_PI*r*r = %f\n", 4*M_PI*r*r);
	printf("Union area of two circles = %f\n", (M_PI+(sqrt(27.)/4))/M_PI);

	for (n = min_n; n <= max_n; n++) {
		x = new double[n];
		y = new double[n];

		vec_p.clear();

		// make a number of runs for each value of n
		for (run = 0; run < NUM_RUNS; run++) {
			p = 0;

			// make the circles
			x[0] = 0.5;
			y[0] = 0.5;
			for (i = 1; i < n; i++) {
				// random neighbors of node 0
				double theta = (double)rand()/RAND_MAX*2*M_PI;
				double d = (double)rand()/RAND_MAX*r;
				x[i] = 0.5+d*cos(theta);
				y[i] = 0.5+d*sin(theta);
				d = EUC_DIST(x[i], y[i], x[0], y[0]);
				//if (run == 2 && n == max_n)
				//	printf("run %d: x[%d] = %f, y[%d] = %f, d = %f, theta = %f deg\n",
				//		run, i, x[i], i, y[i], d, theta*360/2/M_PI);
				// floating-point error maybe
				if (d > r)
					fprintf(stderr, "%s: %f > %f\n", __LINE__, d, r);
			}

			// random sampling
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
	
			// store result
			vec_p.push_back(p/NUM_SAMPLES);

			// viz
			if (run == NUM_RUNS - 1 && n == max_n) {
				GVC_t *gvc = gv_start("a.ps");
				Agraph_t *g = agopen("g", AGRAPH);

				// create nodes
				Agnode_t **gn = new Agnode_t*[n];
				for (i = 0; i < n; i++) {
					gn[i] = gv_create_node(g, i);
				}

				// draw a 2r-circle
				Agnode_t *twor = agnode(g, "");
				agsafeset(twor, "pos", "4,4!", "");
				agsafeset(twor, "shape", "ellipse", "");
				char buf[256];
				sprintf_s(buf, "%f", 4*r*8);	
				agsafeset(twor, "width", buf, "");
				agsafeset(twor, "height", buf, "");
				agsafeset(twor, "color", "blue", "");

				gv_run(gvc, g);
				gv_end(gvc, g);
				delete[] gn;
			}
		}

		// display result
		double avg, stddev;
		get_stat(vec_p, avg, stddev);
		printf("n = %d, area = %f ¡À%f, E[C_{%d}] = %f\n",
			n, avg/M_PI/r/r, stddev, n, 4*(1-pow(.75, n)));

		delete[] x;
		delete[] y;
	}
}

// vim:foldmethod=marker:
