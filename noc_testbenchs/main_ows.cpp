#include <systemc.h>
#include "ows.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	ows *ows0;

	//Sinais do ows
	sc_signal< sc_bv<4> > ssel;
	sc_signal< sc_bv<4> > swrin;

	//Sinais do teste Bench
	sc_signal< bool > swrout;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->sel(ssel);
		tb0->wrin(swrin);
		tb0->wrout(swrout);

		tb0->clk(clk_sig);

		ows0 = new ows("ows0");
		ows0->sel(ssel);
		ows0->wrin(swrin);
		ows0->wrout(swrout);
	}

	~TopLevel(){
		delete tb0;
		delete ows0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}