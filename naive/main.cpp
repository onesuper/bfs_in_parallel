/**********************************************************************
filename: naive/main.cpp
author: onesuper
email: onesuperclark@gmail.com

a naive/sequential implementation of breadth-first search.

***********************************************************************/

#include <stdio.h>
#include "./../graph/graph.h"
#include "bfs.cpp"

int main(int argc, char** argv)
{
	 if (argc != 2) {
		  printf("please give the path of the graph.\n");
		  return -1;
	 }
	 graph_read_and_alloc(argv[1]);
	 //graph_watch();
	 float time_used = bfs();

	 gen_level_log();
	 gen_test_log(time_used, argv[1], "naive");
	 graph_free();
	 return 0;
}
