/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

two queues version

***********************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "syncbitops.h"
#include "bitops.h"
#include <queue>
//#define DEBUG

#define SOCKET_NUM_USED 1

typedef struct pair_t {
     unsigned int first;
     unsigned int second;
} PAIR;




unsigned int* current_a[SOCKET_NUM_USED];
unsigned int* current_b[SOCKET_NUM_USED];
PAIR* socket_queue[SOCKET_NUM_USED];
int current_a_size[SOCKET_NUM_USED];
int current_b_size[SOCKET_NUM_USED];
int socket_queue_size[SOCKET_NUM_USED];

unsigned long* bitmap[SOCKET_NUM_USED];


pthread_barrier_t barr;
pthread_barrier_t barr2;



int list[16] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};


unsigned int determine_socket(unsigned int v) {
     return v % SOCKET_NUM_USED;
}


void* thread_func(void*) {
     pthread_t thread_id = pthread_self();
     int socket_no = sched_getcpu();
     int k = 0;
     unsigned int *local_queue = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);
     PAIR* socket_batch[SOCKET_NUM_USED];
     int socket_batch_size[SOCKET_NUM_USED];
     for (int i=0; i<SOCKET_NUM_USED; i++) {
          socket_batch[i] = (PAIR*) malloc(sizeof(PAIR)*num_of_nodes);
          socket_batch_size[i] = 0;
     }
     int local_queue_size = 0;
     


     while(1) {
          if (k%2 ==0) {
               while (current_a_size[socket_no] > 0) {
                    
                    int read_pos = __sync_sub_and_fetch(&current_a_size[socket_no], 1);

                    if (read_pos >= 0) {
                         
                         unsigned int index = current_a[socket_no][read_pos];
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest;
                              int it_belongs_to = determine_socket(id);
                              if (socket_no == it_belongs_to) {
                                   if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                                        int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                                        if (!its_color) {
                                             cost[id] = cost[index] + 1;
                                             local_queue[local_queue_size] = id;
                                             local_queue_size += 1;
                                        }
                                   }
                              } else {
                                   PAIR pair;
                                   pair.first = id;
                                   pair.second = index;
                                   
                                   //int write_pos = __sync_fetch_and_add(&socket_queue_size[it_belongs_to], 1);
                                   //socket_queue[it_belongs_to][write_pos] = pair;
                                   socket_batch[it_belongs_to][socket_batch_size[it_belongs_to]] = pair;
                                   socket_batch_size[it_belongs_to] += 1;

                              }                     
                         }
                    } else {
                          __sync_fetch_and_add(&current_a_size[socket_no], 1);
                    }
               }

               if (local_queue_size) {
                    int write_pos = __sync_fetch_and_add(&current_b_size[socket_no], local_queue_size);
                    for (int i =0; i<local_queue_size; i++) {
                         current_b[socket_no][write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
                   
               }
               for (int i=0; i<SOCKET_NUM_USED; i++) {
                    if (socket_batch_size[i] > 0) {
                         int write_pos = __sync_fetch_and_add(&socket_queue_size[i], socket_batch_size[i]);
                         for (int j=0; j<socket_batch_size[i]; j++) {
                              socket_queue[i][write_pos+j] = socket_batch[i][j];
                         }
                         socket_batch_size[i] = 0;
                    }
               }


               pthread_barrier_wait(&barr);


               while (socket_queue_size[socket_no] > 0) {
                    PAIR pair;
                    int read_pos = __sync_sub_and_fetch(&socket_queue_size[socket_no], 1);
                    if (read_pos >= 0) {
                         pair = socket_queue[socket_no][read_pos];
                         unsigned int index = pair.second;
                         unsigned int id = pair.first;
                         if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                              int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                              if (!its_color) {
                                   cost[id] = cost[index] + 1;
                                   local_queue[local_queue_size] = id;
                                   local_queue_size += 1;
                              }
                         }
                    } else {
                         __sync_fetch_and_add(&socket_queue_size[socket_no], 1);
                    }
               }

               if (local_queue_size) { //batch to next current
                    int write_pos = __sync_fetch_and_add(&current_b_size[socket_no], local_queue_size);
                    for (int i =0; i<local_queue_size; i++) {
                         current_b[socket_no][write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
               }

               pthread_barrier_wait(&barr);
               if (current_b_size[0] == 0  ) break;
               pthread_barrier_wait(&barr2);


          } else {

               while (current_b_size[socket_no] > 0) {
                    
                    int read_pos = __sync_sub_and_fetch(&current_b_size[socket_no], 1);
                    if (read_pos >= 0) {

                         unsigned int index = current_b[socket_no][read_pos];
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest;
                              int it_belongs_to = determine_socket(id);
                              if (socket_no == it_belongs_to) {
                                   if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                                        int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                                        if (!its_color) {
                                             cost[id] = cost[index] + 1;
                                             local_queue[local_queue_size] = id;
                                             local_queue_size += 1;
                                        }
                                   }
                              } else {
                                   PAIR pair;
                                   pair.first = id;
                                   pair.second = index;
                                   //int write_pos = __sync_fetch_and_add(&socket_queue_size[it_belongs_to], 1);
                                   //socket_queue[it_belongs_to][write_pos] = pair;
                                   socket_batch[it_belongs_to][socket_batch_size[it_belongs_to]] = pair;
                                   socket_batch_size[it_belongs_to] += 1;

                              }                     
                         }
                    } else {
                         __sync_fetch_and_add(&current_b_size[socket_no], 1);
                    }
               }

               if (local_queue_size) {
                    int write_pos = __sync_fetch_and_add(&current_a_size[socket_no], local_queue_size);
                    for (int i =0; i<local_queue_size; i++) {
                         current_a[socket_no][write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
                   
               }
               for (int i=0; i<SOCKET_NUM_USED; i++) {
                    if (socket_batch_size[i] > 0) {
                         int write_pos = __sync_fetch_and_add(&socket_queue_size[i], socket_batch_size[i]);
                         for (int j=0; j<socket_batch_size[i]; j++) {
                              socket_queue[i][write_pos+j] = socket_batch[i][j];
                         }
                         socket_batch_size[i] = 0;
                    }
               }


               pthread_barrier_wait(&barr);


               while (socket_queue_size[socket_no] > 0) {
                    PAIR pair;
                    int read_pos = __sync_sub_and_fetch(&socket_queue_size[socket_no], 1);
                    if (read_pos >= 0) {
                         pair = socket_queue[socket_no][read_pos];
                         unsigned int index = pair.second;
                         unsigned int id = pair.first;
                         if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                              int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                              if (!its_color) {
                                   cost[id] = cost[index] + 1;
                                   local_queue[local_queue_size] = id;
                                   local_queue_size += 1;
                              }
                         }
                    } else {
                         __sync_fetch_and_add(&socket_queue_size[socket_no], 1);
                    }
               }

               if (local_queue_size) { //batch to next current
                    int write_pos = __sync_fetch_and_add(&current_a_size[socket_no], local_queue_size);
                    for (int i =0; i<local_queue_size; i++) {
                         current_a[socket_no][write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
               }

               pthread_barrier_wait(&barr);
               if (current_a_size[0] == 0 ) break;
               pthread_barrier_wait(&barr2);

          }
          k++;
     }
}



float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;

  
     


     int map_size = num_of_nodes /(32*SOCKET_NUM_USED) + 1;


     for (int i=0; i<SOCKET_NUM_USED; i++) {
          current_a[i] = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);
          current_b[i] = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);
          socket_queue[i] = (PAIR*) malloc(sizeof(PAIR)*num_of_nodes);
          bitmap[i] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     }



     for (int i=0; i<SOCKET_NUM_USED; i++) 
          for (int j=0; j<map_size; j++)
               bitmap[i][j] = 0;


     for (int i=0; i<SOCKET_NUM_USED; i++) {
          current_a_size[i] = 0;
          current_b_size[i] = 0;
          socket_queue_size[i] = 0;
     }


	 gettimeofday(&start, 0);

     set_bit(source_node_no, bitmap[determine_socket(source_node_no)]);
	 current_a[determine_socket(source_node_no)][0] = source_node_no;
     current_a_size[determine_socket(source_node_no)] = 1;
	 cost[source_node_no] = 0;


     if (pthread_barrier_init(&barr, NULL, num_of_threads))
     {
          printf("could not create barrier1\n");
          return -1;
     }

     if (pthread_barrier_init(&barr2, NULL, num_of_threads))
     {
          printf("could not create barrier2\n");
          return -1;
     }

	 pthread_t tid[50];
     pthread_attr_t attr[50];
     cpu_set_t cpu_info;


     for(int i=0; i<num_of_threads; i++) {
          pthread_attr_init(&attr[i]);
          CPU_ZERO(&cpu_info);
          CPU_SET(list[i], &cpu_info);
          if (0 != pthread_attr_setaffinity_np(&attr[i], sizeof(cpu_set_t), &cpu_info)) {
               printf("set affinity fail\n");
          }
          
     }

	 for (int i=0; i<num_of_threads; i++) {
          int err = pthread_create(&tid[i], &attr[i], thread_func, NULL);
          if (err != 0) {
               printf("can't create thread!");
               break;
          }
     }

     for (int i=0; i<num_of_threads; i++) {
          int err = pthread_join(tid[i], NULL);
          if (err != 0) {
               printf("can't join\n");
          }
     }

	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);

     for (int i=0; i<SOCKET_NUM_USED; i++) {
          free(bitmap[i]);
          free(current_a[i]);
          free(current_b[i]);
          free(socket_queue[i]);
     }

	 return time_used;
	 
}

