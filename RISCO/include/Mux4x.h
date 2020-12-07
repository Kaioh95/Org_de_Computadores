#ifndef MUX4x_H
#define MUX4x_H

#include <systemc.h>

/**
* @file Mux4x.h
* @brief Multiplexador de quatro entradas
* @author Kaio Henrique de Sousa
* @since 03/11/2020
*/

SC_MODULE(Mux4x){
	sc_in< sc_bv<32> > data0, data1, data2;
	sc_in< sc_bv<2> > x4Sel;
	sc_out< sc_bv<32> > outData;

	void mux4Process();

	SC_CTOR(Mux4x){
		SC_METHOD(mux4Process);
		sensitive << data0 << data1 << x4Sel;
	}
};

#endif