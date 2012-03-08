/*********************************************************************
filename: alloc.c 
author: onesuper
email: onesupperclark@gmail.com

some functions used to allocate and free graphs
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>

/*
 * get a name of a graph file and read the file
 * line-by-line to generate the graph
 */ 
void graph_read_and_alloc(char* filename) 
{
	 fp = fopen(filename, "r");
	 if (!fp) {
		  printf("Cannot read the graph file.\n");
		  return;
	 }
	 int i;
	 
	 
	 /* read the number of nodes */
	 fscanf(fp, "%d", &NUM_OF_NODES);
	 printf("there are %d nodes in the graph.\n", NUM_OF_NODES);

	 /* allocate memory of nodes according to the NUM_OF_NODES */
	 NODE_LIST = (Node*) malloc(sizeof(Node) * NUM_OF_NODES);
	 
	 /* read the nodes' infomation from disk to memory */
	 unsigned int start;
	 unsigned int edge_num;
	 for (i=0; i<NUM_OF_NODES; i++) {
		  fscanf(fp, "%u %u", &start, &edge_num);
		  NODE_LIST[i].start = start;
		  NODE_LIST[i].edge_num = edge_num = edge_num;
	 }

	 /* read the source node */
	 fscanf(fp, "%u", &SOURCE_NODE_NO);
	 printf("the source node is %u.\n", SOURCE_NODE_NO);
	 
	 /* read the number of edges */
	 fscanf(fp, "%u", &NUM_OF_EDGES);
	 printf("there are %u edges in the graph.\n", NUM_OF_EDGES);

	 /* allocate the memroy of edges according to NUM_OF_EDGES */
	 EDGE_LIST = (Edge*) malloc(sizeof(Edge) * NUM_OF_EDGES);
	 
	 /* read the edges' information from disk to memory */
	 unsigned int dest;
	 unsigned int cost;
	 for (i=0; i<NUM_OF_EDGES; i++) {
		  fscanf(fp, "%u %u", &dest, &cost);
		  EDGE_LIST[i].dest = dest;
		  EDGE_LIST[i].cost = cost;
	 }
	 

	 fclose(fp);
	 return;
}

void graph_free(void) 
{
	 free(NODE_LIST);
	 free(EDGE_LIST);
	 return;
	 
}

/*
 * have a look at the memory to verify
 */
void graph_watch(void)
{
	 int i;
	 printf("************ node ****************");	 
	 for (i=0; i<NUM_OF_NODES; i++) {
		  printf("%d %d\n", NODE_LIST[i].start, NODE_LIST[i].edge_num);
	 }
	 printf("*********** edge *****************");
	 for (i=0; i<NUM_OF_EDGES; i++) {
		  printf("%d %d\n", EDGE_LIST[i].dest, EDGE_LIST[i].cost);
	 }
	 return;
	 
}
	 
	 
