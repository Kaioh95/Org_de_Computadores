
SYSTEMC_ARCH=linux64
SYSTEMC=/usr/local/systemc-2.3.1/

LIB_DIRS=$(SYSTEMC)lib-$(SYSTEMC_ARCH)

INCLUDE_DIRS = -I. -I$(SYSTEMC)include

SOURCES = src/main.cpp src/Router.cpp src/X.cpp src/Xout.cpp src/ows.cpp src/ods.cpp src/ofc.cpp src/oc.cpp src/arb_rr.cpp src/ppe.cpp src/pg.cpp src/Xin.cpp src/dout_slice.cpp src/ifc.cpp src/Fifo.cpp src/irs.cpp src/ic.cpp src/routing_xy.cpp src/req_reg.cpp src/testB.cpp

DEPENDENCIES = Makefile $(SOURCES)

LIBS = -lm -lsystemc

#nome do executável
TESTS = bin/NoC

all: $(TESTS)
	./$(TESTS)
	#@make cmp_result

$(TESTS): $(DEPENDENCIES)
	g++ -w -Wfatal-errors -std=c++11 -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L$(LIB_DIRS) -Wl,-rpath=$(SYSTEMC)lib-$(SYSTEMC_ARCH) $(LIBS)
