#ifndef INSTMEM_H
#define INSTMEM_H

#include <systemc.h>

#define DATA_WIDTH	32 
#define ADDR_WIDTH	32
#define RAM_DEPTH	2048

/**
* @file InstMem.h
* @brief Implementação da Memória de instruções
* @author Kaio Henrique de Sousa
* @since 13/11/2020
*/

SC_MODULE (InstMem) {
	sc_in< sc_bv<ADDR_WIDTH> > address ;
	sc_in< sc_bv<DATA_WIDTH> > data_in;
	sc_in< bool > clk;
	sc_in< bool > MemW;

	sc_out< sc_bv<DATA_WIDTH> > data_out;

//-----------Internal variables-------------------
	sc_int< DATA_WIDTH > mem[RAM_DEPTH];

	void write_mem();
	void read_mem();

	SC_CTOR(InstMem) {
		SC_METHOD (read_mem);
		sensitive << clk.pos();

		SC_METHOD (write_mem);
		sensitive << clk.pos();
	}

};

#endif