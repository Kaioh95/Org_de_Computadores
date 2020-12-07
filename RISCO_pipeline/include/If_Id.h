#ifndef IF_ID_H
#define IF_ID_H

#include <systemc.h>

/**
* @file If_Id.h
* @brief Implementação do buffer do estágio de busca e decodificação de instruções
* @author Kaio Henrique de Sousa
* @since 13/11/2020
*/

SC_MODULE(If_Id){
	sc_in< bool > clk, reset, valid;
	sc_in< sc_bv<32> > Iin;
	sc_in< sc_bv<32> > jAddressIn;

	sc_out< sc_bv<6> > Iop;
	sc_out< sc_bv<5> > IaddressA;
	sc_out< sc_bv<5> > IaddressB0;
	sc_out< sc_bv<5> > IaddressB1;
	sc_out< sc_bv<16> > Iimmediate;
	sc_out< sc_bv<32> > jAddressOut;
	sc_out< bool > clk_out;

//-----------Internal variables-------------------
	sc_bv<6> tIop;
	sc_bv<5> tIaddressA;
	sc_bv<5> tIaddressB0;
	sc_bv<5> tIaddressB1;
	sc_bv<16> tIimmediate;
	sc_bv<32> tjAddressOut;
	bool tclk_out;

	void write();
	void read();
	
	SC_CTOR(If_Id){
		SC_METHOD(write);
		sensitive << clk.neg();
		SC_METHOD(read);
		sensitive << clk.pos();
	}
};

#endif