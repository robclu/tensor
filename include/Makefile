########################################################################################
#				 	                EXECUTABLE NAME 	                               #
#				 	                                                                   #
# NOTE: The following conventions are used:                                            #
#                                                                                      #
#       - CU = CUDA related variables                                                  #
#       - CX = C++ related variables                                                   #
########################################################################################

EXE 			:= ftl_tests

########################################################################################
#					                  COMPILERS						                   #
#                                                                                      #					 
# NOTE: Compiling with cuda because GPU support will be added                          #
########################################################################################

HOST_COMPILER	:= g++
NVCC 			:= nvcc -ccbin $(HOST_COMPILER)
CXX 			:= $(HOST_COMPILER)

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

########################################################################################
# 					                TARGET RULES 					                   #
#######################################################################################

.PHONY: all debug run 
	
all: debug
	
release: CX_FLAGS += $(RE_FLAGS)
release: run
	
debug: CX_FLAGS += $(DG_FLAGS)
debug: run

run: build_tests
	rm -rf *.o
	./$(EXE) --log_level=test_suite
	
ftl_tests.o: ftl_tests.cpp 
	$(CXX) $(CU_INC) $(CU_FLAGS) $(CX_INC) $(CX_FLAGS) -o $@ -c $<

build_tests: ftl_tests.o 
	$(CXX) -o $(EXE) $+ $(CU_LDIR) $(CU_LIBS) $(CX_LDIR) $(CX_LIBS)
	
clean:
	rm -rf *.o
	rm -rf $(EXE) 

clobber: clean
