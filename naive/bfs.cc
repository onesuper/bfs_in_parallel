/**********************************************************************
filename: naive/bfs.cc
author: onesuper
email: onesuperclark@gmail.com

the single-core implemenation of bfs algorithm

***********************************************************************/

#include <stdio.h>
#include <deque>
#include <sys/time.h>

void bfs(void) 
{
	 printf("bfs starts.\n");
	 std::deque<unsigned int> current;

	 // visiting the source node now
	 color[source_node_no] = GREY;
	 current.push_back(source_node_no);
	 
	 unsigned int index;
	 while(!current.empty()) {
		  index = current.front();
		  current.pop_front();
		  
		  // put all its neighbours in the current queue
		  for (int i = node_list[index].start;
			   i < (node_list[index].start + node_list[index].edge_num);
			   i ++) {
			   unsigned int id = edge_list[i].dest;
			   unsigned int weight = edge_list[i].cost;
			   
			   if (color[id] == WHITE) {
					cost[id] = cost[index] + weight; // expanding the cost
					counter[cost[id]] ++;
					current.push_back(id);
					color[id] = GREY;

			   } // only if its neighbour is has not been visited
		  }
		  color[index] = BLACK;
		  
	 }
	 
	 
	 
	 printf("bfs ends.\n");
	 return;
	 
}
