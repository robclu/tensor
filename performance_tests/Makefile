########################################################################################
#				 	                EXECUTABLE NAME 	                               #
########################################################################################

EXE_CONT 		:=  container_comparison 
EXE             :=

########################################################################################
#                                   INPUT FILES                                        #
########################################################################################

INPUTS          :=
OBJS            :=

########################################################################################
#					                  COMPILERS						                   #
#                                                                                      #					 
# NOTE: Compiling with cuda because GPU support will be added                          #
########################################################################################

CXX 			:= g++ 

########################################################################################
#				                    INCLUDE DIRECTORIES 		                       #
########################################################################################

CXX_INC          :=

########################################################################################
#				   	                   LIBRARIES 						               #
########################################################################################

CXX_LIBS 		:= 
CXX_LDIR  	    := 

########################################################################################
#					                COMPILER FLAGS 					                   #
#                                                                                      #
# NOTE: To enable compiler warnings, remove -w and replace with :                      #
# 		--compiler-options -Wall                                                       #
########################################################################################

CXX_FLAGS 		:= -std=c++11 -w 

########################################################################################
# 					                TARGET RULES 					                   #
#######################################################################################

.PHONY: cont_compare cont_compare_asm
	
cont_compare: build_and_run_cont
	
build_and_run_cont: build_sample_cont
	rm -rf *.o
	./$(EXE_CONT)

container_comparison.o: container_comparison.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<
	
build_sample_cont: container_comparison.o
	$(CXX) -o $(EXE_CONT) $+ $(CXX_LDIR) $(CXX_LIBS)
	
container_comparison.s: container_comparison.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<

cont_compare_asm: CXX_FLAGS += -S -g -fverbose-asm -masm=intel -O3
cont_compare_asm: container_comparison.s 
	as -adhln container_comparison.s > container_comparison.lst

clean_cont:
	rm -rf *.o
	rm -rf $(EXE_CONT) 
	
clean_cont_asm:
	rm -rf container_comparison.s
	rm -rf container_comparison.lst
