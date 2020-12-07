#ifndef EXT_26TO32_H
#define EXT_26TO32_H

#include <systemc.h>

/**
* @file Ext_26to32.h
* @brief Extensor de Sinal 26 bits para 32
* @author Kaio Henrique de Sousa
* @since 04/11/2020
*/

SC_MODULE(Ext_26to32){
	sc_in< sc_bv<26> > extdata_in;
	sc_out< sc_bv<32> > extdata_out;

	void extend();

	SC_CTOR(Ext_26to32){
		SC_METHOD(extend);
		sensitive << extdata_in;
	}
};

#endif