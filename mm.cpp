/* Only compatible with VC++ because set.erase is different between VC++ and GNU implementation */

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_RAND_S
	#define _USE_MATH_DEFINES
#else
	#define sprintf_s sprintf
	#define _stricmp	strcasecmp
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include "gvc.h"

using namespace std;

// - - - - Configuration - - - - - - - - -- - - - - - - - - - - - - - - 

#ifdef _DEBUG
#	define NUM_RUNS 1
#else
#	define NUM_RUNS 100
#endif

#define GAMMA 0.17

// options:
#define TORUS_CONVENTION		// uses toroidal instead of euclidean distances
//#define PAR_POL_DEPTH				// policy for choosing parent depending on depth,
//#define PAR_POL_SLOT				// or slot,
//#define PAR_POL_DEPTH_SLOT	// or depth then slot,
#define PAR_POL_SLOT_DEPTH	// or slot then depth
//#define PRECISE_PROB				// calculate probabilities precisely using distance information

// - - - - End configuration  - - - - - - - - - - - - - - - - - - - - - 

double phi[] = {0,	// first element is dummy
0.862168,
0.756130,
0.673142,
0.607086,
0.553643,
0.509726,
0.473108,
0.442160,
0.415680,
0.392767,
0.372737,
0.355069,
0.339355,
0.325277,
0.312580,
0.301063,
0.290558,
0.280932,
0.272072,
0.263885,
0.256292,
0.249233,
0.242636,
0.236162,
0.234460,		// 25
0.225541,		// experimental values start from here
0.219539,
0.217656,
0.208506,
0.206910,
0.201181,
0.201857,
0.193218};	// 33

// copied from sigmak.m
double sigma[] = {0,	// first element is dummy
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
1.680960,
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
1.820560,
1.816817,
1.825232,
1.823967,
1.828635,
1.827867,
1.833320,
1.832967,
1.838618,
1.839045,
1.843508,
1.843903,
1.843647,
1.848080,
1.848892,
1.847799,
1.848122,
1.853762,
1.856365,
1.859282,
1.858016,
1.856038,
1.858209,
1.859471,
1.862396,
1.860649,
1.862432,
1.865573,
1.868555,
1.864094,
1.863789,
1.868687,
1.869662,
1.872337,
1.873923,
1.872995,
1.876393,
1.871412,
1.878048,
1.878482,
1.878739,
1.879569,
1.879286,
1.879293,
1.883116,
1.884680,
1.882508,
1.883078,
1.883390,
1.883230,
1.887134,
1.889005,
1.888848,
1.885877};	// k = 99

#define EUC_DIST(xi,yi,xj,yj)	sqrt(((xi)-(xj))*((xi)-(xj)) + ((yi)-(yj))*((yi)-(yj)))
#define CONNECTED(u,v)				(adjlist[(u)].find((v)) != adjlist[(u)].end())
#define CONNECTED2R(u,v)			(adjlist2r[(u)].find((v)) != adjlist2r[(u)].end())
#define NUM_CHILDREN(u)				(int)(devices[(u)].ZR_children.size() + devices[(u)].ZED_children.size())
#define SCHEME_NAME(s)				(s == S_TSENG ? "tseng" : \
																(s == S_D1VHU ? "d1vhu" : \
																	(s == S_D1HU ? "d1hu" : \
																		(s == S_D2VHU ? "d2vhu" : \
																			(s == S_D2HU ? "d2hu" : \
																				(s == S_D2U ? "d2u" : \
																					(s == S_CVHU ? "cvhu" : \
																						(s == S_CHU ? "chu" : \
																							(s == S_CU ? "cu" : \
																								(s == S_C ? "c" : ""))))))))))

// MUST NOT modify the sequence of this:
typedef enum {
	S_TSENG,
	S_D1VHU,
	S_D1HU,
	S_D2VHU,
	S_D2HU,
	S_D2U,
	S_CVHU,
	S_CHU,
	S_CU,
	S_C
} scheme_t;

typedef enum {UNKNOWN, ZC_ZR, ZED} role_t;

typedef enum {IP, VP, HP, UP} pair_type_t;

typedef struct {
	double pos_x;
	double pos_y;
	int depth;
	int parent_id;
	set<int> ZR_children;
	set<int> ZED_children;
	role_t role;
} device_t;

scheme_t scheme;
double area_width, area_height;
double radio_range;
bool degFixed = false;
int degree;													// expected degree of a node (either this or num_FFD is specified)
int num_FFD;												// all nodes are FFDs
int Lm;															// max depth
int Cm;															// max children
int Rm;															// max children that can be ZRs
int num_slots = 0;
device_t *devices;
set<int> *adjlist;									// adjlist[i] stores r-neighbors of i
set<int> *adjlist2r;								// adjlist2r[i] stores 2r-neighbors of i
map< pair<int, int>, double > uvdist;			// stores neighboring nodes' distances
int *slot;													// slot[i] stores the slot ID of the ZC/ZR i
map<int, int> ZED_slot;							// ZED_slot[i] stores the slot ID of the ZED i (not needed by Tseng)
map< int, set<int> > who_use_slot;
int *reassoc_count;
double prob_link;										// see paper
double P_V;													// see paper
double P_H;													// see paper
double P_U;													// see paper


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
	sprintf_s(buf, "%f,%f!", devices[i].pos_x/area_width*8, devices[i].pos_y/area_height*8);
	agsafeset(u, "pos", buf, "");

	// size		
	agsafeset(u, "fontname", "Courier", "");
	agsafeset(u, "fontsize", "8", "");
	agsafeset(u, "shape", "box", "");
	agsafeset(u, "width", "0.01", "");
	agsafeset(u, "height", "0.01", "");
	if (i == 0)
		agsafeset(u, "color", "red", "");
	else
		if (devices[i].role == ZC_ZR)
			agsafeset(u, "color", "green", "");
		else if (devices[i].role == ZED)
			agsafeset(u, "color", "blue", "");

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

/**
 * @returns true at a probability of p.
 */
bool bernoulli(double p)
{ //{{{
#ifdef _MSC_VER	
	unsigned int nonce;	
	rand_s(&nonce);
	return ((double)nonce/UINT_MAX < p ? true : false);
#else	
	return ((double)rand()/RAND_MAX < p ? true : false);
#endif
} //}}}

/**
 * @return the ID of the node's neighbor whose beacon collides with v's.
 */
int check_collision(int node, int v)
{ //{{{
	for (set<int>::const_iterator iter = adjlist[node].begin(); iter != adjlist[node].end(); iter++) {
		if (*iter != v && slot[*iter] == slot[v]) {
			return *iter;
		}
	}
	return -1;
} //}}}

void get_avg_latency(double &avg_latency, int &max_latency)
{ //{{{	
	bool path_breaks;
	int i, path_latency, node, parent, num_paths = 0;
	int colliding_node;

	avg_latency = 0;
	max_latency = 0;

	for (i = 1; i < num_FFD; i++) {
		path_breaks = false;
		path_latency = 0;
		node = i;
		parent = devices[node].parent_id;
#ifdef _DEBUG
		printf("path: %d (%d) ", node, slot[node]);
#endif
		while (1) {
#ifdef _DEBUG
			printf("-> %d (%d) ", parent, (parent >= 0 ? slot[parent] : -1));
#endif			
			if (parent < 0) {
				path_breaks = true;
				break;
			}
			if ((colliding_node = check_collision(node, parent)) > 0)
				printf("(%d's neighbors %d and %d share slot %d) ", node, parent, colliding_node, slot[parent]);
			if (slot[node] < 0)
				// a ZED does not occupy a slot, instead
				// it follows the slot of its parent;
				// in this case, we should count the latency as 0
				assert(devices[node].role == ZED);
			else if (slot[parent] > slot[node])
				path_latency += (slot[parent] - slot[node]);
			else
				path_latency += (num_slots - slot[node] + slot[parent]);
			if (parent == 0)
				break;
			node = parent;
			parent = devices[node].parent_id;
		}
		if (!path_breaks) {
			avg_latency += path_latency;
			if (path_latency > max_latency)
				max_latency = path_latency;
			num_paths++;
#ifdef _DEBUG
			printf("\n\tnum_paths = %3d, path_latency = %4d slots\n",
				 num_paths, path_latency);
#endif
		} else {
#ifdef _DEBUG
			printf("\n");
#endif
		}
	}
	avg_latency /= num_paths;
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

void get_stat(int *hist, int max_x, double &avg, double &stddev)
{ //{{{
	int i, count = 0;

	avg = stddev = 0;
	for (i = 0; i < max_x+1; i++) {
		avg += i*hist[i];
		count += hist[i];
		stddev += i*i*hist[i];
	}
	avg /= count;
	stddev = sqrt(stddev/count - avg*avg);
} //}}}

/** 
 * This function is invoked when i and j use the same slot.
 * @parameter i	The ID of the first node.
 * @parameter j	The ID of the second node.
 * Originally judge_IVHU().
 * This is wrong, because HP and UP can never be detected.
 */
pair_type_t get_pair_type(int i, int j)
{//{{{
	if (CONNECTED(i, j))
	{		
		if ( !devices[i].ZR_children.empty()
			|| !devices[i].ZED_children.empty()
			|| !devices[j].ZR_children.empty()
			|| !devices[j].ZED_children.empty())
			// if i and j are neighbors, and either i or j is a parent
			return IP;
		else
			// if i and j are neighbors, but neither i nor j has any child
			return VP;
	}
	else 
	{	
		bool has_common_neighb = false;
		set<int>::const_iterator iter;

		for (iter = adjlist[i].begin(); iter != adjlist[i].end(); iter++) {
			if (CONNECTED(*iter, j)) {
				// if i and j aren't connected, but have a common neighbor
				// and either i or j is a parent of the common neighbor
				if (devices[*iter].parent_id == i || devices[*iter].parent_id == j)
					return IP;
				has_common_neighb = true;
			}
		}

		if (has_common_neighb)
			// if i and j aren't connected, but have a common neighbor
			// but neither i nor j is a parent of the common neighbor
			return HP;								
		else
			// if i and j aren't connected, and have no common neighbor
			return UP;
	}

	// this should never be reached
	assert(false);
};//}}}

double get_risk(int i, int j, pair_type_t t)
{ //{{{
#ifdef PRECISE_PROB
	// ensure order
	double tmp;
	if (i > j) {
		tmp = i;
		i = j;
		j = tmp;
	}

	// query database
	pair<int,int> p(i, j);

	// theta ranges from 0 to 120 degrees
	double theta = 2*acos(uvdist[p]/2/radio_range);
	return radio_range*radio_range*(theta - sin(theta));		
#else
	return (t == VP ? P_V : (t == HP ? P_H : P_U));
#endif
} //}}}

/**
 * Disassociate oneself from one's parent,
 * and dissassociate its descendants too.
 * This is necessary for avoiding loops.
 */
void disassociate(int node)
{ //{{{
	set<int>::const_iterator iter;

	assert(devices[node].role != UNKNOWN);

	reassoc_count[node]++;

	if (devices[node].role == ZC_ZR) {
		// clear slot occupancy
		assert(slot[node] >= 0);
		who_use_slot[slot[node]].erase(node);
		slot[node] = -1;
		
		// detach from parent
		devices[ devices[node].parent_id ].ZR_children.erase(
			 devices[ devices[node].parent_id ].ZR_children.find(node));

		// reset other fields
		// MUST do this last, because we needed this info earlier:
		devices[node].depth = Lm + 1;
		devices[node].parent_id = -1;
		devices[node].role = UNKNOWN;
		
		// recursively disassociate descendants
		for (iter = adjlist[node].begin(); iter != adjlist[node].end(); iter++) {
			if (devices[*iter].parent_id == node) {
				disassociate(*iter);
			}
		}
	} else {
		// clear slot occupancy
		assert(ZED_slot[node] >= 0);
		ZED_slot.erase(node);
		
		// detach from parent
		devices[ devices[node].parent_id ].ZED_children.erase(
			 devices[ devices[node].parent_id ].ZED_children.find(node));

		// reset other fields
		// MUST do this last, because we needed this info earlier:
		devices[node].depth = Lm + 1;
		devices[node].parent_id = -1;
		devices[node].role = UNKNOWN;		
	}	
} //}}}

/**
 * Distributed algorithm.
 */
int pick_slot_yen_d(int j, int u)
{ //{{{
	int l;
	bool collides;
	set<int>::iterator iter, iter2;
	set<int> relevant_neighbs;
	int test_slot, neighb_slot;
	pair_type_t rel;
	double P;
	

	// find relevant neighbs
	// in practice, this is achieved by a node broadcasting a list of the slots
	// occupied by itself and its neighbors
	for (iter = adjlist[u].begin(); iter != adjlist[u].end(); iter++) {
		if (*iter == u) continue;
		relevant_neighbs.insert(*iter);
		if (scheme == S_D2VHU || scheme == S_D2HU || scheme == S_D2U) {
			for (iter2 = adjlist[*iter].begin(); iter2 != adjlist[*iter].end(); iter2++) {
				if (*iter2 == *iter) continue;
				relevant_neighbs.insert(*iter2);
			}
		}
	}

	// find a free slot
	for (l = 1; l < num_slots; l++)
	{
		collides = false;
		test_slot = slot[j]<l ? num_slots+slot[j]-l : slot[j]-l;
		for (iter = relevant_neighbs.begin(); iter != relevant_neighbs.end(); iter++)
		{
			if (*iter == j)
				continue;

			neighb_slot = (devices[*iter].role == ZED ? ZED_slot[*iter] : slot[*iter]);

			// if neighbor's slot == test slot, it maybe acceptable
			// depending on the scheme
			if (neighb_slot == test_slot) {
				rel = get_pair_type(u, *iter);
				P = get_risk(u, *iter, rel);

#ifdef _DEBUG
				// handy for debugging, keep as is
				//if (u == 35) {
				//	printf("%3d checks slot %d: %d and %d are type %d\n",
				//		u, test_slot, u, *iter, rel);
				//}
#endif
				
				if (rel == IP)
					collides = true;
				else if (rel == VP)
					collides =(
						(scheme == S_D1VHU && bernoulli(P)) ||
						(scheme == S_D1HU) ||
						(scheme == S_D2VHU && bernoulli(P)) ||
						(scheme == S_D2HU) ||
						(scheme == S_D2U));
				else
					// D1* algorithms cannot detect HP's
					collides = (
						(scheme == S_D2VHU && bernoulli(P)) ||
						(scheme == S_D2HU && bernoulli(P)) ||
						(scheme == S_D2U));
				// distributed algorithms cannot detect UP's
			}

			// if collides, decrement test_slot and try again
			if (collides)
				break;

		} // for each neighbor, consider test_slot

		// all neighbors' slots turn out to be compatible
		if (!collides) {
#ifdef _DEBUG
			// handy for debugging, keep as is
			//if (u == 35) {
			//	printf("%3d settles on %d\n", u, test_slot);
			//}
#endif			
			return test_slot;
		}

	} // for each possible test_slot

	return -1;
} //}}}

/**
 * Centralized algorithm.
 */
int pick_slot_yen_c(int j, int u)
{ //{{{
	int l;
	bool collides;
	set<int>::iterator iter;
	int test_slot;

	// find a free slot
	for (l = 1; l < num_slots; l++) {
		collides = false;
		test_slot = slot[j]<l ? num_slots+slot[j]-l : slot[j]-l;
		for (iter = who_use_slot[test_slot].begin(); iter != who_use_slot[test_slot].end(); iter++) {
			// if we are here, it means some other node is already using test_slot
			pair_type_t rel = get_pair_type(u, *iter);
			double P = get_risk(u, *iter, rel);
			if (rel == IP)
				collides = true;
			else if (rel == VP)
				collides = (
					 (scheme == S_CVHU && bernoulli(P)) ||
					 (scheme == S_CHU) ||
					 (scheme == S_CU) ||
					 (scheme == S_C));
			else if (rel == HP)
				collides = (
					 (scheme == S_CVHU && bernoulli(P)) ||
					 (scheme == S_CHU && bernoulli(P)) ||
					 (scheme == S_CU) ||
					 (scheme == S_C));
			else if (rel == UP)
				collides = (
					 (scheme == S_CVHU && bernoulli(P)) ||
					 (scheme == S_CHU && bernoulli(P)) ||
					 (scheme == S_CU && bernoulli(P)) ||
					 (scheme == S_C));
			if (collides)
				break;
		}
		if (!collides)
			return test_slot;
	}

	return -1;
} //}}}

/**
 * Decide u's slot number, where j is u's parent candidate.
 */
int pick_slot_yen(int j, int u)
{ //{{{
	if (scheme == S_D1VHU || scheme == S_D1HU || scheme == S_D2VHU || scheme == S_D2HU || scheme == S_D2U) {
		return pick_slot_yen_d(j, u);		
	} else {
		return pick_slot_yen_c(j, u);			
	}
} //}}}

/**
 * Decide u's slot number, where j is u's parent candidate.
 */
int pick_slot_tseng(int j, int u)
{ //{{{
	bool collides;
	set<int>::iterator iter;
	int test_slot, initial;

	// find a free slot (note: HELLO packets from 2r-neighbors
	// should have been received at boot-up)
	initial = test_slot = slot[j]<1 ? num_slots+slot[j]-1 : slot[j]-1;
	do {
		collides = false;
		for (iter = adjlist2r[u].begin(); iter != adjlist2r[u].end(); iter++) {
			if (test_slot == slot[*iter]) {
				collides = true;
				break;
			}
		}
		if (!collides) {
			return test_slot;
		}
		test_slot = (test_slot - 1) % num_slots;
	} while (test_slot != initial);

	return -1;
} //}}}

void new_tree_yen()
{ //{{{
	bool new_ZR_found;
	int i, j, node;
	vector<int> par_cand;	// parent candidates
	vector<int>::iterator iter;
	vector<int>::iterator iter2;

	// assoc_order[i] = u, means at the i-th iteration process node u
	vector<int> assoc_order;
	
	for (i = 1; i < num_FFD; i++)
		assoc_order.push_back(i);

	do {
		new_ZR_found = false;

		random_shuffle(assoc_order.begin(), assoc_order.end());
		
		for (vector<int>::const_iterator round = assoc_order.begin(); round != assoc_order.end(); round++)
		{
			node = *round;
			
			// if already associated, check for beacon collisions between parent and
			// any of the neighbors
			if (devices[node].role != UNKNOWN) {
				int colliding_node = check_collision(node, devices[node].parent_id);
				if (colliding_node > 0) {
#ifdef _DEBUG
					printf("%3d -X-> %3d: which collides with %d on slot %d\n",
						 node, devices[node].parent_id, colliding_node, slot[colliding_node]);
#endif
					// if there's beacon collision, disassociate with current parent
					disassociate(node);
				} else {
					// if there's no beacon collision, then carry on with other nodes
					continue;
				}
			}

#ifdef _DEBUG
			// handy for debugging, leave as is
			//if (node == 35) {
			//	printf("Before: %d's neighbors: ", node);
			//	for (iter = adjlist[node].begin(); iter != adjlist[node].end(); iter++) {
			//		printf("%d (%d), ", *iter, slot[*iter]);
			//	}
			//	printf("\n");
			//}
#endif

			// Keep this code for reference:
			//par_cand.clear();
			//iter = adjlist[node].begin();
			//while (iter != adjlist[node].end()) {
			//	collides = false;
			//	riter = adjlist[node].rbegin();
			//	while (riter != adjlist[node].rend() && *riter != *iter) {
			//		if (slot[*riter] == slot[*iter]) {
			//			collides = true;
			//			break;
			//		}
			//		riter++;
			//	}
			//	if (!collides)
			//		par_cand.insert(*iter);
			//	iter++;
			//}
			
			// collect all neighbors and eliminate those that share the same slot
			// note: the above doesn't work, ONLY this elimination method works
			par_cand.clear();
			for (set<int>::iterator sit = adjlist[node].begin(); sit != adjlist[node].end(); sit++)
				par_cand.push_back(*sit);
			for (iter = par_cand.begin(); iter != par_cand.end();) {
				bool collides = false;
				for (iter2 = iter+1; iter2 != par_cand.end();) {
					if (slot[*iter2] == slot[*iter]) {
						collides = true;
						iter2 = par_cand.erase(iter2);
					} else {
						iter2++;
					}
				}
				if (collides)
					iter = par_cand.erase(iter);
				else
					iter++;
			}

#ifdef _DEBUG
			// handy for debugging, leave as is
			//if (node == 35) {
			//	printf("After: %d's neighbors: ", node);
			//	for (iter = par_cand.begin(); iter != par_cand.end(); iter++) {
			//		printf("%d (%d), ", *iter, slot[*iter]);
			//	}
			//	printf("\n");
			//}
#endif
			
			if (par_cand.empty())
				continue;

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// Conditions to adopt a parent as *at least* a ZED:
			// x pot_par's beacon doesn't clash with any other neighbor's
			//   (already satisfied)
			// - pot_par is a ZC or ZR
			// - pot_par has less than Cm children
			// - pot_par's depth is less than Lm, because the max depth is Lm
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -		
			
			// eliminate all parent candidates that do NOT satisfy the above criteria
			for (iter = par_cand.begin(); iter != par_cand.end();) {
				if (devices[*iter].role != ZC_ZR
					|| NUM_CHILDREN(*iter) >= Cm
					|| devices[*iter].depth >= Lm)
				{
					iter = par_cand.erase(iter);
				} else {
					iter++;
				}
			}

			if (par_cand.empty())
				continue;

#ifdef PAR_POL_DEPTH
			int test_slot;

			// rank parents using insertion sort
			for (i = 0; i < (int)par_cand.size(); i++) {
				j = i;
				while (j > 0 &&	devices[par_cand[j-1]].depth > devices[par_cand[j]].depth) {
					int tmp = par_cand[j];
					par_cand[j] = par_cand[j-1];
					par_cand[j-1] = tmp;
					j--;
				}
			}

			// - - - - - - - - - - - - - - - - - - - 
			// Conditions to become a ZR:
			// - Parent has less than Rm ZRs
			// - Parent's depth is less than Lm - 1
			// - Can get a free slot
			// - - - - - - - - - - - - - - - - - - -
			for (i = 0; i < (int)par_cand.size(); i++)
			{
				if ((int)devices[par_cand[i]].ZR_children.size() < Rm
					&& devices[par_cand[i]].depth < Lm - 1
					&& (test_slot = pick_slot_yen(par_cand[i], node)) >= 0)
				{
					devices[node].parent_id = par_cand[i];
					devices[node].depth = devices[par_cand[i]].depth + 1;
					
					slot[node] = test_slot;
					who_use_slot[slot[node]].insert(node);
					devices[node].role = ZC_ZR;
					devices[par_cand[i]].ZR_children.insert(node);
					
					new_ZR_found = true;	// this triggers the next round
					break;
				} 
			}
			if (!new_ZR_found) {
				devices[node].parent_id = par_cand[0];
				devices[node].depth = devices[par_cand[0]].depth + 1;
				
				ZED_slot[node] = slot[par_cand[0]];
				devices[node].role = ZED;
				devices[par_cand[0]].ZED_children.insert(node);
			}
#endif

#if defined(PAR_POL_SLOT) || defined(PAR_POL_DEPTH_SLOT) || defined(PAR_POL_SLOT_DEPTH)
			vector<int> slot_cand;	// best available slots corresponding to parent candidates
			
			// find the best available slots corresponding to parant candidates
			slot_cand.clear();
			for (iter = par_cand.begin(); iter != par_cand.end(); iter++) {
				// if picked slot < 0, node would have to become a ZED
				slot_cand.push_back(pick_slot_yen(*iter, node));
			}
			assert(slot_cand.size() == par_cand.size());

			// rank parents using insertion sort
			for (i = 0; i < (int)par_cand.size(); i++) {
				j = i;
				while (j > 0 &&
#	ifdef PAR_POL_SLOT
						slot_cand[j-1] < slot_cand[j]) {
#	elif defined(PAR_POL_DEPTH_SLOT)
						(devices[par_cand[j-1]].depth > devices[par_cand[j]].depth
						 || (devices[par_cand[j-1]].depth == devices[par_cand[j]].depth && slot_cand[j-1] < slot_cand[j]))) {
#	elif defined(PAR_POL_SLOT_DEPTH)
						(slot_cand[j-1] < slot_cand[j]
						 || (slot_cand[j-1] == slot_cand[j] && devices[par_cand[j-1]].depth > devices[par_cand[j]].depth))) {
#	endif
					int tmp = par_cand[j];
					par_cand[j] = par_cand[j-1];
					par_cand[j-1] = tmp;

					tmp = slot_cand[j];
					slot_cand[j] = slot_cand[j-1];
					slot_cand[j-1] = tmp;

					j--;
				}
			}
			
			// - - - - - - - - - - - - - - - - - - - 
			// Conditions to become a ZR:
			// - Parent has less than Rm ZRs
			// - Parent's depth is less than Lm - 1
			// - Can get a free slot
			// - - - - - - - - - - - - - - - - - - -
			for (i = 0; i < (int)par_cand.size(); i++)
			{
				if ((int)devices[par_cand[i]].ZR_children.size() < Rm
					&& devices[par_cand[i]].depth < Lm - 1
					&& slot_cand[i] >= 0)
				{
					devices[node].parent_id = par_cand[i];
					devices[node].depth = devices[par_cand[i]].depth + 1;
					
					slot[node] = slot_cand[i];
					who_use_slot[slot[node]].insert(node);
					devices[node].role = ZC_ZR;
					devices[par_cand[i]].ZR_children.insert(node);
					
					new_ZR_found = true;	// this triggers the next round
					break;
				} 
			}
			if (!new_ZR_found) {
				devices[node].parent_id = par_cand[0];
				devices[node].depth = devices[par_cand[0]].depth + 1;
				
				ZED_slot[node] = slot[par_cand[0]];
				devices[node].role = ZED;
				devices[par_cand[0]].ZED_children.insert(node);
			}
#endif

#ifdef _DEBUG
			printf("%3d ---> %3d: depth = %d, role = %d",
				node, devices[node].parent_id, devices[node].depth, devices[node].role);
			if (devices[node].role == ZC_ZR)
				printf(", slot = %d\n", slot[node]);
			else
				printf("\n");
#endif
		}
	} while (new_ZR_found);
	
#ifdef _DEBUG
	// init Graphviz
	GVC_t *gvc;
	char fname[256];
	sprintf(fname, "mm_%s.ps", SCHEME_NAME(scheme));
	gvc = gv_start(fname);
	
	// init graph
	Agraph_t *g = agopen("g", AGDIGRAPH);

	// fill in the nodes and edges
	Agnode_t **u = new Agnode_t*[num_FFD];
	for (i = 0; i < num_FFD; i++) {
		u[i] = NULL;
	}
	for (i = 0; i < num_FFD; i++) {
		// node
		if (u[i] == NULL) u[i] = gv_create_node(g, i);

		// node -> parent -> ...
		int node = i;
		int parent = devices[node].parent_id;
		while (parent >= 0) {
			if (u[parent] == NULL)
				u[parent] = gv_create_node(g, parent);
			if (agfindedge(g, u[node], u[parent]) == NULL)
				agedge(g, u[node], u[parent]);
			node = parent;
			parent = devices[node].parent_id;
		}
	}
	
	// ask Graphviz to do it
	gv_run(gvc, g);

	// cleanup
	gv_end(gvc, g);
	delete[] u;
#endif
} //}}}

void new_tree_tseng()
{ //{{{
	set<int>::iterator iter;

	// the first element stores the node A to tx next
	// the second element stores the node B where A has received beacon from,
	// i.e. a potential parent
	vector< pair<int,int> > nodes2txnext;
	vector< pair<int,int> >::iterator pair_iter;
	set<int> *tmp_adjlist;

	int i;
	int node;
	int pot_par;			// potential parent
	int test_slot;
	enum {AS_ZR, AS_ZED, AS_IS} assoc_action;
	
	// alloc storage
	tmp_adjlist = new set<int>[num_FFD];
	for (i = 0; i < num_FFD; i++){
		tmp_adjlist[i] = adjlist[i];
	}

	// the sink broadcasts its beacon
	for (iter = adjlist[0].begin(); iter != adjlist[0].end(); iter++) {
		pair<int,int> receiver_sender(*iter, 0);
		nodes2txnext.push_back(receiver_sender);
	}

	assert(!nodes2txnext.empty());

	// loop through the nodes, starting with a random one
	do {
		//int rand_i = int(double(rand())/RAND_MAX*(nodes2txnext.size()-1));
		//for (pair_iter = nodes2txnext.begin(), i = 0; i < rand_i; i++) {
		//	pair_iter++;
		//}
		pair_iter = nodes2txnext.begin();

		node = pair_iter->first;
		pot_par = pair_iter->second;

		// remove current node from the pipeline now
		// because after we modify nodes2txnext later,
		// iter will no longer be valid
		nodes2txnext.erase(pair_iter);

		// if it's the sink node, or the node is already associated with the sink, 
		// leave it as it is
		if (node == 0 || devices[node].parent_id == 0)
			continue;
		
		// Conditions to adopt a parent as at least a ZED:
		// - pot_par is a ZC or ZR
		// - pot_par has less than Cm children
		// - pot_par's depth is less than Lm, because the max depth is Lm		
		//
		// Conditions to become a ZR:
		// - Parent has less than Rm ZRs
		// - Parent's depth is less than Lm - 1
		// - Can get a free slot	
		//
		if (devices[pot_par].role == ZC_ZR
			&& NUM_CHILDREN(pot_par) < Cm
			&& devices[pot_par].depth < Lm)
		{
			if ((int)devices[pot_par].ZR_children.size() < Rm
				&& devices[pot_par].depth < Lm - 1
				&& (test_slot = pick_slot_tseng(pot_par, node)) >= 0)
			{
				assoc_action = AS_ZR;
			} else {
				assoc_action = AS_ZED;
			}
		} else {
			assoc_action = AS_IS;
		}
		
		// Conditions to change parent:
		// - pot_par has a smaller depth than the current parent
		//
		if (assoc_action != AS_IS)
		{
			// if already associated, decide whether to change association
			// note: we have already handled the case of parent_id == 0 earlier on
			if (devices[node].parent_id > 0)
			{
				if (devices[pot_par].depth + 1 < devices[node].depth)
				{
					// disassociate with current parent
					if (devices[node].role == ZC_ZR) {
						devices[ devices[node].parent_id ].ZR_children.erase(
							 devices[ devices[node].parent_id ].ZR_children.find(node));
					} else {
						devices[ devices[node].parent_id ].ZED_children.erase(
							 devices[ devices[node].parent_id ].ZED_children.find(node));
					}
				} else {
					// condition not satisfied, so not changing current association
					assoc_action = AS_IS;
				}
			}
		}

		if (assoc_action != AS_IS) {
			// associate with new parent
			devices[node].depth = devices[pot_par].depth + 1;
			devices[node].parent_id = pot_par;
			if (assoc_action == AS_ZR) {
				slot[node] = test_slot;
				who_use_slot[slot[node]].insert(node);
				devices[node].role = ZC_ZR;
				devices[pot_par].ZR_children.insert(node);
			} else {
				devices[node].role = ZED;
				devices[pot_par].ZED_children.insert(node);
			}

#ifdef _DEBUG
			printf("%3d ---> %3d: depth = %d, role = %d",
				 node, pot_par, devices[node].depth, devices[node].role);
			if (devices[node].role == ZC_ZR)
				printf(", slot = %d\n", slot[node]);
			else
				printf("\n");
#endif

			// node broadcasts beacon
			if (devices[node].role == ZC_ZR) {
				iter = tmp_adjlist[node].begin();
				while (iter != tmp_adjlist[node].end()) {
					pair<int,int> receiver_sender(*iter, node);
					nodes2txnext.push_back(receiver_sender);
					iter = tmp_adjlist[node].erase(iter);
				}
			}

			// node broadcasts HELLO implicitly; in pick_slot_tseng(),
			// a node knows the slot number of its 2r-neighbors
		} else {
#ifdef _DEBUG
			printf("%3d -X-> %3d because ", node, pot_par);
			if (devices[pot_par].role != ZC_ZR)
				printf("%3d is not a ZC/ZR; ", pot_par);
			if (NUM_CHILDREN(pot_par) >= Cm)
				printf("%3d has enough children; ", pot_par);
			if (devices[pot_par].depth >= Lm)
				printf("%3d is deep enough; ", pot_par);
			if (devices[node].parent_id > 0 && (devices[pot_par].depth + 1 >= devices[node].depth))
				printf("%3d stays with %3d", node, devices[node].parent_id);
			printf("\n");
#endif
		}
	} while(!nodes2txnext.empty());

	// dealloc storage
	delete[] tmp_adjlist;

#ifdef _DEBUG
	// sanity check (superseded by check_collision(), but I like the code here, so I'm keeping)
	/*
	map< int, set<int> >::const_iterator map_iter;
	set<int>::const_reverse_iterator riter;
	for (map_iter = who_use_slot.begin(); map_iter != who_use_slot.end(); map_iter++) {
		// get the nodes that share the slot
		set<int> sharers = map_iter->second;

		// check if there's any pair of nodes are 2r-connected
		for (iter = sharers.begin(); iter != sharers.end(); iter++) {
			for (riter = sharers.rbegin(); *riter != *iter; riter++) {
				if (CONNECTED2R(*iter, *riter)) {
					printf("Sanity check failed: %d and %d share slot %d\n", *iter, *riter, map_iter->first);
				}
			}
		}
	}
	*/

	// init Graphviz
	GVC_t *gvc = gv_start("mm_tseng.ps");
	
	// init graph
	Agraph_t *g = agopen("g", AGDIGRAPH);

	// fill in the nodes and edges
	Agnode_t **u = new Agnode_t*[num_FFD];
	for (int i = 0; i < num_FFD; i++) {
		u[i] = NULL;
	}
	for (int i = 0; i < num_FFD; i++) {
		// node
		if (u[i] == NULL) u[i] = gv_create_node(g, i);

		// node -> parent -> ...
		int node = i;
		int parent = devices[node].parent_id;
		while (parent >= 0) {
			if (u[parent] == NULL) u[parent] = gv_create_node(g, parent);
			if (agfindedge(g, u[node], u[parent]) == NULL)
				agedge(g, u[node], u[parent]);
			node = parent;
			parent = devices[node].parent_id;
		}
	}
	
	// ask Graphviz to do it
	gv_run(gvc, g);

	// cleanup
	gv_end(gvc, g);
	delete[] u;
#endif	
} //}}}

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

	min = EUC_DIST(devices[i].pos_x,              devices[i].pos_y,               devices[j].pos_x, devices[j].pos_y);
	tmp = EUC_DIST(devices[i].pos_x + area_width, devices[i].pos_y,               devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x - area_width, devices[i].pos_y,               devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x,              devices[i].pos_y + area_height, devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x,              devices[i].pos_y - area_height, devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x + area_width, devices[i].pos_y + area_height, devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x + area_width, devices[i].pos_y - area_height, devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x - area_width, devices[i].pos_y + area_height, devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	tmp = EUC_DIST(devices[i].pos_x - area_width, devices[i].pos_y - area_height, devices[j].pos_x, devices[j].pos_y);
	if (tmp < min) min = tmp;
	uvdist[p] = min;
	return min;
#else
	tmp = EUC_DIST(devices[i].pos_x, devices[i].pos_y, devices[j].pos_x, devices[j].pos_y);
	uvdist[p] = tmp;
	return tmp;
#endif
} //}}}

void init_data(double area_width, double area_height, double r)
{ //{{{
	int i, j, sum_deg = 0;

	devices[0].pos_x = area_width / 2;
	devices[0].pos_y = area_height / 2;
	devices[0].depth = 0;
	devices[0].parent_id = -1;
	devices[0].role = ZC_ZR;
	slot[0] = 0;
	reassoc_count[0] = 0;
 
	if (!degFixed) {
		// node degree not fixed
		for (i = 1; i < num_FFD; i++) {
#ifdef _MSC_VER
			unsigned int nonce;
			rand_s(&nonce);
			devices[i].pos_x = (double)nonce/UINT_MAX * area_width;
			rand_s(&nonce);
			devices[i].pos_y = (double)nonce/UINT_MAX * area_height;
#else
			devices[i].pos_x = (double)rand()/RAND_MAX * area_width;
			devices[i].pos_y = (double)rand()/RAND_MAX * area_height;		
#endif		
			devices[i].depth = Lm + 1;
			devices[i].parent_id = -1;
			devices[i].role = UNKNOWN;
			slot[i] = -1;	// NULL slot
			for (j = 0; j < i; j++) {
				if (distance(j, i, area_width, area_height) < r)
				{				
					adjlist[i].insert(j);
					adjlist[j].insert(i);
					sum_deg += 2;
				}			
				if (distance(j, i, area_width, area_height) < 2*r)
				{
					adjlist2r[i].insert(j);
					adjlist2r[j].insert(i);
				}
			}
			reassoc_count[i] = 0;
		}
		degree = (int)(sum_deg/(double)num_FFD);
	} else {
		// node degree fixed, find num_FFD
		i = 1;
		do {
#ifdef _MSC_VER
			unsigned int nonce;
			rand_s(&nonce);
			devices[i].pos_x = (double)nonce/UINT_MAX * area_width;
			rand_s(&nonce);
			devices[i].pos_y = (double)nonce/UINT_MAX * area_height;
#else
			devices[i].pos_x = (double)rand()/RAND_MAX * area_width;
			devices[i].pos_y = (double)rand()/RAND_MAX * area_height;		
#endif		
			devices[i].depth = Lm + 1;
			devices[i].parent_id = -1;
			devices[i].role = UNKNOWN;
			slot[i] = -1;	// NULL slot
			for (j = 0; j < i; j++) {
				if (distance(j, i, area_width, area_height) < r)
				{				
					adjlist[i].insert(j);
					adjlist[j].insert(i);
					sum_deg += 2;
				}			
				if (distance(j, i, area_width, area_height) < 2*r)
				{
					adjlist2r[i].insert(j);
					adjlist2r[j].insert(i);
				}
			}
			reassoc_count[i] = 0;
			i++;
		} while (sum_deg/(double)i < degree);
		num_FFD = i;
	}

	// initialize probabilities
	prob_link = M_PI * radio_range * radio_range / (area_width * area_height);
	P_V = (M_PI + sqrt(27.)/4) * prob_link;
#if 0
	assert(sizeof(phi)/sizeof(double) >= degree+1);
	P_H = GAMMA * prob_link;	
	P_U = (GAMMA + (sqrt(3.)/4/M_PI - GAMMA)/phi[degree]) * prob_link;
#else
	assert(sizeof(phi)/sizeof(double) >= degree+1 && sizeof(sigma)/sizeof(double) >= degree+1);
	P_U = 8*(1-sigma[degree]*sigma[degree])*acos(sigma[degree]*0.5);
	P_U+= sigma[degree]*(2+sigma[degree]*sigma[degree])*sqrt(4-sigma[degree]*sigma[degree]);
	P_U*= prob_link/(4*M_PI*(4-sigma[degree]*sigma[degree]));
	P_H = (phi[degree]*P_U-sqrt(3.)*prob_link*0.25/M_PI)/(phi[degree]-1);
#endif
	printf("P_V = %f, P_H = %f, P_U = %f (prob_link = %f, avg_deg = %f)\n",
		 P_V, P_H, P_U, prob_link, sum_deg/(double)num_FFD);
	
#ifdef _DEBUG	
	// init Graphviz
	GVC_t *gvc = gv_start("mm.ps");
	
	// init graph
	Agraph_t *g = agopen("g", AGRAPH);

	// fill in the nodes and edges
	Agnode_t **u = new Agnode_t*[num_FFD];
	for (i = 0; i < num_FFD; i++) {
		// node		
		u[i] = gv_create_node(g, i);

		// edge
		for (set<int>::iterator iter = adjlist[i].begin(); iter != adjlist[i].end(); iter++) {
			if (*iter < i) {
				Agedge_t *e = agedge(g, u[i], u[*iter]);
			}
		}
	}
	
	// ask Graphviz to do it
	gv_run(gvc, g);

	// cleanup
	gv_end(gvc, g);
	delete[] u;
#endif
} //}}}

void reset_data()
{ //{{{	
	for (int i = 0; i < num_FFD; i++) {
		devices[i].ZR_children.clear();
		devices[i].ZED_children.clear();
		adjlist[i].clear();
		adjlist2r[i].clear();
		// don't worry about slot array, because it will be initialized in init_data()
		reassoc_count[i] = 0;
	}
	uvdist.clear();
	ZED_slot.clear();	
	who_use_slot.clear();
} //}}}

void update_reassoc_count_hist(int *&hist, int &max_reassoc_count)
{ //{{{
	int i;
	int old_max_reassoc_count = max_reassoc_count;
	int *tmp_hist;

	// get max of reassoc_count
	for (i = 0; i < num_FFD; i++) {
		//printf("reassoc_count[%d]=%d\n", i, reassoc_count[i]);
		if (reassoc_count[i] > max_reassoc_count) {
			max_reassoc_count = reassoc_count[i];
		}
	}

	// create new histogram
	if (hist == NULL) {
		hist = new int[max_reassoc_count+1];
		for (i = 0; i < max_reassoc_count+1; i++)
			hist[i] = 0;
	} else {
		if (old_max_reassoc_count < max_reassoc_count) {
			tmp_hist = new int[old_max_reassoc_count+1];
			for (i = 0; i < old_max_reassoc_count+1; i++)
				tmp_hist[i] = hist[i];
			hist = new int[max_reassoc_count+1];
			for (i = 0; i < old_max_reassoc_count+1; i++)
				hist[i] = tmp_hist[i];
			for (i = old_max_reassoc_count+1; i < max_reassoc_count+1; i++)
				hist[i] = 0;
			delete tmp_hist;
		}
	}

	// update the histogram
	for (i = 0; i < num_FFD; i++)
		hist[reassoc_count[i]]++;
} //}}}

/**
 * num_assoc: counts number of associated devices
 * num_unassoc1: counts unassociated devices who has ZC/ZR neighbors
 * num_unassoc2: counts unassociated devices who has ZC/ZR neighbors and among these neighbors, 
 * there are neighbors who occupy the same slot (these devices might have ZED neighbors)
 */
void get_assoc_stat(int &num_assoc, int &num_unassoc1, int &num_unassoc2)
{ //{{{
	int i;
	vector<int> neighbs;
	vector<int>::iterator iter, iter2;
	bool collides;
	bool flag2;	// flags node as one of num_unassoc2

	num_assoc = num_unassoc1 = num_unassoc2 = 0;

	for (i = 0; i < num_FFD; i++) {
		if (devices[i].role != UNKNOWN) {
			num_assoc++;
			continue;
		}

		neighbs.clear();
		for (set<int>::const_iterator sit = adjlist[i].begin(); sit != adjlist[i].end(); sit++) {
			if (devices[*sit].role == ZC_ZR)
				neighbs.push_back(*sit);
		}

		if (neighbs.size() > 0)
			num_unassoc1++;

		if (neighbs.size() < 2)	// no collision can occur with less than 2 neighbors
			continue;

		// debug
		//if (i == 7) {
		//	printf("ZR neigbs of 7: ");
		//	for (iter = neighbs.begin(); iter != neighbs.end(); iter++) 
		//		printf("%d, ", *iter);
		//	printf("\n");
		//}

		// remove conflicting neighbors
		flag2 = false;
		for (iter = neighbs.begin(); iter != neighbs.end();) {
			collides = false;
			for (iter2 = iter+1; iter2 != neighbs.end();) {
				if (slot[*iter2] == slot[*iter]) {
					collides = true;
					flag2 = true;
					//if (i == 7) printf("%d clashes with %d\n", *iter, *iter2);	// debug
					iter2 = neighbs.erase(iter2);
				} else {
					iter2++;
				}
			}
			if (collides)
				iter = neighbs.erase(iter);
			else
				iter++;
		}
		
		// inc count
		if (flag2) {
#ifdef _DEBUG
			printf("Unaccommodated: %d; num of non-conflicting neighbs: %d\n", i, neighbs.size());
#endif
			num_unassoc2++;
		}
	}
} //}}}

int main(int argc, char* argv[])
{ //{{{
	// parse command line
	if (argc < 9) {
		fprintf(stderr, "Usage: %s <scheme> <area_len> <radio_range> <num_FFD> <Lm> <Cm> <Rm> <num_slots>\n", argv[0]);
		fprintf(stderr, "Note: if <num_FFD> is prefixed by 'd', then it specifies the expected degree of a node\n");
		exit(1);
	}
	
	char *s = argv[1];
	if (!_stricmp(s, "tseng"))
		scheme = S_TSENG;
	else if (!_stricmp(s, "d1vhu"))
		scheme = S_D1VHU;
	else if (!_stricmp(s, "d1hu"))
		scheme = S_D1HU;
	else if (!_stricmp(s, "d2vhu"))
		scheme = S_D2VHU;
	else if (!_stricmp(s, "d2hu"))
		scheme = S_D2HU;
	else if (!_stricmp(s, "d2u"))
		scheme = S_D2U;
	else if (!_stricmp(s, "cvhu"))
		scheme = S_CVHU;
	else if (!_stricmp(s, "chu"))
		scheme = S_CHU;
	else if (!_stricmp(s, "cu"))
		scheme = S_CU;
	else if (!_stricmp(s, "c"))
		scheme = S_C;	
	else {
		fprintf(stderr, "Error: Invalid scheme.\n");
		exit(1);
	}
	if (!(area_width = area_height = atof(argv[2]))) {
		fprintf(stderr, "Error: Invalid area length.\n");
		exit(1);
	}	
	if (!(radio_range = atof(argv[3]))) {
		fprintf(stderr, "Error: Invalid radio range.\n");
		exit(1);
	}

	if (argv[4][0] == 'd') {	// either specifies degree
		degFixed = true;
		char *s = argv[4];
		while (*s != 0) {
			*s = *(s+1);
			s++;
		}
		if (!(degree = atoi(argv[4]))) {
			fprintf(stderr, "Error: Invalid node degree.\n");
			exit(1);
		}
		if (degree > 50) {
			fprintf(stderr, "Error: Node degree too large.\n");
			exit(1);			
		}
		//fprintf(stderr, "degree=%d\n", degree);
	} else {									// or specifies num_FFD
		degFixed = false;
		if (!(num_FFD = atoi(argv[4]))) {
			fprintf(stderr, "Error: Invalid number of FFD's.\n");
			exit(1);
		}
		//fprintf(stderr, "num_FFD=%d\n", num_FFD);
	}
	
	if (!(Lm = atoi(argv[5]))) {
		fprintf(stderr, "Error: Invalid Lm.\n");
		exit(1);
	}
	if (!(Cm = atoi(argv[6]))) {
		fprintf(stderr, "Error: Invalid Cm.\n");
		exit(1);
	}	
	if (!(Rm = atoi(argv[7]))) {
		fprintf(stderr, "Error: Invalid Rm.\n");
		exit(1);
	}
	if (Rm > Cm) {
		fprintf(stderr, "Error: Rm cannot be larger than Cm.\n");
		exit(1);
	}
	if (!(num_slots = atoi(argv[8]))) {
		fprintf(stderr, "Error: Invalid number of slots.\n");
		exit(1);
	}
	if (num_slots % 2) {
		fprintf(stderr, "Error: Number of slots has to be an even number.\n");
		exit(1);
	}

	// display options enabled
	printf("Options enabled: ");
#ifdef TORUS_CONVENTION
	printf("TORUS_CONVENTION ");
#endif
#ifdef PAR_POL_DEPTH
	printf("PAR_POL_DEPTH ");
#endif
#ifdef PAR_POL_SLOT
	printf("PAR_POL_SLOT ");
#endif
#ifdef PAR_POL_DEPTH_SLOT
	printf("PAR_POL_DEPTH_SLOT ");
#endif
#ifdef PRECISE_PROB
	printf("PRECISE_PROB ");
#endif
	printf("\n");

	// derive number of slots
	//k = 1;
	//for (i = 0; i < Lm; i++)
	//	k *= Rm;
	//k = (k - 1)/(Rm - 1);	// max number of ZRs
	//if (num_slots == 0) {		
	//	num_slots = 2;
	//	while (num_slots < k)
	//		num_slots *= 2;
	//}
	if (degFixed)
		printf("Parameters: l/%f, r/%f, d/%d, Lm/%d, Cm/%d, Rm/%d, num_slots/%d\n",
			 area_width, radio_range, degree, Lm, Cm, Rm, num_slots);
	else
		printf("Parameters: l/%f, r/%f, n/%d, Lm/%d, Cm/%d, Rm/%d, num_slots/%d\n",
			 area_width, radio_range, num_FFD, Lm, Cm, Rm, num_slots);

	// alloc storage; will be initialized in init_data()
	if (degFixed) {
		int est_num_FFD = (int)ceil(1.2*(area_width*area_width)/(M_PI*radio_range*radio_range)*(degree+1)); // actual num_FFD should be less
		devices = new device_t[est_num_FFD];
		adjlist = new set<int>[est_num_FFD];
		adjlist2r = new set<int>[est_num_FFD];
		slot = new int[est_num_FFD];
		reassoc_count = new int[est_num_FFD];
	} else {
		devices = new device_t[num_FFD];	
		adjlist = new set<int>[num_FFD];
		adjlist2r = new set<int>[num_FFD];
		slot = new int[num_FFD];
		reassoc_count = new int[num_FFD];
	}

	// declare local vars
	int i;
	double avg_latency = 0;
	int max_latency = 0;
	int num_assoc = 0;
	int num_unassoc1 = 0;
	int num_unassoc2 = 0;
	vector<double> vec_avg_latency;
	vector<int> vec_max_latency;
	vector<int> vec_num_assoc;
	vector<int> vec_num_FFD;		// num_FFD not same for each round for fixed-density sims
	int *reassoc_count_hist = NULL;
	int max_reassoc_count = 0;
	vector<double> vec_frac_unaccom;

	// loop through runs
	for (i = 0; i < NUM_RUNS; i++) {
		init_data(area_width, area_height, radio_range);
		
		if (scheme == S_TSENG)
			new_tree_tseng();
		else
			new_tree_yen();
		
		get_avg_latency(avg_latency, max_latency);
		vec_avg_latency.push_back(avg_latency);
		vec_max_latency.push_back(max_latency);
		
		get_assoc_stat(num_assoc, num_unassoc1, num_unassoc2);
		vec_num_assoc.push_back(num_assoc);
		if (num_unassoc1 > 0) vec_frac_unaccom.push_back(num_unassoc2/(double)num_unassoc1);

		vec_num_FFD.push_back(num_FFD);
		update_reassoc_count_hist(reassoc_count_hist, max_reassoc_count);
		
#ifdef _DEBUG
		printf("Run %d: avg_latency = %f, max_latency = %d, num_assoc = %d\n",
			 i, avg_latency, max_latency, num_assoc);
#endif

		reset_data();
	}

	// display results
	double avg, stddev, sum;

	get_stat< vector<double> >(vec_avg_latency, avg, stddev);
	printf("* Average average latency = %f (%f)\n", avg, stddev);

	get_stat< vector<int> >(vec_max_latency, avg, stddev);
	printf("* Average maximum latency = %f (%f)\n", avg, stddev);

	get_stat< vector<int> >(vec_num_assoc, avg, stddev);
	printf("* Average number of associated devices = %f (%f)\n", avg, stddev);

	get_stat< vector<int> >(vec_num_FFD, avg, stddev);
	printf("* Average total number of devices = %f (%f)\n", avg, stddev);

	get_stat(reassoc_count_hist, max_reassoc_count, avg, stddev);
	printf("* Average number of reassociations per node = %f (%f)\n", avg, stddev);

	printf("** Normalized hist of reassoc count: ");
	sum = accumulate(vec_num_FFD.begin(), vec_num_FFD.end(), 0);
	for (i = 0; i < max_reassoc_count+1; i++)
		printf("%6.4f, ", reassoc_count_hist[i]/sum);
	printf("\n");

	if (vec_frac_unaccom.size() > 0) {
		get_stat< vector<double> >(vec_frac_unaccom, avg, stddev);
		printf("* Average number of unaccommodated nodes due to collision = %f (%f)\n", avg, stddev);
	} else {
		printf("* Average number of unaccommodated nodes due to collision = N/A\n");
	}

	// dealloc storage
	delete[] devices;	
	delete[] adjlist;
	delete[] adjlist2r;
	delete[] slot;
	delete[] reassoc_count;
   
	return 0;
} //}}}

// vim:foldmethod=marker:sw=2:ts=2:
