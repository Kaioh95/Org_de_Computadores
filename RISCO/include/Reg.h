#ifndef _REG_H
#define _REG_H

#include <systemc.h>

/**
* @file Reg.h
* @brief Implementação de um registrador sem sinal para escrita
* @author Kaio Henrique de Sousa
* @since 22/10/2020
*/

SC_MODULE(Reg){
	sc_in< bool > clk, reset;
	sc_in< sc_bv<32> > Din;
	sc_out< sc_bv<32> > Dout;

	void mainProcess();
	
	SC_CTOR(Reg){
		SC_METHOD(mainProcess);
		sensitive << clk.pos();
	}
};

#endif