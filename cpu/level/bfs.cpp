/**********************************************************************
filename: cpu/level/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

bfs algorithm implemented by OpenMP without any optimization.


the thread number is dynamically set to to the number of nodes
in each level
***********************************************************************/

#include <omp.h>
#include <stdio.h>
#include <deque>
#include <sys/time.h>



float bfs() 
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
	 
	 unsigned int index; // index => node u

	 omp_lock_t current_lock;
	 omp_lock_t color_lock;
	 omp_lock_t cost_lock;

	 omp_init_lock(&current_lock);
	 omp_init_lock(&color_lock);
	 omp_init_lock(&cost_lock);
	 
	 while(!current.empty()) {

		  omp_set_num_threads(current.size());

// proccess each node in the current queue in parallel
#pragma omp parallel for shared(current, color, counter, cost) private(index)
		  for (int i=0; i<current.size(); i++ ) {
			   
			   omp_set_lock(&current_lock);
			   index = current.front();
			   current.pop_front();
			   omp_unset_lock(&current_lock);
#ifdef DEBUG
			   printf("thread %d is on node %d\n", omp_get_thread_num(), index);
#endif			   
			   for (int i = node_list[index].start;
					i < (node_list[index].start + node_list[index].edge_num);
					i ++) {
					
					unsigned int id = edge_list[i].dest; // id => node v
#ifdef DEBUG
					printf("thread %d: look at his neighbour node: %d\n", omp_get_thread_num(), id);
#endif		
					if (color[id] == WHITE) {
#ifdef DEBUG
						 printf("thread %d: node %d is not visited\n", omp_get_thread_num(), id);
#endif			 
						 omp_set_lock(&cost_lock);
						 cost[id] = cost[index] + 1; // expand the cost, assuming all the edge cost is 1
						 omp_unset_lock(&cost_lock);

						 omp_set_lock(&current_lock);
						 current.push_back(id);
						 omp_unset_lock(&current_lock);
#ifdef DEBUG
						 printf("thread %d: %d is put into current queue\n", omp_get_thread_num(), id);
#endif
						 omp_set_lock(&color_lock);
						 color[id] = GREY;
						 omp_unset_lock(&color_lock);
#ifdef DEBUG
						 printf("thread %d: change %d 's color\n", omp_get_thread_num() ,id);
#endif
					} // only if its neighbour is has not been visited
					
					
			   }

			   omp_set_lock(&color_lock);
			   color[index] = BLACK;
			   omp_unset_lock(&color_lock);
#ifdef DEBUG
			   printf("thread %d: all %d 's neighbours has been checked ,now visit it\n", omp_get_thread_num(), index);
#endif
		  } // parallel block ends

	 } // end of while
	 
	 omp_destroy_lock(&current_lock);
	 omp_destroy_lock(&color_lock);
	 omp_destroy_lock(&cost_lock);
	 
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
