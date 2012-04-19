AUTHOR = onesuper
VERSION = 1.0
DEBUG = -g
CC0 = g++
OMPFLAG = -fopenmp -O3
TBB = -ltbb
CC1 = nvcc


#**************************************

all:	naive cpu
naive:	naive/naive
cpu:	cpu/baseline1/baseline1	cpu/baseline2/baseline2 cpu/conflict/conflict cpu/non-lock/non-lock cpu/rodinia/rodinia cpu/concurrent/concurrent cpu/concurrent2/concurrent2 cpu/concurrent3/concurrent3 cpu/bitmap/bitmap
gpu:	gpu/baseline/baseline


#*******************************************

# naive
naive/naive: naive/main.cpp
	$(CC0) naive/main.cpp -o naive/naive -Wall -O3


# cpu
cpu/baseline1/baseline1: cpu/baseline1/main.cpp
	$(CC0) cpu/baseline1/main.cpp -o cpu/baseline1/baseline1 -Wall $(OMPFLAG)

cpu/baseline2/baseline2: cpu/baseline2/main.cpp
	$(CC0) cpu/baseline2/main.cpp -o cpu/baseline2/baseline2 -Wall $(OMPFLAG) 

cpu/conflict/conflict: cpu/conflict/main.cpp
	$(CC0) cpu/conflict/main.cpp -o cpu/conflict/conflict -Wall $(OMPFLAG)

cpu/non-lock/non-lock: cpu/non-lock/main.cpp
	$(CC0) cpu/non-lock/main.cpp -o cpu/non-lock/non-lock -Wall $(OMPFLAG)

cpu/rodinia/rodinia: cpu/rodinia/main.cpp
	$(CC0) cpu/rodinia/main.cpp -o cpu/rodinia/rodinia -Wall $(OMPFLAG)

cpu/concurrent/concurrent: cpu/concurrent/main.cpp
	$(CC0) cpu/concurrent/main.cpp -o cpu/concurrent/concurrent -Wall  $(OMPFLAG) $(TBB)

cpu/concurrent2/concurrent2: cpu/concurrent2/main.cpp
	$(CC0) cpu/concurrent2/main.cpp -o cpu/concurrent2/concurrent2 -Wall $(OMPFLAG) $(TBB)

cpu/concurrent3/concurrent3: cpu/concurrent3/main.cpp
	$(CC0) cpu/concurrent3/main.cpp -o cpu/concurrent3/concurrent3 -Wall $(OMPFLAG) $(TBB)

cpu/bitmap/bitmap: cpu/bitmap/main.cpp
	$(CC0) cpu/bitmap/main.cpp -o cpu/bitmap/bitmap -Wall $(OMPFLAG) $(TBB)

#gpu
gpu/baseline/baseline: gpu/baseline/main.cu
	$(CC1) gpu/baseline/main.cu -o gpu/baseline/baseline



#*****************************************

clean:
	rm -r ./*~

