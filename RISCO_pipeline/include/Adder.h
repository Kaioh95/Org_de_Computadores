#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

/**
* @file Adder.h
* @brief Implementação de um somador
* @author Kaio Henrique de Sousa
* @since 13/11/2020
*/

SC_MODULE(Adder){
	sc_in< sc_bv<32> > Adata_in;
	sc_in< sc_bv<32> > Bdata_in;
	sc_out< sc_bv<32> > data_out;

	//Internal variables
	sc_int<32> vAdata_in, vBdata_in;
	sc_int<32> vdata_out;

	void add();

	SC_CTOR(Adder){
		SC_METHOD(add);
		sensitive << Adata_in << Bdata_in;
	}
};


#endif