/***********************************************************************
filename: cpu/baseline/main.cpp
author: onesuper
email: onesuperclark@gmail.com

a baseline parallel bfs implementation using OpenMP
************************************************************************/


#include <stdio.h>
#include "./../../graph/graph.h"
#include <stdlib.h>
#include "bfs.cpp"

int main(int argc, char** argv)
{
	 if (argc != 3) {
		  printf("please give the path of the graph and the num of threads.\n");
		  return -1;
	 }
	 graph_read_and_alloc(argv[1]);
	 //graph_watch();
	 float time_used = bfs(atoi(argv[2]));

	 gen_level_log();
	 gen_test_log_cpu(time_used, argv[1], "c0", atoi(argv[2]));
	 
	 return 0;
}
