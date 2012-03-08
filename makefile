AUTHOR = onesuper
VERSION = 1.0



#**************************************

all:	naive
naive:	naive/naive




#*****************************************
naive/naive: naive/main.cc naive/bfs.cc
	g++ naive/main.cc naive/bfs.cc -o naive/naive -Wall

#*****************************************

clean:
	rm ./navie/*~
	rm ./*~
