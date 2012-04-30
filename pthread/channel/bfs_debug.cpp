/**********************************************************************
filename: cpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

two queues version

***********************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <tbb/concurrent_queue.h>
#include <sys/time.h>
#include <stdlib.h>
//#define DEBUG



tbb::concurrent_queue<unsigned int> current_a;
tbb::concurrent_queue<unsigned int> current_b;

//tbb::concurrent_bounded_queue<unsigned int> current_a;
//tbb::concurrent_bounded_queue<unsigned int> current_b;
pthread_barrier_t barr;
pthread_barrier_t barr2;




void* thread_func(void*) {
     pthread_t thread_id = pthread_self();
    
     int k = 0;
     bool stop = false;
     while(1) {
         
          if (k%2 ==0) {
     
               while (current_a.unsafe_size()) {
                    unsigned int index;
                    if (current_a.try_pop(index)) {
#ifdef DEBUG
                         printf("%lu: %d is out\n", thread_id, index);
#endif
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest; 
#ifdef DEBUG
                              printf("%lu: looking at %d\n", thread_id, id);
#endif
                              bool its_color;
                              if (visited[id] == false) {
                                   its_color = __sync_lock_test_and_set(&visited[id], true);
                                   if (its_color == false) {
                                        cost[id] = cost[index] + 1;  
#ifdef DEBUG
                                        printf("%lu: visiting %d\n", thread_id, id);  
#endif
                                        current_b.push(id);
                                   }
                              }
                         }
                    } 
   
               }
#ifdef DEBUG               
               printf("%lu:going to wait in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr);
#ifdef DEBUG
               printf("%lu:recovering in %d\n",thread_id, k);
#endif
               if (current_b.empty()) break;
               pthread_barrier_wait(&barr2);
               
          } else {

               while (current_b.unsafe_size()) {
                    unsigned int index;
                    if (current_b.try_pop(index)) {
#ifdef DEBUG
                         printf("%lu: %d is out\n", thread_id, index);
#endif
                         Node cur_node = node_list[index];
                         for (int i = cur_node.start; i < (cur_node.start+cur_node.edge_num); i++) {
                              unsigned int id = edge_list[i].dest; 
#ifdef DEBUG
                              printf("%lu: looking at %d\n", thread_id, id);
#endif
                              bool its_color;
                              if (visited[id] == false) {
                                   its_color = __sync_lock_test_and_set(&visited[id], true);
                                   if (its_color == false) {
                                        cost[id] = cost[index] + 1; 
#ifdef DEBUG
                                        printf("%lu: visiting %d\n", thread_id, id);  
#endif
                                        current_a.push(id);
                                   }
                              }
                         }
                    } 


               }
#ifdef DEBUG
               printf("%lu:going to wait in %d\n",thread_id, k);
#endif
               pthread_barrier_wait(&barr);
#ifdef DEBUG
               printf("%lu:recovering in %d\n",thread_id, k);
#endif
               if (current_a.empty()) break;
               pthread_barrier_wait(&barr2);
          }


          k++;

     }

       
     

     
}




float bfs(int num_of_threads) 
{
	 struct timeval start, end;
	 float time_used;

     //current_a.set_capacity(num_of_threads);

	 gettimeofday(&start, 0);

	 // visiting the source node now
	 visited[source_node_no] = true;
	 current_a.push(source_node_no);
	 cost[source_node_no] = 0;


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


	 // set threads number
	 pthread_t tid[50];

	 for (int i=0; i<num_of_threads; i++) {
          int err = pthread_create(&tid[i], NULL, thread_func, NULL);
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

	 return time_used;
	 
}

