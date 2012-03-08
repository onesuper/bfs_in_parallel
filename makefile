AUTHOR = onesuper
VERSION = 1.0



#**************************************

all:	naive
naive:	naive/naive




#*****************************************
naive/naive: naive/main.c naive/bfs.c
	gcc naive/main.c naive/bfs.c -o naive/naive -Wall

#*****************************************

clean:
	rm ./navie/*~
