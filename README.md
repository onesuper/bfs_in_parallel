


## Description
 

These are some code pieces of my undergraduation research on breadth-first search in parrallel.


Since BFS is a regular algorithm, which is a nightmare to the current cache model of computers, the commuication overhead between
computing cores is a big problem. So it's meaningful to design an architecture-related algorithm and use some optimization
techniques to accelerate the application.


Through these works, I have another understanding on how to implement a scalable algorithm in different architectures. 



## Organization of the Codes

The project consists of three parts:

1. A naive implementation of bfs in C language. (The algorithm is from CLRS)
2. Several parrallel versions for Multi-core platform implemented in OpenMP.
 * **baseline1**: single queue/the num of threads is given by command line argument
 * **baseline2**: double queues
 * **level**: the num of threads equals the number of nodes in the current queue
 * **bitmap**: optimized with a bitmap 
 * **socket**: local socket queue version
3. Serveral parrallel versions for Many-core platform implemented in NVIDIA CUDA.
 * **baseline**
 * **flexible**

They are all tested on computer with 4-sockets CPUs (each one has 8 cores) and a NVIDIA TELSA 2050 graphics card. 

## About the Test Cases


The test cases are the following 4 kinds:

1. real graphs from DIAMCS
2. regular graphs
3. irregular graph
4. R-MAT graphs


## About the Algorithm

The algorithm described in CLRS looks like *algorithm 1*


It's simply revised muti-core version should look like *algorithm 2* (**better** because it needs less locked operation)


A better solution is a version using two queues which looks like *algorithm 3*


When we want to implement BFS on GPU-CUDA environment, the algorithm should be revised further more, becauce CUDA didn't support a dynamic data structures such as queue. What's more, CUDA uses another programming mode called SIMT.




### Navie(single-core)


algorithm 1

    color[r] = GREY;
    Enqueue(CQ, r);
    cost[r] = 0;
    
    while CQ is not empty do:
        u = Dequeue(CQ);
        for each v in adjacent to u do:
            if color[v] == WHITE then:
                cost[v] = cost[u] + 1;
                Enqueue(CQ, v);
                color[v] = GREY;
        color[u] = BLACK;


### CPU(multi-core)

#### Baseline

algorithm 2

    color[r] = GREY;
    Enqueue(CQ, r);
    cost[r] = 0;

    while CQ is not empty in parallel do:
        u = LockedDequeue(CQ);
        for each v in adjacent to u do:
            if color[v] = WHITE then:
                its_color = LockedReadSet(color[v], BLACK);
                if its_color = WHITE then:
                    LockedEnqueue(CQ, v);
                    cost[v] = cost[u] + 1;
                  
        Synchronize;
        
            


#### Baseline with Two Queues

algorithm 3

    color[r] = BLACK;
    Enqueue(CQ,r);
    cost[r] = 0;

    while CQ is not empty in parallel do:
        u = LockedDequeue(CQ);
        for each v in adjcent to u do:
            if color[v] = WHITE then:
                its_color = LockedReadSet(color[v], BLACK);
                if its_color = WHITE then:  //ensure only one thread access
                    LockedEnqueue(NQ, v);   // to node v
                    cost[v] = cost[u] + 1;
         Synchronize;
         Swap(CQ, NQ);
    
    

#### Optimized with a Bitmap

algorithm 4

    bitmap[r] = 1;
    Enqueue(CQ,r);
    cost[r] = 0;

    while CQ is not empty in parallel do:
        u = LockedDequeue(CQ);
        for each v in adjcent to u do:
            if bitmap[v] = WHITE then:
                its_value = LockedReadSet(bitmap[v], 1);
                if its_value = 0 then:  //ensure only one thread access
                    LockedEnqueue(NQ, v);   // to node v
                    cost[v] = cost[u] + 1;  
         Synchronize;
         Swap(CQ, NQ);


#### Optimized with Inner-sockets Queue


algorithm 5

### GPU(many-core)


#### Baseline

algorithm 6

    color[r] = BLACK;
    set_A[0] = r;
    cost[r] = 0;
    set_size = 1;
    level = 0
    
    while set_size != 0  do:
        if level%2 = 0 then:
            kernel(set_A, set_B, ...)
            Synchronize;
            set_size = new_set_size;
         else:
             kernel(set_B, set_A, ...)
             Synchronize;
             set_size = new_set_size;
         level = level + 1
         
    kernel(CQ, NQ, ...):
        tid = GetThreadNum();
        new_set_size = 0;       //empty NQ
        if tid < set_size then:
            u = CQ[tid];
            cost[u] = level;
            for each v in adjacent to u do:
                if color[v] = WHITE then:
                    its_color = LockedReadSet(color[v), BLACK);
                    if its_color = WHITE then:
                        write_pos = AtomicAdd(new_size, 1);  // like Enqueue
                        NQ[write_pos] = v;                 // the size is marked by new_size
                    



#### Optimized with flexible threads

algorithm 7



## Contact


email: onesuperclark@gmail.com
