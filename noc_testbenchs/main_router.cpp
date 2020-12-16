#include <systemc.h>
#include "Router.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	Router *router0;

//Sinais do router
	// Porta de comunicação local
	sc_signal< bool > Lin_ret;
	sc_signal< sc_bv<10> > Lout_data;
	sc_signal< bool > Lout_val;

	// Porta Norte de comunicação
	sc_signal< bool > Nin_ret;
	sc_signal< sc_bv<10> > Nout_data;
	sc_signal< bool > Nout_val;

	// Porta Leste de comunicação
	sc_signal< bool > Ein_ret;
	sc_signal< sc_bv<10> > Eout_data;
	sc_signal< bool > Eout_val;

	// Porta Sul de comunicação
	sc_signal< bool > Sin_ret;
	sc_signal< sc_bv<10> > Sout_data;
	sc_signal< bool > Sout_val;

	// Porta Oeste de comunicação
	sc_signal< bool > Win_ret;
	sc_signal< sc_bv<10> > Wout_data;
	sc_signal< bool > Wout_val;

//Sinais do teste Bench
	sc_signal< bool > rst;

	// Porta de comunicação local
	sc_signal< sc_bv<10> > Lin_data;
	sc_signal< bool > Lin_val;
	sc_signal< bool > Lout_ret;

	// Porta Norte de comunicação
	sc_signal< sc_bv<10> > Nin_data;
	sc_signal< bool > Nin_val;
	sc_signal< bool > Nout_ret;

	// Porta Leste de comunicação
	sc_signal< sc_bv<10> > Ein_data;
	sc_signal< bool > Ein_val;
	sc_signal< bool > Eout_ret;

	// Porta Sul de comunicação
	sc_signal< sc_bv<10> > Sin_data;
	sc_signal< bool > Sin_val;
	sc_signal< bool > Sout_ret;

	// Porta Oeste de comunicação
	sc_signal< sc_bv<10> > Win_data;
	sc_signal< bool > Win_val;
	sc_signal< bool > Wout_ret;


	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->rst(rst);

		tb0->Lin_data(Lin_data);
		tb0->Lin_val(Lin_val);
		tb0->Lin_ret(Lin_ret);
		tb0->Lout_data(Lout_data);
		tb0->Lout_val(Lout_val);
		tb0->Lout_ret(Lout_ret);

		tb0->Nin_data(Nin_data);
		tb0->Nin_val(Nin_val);
		tb0->Nin_ret(Nin_ret);
		tb0->Nout_data(Nout_data);
		tb0->Nout_val(Nout_val);
		tb0->Nout_ret(Nout_ret);

		tb0->Ein_data(Ein_data);
		tb0->Ein_val(Ein_val);
		tb0->Ein_ret(Ein_ret);
		tb0->Eout_data(Eout_data);
		tb0->Eout_val(Eout_val);
		tb0->Eout_ret(Eout_ret);

		tb0->Sin_data(Sin_data);
		tb0->Sin_val(Sin_val);
		tb0->Sin_ret(Sin_ret);
		tb0->Sout_data(Sout_data);
		tb0->Sout_val(Sout_val);
		tb0->Sout_ret(Sout_ret);

		tb0->Win_data(Win_data);
		tb0->Win_val(Win_val);
		tb0->Win_ret(Win_ret);
		tb0->Wout_data(Wout_data);
		tb0->Wout_val(Wout_val);
		tb0->Wout_ret(Wout_ret);

		tb0->clk(clk_sig);

		router0 = new Router("router0");
		router0->rst(rst);

		router0->Lin_data(Lin_data);
		router0->Lin_val(Lin_val);
		router0->Lin_ret(Lin_ret);
		router0->Lout_data(Lout_data);
		router0->Lout_val(Lout_val);
		router0->Lout_ret(Lout_ret);

		router0->Nin_data(Nin_data);
		router0->Nin_val(Nin_val);
		router0->Nin_ret(Nin_ret);
		router0->Nout_data(Nout_data);
		router0->Nout_val(Nout_val);
		router0->Nout_ret(Nout_ret);

		router0->Ein_data(Ein_data);
		router0->Ein_val(Ein_val);
		router0->Ein_ret(Ein_ret);
		router0->Eout_data(Eout_data);
		router0->Eout_val(Eout_val);
		router0->Eout_ret(Eout_ret);

		router0->Sin_data(Sin_data);
		router0->Sin_val(Sin_val);
		router0->Sin_ret(Sin_ret);
		router0->Sout_data(Sout_data);
		router0->Sout_val(Sout_val);
		router0->Sout_ret(Sout_ret);

		router0->Win_data(Win_data);
		router0->Win_val(Win_val);
		router0->Win_ret(Win_ret);
		router0->Wout_data(Wout_data);
		router0->Wout_val(Wout_val);
		router0->Wout_ret(Wout_ret);

		router0->clk(clk_sig);

	}

	~TopLevel(){
		delete tb0;
		delete router0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}