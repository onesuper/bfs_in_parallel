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
     

#pragma omp parallel
     {

          int k = 0;
          unsigned int index;
          bool stop = false;
          do {
               if (k%2 == 0) {
                    
                    while (!current_a.empty()) {
                         index = -1; 
                         current_a.try_pop(index); 
                         if (index != -1) {
                              Node cur_node = node_list[index];  //printf("%d pop out %d\n", omp_get_thread_num(), index);
                              for (int i=cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                              {
					
                                   unsigned int id = edge_list[i].dest; 
                                   bool its_color;
                                   if (visited[id] == false) {
                                        its_color = __sync_lock_test_and_set(&visited[id], true);
                                        if (its_color == false) {
                                             cost[id] = cost[index] + 1;
                                             current_b.push(id);  // printf("%d push %d\n", omp_get_thread_num(), id);
                                        }
                                   }
                              } 
                         }
                    }
               } else {
                    
                    
                    while (!current_b.empty()) {
                         index = -1; 
                         current_b.try_pop(index);  
                         if (index != -1) {
                              Node cur_node = node_list[index];// printf("%d pop out %d\n", omp_get_thread_num(), index);
                              for (int i=cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                              {
					
                                   unsigned int id = edge_list[i].dest; 
                                   bool its_color;
                                   if (visited[id] == false) {
                                        its_color = __sync_lock_test_and_set(&visited[id], true);
                                        if (its_color == false) {
                                             cost[id] = cost[index] + 1;
                                             current_a.push(id); //printf("%d push %d\n", omp_get_thread_num(), id);
                                        }
                                   }
                              } 
                         }
                    }
               }
               #pragma omp barrier
               
               k++; 
          } while(!stop);

     }

     
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
