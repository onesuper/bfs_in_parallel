AUTHOR = onesuper
VERSION = 1.0
DEBUG = -g
CC0 = g++
OMPFLAG = -fopenmp -O2
TBB = -ltbb
CC1 = nvcc
PTHREAD = -lpthread -O3
CUFLAG1 = -lcuda -lcutil_x86_64 -L/home/liugu/NVIDIA_GPU_Computing_SDK/C/lib
CUFLAG2 = -I/home/liugu/NVIDIA_GPU_Computing_SDK/C/common/inc -O3 -Xcompiler "-m32" -Xptxas -dlcm=cg -arch sm_20
#**************************************

all:	naive pthread gpu
naive:	naive/naive
cpu:	cpu/baseline1/baseline1	cpu/baseline2/baseline2 cpu/conflict/conflict cpu/non-lock/non-lock cpu/rodinia/rodinia cpu/concurrent/concurrent cpu/concurrent2/concurrent2 cpu/concurrent3/concurrent3 cpu/bitmap/bitmap cpu/socket/socket cpu/sockets/sockets cpu/bitmap_while/bitmap_while
gpu:	gpu/baseline/baseline
pthread: pthread/baseline/baseline pthread/bitmap/bitmap pthread/batch/batch pthread/check/check pthread/channel/channel


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

cpu/socket/socket: cpu/socket/main.cpp
	$(CC0) cpu/socket/main.cpp -o cpu/socket/socket -Wall $(OMPFLAG) $(TBB)

cpu/sockets/sockets: cpu/sockets/main.cpp
	$(CC0) cpu/sockets/main.cpp -o cpu/sockets/sockets -Wall $(OMPFLAG) $(TBB)

cpu/bitmap_while/bitmap_while: cpu/bitmap_while/main.cpp
	$(CC0) cpu/bitmap_while/main.cpp -o cpu/bitmap_while/bitmap_while -Wall $(OMPFLAG) $(TBB)



# pthread
pthread/baseline/baseline: pthread/baseline/main.cpp
	$(CC0) pthread/baseline/main.cpp -o pthread/baseline/baseline -Wall $(PTHREAD) $(TBB)

pthread/bitmap/bitmap: pthread/bitmap/main.cpp
	$(CC0) pthread/bitmap/main.cpp -o pthread/bitmap/bitmap -Wall $(PTHREAD) $(TBB)

pthread/batch/batch: pthread/batch/main.cpp
	$(CC0) pthread/batch/main.cpp -o pthread/batch/batch -Wall $(PTHREAD) $(TBB)

pthread/check/check: pthread/check/main.cpp
	$(CC0) pthread/check/main.cpp -o pthread/check/check -Wall $(PTHREAD) $(TBB)

pthread/channel/channel: pthread/channel/main.cpp
	$(CC0) pthread/channel/main.cpp -o pthread/channel/channel -Wall $(PTHREAD) $(TBB)



#gpu
gpu/baseline/baseline: gpu/baseline/main.o
	$(CC1) -o gpu/baseline/baseline gpu/baseline/main.o $(CUFLAG1)


gpu/baseline/main.o: gpu/baseline/main.cu
	$(CC1) gpu/baseline/main.cu  $(CUFLAG2)  -c -o gpu/baseline/main.o 




#*****************************************

clean:
	rm -r ./*~

