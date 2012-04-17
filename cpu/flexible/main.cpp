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
	 if (argc != 2) {
		  printf("please give the path of the graph.\n");
		  return -1;
	 }
	 graph_read_and_alloc(argv[1]);
	 
	 float time_used = bfs();

    
     
     calculate_counter();
     gen_level_log();
	 gen_test_log(time_used, argv[1], "cpu_flexible");

     graph_free();
	 return 0;
}
