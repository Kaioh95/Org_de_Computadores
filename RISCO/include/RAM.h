#ifndef RAM_H
#define RAM_H

#include <systemc.h>

#define DATA_WIDTH	32 
#define ADDR_WIDTH	32
#define RAM_DEPTH	2048

/**
* @file RAM.h
* @brief Implementação de uma Memória
* @author Kaio Henrique de Sousa
* @since 19/10/2020
*/

SC_MODULE (RAM) {
	sc_in<sc_bv<ADDR_WIDTH> > address ;
	sc_in< sc_bv<DATA_WIDTH> > data_in;
	sc_in< bool > clk;
	sc_in< bool > MemW;
	sc_in< bool > MemR;

	sc_out< sc_bv<DATA_WIDTH> > data_out;

//-----------Internal variables-------------------
	sc_int< DATA_WIDTH > mem[RAM_DEPTH];

	void write_mem();
	void read_mem();

	SC_CTOR(RAM) {
		SC_METHOD (read_mem);
		sensitive << clk.neg();

		SC_METHOD (write_mem);
		sensitive << clk.pos();
	}

};

#endif