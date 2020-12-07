#ifndef MUX2X5B_H
#define MUX2X5B_H

#include <systemc.h>

/**
* @file Mux2x5b.h
* @brief Multiplexador de duas entradas de 5 bits
* @author Kaio Henrique de Sousa
* @since 03/11/2020
*/

SC_MODULE(Mux2x5b){
	sc_in< sc_bv<5> > data0, data1;
	sc_in< bool > x2Sel;
	sc_out< sc_bv<5> > outData;

	void mux2Process();

	SC_CTOR(Mux2x5b){
		SC_METHOD(mux2Process);
		sensitive << data0 << data1 << x2Sel;
	}
};

#endif