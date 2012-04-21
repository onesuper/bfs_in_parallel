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
#include "syncbitops.h"
#include "bitops.h"
#include <sched.h>

//#define DEBUG

/*
void set_bit(unsigned int num, unsigned long* bitmap) {
     bitmap[num/32] |= ( 0x80000000 >> num%32);
}

int test_bit(unsigned int num, unsigned long* bitmap) {
     return bitmap[num/32] & (0x80000000 >> num%32);
}
*/

unsigned int determine_socket(unsigned int v) {
     return v % 4;
}

float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;
	 tbb::concurrent_bounded_queue<unsigned int> current_a[4];
     tbb::concurrent_bounded_queue<unsigned int> current_b[4];
     tbb::concurrent_bounded_queue< std::pair<unsigned int, unsigned int> > socket_queue[4];



     int map_size = num_of_nodes/ (32*4) + 1;

     unsigned long* bitmap[4];

     bitmap[0] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     bitmap[1] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     bitmap[2] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     bitmap[3] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);

     for (int i=0; i<4; i++)
          for (int j=0; j<map_size; j++)
               bitmap[i][j] = 0;

	 gettimeofday(&start, 0);

	 // visiting the source node now
     set_bit(source_node_no, bitmap);
	 current_a[determine_socket(source_node)].push(source_node_no);
	 cost[source_node_no] = 0;

	 // set threads number
	 omp_set_num_threads(num_of_threads);
	 int k = 0;
     bool stop = false;
     omp_set_nested(true);


     do {
          if (k%2 == 0) {

               int parallel_num = current_a[0].size() +current_a[1].size()
                    + current_a[2].size() + current_a[3].size(); 
#pragma omp parallel for
               for (int j=0; j<parallel_num; j++) {

                    int socket_no = sched_getcpu();
                    unsigned int index; 
                    current_a[socket_no].pop(index);
                    Node cur_node = node_list[index];

                    for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                    {
                         unsigned int id = edge_list[i].dest;
                         id_belongs_to = determine_socket(id);
                         if (socket_no == id_belongs_to) {
                              if (!test_bit(id/4, bitmap[socket_no])) {
                                   int its_color = sync_test_and_set_bit(id/4, bitmap[socket]);
                                   if (!its_color) {
                                        cost[id] = cost[index] + 1;
                                        current_b[socket_no].push(id);
                                   }
                              }
                         } else {
                              socket_queue[it_belongs_to].push(std::pair(id, index));
                         }
                    } 
               }
               //
               // barrier here!!!
               //
               parallel_num = socket_queue[0].size() + socket_queue[1].size()
                    + socket_queue[2].size() + socket_queue[3].size();

#pragma omp parallel for
               for (int j=0; j<parallel_num; j++) {

                    int socket_no = sched_get_cpu();
                    std::pair a_par;
                    socket_queue[socket_no].pop(a_pair);
                    unsigned int index = a_pair.second;
                    unsigned int id = a_pair.first;
                    if(!test_bit(id/4, bitmap[socket_no])) {
                         int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                         if (!its_color) {
                              cost[id] = cost[index] + 1;
                              current_b[socket_no].push(id);
                         }
                    }
               }
               if (current_b[socket_no].empty()) stop =true; 
               //
               // barrier here!!! 
               //
          } else {

               int parallel_num = current_b[0].size() + current_b[1].size() +
                    current_b[2].size() + current_b[3].size();

#pragma omp parallel for
               for (int j=0; j<parallel_num; j++) {

                    int socket_no = sched_getcpu();
                    unsigned int index; 
                    current_b[socket_no].pop(index);
                    Node cur_node = node_list[index];

                    for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                    {
                         unsigned int id = edge_list[i].dest;
                         id_belongs_to = determine_socket(id);
                         if (socket_no == id_belongs_to) {
                              if (!test_bit(id/4, bitmap[socket_no])) {
                                   int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                                   if (!its_color) {
                                        cost[id] = cost[index] + 1;
                                        current_a[socket_no].push(id);
                                   }
                              }
                         } else {
                              socket_queue[it_belongs_to].push(std::pair(id, index));
                         }
                    } 
               } 
               //
               // barrier here!!!
               //
               parallel_num = socket_queue[0].size() + socket_queue[1].size()
                    + socket_queue[2].size() + socket_queue[3].size();

#pragma omp parallel for
               for (int j=0; j<parallel_num; j++) {

                    int socket_no = sched_get_cpu();
                    std::pair a_par;
                    socket_queue[socket_no].pop(a_pair);
                    unsigned int index = a_pair.second;
                    unsigned int id = a_pair.first;
                    if(!test_bit(id/4, bitmap[socket_no])) {
                         int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                         if (!its_color) {
                              cost[id] = cost[index] + 1;
                              current_a[socket_no].push(id);
                         }
                    }
               }
               if (current_a[socket_no].empty()) stop =true;
               //
               // barrier here!!
               // 
          }
          k++;
     } while(!stop);

	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);

     free(bitmap);
	 return time_used;
	 
}
