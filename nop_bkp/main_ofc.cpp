#include <systemc.h>
#include "ofc.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	ofc *ofc0;

	//Sinais do ofc
	sc_signal< bool > sval;
	sc_signal< bool > srd;

	//Sinais do teste Bench
	sc_signal< bool > srst;
	sc_signal< bool > sret;
	sc_signal< bool > srok;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->rst(srst);
		tb0->val(sval);
		tb0->ret(sret);
		tb0->rd(srd);
		tb0->rok(srok);

		tb0->clk(clk_sig);

		ofc0 = new ofc("ofc0");
		ofc0->rst(srst);
		ofc0->val(sval);
		ofc0->ret(sret);
		ofc0->rd(srd);
		ofc0->rok(srok);

		ofc0->clk(clk_sig);
	}

	~TopLevel(){
		delete tb0;
		delete ofc0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}