#include <systemc.h>

#define SWITCH_TYPE "LOGIC"
/**
* @file ods.cpp
* @details Implementa a chave usada nos canais
* de output para selecionar um comando write recebido
* de um canal de input concedido.
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(ows){
	sc_in< sc_bv<4> > sel;	//input selector
	sc_in< sc_bv<4> > wrin;	//wr comando de canais de input
	sc_out< bool > wrout;	//comando write selecionado

	void ows_logic(){
		if(sel.read()[0])
			wrout = wrin.read()[0];
		else if(sel.read()[1])
			wrout = wrin.read()[1];
		else if(sel.read()[2])
			wrout = wrin.read()[2];
		else if(sel.read()[3])
			wrout = wrin.read()[3];
		else
			wrout = 0;
	}

	SC_CTOR(ows){
		SC_METHOD(ows_logic);
		sensitive << sel << wrin;
	}
};