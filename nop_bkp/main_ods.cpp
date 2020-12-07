#include <systemc.h>
#include "ods.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	ods *ods0;

	//Sinais do ods
	sc_signal< sc_bv<10> > sdout;

	//Sinais do teste Bench
	sc_signal< sc_bv<4> > ssel;
	sc_signal< sc_bv<10> > sdin0;
	sc_signal< sc_bv<10> > sdin1;
	sc_signal< sc_bv<10> > sdin2;
	sc_signal< sc_bv<10> > sdin3;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->sel(ssel);
		tb0->din0(sdin0);
		tb0->din1(sdin1);
		tb0->din2(sdin2);
		tb0->din3(sdin3);
		tb0->dout(sdout);

		tb0->clk(clk_sig);

		ods0 = new ods("ods0");
		ods0->sel(ssel);
		ods0->din0(sdin0);
		ods0->din1(sdin1);
		ods0->din2(sdin2);
		ods0->din3(sdin3);
		ods0->dout(sdout);

	}

	~TopLevel(){
		delete tb0;
		delete ods0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}