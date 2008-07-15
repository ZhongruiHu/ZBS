#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "gvc.h"

using namespace std;

#define NUM_NODES	300
#define RADIO_RANGE 0.1
#define NUM_SIMS	100

#define DIST(i,j)		sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]))
#define CONNECTED(u,v)	(adjlist[(u)].find((v)) != adjlist[(u)].end())

double x[NUM_NODES], y[NUM_NODES];
map< int, set<int> > adjlist;						// adjlist[i] stores r-neighbors of i

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
	agsafeset(u, "shape", "box", "");
	agsafeset(u, "width", "0.01", "");
	agsafeset(u, "height", "0.01", "");

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
{ //{{{
	int sim = 0, i, j;
	double r;
	vector<double> vec_area;

	r = RADIO_RANGE;

	srand(1234);

	while (sim < NUM_SIMS)
	{	
		// distribute
		for (i = 0; i < NUM_NODES; i++) {
			x[i] = (double)rand() / RAND_MAX;
			y[i] = (double)rand() / RAND_MAX;
			for (j = 0; j < i; j++) {				
				if (DIST(i,j) < r) {
					//printf("|%d, %d| = %f\n", i, j, DIST(i,j));
					adjlist[i].insert(j);
					adjlist[j].insert(i);
				}				
			}
		}

		// look for an UP (u,v)
		int u = -1, v = -1;
		for (i = 0; i < NUM_NODES; i++) {
			for (set<int>::const_iterator iter = adjlist[i].begin(); iter != adjlist[i].end(); iter++) {
				double isUP = true;
				for (set<int>::const_iterator iter2 = adjlist[*iter].begin(); iter2 != adjlist[*iter].end(); iter2++) {
					if (*iter2 == i) continue;
					if (CONNECTED(*iter2, i)) {
						isUP = false;
						break;
					}
				}
				if (isUP) {
					v = i;
					u = *iter;
					break;
				}
			}
		}

		// no UP found
		if (u < 0 && v < 0) {
			printf("UP not found\n");
			continue;
		} else {
			printf("(u, v) = (%d, %d)\n", u, v);

			// viz using Graphviz
			if (sim == NUM_SIMS - 1) {
				GVC_t *gvc = gv_start("p.ps");
				Agraph_t *g = agopen("g", AGRAPH);
				Agnode_t *gn[NUM_NODES];
				for (i = 0; i < NUM_NODES; i++) {
					gn[i] = NULL;
				}
				for (i = 0; i < NUM_NODES; i++) {
					// node		
					gn[i] = gv_create_node(g, i);
					if (i == u || i == v)
						agsafeset(gn[i], "color", "blue", "");

					// edge
					for (set<int>::iterator iter = adjlist[i].begin(); iter != adjlist[i].end(); iter++) {
						if (*iter < i) {
							Agedge_t *e = agedge(g, gn[i], gn[*iter]);
						}
					}
				}
				gv_run(gvc, g);
				gv_end(gvc, g);
			}			
		}

		// clean-up
		for (i = 0; i < NUM_NODES; i++) {
			adjlist[i].clear();
		}

		// calculate area of intersection between u and v
		double theta = 2*acos(DIST(u,v)/2/r);
		double area = r*r*(theta-sin(theta));
		vec_area.push_back(area);

		// next sim round
		sim++;
	}

	// theoretical result
	printf("Theoretical: %f\n", r*r*sqrt((double)3)/4);

	// display result
	double avg, stddev;
	get_stat(vec_area, avg, stddev);
	printf("Simulation : %f ¡À%f\n", avg, stddev);
} //}}}

// vim:foldmethod=marker:
