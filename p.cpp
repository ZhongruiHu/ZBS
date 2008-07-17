#define _USE_MATH_DEFINES

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
#define NUM_SIMS	200

#define DIST(i,j)		sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]))
#define CONNECTED(u,v)	(adjlist[(u)].find((v)) != adjlist[(u)].end())

// Let X be the event that u is between r and 2r away from v
// Let Y be the event that u shares no neighbor with v
double r;
double x[NUM_NODES], y[NUM_NODES];
map< int, set<int> > adjlist;						// adjlist[i] stores r-neighbors of i
map< int, set<int> > adjlist2;						// adjlist2[i] stores node between r and 2r away

inline double joint_area(int u, int v)
{ //{{{
	double theta = 2*acos(DIST(u,v)/2/r);
	return r*r*(theta-sin(theta));
} //}}}

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
	vector<double> vec_jarea;	// stores joint areas of all pairs r<d<=2r apart
	vector<double> vec_P_Y_X;	// stores nY_X/nX of each sim round
	vector<double> vec_uarea;	// stores joint areas of UPs
	vector<double> vec_harea;	// stores joint areas of HPs	
	int avg_deg = 0;			// average degree (NEEDED here)

	r = RADIO_RANGE;
	srand(123456);
	while (sim < NUM_SIMS)
	{	
		int u = -1, v = -1;		// UP
		int uh = -1, vh = -1;	// HP
		int nX = 0;				// incremented whenever event X occurs
		int nY_X = 0;			// incremented whenever event X and event Y occurs
		double sum_deg = 0;

		// distribute
		for (i = 0; i < NUM_NODES; i++) {
			x[i] = (double)rand() / RAND_MAX;
			y[i] = (double)rand() / RAND_MAX;
			for (j = 0; j < i; j++) {				
				if (DIST(i,j) <= r) {
					adjlist[i].insert(j);
					adjlist[j].insert(i);
					sum_deg++;
				} else if (DIST(i,j) <= 2*r) {
					adjlist2[i].insert(j);
					adjlist2[j].insert(i);
					vec_jarea.push_back(joint_area(i, j));
				}
			}
		}
		avg_deg = 2*(int)(sum_deg/NUM_NODES);

		// calculate average number of neighbors (sanity check)
		/*
		double sum = 0;
		for (i = 0; i < NUM_NODES; i++) {
			sum += adjlist[i].size();			
		}
		avg_deg = (int)(sum/NUM_NODES);
		*/

		// look for an UP (u,v)		
		for (i = 0; i < NUM_NODES; i++) {	
			for (set<int>::const_iterator iter = adjlist2[i].begin(); iter != adjlist2[i].end(); iter++) {
				// at this stage i and *iter are between r and 2r apart
				// now we iterate through *iter's neighbors
				nX++;
				double isUP = true;
				for (set<int>::const_iterator iter2 = adjlist[*iter].begin(); iter2 != adjlist[*iter].end(); iter2++) {
					if (*iter2 == i) continue;
					if (CONNECTED(*iter2, i)) {
						isUP = false;
						break;
					}
				}				
				if (isUP) {
					nY_X++;
					if (u < 0) { // we only want to keep the first UP
						v = i;
						u = *iter;
					}					
				}
			}
		}

		// UP found, then look fro HP
		if (u >= 0) {	
			// look for an HP (uh, vh)
			// skip the sink intentionally
			for (i = 1; i < NUM_NODES; i++) {
				for (set<int>::const_iterator iter = adjlist2[i].begin(); iter != adjlist2[i].end(); iter++) {
					double isHP = false;
					for (set<int>::const_iterator iter2 = adjlist[*iter].begin(); iter2 != adjlist[*iter].end(); iter2++) {
						if (*iter2 == i) continue;
						if (CONNECTED(*iter2, i)) {
							isHP = true;
							break;
						}
					}
					if (isHP) {
						vh = i;
						uh = *iter;
						break;
					}
				}
				if (uh >= 0)
					break;
			}

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
					if (i == uh || i == vh)
						agsafeset(gn[i], "color", "green", "");

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

			// debug
			printf("%3d: UP: (%3d, %3d)\tHP: (%3d, %3d)\tavg_deg: %d\n", sim+1, u, v, uh, vh, avg_deg);
			//assert(!CONNECTED(u,v));
			//assert(!CONNECTED(uh,vh));
		}

		// clean-up
		for (i = 0; i < NUM_NODES; i++) {
			adjlist[i].clear();
			adjlist2[i].clear();
		}
		
		// this round doesn't count if no UP found
		if (u < 0) {
			printf("UP not found\n");
			continue;
		}

		// calculate area of intersection between u and v
		vec_uarea.push_back(joint_area(u, v));
		vec_harea.push_back(joint_area(uh, vh));
		vec_P_Y_X.push_back((double)nY_X/nX);

		// next sim round
		sim++;
	}

	// theoretical result (HP)
	double P_W_X = sqrt(3.)/4*r*r;
	double P_Y = 1 - 4*M_PI*r*r*(1 - pow(0.75, avg_deg));
	double P_X_Y = 3*M_PI*r*r*pow(1-sqrt(3.)/4/M_PI, avg_deg);
	P_X_Y /= (1 - 4*M_PI*r*r*(1 - pow(0.75, avg_deg)));
	double P_Y_X = pow(1 - sqrt(3.)/4/M_PI, avg_deg);
	double P_X_YC = 3*M_PI*r*r*(1 - P_Y_X)/(1 - P_Y);
	printf("Theoretical P[W|X] : %f\n", P_W_X);
	printf("Theoretical P[Y|X] : %f\n", P_Y_X);
	//printf("Theoretical P[Y]   : %f\n", P_Y);	
	//printf("Theoretical P[X|Y] : %f\n", P_X_Y);
	//printf("Theoretical P[X|Y']: %f\n", P_X_YC);

	// display result (UP)
	double sim_P_W_X, sim_P_Y_X, sim_P_U, sim_P_H, stddev;
	get_stat(vec_jarea, sim_P_W_X, stddev);
	printf("Simulated   P[W|X] : %f ¡À%f\n", sim_P_W_X, stddev);
	get_stat(vec_P_Y_X, sim_P_Y_X, stddev);
	printf("Simulated   P[Y|X] : %f ¡À%f\n", sim_P_Y_X, stddev);
	get_stat(vec_uarea, sim_P_U, stddev);	
	printf("Simulated   P_U    : %f ¡À%f\n", sim_P_U, stddev);
	get_stat(vec_harea, sim_P_H, stddev);
	printf("Simulated   P_H    : %f ¡À%f\n", sim_P_H, stddev);

	// experiment
	printf("In theory          : %f\n", sim_P_U*P_Y_X + sim_P_H*(1-P_Y_X)); // correct
	printf("Should be          : %f\n", sim_P_U*sim_P_Y_X + sim_P_H*(1-sim_P_Y_X)); // correct
	double p = M_PI*r*r;
	printf("P_U?               : %f\n", 1.213525*pow(p, avg_deg+1));
	printf("P_U?               : %f\n", 1.213525*p*(1-pow(0.1378*p, avg_deg))/pow(0.8621, avg_deg));
} //}}}

// vim:foldmethod=marker:
