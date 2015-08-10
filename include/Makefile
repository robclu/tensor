########################################################
#					EXECUTABLE NAME 				   #
########################################################

EXE 			:= new_tensor_tests

########################################################
#					COMPILERS						   #
########################################################

HOST_COMPILER	:= g++
NVCC 			:= nvcc -ccbin $(HOST_COMPILER)
CXX 			:= $(HOST_COMPILER)

########################################################
#				INCLUDE DIRECTORIES 				   #
########################################################

INCLUDES 		:= -I/usr/local/cuda-7.0/include -I.

########################################################
#					LIBRARIES 						   #
########################################################

CUDA_LIBS 		:= -lcuda -lcublas
TEST_LIBS 		:= -lgtest -lgtest_main -lpthread

LIB_DIR 		:= -L/usr/local/cuda/lib64

########################################################
#					COMPILER FLAGS 					   #
#                                                      #
# To enable compiler warnings, remove -w and replace   #
# with :                                               #
# 			--compiler-options -Wall                   #
########################################################

CCFLAGS 		:= -std=c++11 -w 
CUFLAGS 		:= -arch=sm_30

########################################################
# 					TARGET RULES 					   #
########################################################

.PHONY: all debug run cleanobs
	
all: debug 

release: CCFLAGS += -O3
release: tests
	
debug: CCFLAGS += -g
debug: run
	
new_tensor_tests.o: new_tensor_tests.cpp 
	$(NVCC) -x cu $(INCLUDES) $(CCFLAGS) $(CUFLAGS) -o $@ -c $<

main.o : main.cpp
	$(NVCC) -x cu $(INCLUDES) $(CCFLAGS) $(CUFLAGS) -o $@ -c $<

tests:  new_tensor_tests.o 
	$(NVCC) $(LDFLAGS) -o $(EXE) $+ $(LIB_DIR) \
		$(CUDA_LIBS) $(TEST_LIBS)	
		
run: tests cleanobs
	./$(EXE)
	
cleanobs:
	rm -rf *.o

clean:
	rm -rf *.o
	rm -rf $(EXE) 

clobber: clean
