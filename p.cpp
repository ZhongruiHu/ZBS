#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ostream>
#include <fstream>
#include "gvc.h"

using namespace std;

// - - - - Configuration - - - - - - - - -- - - - - - - - - - - - - - - 

#define NUM_SIMS		200

// options:
#define TORUS_CONVENTION			// uses toroidal instead of euclidean distances

// - - - - End configuration  - - - - - - - - - - - - - - - - - - - - - 

#define CONNECTED(u,v)			(adjlist[(u)].find((v)) != adjlist[(u)].end())
#define EUC_DIST(xi,yi,xj,yj)	sqrt(((xi)-(xj))*((xi)-(xj)) + ((yi)-(yj))*((yi)-(yj)))

// Let X be the event that u is between r and 2r away from v
// Let Y be the event that u shares no neighbor with v
int n;									// number of nodes
double r;								// radio range
double *x, *y;
set<int> *adjlist;						// adjlist[i] stores r-neighbors of i
set<int> *adjlist2;						// adjlist2[i] stores node between r and 2r away
map< pair<int, int>, double > uvdist;	// stores neighboring nodes' distances

/**
 * @param i					Node ID of the first node
 * @param j					Node ID of the second node
 * @param area_width 	Width of the simulation area
 * @param area_height	Height of the simulation area
 */
double distance(int i, int j, double area_width, double area_height)
{ //{{{
	double tmp;	

	// ensure order
	if (i > j) {
		tmp = i;
		i = j;
		j = (int)tmp;
	}

	// query database
	pair<int,int> p(i, j);
	map< pair<int,int>,double >::iterator iter = uvdist.find(p);
	if (iter != uvdist.end())
		return iter->second;
	
#ifdef TORUS_CONVENTION
	double min;

	min = EUC_DIST(x[i],				y[i],				x[j], y[j]);
	tmp = EUC_DIST(x[i] + area_width,	y[i],				x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i] - area_width,	y[i],				x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i],				y[i] + area_height,	x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i],				y[i] - area_height,	x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i] + area_width,	y[i] + area_height,	x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i] + area_width,	y[i] - area_height,	x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i] - area_width,	y[i] + area_height,	x[j], y[j]);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(x[i] - area_width,	y[i] - area_height,	x[j], y[j]);
	if (tmp < min) min = tmp;
	uvdist[p] = min;
	return min;
#else
	tmp = EUC_DIST(x[i], y[i], x[j], y[j]);
	uvdist[p] = tmp;
	return tmp;
#endif
} //}}}

inline double joint_area(int u, int v)
{ //{{{
	double theta = 2*acos(distance(u,v,1,1)/2./r);
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
	double avg_deg = 0;			// average degree (NEEDED here) (doesn't make much diff if double)

	// parse command line params
	if (argc < 3) {
		printf("Usage: %s <radio range> <number of nodes>\n", argv[0]);
		exit(1);
	}
	if (!(r = atof(argv[1]))) {
		printf("Error: Invalid radio range.\n");
		exit(1);
	}
	if (!(n = atoi(argv[2])) || n < 0) {
		printf("Error: Invalid number of nodes.\n");
		exit(1);
	}

	// init vars
	x = new double[n];
	y = new double[n];
	adjlist = new set<int>[n];
	adjlist2 = new set<int>[n];

	// start simulation rounds
	srand(123456);
	while (sim < NUM_SIMS)
	{	
		int u = -1, v = -1;		// UP
		int uh = -1, vh = -1;	// HP
		int nX = 0;				// incremented whenever event X occurs
		int nY_X = 0;			// incremented whenever event X and event Y occurs
		int sum_deg = 0;

		// distribute and init each node
		for (i = 0; i < n; i++) {
			x[i] = (double)rand() / RAND_MAX;
			y[i] = (double)rand() / RAND_MAX;
			for (j = 0; j < i; j++) {				
				if (distance(j,i,1,1) <= r) {
					adjlist[i].insert(j);
					adjlist[j].insert(i);
					sum_deg += 2;
				} else if (distance(j,i,1,1) <= 2*r) {
					adjlist2[i].insert(j);
					adjlist2[j].insert(i);
					vec_jarea.push_back(joint_area(j, i));
				}
			}
		}
		avg_deg = (int)((double)sum_deg/n);

		// calculate average number of neighbors (sanity check)
		/*
		double sum = 0;
		for (i = 0; i < n; i++) {
			sum += adjlist[i].size();			
		}
		avg_deg = (int)(sum/n);
		*/

		// look for an UP (u,v)		
		for (i = 0; i < n; i++) {	
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
			for (i = 1; i < n; i++) {
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
				Agnode_t **gn = new Agnode_t *[n];
				for (i = 0; i < n; i++) {
					gn[i] = NULL;
				}
				for (i = 0; i < n; i++) {
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
				delete[] gn;
			}

			// debug
			printf("%3d: UP: (%3d, %3d)\tHP: (%3d, %3d)\tavg_deg: %f\n", sim+1, u, v, uh, vh, avg_deg);
			//assert(!CONNECTED(u,v));
			//assert(!CONNECTED(uh,vh));

			// calculate area of intersection between u and v
			vec_uarea.push_back(joint_area(u, v));
			vec_harea.push_back(joint_area(uh, vh));
			vec_P_Y_X.push_back((double)nY_X/nX);

			// reset data
			for (i = 0; i < n; i++) {
				adjlist[i].clear();
				adjlist2[i].clear();
			}
			uvdist.clear();
		}
		
		// this round doesn't count if no UP found
		if (u < 0) {
			printf("UP not found\n");
			continue;
		}

		// next sim round
		sim++;
	}

	// theoretical result (HP)
	double P_W_X = sqrt(3.)/4*r*r;
	double P_Y = 1 - 4*M_PI*r*r*(1 - pow(0.75, avg_deg));
	double P_X_Y = 3*M_PI*r*r*pow(1-sqrt(3.)/4/M_PI, avg_deg);
	P_X_Y /= (1 - 4*M_PI*r*r*(1 - pow(0.75, avg_deg)));
	double P_Y_X = pow(1 - sqrt(3.)/(4*M_PI), avg_deg);	// wrong!
	//double P_Y_X = pow(.75, avg_deg)*(1 - 4*M_PI*r*r*(1 - pow(.75, avg_deg)));	// wrong!
	double P_X_YC = 3*M_PI*r*r*(1 - P_Y_X)/(1 - P_Y);
	printf("Theoretical P[W|X] : %f\n", P_W_X);
	//printf("Theoretical P[Y|X] : %f\n", P_Y_X);
	//printf("Theoretical P[Y]   : %f\n", P_Y);	
	//printf("Theoretical P[X|Y] : %f\n", P_X_Y);
	//printf("Theoretical P[X|Y']: %f\n", P_X_YC);

	// display result (UP)
	double sim_P_W_X, sim_P_Y_X, sim_P_U, sim_P_H, stddev;
	get_stat(vec_jarea, sim_P_W_X, stddev);
	printf("Simulated   P[W|X] : %f ¡À%f\n", sim_P_W_X, stddev);
	get_stat(vec_P_Y_X, sim_P_Y_X, stddev);
	printf("Simulated   P[Y|X] : %f ¡À%f (k = %f)\n", sim_P_Y_X, stddev, avg_deg);
	get_stat(vec_uarea, sim_P_U, stddev);	
	printf("Simulated   P_U    : %f ¡À%f\n", sim_P_U, stddev);
	get_stat(vec_harea, sim_P_H, stddev);
	printf("Simulated   P_H    : %f ¡À%f\n", sim_P_H, stddev);

	// experiments
	printf("P[W|X] in theory   : %f\n", sim_P_U*P_Y_X + sim_P_H*(1-P_Y_X)); // wrong
	printf("P[W|X] in reality  : %f\n", sim_P_U*sim_P_Y_X + sim_P_H*(1-sim_P_Y_X)); // says sim_P_Y_X is right

	// output some results to a file
	/*
	ofstream fs;
	fs.open("p.uarea.dat", ios_base::out);
	if (fs.good()) {
		for (vector<double>::const_iterator iter = vec_uarea.begin(); iter != vec_uarea.end(); iter++) {
			fs << *iter << endl;
		}
		fs.close();
	} else {
		printf("Could not open file for output.\n");
	}
	*/

	// cleanup vars
	delete[] x;
	delete[] y;
	delete[] adjlist;
	delete[] adjlist2;
} //}}}

// vim:foldmethod=marker:
