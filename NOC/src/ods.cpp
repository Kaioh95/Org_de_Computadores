#include <systemc.h>

#define SWITCH_TYPE "LOGIC"
#define WIDTH 10
/**
* @file ods.cpp
* @details Implementa a chave usada nos canais
* de output para selecionar um dado de um canal 
* de input concedido.
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(ods){
	sc_in< sc_bv<4> > sel;
	sc_in< sc_bv<WIDTH> > din0;	//dado do canal 0
	sc_in< sc_bv<WIDTH> > din1; //dado do canal 1
	sc_in< sc_bv<WIDTH> > din2; //dado do canal 2
	sc_in< sc_bv<WIDTH> > din3; //dado do canal 3

	// canal de dados selecionado e bits de enquadramento
	sc_out< sc_bv<WIDTH> > dout;

	void ods_logic(){
		if(sel.read()[0])
			dout = din0;
		else if(sel.read()[1])
			dout = din1;
		else if(sel.read()[2])
			dout = din2;
		else if(sel.read()[3])
			dout = din3;
		else
			dout = 0;
	}

	SC_CTOR(ods){
		SC_METHOD(ods_logic);
		sensitive << sel << din0 << din1 << din2 << din3;	
	}

};