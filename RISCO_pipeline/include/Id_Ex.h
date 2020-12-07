#ifndef ID_EX_H
#define ID_EX_H

#include <systemc.h>

/**
* @file Id_Ex.h
* @brief Implementação do buffer do estágio decodificação/execução
* @author Kaio Henrique de Sousa
* @since 13/11/2020
*/

SC_MODULE(Id_Ex){
	sc_in< bool > clk, reset, valid;
	sc_in< bool > WB0;
	sc_in< bool > WB1;
	sc_in< bool > M0;
	sc_in< bool > M1;
	sc_in< bool > M2;
	sc_in< bool > EX0;
	sc_in< bool > EX1;
	sc_in< sc_bv<3> > ulaOp;
	sc_in< sc_bv<32> > jAddress;
	sc_in< sc_bv<32> > dataA, dataB;
	sc_in< sc_bv<32> > immediate;
	sc_in< sc_bv<5> > addressA, addressB;

	sc_out< bool > WB0O;
	sc_out< bool > WB1O;
	sc_out< bool > M0O;
	sc_out< bool > M1O;
	sc_out< bool > M2O;
	sc_out< bool > EX0O;
	sc_out< bool > EX1O;
	sc_out< sc_bv<3> > ulaOpO;
	sc_out< sc_bv<32> > jAddressO;
	sc_out< sc_bv<32> > dataAO, dataBO;
	sc_out< sc_bv<32> > immediateO;
	sc_out< sc_bv<5> > addressAO, addressBO;
	sc_out< bool > clk_out;

//-----------Internal variables-------------------
	bool tWB0;
	bool tWB1;
	bool tM0;
	bool tM1;
	bool tM2;
	bool tEX0;
	bool tEX1;;
	sc_bv<3> tulaOp;
	sc_bv<32> tjAddress;
	sc_bv<32> tdataA, tdataB;
	sc_bv<16> timmediate;
	sc_bv<5> taddressA, taddressB;
	bool tclk_out;

	void write();
	void read();
	
	SC_CTOR(Id_Ex){
		SC_METHOD(write);
		sensitive << clk.pos();
		SC_METHOD(read);
		sensitive << clk.neg();
	}
};

#endif