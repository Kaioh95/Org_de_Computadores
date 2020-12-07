#ifndef EXT_16TO32_H
#define EXT_16TO32_H

#include <systemc.h>

SC_MODULE(Ext_16to32){
	sc_in< sc_bv<16> > extdata_in;
	sc_out< sc_bv<32> > extdata_out;

	void extend();

	SC_CTOR(Ext_16to32){
		SC_METHOD(extend);
		sensitive << extdata_in;
	}
};

#endif