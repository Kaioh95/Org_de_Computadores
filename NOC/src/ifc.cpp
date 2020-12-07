#include <systemc.h>

/**
* @file ifc.cpp
* @details Controle responsável por regular
* fluxo dos flits no canais de input.
* @author Kaio Henrique de Sousa
* @since 30/11/2020
*/

SC_MODULE(ifc){
	sc_in< bool > clk, rst;
	sc_in< bool > val;		//validar dado
	sc_out< bool > ret;		//credit or acknowledgment

	// interface FIFO
	sc_out< bool > wr;		//comando para escrever dado na FIFO
	sc_in< bool > wok;		//FIFO não está cheia
	sc_in< bool > rd;		//comando para ler dado da FIFO
	sc_in< bool > rok;		//FIFO não está vazia

//---------------Variáveis Internas----------------------
	enum states{S0, S1, S2};		//estados da máquina de estados do handshake
	sc_signal< states > state_reg;	//estado atual
	sc_signal< states > next_state;	//prox estado

	void fsm_p(){
		switch(state_reg){
			// Espera um dado novo válido e se a FIFO
			// não está cheia (wok=1), prossegui para
			// o estado S1 para receber o dado.
			case S0:
				if(val.read() & wok.read())
					next_state = S1;
				else
					next_state = S0;
				break;
			// Escreve o dado na FIFO e volta para o estado S0
			// se val=0, caso contrário prossegui para o estado S2.
			case S1:
				if(!val.read())
					next_state = S0;
				else
					next_state = S2;
				break;
			// Espera até que val seja 0 para completar a tranferência.
			case S2:
				if(!val.read())
					next_state = S0;
				else
					next_state = S2;
				break;
			default:
				next_state = S0;
				break;
		}
	}

	void outputs(){
		switch(state_reg){
			// nada a fazer
			case S0:
				ret.write(0);
				wr.write(0);
				break;
			// Escreve o dado na FIFO
			case S1:
				ret.write(1);
				wr.write(1);
				break;
			//  Cotinua buscando dado enquanto val for 1.
			case S2:
				ret.write(1);
				wr.write(0);
				break;
			default:
				ret.write(0);
				wr.write(0);
				break;
		}
	}

	void curstate(){
		if(rst.read())
			state_reg = S0;
		else if(clk.event())
			state_reg = next_state;
	}

	SC_CTOR(ifc){
		SC_METHOD(fsm_p);
		sensitive << state_reg << val << wok;
		SC_METHOD(outputs);
		sensitive << state_reg;
		SC_METHOD(curstate);
		sensitive << clk.pos() << rst;
	}
};