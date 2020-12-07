#include <systemc.h>
#include "ppe.cpp"
#include "pg.cpp"

#define N 4
/**
* @file arb_rr.cpp
* @details Um árbitro round-robin  baseado em um codificador de prioridades
* e em um gerador de prioridade circular que atualiza a ordem prioridades a cada
* ciclo de arbitragem. 
* É garantido que concessão de request dada no ciclo atual de arbitragem,
* terá o nível de prioridade mais baixo no próximo.
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(arb_rr){
	sc_in< bool > clk, rst;
	// Sinais de arbitragem
	sc_in< sc_bv<N> > R; 	//request
	sc_out< sc_bv<N> > G;	// Concessão
	sc_out< bool > idle; 	// status

	sc_signal< sc_bv<N> > P;		//Prioridades
	sc_signal< sc_bv<N> > Grant;	// Sinais de concessão

	ppe *ppe0;
	pg * pg0;

	void outputs(){
		G.write(Grant);
	}

	SC_CTOR(arb_rr){
		ppe0 = new ppe("ppe0");
		ppe0->rst(rst);
		ppe0->R(R);
		ppe0->P(P);
		ppe0->G(Grant);
		ppe0->idle(idle);
		ppe0->clk(clk);

		pg0 = new pg("pg0");
		pg0->rst(rst);
		pg0->G(Grant);
		pg0->P(P);
		pg0->clk(clk);

		SC_METHOD(outputs);
		sensitive << Grant;
	}

	~arb_rr(){
		delete ppe0;
		delete pg0;
	}

};