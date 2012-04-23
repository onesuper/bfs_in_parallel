/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

two queues version

***********************************************************************/


#include <stdio.h>
#include <tbb/concurrent_queue.h>
#include <sys/time.h>
#include "syncbitops.h"
#include "bitops.h"
#include <sched.h>
#include <pthread.h>
#include <unistd.h>


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

typedef struct pair_t {
     unsigned int first;
     unsigned int second;
} PAIR;


tbb::concurrent_bounded_queue<unsigned int> current_a[4];
tbb::concurrent_bounded_queue<unsigned int> current_b[4];
tbb::concurrent_bounded_queue<PAIR> socket_queue[4];
unsigned long* bitmap[4];

void* thread_fun() {
     do {
          if (k%2 == 0) {
               bool sstop = false;
               while (!sstop) {
#pragma omp parallel
                    {
                         int socket_no = sched_getcpu();

#ifdef DEBUG
                         printf("in socket:%d\n", socket_no);
#endif

                         unsigned int index;
                         if (!current_a[socket_no].empty())
                         {
                              current_a[socket_no].pop(index);

#ifdef DEBUG
                              printf("pop %d in socket %d\n", index, socket_no);
#endif

                              Node cur_node = node_list[index];
                              for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                              {
                                   unsigned int id = edge_list[i].dest;
#ifdef DEBUG
                                   printf("id=%d\n", id);
#endif
                                   unsigned int it_belongs_to = determine_socket(id);

#ifdef DEBUG
                                   printf("id belongs to %d; ", it_belongs_to);
#endif

                                   if (socket_no == it_belongs_to) {
                                        if (!test_bit(id/4, bitmap[socket_no])) {
                                             int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                                             if (!its_color) {
                                                  cost[id] = cost[index] + 1; 
#ifdef DEBUG
                                                  printf("visit it \n");
#endif 
                                                  current_b[socket_no].push(id);
#ifdef DEBUG
                                                  printf("push %d\n", id);
#endif
                                             }
                                        }
                                   } else {
                                        PAIR a_pair;
                                        a_pair.first = id;
                                        a_pair.second = index;
                                        socket_queue[it_belongs_to].push(a_pair);
#ifdef DEBUG
                                        printf("(%d, %d) go to %d\n", id, index, it_belongs_to);
#endif
                                   }
                              }

                         }

                         if (current_a[0].empty() && current_a[1].empty() && current_a[2].empty() && current_a[3].empty())
                         {
                              sstop = true; 
#ifdef DEBUG
                              printf("all currents are empty\n");
#endif
                         }

                    }
               }

               
               //
               // phase 1 stops ! barrier here!!!
               //
               
               sstop =false;
               while (!sstop) {
#pragma omp parallel
                    {
                  
                         int socket_no = sched_getcpu();
#ifdef DEBUG
                         printf("%d cleaner on\n", socket_no);
#endif
                         PAIR a_pair;
                         if (!socket_queue[socket_no].empty())
                         {
                              socket_queue[socket_no].pop(a_pair);
                              unsigned int index = a_pair.second;
                              unsigned int id = a_pair.first;
                              if(!test_bit(id/4, bitmap[socket_no])) {
                                   int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                                   if (!its_color) {
                                        cost[id] = cost[index] + 1;
                                        current_b[socket_no].push(id);
#ifdef DEBUG
                                        printf("push %d to next[%d]\n", id, socket_no);
#endif
                                   }
                              }
                         }
                         if (socket_queue[0].empty() && socket_queue[1].empty() && socket_queue[2].empty() && socket_queue[3].empty())
                         {
                              sstop = true;
#ifdef DEBUG
                              printf("%d cleaner is off\n", socket_no);
#endif
                         }
                    }
               }
               //
               // phase 2 ends ! barrier here!!! 
               //
               if (current_b[0].empty() && current_b[1].empty() && current_b[2].empty() && current_b[3].empty()) 
               {
                    stop = true;
#ifdef DEBUG
                    printf("all nexts are empty\n");
#endif
               } 

          } else {
      
               bool sstop = false;
               while (!sstop) {
#pragma omp parallel
                    {
                         int socket_no = sched_getcpu();
#ifdef DEBUG
                         printf("in socket:%d\n", socket_no);
#endif
                         unsigned int index; 
                         if (!current_b[socket_no].empty())
                         {
                              current_b[socket_no].pop(index);
#ifdef DEBUG
                              printf("pop %d in socket %d\n", index, socket_no);
#endif
                              Node cur_node = node_list[index];
                              for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++)
                              {
                                   unsigned int id = edge_list[i].dest;
#ifdef DEBUG
                                   printf("id=%d\n", id);
#endif
                                   unsigned int it_belongs_to = determine_socket(id);
#ifdef DEBUG
                                   printf("id belongs to %d; ", it_belongs_to);
#endif
                                   if (socket_no == it_belongs_to) {
                                        if (!test_bit(id/4, bitmap[socket_no])) {
                                             int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                                             if (!its_color) {
                                                  cost[id] = cost[index] + 1; 
#ifdef DEBUG
                                                  printf("visit it \n");
#endif
                                                  current_b[socket_no].push(id);
#ifdef DEBUG
                                                  printf("push %d\n", id);
#endif
                                             }
                                        }
                                   } else {
                                        PAIR a_pair;
                                        a_pair.first = id;
                                        a_pair.second = index;
                                        socket_queue[it_belongs_to].push(a_pair);
#ifdef DEBUG                                        
                                        printf("(%d, %d) go to %d\n", id, index, it_belongs_to);
#endif 
                                   }
                              }
                              if (current_b[0].empty() && current_b[1].empty() && current_b[2].empty() && current_b[3].empty())
                              {
                                   sstop = true;
#ifdef DEBUG
                                   printf("all currents are empty\n");
#endif
                              }
                         }
                    }
               }

               
               //
               // phase 1 stops ! barrier here!!!
               //
               
               sstop =false;
               while (!sstop) {
#pragma omp parallel
                    {
                  
                         int socket_no = sched_getcpu();
#ifdef DEBUG
                         printf("%d cleaner on\n", socket_no);
#endif
                         PAIR a_pair;
                         if (!socket_queue[socket_no].empty())
                         {
                              socket_queue[socket_no].pop(a_pair);
                              unsigned int index = a_pair.second;
                              unsigned int id = a_pair.first;
                              if(!test_bit(id/4, bitmap[socket_no])) {
                                   int its_color = sync_test_and_set_bit(id/4, bitmap[socket_no]);
                                   if (!its_color) {
                                        cost[id] = cost[index] + 1;
                                        current_a[socket_no].push(id);
#ifdef DEBUG
                                        printf("push %d to next[%d]\n", id, socket_no);
#endif
                                   }
                              }
                         }
                         if (socket_queue[0].empty() && socket_queue[1].empty() && socket_queue[2].empty() && socket_queue[3].empty())
                         {
                              sstop = true;
#ifdef DEBUG
                              printf("cleaner is off\n");
#endif
                         }
                    }
               }
               //
               // phase 2 ends ! barrier here!!! 
               //
               if (current_a[0].empty() && current_a[1].empty() && current_a[2].empty() && current_a[3].empty()) 
               {
                    stop = true;
#ifdef DEBUG
                    printf("all nexts are empty\n");
#endif
               } 


          }
          k++;
     } while(!stop);
}

float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;

     int map_size = num_of_nodes/ (32*4) + 1;


     bitmap[0] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     bitmap[1] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     bitmap[2] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);
     bitmap[3] = (unsigned long*) malloc(sizeof(unsigned long)*map_size);

     for (int i=0; i<4; i++)
          for (int j=0; j<map_size; j++)
               bitmap[i][j] = 0;

	 gettimeofday(&start, 0);

	 // visiting the source node now
     set_bit(source_node_no, bitmap[determine_socket(source_node_no)]);
	 current_a[determine_socket(source_node_no)].push(source_node_no);
	 cost[source_node_no] = 0;

	 // set threads number
	 omp_set_num_threads(num_of_threads);
	 int k = 0;
     bool stop = false;


     pthread_t t1;
     pthread_t t2;
     pthread_attr_t att1;
     pthread_attr_t att2;

     pthread_attr_init(&attr1);
     pthread_attr_init(&attr2);



     if (0!= pthread_create(&t1, &attr1, thread_fun, NULL)) {
          printf("thread1 fail\n");
          return;
     }


     if (0!= pthread_create(&t2, &attr2, thread_fun, NULL)) {
          printf("thread2 fail\n");
          return;
     }

     
     cpu_set_t cpu_info;
     __CPU_ZERO(&cpu_info);
     __CPU_SET(0, &cpu_info);
     if (0!= pthread_setaffinity_np(t1, sizeof(cpu_set_t), &cpu_info))
          printf("set affinity fail");

     __CPU_ZERO(&cpu_info);
     __CPU_SET(1, &cpu_info);
     if (0!= pthread_setaffinity_np(t2, sizeof(cpu_set_t), &cpu_info))
          printf("set affinity fail");

     pthread_join(t1, NULL);
     pthread_join(t2, NULL);


	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
     for (int i=0; i<4; i++) free(bitmap[i]);
	 return time_used;
	 
}
