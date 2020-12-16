#include <systemc.h>
#include "ic.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	ic *ic0;

	//Sinais do router
	sc_signal< bool > reqL;
	sc_signal< bool > reqN;
	sc_signal< bool > reqE;
	sc_signal< bool > reqS;
	sc_signal< bool > reqW;

	//Sinais do teste Bench
	sc_signal< bool > rst;
	sc_signal< sc_bv<8/2> > Xdest;
	sc_signal< sc_bv<8/2> > Ydest;
	sc_signal< bool > rok;
	sc_signal< bool > rd;
	sc_signal< bool > bop;
	sc_signal< bool > eop;
	sc_signal< bool > Lidle;
	sc_signal< bool > Nidle;
	sc_signal< bool > Eidle;
	sc_signal< bool > Sidle;
	sc_signal< bool > Widle;

	sc_signal< int > MODULE_ID;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->MODULE_ID(MODULE_ID);
		tb0->reqL(reqL);
		tb0->reqN(reqN);
		tb0->reqE(reqE);
		tb0->reqS(reqS);
		tb0->reqW(reqW);
		tb0->rst(rst);
		tb0->Xdest(Xdest);
		tb0->Ydest(Ydest);
		tb0->rok(rok);
		tb0->rd(rd);
		tb0->bop(bop);
		tb0->eop(eop);
		tb0->Lidle(Lidle);
		tb0->Nidle(Nidle);
		tb0->Eidle(Eidle);
		tb0->Sidle(Sidle);
		tb0->Widle(Widle);

		tb0->clk(clk_sig);

		ic0 = new ic("ic0");
		ic0->MODULE_ID(MODULE_ID);
		ic0->reqL(reqL);
		ic0->reqN(reqN);
		ic0->reqE(reqE);
		ic0->reqS(reqS);
		ic0->reqW(reqW);
		ic0->rst(rst);
		ic0->Xdest(Xdest);
		ic0->Ydest(Ydest);
		ic0->rok(rok);
		ic0->rd(rd);
		ic0->bop(bop);
		ic0->eop(eop);
		ic0->Lidle(Lidle);
		ic0->Nidle(Nidle);
		ic0->Eidle(Eidle);
		ic0->Sidle(Sidle);
		ic0->Widle(Widle);

		ic0->clk(clk_sig);

	}

	~TopLevel(){
		delete tb0;
		delete ic0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}