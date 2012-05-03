/***********************************************************************
filename: gpu/baseline/main.cpp
author: onesuper
email: onesuperclark@gmail.com

a baseline parallel bfs implementation using CUDA
************************************************************************/


#include <stdio.h>
#include "./../../graph/graph.h"
#include "./../cuda.cu"
#include <stdlib.h>
#include <math.h>
#include "bfs.cu"

unsigned int* current_set;      
int* current_set_size_new;      


Node* d_node_list;
Edge* d_edge_list;
int* d_color;
int* d_cost;
int* d_counter;
unsigned int* d_current_set_a;    
unsigned int* d_current_set_b;
int* d_current_set_size_new;



int main(int argc, char** argv)
{
	 if (argc != 3) {
		  printf("please give the path of the graph and the block_num.\n");
		  return -1;
	 }
	 if (!init_cuda()) {
		  return -1;
	 }
	 printf("CUDA has been initialized.\n");

	 graph_read_and_alloc(argv[1]);     //CPU alloc


     
     // more alloc
     current_set = (unsigned int*) malloc(sizeof(unsigned int) * num_of_nodes);
     for (int i=0; i<num_of_nodes; i++) {
          current_set[i] = INF;
     }
     current_set_size_new = (int*) malloc(sizeof(int));
     *current_set_size_new = 0;

	 device_alloc_and_copy();           //GPU alloc
	 float time_used = bfs(atoi(argv[2]));
	 calculate_counter();
	 gen_level_log();
	 gen_test_log_cpu(time_used, argv[1], "gpu_baseline", atoi(argv[2]));
	 device_free();             //CPU free
	 graph_free();              //GPU free
     //more free
     free(current_set);
     free(current_set_size_new);
	 return 0;
}
