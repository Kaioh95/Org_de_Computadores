#ifndef P_C_H
#define P_C_H

#include <systemc.h>

/**
* @file P_C.h
* @brief Implementação do Controle
* @author Kaio Henrique de Sousa
* @since 14/11/2020
*/

SC_MODULE(P_C){
	sc_in< sc_bv<6> > op;
	sc_in< bool > clk, reset, valid;

	sc_out< bool > WB0, WB1, EX0, EX1;
	sc_out< bool > M0, M1, M2;
	sc_out< sc_bv<3> > ulaOp;

//-----------Internal Variable-------------------
	sc_bv<3> nextOP;

//-----------Methods-------------------
	void pc_outputs();

//-----------Contructor-------------------
	SC_CTOR(P_C){
		SC_METHOD(pc_outputs)
		sensitive << op;
	}
};

#endif
