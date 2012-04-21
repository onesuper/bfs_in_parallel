/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

two queues version

***********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <tbb/concurrent_queue.h>
#include <sys/time.h>

//#define DEBUG


float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;
	 tbb::concurrent_bounded_queue<unsigned int> current;

	 gettimeofday(&start, 0);

	 visited[source_node_no] = true;
	 current.push(source_node_no);
	 cost[source_node_no] = 0;
	
	 omp_set_num_threads(num_of_threads);
	 while(!current.empty()) {
          int parallel_num = current.size();
#pragma omp parallel for
		  for (int j=0; j<parallel_num; j++) {
               unsigned int index;      
               current.pop(index);
               Node cur_node = node_list[index];
			   for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
               {
					
					unsigned int id = edge_list[i].dest; // id => node v          
                    if (color[id] == false) {
                         color[id] = true;
                         cost[id] = cost[index] + 1;
                         current.push(id);
                         
                    } 
			   } 
		  } 
	 }
     
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
