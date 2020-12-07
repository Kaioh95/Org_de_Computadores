#ifndef EX_MEM_H
#define EX_MEM_H

#include <systemc.h>

/**
* @file Ex_Mem.h
* @brief Implementação do buffer do estágio execução/acesso a memória
* @author Kaio Henrique de Sousa
* @since 11/11/2020
*/

SC_MODULE(Ex_Mem){
	sc_in< bool > clk, reset, valid;
	sc_in< bool > WB0;
	sc_in< bool > WB1;
	sc_in< bool > M0;
	sc_in< bool > M1;
	sc_in< bool > M2;
	sc_in< sc_bv<32> > jAddress;
	sc_in< bool > zero;
	sc_in< sc_bv<32> > ulaResult, dataB;
	sc_in< sc_bv<5> > addressWriteReg;

	sc_out< bool > WB0O;
	sc_out< bool > WB1O;
	sc_out< bool > M0O;
	sc_out< bool > M1O;
	sc_out< bool > M2O;
	sc_out< sc_bv<32> > jAddressO;
	sc_out< bool > zeroO;
	sc_out< sc_bv<32> > ulaResultO, dataBO;
	sc_out< sc_bv<5> > addressWriteRegO;
	sc_out< bool > clk_out;

//-----------Internal variables-------------------
	bool tWB0;
	bool tWB1;
	bool tM0;
	bool tM1;
	bool tM2;
	sc_bv<32> tjAddress;
	bool tzero;
	sc_bv<32> tulaResult, tdataB;
	sc_bv<5> taddressWriteReg;
	bool tclk_out;

	void write();
	void read();
	
	SC_CTOR(Ex_Mem){
		SC_METHOD(write);
		sensitive << clk.neg();
		SC_METHOD(read);
		sensitive << clk.pos();
	}
};

#endif