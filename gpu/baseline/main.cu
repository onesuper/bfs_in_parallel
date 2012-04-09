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
#include "bfs.cpp"

#define MAX_THREADS_PER_BLOCK 512


#define CUDA_ENABLE

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

	 graph_read_and_alloc(argv[1]);     //CPU alloc
	 device_alloc_and_copy();           //GPU alloc
	 float time_used = bfs();
	 calculate_counter();
	 gen_level_log();
	 gen_test_log(time_used, argv[1], "gpu_baseline");
	 device_free();             //CPU free
	 graph_free();              //GPU free
	 return 0;
}
