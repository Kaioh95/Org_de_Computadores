#ifndef _REGIT_H
#define _REGIT_H

#include <systemc.h>

/**
* @file RegIR.h
* @brief Implementação de um registrador com sinal para escrita para guardar instruções
* @author Kaio Henrique de Sousa
* @since 22/10/2020
*/

SC_MODULE(RegIR){
	sc_in< bool > clk, reset, w;
	sc_in< sc_bv<32> > Iin;

	sc_out< sc_bv<6> > Iop;
	sc_out< sc_bv<5> > IaddressA;
	sc_out< sc_bv<5> > IaddressB0;
	sc_out< sc_bv<5> > IaddressB1;
	sc_out< sc_bv<16> > Iimmediate;
	sc_out< sc_bv<26> > Ipcmux;

//-----------Internal variables-------------------
	sc_bv<6> tIop;
	sc_bv<5> tIaddressA;
	sc_bv<5> tIaddressB0;
	sc_bv<5> tIaddressB1;
	sc_bv<16> tIimmediate;
	sc_bv<26> tIpcmux;

	void mainProcess();
	
	SC_CTOR(RegIR){
		SC_METHOD(mainProcess);
		sensitive << clk.neg() << Iop;
	}
};

#endif