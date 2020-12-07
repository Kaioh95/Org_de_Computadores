
SYSTEMC_ARCH=linux64
SYSTEMC=/usr/local/systemc-2.3.1/

LIB_DIRS=$(SYSTEMC)lib-$(SYSTEMC_ARCH)

INCLUDE_DIRS = -I. -I$(SYSTEMC)include -I include

HEADERS = include/Adder.h include/And.h include/B_Reg.h include/DataMem.h include/Ex_Mem.h include/Ext_16to32.h include/Id_Ex.h include/If_Id.h include/InstMem.h include/Mem_Wb.h include/Mux2x.h include/Mux2x5b.h include/P_C.h include/Reg.h include/testBench.h include/ULA.h

SOURCES = src/main.cpp src/Adder.cpp src/And.cpp src/B_Reg.cpp src/DataMem.cpp src/Ex_Mem.cpp src/Ext_16to32.cpp src/Id_Ex.cpp src/If_Id.cpp src/InstMem.cpp src/Mem_Wb.cpp src/Mux2x.cpp src/Mux2x5b.cpp src/P_C.cpp src/Reg.cpp src/testBench.cpp src/ULA.cpp

DEPENDENCIES = Makefile $(HEADERS) $(SOURCES)

LIBS = -lm -lsystemc

#nome do executável
TESTS = bin/teste

all: $(TESTS)
	./$(TESTS)
	#@make cmp_result

$(TESTS): $(DEPENDENCIES)
	g++ -Wfatal-errors -std=c++11 -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) -Wl,-rpath=$(SYSTEMC)lib-$(SYSTEMC_ARCH) $(LIBS)

