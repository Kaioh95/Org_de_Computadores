#include <systemc.h>
#include "arb_rr.cpp"

#define ARBITER_TYPE "ROUND-ROBIN"
#define N 4
/**
* @file oc.cpp
* @details Controle responsável por reservar o uso
* do canal de output associado. O controle é baseado
* no árbitro que recebe request e, baseado em um
* algoritmo de arbitragem, seleciona um request para
* concessão. Um concessão é mantida em alto nível
* enquanto o request for igual a 1.
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(oc){
	sc_in< bool > clk, rst;
	// Sinais de arbitragem
	sc_in< sc_bv<N> > R;	// Request
	sc_out< sc_bv<N> > G;	// Concessões
	sc_out< bool > idle;

	sc_signal< sc_bv<N> > Grant;

	arb_rr *arb0;

	void g_out(){
		G.write(Grant.read() & R.read());
	}

	SC_CTOR(oc){
		arb0 = new arb_rr("arb0");
		arb0->R(R);
		arb0->clk(clk);
		arb0->rst(rst);
		arb0->G(Grant);
		arb0->idle(idle);
	
		SC_METHOD(g_out);
		sensitive << Grant << R;
	}

	~oc(){
		delete arb0;
	}

};