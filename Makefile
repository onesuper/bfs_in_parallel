AUTHOR = onesuper
VERSION = 1.0
DEBUG = -g
CC0 = g++

#**************************************

all:	naive
naive:	naive/naive




#*****************************************
naive/naive: naive/main.cpp
	$(CC) naive/main.cpp -o naive/naive -Wall $(DEBUG)

#*****************************************

clean:
	rm ./navie/*~
	rm ./*~
