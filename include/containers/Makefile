########################################################
#					EXECUTABLE NAME 				   #
########################################################

EXE 			:= container_tests

########################################################
#					COMPILERS						   #
########################################################

HOST_COMPILER	:= g++
NVCC 			:= nvcc -ccbin $(HOST_COMPILER)
CXX 			:= $(HOST_COMPILER)

########################################################
#				INCLUDE DIRECTORIES 				   #
########################################################

INCLUDES 		:= 

########################################################
#					LIBRARIES 						   #
########################################################

CUDA_LIBS 		:= 
TEST_LIBS 		:= -lgtest -lgtest_main \
				   -lpthread

LIB_DIR 		:= 

########################################################
#					COMPILER FLAGS 					   #
#                                                      #
# To enable compiler warnings, remove -w and replace   #
# with :                                               #
# 			--compiler-options -Wall                   #
########################################################

CCFLAGS 		:= -std=c++11 -w -g
CUFLAGS 		:= -arch=sm_30

########################################################
# 					TARGET RULES 					   #
########################################################

all: tests 

container_tests.o: container_tests.cpp 
	$(NVCC) -x cu $(INCLUDES) $(CCFLAGS) $(CUFLAGS) -o $@ -c $<

main.o : main.cpp
	$(NVCC) -x cu $(INCLUDES) $(CCFLAGS) $(CUFLAGS) -o $@ -c $<

tests: container_tests.o main.o
	$(NVCC) $(LDFLAGS) -o $(EXE) $+ $(LIB_DIR) \
		$(CUDA_LIBS) $(TEST_LIBS)	
		
cleanobs:
	rm -rf *.o

clean:
	rm -rf *.o
	rm -rf $(EXE) 

clobber: clean
