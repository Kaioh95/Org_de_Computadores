#include <systemc.h>

#define FC_TYPE "HANDSHAKE"
/**
* @file ofc.cpp
* @details Controle responsável por regular o fluxo
* dos flits nos canais de output. Faz a adaptação entre
* o protocolo de controle interno (FIFO) e o protocolo de 
* controle de fluxo de link (handshake).
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(ofc){
	sc_in< bool > clk, rst;

	// interface Link
	sc_out< bool > val;	//validação de dado
	sc_in< bool > ret;	//retorno (credit ou acknowledgement)
	// interface FIFO 
	sc_out< bool > rd;	//comando read
	sc_in< bool > rok;	//FIFO não vazia

	enum states{S0, S1, S2};		//estados do handshake SFM
	sc_signal< states > state_reg;	//estado atual
	sc_signal< states > next_state;	//prox estado

	void n_state(){
		switch(state_reg){
			case S0:
				if(rok.read() & !ret.read())
					next_state = S1;
				else
					next_state = S0;
				break;
			case S1:
				if(ret.read())
					next_state = S2;
				else
					next_state = S1;
				break;
			case S2:
				if(rok.read() & !ret.read())
					next_state = S1;
				else
					next_state = S0;
				break;
			default:
				next_state = S0;
				break;
		}
	}

	void outputs(){
		switch(state_reg){
			case S0:
				val.write(0);
				rd.write(0);
				break;
			case S1:
				val.write(1);
				rd.write(0);
				break;
			case S2:
				val.write(0);
				rd.write(1);
				break;
			default:
				val.write(0);
				rd.write(0);
				break;
		}
	}

	void cur_state(){
		if(rst.read())
			state_reg = S0;
		else if(clk.event())
			state_reg = next_state;
	}

	SC_CTOR(ofc){
		SC_METHOD(n_state);
		sensitive << state_reg << ret << rok;
		SC_METHOD(outputs);
		sensitive << state_reg;
		SC_METHOD(cur_state);
		sensitive << clk.pos() << rst;
	}
};