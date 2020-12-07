#ifndef MUX2XV1_H
#define MUX2XV1_H

#include <systemc.h>

/**
* @file Mux2xv1.h
* @brief Multiplexador de duas entradas
* @author Kaio Henrique de Sousa
* @since 03/11/2020
*/

SC_MODULE(Mux2xv1){
	sc_in< sc_bv<5> > data0, data1;
	sc_in< bool > x2Sel;
	sc_out< sc_bv<5> > outData;

	void mux2Process();

	SC_CTOR(Mux2xv1){
		SC_METHOD(mux2Process);
		sensitive << data0 << data1 << x2Sel;
	}
};

#endif