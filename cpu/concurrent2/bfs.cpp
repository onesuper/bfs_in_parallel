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
	 tbb::concurrent_bounded_queue<unsigned int> current_a;
     tbb::concurrent_bounded_queue<unsigned int> current_b;

	 gettimeofday(&start, 0);

	 // visiting the source node now
	 visited[source_node_no] = true;
	 current_a.push(source_node_no);
	 cost[source_node_no] = 0;

	 // set threads number
	 omp_set_num_threads(num_of_threads);
	 int k = 0;
     bool stop = false;
     
     do {
          if (k%2 == 0) {
               int parallel_num = current_a.size();
// proccess each node in the current queue in parallel
#pragma omp parallel for shared(current_a, current_b, color, cost)
               for (int i=0; i<parallel_num; i++) {
                    unsigned int index; // index => node u
                    current_a.pop(index);
                    Node cur_node = node_list[index];
                    for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                    {
					
                         unsigned int id = edge_list[i].dest; // id => node v          
                         if (visited[id] == false) {
                              visited[id] = true;
                              cost[id] = cost[index] + 1;
                              current_b.push(id);
                         } 
                    } 
               } 
               if (current_b.empty()) stop =true; //there's no node in next queue

          } else {

               int parallel_num = current_b.size();
// proccess each node in the current queue in parallel
#pragma omp parallel for shared(current_a, current_b, color, cost)
               for (int i=0; i<parallel_num; i++) {
                    unsigned int index; // index => node u
                    current_b.pop(index);
                    Node cur_node = node_list[index];
                    for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                    {
					
                         unsigned int id = edge_list[i].dest; // id => node v          
                         if (visited[id] == false) {
                              visited[id] = true;
                              cost[id] = cost[index] + 1;
                              current_a.push(id);
                         } 
                    } 
               } 
               if (current_a.empty()) stop = true; //there's no node in next queue
          }
          k++;
	 } while(!stop);
	 

     
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
