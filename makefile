AUTHOR = onesuper
VERSION = 1.0
DEBUG = -g


#**************************************

all:	naive
naive:	naive/naive




#*****************************************
naive/naive: naive/main.cc
	g++ naive/main.cc -o naive/naive -Wall $(DEBUG)

#*****************************************

clean:
	rm ./navie/*~
	rm ./*~
