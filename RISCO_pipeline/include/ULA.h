#ifndef _ULA_H_
#define _ULA_H_

#include <systemc.h>

/**
* @file ULA.h
* @brief Unidade Lógico/Aritmética
* @author Kaio Henrique de Sousa
* @since 18/10/2020
*/

SC_MODULE(ULA){
	sc_in< sc_bv<32> > A;
	sc_in< sc_bv<32> > B;
	sc_in< sc_bv<3> > opSel;
	sc_out< sc_bv<32> > result;
	sc_out< bool > z;

	void ula_op();

	SC_CTOR(ULA){
		SC_METHOD(ula_op);
		sensitive << A << B << opSel;
	}
};

#endif