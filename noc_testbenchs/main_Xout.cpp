#include <systemc.h>
#include "Xout.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	Xout *Xout0;

	//Sinais do Xout
	sc_signal< sc_bv<10> > out_data;
	sc_signal< bool > out_val;
	sc_signal< bool > x_rd;
	sc_signal< sc_bv<4> > x_gnt;
	sc_signal< bool > x_idle;

	//Sinais do teste Bench
	sc_signal< bool > rst;
	sc_signal< bool > out_ret;
	sc_signal< sc_bv<4> > x_req;
	sc_signal< sc_bv<4> > x_rok;
	sc_signal< sc_bv<10> > x_din0;
	sc_signal< sc_bv<10> > x_din1;
	sc_signal< sc_bv<10> > x_din2;
	sc_signal< sc_bv<10> > x_din3;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->out_data(out_data);
		tb0->out_val(out_val);
		tb0->x_rd(x_rd);
		tb0->x_gnt(x_gnt);
		tb0->x_idle(x_idle);
		tb0->rst(rst);
		tb0->out_ret(out_ret);
		tb0->x_req(x_req);
		tb0->x_rok(x_rok);
		tb0->x_din0(x_din0);
		tb0->x_din1(x_din1);
		tb0->x_din2(x_din2);
		tb0->x_din3(x_din3);

		tb0->clk(clk_sig);

		Xout0 = new Xout("Xout0");
		Xout0->out_data(out_data);
		Xout0->out_val(out_val);
		Xout0->x_rd(x_rd);
		Xout0->x_gnt(x_gnt);
		Xout0->x_idle(x_idle);
		Xout0->rst(rst);
		Xout0->out_ret(out_ret);
		Xout0->x_req(x_req);
		Xout0->x_rok(x_rok);
		Xout0->x_din0(x_din0);
		Xout0->x_din1(x_din1);
		Xout0->x_din2(x_din2);
		Xout0->x_din3(x_din3);

		Xout0->clk(clk_sig);

	}

	~TopLevel(){
		delete tb0;
		delete Xout0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}