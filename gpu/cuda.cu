/************************************************************************
filename: gpu/cuda.cu
author: onesuper
email: onesuperclark@gmail.com

allocate and free memory on device
for common use
*************************************************************************/

#include <stdio.h>
#include <cuda_runtime.h>

bool init_cuda() 
{
	int count = 0;

	cudaGetDeviceCount(&count);
	
	printf("%d device\n", count);

	if (count == 0) {
		fprintf(stderr, "There is no device.\n");
		return false;
	}

	int i;
	for (i=0; i<count; i++) {
		cudaDeviceProp prop;
		if (cudaGetDeviceProperties(&prop, i) == cudaSuccess) {
			if (prop.major >= 1) {
				break;
			}
		}
	}

	if (i == count) {
		fprintf(stderr, "There is no device supporting CUDA 1.x.\n");
		return false;
	}

	cudaSetDevice(i);

	return true;
}


void device_alloc_and_copy(void) {

	 cudaMalloc((void**) &d_node_list, sizeof(Node) * num_of_nodes);
	 cudaMemcpy(d_nodes_list, node_list, sizeof(Node) * num_of_nodes,
				cudaMemcpyHostToDevice);

	 cudaMalloc((void**) &d_edge_list, sizeof(Edge) * num_of_edges);
	 cudaMemcopy(d_edge_list, edge_list. sizeof(Edge) * num_of_edges,
				 cudaMemcpyHostToDevice);

	 cudaMalloc((void**) &d_color, sizeof(int) * num_of_nodes);
	 cudaMemcopy(d_color, color, sizeof(int) * num_of_nodes,
				 cudaMemcpyHostToDevice);

	 cudaMalloc((void**) &d_cost, sizeof(int) * num_of_nodes);
	 cudaMemcopy(d_cost, cost, sizeof(int) * num_of_nodes,
				 cudaMemcpyHostToDevice);

	 cudaMalloc((void**) &d_counter, sizeof(int) * MAX_LEVEL);
	 cudaMemcopy(d_counter, counter, sizeof(int) * MAX_LEVEL,
				 cudaMemcpyHostToDevice);

	 return; 
}

void device_free(void) {
	 cudaFree(d_node_list);
	 cudaFree(d_edge_list);
	 cudaFree(d_cost);
	 cudaFree(d_color);
	 cudaFree(d_counter);
	 return;
}
