#ifndef B_REG
#define B_REG
#include <systemc.h>

#define BDATA_WIDTH	32
#define BADDR_WIDTH	5
#define BANK_DEPTH 	32

/**
* @file B_Reg.h
* @brief Banco de Registradores
* @author Kaio Henrique de Sousa
* @since 19/10/2020
*/


SC_MODULE(B_Reg){
	sc_in< sc_bv<BADDR_WIDTH> > address_A;
	sc_in< sc_bv<BADDR_WIDTH> > address_B;

	sc_in< sc_bv<BADDR_WIDTH> > address_data;
	sc_in< sc_bv<BDATA_WIDTH> > data_in;
	
	sc_in<bool> wReg;
	sc_in<bool> clk;
	
	sc_out< sc_bv<BDATA_WIDTH> > data_A;
	sc_out< sc_bv<BDATA_WIDTH> > data_B;
	//sc_inout_rv< BDATA_WIDTH > data_1;

//-----------Internal variables-------------------
 	sc_bv< BDATA_WIDTH > bank[BANK_DEPTH];

//-----------Methods------------------------------
	void READ_A();
	void READ_B();
	void WRITE_DATA();

//-----------Constructor--------------------------
	SC_CTOR(B_Reg){
		SC_METHOD(READ_A);
		sensitive << clk.pos();
		
		SC_METHOD(READ_B);
		sensitive << clk.pos();

		SC_METHOD(WRITE_DATA);
		sensitive << clk.pos();
 	}
 };

 #endif