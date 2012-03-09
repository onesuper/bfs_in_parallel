/**********************************************************************
filename:graph.c
author: onesuper
email: onesuperclark@gmail.com

defining the graph's, node's, edge's structures in this file
 
nodes and edges are two big arrays:
 
each node in nodes array has two indexing infomation to
find all its outcoming edges(start and width).

the dest variable of each edge in edges array points out
the node it connecting to.
************************************************************************/

#define WHITE	0				/* not visited */
#define GREY	1				/* visiting */
#define BLACK	2				/* visited */
#define INF		2147483647		/* inifinity is  2^31 - 1  */
#define MAX_LEVEL		20000	

typedef struct node_t 
{
	 unsigned int start;		/* starting index of edges */
	 unsigned int edge_num;
} Node;

typedef struct edge_t
{
	 unsigned int dest;			/* index of nodes */
	 unsigned int cost;
 } Edge;

/********************************************
global variables 
*********************************************/

Node* node_list;
Edge* edge_list;
int* color;
int* cost;
int* counter;
unsigned int num_of_nodes;
unsigned int num_of_edges;
unsigned int source_node_no;
unsigned int num_of_levels;

/********************************************/
#include "alloc.cpp"
		  
extern void graph_read_and_alloc(char*);
extern void graph_watch(void);
extern void graph_free(void);

#include "util.cpp"

extern void gen_log(void);

	 
