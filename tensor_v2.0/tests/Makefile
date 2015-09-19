########################################################################################
#				 	                EXECUTABLE NAME 	                               #
#				 	                                                                   #
# NOTE: The following conventions are used:                                            #
#                                                                                      #
#       - CU = CUDA related variables                                                  #
#       - CX = C++ related variables                                                   #
########################################################################################

EXE 			:= test_suite

########################################################################################
#					                  COMPILERS						                   #
#                                                                                      #					 
# NOTE: Compiling with cuda because GPU support will be added                          #
########################################################################################

HOST_COMPILER	:= clang++
NVCC 			:= nvcc -ccbin $(HOST_COMPILER)
CXX 			:= clang++ 

########################################################################################
#				                    INCLUDE DIRECTORIES 		                       #
########################################################################################

CU_INC 		    := 
CX_INC          :=

########################################################################################
#				   	                   LIBRARIES 						               #
########################################################################################

CU_LIBS 		:= 
CX_LIBS 		:= -lboost_unit_test_framework      

CU_LDIR         :=
CX_LDIR  	    := 

########################################################################################
#					                COMPILER FLAGS 					                   #
#                                                                                      #
# NOTE: To enable compiler warnings, remove -w and replace with :                      #
# 		--compiler-options -Wall                                                       #
########################################################################################

CU_FLAGS        :=
CX_FLAGS 		:= -std=c++11 -w 

DG_FLAGS        := -g
RE_FLAGS        := -O3

TP_FLAGS        := $(CX_FLAGS)

########################################################################################
# 					                TARGET RULES 					                   #
#######################################################################################

.PHONY: all container tensor traits

all: debug

debug: CX_FLAGS += $(DG_FLAGS)
debug: build_tests

container_tests.o: container_tests.cpp 
	$(CXX) $(CU_INC) $(CU_FLAGS) $(CX_INC) $(CX_FLAGS) -o $@ -c $<
	
tensor_tests.o: tensor_tests.cpp 
	$(CXX) $(CU_INC) $(CU_FLAGS) $(CX_INC) $(CX_FLAGS) -o $@ -c $<
	
traits_tests.o: traits_tests.cpp 
	$(CXX) $(CU_INC) $(CU_FLAGS) $(CX_INC) $(CX_FLAGS) -o $@ -c $<
	
tests.o: tests.cpp 
	$(CXX) $(CU_INC) $(CU_FLAGS) $(CX_INC) $(CX_FLAGS) -o $@ -c $<

build_tests: container_tests.o tensor_tests.o traits_tests.o tests.o
	$(CXX) -o $(EXE) $+ $(CU_LDIR) $(CU_LIBS) $(CX_LDIR) $(CX_LIBS)	

clean:
	rm -rf *.o
	rm -rf $(EXE) 
