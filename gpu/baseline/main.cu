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
#include "bfs.cpp"


int main(int argc, char** argv)
{
	 if (argc != 2) {
		  printf("please give the path of the graph.\n");
		  return -1;
	 }
	 if (init_cuda()) {
		  return -1;
	 }
	 printf("CUDA has been initialized.\n");

	 graph_read_and_alloc(argv[1]);
	 device_alloc_and_copy();
	 float time_used = bfs();
	 calculate_counter();
	 gen_level_log();
	 gen_test_log(time_used, argv[1], "gpu_baseline");
	 device_free();
	 graph_free();
	 return 0;
}
