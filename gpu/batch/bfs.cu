/**********************************************************************
filename: gpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

bfs algorithm implemented by CUDA without any optimization.

***********************************************************************/

#include <cuda.h>
#include <stdio.h>

#include <sys/time.h>

#define MAX_THREAD_PER_BLOCK 1024
#define THREAD_PER_BLOCK 128
#define MAX_LOCAL_QUEUE_SIZE 1200
/*
 the method is a little different with the naive one

 it uses two current sets

 */




__global__ static void bfs_kernel(unsigned int* current_set, unsigned int* new_set,
                                  int current_set_size, int* current_set_size_new, 
                                  Node* node_list, Edge* edge_list, int* color, int* cost, int level)
{
     int tid = blockIdx.x * blockDim.x + threadIdx.x;
 
     __shared__ int local_queue[MAX_LOCAL_QUEUE_SIZE];
     __shared__ int local_queue_size;
     __shared__ int new_set_cursor;

     __syncthreads();
     if (threadIdx.x == 0) {
          new_set_cursor = 0;
     }
     __syncthreads();
     
     
     for(int j=tid; j<(current_set_size+blockDim.x*gridDim.x); j+=blockDim.x*gridDim.x) {
          
          __syncthreads();
          if (threadIdx.x == 0) {
               local_queue_size = 0;
          }
          __syncthreads();

          if (j < current_set_size) {

               unsigned int index = current_set[j];// fetch one from the current set
               current_set[j] = 0;                 // erase it
               cost[index] = level;
               Node cur_node = node_list[index];
               for (int i=cur_node.start; i < cur_node.start + cur_node.edge_num; i++)
               {
                    unsigned int id = edge_list[i].dest;
                    int its_color = atomicExch((int*) &color[id], BLACK);
                    if (its_color == WHITE) {
                         int write_position = atomicAdd((int*) &local_queue_size, 1);
                         local_queue[write_position] = id;
                         //printf("push %d to local queue total:%d \n", id, local_queue_size);
                    }
               }
          }

          __syncthreads();
          
          if (threadIdx.x == 0) {
               new_set_cursor = atomicAdd((int*) &(*current_set_size_new), local_queue_size);
               // printf("new_set_cursor = %d\n", new_set_cursor);
          }
          __syncthreads();
          
          for (int i=threadIdx.x; i<local_queue_size; i+=blockDim.x) {
               new_set[new_set_cursor+i] = local_queue[i];
               //printf("push %d to next queue total:%d  \n",local_queue[i], *current_set_size_new);
          }
          __syncthreads();
          
     }

   




}


float bfs(int block_in_a_grid) 
{
	 struct timeval start, end;
	 float time_used;
	 gettimeofday(&start, 0);

	 // visiting the source node now(CPU)
	 color[source_node_no] = BLACK;
	 current_set[0]= source_node_no;
	 cost[source_node_no] = 0;
	 
     // synchronize to GPU mem
     cudaMemcpy(d_color, color, sizeof(int) * num_of_nodes, cudaMemcpyHostToDevice);
     cudaMemcpy(d_current_set_a, current_set, sizeof(unsigned int) * num_of_nodes, cudaMemcpyHostToDevice);
     cudaMemcpy(d_cost, cost, sizeof(int) * num_of_nodes, cudaMemcpyHostToDevice); 


     //cudaMemset(d_color, BLACK, sizeof(int));
     //cudaMemset(d_current_set_a[0], source_node_no, sizeof(unsigned int));
     //cudaMemset(d_cost[source_node_no], 0, sizeof(int));


     int current_set_size = 1;          // only source node in it     
     int block_num = block_in_a_grid;
     int thread_num = THREAD_PER_BLOCK;


     int level = 0;                     // used to control the current_set_a/b to visit
	 while(current_set_size != 0) {
          if (level%2 == 0) {
               cudaMemset(d_current_set_size_new, 0, sizeof(int));
               bfs_kernel<<<block_num, thread_num, 10000>>>(d_current_set_a, d_current_set_b, current_set_size, d_current_set_size_new,
                                                     d_node_list, d_edge_list, d_color, d_cost, level);
               cudaThreadSynchronize();
               cudaMemcpy(current_set_size_new, d_current_set_size_new, sizeof(int), cudaMemcpyDeviceToHost);
               current_set_size = *current_set_size_new; 
               //printf("%d:%d\n",level,current_set_size);
               
          } else {

               cudaMemset(d_current_set_size_new, 0, sizeof(int));
               bfs_kernel<<<block_num, thread_num, 10000>>>(d_current_set_b, d_current_set_a, current_set_size, d_current_set_size_new,
                                                     d_node_list, d_edge_list, d_color, d_cost, level);
               cudaThreadSynchronize();
               cudaMemcpy(current_set_size_new, d_current_set_size_new, sizeof(int), cudaMemcpyDeviceToHost);
               current_set_size = *current_set_size_new;
               //printf("%d:%d\n",level,current_set_size);
               
          }
          level++;
	 }

     // copy the result from GPU to CPU mem
     cudaMemcpy(cost, d_cost, sizeof(unsigned int)*num_of_nodes, cudaMemcpyDeviceToHost);

     // come out the time
	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
