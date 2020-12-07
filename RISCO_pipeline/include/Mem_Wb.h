#ifndef MEM_WB_H
#define MEM_WB_H

#include <systemc.h>

/**
* @file Mem_Wb.h
* @brief Implementação do buffer do estágio acesso a memória/write back
* @author Kaio Henrique de Sousa
* @since 13/11/2020
*/

SC_MODULE(Mem_Wb){
	sc_in< bool > clk, reset, valid;
	sc_in< bool > WB0;
	sc_in< bool > WB1;
	sc_in< sc_bv<32> > dataOut, ulaResult;
	sc_in< sc_bv<5> > addressWriteReg;

	sc_out< bool > WB0O;
	sc_out< bool > WB1O;
	sc_out< sc_bv<32> > dataOutO, ulaResultO;
	sc_out< sc_bv<5> > addressWriteRegO;
	sc_out< bool > clk_out;

//-----------Internal variables-------------------
	bool tWB0;
	bool tWB1;
	sc_bv<32> tdataOut, tulaResult;
	sc_bv<5> taddressWriteReg;
	bool tclk_out;

	void write();
	void read();
	
	SC_CTOR(Mem_Wb){
		SC_METHOD(write);
		sensitive << clk.pos();
		SC_METHOD(read);
		sensitive << clk.neg();
	}
};

#endif