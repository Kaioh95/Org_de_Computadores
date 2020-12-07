#include <systemc.h>

#define N 4
/**
* @file pg.cpp
* @details Função que determina os próximos
* níveis de prioridade por meio da implementaçãp
* de um arbitrário round-robin. 
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(pg){
	sc_in< bool > clk, rst;
	sc_in< sc_bv<N> > G;	//concessões
	sc_out< sc_bv<N> > P;	//prioridade

	sc_signal< bool > update_register;
	sc_signal< sc_bv<N> > grating;		//resquest concedida
	sc_signal< sc_bv<N> > Gdelayed;		//G atrasada em um ciclo
	sc_bv<N> nextP;						//próximas prioridades
	sc_signal< sc_bv<N> > Preg;			//registrador de prioridades

	// Flip-flop que guarda o estado de G por um ciclo
	void flip_flop(){
		if(rst.read())
			Gdelayed = 0;
		else if(clk.event())
			Gdelayed = G;
	}

	void enable_reg_update(){
		// determina se há algum request concedido no ciclo anterior
		grating = G.read() & (~Gdelayed.read());

		// Se houve request concedido no último ciclo, então é habilitado o update do registrador de prioridade
		bool tmp = 0;
		for(int i = N-1; i>=0; i--){
			tmp = tmp | grating.read()[i];
		}
		update_register = tmp;

		// Se G="0001" então nextP="0010". Essa rotação irá
		// garantir que o request atual concedido terá o menor
		// nível de prioridade na próxima arbitragem.
		for(int i = N-1; i>=0; i--){
			nextP[i] = G.read()[(i-1) % N];
		}
	}

	// É resetado quando o bit menos significativo é 1 e os outros 0,
	// e é atualizado a cada ciclo de arbitragem com o valor determinado para nextP.
	void reg_update(){
		if(rst.read()){
			Preg = "0001";
		}
		else if(clk.event()){
			if(update_register == 1)
				Preg = nextP;
		}
	}

	void outputs(){
		P.write(Preg);
	}

	SC_CTOR(pg){
		SC_METHOD(flip_flop);
		sensitive << clk.pos() << rst;
		SC_METHOD(enable_reg_update);
		sensitive << G << Gdelayed << grating;
		SC_METHOD(reg_update);
		sensitive << clk.pos() << rst;
		SC_METHOD(outputs);
		sensitive << Preg;
	}

};