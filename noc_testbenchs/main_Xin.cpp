#include <systemc.h>
#include "Xin.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	Xin *Xin0;

	//Sinais do router
	sc_signal< bool > in_ret;
	sc_signal< bool > x_reqL;
	sc_signal< bool > x_reqN;
	sc_signal< bool > x_reqE;
	sc_signal< bool > x_reqS;
	sc_signal< bool > x_reqW;
	sc_signal< bool > x_rok;
	sc_signal< sc_bv<10> > x_dout;

	//Sinais do teste Bench
	sc_signal< bool > rst;
	sc_signal< sc_bv<10> > in_data;
	sc_signal< bool > in_val;
	sc_signal< sc_bv<4> > x_rd;
	sc_signal< sc_bv<4> > x_gnt;
	sc_signal< bool > x_Lidle;
	sc_signal< bool > x_Nidle;
	sc_signal< bool > x_Eidle;
	sc_signal< bool > x_Sidle;
	sc_signal< bool > x_Widle;

	sc_signal< int > MODULE_ID{"MODULE_ID", 1};

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->rst(rst);
		tb0->in_ret(in_ret);
		tb0->x_reqL(x_reqL);
		tb0->x_reqN(x_reqN);
		tb0->x_reqE(x_reqE);
		tb0->x_reqS(x_reqS);
		tb0->x_reqW(x_reqW);
		tb0->x_rok(x_rok);
		tb0->x_dout(x_dout);
		tb0->in_data(in_data);
		tb0->in_val(in_val);
		tb0->x_rd(x_rd);
		tb0->x_gnt(x_gnt);
		tb0->x_Lidle(x_Lidle);
		tb0->x_Nidle(x_Nidle);
		tb0->x_Eidle(x_Eidle);
		tb0->x_Sidle(x_Sidle);
		tb0->x_Widle(x_Widle);

		tb0->clk(clk_sig);

		Xin0 = new Xin("Xin0");
		Xin0->MODULE_ID(MODULE_ID);
		Xin0->rst(rst);
		Xin0->in_ret(in_ret);
		Xin0->x_reqL(x_reqL);
		Xin0->x_reqN(x_reqN);
		Xin0->x_reqE(x_reqE);
		Xin0->x_reqS(x_reqS);
		Xin0->x_reqW(x_reqW);
		Xin0->x_rok(x_rok);
		Xin0->x_dout(x_dout);
		Xin0->in_data(in_data);
		Xin0->in_val(in_val);
		Xin0->x_rd(x_rd);
		Xin0->x_gnt(x_gnt);
		Xin0->x_Lidle(x_Lidle);
		Xin0->x_Nidle(x_Nidle);
		Xin0->x_Eidle(x_Eidle);
		Xin0->x_Sidle(x_Sidle);
		Xin0->x_Widle(x_Widle);

		Xin0->clk(clk_sig);

	}

	~TopLevel(){
		delete tb0;
		delete Xin0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}