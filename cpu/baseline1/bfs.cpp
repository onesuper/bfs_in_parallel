/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

bfs algorithm implemented by OpenMP without any optimization.

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

	 gettimeofday(&start, 0);

	 // visiting the source node now
	 color[source_node_no] = GREY;
	 current.push_back(source_node_no);
	 cost[source_node_no] = 0;

	 // set threads number
	 omp_set_num_threads(num_of_threads);
	 unsigned int index; // index => node u

	 omp_lock_t current_lock;

	 omp_init_lock(&current_lock);
	 
	 
	 
	 
	 while(!current.empty()) {
// proccess each node in the current queue in parallel
#pragma omp parallel for shared(current, color, counter, cost) private(index)
		  for (int i=0; i<current.size(); i++ ) {
			   
			   omp_set_lock(&current_lock);
			   index = current.front();
			   current.pop_front();
			   omp_unset_lock(&current_lock);
			   

               Node cur_node = node_list[index];
			   for (int i = cur_node.start; i < (cur_node.start + cur_node.edge_num); i ++)
               {
					
					unsigned int id = edge_list[i].dest; // id => node v
	
                    int its_color = yuanzi;

					if (its_color == WHITE) {

						 omp_set_lock(&cost_lock);
						 cost[id] = cost[index] + 1; // expand the cost, assuming all the edge cost is 1
						 omp_unset_lock(&cost_lock);

						 
						 omp_set_lock(&current_lock);
						 current.push_back(id);
						 omp_unset_lock(&current_lock);

						 omp_set_lock(&color_lock);
						 color[id] = GREY;
						 omp_unset_lock(&color_lock);

					} // only if its neighbour is has not been visited
					
					
			   }
		  }

	 } 
	 
	 omp_destroy_lock(&current_lock);

	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
