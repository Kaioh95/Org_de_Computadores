#include <systemc.h>
#include "arb_rr.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	arb_rr *a_rr0;

	//Sinais do árbitro
	sc_signal< bool > sidle;
	sc_signal< sc_bv<4> > sG;

	//Sinais do teste Bench
	sc_signal< bool > srst;
	sc_signal< sc_bv<4> > sR;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->rst(srst);
		tb0->R(sR);
		tb0->G(sG);
		tb0->idle(sidle);

		tb0->clk(clk_sig);

		a_rr0 = new arb_rr("a_rr0");
		a_rr0->rst(srst);
		a_rr0->R(sR);
		a_rr0->G(sG);
		a_rr0->idle(sidle);

		a_rr0->clk(clk_sig);
	}

	~TopLevel(){
		delete tb0;
		delete a_rr0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}