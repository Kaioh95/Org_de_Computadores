#include <systemc.h>

/**
* @file irs.cpp
* @details Implementação a leitura usada nos
* canais de input para selecionar um comando
* de leitura. Esta entidade é apenas um
* multiplexador 4 para 1.
* @author Kaio Henrique de Sousa
* @since 29/11/2020
*/

SC_MODULE(irs){
	sc_in< sc_bv<4> > sel;		//seletor
	sc_in< sc_bv<4> > rdin;		//comandos read
	sc_out< bool > rdout;	//comando selecionado

	void sel_proccess(){
		if(sel.read()[0] == 1)
			rdout.write(rdin.read()[0]);
		else if(sel.read()[1] == 1)
			rdout.write(rdin.read()[1]);
		else if(sel.read()[2] == 1)
			rdout.write(rdin.read()[2]);
		else if(sel.read()[3] == 1)
			rdout.write(rdin.read()[3]);
		else
			rdout.write(0);
	}

	SC_CTOR(irs){
		SC_METHOD(sel_proccess);
		sensitive << sel << rdin;
	}
};