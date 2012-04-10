/**********************************************************************
filename:graph.c
author: onesuper
email: onesuperclark@gmail.com

defining the graph, node, edge structures in this file
 
nodes and edges are two big arrays:
 
each node in nodes array has two indexing infomation: 
to find all its outcoming edges(start and width).

for example:

node(3 , 5) in *node_list* means it has 5 outcomming edges,
 the first of which is the thrid edge in *edge_list*

the variable *dest* of edge points out the node it connecting to,
and *cost* means the cost of the edge.

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

unsigned int num_of_nodes;
unsigned int num_of_edges;
unsigned int source_node_no;
unsigned int num_of_levels;


/* pointing to host */
Node* node_list;
Edge* edge_list;
int* color;
int* cost;
int* counter;
unsigned int* current_set;       /* used in GPU version because CUDA doesn't support heap variable */
int* current_set_size_new;      /* let cpu know the size of current_size */


/* pointing to device  FOR CUDA */
Node* d_node_list;
Edge* d_edge_list;
int* d_color;
int* d_cost;
int* d_counter;
unsigned int* d_current_set_a;    
unsigned int* d_current_set_b;
int* d_current_set_size_new;


/********************************************/
#include "alloc.cpp"
		  
extern void graph_read_and_alloc(char*);
extern void graph_watch(void);
extern void graph_free(void);

#include "util.cpp"

extern void gen_log(void);

