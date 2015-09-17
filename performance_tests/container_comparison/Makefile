########################################################################################
#				 	                EXECUTABLE NAME 	                               #
########################################################################################

EXE_SCONT 		:=  scontainer 
EXE_DCONT       :=  dcontainer
EXE_CONT        :=   container

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

CXX_FLAGS 		:= -std=c++11 -w -O3

########################################################################################
# 					                TARGET RULES 					                   #
#######################################################################################

.PHONY: scont scont_asm dcont dcont_asm cont clean 
	
scont: build_and_run_scont
dcont: build_and_run_dcont
cont:  build_and_run_cont

build_and_run_scont: build_scont
	rm -rf *.o
	./$(EXE_SCONT)

scontainer.o: scontainer.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<
	
build_scont: scontainer.o
	$(CXX) -o $(EXE_SCONT) $+ $(CXX_LDIR) $(CXX_LIBS)
	
scontainer.s: scontainer.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<

scont_asm: CXX_FLAGS += -S -g -fverbose-asm -masm=intel -O3
scont_asm: scontainer.s 
	as -adhln scontainer.s > scontainer.lst
	
build_and_run_dcont: build_dcont
	rm -rf *.o
	./$(EXE_DCONT)

dcontainer.o: dcontainer.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<
	
build_dcont: dcontainer.o
	$(CXX) -o $(EXE_DCONT) $+ $(CXX_LDIR) $(CXX_LIBS)
	
dcontainer.s: dcontainer.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<

dcont_asm: CXX_FLAGS += -S -g -fverbose-asm -masm=intel -O3
dcont_asm: dcontainer.s 
	as -adhln dcontainer.s > dcontainer.lst

build_and_run_cont: build_cont
	rm -rf *.o
	./$(EXE_CONT)

container.o: container.cpp
	$(CXX) $(CXX_INC) $(CXX_FLAGS) -o $@ -c $<
	
build_cont: container.o
	$(CXX) -o $(EXE_CONT) $+ $(CXX_LDIR) $(CXX_LIBS)
	
clean:
	rm -rf *.o
	rm -rf *.s
	rm -rf *.lst
	rm -rf $(EXE_SCONT) 
	rm -rf $(EXE_DCONT) 
	rm -rf $(EXE_CONT) 
	
