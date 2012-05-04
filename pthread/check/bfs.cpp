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
#include <sched.h>
#include "syncbitops.h"
#include "bitops.h"

//#define DEBUG


unsigned int* current_a;
unsigned int* current_b;
int current_a_size;
int current_b_size;

unsigned long* bitmap;


pthread_barrier_t barr;
pthread_barrier_t barr2;

int list[16] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};


void* thread_func(void*) {
     pthread_t thread_id = pthread_self();
     //printf("%d\n", sched_getcpu());
     int k = 0;

     unsigned int *local_queue = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);
     int local_queue_size = 0;

     while(1) {
          if (k%2 ==0) {
               while (current_a_size > 0) {
                    unsigned int index;
                    int read_pos = __sync_sub_and_fetch(&current_a_size, 1);
                    if (read_pos >= 0) {
                         index = current_a[read_pos];
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest;
                              
                              if (!test_bit(id, bitmap)) {
                                   int its_color = sync_test_and_set_bit(id, bitmap);
                                   if (!its_color) {
                                        cost[id] = cost[index] + 1;
                                        //int write_pos = __sync_fetch_and_add(&current_b_size, 1);
                                        //current_b[write_pos] = id;
                                        local_queue[local_queue_size] = id;
                                        local_queue_size += 1;
                                   }
                              }
                         }
                    } else {
                         __sync_fetch_and_add(&current_a_size, 1);
                    }
               } 
               if (local_queue_size) {
                    int write_pos = __sync_fetch_and_add(&current_b_size, local_queue_size);
                    for (int i=0; i<local_queue_size; i++) {
                         current_b[write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
               }
               pthread_barrier_wait(&barr);
               if (current_b_size == 0)  break;
               pthread_barrier_wait(&barr2);
          } else {
               while (current_b_size > 0) {
                    unsigned int index;
                    int read_pos = __sync_sub_and_fetch(&current_b_size, 1);
                    if (read_pos >= 0) {
                         index = current_b[read_pos];
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest;

                              if (!test_bit(id, bitmap)) {
                                   int its_color = sync_test_and_set_bit(id, bitmap);
                                   if (!its_color) {
                                        cost[id] = cost[index] + 1;
                                        //int write_pos = __sync_fetch_and_add(&current_a_size, 1);
                                        //current_a[write_pos] = id;
                                        local_queue[local_queue_size] = id;
                                        local_queue_size += 1;
                                   }
                              }
                         }
                    } else {
                         __sync_fetch_and_add(&current_b_size, 1);
                    }
               }
               if (local_queue_size) {
                    int write_pos = __sync_fetch_and_add(&current_a_size, local_queue_size);
                    for (int i=0; i<local_queue_size; i++) {
                         current_a[write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
               }
               pthread_barrier_wait(&barr);
               if (current_a_size == 0)  break;
               pthread_barrier_wait(&barr2);
          }
          k++;
     }
}




float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;
     


     current_a = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);
     current_b = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);

     int map_size = num_of_nodes /32 + 1;
     bitmap = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     for (int i=0; i<map_size; i++) bitmap[i] = 0;


     if (pthread_barrier_init(&barr, NULL, num_of_threads))
     {
          printf("could not create a barrier\n");
          return -1;
     }

     if (pthread_barrier_init(&barr2, NULL, num_of_threads))
     {
          printf("could not create a barrier\n");
          return -1;
     }
	 
	 pthread_t tid[50];
     pthread_attr_t attr[50];
     cpu_set_t cpu_info;



     
	 gettimeofday(&start, 0);

     current_b_size = 0;
     current_a_size = 1;


     set_bit(source_node_no, bitmap);
	 current_a[0] = source_node_no;
	 cost[source_node_no] = 0;

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
     free(current_a);
     free(current_b);
     free(bitmap);
	 return time_used;	 
}

