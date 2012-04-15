AUTHOR = onesuper
VERSION = 1.0
DEBUG = -g
CC0 = g++
OMPFLAG = -fopenmp
CC1 = nvcc

#**************************************

all:	naive cpu
naive:	naive/naive
cpu:	cpu/baseline1/baseline1	cpu/level/level
gpu:	gpu/baseline/baseline


#*******************************************

# naive
naive/naive: naive/main.cpp
	$(CC0) naive/main.cpp -o naive/naive -Wall


# cpu
cpu/baseline1/baseline1: cpu/baseline1/main.cpp
	$(CC0) cpu/baseline1/main.cpp -o cpu/baseline1/baseline1 -Wall $(OMPFLAG)

cpu/level/level: cpu/level/main.cpp
	$(CC0) cpu/level/main.cpp -o cpu/level/level -Wall $(OMPFLAG)


#gpu
gpu/baseline/baseline: gpu/baseline/main.cu
	$(CC1) gpu/baseline/main.cu -o gpu/baseline/baseline



#*****************************************

clean:
	rm -r ./*~

