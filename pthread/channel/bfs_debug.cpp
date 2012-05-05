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


tbb::concurrent_queue<unsigned int> current_a[SOCKET_NUM_USED];
tbb::concurrent_queue<unsigned int> current_b[SOCKET_NUM_USED];
tbb::concurrent_queue<PAIR> socket_queue[SOCKET_NUM_USED];



unsigned int* current_a[SOCKET_NUM_USED];
unsigned int* current_b[SOCKET_NUM_USED];
PAIR socket_queue[SOCKET_NUM_USED];
int current_a_size[SOCKET_NUM_USED];
int current_b_size[SOCKET_NUM_USED];
int socket_queue[SOCKET_NUM_USED];

unsigned long* bitmap[SOCKET_NUM_USED];


pthread_barrier_t barr;
pthread_barrier_t barr2;

//int list[16] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};

int list[16] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};


unsigned int determine_socket(unsigned int v) {
     return v % SOCKET_NUM_USED;
}


void* thread_func(void*) {
     pthread_t thread_id = pthread_self();
     int socket_no = sched_getcpu();
     int k = 0;
     unsigned int *local_queue = (unsigned int*) malloc(sizeof(unsigned int)*num_of_nodes);
     int local_queue_size = 0;
     
#ifdef DEBUG
     printf("I'm in socket %d\n", socket_no);
#endif

     while(1) {
          if (k%2 ==0) {
               while (current_a_size[socket_no] > 0) {
                    unsigned int index;
                    int read_pos = __sync_sub_and_fetch(&current_a_size[socket_no], 1);
                    if (read_pos >= 0) {


#ifdef DEBUG
                         printf("%lu: %d is out\n", thread_id, index);
#endif
                         index = current_a[socket_no][read_pos];
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest;


#ifdef DEBUG
                              printf("%lu: forward looking at %d\n", thread_id, id);
#endif

                              int it_belongs_to = determine_socket(id);
                              if (socket_no == it_belongs_to) {
                                   if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                                        int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                                        if (!its_color) {
                                             cost[id] = cost[index] + 1;

#ifdef DEBUG
                                             printf("%lu: forward visiting %d\n", thread_id, id);  
#endif
                                             local_queue[local_queue_size] = id;
                                             local_queue_size += 1;
                                        }
                                   }
                                        
                              } else {
                                   PAIR pair;
                                   pair.first = id;
                                   pair.second = index;
                                   int write_pos = __sync_fetch_and_add(&socket_queue[it_belongs_to], 1);
                                   socket_queue[write_pos] = pair;
#ifdef DEBUG
                                   printf("%lu: forward to %d\n", thread_id, it_belongs_to);
#endif
                              }                     
                         }
                    } else {
                          __sync_fetch_and_add(&current_a_size[socket_no], 1);
                    }
               }

               if (local_queue_size) {
                    int write_pos = __sync_fetch_and_add(&current_b_size, local_queue_size);
                    
                    
                    for (int i =0; i<local_queue_size; i++) {
                         current_b[write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
                   
               }

#ifdef DEBUG               
               printf("%lu:going to wait @lock1 in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr);
#ifdef DEBUG
               printf("%lu:recovering @lock1 in %d\n",thread_id, k);
#endif

               while (socket_queue_size[socket_no] > 0) {
                    PAIR pair;
                    int read_pos = __sync_sub_an_fetch(&socket_queue_size[socket_no], 1);
                    
                    if (read_pos >= 0) {
                         pair = socket_queue[socket_no][read_pos];
                         unsigned int index = pair.second;
                         unsigned int id = pair.first;

#ifdef DEBUG
                         printf("%lu: cleaner looking at %d\n", thread_id, id);
#endif

                         if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                              int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                              if (!its_color) {
                                   cost[id] = cost[index] + 1;
                                   

#ifdef DEBUG
                                   printf("%lu: cleaner visiting %d\n", thread_id, id);  
#endif
                                   local_queue[local_queue_size] = id;
                                   local_queue_size += 1;
                              }
                         }
                    } else {
                          __sync_fetch_and_add(&socket_queue, 1);
                    }
               }

               if (local_queue_size) {
                    int write_pos = __sync_fetch_and_add(&current_b_size, local_queue_size);
                    for (int i =0; i<local_queue_size; i++) {
                         current_b[write_pos+i] = local_queue[i];
                    }
                    local_queue_size = 0;
                   
               }
               
#ifdef DEBUG               
               printf("%lu:going to wait @lock2 in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr);
#ifdef DEBUG
               printf("%lu:recovering @lock2 in %d\n",thread_id, k);
#endif



               if (current_b[0].empty()) break;



#ifdef DEBUG               
               printf("%lu:going to wait @lock3 in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr2);

#ifdef DEBUG
               printf("%lu:recovering @lock3 in %d\n",thread_id, k);
#endif


          } else {


               while (current_b[socket_no].unsafe_size()) {
                    unsigned int index;
                    if (current_b[socket_no].try_pop(index)) {


#ifdef DEBUG
                         printf("%lu: %d is out\n", thread_id, index);
#endif

                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest;


#ifdef DEBUG
                              printf("%lu: forward looking at %d\n", thread_id, id);
#endif

                              
                              int it_belongs_to = determine_socket(id);
                              if (socket_no == it_belongs_to) { 
                                   if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                                        int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                                        if (!its_color) {
                                             cost[id] = cost[index] + 1;

#ifdef DEBUG
                                             printf("%lu: forward visiting %d\n", thread_id, id);  
#endif


                                             own_queue.push(id);
                                        }
                                   }
                                   
                              } else {
                                   PAIR pair;
                                   pair.first = id;
                                   pair.second = index;
                                   socket_queue[it_belongs_to].push(pair);

#ifdef DEBUG
                                   printf("%lu: forward to %d\n", thread_id, it_belongs_to);
#endif

                              }
                              
                           
                         }
                    }
               }

               while(!own_queue.empty()) {
                    unsigned int index = own_queue.front();
                    own_queue.pop();
                    current_a[socket_no].push(index);
#ifdef DEBUG
                    printf("%lu: forward push %d\n", thread_id, index);
#endif

                   
               }

#ifdef DEBUG               
               printf("%lu:going to wait @lock1 in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr);
#ifdef DEBUG
               printf("%lu:recovering @lock1 in %d\n",thread_id, k);
#endif

               while (socket_queue[socket_no].unsafe_size()) {
                    PAIR pair;
                    if (socket_queue[socket_no].try_pop(pair)) {
                         unsigned int index = pair.second;
                         unsigned int id = pair.first;

#ifdef DEBUG
                         printf("%lu: cleaner looking at %d\n", thread_id, id);
#endif

                         if (!test_bit(id/SOCKET_NUM_USED, bitmap[socket_no])) {
                              int its_color = sync_test_and_set_bit(id/SOCKET_NUM_USED, bitmap[socket_no]);
                              if (!its_color) {
                                   cost[id] = cost[index] + 1;
                                   

#ifdef DEBUG
                                   printf("%lu: cleaner visiting %d\n", thread_id, id);  
#endif

                                   own_queue.push(id);
                              }
                         }
                    } 
               }

               while(!own_queue.empty()) {
                    unsigned int index = own_queue.front();
                    own_queue.pop();
                    current_a[socket_no].push(index);

#ifdef DEBUG
                    printf("%lu: cleaner push %d\n", thread_id, index);
#endif
               }
               
#ifdef DEBUG               
               printf("%lu:going to wait @lock2 in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr);
#ifdef DEBUG
               printf("%lu:recovering @lock2 in %d\n",thread_id, k);
#endif


               if (current_a[0].empty()) break;



#ifdef DEBUG               
               printf("%lu:going to wait @lock3 in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr2);
#ifdef DEBUG
               printf("%lu:recovering @lock3 in %d\n",thread_id, k);
#endif
             
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
          bitmap[i] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     }
     
     for (int i=0; i<SOCKET_NUM_USED; i++)
          for (int j=0; j<map_size; j++)
               bitmap[i][j] = 0;


	 gettimeofday(&start, 0);

     set_bit(source_node_no, bitmap[determine_socket(source_node_no)]);
	 current_a[determine_socket(source_node_no)].push(source_node_no);
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
     }

	 return time_used;
	 
}

