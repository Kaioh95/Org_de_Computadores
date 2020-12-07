#ifndef _REGWITHW_H
#define _REGWITHW_H

#include <systemc.h>

/**
* @file RegWithW.h
* @brief Implementação de um registrador com sinal para escrita
* @author Kaio Henrique de Sousa
* @since 22/10/2020
*/

SC_MODULE(RegWithW){
	sc_in< bool > clk, reset, w;
	sc_in< sc_bv<32> > Iin;
	sc_out< sc_bv<32> > Iout;

	void mainProcess();
	
	SC_CTOR(RegWithW){
		SC_METHOD(mainProcess);
		sensitive << clk.pos();
	}
};

#endif