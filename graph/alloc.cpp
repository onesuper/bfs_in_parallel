/*********************************************************************
filename: alloc.cpp
author: onesuper
email: onesupperclark@gmail.com

some functions used to allocate and free graphs
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//#define RANDOM_SOURCE

/*
 * get a name of a graph file and read the file
 * line-by-line to generate the graph
 */ 
void graph_read_and_alloc(char* filename) 
{
	 FILE* fp = fopen(filename, "r");
	 if (!fp) {
		  printf("Cannot open the graph file.\n");
		  return;
	 }

	 
	 fscanf(fp, "%d", &num_of_nodes);

	 printf("************** graph **************\n");
	 printf("there are %d nodes in the graph.\n", num_of_nodes);
	 node_list = (Node*) malloc(sizeof(Node) * num_of_nodes);
	 color = (int*) malloc(sizeof(int) * num_of_nodes);
	 cost = (int*) malloc(sizeof(int) * num_of_nodes);

     // initialize
	 unsigned int start;
	 unsigned int edge_num;
	 for (int i=0; i<num_of_nodes; i++) {
		  fscanf(fp, "%u %u", &start, &edge_num);
		  node_list[i].start = start;
		  node_list[i].edge_num = edge_num;
		  color[i] = WHITE;
		  cost[i] = INF;
	 }

	 fscanf(fp, "%u", &source_node_no);  // basically it's #0 node
// make a tricky here
#ifdef RANDOM_SOURCE
	 srand((unsigned)time(0));
	 source_node_no = rand() % num_of_nodes;
#endif
	 printf("the source node is %u.\n", source_node_no);
	 
	 fscanf(fp, "%u", &num_of_edges);
	 printf("there are %u edges in the graph.\n", num_of_edges);
	 
	 edge_list = (Edge*) malloc(sizeof(Edge) * num_of_edges);
	 
	 unsigned int dest;
	 unsigned int cost;
	 for (int i=0; i<num_of_edges; i++) {
		  fscanf(fp, "%u %u", &dest, &cost);
		  edge_list[i].dest = dest;
		  edge_list[i].cost = cost;
	 }

	 counter = (int*) malloc(sizeof(int) * MAX_LEVEL);
	 for (int i=0; i<MAX_LEVEL; i++) {
		  counter[i] = 0;
	 }

// CPU version use the std:queue instead
#ifdef CUDA_ENABLE
     current_set = (unsigned int*) malloc(sizeof(unsigned int) * num_of_nodes);
     for (int i=0; i<num_of_nodes; i++) {
          current_set[i] = INF;
     }
     current_set_size_new = (int*) malloc(sizeof(int));
     *current_set_size_new = 0;
#endif

	 
	 fclose(fp);
	 return;
}

void graph_free(void) 
{
	 free(node_list);
	 free(edge_list);
	 free(color);
	 free(cost);
#ifdef CUDA_ENABLE
     free(current_set);
#endif
     return;
	 
}

/*
 * have a look at the memory to verify
 */
void graph_watch(void)
{
	 printf("************ node **************\n");	 
	 for (int i=0; i<num_of_nodes; i++) {
		  printf("%d %d\n", node_list[i].start, node_list[i].edge_num);
	 }
	 printf("************ edge **************\n");
	 for (int i=0; i<num_of_edges; i++) {
		  printf("%d %d\n", edge_list[i].dest, edge_list[i].cost);
	 }
	 printf("************ cost **************\n");
	 for (int i=0; i<num_of_nodes; i++) {
		  printf("%d\n", cost[i]);
	 }
	 printf("*********** counter *************\n");
	 for (int i=0; i<MAX_LEVEL; i++) {
		  if (counter[i] != 0)
			   printf("%d\n", counter[i]);
	 }
	 return;
}
	 
	 
