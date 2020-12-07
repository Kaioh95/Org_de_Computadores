#ifndef MUX2x_H
#define MUX2x_H

#include <systemc.h>

/**
* @file Mux2x.h
* @brief Multiplexador de duas entradas
* @author Kaio Henrique de Sousa
* @since 03/11/2020
*/

SC_MODULE(Mux2x){
	sc_in< sc_bv<32> > data0, data1;
	sc_in< bool > x2Sel;
	sc_out< sc_bv<32> > outData;

	void mux2Process();

	SC_CTOR(Mux2x){
		SC_METHOD(mux2Process);
		sensitive << data0 << data1 << x2Sel;
	}
};

#endif