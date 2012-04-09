/**********************************************************************
filename: gpu/baseline/bfs.cpp
author: onesuper
email: onesuperclark@gmail.com

bfs algorithm implemented by CUDA without any optimization.

***********************************************************************/

#include <cuda.h>
#include <stdio.h>
//#include <deque>
#include <sys/time.h>


#define BLOCK_IN_A_GRID 80
#define THREAD_PER_BLOCK 64
#define MAX_THREAD_PER_BLOCK 256

__global__ static void bfs_kernel(unsigned int* current_set, unsigned int* new_set, int* current_set_size,
                                  int* cost, Node* node_list, Edge* edge_list, int* color, int* level, int* current_set_size_new)
{
	
     int tid = blockIdx.x*blockDim.x + threadIdx.x;
     if (tid < current_set_size) {  // the rest threads take a rest
          unsigned int index = current_set[tid];  // fetch one from the current set
          
          d_cost[index] = level;

          for (int i = node_list[index].start;
               i < (node_list[index].start + node_list[index].edge_num);
               i++)
          {
               unsigned int id = edge_list[i].dest;
               int 
          }
          
          
          
     }


}


float bfs() 
{
	 struct timeval start, end;
	 float time_used;
	 gettimeofday(&start, 0);

	 // visiting the source node now(CPU)
	 color[source_node_no] = GREY;
	 current_set[0]= source_node_no;
	 cost[source_node_no] = 0;
	 
     // synchronize to GPU mem
     cudaMemcopy(d_cost, cost, sizeof(int) * num_of_nodes, cudaMemcpyHostToDevice);
     cudaMemcopy(d_current_set_a, current_set, sizeof(unsigned int) * num_of_nodes,
                 cudaMemcpyHostToDevice);
     cudaMemcopy(d_cost, cost, sizeof(int) * num_of_nodes, cudaMemcpyHostToDevice); 
     int current_set_size = 1;          // only source node in it 
     int level = 0;                     // used to control the current_set_a/b to visit
     int block_num = BLOCK_IN_A_GRID;
     int thread_num = THREAD_PER_BLOCK;
     
	 while(current_set_size != 0) {
          if (level%2 == 0) {
               bfs_kernel<<<block_num, thread_num>>>(d_current_set_a, d_current_set_b, current_set_size, d_cost,
                                                     d_node_list, d_edge_list, d_color, level, d_current_set_size_new);
               cudaThreadSynchronize();
               cudaMemcpy(current_set_size_new, d_current_set_size_new, sizeof(int)*1, cudaMemcpyDeviceToHost);
               current_set_size = *current_set_size_new; // update the size of current_size
          } else {
               bfs_kernel<<<block_num, thread_num>>>(d_current_set_b, d_current_set_a, current_set_size, d_cost,
                                                     d_node_list, d_edge_list, d_color, level, d_current_set_size_new);
               cudaThreadSynchronize();
               cudaMemcpy(current_set_size_new, de_current_set_size_new, sizeof(int)*1, cudaMemcpyDeviceToHost);
               current_set_size = *current_set_size_new; // update the size of current_size
          }
          level++;
	 }

     //copy the result from GPU to CPU mem
     cudaMemcopy(cost, d_cost, sizeof(unsigned int)*num_of_nodes, cudaMemcpyDeviceToHost);

	 gettimeofday(&end, 0);
	 time_used = 1000000 * (end.tv_sec - start.tv_sec) +
		  end.tv_usec - start.tv_usec;
	 time_used /= 1000000;
	 printf("used time: %f\n", time_used);
	 
	 return time_used;
	 
}
