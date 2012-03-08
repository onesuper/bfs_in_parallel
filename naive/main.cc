/**********************************************************************
filename: naive/main.cc
author: onesuper
email: onesuperclark@gmail.com

a naive/sequential implementation of breadth-first search.

***********************************************************************/

#include <stdio.h>
#include "naive.h"

int main(int argc, char** argv)
{
	 if (argc != 2) {
		  printf("please give the path of the graph.\n");
		  return -1;
	 }
	 graph_read_and_alloc(argv[1]);
	 //graph_watch();
	 bfs();
	 return 0;
}
