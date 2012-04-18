/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

two queues version

***********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <sys/time.h>

//#define DEBUG


float bfs(int num_of_threads) 
{
     

	 struct timeval start, end;
	 float time_used;
     

	 // visiting the source node now
	 visited[source_node_no] = true;
	 cost[source_node_no] = 0;
     mask[source_node_no] = true;
     gettimeofday(&start, 0);
     bool stop;
     do {
          stop = false;
          omp_set_num_threads(num_of_threads);

//using a mask to take the place of the queue to avoid lock-operations
#pragma omp parallel for
          for(int index=0; index<num_of_nodes; index++) {
               if (mask[index]) {
                    mask[index] = false;
                    for (int i=node_list[index].start;
                         i<(node_list[index].start+node_list[index].edge_num); i++)
                    {
                         unsigned int id = edge_list[i].dest;
                         if (!visited[id]) {
                              cost[id] = cost[index] + 1;
                              updating_mask[id] = true;
                             
                         }
                    }
               }
          }
          // just like swap(current, next)
          for (int i=0; i<num_of_nodes; i++) {
               if (updating_mask[i]) {
                    mask[i] = true;
                    visited[i] = true;
                    updating_mask[i] = false;
                    // if next is empty, stop the loop
                    stop = true; 
               }
          }

	 } while(stop);

	 

     
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
