AUTHOR = onesuper
VERSION = 1.0
DEBUG = -g
CC0 = g++
OMP = -fopenmp

#**************************************

all:	naive cpu

naive:	naive/naive

cpu:	cpu/baseline/baseline

#*******************************************

# naive
naive/naive: naive/main.cpp
	$(CC0) naive/main.cpp -o naive/naive -Wall

# cpu
cpu/baseline/baseline: cpu/baseline/main.cpp
	$(CC0) cpu/baseline/main.cpp -o cpu/baseline/baseline -Wall $(OMP)



# gpu

#*****************************************

clean:
	rm -r ./*~
