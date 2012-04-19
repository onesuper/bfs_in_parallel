/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

two queues version

***********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <deque>
#include <sys/time.h>

//#define DEBUG





float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;
	 std::deque<unsigned int> current;
     std::deque<unsigned int> next;

	 gettimeofday(&start, 0);

	 // visiting the source node now
	 visited[source_node_no] = true;
	 current.push_back(source_node_no);
	 cost[source_node_no] = 0;

	 // set threads number
	 omp_set_num_threads(num_of_threads);
	 
	 while(!current.empty()) {

          int parallel_num = current.size();

// proccess each node in the current queue in parallel
#pragma omp parallel for shared(current, next, color, cost)
		  for (int i=0; i<parallel_num; i++) {

               unsigned int index; // index => node u			   

               // LockedDequeue current queue
#pragma omp critical
               {       
                    index = current.front();
                    current.pop_front();          
			   }
			   

               Node cur_node = node_list[index];
			   for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
               {
					
					unsigned int id = edge_list[i].dest; // id => node v          
                    if (visited[id] == false) {
                         bool its_color = __sync_lock_test_and_set(&visited[id], true);
                         if (its_color == false) {   
                              cost[id] = cost[index] + 1;
#pragma omp critical
                              {    
                                   next.push_back(id);
                              }
                         }
                    } 
			   } // end of for each v
		  } // end of for each u ;barrier here
          current.swap(next);
          next.clear();
	 } //end of while
	 

     
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
