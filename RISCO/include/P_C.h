#ifndef P_C_H
#define P_C_H

#include <systemc.h>

/**
* @file P_C.h
* @brief Implementação da Parte de Controle
* @author Kaio Henrique de Sousa
* @since 24/10/2020
*/

SC_MODULE(P_C){
	sc_in< sc_bv<6> > op;
	sc_in< bool > clk, reset, valid;

	sc_out< bool > PCwCond, PCw, IorD, MemRead, MemWrite, IRWrite, RegDst, MemtoReg, RegWrite, SrcA;
	sc_out< sc_bv<2> > SrcB, PCSrc;
	sc_out< sc_bv<3> > ULAOp;

	enum states {init, instFetch, instDec, instDecode, opR1, opR2, opI1, opI2, opMeM_JR, opL1, opL2, opS, opBeq, opJ, opJr2};
	sc_signal<states> mstate;

//-----------Methods-------------------
	void proxEstado();
	void pc_outputs();

//-----------Contructor-------------------
	SC_CTOR(P_C){
		SC_METHOD(proxEstado);
		sensitive << clk.pos(); 
		SC_METHOD(pc_outputs)
		sensitive << mstate << op;
	}
};

#endif
