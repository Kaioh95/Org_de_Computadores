
SYSTEMC_ARCH=linux64
SYSTEMC=/usr/local/systemc-2.3.1/

LIB_DIRS=$(SYSTEMC)lib-$(SYSTEMC_ARCH)

INCLUDE_DIRS = -I. -I$(SYSTEMC)include -I include

HEADERS = include/Ext_26to32.h include/Ext_16to32.h include/Mux2xv1.h include/Mux2x.h include/Mux4x.h include/And_or.h include/P_C.h include/RegIR.h include/RegWithW.h include/RegNeg.h include/Reg.h include/B_Reg.h include/RAM.h include/ULA.h include/testBench.h

SOURCES = src/main.cpp src/Ext_26to32.cpp src/Ext_16to32.cpp src/Mux2xv1.cpp src/Mux2x.cpp src/Mux4x.cpp src/And_or.cpp src/P_C.cpp src/RegIR.cpp src/RegWithW.cpp src/RegNeg.cpp src/Reg.cpp src/B_Reg.cpp src/RAM.cpp src/ULA.cpp src/testBench.cpp

DEPENDENCIES = Makefile $(HEADERS) $(SOURCES)

LIBS = -lm -lsystemc

#nome do executável
TESTS = bin/teste

all: $(TESTS)
	./$(TESTS)
	#@make cmp_result

$(TESTS): $(DEPENDENCIES)
	g++ -Wfatal-errors -std=c++11 -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) -Wl,-rpath=$(SYSTEMC)lib-$(SYSTEMC_ARCH) $(LIBS)

