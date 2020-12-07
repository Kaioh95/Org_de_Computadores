#ifndef _REGNEG_H
#define _REGNEG_H

#include <systemc.h>

/**
* @file RegNeg.h
* @brief Implementação de um registrador com clock negativo
* @author Kaio Henrique de Sousa
* @since 22/10/2020
*/

SC_MODULE(RegNeg){
	sc_in< bool > clk, reset;
	sc_in< sc_bv<32> > Din;
	sc_out< sc_bv<32> > Dout;

	void mainProcess();
	
	SC_CTOR(RegNeg){
		SC_METHOD(mainProcess);
		sensitive << clk.neg() << Din;
	}
};

#endif